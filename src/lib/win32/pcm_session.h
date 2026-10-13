#ifndef MYGAMES_WIN32_PCM_SESSION_H
#define MYGAMES_WIN32_PCM_SESSION_H
#include "win32/pcm.h"
#include "kvm/audio.h"
struct mygames_win32_pcm_session;
/* Lifetime-resource seam; callbacks are copied and remain callable through
 * terminal release. The default uses the process heap and Windows handles. */
struct mygames_win32_pcm_resources {
 void *(*allocate)(SIZE_T);
 void (*free)(void *);
 HANDLE (*event)(void);
 HANDLE (*thread)(LPTHREAD_START_ROUTINE,void *);
 void (*close)(HANDLE);
};
/* Single producer. begin/status/acquire/publish/reset/stop/release never call
 * the driver or wait for its thread. NULL is a safely absent device. */
struct mygames_win32_pcm_session *mygames_win32_pcm_session_begin(
 unsigned long rate,unsigned short bits,unsigned short count,unsigned short bytes,
 const struct mygames_win32_pcm_api *api);
struct mygames_win32_pcm_session *mygames_win32_pcm_session_begin_with_resources(
 unsigned long rate,unsigned short bits,unsigned short count,unsigned short bytes,
 const struct mygames_win32_pcm_api *,const struct mygames_win32_pcm_resources *);
int mygames_win32_pcm_session_phase(struct mygames_win32_pcm_session *);
MMRESULT mygames_win32_pcm_session_error(struct mygames_win32_pcm_session *);
int mygames_win32_pcm_session_stalled(struct mygames_win32_pcm_session *,DWORD budget);
void *mygames_win32_pcm_session_acquire(struct mygames_win32_pcm_session *,int *slot);
void mygames_win32_pcm_session_publish(struct mygames_win32_pcm_session *,int slot);
/* One outstanding reset. Same request ID returned until acknowledged. */
LONG mygames_win32_pcm_session_reset(struct mygames_win32_pcm_session *);
int mygames_win32_pcm_session_reset_result(struct mygames_win32_pcm_session *,LONG id);
void mygames_win32_pcm_session_stop(struct mygames_win32_pcm_session *);
/* Returns0 while the driver or producer still borrows storage. */
int mygames_win32_pcm_session_release(struct mygames_win32_pcm_session **);
#endif
