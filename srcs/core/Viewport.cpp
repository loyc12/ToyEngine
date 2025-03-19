#include "../../incs/core.hpp"

// ================================ CORE METHODS

void Viewport2D::init()
{
	log( "Viewport2D::init()" );

	_windowSize = {SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT};
	_mousePos = {0, 0};
	_targetFPS = WINDOW_DEFAULT_FPS;
	_zoomLevel = 1.0f;
	_trackingObject = false;

	bzero( &_camera, sizeof( Camera2D ) );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Viewport2D::Viewport2D()
{
	log( "Viewport2D::Viewport2D()" ); init();
}

Viewport2D::~Viewport2D()
{
	log( "Viewport2D::~Viewport2D()" ); close();
}

// ================================ ACCESSORS

posint_t Viewport2D::getWindowWidth()  { return _windowSize.x; }
posint_t Viewport2D::getWindowHeight() { return _windowSize.y; }
pos2_s Viewport2D::getWindowSize()     { return _windowSize; }

pos2_s Viewport2D::getWindowCenter()   { return _windowSize / 2; }
pos2_s Viewport2D::getWindowTopLeft()  { return { 0, 0 }; }
pos2_s Viewport2D::getWindowTopRight() { return { _windowSize.x, 0 }; }
pos2_s Viewport2D::getWindowBotLeft()  { return { 0, _windowSize.y }; }
pos2_s Viewport2D::getWindowBotRight() { return _windowSize; }

posint_t Viewport2D::getMousePosX()	{ return _mousePos.x; }
posint_t Viewport2D::getMousePosY()	{ return _mousePos.y; }
pos2_s Viewport2D::getMousePos()		{ return _mousePos; }

Camera2D &Viewport2D::getCamera() { return _camera; }
bool Viewport2D::isTracking() const { return _trackingObject; }
BaseObject *Viewport2D::getTrackedObject() const { return _trackedObject.lock().get(); }

void Viewport2D::setTarget( Vector2 target, bool overrideTracking )
{
	if ( _trackingObject )
	{
		if ( !overrideTracking )
		{
			log( "Viewport2D::setTarget() : Already tracking an object", INFO );
			log( "Viewport2D::setTarget() : Use overrideTracking = true to override", INFO );
			return;
		}
		else { log( "Viewport2D::setTarget() : Overriding tracking", INFO ); }
	}
	_trackingObject = false;
	_camera.target = target;
}
void Viewport2D::moveTarget( Vector2 offset )
{
	_camera.target.x += offset.x;
	_camera.target.y += offset.y;
}

void Viewport2D::setZoom( float zoom ) { _zoomLevel = zoom; }
void Viewport2D::changeZoom( float factor ) { _zoomLevel *= factor; }


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

	update();

	ClearBackground( BACKGROUND_COLOUR );

	DrawText( "Hello, World!", DEBUG_FONT_SIZE, DEBUG_FONT_SIZE, DEBUG_FONT_SIZE, WHITE ); // DEBUG
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
	_camera.zoom = _zoomLevel;

	if ( _trackingObject )
	{
		// Check if the weak pointer is still valid
		auto trackedObject = _trackedObject.lock();
		if ( !trackedObject )
		{
			log( "Viewport2D::updateCamera() : Tracked object no longer exists", INFO );
			log( "Viewport2D::updateCamera() : Stopping tracking", INFO );
			_trackingObject = false; return;
		}
		_camera.target = { trackedObject->getPosition().x, trackedObject->getPosition().y };
		_camera.offset = { ( float )_windowSize.x / 2, ( float )_windowSize.y / 2 }; // NOTE : superfluous ?
		}

}
