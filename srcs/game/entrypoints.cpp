# include "../../incs/game.hpp"
#include <raylib.h>

Object2D *PlayerObject;

Engine *ng = Engine::getEngine();
Viewport2D *vp = ng->getViewport();

void OnGameStart()
{
	log( "OnGameStart()", INFO );

	PlayerObject = new Object2D;
}

void OnGameClose()
{
	log( "OnGameClose()", INFO );
}

// Code to run at the start of the Step Sequence, or of a SubStep

void OnGameStep()
{

}

// code to be run at the end of each substep

void OnReadInputs()
{
	log( "OnReadInputs()", INFO );

	inputs_s np = ng->getLatestInputs();
	float DT = ng->getDeltaTime();

	float factor = 1.0f;
	if ( np.SHIFT ){ factor *= 0.5; }
	if ( np.CTRL  ){ factor *= 4.0; }

	int32_t moveHor = ( np.RIGHT - np.LEFT ) * MOVE_SPEED;
	if ( moveHor ){ PlayerObject->changePosition( { moveHor * factor * DT, 0.0f } ); }

	int32_t moveVer = ( np.BACK - np.FORE ) * MOVE_SPEED;
	if ( moveVer ){ PlayerObject->changePosition( { 0.0f, moveVer * factor * DT } ); }

	if ( np.SCROLL_DOWN ){ vp->scaleZoom( pow( 2.0f, factor * DT * ZOOM_SPEED )); }
	if ( np.SCROLL_UP   ){ vp->scaleZoom( pow( 0.5f, factor * DT * ZOOM_SPEED )); }

	if ( np.X ){ vp->untrackObject(); }
	if ( np.C ){ vp->trackObject( PlayerObject ); }

	if ( np.CLICK_LEFT ) // log the mouse worl and screen position
	{
		Vector2 mouseWorldPos = vp->getMouseWorldPos();

		PlayerObject->setPosition( { mouseWorldPos.x, mouseWorldPos.y } );
		PlayerObject->setVelocity( { 0.0f, 0.0f } );
		//PlayerObject->setRotation( 0.0f );
	}

}

void OnRunPhysics()
{
	log( "OnRunPhysics()", INFO );
}

void OnRunScripts()
{
	log( "OnRunScripts()", INFO );
}

void OnRenderObjects()
{
	log( "OnRenderObjects()", INFO );

}

void OnRenderUI() // DEBUG FOR NOW
{
	string moInfo = "Mouse  : " + to_string( ( int )vp->getMouseWorldPos().x ) + ":" + to_string( ( int )vp->getMouseWorldPos().y ) + " | " + to_string( ( int )vp->getMousePos().x ) + ":" + to_string( ( int )vp->getMousePos().y );
	log( moInfo, INFO );

	string caInfo = "Camera : " + to_string( vp->getZoom() ) + " | " + to_string( ( int )vp->getRotation() ) + " | " + to_string( ( int )vp->getTarget().x ) + ":" + to_string( ( int )vp->getTarget().y );
	log( caInfo, INFO );

	Vector2 playerWorldPos = PlayerObject->getPosition();
	Vector2 playerScreenPos = GetWorldToScreen2D( playerWorldPos, vp->getCamera() );
	string plInfo = "Player  : " + to_string( ( int )playerScreenPos.x ) + ":" + to_string( ( int )playerScreenPos.y ) + " | " + to_string( ( int )playerWorldPos.x ) + ":" + to_string( ( int )playerWorldPos.y );
	log( plInfo, INFO );

	int FontSizeUI = DEBUG_FONT_SIZE;

	DrawText( moInfo.c_str(), FontSizeUI, ( 2.5f * FontSizeUI ), FontSizeUI, WHITE );
	DrawText( caInfo.c_str(), FontSizeUI, ( 4.0f * FontSizeUI ), FontSizeUI, WHITE );
	DrawText( plInfo.c_str(), FontSizeUI, ( 5.5f * FontSizeUI ), FontSizeUI, WHITE );

	// DEBUG : drawing to each corner of the screen for debug purposes
	DrawText( "TL", FontSizeUI,                               FontSizeUI,                               FontSizeUI, WHITE );
	DrawText( "TR", GetScreenWidth() - ( 2.5f * FontSizeUI ), FontSizeUI,                               FontSizeUI, WHITE );
	DrawText( "BL", FontSizeUI,                               GetScreenHeight() - ( 2.0 * FontSizeUI ), FontSizeUI, WHITE );
	DrawText( "BR", GetScreenWidth() - ( 2.5f * FontSizeUI ), GetScreenHeight() - ( 2.0 * FontSizeUI ), FontSizeUI, WHITE );
}

// code to be run on each object on their update methods calls

void OnEach( PhysicObject *obj )
{
	if ( obj == nullptr ) { return; }
	log( "OnEach:PhysicObject()", INFO, obj->getID() );

	//obj->changeAcceleration( { 0.0f, 0.1f } );
}

void OnEach( ScriptObject *obj )
{
	if ( obj == nullptr ) { return; }
	log( "OnEach:ScriptObject()", INFO, obj->getID() );

	log( "Hello, World!", WARN );

}

void OnEach( RenderObject *obj )
{
	if ( obj == nullptr ) { return; }
	log( "OnEach:RenderObject()", INFO, obj->getID() );

	DrawCircle( ( int )obj->getPosition().x, ( int )obj->getPosition().y, 16, BLUE );
}
