#include <raylib.h>
# include "../../incs/game.hpp"

// ===================== OBJECT STEP INJECTION FUNCTIONS
// called when the engine calls the these update method of any object

void OnRenderCall( RenderObject *obj )
{
	if ( obj == nullptr ){ return; }
	log( "OnEach:RenderObject()", INFO, obj->getID() );
}

void OnPhysicCall( PhysicObject *obj )
{
	if ( obj == nullptr ){ return; }
	log( "OnEach:PhysicObject()", INFO, obj->getID() );

	//obj->changeAcceleration( { 0.0f, 0.1f } ); // DEBUG : gravity
	//obj->moveAngle( 1.0f ); // DEBUG : rotation
}

void OnScriptCall( ScriptObject *obj )
{
	if ( obj == nullptr ){ return; }
	log( "OnEach:ScriptObject()", INFO, obj->getID() );
}
