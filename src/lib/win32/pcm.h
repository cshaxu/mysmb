#ifndef MYGAMES_WIN32_PCM_H
#define MYGAMES_WIN32_PCM_H
#include <windows.h>
#include <mmsystem.h>
/* Synchronous control of caller-owned PCM blocks. No synthesis, cadence or
 * overflow/drop policy. Zero-initialize before open; storage remains valid
 * until close returns1. A failed close retains ownership for a later retry. */
struct mygames_win32_pcm_api {
 MMRESULT (WINAPI *open)(LPHWAVEOUT,UINT,LPCWAVEFORMATEX,DWORD_PTR,DWORD_PTR,DWORD);
 MMRESULT (WINAPI *prepare)(HWAVEOUT,LPWAVEHDR,UINT);
 MMRESULT (WINAPI *write)(HWAVEOUT,LPWAVEHDR,UINT);
 MMRESULT (WINAPI *reset)(HWAVEOUT);
 MMRESULT (WINAPI *unprepare)(HWAVEOUT,LPWAVEHDR,UINT);
 MMRESULT (WINAPI *close)(HWAVEOUT);
};
struct mygames_win32_pcm {
 HWAVEOUT device;WAVEHDR *headers;unsigned char *queued,*samples;
 unsigned short count,block_bytes,prepared,next;
 const struct mygames_win32_pcm_api *api;
};
int mygames_win32_pcm_open(struct mygames_win32_pcm *,unsigned long rate,
 unsigned short channels,unsigned short bits,WAVEHDR *,unsigned char *queued,
 void *samples,unsigned short count,unsigned short block_bytes,
 const struct mygames_win32_pcm_api *api);
int mygames_win32_pcm_acquire(struct mygames_win32_pcm *);
int mygames_win32_pcm_submit(struct mygames_win32_pcm *,unsigned short index);
int mygames_win32_pcm_reset(struct mygames_win32_pcm *);
int mygames_win32_pcm_close(struct mygames_win32_pcm *);
#endif
