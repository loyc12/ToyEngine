# include "../../incs/game.hpp"

Object2D *PlayerObject;

void OnGameStart()
{
	log( "OnGameStart()", INFO );

	PlayerObject = new Object2D;
}

void OnGameStep()
{

}

void OnGameClose()
{
	log( "OnGameClose()", INFO );
}

void OnReadInputs()
{
	log( "OnReadInputs()", INFO );

	inputs_s inputs = Engine::getEngine()->getLastestInputs();

	float moveHor = inputs.RIGHT - inputs.LEFT;
	if ( moveHor ){ PlayerObject->changePosition( { moveHor, 0 } ); }

	float moveVer = inputs.FORE - inputs.BACK;
	if ( moveVer ){ PlayerObject->changePosition( { 0, moveVer } ); }
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

	string playerPos = "[" + to_string( PlayerObject->getPosition().x ) + ":" + to_string( PlayerObject->getPosition().y ) + "]";
	log( "Player position : " + playerPos, INFO );

	DrawText( playerPos.c_str(), PlayerObject->getPosition().x, PlayerObject->getPosition().y, DEBUG_FONT_SIZE, WHITE );

}

