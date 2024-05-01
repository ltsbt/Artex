#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

typedef struct {
  char **file_names;
  int count;
} FileList;

FileList list_files(const char *dir_path);

#endif
