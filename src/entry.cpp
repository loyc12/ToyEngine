#include "../inc/core.hpp"

int main()
{
	start_clock();

	log( "Entering main()", INFO );

	//InputsObject inputs;
	//ScriptObject script;
	//PhysicObject physic;
	//RenderObject render;

	Object2D obj1;
	Object2D obj2;

	log( "step", INFO );

	printf( "\n%u\n", obj1.getType());
	printf( "%u\n", obj1.getID());

	printf( "%u\n", obj1.getIsControlled());
	printf( "%u\n", obj1.getIsActive());
	printf( "%u\n", obj1.getIsDynamic());
	printf( "%u\n", obj1.getIsCollide());
	printf( "%u\n\n", obj1.getIsVisible());

	log( "step", INFO );

	obj1.setIsActive( false );
	obj1.setIsControlled( false );
	obj1.setIsDynamic( false );
	obj1.setIsCollide( false );
	obj1.setIsVisible( false );

	log( "step", INFO );

	printf( "\n%u\n", obj1.getType());
	printf( "%u\n", obj1.getID());

	printf( "%u\n", obj1.getIsControlled());
	printf( "%u\n", obj1.getIsActive());
	printf( "%u\n", obj1.getIsDynamic());
	printf( "%u\n", obj1.getIsCollide());
	printf( "%u\n\n", obj1.getIsVisible());

	log( "step", INFO );

	obj1 = obj2;

	log( "step", INFO );

	printf( "\n%u\n", obj1.getType());
	printf( "%u\n", obj1.getID());

	printf( "%u\n", obj1.getIsControlled());
	printf( "%u\n", obj1.getIsActive());
	printf( "%u\n", obj1.getIsDynamic());
	printf( "%u\n", obj1.getIsCollide());
	printf( "%u\n\n", obj1.getIsVisible());

	log( "Exiting main()", INFO );

	sleep( 5 );

	log_time();

	return 0;
}