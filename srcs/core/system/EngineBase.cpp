#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _maxID( 0 ), _DT( 0 ), _TS( 1 ), _state( ES_CLOSED )
{
	flog( 0 );
	if ( getState() < ES_CLOSING )
		switchState(  ES_INITIALIZED );
}

Engine::~Engine()
{
	flog( 0 );
	if ( getState() > ES_CLOSED )
		switchState(  ES_CLOSED );
}

Engine *Engine::getEngine()
{
	flog( 0 );
	static Engine *instance = new Engine();

	return instance;
}

// ================================ ACCESSORS / MUTATORS

inputs_s   &Engine::getLatestInputs(){   return _controller->getLatestInputs(); }
inputs_s   &Engine::getPreviousInputs(){ return _controller->getPreviousInputs(); }
Controller *Engine::getController(){     return _controller; }

Camera2D   &Engine::getCamera(){         return _viewport2D->getCamera(); }
Viewport2D *Engine::getViewport(){       return _viewport2D; }

CompManager *Engine::getCompManager(){   return _compManager; }

BaseObject *Engine::getObjectByID( objID_t id )
{
	flog( 0 );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( (*it)->getID() == id )
		{
			qlog( "getObjectByID : Found requested object", DEBUG, id );
			return *it;
		}
	}

	qlog( "getObjectByID : Failed to find requested object", WARN, id );
	return nullptr;
}

objID_t Engine::getNewID()
{
	flog( 0 );
	return ++_maxID;
}

uint32_t Engine::getObjectCount() const // NOTE : add a resetIDs() method ?
{
	flog( 0 );
	return ObjectContainer.size();
}

float Engine::getDeltaTime() const { return _DT * _TS; }
void  Engine::setTimeScale( float timeScale )
{
	flog( 0 );
	if ( timeScale < 0 )
	{
		qlog( "setTimeScale : Time scale cannot be negative", WARN, 0 );
		_TS = 0;
		return;
	}
	_TS = timeScale;
}

// ================ MUTEXES

engineState_e Engine::getState()
{
	flog( 0 );
	std::lock_guard< std::mutex > lock( mtx_state );
	return _state;
}

void Engine::setState( engineState_e newState )
{
	flog( 0 );
	std::lock_guard< std::mutex > lock( mtx_state );
	_state = newState;
}

// ==================== ENGINE SHORTCUTS
// Shortcuts to the engine and its components

Engine      *GNG = Engine::getEngine();
Controller  *GCN = GNG->getController();
Viewport2D  *GVP = GNG->getViewport();
CompManager *GCM = GNG->getCompManager();

float    GDTS(){ return GNG->getDeltaTime(); }
inputs_s &GIN(){ return GNG->getLatestInputs(); }