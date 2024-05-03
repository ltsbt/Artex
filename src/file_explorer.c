#include "../include/file_explorer.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// compare file names ignoring case
int compare_file_names(const void *a, const void *b) {
  return strcasecmp((const char *)a, (const char *)b);
}

FileList list_files(const char *dir_path) {

  DIR *dir;
  struct dirent *entry;

  FileList list;
  memset(list.file_names, 0, sizeof(list.file_names));
  list.count = 0;

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

    strncpy(list.file_names[list.count], entry->d_name, MAX_FILE_NAME_LENGTH);
    list.count++;
  }

  (void)closedir(dir);

  // sort the file names
  qsort(list.file_names, list.count, MAX_FILE_NAME_LENGTH, compare_file_names);

  return list;
}
