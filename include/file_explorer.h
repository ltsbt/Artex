#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#define MAX_FILE_COUNT 100
#define MAX_FILE_NAME_LENGTH 512

typedef struct {
  char file_names[MAX_FILE_COUNT][MAX_FILE_NAME_LENGTH];
  int count;
} FileList;

FileList list_files(const char *dir_path);

#endif
