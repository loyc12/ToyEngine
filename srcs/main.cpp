#include "../incs/base.hpp"
#include "../incs/core.hpp"
#include "../incs/game.hpp"

int main()
{
	log( "Initializing the Engine", INFO );

	GNG->switchState( ES_RUNNING );

	GNG->launchLoop();

	GNG->switchState( ES_CLOSED );

	delete GNG;   GNG = nullptr;

	log( "Exiting main()", INFO );
}