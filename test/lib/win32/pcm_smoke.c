#include <string.h>
#include "win32/pcm.h"
static unsigned open_calls,prepare_calls,write_calls,reset_calls,unprepare_calls,close_calls;
static int fault;
static MMRESULT WINAPI open_device(LPHWAVEOUT device,UINT id,LPCWAVEFORMATEX format,DWORD_PTR cb,DWORD_PTR context,DWORD flags)
{(void)id;(void)cb;(void)context;(void)flags;++open_calls;if(format->nSamplesPerSec!=8000 || format->nBlockAlign!=1)return 1;*device=(HWAVEOUT)1;return fault==1?1:0;}
static MMRESULT WINAPI prepare(HWAVEOUT device,LPWAVEHDR header,UINT bytes)
{(void)device;(void)header;(void)bytes;++prepare_calls;return fault==2 && prepare_calls==2?1:0;}
static MMRESULT WINAPI write_block(HWAVEOUT device,LPWAVEHDR header,UINT bytes)
{(void)device;(void)bytes;++write_calls;if(fault==3)return 1;header->dwFlags&=~WHDR_DONE;return 0;}
static MMRESULT WINAPI reset(HWAVEOUT device){(void)device;++reset_calls;return fault==4?1:0;}
static MMRESULT WINAPI unprepare(HWAVEOUT device,LPWAVEHDR h,UINT n){(void)device;(void)h;(void)n;++unprepare_calls;return 0;}
static MMRESULT WINAPI close_device(HWAVEOUT device){(void)device;++close_calls;return 0;}
int main(void)
{
 const struct mygames_win32_pcm_api api={open_device,prepare,write_block,reset,unprepare,close_device};
 struct mygames_win32_pcm pcm;WAVEHDR headers[2];unsigned char queued[2],samples[16];
 memset(&pcm,0,sizeof(pcm));
 if(mygames_win32_pcm_acquire(&pcm)!=-1 || mygames_win32_pcm_submit(&pcm,0))return 1;
 if(mygames_win32_pcm_open(&pcm,8000,3,8,headers,queued,samples,2,8,&api) || open_calls)return 2;
 fault=1;if(mygames_win32_pcm_open(&pcm,8000,1,8,headers,queued,samples,2,8,&api) || pcm.device)return 3;
 fault=2;if(mygames_win32_pcm_open(&pcm,8000,1,8,headers,queued,samples,2,8,&api) || unprepare_calls!=1 || close_calls!=1)return 4;
 fault=0;if(!mygames_win32_pcm_open(&pcm,8000,1,8,headers,queued,samples,2,8,&api))return 5;
 if(headers[1].lpData!=(LPSTR)(samples+8) || headers[1].dwBufferLength!=8 || mygames_win32_pcm_acquire(&pcm)!=0)return 6;
 fault=3;if(mygames_win32_pcm_submit(&pcm,0) || queued[0] || pcm.next)return 7;
 fault=0;if(!mygames_win32_pcm_submit(&pcm,0) || !mygames_win32_pcm_submit(&pcm,1) || mygames_win32_pcm_acquire(&pcm)!=-1 || mygames_win32_pcm_submit(&pcm,1))return 8;
 headers[0].dwFlags|=WHDR_DONE;if(mygames_win32_pcm_acquire(&pcm)!=0)return 9;
 fault=4;if(mygames_win32_pcm_reset(&pcm) || !queued[1])return 10;
 if(mygames_win32_pcm_close(&pcm) || !pcm.device || close_calls!=1)return 13;
 fault=0;if(!mygames_win32_pcm_reset(&pcm) || queued[0] || queued[1] || pcm.next)return 11;
 mygames_win32_pcm_close(&pcm);mygames_win32_pcm_close(&pcm);
 if(close_calls!=2 || unprepare_calls!=3 || pcm.device)return 12;
 return 0;
}
