#include <raylib.h>
# include "../../incs/game.hpp"

// ===================== OBJECT STEP INJECTION FUNCTIONS
// called when the engine calls the these update method of any object

void OnRenderCall( RenderObject *obj )
{
	if ( obj == nullptr ){ return; }
	flog( obj->getID() );
}

void OnPhysicCall( PhysicObject *obj )
{
	if ( obj == nullptr ){ return; }
	flog( obj->getID() );

	/*
	//obj->changeAcceleration( { 0.0f, 0.1f } ); // DEBUG : gravity
	if ( GIN().EQU ) { obj->moveAngle( 1.0f ); }  // DEBUG : rotation
	if ( GIN().MIN ) { obj->moveAngle( -1.0f ); } // DEBUG : rotation

	if ( GIN().K8 ) { obj->movePosition( { 0.0f,  -1.0f } ); } // DEBUG : move up
	if ( GIN().K2 ) { obj->movePosition( { 0.0f,  1.0f  } ); } // DEBUG : move down
	if ( GIN().K4 ) { obj->movePosition( { -1.0f, 0.0f  } ); } // DEBUG : move left
	if ( GIN().K6 ) { obj->movePosition( { 1.0f,  0.0f  } ); } // DEBUG : move right
	*/
}

void OnScriptCall( ScriptObject *obj )
{
	if ( obj == nullptr ){ return; }
	flog( obj->getID() );
}
