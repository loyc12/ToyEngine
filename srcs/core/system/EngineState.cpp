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
		qlog( "switchState : State matches current state : " + to_string( targetState ), WARN, 0 );
		return false;
	}

	engineState_e previousState = getState();
	qlog( "switchState : Changing state from " + to_string( getState() ) + " to " + to_string( targetState ), INFO, 0 );

	// goes through the steps to raise the state
	if ( targetState > getState() ){ switch ( getState() )
	{
		case ES_CLOSED:
			qlog( "switchState : Raising to ES_INITIALIZED", DEBUG, 0 );
			setState( ES_INITIALIZING ); init();
			if ( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_INITIALIZED:
			qlog( "switchState : Raising to ES_STARTED", DEBUG, 0 );
			setState( ES_STARTING ); start();
			if ( getState() == targetState ) break;

			[[ fallthrough ]];

		case ES_STARTED:
			qlog( "switchState : Raising to ES_RUNNING", DEBUG, 0 );
			setState( ES_RESUMING ); resume();
			if ( getState() == targetState ) break;

			[[ fallthrough ]];

		default:
			qlog( "switchState : Invalid state : Raising from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR, 0 );
			return false;
	}}

	// goes through the steps to lower the state
	if ( targetState < getState() ){ switch ( getState() )
	{
		case ES_RUNNING:
			qlog( "switchState : Lowering to ES_STARTED", DEBUG, 0 );
			setState( ES_PAUSING ); pause();
			if ( getState() == targetState ) break;
			[[ fallthrough ]];

		case ES_STARTED:
			qlog( "switchState : Lowering to ES_INITIALIZED", DEBUG, 0 );
			setState( ES_STOPPING ); stop();
			if ( getState() == targetState ) break;
			[[ fallthrough ]];

		case ES_INITIALIZED:
			qlog( "switchState : Lowering to ES_CLOSED", DEBUG, 0 );
			setState( ES_CLOSING ); close();
			if ( getState() == targetState ) break;
			[[ fallthrough ]];

		default:
			qlog( "switchState : Invalid state : Lowering from " + to_string( previousState ) + " to " + to_string( targetState ), ERROR, 0 );
			return false;
	}}

	qlog( "switchState : State changed from " + to_string( previousState ) + " to " + to_string( targetState ), INFO, 0 );
	return true;
}

bool Engine::togglePause()
{
	flog( 0 );
	qlog( "togglePause : Current state is " + to_string( getState() ), DEBUG, 0 );

	switch ( getState() )
	{
		case ES_RUNNING:
			qlog( "togglePause : Pausing engine", INFO, 0 );
			pause();
			break;

		case ES_STARTED:
			qlog( "togglePause : Resuming engine", INFO, 0 );
			resume();
			break;

		default:
			qlog( "togglePause : Engine is neither resumed nor paused", ERROR, 0 );
			return false;
	}
	return true;
}

void Engine::init()
{
	flog( 0 );
	if ( getState() > ES_INITIALIZING ){ qlog( "init : Engine already initialized",  ERROR, 0 ); return; }
	if ( getState() < ES_CLOSED){        qlog( "init : how did you even get here ?", ERROR, 0 ); return; }

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
	if ( getState() > ES_STARTING ){    qlog( "start : Engine already started", ERROR, 0 ); return; }
	if ( getState() < ES_INITIALIZED ){ qlog( "start : Engine not initialized", ERROR, 0 ); return; }

	_viewport2D->open();

	OnGameStart(); // from game.hpp
	setState( ES_STARTED );
}

void Engine::resume()
{
	flog( 0 );
	if ( getState() > ES_RESUMING ){ qlog( "resume : Engine already running", ERROR, 0 ); return; }
	if ( getState() < ES_STARTED ){  qlog( "resume : Engine not yet started", ERROR, 0 ); return; }

	OnGameResume(); // from game.hpp
	setState( ES_RUNNING );


}

void Engine::pause()
{
	flog( 0 );
	if ( getState() < ES_PAUSING ){ qlog( "pause : Engine not currently running", ERROR, 0 ); return; }
	if ( getState() > ES_RUNNING ){ qlog( "pause : how did you even get here ?",  ERROR, 0 ); return; }

	OnGamePause(); // from game.hpp
	setState( ES_STARTED );
}

void Engine::stop()
{
	flog( 0 );
	if ( getState() < ES_STOPPING ){ qlog( "stop : Engine not yet started",  ERROR, 0 ); return; }
	if ( getState() > ES_STARTED ){  qlog( "stop : Engine is still running", ERROR, 0 ); return; }

	_viewport2D->close();

	OnGameStop(); // from game.hpp
	setState( ES_INITIALIZED );
}

void Engine::close()
{
	flog( 0 );
	if ( getState() < ES_CLOSING ){     qlog( "close : Engine not initialized", ERROR, 0 ); return; }
	if ( getState() > ES_INITIALIZED ){ qlog( "close : Engine still started",   ERROR, 0 ); return; }

	OnGameClose(); // from game.hpp
	setState( ES_CLOSED );

	delete _compManager;  _compManager = nullptr;  GCM = nullptr;
	delete _viewport2D;   _viewport2D = nullptr;   GVP = nullptr;
	delete _controller;   _controller = nullptr;   GCN = nullptr;

	DelAllObjects(); // TODO : REMOVE ME
}
