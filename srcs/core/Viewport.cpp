#include "../../incs/core.hpp"

// ================================ CORE METHODS

void Viewport2D::init()
{
	log( "Viewport2D::init()" );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Viewport2D::Viewport2D() :
_windowSize( { SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT } ),
_mousePos(   { 0, 0 } ),
_targetFPS( WINDOW_DEFAULT_FPS ),
_zoomLevel( 1.0f )
{
	log( "Viewport2D::Viewport2D()" ); init();
}

Viewport2D::~Viewport2D()
{
	log( "Viewport2D::~Viewport2D()" ); close();
}

// ================================ ACCESSORS

posint_t Viewport2D::getWindowWidth() { return _windowSize.x; }
posint_t Viewport2D::getWindowHeight(){ return _windowSize.y; }
pos2_s Viewport2D::getWindowSize()    { return _windowSize; }

pos2_s Viewport2D::getWindowCenter()  { return _windowSize / 2; }
pos2_s Viewport2D::getWindowTopLeft() { return { 0, 0 }; }
pos2_s Viewport2D::getWindowTopRight(){ return { _windowSize.x, 0 }; }
pos2_s Viewport2D::getWindowBotLeft() { return { 0, _windowSize.y }; }
pos2_s Viewport2D::getWindowBotRight(){ return _windowSize; }

posint_t Viewport2D::getMousePosX()      { return _mousePos.x; }
posint_t Viewport2D::getMousePosY()      { return _mousePos.y; }
pos2_s Viewport2D::getMousePos()      { return _mousePos; }

// ================================ METHODS

void Viewport2D::open()
{
	log( "Viewport2D::open()" );
	InitWindow( _windowSize.x, _windowSize.y, WINDOW_DEFAULT_TITLE );
	SetTargetFPS( _targetFPS );
}

void Viewport2D::close()
{
	log( "Viewport2D::close()" );

	CloseWindow();
}

void Viewport2D::update()
{
	log( "Viewport2D::update()" );
	updateWindowSize();
	updateMousePos();
	updateCamera();
}

void Viewport2D::refresh()
{
	log( "Viewport2D::refresh()" );

	ClearBackground( BACKGROUND_COLOUR );
	DrawText( "Hello, World!", DEBUG_FONT_SIZE, DEBUG_FONT_SIZE, DEBUG_FONT_SIZE, WHITE ); // DEBUG
	BeginMode2D( _camera );
}

void Viewport2D::updateWindowSize()
{
	_windowSize.x = GetScreenWidth();
	_windowSize.y = GetScreenHeight();
}
void Viewport2D::updateMousePos()
{
	_mousePos.x = GetMouseX();
	_mousePos.y = GetMouseY();
}
void Viewport2D::updateCamera()
{

}