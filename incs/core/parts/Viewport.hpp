#ifndef VIEWPORT_HPP
# define VIEWPORT_HPP

# include <raylib.h>
# include "../../base.hpp"
# include "../objects/ShapeObject.hpp"


# define WINDOW_DEFAULT_TITLE  "ToyEngine"
# define WINDOW_DEFAULT_FPS    128
# define SCREEN_DEFAULT_WIDTH  2048
# define SCREEN_DEFAULT_HEIGHT 1024

# define DEBUG_FONT_SIZE 32
# define MAX_ZOOM        0.25f
# define DEFAULT_ZOOM    2.00f
# define MIN_ZOOM        16.0f

# define BACKGROUND_COLOUR { 64, 64, 64, 255 }

class Viewport2D
{
	private:
	// ================================ ATTRIBUTES
		uint8_t	_targetFPS;

		Vector2	_windowSize;    // latest size of the window in pixels
		Vector2	_mousePos;      // latest position of the mouse in pixels
		Vector2	_mouseWorldPos; // latest position of the mouse in world units

		Camera2D	 _camera;      // contains target, zoom, rotation, offset
		ShapeObject *_trackedObject;

		bool _trackingObject;

		// ================================ CORE METHODS
		void init();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Viewport2D();
		~Viewport2D();

	// ================================ ACCESSORS
		float getWidth()      const;
		float getHeight()     const;
		float getZmdWidth()   const;
		float getZmdHeight()  const;

		Vector2 getSize()     const;
		Vector2 getOrigin()   const;
		Vector2 getCenter()   const;

		Vector2 getTop()      const;
		Vector2 getBot()      const;
		Vector2 getLeft()     const;
		Vector2 getRight()    const;
		Vector2 getTopLeft()  const;
		Vector2 getTopRight() const;
		Vector2 getBotLeft()  const;
		Vector2 getBotRight() const;

		Vector2 getMousePos()      const;
		Vector2 getMouseWorldPos() const;

		// ================================ CAMERA ACCESSORS
		Camera2D &getCamera();

		Vector2	getTarget() const;
		void    setTarget(  Vector2 target, bool overrideTracking = false );
		void    moveTarget( Vector2 offset );

		float   getZoom();
		void    setZoom( float zoom );
		void    scaleZoom( float factor );

		float   getRotation();
		//void    setRotation( float rotation );
		//void    changeRotation( float delta );

		Vector2 getOffset() const;
		//void    setOffset( Vector2 offset );
		//void    moveOffset( Vector2 delta );

	// ================================ OPERATORS

	// ================================ METHODS
		void open();
		void close();
		void update();
		void refresh();

		void updateSize();
		void updateMouse();
		void updateCamera();

	// ================================ OBJECT TRACKING
		ShapeObject *getTrackedObject() const;

		bool isTracking() const;
		bool trackObject( ShapeObject *obj, bool overrideTracking = false );
		bool untrackObject();
};


#endif // VIEWPORT_HPP