#ifndef VIEWPORT_HPP
# define VIEWPORT_HPP

# include "../../base.hpp"
# include "../objects/BaseObject.hpp"
#include <raylib.h>

# define WINDOW_DEFAULT_TITLE  "ToyEngine"
# define SCREEN_DEFAULT_WIDTH  2048
# define SCREEN_DEFAULT_HEIGHT 1024
# define WINDOW_DEFAULT_FPS    120
# define DEBUG_FONT_SIZE       32

# define BACKGROUND_COLOUR { 64, 64, 64, 255 }

class Viewport2D
{
	private:
	// ================================ ATTRIBUTES
		pos2_s	_windowSize;
		pos2_s	_mousePos;

		uint8_t	_targetFPS;
		float		_zoomLevel;

		Camera2D	_camera;
		bool			_trackingObject;

		// Using a weak pointer to track the object's existence
		const std::weak_ptr< BaseObject >	_trackedObject;


		// ================================ CORE METHODS
		void init();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Viewport2D();
		~Viewport2D();

	// ================================ ACCESSORS
		posint_t getWindowWidth();
		posint_t getWindowHeight();
		pos2_s   getWindowSize();

		pos2_s getWindowCenter();
		pos2_s getWindowTopLeft();
		pos2_s getWindowTopRight();
		pos2_s getWindowBotLeft();
		pos2_s getWindowBotRight();

		posint_t getMousePosX();
		posint_t getMousePosY();
		pos2_s   getMousePos();

		Camera2D &getCamera();
		bool isTracking() const;
		BaseObject *getTrackedObject() const;

		void setTarget( Vector2 target, bool overrideTracking = false );
		void moveTarget( Vector2 offset );

		void setZoom( float zoom );
		void changeZoom( float factor );

	// ================================ OPERATORS

	// ================================ METHODS
		void open();
		void close();
		void update();
		void refresh();

		void updateWindowSize();
		void updateMousePos();
		void updateCamera();

		// Using a shared pointer to track the object's existence
		bool trackObject( const std::shared_ptr<BaseObject> obj );
		bool untrackObject();
};


#endif // VIEWPORT_HPP