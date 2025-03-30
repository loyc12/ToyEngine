#include <raylib.h>
#include "../../incs/core.hpp"

// ================================ CORE METHODS

void Controller::init()
{
	log( "Controller::init()" );

	bzero( &_previousInputs, sizeof( inputs_s ) );
	bzero( &_latestInputs,   sizeof( inputs_s ) );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Controller::Controller()
{
	log( "Controller::Controller()" );
	init();
}
Controller::~Controller()
{
	log( "Controller::~Controller()" );
}

// ================================ ACCESSORS

inputs_s &Controller::getLatestInputs()   { return _latestInputs; }
inputs_s &Controller::getPreviousInputs() { return _previousInputs; }

// ================================ METHODS

void Controller::refreshInputs() // NOTE : archaic way of doing things, but it works for now
{
	log( "Controller::refresh()" );

	// SAVE PREVIOUS INPUTS
	_previousInputs = _latestInputs;

	// BASE
	_latestInputs.LEFT  = IsKeyDown( KEY_A )            || IsKeyDown( KEY_LEFT );
	_latestInputs.RIGHT = IsKeyDown( KEY_D )            || IsKeyDown( KEY_RIGHT );
	_latestInputs.FORE  = IsKeyDown( KEY_W )            || IsKeyDown( KEY_UP );
	_latestInputs.BACK  = IsKeyDown( KEY_S )            || IsKeyDown( KEY_DOWN );
	_latestInputs.SPACE = IsKeyDown( KEY_SPACE )        || IsKeyDown( KEY_KP_0 );
	_latestInputs.ENTER = IsKeyDown( KEY_ENTER )        || IsKeyDown( KEY_KP_ENTER );
	_latestInputs.SHIFT = IsKeyDown( KEY_LEFT_SHIFT )   || IsKeyDown( KEY_RIGHT_SHIFT );
	_latestInputs.CTRL  = IsKeyDown( KEY_LEFT_CONTROL ) || IsKeyDown( KEY_RIGHT_CONTROL );
	_latestInputs.ALT   = IsKeyDown( KEY_LEFT_ALT )     || IsKeyDown( KEY_RIGHT_ALT );
	_latestInputs.TAB   = IsKeyDown( KEY_TAB )          || IsKeyDown( KEY_BACKSLASH );

	// MOUSE
	_latestInputs.CLICK_LEFT  = IsMouseButtonDown( MOUSE_LEFT_BUTTON );
	_latestInputs.CLICK_MID   = IsMouseButtonDown( MOUSE_MIDDLE_BUTTON );
	_latestInputs.CLICK_RIGHT = IsMouseButtonDown( MOUSE_RIGHT_BUTTON );
	_latestInputs.SCROLL_UP   = ( GetMouseWheelMove() > 0 );
	_latestInputs.SCROLL_DOWN = ( GetMouseWheelMove() < 0 );

	// TODO : move raw screen mouse pos here

	// LETTERS
	_latestInputs.A = IsKeyDown( KEY_A );      _latestInputs.B = IsKeyDown( KEY_B );
	_latestInputs.C = IsKeyDown( KEY_C );      _latestInputs.D = IsKeyDown( KEY_D );
	_latestInputs.E = IsKeyDown( KEY_E );      _latestInputs.F = IsKeyDown( KEY_F );
	_latestInputs.G = IsKeyDown( KEY_G );      _latestInputs.H = IsKeyDown( KEY_H );
	_latestInputs.I = IsKeyDown( KEY_I );      _latestInputs.J = IsKeyDown( KEY_J );
	_latestInputs.K = IsKeyDown( KEY_K );      _latestInputs.L = IsKeyDown( KEY_L );
	_latestInputs.M = IsKeyDown( KEY_M );      _latestInputs.N = IsKeyDown( KEY_N );
	_latestInputs.O = IsKeyDown( KEY_O );      _latestInputs.P = IsKeyDown( KEY_P );
	_latestInputs.Q = IsKeyDown( KEY_Q );      _latestInputs.R = IsKeyDown( KEY_R );
	_latestInputs.S = IsKeyDown( KEY_S );      _latestInputs.T = IsKeyDown( KEY_T );
	_latestInputs.U = IsKeyDown( KEY_U );      _latestInputs.V = IsKeyDown( KEY_V );
	_latestInputs.W = IsKeyDown( KEY_W );      _latestInputs.X = IsKeyDown( KEY_X );
	_latestInputs.Y = IsKeyDown( KEY_Y );      _latestInputs.Z = IsKeyDown( KEY_Z );

	// DIGITS
	_latestInputs.D0 = IsKeyDown( KEY_ZERO);   _latestInputs.K0 = IsKeyDown( KEY_KP_0 );
	_latestInputs.D1 = IsKeyDown( KEY_ONE);    _latestInputs.K1 = IsKeyDown( KEY_KP_1 );
	_latestInputs.D2 = IsKeyDown( KEY_TWO);    _latestInputs.K2 = IsKeyDown( KEY_KP_2 );
	_latestInputs.D3 = IsKeyDown( KEY_THREE);  _latestInputs.K3 = IsKeyDown( KEY_KP_3 );
	_latestInputs.D4 = IsKeyDown( KEY_FOUR);   _latestInputs.K4 = IsKeyDown( KEY_KP_4 );
	_latestInputs.D5 = IsKeyDown( KEY_FIVE);   _latestInputs.K5 = IsKeyDown( KEY_KP_5 );
	_latestInputs.D6 = IsKeyDown( KEY_SIX);    _latestInputs.K6 = IsKeyDown( KEY_KP_6 );
	_latestInputs.D7 = IsKeyDown( KEY_SEVEN);  _latestInputs.K7 = IsKeyDown( KEY_KP_7 );
	_latestInputs.D8 = IsKeyDown( KEY_EIGHT);  _latestInputs.K8 = IsKeyDown( KEY_KP_8 );
	_latestInputs.D9 = IsKeyDown( KEY_NINE);   _latestInputs.K9 = IsKeyDown( KEY_KP_9 );
}