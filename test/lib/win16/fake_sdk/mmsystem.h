#include <windows.h>
typedef unsigned short HWAVEOUT;
typedef struct { char *lpData; DWORD dwBufferLength,dwBytesRecorded,dwUser,dwFlags,dwLoops; void *lpNext; DWORD reserved; } WAVEHDR;
typedef struct { UINT wFormatTag,nChannels; DWORD nSamplesPerSec,nAvgBytesPerSec; UINT nBlockAlign; } WAVEFORMAT;
typedef struct { WAVEFORMAT wf; UINT wBitsPerSample; } PCMWAVEFORMAT;
#define MMSYSERR_NOERROR 0
#define MMSYSERR_ALLOCATED 4
#define WAVE_FORMAT_PCM 1
#define WAVE_MAPPER 65535
#define CALLBACK_NULL 0
#define WHDR_INQUEUE 16
#define WHDR_PREPARED 2
