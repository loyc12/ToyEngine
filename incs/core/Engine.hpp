#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <raylib.h>
# include "../base.hpp"
# include "./objects/Object2D.hpp"
# include "./parts/Viewport.hpp"
# include "./parts/Controller.hpp"

# define MOVE_SPEED 128
# define ZOOM_SPEED 16

typedef enum : byte_t
{
	E_UNINITIALIZED = 0,
	E_INITIALIZED,
	E_STARTED,
	E_RUNNING

} engineState_e;

class Engine
{
	private:
	// ================================ CORE METHODS
		void init(); // initializes the engine's data
		void runStep(); // calls the 4 object update methods

		void readInputs(); // reads the inputs, updates the global var struct & calls the onInput() method of every object
		void runPhysics(); // calls the onTick() method of every object
		void runScripts(); // calls the onUpdate() method of every object
		void renderObjects(); // calls the onRefresh() method of every object

	// ================================ ATTRIBUTES
		Viewport2D *_viewport;
		Controller *_controller;

		vector< BaseObject* > ObjectContainer;

		engineState_e _state;
		objID_t maxID;
		float _DT;

	// ================================ CONSTRUCTORS / DESTRUCTORS
	// prevents this singleton from being copied
		Engine( const Engine &cpy ) = delete;
		Engine &operator=( const Engine &cpy ) = delete;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Engine();   ~Engine();

		static Engine *getEngine();

	// ================================ CORE METHODS
		void start(); //  opens the window and redies the engine for the game loop
		void launch(); // calls the 4 object update methods in a loop
		void close(); //  closes the window and frees the memory

	// ================================ OBJECTS METHODS
		BaseObject *addObject( BaseObject *ob, bool checkForDupID = false ); // NOTE : put to true by default ?

		bool delObject( BaseObject *obj );
		bool delObjectByID( objID_t id );
		void DelAllObjects();

	// ================================ ACCESSORS
	  float getDeltaTime() const;

		inputs_s   &getLatestInputs();
		inputs_s   &getPreviousInputs();
		Controller *getController();

		Camera2D   &getCamera();
		Viewport2D *getViewport();

		BaseObject *getObjectByID( objID_t id );

		objID_t  getNewID();
		objID_t  getState() const;
		uint32_t getObjectCount() const;

	// ================================ OPERATORS

	// ================================ METHODS

};

#endif // ENGINE_HPP