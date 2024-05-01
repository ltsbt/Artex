#include "../include/file_explorer.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

FileList list_files(const char *dir_path) {

  DIR *dir;
  struct dirent *entry;

  FileList list;
  list.file_names = malloc(10 * sizeof(char *));
  list.count = 0;
  int capacity = 10;

  dir = opendir(dir_path);

  if (dir == NULL) {
    perror("Couldn't open the directory");
    exit(1);
  }

  while ((entry = readdir(dir))) {
    // skip hidden files and directories
    if (entry->d_name[0] == '.') {
      continue;
    }

    if (list.count == capacity) {
      capacity *= 2;
      list.file_names = realloc(list.file_names, capacity * sizeof(char *));
    }
    list.file_names[list.count] = entry->d_name;
    list.count++;
  }

  (void)closedir(dir);

  return list;
}
