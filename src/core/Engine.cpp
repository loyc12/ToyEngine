#include "../../inc/core.hpp"
#include <cstddef>
#include <raylib.h>

// ================================ MEMORY METHODS

// ================================ CONSTRUCTORS / DESTRUCTORS

Engine::Engine() : state( E_UNINITIALIZED ), maxID( 0 )
{
	log( "Engine::Engine()" );

	start();
}

Engine::~Engine()
{
	log( "Engine::~Engine()" );

	if ( state > E_UNINITIALIZED )
		close();
}

Engine *Engine::getEngine()
{
	log( "Engine::getInstance()" );

	static Engine *instance;

	if ( instance == nullptr ){ instance = new Engine(); }

	return instance;
}

// ================================ CORE METHODS

void Engine::start()
{
	log( "Engine::start()" );

	if ( state != E_UNINITIALIZED )
	{
		log( "Engine::start() : Engine already running", ERROR );
		return;
	}

	state = E_INITIALIZED;
}

void Engine::close()
{
	log( "Engine::close()" );

	if ( state < E_INITIALIZED )
	{
		log( "Engine::close() : Engine not running", ERROR );
		return;
	}

	DelAllObjects();

	state = E_UNINITIALIZED;

	CloseWindow();

}

void Engine::launch()
{
	log( "Engine::launch()" );

	if ( state < E_INITIALIZED )
	{
		log( "Engine::launch() : Engine not initialized", ERROR );
		return;
	}

	state = E_RUNNING;

	InitWindow( SCREEN_STARTING_WIDTH, SCREEN_STARTING_HEIGHT, WINDOW_STARTING_TITLE );

	while ( state >= E_RUNNING && !WindowShouldClose() )
	{
		runStep();
	}
}

void Engine::runStep()
{
	log( "Engine::runeStep()" );

	if ( state < E_INITIALIZED )
	{
		log( "Engine::runeStep() : Engine not initialized", ERROR );
		return;
	}

	readInputs();
	runPhysics();
	runScripts();
	renderObjects();
}

void Engine::readInputs()
{
	log( "Engine::readInputs()" );

	// update gloal inputs here

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

	ClearBackground( { 64, 64, 64, 255 } );

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

	return state;
}

uint32_t Engine::getObjectCount() const
{
	log( "Engine::getObjectCount()" );

	return ObjectContainer.size();
}

// ================================ OPERATORS

// ================================ METHODS
