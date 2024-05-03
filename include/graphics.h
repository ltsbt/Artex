#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

void initGraphics(const char *window_title, int window_options);
void cleanupGraphics();
void renderClear();
void renderPresent();
void renderBackground();
void showFileNamePreview(const char *current_file, bool did_file_change);

#endif
