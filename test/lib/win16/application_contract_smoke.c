#include "win16/application.h"

struct fixture {mygames_kvm_u8 view,exit;unsigned short ticks,keys;};
static struct mygames_kvm_text_frame text;
static mygames_kvm_u8 pixels[256];
static void input(void *context,const struct mygames_kvm_input_event *event)
{
    struct fixture *app=(struct fixture *)context;
    ++app->keys;
    if(event->kind==MYGAMES_KVM_INPUT_KEY && event->down && !event->repeat) {
        if(event->physical_code==MYGAMES_KVM_KEY_TAB)
            app->view=(mygames_kvm_u8)(app->view==MYGAMES_KVM_PRESENTATION_TEXT?
                MYGAMES_KVM_PRESENTATION_GRAPHICS:MYGAMES_KVM_PRESENTATION_TEXT);
        if(event->physical_code==MYGAMES_KVM_KEY_ESCAPE)app->exit=1U;
    }
}
static void tick(void *context){++((struct fixture *)context)->ticks;}
static mygames_kvm_u8 view(void *context){return ((struct fixture *)context)->view;}
static mygames_kvm_u8 exiting(void *context){return ((struct fixture *)context)->exit;}
static const struct mygames_kvm_text_frame MYGAMES_KVM_FAR *text_frame(void *context)
{(void)context;return &text;}
static int graphics(void *context,struct mygames_kvm_video_band *band)
{
    (void)context;band->pixels=pixels;band->first=0U;band->rows=1U;
    band->width=band->stride=256U;band->capacity=256U;return 1;
}
int main(void)
{
    struct fixture state={0U,0U,0U,0U};
    struct mygames_win16_application app={&state,"Contract fixture",
        MYGAMES_WIN16_VIEW_GRAPHICS|MYGAMES_WIN16_VIEW_TEXT,
        input,tick,view,exiting,text_frame,graphics,0,0U,256U,240U};
    struct mygames_kvm_input_event event={MYGAMES_KVM_INPUT_KEY,1U,0U,
        MYGAMES_KVM_KEY_TAB,0U,0U,0U,0U,0U,MYGAMES_KVM_COORD_NONE};
    struct mygames_kvm_video_band band;
    app.input(app.context,&event);
    app.tick(app.context);
    if(app.presentation(app.context)!=MYGAMES_KVM_PRESENTATION_TEXT || state.ticks!=1U)return 1;
    if(app.text(app.context)!=&text || !app.graphics(app.context,&band) ||
        band.pixels!=pixels || band.rows!=1U)return 2;
    event.physical_code=MYGAMES_KVM_KEY_ESCAPE;
    app.input(app.context,&event);
    if(!app.exit_requested(app.context) || state.keys!=2U)return 3;
    return 0;
}
