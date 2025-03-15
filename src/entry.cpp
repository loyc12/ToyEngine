#include "../inc/core.hpp"

int main()
{
	start_clock();

	log( "Entering main()", INFO );

	Engine *engine = getEngine();

	engine->addNewObject();

	log( "Launching", INFO );

	engine->launch();

	log( "Exiting main()", INFO );

	return 0;
}