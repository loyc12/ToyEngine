#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ STEP METHODS


bool Engine::launchLoop()
{
	log( "Engine::launch()" );

	if ( getState() < ES_STARTED )
	{
		log( "Engine::launch() : Engine not yet started", ERROR );
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
	log( "Engine::runStep()" );
	if ( getState() < ES_STARTED ){ log( "Engine::runeStep() : Engine not started", ERROR ); return; }

	_DT = GetFrameTime();

	readInputs();
	runScripts();
	if ( getState() >= ES_RUNNING ){ runPhysics(); } // Only runs the physics call if the enguine is unpaused
	runRenders();

	OnGameStep(); // from game.hpp
}

void Engine::readInputs()
{
	log( "Engine::readInputs()" );

	_controller->refreshInputs();

	OnReadInputs(); // from game.hpp
}

void Engine::runPhysics()
{
	log( "Engine::runPhysics()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ){ (*it)->onPhysicTick(); }

	OnRunPhysics(); // from game.hpp
}

void Engine::runScripts()
{
	log( "Engine::runScripts()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ){ (*it)->onScriptTick(); }

	OnRunScripts(); // from game.hpp
}

void Engine::runRenders()
{
	log( "Engine::runRenders()" );

	BeginDrawing();
	_viewport2D->refresh();

	renderWorld();
	renderUIs();

	EndDrawing();
}

void Engine::renderWorld()
{
	log( "Engine::renderObjects()" );

	BeginMode2D( _viewport2D->getCamera() );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ){ (*it)->onRenderTick(); }

	OnRenderWorld(); // from game.hpp

	EndMode2D();
}

void Engine::renderUIs()
{
	log( "Engine::renderUIs()" );

	OnRenderUI(); // from game.hpp
}