# include "../../incs/game.hpp"

Object2D *PlayerObject;

Engine *ng = Engine::getEngine();
Viewport2D *vp = ng->getViewport();

void OnGameStart()
{
	log( "OnGameStart()", INFO );

	PlayerObject = new Object2D;
	//PlayerObject->setPosition( PtoV2( vp->getCenter() ));
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

	inputs_s inputs = ng->getLastestInputs();

	float factor = 1.0f;
	if ( inputs.SHIFT ){ factor *= 0.5; }
	if ( inputs.CTRL  ){ factor *= 4.0; }

	int moveHor = inputs.RIGHT - inputs.LEFT;
	if ( moveHor ){ PlayerObject->changePosition( { moveHor * factor, 0.0f } ); }

	int moveVer = inputs.BACK - inputs.FORE;
	if ( moveVer ){ PlayerObject->changePosition( { 0.0f, moveVer * factor } ); }

	if ( inputs.SCROLL_DOWN ){ vp->scaleZoom( 1 - ( 0.1f * factor )); }
	if ( inputs.SCROLL_UP   ){ vp->scaleZoom( 1 + ( 0.1f * factor )); }

	if ( inputs.X ){ vp->untrackObject(); }
	if ( inputs.C ){ vp->trackObject( PlayerObject ); }

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
	log( "Player position : " + playerPos, INFO );

	DrawText( playerPos.c_str(), PlayerObject->getPosition().x, PlayerObject->getPosition().y, DEBUG_FONT_SIZE, WHITE );

	string caInfo = "Camera : " + to_string( ( int )vp->getTarget().x ) + ":" + to_string( ( int )vp->getTarget().y ) + " | " + to_string( vp->getZoom() ) + " | " + to_string( ( int )vp->getRotation() );
	log( caInfo, INFO );

	DrawText( caInfo.c_str(), vp->getTopLeft().x + DEBUG_FONT_SIZE, vp->getTopLeft().y + DEBUG_FONT_SIZE, DEBUG_FONT_SIZE, WHITE );

	// DEBUG : drawing to each corner of the screen for debug purposes
	//DrawText( "TL", vp->getTopLeft().x  +       DEBUG_FONT_SIZE,   vp->getTopLeft().y  +       DEBUG_FONT_SIZE,   DEBUG_FONT_SIZE, WHITE );
	DrawText( "TR", vp->getTopRight().x - ( 2 * DEBUG_FONT_SIZE ), vp->getTopRight().y +       DEBUG_FONT_SIZE,   DEBUG_FONT_SIZE, WHITE );
	DrawText( "BL", vp->getBotLeft().x  +       DEBUG_FONT_SIZE,   vp->getBotLeft().y  - ( 2 * DEBUG_FONT_SIZE ), DEBUG_FONT_SIZE, WHITE );
	DrawText( "BR", vp->getBotRight().x - ( 2 * DEBUG_FONT_SIZE ), vp->getBotRight().y - ( 2 * DEBUG_FONT_SIZE ), DEBUG_FONT_SIZE, WHITE );

}

