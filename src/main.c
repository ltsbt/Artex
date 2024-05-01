#include "../include/file_explorer.h"
#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  // receive directory from user, else use current directory
  char *dir = argc > 1 ? argv[1] : ".";

  FileList files = list_files(dir);

  for (int i = 0; i < files.count; i++) {
    printf("%s\n", files.file_names[i]);
  }

  return 0;
}
