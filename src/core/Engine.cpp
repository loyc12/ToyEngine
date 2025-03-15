#include "../../inc/core.hpp"
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

	if ( state != E_UNINITIALIZED )
		close();
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

	state = E_UNINITIALIZED;
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

	InitWindow( 800, 600, "Engine" );

	while ( state >= E_RUNNING && !WindowShouldClose() )
	{
		readInputs(); if ( WindowShouldClose() ){ break; }
		runPhysics();
		runScripts();
		renderObjects();
	}
}

void Engine::readInputs()
{
	log( "Engine::readInputs()" );

	//if ( IsKeyPressed( KEY_ESCAPE )){ CloseWindow(); }

	// update gloal inputs here

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { it->onInput(); }
}

void Engine::runPhysics()
{
	log( "Engine::runPhysics()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { it->onTick(); }
}

void Engine::runScripts()
{
	log( "Engine::runScripts()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { it->onUpdate(); }
}

void Engine::renderObjects()
{
	log( "Engine::renderObjects()" );

	BeginDrawing();

	ClearBackground( { 64, 64, 64, 255 } );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ ) { it->onRefresh(); }

	EndDrawing();
}

// ================================ OBJECTS METHODS

Object2D *Engine::addNewObject()
{
	log( "Engine::addNewObject()" );

	Object2D *Obj = new Object2D( getNewID() );
	ObjectContainer.push_back( *Obj );

	return Obj;
}

Object2D *Engine::getObjectByID( objID_t id )
{
	log( "Engine::getObjectByID()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( it->getID() == id )
			return &*it;
	}

	log( "Engine::getObjectByID() : Failed to find requested object", WARN );

	return nullptr;
}

bool Engine::delObject( Object2D *obj )
{
	log( "Engine::delObject()" );

	if ( obj == nullptr )
	{
		log( "Engine::delObject() : obj cannot be a nullptr", INFO );
		return false;
	}

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( &*it == obj )
		{
			ObjectContainer.erase( it );
			return true;
		}
	}

	log( "Engine::delObject() : Failed to find requested object", INFO );

	return false;
}

bool Engine::delObjectByID( objID_t id )
{
	log( "Engine::delObjectByID()" );

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( it->getID() == id )
		{
			ObjectContainer.erase( it );
			return true;
		}
	}

	log( "Engine::delObjectByID() : Failed to find requested object", INFO );

	return false;
}

// ================================ ACCESSORS

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

// ================================ OPERATORS

// ================================ METHODS

Engine *getEngine()
{
	static Engine *engine = nullptr;

	if ( engine == nullptr )
	{
		engine = new Engine();
	}

	return engine;
}