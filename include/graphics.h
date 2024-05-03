#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

/**
 * Initialize the graphics system. Must be called before any other graphics
 * functions.
 *
 * This function creates the SDL window and renderer and loads the fonts and
 * textures.
 *
 * @param window_title The title of the window.
 * @param window_options The options for the window.
 */
void initGraphics(const char *window_title, int window_options);

/**
 * Cleanup the graphics system's resources. Must be called after all other
 * graphics functions.
 */
void cleanupGraphics();
void renderClear();
void renderPresent();
void renderBackground();
void showFileNamePreview(const char *current_file, bool did_file_change);

#endif
