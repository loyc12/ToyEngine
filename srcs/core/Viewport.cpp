#include <raylib.h>
#include "../../incs/core.hpp"

// ================================ CORE METHODS

void Viewport2D::init()
{
	log( "Viewport2D::init()" );

	_targetFPS = WINDOW_DEFAULT_FPS;

	_windowSize     = {SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT};
	_mousePos       = {0, 0};
	_mouseWorldPos  = {0, 0};

	_camera.target   = { 0.0f, 0.0f };
	_camera.zoom     = DEFAULT_ZOOM;
	_camera.rotation = 0.0f;
	_camera.offset   = { _windowSize.x / 2, _windowSize.y / 2 };

	_trackingObject  = false;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Viewport2D::Viewport2D()
{
	log( "Viewport2D::Viewport2D()" );
	init();
}

Viewport2D::~Viewport2D()
{
	log( "Viewport2D::~Viewport2D()" );
	close();
}

// ================================ ACCESSORS

float Viewport2D::getWidth()      const { return _windowSize.x; }
float Viewport2D::getHeight()     const { return _windowSize.y; }
float Viewport2D::getZmdWidth()   const { return _windowSize.x / _camera.zoom; } // returns the width of the camera view in world units
float Viewport2D::getZmdHeight()  const { return _windowSize.y / _camera.zoom; } // returns the height of the camera view in world units

Vector2 Viewport2D::getSize()     const { return _windowSize; }
Vector2 Viewport2D::getCenter()   const { return _camera.target; }
Vector2 Viewport2D::getOrigin()   const { return GetScreenToWorld2D( { 0, 0 }, _camera ); } // returns the origin of the camera view in world units

Vector2 Viewport2D::getTopLeft()  const { return GetScreenToWorld2D( { 0,                0 },                _camera ); }
Vector2 Viewport2D::getTopRight() const { return GetScreenToWorld2D( { getZmdWidth(),    0 },                _camera ); }
Vector2 Viewport2D::getBotLeft()  const { return GetScreenToWorld2D( { 0,                getZmdHeight()   }, _camera ); }
Vector2 Viewport2D::getBotRight() const { return GetScreenToWorld2D( { getZmdWidth(),    getZmdHeight()   }, _camera ); }

Vector2 Viewport2D::getTop()      const { return GetScreenToWorld2D( { _camera.target.x, 0 },                _camera ); }
Vector2 Viewport2D::getBot()      const { return GetScreenToWorld2D( { _camera.target.x, getZmdHeight()   }, _camera ); }
Vector2 Viewport2D::getLeft()     const { return GetScreenToWorld2D( { 0,                _camera.target.y }, _camera ); }
Vector2 Viewport2D::getRight()    const { return GetScreenToWorld2D( { getZmdWidth(),    _camera.target.y }, _camera ); }

Vector2 Viewport2D::getMousePos()      const { return _mousePos; }
Vector2 Viewport2D::getMouseWorldPos() const { return _mouseWorldPos; }

// ================================ CAMERA ACCESSORS

Camera2D &Viewport2D::getCamera(){ return _camera; }

Vector2 Viewport2D::getTarget() const { return _camera.target; }
void Viewport2D::moveTarget( Vector2 offset )
{
	_camera.target.x += offset.x;
	_camera.target.y += offset.y;
}
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

float Viewport2D::getZoom(){ return _camera.zoom; }
void Viewport2D::setZoom(   float zoom ){ _camera.zoom = zoom; }
void Viewport2D::scaleZoom( float factor ){ _camera.zoom *= factor; }

float Viewport2D::getRotation(){ return _camera.rotation; }
//void Viewport2D::setRotation( float rotation ){ _camera.rotation = rotation; }
//void Viewport2D::changeRotation( float delta ){ _camera.rotation += delta; }

Vector2 Viewport2D::getOffset() const { return _camera.offset; }
/*
void Viewport2D::setOffset( Vector2 &offset ){ _camera.offset = offset; }
void Viewport2D::moveOffset( Vector2 &delta )
{
	_camera.offset.x += offset.x;
	_camera.offset.y += offset.y;
}
*/

// ================================ METHODS

void Viewport2D::open()
{
	log( "Viewport2D::open()" );

	if ( IsWindowReady() )
	{
		log( "Viewport2D::open() : Window already opened", INFO );
		return;
	}

	InitWindow( _windowSize.x, _windowSize.y, WINDOW_DEFAULT_TITLE );

	// TODO : handle failure case

	SetTargetFPS( _targetFPS );
}

void Viewport2D::close()
{
	log( "Viewport2D::close()" );

	if ( !IsWindowReady() )
	{
		log( "Viewport2D::close() : Window already closed", INFO );
		return;
	}

	// TODO : handle failure case

	CloseWindow();
}

void Viewport2D::update()
{
	log( "Viewport2D::update()" );
	updateCamera();
	updateSize();
	updateMouse();
}

void Viewport2D::refresh()
{
	log( "Viewport2D::refresh()" );
	ClearBackground( BACKGROUND_COLOUR );
	update();
}

void Viewport2D::updateSize()
{
	// sets _windowSize to the camera view size
	_windowSize.x = GetScreenWidth()  * _camera.zoom;
	_windowSize.y = GetScreenHeight() * _camera.zoom;
}
void Viewport2D::updateMouse()
{
	// sets _mousePos to were the mouse is in the world, accounting for the camera position
	_mousePos = GetMousePosition();
	_mouseWorldPos = GetScreenToWorld2D( _mousePos, _camera );

}
void Viewport2D::updateCamera()
{
	if ( _trackingObject ){ _camera.target = { _trackedObject->getPosition() }; }

	// Clamping camera values
	if ( _camera.zoom > MIN_ZOOM ){ _camera.zoom = MIN_ZOOM; }
	if ( _camera.zoom < MAX_ZOOM ){ _camera.zoom = MAX_ZOOM; }

	if ( _camera.rotation < 0.0f   ) while ( _camera.rotation < 0.0f   ){ _camera.rotation += 360.0f; }
	if ( _camera.rotation > 360.0f ) while ( _camera.rotation > 360.0f ){ _camera.rotation -= 360.0f; }

	//_camera.offset = { ( float )_windowSize.x / 2, ( float )_windowSize.y / 2 };

}

// ================================ OBJECTS TRACKING

BaseObject *Viewport2D::getTrackedObject() const { return _trackedObject; }

bool Viewport2D::isTracking() const { return _trackingObject; }

bool Viewport2D::trackObject( BaseObject *obj, bool overrideTracking )
{
	if ( obj == nullptr )
	{
		log( "Viewport2D::trackObject() : cannot track a nullptr", INFO );
		log( "Viewport2D::trackObject() : Use untrackObject() to stop tracking", DEBUG );
		return false;
	}

	if ( _trackingObject )
	{
		if ( !overrideTracking )
		{
			log( "Viewport2D::trackObject() : Already tracking an object", INFO );
			log( "Viewport2D::trackObject() : Use overrideTracking = true to override", DEBUG );
			return false;
		}
		else { log( "Viewport2D::trackObject() : Overriding tracking", INFO ); }
	}

	_trackedObject  = obj;
	_trackingObject = true;

	return true;
}

bool Viewport2D::untrackObject()
{
	_trackedObject = nullptr;

	if ( !_trackingObject ){ return false; }

	_trackingObject = false; return true;
}

