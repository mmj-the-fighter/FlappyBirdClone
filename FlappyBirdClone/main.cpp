#include <iostream>
#include "spinach/core/spn_canvas.h"
#include "spinach/core/spn_core.h"
#include "game/game.h"

int main() {
	Game game;
	spn::SpinachCore sc(800, 600);
	if (sc.IsInitFailed()) {
		std::cout << "initialization failed with error "
			<< sc.GetInitializationResult()
			<< std::endl;
		return 1;
	}
	//sc.SetWindowTitle("Flappy Bird Clone");
	game.Init(&sc);
	sc.SetUpdateAndRenderHandler(
		std::bind(&Game::UpdateAndRender,
			&game,
			std::placeholders::_1));

	sc.SetInputHandler(
		std::bind(&Game::HandleInput,
			&game,
			std::placeholders::_1));
	sc.MainLoop();
	return 0;
}