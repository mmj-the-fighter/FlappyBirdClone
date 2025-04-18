#include <iostream>
#include "game.h"

void Game::Init(spn::SpinachCore* sc) 
{
	sc->GetCanvas()->SetPrimaryColor(255, 255, 255);
	sc->GetCanvas()->SetClearColor(0, 0, 128);
}

void Game::UpdateAndRender(spn::Canvas* canvas)
{
	canvas->Clear();
}

void Game::HandleInput(const SDL_Event* sdlEvent) 
{
	if (sdlEvent->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (sdlEvent->button.button == SDL_BUTTON_LEFT) {
			OnLmbDown();
		}
		else if (sdlEvent->button.button == SDL_BUTTON_RIGHT) {
			OnRmbDown();
		}
	}
}

void Game::OnLmbDown() {
	std::cout << "lmb down\n";
}

void Game::OnRmbDown() {
	std::cout << "rmb down\n";
}

