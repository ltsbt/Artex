#include "../include/graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void initGraphics(const char *window_title, int window_options);
void initFonts();
void initTextures();
void cleanupGraphics();
void cleanupFonts();
void cleanupTextures();
void renderClear();
void renderPresent();
void renderBackground();
SDL_Texture *getImageTexture(const char *path, SDL_Renderer *renderer);
void showFileNamePreview(const char *current_file, bool did_file_change);

static const char *BACKGROUND_PATH = "../assets/textures/background.png";
static const char *FONT_PATH = "../assets/fonts/Perfect DOS VGA 437.ttf";
static const int FONT_SIZE = 64;
static const int OUTLINE_SIZE = 1;

static SDL_Window *window;
static SDL_Renderer *renderer;
static TTF_Font *font;
static TTF_Font *font_outline;
static SDL_Texture *text_texture;
static SDL_Texture *text_outline_texture;
static SDL_Texture *background_texture;

static const SDL_Color TEXT_COLOR = {255, 255, 255, 255};
static const SDL_Color TEXT_OUTLINE_COLOR = {0, 0, 0, 255};

void initGraphics(const char *window_title, int window_options) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    exit(1);
  }

  window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800, 600, window_options);
  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    exit(1);
  }

  initFonts();
  initTextures();
}

void initFonts() {
  if (TTF_Init() != 0) {
    fprintf(stderr, "TTF_Init failed: %s\n", TTF_GetError());
    exit(1);
  }

  font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
  font_outline = TTF_OpenFont(FONT_PATH, FONT_SIZE);

  if (font == NULL) {
    fprintf(stderr, "TTF_OpenFont failed: %s\n", TTF_GetError());
    exit(1);
  }

  TTF_SetFontOutline(font_outline, OUTLINE_SIZE);
}

void initTextures() {
  background_texture = getImageTexture(BACKGROUND_PATH, renderer);
}

void cleanupGraphics() {
  cleanupFonts();
  cleanupTextures();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_Quit();
  SDL_Quit();
}

void cleanupFonts() {
  TTF_CloseFont(font);
  TTF_CloseFont(font_outline);

  SDL_DestroyTexture(text_texture);
  SDL_DestroyTexture(text_outline_texture);
}

void cleanupTextures() { SDL_DestroyTexture(background_texture); }

void renderClear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void renderPresent() { SDL_RenderPresent(renderer); }

void renderBackground() {
  SDL_RenderCopy(renderer, background_texture, NULL, NULL);
}

SDL_Texture *getImageTexture(const char *path, SDL_Renderer *renderer) {
  SDL_Surface *surface = IMG_Load(path);
  if (surface == NULL) {
    fprintf(stderr, "IMG_Load failed: %s\n", IMG_GetError());
    exit(1);
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == NULL) {
    fprintf(stderr, "SDL_CreateTextureFromSurface failed: %s\n",
            SDL_GetError());
    exit(1);
  }

  SDL_FreeSurface(surface);
  return texture;
}

void showFileNamePreview(const char *current_file, bool did_file_change) {
  SDL_Rect text_rect;
  // if the file name has changed, update the text surfaces and textures
  if (did_file_change) {
    SDL_Surface *text_surface =
        TTF_RenderText_Solid(font, current_file, TEXT_COLOR);
    SDL_Surface *text_outline_surface =
        TTF_RenderText_Solid(font_outline, current_file, TEXT_OUTLINE_COLOR);

    SDL_DestroyTexture(text_texture);
    SDL_DestroyTexture(text_outline_texture);
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    text_outline_texture =
        SDL_CreateTextureFromSurface(renderer, text_outline_surface);
    SDL_FreeSurface(text_surface);
    SDL_FreeSurface(text_outline_surface);
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
}
