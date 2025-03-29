#include "../../incs/core.hpp"
#include "../../incs/game.hpp"
#include <raylib.h>

// ================================ MEMORY METHODS

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : _state( E_UNINITIALIZED ), maxID( 0 )
{
	log( "Engine::Engine()" );

	init();
}

Engine::~Engine()
{
	log( "Engine::~Engine()" );


	if ( _state > E_UNINITIALIZED )
		close();
}

Engine *Engine::getEngine()
{
	log( "Engine::getInstance()" );

	static Engine *instance = new Engine();

	return instance;
}

// ================================ CORE METHODS

void Engine::init()
{
	log( "Engine::init()" );

	if ( _state != E_UNINITIALIZED ){ log( "Engine::init() : Engine already initialized", ERROR ); return; }

	_controller = new Controller();
	_viewport   = new Viewport2D();

	_state = E_INITIALIZED;
}

void Engine::start()
{
	log( "Engine::start()" );

	if ( _state < E_INITIALIZED ){ log( "Engine::start() : Engine not initialized", ERROR ); return; }
	if ( _state > E_INITIALIZED ){ log( "Engine::start() : Engine already started", ERROR ); return; }

	OnGameStart(); // from game.hpp

	_viewport->open();

	_state = E_STARTED;

}

void Engine::close()
{
	log( "Engine::close()" );

	if ( _state < E_INITIALIZED ){ log( "Engine::close() : Engine not initialized", ERROR ); return; }

	OnGameClose(); // from game.hpp

	delete _viewport;

	DelAllObjects();

	delete _controller;

	_state = E_UNINITIALIZED;

}

void Engine::launch()
{
	log( "Engine::launch()" );

	if ( _state < E_STARTED ) { log( "Engine::launch() : Engine not started yet", ERROR ); return; }
	if ( _state > E_STARTED ) { log( "Engine::launch() : Engine already running", ERROR ); return; }

	_state = E_RUNNING;

	while ( _state >= E_RUNNING && !WindowShouldClose() ){ runStep(); }

	_state = E_STARTED;
}

void Engine::runStep()
{
	log( "Engine::runStep()" );

	if ( _state < E_STARTED ){ log( "Engine::runeStep() : Engine not started", ERROR ); return; }

	OnGameStep(); // from game.hpp
	readInputs();
	runPhysics();
	runScripts();
	renderObjects();
}

void Engine::readInputs()
{
	log( "Engine::readInputs()" );

	_controller->refreshInputs();

	_DT = GetFrameTime();

	log( "DeltaTime : " + to_string( _DT ), WARN );

	// UPDATE OBJECTS
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onInput(); }

	OnReadInputs(); // from game.hpp
}

void Engine::runPhysics()
{
	log( "Engine::runPhysics()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onTick(); }

	OnRunPhysics(); // from game.hpp
}

void Engine::runScripts()
{
	log( "Engine::runScripts()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onUpdate(); }

	OnRunScripts(); // from game.hpp
}

void Engine::renderObjects()
{
	log( "Engine::renderObjects()" );

	BeginDrawing();

	_viewport->refresh();

	BeginMode2D( _viewport->getCamera() );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onRefresh(); }

	OnRenderObjects(); // from game.hpp

	EndMode2D();

	OnRenderUI(); // from game.hpp

	EndDrawing();
}

// ================================ OBJECTS METHODS

BaseObject *Engine::addObject( BaseObject *obj, bool checkForDupID ) // NOTE : false by default for now
{
	log( "Engine::addObject()" );

	if ( obj == nullptr )
	{
		log( "Engine::addObject() : obj cannot be a nullptr", WARN );
		return nullptr;
	}

	if ( checkForDupID )
	{
		for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
		{
			if ( *it == obj  )
			{
				log( "Engine::addObject() : obj already in container", WARN );
				return nullptr;
			}
		}
	}

	log( "Engine::addObject() : Adding object");
	ObjectContainer.push_back( obj );

	return obj;
}

bool Engine::delObject( BaseObject *obj )
{
	log( "Engine::delObject()" );

	if ( obj == nullptr )
	{
		log( "Engine::delObject() : obj cannot be a nullptr", WARN );
		return EXIT_FAILURE;
	}

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( *it == obj )
		{
			log( "Engine::delObject() : Deleting object" );
			ObjectContainer.erase( it );
			return EXIT_SUCCESS;
		}
	}

	log( "Engine::delObject() : Failed to find requested object", WARN );
	return EXIT_FAILURE;
}

bool Engine::delObjectByID( objID_t id )
{
	log( "Engine::delObjectByID()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( (*it)->getID() == id )
		{
			log( "Engine::delObjectByID() : Deleting object" );
			ObjectContainer.erase( it );
			return EXIT_SUCCESS;
		}
	}

	log( "Engine::delObjectByID() : Failed to find requested object", WARN );

	return EXIT_FAILURE;
}

void Engine::DelAllObjects()
{
	log( "Engine::DelAllObjects()" );
	while ( !ObjectContainer.empty() ) { delete ObjectContainer[ 0 ]; }
	ObjectContainer.clear();
}

// ================================ ACCESSORS

float Engine::getDeltaTime() const { return _DT; }

inputs_s   &Engine::getLatestInputs(){  return _controller->getLatestInputs(); }
inputs_s   &Engine::getPreviousInputs(){ return _controller->getPreviousInputs(); }
Controller *Engine::getController()
{
	log( "Engine::getController()" );
	return _controller;
}

Camera2D   &Engine::getCamera() { return _viewport->getCamera(); }
Viewport2D *Engine::getViewport()
{
	log( "Engine::getViewport()" );
	return _viewport;
}



BaseObject *Engine::getObjectByID( objID_t id )
{
	log( "Engine::getObjectByID()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( (*it)->getID() == id )
		{
			log( "Engine::getObjectByID() : Found requested object" );
			return *it;
		}
	}

	log( "Engine::getObjectByID() : Failed to find requested object", WARN );
	return nullptr;
}

objID_t Engine::getNewID()
{
	log( "Engine::getNewID()" );
	return ++maxID;
}

objID_t Engine::getState() const
{
	log( "Engine::getState()" );
	return _state;
}

uint32_t Engine::getObjectCount() const
{
	log( "Engine::getObjectCount()" );
	return ObjectContainer.size();
}

// ================================ OPERATORS

// ================================ METHODS
