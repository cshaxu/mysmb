#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "dos16/file.h"
static int put(const char *name,const char *value){FILE *f=fopen(name,"wb");if(!f)return 0;fputs(value,f);return fclose(f)==0;}
int main(void)
{
 FILE *f;char text[8]={0};
 remove("next.tmp");remove("slot.dat");_rmdir("target");
 if(!put("next.tmp","first") || !mygames_dos16_file_replace("next.tmp","slot.dat"))return 1;
 if(!put("next.tmp","second") || !mygames_dos16_file_replace("next.tmp","slot.dat"))return 2;
 f=fopen("slot.dat","rb");if(!f)return 3;fread(text,1,6,f);fclose(f);if(strcmp(text,"second"))return 4;
 if(_mkdir("target") || !put("target/keep.dat","x") || !put("next.tmp","x"))return 5;
 if(mygames_dos16_file_replace("next.tmp","target") || mygames_dos16_file_replace("next.tmp","absent/file.dat"))return 6;
 remove("target/keep.dat");_rmdir("target");remove("next.tmp");remove("slot.dat");return 0;
}
