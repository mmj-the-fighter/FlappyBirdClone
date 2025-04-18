#ifndef _GAME_H_
#define _GAME_H_

#include <SDL3/SDL.h>
#include "../spinach/core/spn_core.h"
#include "../spinach/core/spn_canvas.h"

class Game
{
public:
	Game() {}
	~Game() {}
	void Init(spn::SpinachCore* sc) {}
	void Restart() {}
	void UpdateAndRender(spn::Canvas* canvas) {}
	void HandleInput(const SDL_Event* sdlEvent) {}
private:
	bool gameOver;
	int ww, wh;
};

#endif
