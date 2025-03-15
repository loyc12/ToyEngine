#include "../inc/core.hpp"

int main()
{
	start_clock();
	Engine *engine = Engine::getEngine();

	log( "Adding object", INFO );
	Object2D *obj = new Object2D();

	log( "Deleting object", INFO );
	delete obj;

	//log( "Launching Engine", INFO );
	engine->launch();

	log( "Closing Engine", INFO );
	engine->close();

	log( "Object count : ", INFO );
	cout << engine->getObjectCount() << endl;

	log( "Exiting main()", INFO );
	return 0;
}