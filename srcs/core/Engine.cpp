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

	_viewport = new Viewport2D();

	bzero( &_previousInputs, sizeof( inputs_s ) );
	bzero( &_lastestInputs, sizeof( inputs_s ) );

	_state = E_INITIALIZED;
}

void Engine::start()
{
	log( "Engine::start()" );

	if ( _state < E_INITIALIZED ){ log( "Engine::start() : Engine not initialized", ERROR ); return; }
	if ( _state > E_INITIALIZED ){ log( "Engine::start() : Engine already started", ERROR ); return; }

	_viewport->open();

	_state = E_STARTED;

}

void Engine::close()
{
	log( "Engine::close()" );

	if ( _state < E_INITIALIZED ){ log( "Engine::close() : Engine not initialized", ERROR ); return; }

	delete _viewport;

	DelAllObjects();

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

	on_game_step(); // from game.hpp
	readInputs();
	runPhysics();
	runScripts();
	renderObjects();
}

void Engine::readInputs()
{
	log( "Engine::readInputs()" );

	// SAVE PREVIOUS INPUTS
	_previousInputs = _lastestInputs;

	// BASE
	_lastestInputs.LEFT  = IsKeyDown( KEY_A ) || IsKeyDown( KEY_LEFT );
	_lastestInputs.RIGHT = IsKeyDown( KEY_D ) || IsKeyDown( KEY_RIGHT );
	_lastestInputs.FORE  = IsKeyDown( KEY_W ) || IsKeyDown( KEY_UP );
	_lastestInputs.BACK  = IsKeyDown( KEY_S ) || IsKeyDown( KEY_DOWN );
	_lastestInputs.SPACE = IsKeyDown( KEY_SPACE ) || IsKeyDown( KEY_KP_0 );
	_lastestInputs.ENTER = IsKeyDown( KEY_ENTER ) || IsKeyDown( KEY_KP_ENTER );
	_lastestInputs.SHIFT = IsKeyDown( KEY_LEFT_SHIFT ) || IsKeyDown( KEY_RIGHT_SHIFT );
	_lastestInputs.CTRL  = IsKeyDown( KEY_LEFT_CONTROL ) || IsKeyDown( KEY_RIGHT_CONTROL );
	_lastestInputs.ALT   = IsKeyDown( KEY_LEFT_ALT ) || IsKeyDown( KEY_RIGHT_ALT );
	_lastestInputs.TAB   = IsKeyDown( KEY_TAB ) || IsKeyDown( KEY_BACKSLASH );

	// MOUSE
	_lastestInputs.CLICK_LEFT  = IsMouseButtonDown( MOUSE_LEFT_BUTTON );
	_lastestInputs.CLICK_MID   = IsMouseButtonDown( MOUSE_MIDDLE_BUTTON );
	_lastestInputs.CLICK_RIGHT = IsMouseButtonDown( MOUSE_RIGHT_BUTTON );
	_lastestInputs.SCROLL_UP   = ( GetMouseWheelMove() > 0 );
	_lastestInputs.SCROLL_DOWN = ( GetMouseWheelMove() < 0 );

	// KEYBOARD
	_lastestInputs.Q = IsKeyDown( KEY_Q );
	_lastestInputs.E = IsKeyDown( KEY_E );
	_lastestInputs.R = IsKeyDown( KEY_R );
	_lastestInputs.F = IsKeyDown( KEY_F );
	_lastestInputs.Z = IsKeyDown( KEY_Z );
	_lastestInputs.X = IsKeyDown( KEY_X );
	_lastestInputs.C = IsKeyDown( KEY_C );
	_lastestInputs.V = IsKeyDown( KEY_V );

	// UPDATE OBJECTS
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onInput(); }
}

void Engine::runPhysics()
{
	log( "Engine::runPhysics()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onTick(); }
}

void Engine::runScripts()
{
	log( "Engine::runScripts()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onUpdate(); }
}

void Engine::renderObjects()
{
	log( "Engine::renderObjects()" );

	BeginDrawing();

	_viewport->update();
	_viewport->refresh();

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { (*it)->onRefresh(); }

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

inputs_s &Engine::getLastestInputs(){  return _lastestInputs; }
inputs_s &Engine::getPreviousInputs(){ return _previousInputs; }

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
