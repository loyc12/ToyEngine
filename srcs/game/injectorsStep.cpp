# include <raylib.h>
# include "../../incs/game.hpp"

// ==================== ENGINE STEP INJECTION FUNCTIONS
// called when the engine calls the game step method - aka in the game loop of launchLoop()

void OnGameLaunch()
{
	flog( 0 );
}

void OnGameStep()
{
	flog( 0 );
	//CloseWindow(); // DEBUG : to run the game loop only once
}

void OnReadInputs() // only called when the game is launched
{
	flog( 0 );

	inputs_s np = GIN(); // TODO make this shit global

	float moveFactor = GDTS();
	if ( np.SHIFT ){ moveFactor *= 0.5; } // TODO make this shit global
	if ( np.CTRL  ){ moveFactor *= 4.0; }


	if ( GCN->getLatestInputs().P )
	{
		qlog( "Toggling pause", INFO, 0 );
		GNG->togglePause();
	}

	if ( np.SCROLL_UP   ){ GVP->scaleZoom( pow( 2.0f, moveFactor * ZOOM_SPEED )); }
	if ( np.SCROLL_DOWN ){ GVP->scaleZoom( pow( 0.5f, moveFactor * ZOOM_SPEED )); }

}

void OnRunScripts() // only called when the game is launched
{
	flog( 0 );
}

void OnRunPhysics() // only called when the game is launched and unpaused
{

	flog( 0 );
	inputs_s np = GIN(); // TODO make this shit global

	float moveFactor = GDTS() ;
	if ( np.SHIFT ){ moveFactor *= 0.5; } // TODO make this shit global
	if ( np.CTRL  ){ moveFactor *= 4.0; }


	int32_t moveHor = ( np.RIGHT - np.LEFT ) * MOVE_SPEED;
	if ( moveHor ){ G_Player->movePosition( { moveHor * moveFactor, 0.0f } ); }

	int32_t moveVer = ( np.BACK - np.FORE ) * MOVE_SPEED;
	if ( moveVer ){ G_Player->movePosition( { 0.0f, moveVer * moveFactor } ); }

	if ( np.X ){ GVP->untrackObject(); }
	if ( np.C ){ GVP->trackObject( G_Player ); }

	if ( np.CLICK_LEFT && !GVP->isTracking() )
	{
		Vector2 mouseWorldPos = GVP->getMouseWorldPos();

		G_Player->setPosition( { mouseWorldPos.x, mouseWorldPos.y } );
		G_Player->setVelocity( { 0.0f, 0.0f } );
		//G_Player->setRotation( 0.0f );
	}

}

void OnRenderWorld() // only called when the game is launched
{
	flog( 0 );
}

void OnRenderUI() // only called when the game is launched
{

	flog( 0 );
	string moInfo = "Mouse  : " + to_string( ( int )GVP->getMouseWorldPos().x ) + ":" + to_string( ( int )GVP->getMouseWorldPos().y ) + " | " + to_string( ( int )GVP->getMousePos().x ) + ":" + to_string( ( int )GVP->getMousePos().y );
	qlog( moInfo, INFO, 0 );

	string caInfo = "Camera : " + to_string( GVP->getZoom() ) + " | " + to_string( ( int )GVP->getRotation() ) + " | " + to_string( ( int )GVP->getTarget().x ) + ":" + to_string( ( int )GVP->getTarget().y );
	qlog( caInfo, INFO, 0 );

	Vector2 playerWorldPos = G_Player->getPosition();
	Vector2 playerScreenPos = GetWorldToScreen2D( playerWorldPos, GVP->getCamera() );
	string plInfo = "G_Player  : " + to_string( ( int )playerScreenPos.x ) + ":" + to_string( ( int )playerScreenPos.y ) + " | " + to_string( ( int )playerWorldPos.x ) + ":" + to_string( ( int )playerWorldPos.y );
	qlog( plInfo, INFO, 0 );

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