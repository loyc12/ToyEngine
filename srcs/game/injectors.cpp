#include <raylib.h>
# include "../../incs/game.hpp"

// ==================== LOCAL VARIABLES

Engine     *ng = Engine::getEngine();
Viewport2D *vp = ng->getViewport();
Controller *cn = ng->getController();

Object2D *Floor;
Object2D *Wall1;
Object2D *Wall2;

Object2D *Player;
Object2D *Enemy;

Object2D *Ball;
Object2D *Box;

// ==================== ENGINE CORE INJECTION FUNCTIONS
// called when the engine changes state

void OnGameInit()
// NOTE : do not instanciate objects here ( or do anything that requires the engine to be started )
{
	log( "OnGameInit()", INFO );
}
void OnGameStart()
{
	log( "OnGameStart()", INFO );

	// NOTE : this is a temporary solution, the engine should be able to load the game from a file

	//Floor	 = new Object2D;
	//Wall1	 = new Object2D;
	//Wall2	 = new Object2D;

	Player = new Object2D;
	//Enemy  = new Object2D;

	//Ball   = new Object2D;
	//Box    = new Object2D;
}
void OnGameResume()
{
	log( "OnGameResume()", INFO );
}

void OnGamePause()
{
	log( "OnGamePause()", INFO );
}
void OnGameStop()
{
	log( "OnGameStop()", INFO );
}
void OnGameClose() // The engine takes care to delete all objects
{
	log( "OnGameClose()", INFO );
}

// ==================== ENGINE STEP INJECTION FUNCTIONS
// called when the engine calls the game step method - aka in the game loop of launchLoop()

void OnGameLaunch()
{
	log( "OnGameLaunch()", INFO );
}

void OnGameStep()
{
	//CloseWindow(); // DEBUG : to run the game loop only once
}

void OnReadInputs() // only called when the game is launched
{
	log( "OnReadInputs()", INFO );

	inputs_s np = ng->getLatestInputs(); // TODO make this shit global

	float moveFactor = ng->getDeltaTime() ;
	if ( np.SHIFT ){ moveFactor *= 0.5; } // TODO make this shit global
	if ( np.CTRL  ){ moveFactor *= 4.0; }


	if ( cn->getLatestInputs().P )
	{
		log( "Toggling pause", INFO );
		ng->togglePause();
	}

	if ( np.SCROLL_DOWN ){ vp->scaleZoom( pow( 2.0f, moveFactor * ZOOM_SPEED )); }
	if ( np.SCROLL_UP   ){ vp->scaleZoom( pow( 0.5f, moveFactor * ZOOM_SPEED )); }

}

void OnRunScripts() // only called when the game is launched
{
	log( "OnRunScripts()", INFO );
}

void OnRunPhysics() // only called when the game is launched and unpaused
{
	log( "OnRunPhysics()", INFO );;

	inputs_s np = ng->getLatestInputs(); // TODO make this shit global

	float moveFactor = ng->getDeltaTime() ;
	if ( np.SHIFT ){ moveFactor *= 0.5; } // TODO make this shit global
	if ( np.CTRL  ){ moveFactor *= 4.0; }


	int32_t moveHor = ( np.RIGHT - np.LEFT ) * MOVE_SPEED;
	if ( moveHor ){ Player->changePosition( { moveHor * moveFactor, 0.0f } ); }

	int32_t moveVer = ( np.BACK - np.FORE ) * MOVE_SPEED;
	if ( moveVer ){ Player->changePosition( { 0.0f, moveVer * moveFactor } ); }

	if ( np.X ){ vp->untrackObject(); }
	if ( np.C ){ vp->trackObject( Player ); }

	if ( np.CLICK_LEFT && !ng->getViewport()->isTracking() )
	{
		Vector2 mouseWorldPos = vp->getMouseWorldPos();

		Player->setPosition( { mouseWorldPos.x, mouseWorldPos.y } );
		Player->setVelocity( { 0.0f, 0.0f } );
		//Player->setRotation( 0.0f );
	}
}

void OnRenderWorld() // only called when the game is launched
{
	log( "OnRenderWorld()", INFO );
}

void OnRenderUI() // only called when the game is launched
{
	string moInfo = "Mouse  : " + to_string( ( int )vp->getMouseWorldPos().x ) + ":" + to_string( ( int )vp->getMouseWorldPos().y ) + " | " + to_string( ( int )vp->getMousePos().x ) + ":" + to_string( ( int )vp->getMousePos().y );
	log( moInfo, INFO );

	string caInfo = "Camera : " + to_string( vp->getZoom() ) + " | " + to_string( ( int )vp->getRotation() ) + " | " + to_string( ( int )vp->getTarget().x ) + ":" + to_string( ( int )vp->getTarget().y );
	log( caInfo, INFO );

	Vector2 playerWorldPos = Player->getPosition();
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

// ===================== OBJECT STEP INJECTION FUNCTIONS
// called when the engine calls the these update method of any object

void OnPhysicCall( PhysicObject *obj )
{
	if ( obj == nullptr ) { return; }
	log( "OnEach:PhysicObject()", INFO, obj->getID() );

	//obj->changeAcceleration( { 0.0f, 0.1f } ); // DEBUG : gravity
}

void OnScriptCall( ScriptObject *obj )
{
	if ( obj == nullptr ) { return; }
	log( "OnEach:ScriptObject()", INFO, obj->getID() );

}

void OnRenderCall( RenderObject *obj )
{
	if ( obj == nullptr ) { return; }
	log( "OnEach:RenderObject()", INFO, obj->getID() );

	DrawCircle( ( int )obj->getPosition().x, ( int )obj->getPosition().y, 16, BLUE );
}
