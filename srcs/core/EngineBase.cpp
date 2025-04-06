#include <raylib.h>
#include "../../incs/core.hpp"
#include "../../incs/game.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _maxID( 0 ), _DT( 0 ), _TS( 1 ), _state( ES_CLOSED )
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

// ================================ ACCESSORS / MUTATORS

inputs_s   &Engine::getLatestInputs(){   return _controller->getLatestInputs(); }
inputs_s   &Engine::getPreviousInputs(){ return _controller->getPreviousInputs(); }
Controller *Engine::getController()
{
	log( "Engine::getController()" );
	return _controller;
}

Camera2D   &Engine::getCamera(){ return _viewport2D->getCamera(); }
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
	return ++_maxID;
}

uint32_t Engine::getObjectCount() const // NOTE : add a resetIDs() method ?
{
	log( "Engine::getObjectCount()" );
	return ObjectContainer.size();
}

float Engine::getDeltaTime() const { return _DT * _TS; }
void  Engine::setTimeScale( float timeScale )
{
	log( "Engine::setTimeScale()" );
	if ( timeScale < 0 )
	{
		log( "Engine::setTimeScale() : Time scale cannot be negative", WARN );
		_TS = 0;
		return;
	}
	_TS = timeScale;
}

// ================ MUTEXES

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

// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its components

Engine     *GNG = Engine::getEngine();
Controller *GCN = GNG->getController();
Viewport2D *GVP = GNG->getViewport();

float    GDTS(){ return GNG->getDeltaTime(); }
inputs_s &GIN(){ return GNG->getLatestInputs(); }