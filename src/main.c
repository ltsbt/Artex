#include "../include/file_explorer.h"
#include "../include/graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>

const char *WINDOW_TITLE = "Artex";

int main(int argc, char *argv[]) {
  // ========================================================
  // ================== File list ===========================
  // ========================================================
  const char *dir_path = argc > 1 ? argv[1] : ".";
  const FileList file_list = list_files(dir_path);
  if (file_list.count == 0) {
    fprintf(stderr, "No files found in %s\n", dir_path);
    return 1;
  }

  int current_index = 0;
  char current_file[32] = "";
  strncpy(current_file, file_list.file_names[0], sizeof(current_file));

  // ========================================================
  // ================== SDL initialization ==================
  // ========================================================
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  initGraphics(WINDOW_TITLE, SDL_WINDOW_RESIZABLE);

  // ========================================================
  // ================== Main loop ===========================
  // ========================================================
  SDL_Event event;
  bool should_quit = false;
  bool did_file_change = true;

  while (!should_quit) {
    // ================ Event handling ======================
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        should_quit = true;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_q:
          should_quit = true;
          break;
        case SDLK_LEFT:
          current_index =
              current_index == 0 ? file_list.count - 1 : current_index - 1;
          strncpy(current_file, file_list.file_names[current_index],
                  sizeof(current_file));
          did_file_change = true;
          break;
        case SDLK_RIGHT:
          current_index =
              current_index == file_list.count - 1 ? 0 : current_index + 1;
          strncpy(current_file, file_list.file_names[current_index],
                  sizeof(current_file));
          did_file_change = true;
          break;
        }
      }
    }

    // ================ Rendering ===========================
    renderClear();
    renderBackground();
    showFileNamePreview(current_file, did_file_change);

    // ================ Update screen =======================
    renderPresent();
    delay();
  }

  // ========================================================
  // ================== Cleanup =============================
  // ========================================================
  cleanupGraphics();
  TTF_Quit();
  SDL_Quit();

  return 0;
}
