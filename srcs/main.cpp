#include "../incs/core.hpp"

int main()
{
	start_clock();
	Engine *engine = Engine::getEngine();

	log( "Adding objects", INFO );

	new Object2D();
	new Object2D();
	new Object2D();

	//log( "Launching Engine", INFO );
	//engine->launch();

	log( "Running an Egine step", INFO );
	InitWindow( SCREEN_STARTING_WIDTH, SCREEN_STARTING_HEIGHT, WINDOW_STARTING_TITLE );
	engine->runStep();

	log( "Object count : " + tostr( engine->getObjectCount() ), DEBUG );

	log( "Closing Engine", INFO );
	engine->close();
	delete engine;

	log( "Exiting main()", INFO );

	return 0;
}