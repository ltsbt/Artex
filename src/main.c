#include "../include/file_explorer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>

const char *WINDOW_TITLE = "Artex";
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

const char *FONT_PATH = "../assets/fonts/Perfect DOS VGA 437.ttf";
const char *BACKGROUND_PATH = "../assets/textures/background.png";
const int FONT_SIZE = 256;
const int OUTLINE_SIZE = 2;
const SDL_Color TEXT_COLOR = {255, 255, 255, 255};
const SDL_Color TEXT_OUTLINE_COLOR = {0, 0, 0, 255};

int main(int argc, char *argv[]) {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *bg_texture;
  TTF_Font *font;
  TTF_Font *font_outline;
  SDL_Surface *text_surface;
  SDL_Surface *text_outline_surface;
  SDL_Texture *text_texture;
  SDL_Texture *text_outline_texture;
  SDL_Rect text_rect;
  SDL_Event event;

  const char *dir_path = argc > 1 ? argv[1] : ".";
  FileList file_list = list_files(dir_path);

  if (file_list.count == 0) {
    fprintf(stderr, "No files found in %s\n", dir_path);
    return 1;
  }

  int current_index = 0;
  char *current_file = "test";
  bool should_quit = false;
  bool did_file_change = false;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_RESIZABLE);

  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    return 1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    return 1;
  }

  SDL_Surface *surface = IMG_Load(BACKGROUND_PATH);

  if (surface == NULL) {
    fprintf(stderr, "IMG_Load failed: %s\n", IMG_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 1;
  }

  bg_texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (bg_texture == NULL) {
    fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n",
            SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 1;
  }

  // load font
  if (TTF_Init() != 0) {
    fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 1;
  }

  font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
  font_outline = TTF_OpenFont(FONT_PATH, FONT_SIZE);

  if (font == NULL) {
    fprintf(stderr, "TTF_OpenFont failed: %s\n", TTF_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 1;
  }

  TTF_SetFontOutline(font_outline, OUTLINE_SIZE);

  text_surface = TTF_RenderText_Solid(font, current_file, TEXT_COLOR);
  text_outline_surface =
      TTF_RenderText_Solid(font_outline, current_file, TEXT_OUTLINE_COLOR);

  text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

  text_outline_texture =
      SDL_CreateTextureFromSurface(renderer, text_outline_surface);

  SDL_FreeSurface(surface);

  while (!should_quit) {
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
          // TODO: update current file
          break;
        case SDLK_RIGHT:
          current_index =
              current_index == file_list.count - 1 ? 0 : current_index + 1;
          // TODO: update current file
          break;
        }
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bg_texture, NULL, NULL);

    // update text if file has changed
    if (did_file_change) {
      SDL_FreeSurface(text_surface);
      SDL_FreeSurface(text_outline_surface);
      text_surface = TTF_RenderText_Solid(font, current_file, TEXT_COLOR);
      text_outline_surface =
          TTF_RenderText_Solid(font_outline, current_file, TEXT_OUTLINE_COLOR);

      SDL_DestroyTexture(text_texture);
      SDL_DestroyTexture(text_outline_texture);
      text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
      text_outline_texture =
          SDL_CreateTextureFromSurface(renderer, text_outline_surface);
    }

    // center text on the screen
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
    text_rect.x = (window_width - text_rect.w) / 2;
    text_rect.y = (window_height - text_rect.h) / 2;

    // write text to the screen
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_RenderCopy(renderer, text_outline_texture, NULL, &text_rect);

    SDL_RenderPresent(renderer);
    SDL_Delay(FRAME_DELAY);
  }

  return 0;
}
