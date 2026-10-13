#include "win32/pcm.h"
#include <string.h>
static const struct mygames_win32_pcm_api system_api={waveOutOpen,waveOutPrepareHeader,
 waveOutWrite,waveOutReset,waveOutUnprepareHeader,waveOutClose};
int mygames_win32_pcm_open_event(struct mygames_win32_pcm *pcm,unsigned long rate,
 unsigned short channels,unsigned short bits,WAVEHDR *headers,unsigned char *queued,
 void *samples,unsigned short count,unsigned short bytes,const struct mygames_win32_pcm_api *api,HANDLE completion)
{
 WAVEFORMATEX format;unsigned short i,align;
 if(!pcm || pcm->device || !headers || !queued || !samples || !count || count>256U ||
    !rate || rate>192000UL || (channels!=1U && channels!=2U) || (bits!=8U && bits!=16U))return 0;
 align=(unsigned short)(channels*(bits/8U));if(!bytes || bytes%align)return 0;
 if(!api)api=&system_api;
 if(!api->open || !api->prepare || !api->write || !api->reset || !api->unprepare || !api->close)return 0;
 memset(pcm,0,sizeof(*pcm));memset(&format,0,sizeof(format));
 pcm->api=api;pcm->headers=headers;pcm->queued=queued;pcm->samples=(unsigned char *)samples;
 pcm->count=count;pcm->block_bytes=bytes;memset(queued,0,count);memset(headers,0,count*sizeof(*headers));
 format.wFormatTag=WAVE_FORMAT_PCM;format.nChannels=channels;format.wBitsPerSample=bits;
 format.nSamplesPerSec=rate;format.nBlockAlign=align;format.nAvgBytesPerSec=rate*align;
 pcm->result=api->open(&pcm->device,WAVE_MAPPER,&format,(DWORD_PTR)completion,0,
    completion?CALLBACK_EVENT:CALLBACK_NULL);
 if(pcm->result!=MMSYSERR_NOERROR){pcm->device=0;return 0;}
 for(i=0;i<count;++i){
  headers[i].lpData=(LPSTR)(pcm->samples+(unsigned long)i*bytes);headers[i].dwBufferLength=bytes;
  pcm->result=api->prepare(pcm->device,&headers[i],sizeof(WAVEHDR));
  if(pcm->result!=MMSYSERR_NOERROR){MMRESULT error=pcm->result;mygames_win32_pcm_close(pcm);pcm->result=error;return 0;}
  ++pcm->prepared;
 }
 return 1;
}
int mygames_win32_pcm_open(struct mygames_win32_pcm *pcm,unsigned long rate,
 unsigned short channels,unsigned short bits,WAVEHDR *headers,unsigned char *queued,
 void *samples,unsigned short count,unsigned short bytes,const struct mygames_win32_pcm_api *api)
{
 return mygames_win32_pcm_open_event(pcm,rate,channels,bits,headers,queued,samples,count,bytes,api,NULL);
}
int mygames_win32_pcm_acquire(struct mygames_win32_pcm *pcm)
{
 unsigned short offset,index;
 if(!pcm || !pcm->device || pcm->prepared!=pcm->count)return -1;
 for(offset=0;offset<pcm->count;++offset){index=(unsigned short)((pcm->next+offset)%pcm->count);
  if(!pcm->queued[index] || (pcm->headers[index].dwFlags&WHDR_DONE))return index;
 }
 return -1;
}
int mygames_win32_pcm_submit(struct mygames_win32_pcm *pcm,unsigned short index)
{
 if(!pcm || !pcm->device || index>=pcm->prepared ||
    (pcm->queued[index] && !(pcm->headers[index].dwFlags&WHDR_DONE)))return 0;
 pcm->result=pcm->api->write(pcm->device,&pcm->headers[index],sizeof(WAVEHDR));
 if(pcm->result!=MMSYSERR_NOERROR)return 0;
 pcm->queued[index]=1;pcm->next=(unsigned short)((index+1U)%pcm->count);return 1;
}
int mygames_win32_pcm_reset(struct mygames_win32_pcm *pcm)
{
 if(!pcm)return 0;
 pcm->result=pcm->device?pcm->api->reset(pcm->device):MMSYSERR_NOERROR;
 if(pcm->result!=MMSYSERR_NOERROR)return 0;
 if(pcm->queued)memset(pcm->queued,0,pcm->count);
 pcm->next=0;return 1;
}
int mygames_win32_pcm_close(struct mygames_win32_pcm *pcm)
{
 if(!pcm)return 0;
 if(!pcm->device)return 1;
 pcm->result=pcm->api->reset(pcm->device);
 if(pcm->result!=MMSYSERR_NOERROR)return 0;
 while(pcm->prepared) {
  pcm->result=pcm->api->unprepare(pcm->device,&pcm->headers[pcm->prepared-1U],sizeof(WAVEHDR));
  if(pcm->result!=MMSYSERR_NOERROR)return 0;
  --pcm->prepared;
 }
 pcm->result=pcm->api->close(pcm->device);
 if(pcm->result!=MMSYSERR_NOERROR)return 0;
 pcm->device=0;return 1;
}
