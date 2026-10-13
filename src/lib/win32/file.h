#ifndef MYGAMES_WIN32_FILE_H
#define MYGAMES_WIN32_FILE_H
unsigned long mygames_win32_executable_path(char *path,unsigned short capacity);
int mygames_win32_file_replace(const char *pending,const char *final_name);
#endif
