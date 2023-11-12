#include <stdio.h>
#include <string.h>
#include <math.h>
#include "swr/swr_sdl_window.h"
#include "swr/swr_rasterizer.h"
#include "swr/swr_image.h"
#include "swr/swr_rfont.h"

#include "game/Game.h"


Game game;
swr_sdl_context* ctx;

void capture_screen()
{
	write_bmp2(NULL, ctx->screen_texture_pixels,
		ctx->screen_texture_pixels_wide,
		ctx->screen_texture_pixels_high);
}

void tick_and_render(swr_sdl_context *ct)
{
	game.Tick(ct);
	game.Display();
}

void init()
{
	game.Init();
}

int input(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN) {
		switch (e->key.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			return 1;
		case SDL_SCANCODE_F12:
			capture_screen();
			break;
		}
	}
	else if (e->type == SDL_MOUSEBUTTONDOWN){
		if (e->button.button == SDL_BUTTON_LEFT){
			game.OnLeftMouseButtonDown();
		}
		else if (e->button.button == SDL_BUTTON_RIGHT){
			game.OnRightMouseButtonDown();
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	game.Init();
	swr_sdl_create_context(GAME_RESOLUTION_X, GAME_RESOLUTION_Y);
	swr_sdl_set_input_handler(input);
	swr_sdl_set_display_handler(tick_and_render);
	ctx = swr_sdl_get_context();
	rasterizer_set_swr_sdl_context(ctx);
	rasterizer_set_cur_color(255, 255, 255, ctx->opaque_alpha_value);
	rasterizer_set_clear_color(0, 0, 128, ctx->transparent_alpha_value);
	swr_sdl_main_loop();
	swr_sdl_destroy_context();
	return 0;
}
