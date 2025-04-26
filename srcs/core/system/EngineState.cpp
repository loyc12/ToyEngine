#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ STATE METHODS

// Goes trought the steps needed to go from one state to another
bool Engine::switchState(  engineState_e targetState )
{
	flog( 0 );
	if ( getState() == targetState )
	{
		log( "State matches current state : " + to_string( targetState ), WARN );
		return false;
	}

	engineState_e previousState = getState();
	log( "Changing state from " + to_string( getState() ) + " to " + to_string( targetState ), INFO );

	// goes through the steps to raise the state
	if ( targetState > getState() ){ switch ( getState() )
	{
		case ES_CLOSED:
			log( "Raising to ES_INITIALIZED", INFO );
			setState( ES_INITIALIZING ); init();
			if ( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_INITIALIZED:
			log( "Raising to ES_STARTED", INFO );
			setState( ES_STARTING ); start();
			if ( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_STARTED:
			log( "Raising to ES_RUNNING", INFO );
			setState( ES_RESUMING ); resume();
			if ( getState() == targetState ) break;

			[[ fallthrough ]];

		default:
			log( "Invalid state : Raising from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR );
			return false;
	}}

	// goes through the steps to lower the state
	if ( targetState < getState() ){ switch ( getState() )
	{
		case ES_RUNNING:
			log( "Lowering to ES_STARTED", INFO );
			setState( ES_PAUSING ); pause();
			if ( getState() == targetState ) break;
			[[ fallthrough ]];

		case ES_STARTED:
			log( "Lowering to ES_INITIALIZED", INFO );
			setState( ES_STOPPING ); stop();
			if ( getState() == targetState ) break;
			[[ fallthrough ]];

		case ES_INITIALIZED:
			log( "Lowering to ES_CLOSED", INFO );
			setState( ES_CLOSING ); close();
			if ( getState() == targetState ) break;
			[[ fallthrough ]];

		default:
			log( "Invalid state : Lowering from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR );
			return false;
	}}

	log( "State changed from " + to_string( previousState ) + " to " + to_string( targetState ), INFO );
	return true;
}

bool Engine::togglePause()
{
	flog( 0 );
	log( "Current state is " + to_string( getState() ), INFO );

	switch ( getState() )
	{
		case ES_RUNNING:
			log( "Pausing engine", INFO );
			pause();
			break;

		case ES_STARTED:
			log( "Resuming engine", INFO );
			resume();
			break;

		default:
			log( "Engine is neither resumed nor paused", ERROR );
			return false;
	}
	return true;
}

void Engine::init()
{
	flog( 0 );
	if ( getState() > ES_INITIALIZING ){ log( "Engine already initialized",  ERROR ); return; }
	if ( getState() < ES_CLOSED){        log( "how did you even get here ?", ERROR ); return; }

	_controller  = new Controller();   GCN = _controller;
	_viewport2D  = new Viewport2D();   GVP = _viewport2D;
	_compManager = new CompManager();  GCM = _compManager;

	ObjectContainer.clear(); // TODO : REMOVE ME

	OnGameInit(); // from game.hpp

	setState( ES_INITIALIZED );
}

void Engine::start()
{
	flog( 0 );
	if ( getState() > ES_STARTING ){    log( "Engine already started", ERROR ); return; }
	if ( getState() < ES_INITIALIZED ){ log( "Engine not initialized", ERROR ); return; }

	_viewport2D->open();

	OnGameStart(); // from game.hpp
	setState( ES_STARTED );
}

void Engine::resume()
{
	flog( 0 );
	if ( getState() > ES_RESUMING ){ log( "Engine already running", ERROR ); return; }
	if ( getState() < ES_STARTED ){  log( "Engine not yet started", ERROR ); return; }

	OnGameResume(); // from game.hpp
	setState( ES_RUNNING );


}

void Engine::pause()
{
	flog( 0 );
	if ( getState() < ES_PAUSING ){ log( "Engine not currently running", ERROR ); return; }
	if ( getState() > ES_RUNNING ){ log( "how did you even get here ?",  ERROR ); return; }

	OnGamePause(); // from game.hpp
	setState( ES_STARTED );
}

void Engine::stop()
{
	flog( 0 );
	if ( getState() < ES_STOPPING ){ log( "Engine not yet started",  ERROR ); return; }
	if ( getState() > ES_STARTED ){  log( "Engine is still running", ERROR ); return; }

	_viewport2D->close();

	OnGameStop(); // from game.hpp
	setState( ES_INITIALIZED );
}

void Engine::close()
{
	flog( 0 );
	if ( getState() < ES_CLOSING ){     log( "Engine not initialized", ERROR ); return; }
	if ( getState() > ES_INITIALIZED ){ log( "Engine still started",   ERROR ); return; }

	OnGameClose(); // from game.hpp
	setState( ES_CLOSED );

	delete _compManager;  _compManager = nullptr;  GCM = nullptr;
	delete _viewport2D;   _viewport2D = nullptr;   GVP = nullptr;
	delete _controller;   _controller = nullptr;   GCN = nullptr;

	DelAllObjects(); // TODO : REMOVE ME
}
