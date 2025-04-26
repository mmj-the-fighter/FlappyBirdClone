#include <iostream>
#include "game.h"

void Game::Init(spn::SpinachCore* sc) 
{
	sc->GetCanvas()->SetPrimaryColor(255, 255, 255);
	sc->GetCanvas()->SetClearColor(0, 0, 128);
	ww = sc->GetCanvas()->GetWidth();
	wh = sc->GetCanvas()->GetHeight();
	bird = new Bird;
	bird->Init(ww, wh);
}

void Game::UpdateAndRender(spn::Canvas* canvas)
{
	bird->Move(canvas);
	canvas->Clear();
	bird->Display(canvas);
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
	//std::cout << "lmb down\n";
	bird->OnLeftMouseButtonDown();
}

void Game::OnRmbDown() {
	std::cout << "rmb down\n";
}

