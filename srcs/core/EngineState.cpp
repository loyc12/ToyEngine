#include <raylib.h>
#include "../../incs/core.hpp"
#include "../../incs/game.hpp"

// ================================ STATE METHODS

// Goes trought the steps needed to go from one state to another
bool Engine::switchState(  engineState_e targetState )
{
	log( "Engine::switchState( )" );

	if ( getState() == targetState )
	{
		log( "Engine::switchState( ) : State matches current state : " + to_string( targetState ), WARN );
		return false;
	}

	engineState_e previousState = getState();

	log( "Engine::switchState( ) : Changing state from " + to_string( getState() ) + " to " + to_string( targetState ), INFO );

	// goes through the steps to raise the state
	if ( targetState > getState() ){ switch ( getState() )
	{
		case ES_CLOSED:
			log( "Engine::switchState( ) : Raising to ES_INITIALIZED", INFO );
			setState( ES_INITIALIZING ); init();
			if ( getState() == targetState ) break;

			[[fallthrough]];

		case ES_INITIALIZED:
			log( "Engine::switchState( ) : Raising to ES_STARTED", INFO );
			setState( ES_STARTING ); start();
			if ( getState() == targetState ) break;

			[[fallthrough]];

		case ES_STARTED:
			log( "Engine::switchState( ) : Raising to ES_RUNNING", INFO );
			setState( ES_RESUMING ); resume();
			if ( getState() == targetState ) break;

			[[fallthrough]];

		default:
			log( "Engine::switchState( ) : Invalid state : Raising from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR );
			return false;
	}}

	// goes through the steps to lower the state
	if ( targetState < getState() ){ switch ( getState() )
	{
		case ES_RUNNING:
			log( "Engine::switchState( ) : Lowering to ES_STARTED", INFO );
			setState( ES_PAUSING ); pause();
			if ( getState() == targetState ) break;
			[[fallthrough]];

		case ES_STARTED:
			log( "Engine::switchState( ) : Lowering to ES_INITIALIZED", INFO );
			setState( ES_STOPPING ); stop();
			if ( getState() == targetState ) break;
			[[fallthrough]];

		case ES_INITIALIZED:
			log( "Engine::switchState( ) : Lowering to ES_CLOSED", INFO );
			setState( ES_CLOSING ); close();
			if ( getState() == targetState ) break;
			[[fallthrough]];

		default:
			log( "Engine::switchState( ) : Invalid state : Lowering from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR );
			return false;
	}}

	log( "Engine::switchState( ) : DONE ! : State changed from " + to_string( previousState ) + " to " + to_string( targetState ), INFO );
	return true;
}

bool Engine::togglePause()
{
	log( "Engine::togglePause()" );

	log( "Engine::togglePause() : Current state is " + to_string( getState() ), INFO );

	switch ( getState() )
	{
		case ES_RUNNING:
			log( "Engine::togglePause() : Pausing engine", INFO );
			pause();
			break;

		case ES_STARTED:
			log( "Engine::togglePause() : Resuming engine", INFO );
			resume();
			break;

		default:
			log( "Engine::togglePause() : Engine is neither resumed nor paused", ERROR );
			return false;
	}
	return true;
}

void Engine::init()
{
	log( "Engine::init()" );

	if ( getState() > ES_INITIALIZING ){ log( "Engine::init() : Engine already initialized",  ERROR ); return; }
	if ( getState() < ES_CLOSED){        log( "Engine::init() : how did you even get here ?", ERROR ); return; }

	_controller = new Controller();   GCN = _controller;
	_viewport2D = new Viewport2D();   GVP = _viewport2D;

	OnGameInit(); // from game.hpp

	setState( ES_INITIALIZED );
}

void Engine::start()
{
	log( "Engine::start()" );

	if ( getState() > ES_STARTING ){    log( "Engine::start() : Engine already started", ERROR ); return; }
	if ( getState() < ES_INITIALIZED ){ log( "Engine::start() : Engine not initialized", ERROR ); return; }

	_viewport2D->open();

	OnGameStart(); // from game.hpp
	setState( ES_STARTED );
}

void Engine::resume()
{
	log( "Engine::resume()" );

	if ( getState() > ES_RESUMING ){ log( "Engine::resume() : Engine already running", ERROR ); return; }
	if ( getState() < ES_STARTED ){  log( "Engine::resume() : Engine not yet started", ERROR ); return; }

	OnGameResume(); // from game.hpp
	setState( ES_RUNNING );


}

void Engine::pause()
{
	log( "Engine::pause()" );

	if ( getState() < ES_PAUSING ){ log( "Engine::pause() : Engine not currently running", ERROR ); return; }
	if ( getState() > ES_RUNNING ){ log( "Engine::pause() : how did you even get here ?",  ERROR ); return; }

	OnGamePause(); // from game.hpp
	setState( ES_STARTED );
}

void Engine::stop()
{
	log( "Engine::stop()" );

	if ( getState() < ES_STOPPING ){ log( "Engine::stop() : Engine not yet started",  ERROR ); return; }
	if ( getState() > ES_STARTED ){  log( "Engine::stop() : Engine is still running", ERROR ); return; }

	_viewport2D->close();

	OnGameStop(); // from game.hpp
	setState( ES_INITIALIZED );
}

void Engine::close()
{
	log( "Engine::close()" );

	if ( getState() < ES_CLOSING ){     log( "Engine::close() : Engine not initialized", ERROR ); return; }
	if ( getState() > ES_INITIALIZED ){ log( "Engine::close() : Engine still started",   ERROR ); return; }

	OnGameClose(); // from game.hpp

	delete _viewport2D;   GVP = nullptr;
	delete _controller;   GVP = nullptr;

	DelAllObjects();
	setState( ES_CLOSED );
}
