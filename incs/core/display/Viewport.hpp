#ifndef VIEWPORT_HPP
# define VIEWPORT_HPP

# include "../../base.hpp"

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
		pos2_s	 _windowSize;
		pos2_s	 _mousePos;

		uint8_t  _targetFPS;
		float    _zoomLevel;

		Camera2D _camera;

		// ================================ CORE METHODS
		void init();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Viewport2D();
		~Viewport2D();

	// ================================ ACCESSORS
		posint_t getWindowWidth();
		posint_t getWindowHeight();
		pos2_s getWindowSize();

		pos2_s getWindowCenter();
		pos2_s getWindowTopLeft();
		pos2_s getWindowTopRight();
		pos2_s getWindowBotLeft();
		pos2_s getWindowBotRight();

		posint_t getMousePosX();
		posint_t getMousePosY();
		pos2_s getMousePos();

	// ================================ OPERATORS

	// ================================ METHODS
		void open();
		void close();
		void update();
		void refresh();

		void updateWindowSize();
		void updateMousePos();
		void updateCamera();
};


#endif // VIEWPORT_HPP