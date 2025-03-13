#include "../inc/core.hpp"

int main()
{
	start_clock();

	log( "Entering main()", INFO );

	InputsObject inputs;
	ScriptObject script;
	PhysicObject physic;
	RenderObject render;

	Object2D object;

	object.onInput();
	object.onUpdate();
	object.onTick();
	object.onRefresh();

	printf( "%u", object.getIsControlled());

	printf( "%u", object.getIsActive());

	printf( "%u", object.getIsDynamic());
	printf( "%u", object.getIsCollide());

	printf( "%u", object.getIsVisible());

	object.onInput();
	object.onUpdate();
	object.onTick();
	object.onRefresh();

	log( "Exiting main()", INFO );

	return 0;
}