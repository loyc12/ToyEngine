#include "../incs/base.hpp"
#include "../incs/core.hpp"
#include "../incs/game.hpp"

int main()
{
	log( "Initializing the Engine", INFO );

	Engine *engine = Engine::getEngine();


	engine->switchState( ES_RUNNING );

	engine->launchLoop();

	engine->switchState( ES_CLOSED );

	delete engine;

	log( "Exiting main()", INFO );
}