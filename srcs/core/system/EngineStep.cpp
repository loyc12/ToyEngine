#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ STEP METHODS


bool Engine::launchLoop()
{
	flog( 0 );
	if ( getState() < ES_STARTED )
	{
		log( "Engine not yet started", ERROR );
		return false;
	}

	OnGameLaunch(); // from game.hpp
	while ( getState() >= ES_STARTED && !WindowShouldClose() )
	{
		runStep(); // TODO : Multithread this shit
	}

	return true;
}

void Engine::runStep()
{
	flog( 0 );
	if ( getState() < ES_STARTED ){ log( "Engine not started", ERROR ); return; }

	_DT = GetFrameTime();

	readInputs();
	runScripts();
	if ( getState() >= ES_RUNNING ){ runPhysics(); } // Only runs the physics call if the enguine is unpaused
	runRenders();

	OnGameStep(); // from game.hpp
}

void Engine::readInputs()
{
	flog( 0 );
	_controller->refreshInputs();

	OnReadInputs(); // from game.hpp
}

void Engine::runPhysics()
{
	flog( 0 );
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ){ (*it)->onPhysicTick(); }

	OnRunPhysics(); // from game.hpp
}

void Engine::runScripts()
{
	flog( 0 );
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ){ (*it)->onScriptTick(); }

	OnRunScripts(); // from game.hpp
}

void Engine::runRenders()
{
	flog( 0 );

	BeginDrawing();
	_viewport2D->refresh();

	renderWorld();
	renderUIs();

	EndDrawing();
}

void Engine::renderWorld()
{
	flog( 0 );

	BeginMode2D( _viewport2D->getCamera() );
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ){ (*it)->onRenderTick(); }
	OnRenderWorld(); // from game.hpp

	EndMode2D();
}

void Engine::renderUIs()
{
	flog( 0 );
	OnRenderUI(); // from game.hpp
}