#include "game.h"

int main(int argc, char* argv[])
{
	using namespace mcomm;

	Game::instance().setup();
	Game::instance().run();
	return 0;
}
