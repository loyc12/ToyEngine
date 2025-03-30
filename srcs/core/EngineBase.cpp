#include <raylib.h>
#include "../../incs/core.hpp"
#include "../../incs/game.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _state( ES_CLOSED ), maxID( 0 )
{
	log( "Engine::Engine()" );

	if ( getState() < ES_CLOSING )
		switchState(  ES_INITIALIZED );
}

Engine::~Engine()
{
	log( "Engine::~Engine()" );

	if ( getState() > ES_CLOSING )
		switchState(  ES_CLOSED );
}

Engine *Engine::getEngine()
{
	log( "Engine::getEngine()" );

	static Engine *instance = new Engine();

	return instance;
}



// ================================ ACCESSORS

float Engine::getDeltaTime() const { return _DT; }

inputs_s   &Engine::getLatestInputs(){  return _controller->getLatestInputs(); }
inputs_s   &Engine::getPreviousInputs(){ return _controller->getPreviousInputs(); }
Controller *Engine::getController()
{
	log( "Engine::getController()" );
	return _controller;
}

Camera2D   &Engine::getCamera() { return _viewport2D->getCamera(); }
Viewport2D *Engine::getViewport()
{
	log( "Engine::getViewport()" );
	return _viewport2D;
}

BaseObject *Engine::getObjectByID( objID_t id )
{
	log( "Engine::getObjectByID()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( (*it)->getID() == id )
		{
			log( "Engine::getObjectByID() : Found requested object" );
			return *it;
		}
	}

	log( "Engine::getObjectByID() : Failed to find requested object", WARN );
	return nullptr;
}

objID_t Engine::getNewID()
{
	log( "Engine::getNewID()" );
	return ++maxID;
}

uint32_t Engine::getObjectCount() const
{
	log( "Engine::getObjectCount()" );
	return ObjectContainer.size();
}

// ================================ MUTEXED ACCESSORS

engineState_e Engine::getState()
{
	log( "Engine::getState()" );
	std::lock_guard< std::mutex > lock( mtx_state );
	return _state;
}

void Engine::setState( engineState_e newState )
{
	log( "Engine::setState()" );
	std::lock_guard< std::mutex > lock( mtx_state );
	_state = newState;
}


// ================================ OTHER METHODS


// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its components

Engine     *GNG = Engine::getEngine();
Controller *GCN = GNG->getController();
Viewport2D *GVP = GNG->getViewport();