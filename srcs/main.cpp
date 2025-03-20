#include "../incs/base.hpp"
#include "../incs/core.hpp"
#include "../incs/game.hpp"

int main()
{
	log( "Initializing the Engine", INFO );
	start_clock();

	Engine *engine = Engine::getEngine();

	log( "Starting Engine", INFO );

	engine->start();

	log( "Launching Engine", INFO );

	engine->launch();
	//engine->runStep();

	log( "Closing Engine", INFO );

	engine->close();
	delete engine;

	log( "Exiting main()", INFO );
}