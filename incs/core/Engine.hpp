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
	ES_CLOSED, // either not yet initialized or closed ( deinitialized )
	ES_INITIALIZING,

	ES_CLOSING,
	ES_INITIALIZED, // initialized but either not yet started or stopped
	ES_STARTING,

	ES_STOPPING,
	ES_STARTED, // started but either not yet ran or paused
	ES_RESUMING,

	ES_PAUSING,
	ES_RUNNING, // running

} engineState_e;

class Engine
{
	// ================================ ATTRIBUTES
	private:
		Viewport2D *_viewport;
		Controller *_controller;

		vector< BaseObject* > ObjectContainer;

		std::mutex mtx_state;
		engineState_e _state;

		objID_t maxID;
		float _DT;


	// ================================ STATE METHODS
	public:
		bool switchState(  engineState_e targetState );
		bool togglePause(); // switches the state between paused and running

	private:
		void init(); // initializes the engine's data
			void start(); // opens the window and readies the engine for the game loop
				void resume(); // resumes the engine physics
				void pause(); // pauses the engine physics
			void stop(); // stops the engine
		void close(); // closes the engine

	// ================================ STEP METHODS
	public:
		bool launchLoop(); // launches the game loop
		// NOTE : this is a blocking call for now. It will be multithreaded later
		// TODO : add a way to run the game loop in a separate thread
		// DEBUG : for now, this is called manually in main.cpp once I know the window is opened

	private:
		void runStep(); // calls the update methods once
			void readInputs();
			void runPhysics();
			void runScripts();
			void runRenders(); // calls the render methods once
				void renderWorld();
				void renderUIs();

	// ================================ CONSTRUCTORS / DESTRUCTORS
	private:
		// prevents this singleton from being copied
		Engine( const Engine &cpy ) = delete;
		Engine &operator=( const Engine &cpy ) = delete;

	public:
		Engine(); ~Engine();

		static Engine *getEngine();

	// ================================ OBJECTS METHODS
	public:
		BaseObject *addObject( BaseObject *ob, bool checkForDupID = false ); // NOTE : put to true by default ?

		bool delObject( BaseObject *obj );
		bool delObjectByID( objID_t id );

	private:
		void DelAllObjects(); // deletes all objects in the container

	// ================================ ACCESSORS
	public:
	  float getDeltaTime() const;

		inputs_s   &getLatestInputs();
		inputs_s   &getPreviousInputs();
		Controller *getController();

		Camera2D   &getCamera();
		Viewport2D *getViewport();

		BaseObject *getObjectByID( objID_t id );

		objID_t  getNewID();
		uint32_t getObjectCount() const;

		engineState_e  getState();


	// ================================ MUTEXED ACCESSORS
	private:
		void setState( engineState_e newState );

	// ================================ OTHER METHODS

};

#endif // ENGINE_HPP