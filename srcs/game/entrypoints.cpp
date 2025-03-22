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

// Code to run at the start of the Step Seuquence, or of a SubStep

void OnGameStep()
{

}

void OnReadInputs()
{
	log( "OnReadInputs()", INFO );

	inputs_s np = ng->getLastestInputs();

	float factor = 1.0f;
	if ( np.SHIFT ){ factor *= 0.5; }
	if ( np.CTRL  ){ factor *= 4.0; }

	int32_t moveHor = ( np.RIGHT - np.LEFT ) * MOVE_SPEED;
	if ( moveHor ){ PlayerObject->changePosition( { moveHor * factor * np.DT, 0.0f } ); }

	int32_t moveVer = ( np.BACK - np.FORE ) * MOVE_SPEED;
	if ( moveVer ){ PlayerObject->changePosition( { 0.0f, moveVer * factor * np.DT } ); }

	if ( np.SCROLL_DOWN ){ vp->scaleZoom( pow( 2.0f, factor * np.DT * ZOOM_SPEED )); }
	if ( np.SCROLL_UP   ){ vp->scaleZoom( pow( 0.5f, factor * np.DT * ZOOM_SPEED )); }

	if ( np.X ){ vp->untrackObject(); }
	if ( np.C ){ vp->trackObject( PlayerObject ); }

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

	string playerPos = "[" + to_string( ( int )PlayerObject->getPosition().x ) + ":" + to_string( ( int )PlayerObject->getPosition().y ) + "]";

	DrawText( playerPos.c_str(), PlayerObject->getPosition().x, PlayerObject->getPosition().y, DEBUG_FONT_SIZE, RED );

}

void OnRenderUI()
{
	string caInfo = "Camera : " + to_string( ( int )vp->getTarget().x ) + ":" + to_string( ( int )vp->getTarget().y ) + " | " + to_string( vp->getZoom() ) + " | " + to_string( ( int )vp->getRotation() );
	log( caInfo, INFO );

	int FontSizeUI = DEBUG_FONT_SIZE;

	DrawText( caInfo.c_str(), FontSizeUI, ( 2.5f * FontSizeUI ), FontSizeUI, WHITE );

	// DEBUG : drawing to each corner of the screen for debug purposes
	DrawText( "TL", FontSizeUI,                               FontSizeUI,                             FontSizeUI, WHITE );
	DrawText( "TR", GetScreenWidth() - ( 2.5f * FontSizeUI ), FontSizeUI,                             FontSizeUI, WHITE );
	DrawText( "BL", FontSizeUI,                               GetScreenHeight() - ( 2 * FontSizeUI ), FontSizeUI, WHITE );
	DrawText( "BR", GetScreenWidth() - ( 2.5f * FontSizeUI ), GetScreenHeight() - ( 2 * FontSizeUI ), FontSizeUI, WHITE );
}