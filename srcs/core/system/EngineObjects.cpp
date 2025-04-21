#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

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
		return false;
	}

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( *it == obj )
		{
			log( "Engine::delObject() : Deleting object" );
			ObjectContainer.erase( it );
			return true;
		}
	}

	log( "Engine::delObject() : Failed to find requested object", WARN );
	return false;
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
			return true;
		}
	}

	log( "Engine::delObjectByID() : Failed to find requested object", WARN );

	return false;
}

void Engine::DelAllObjects()
{
	log( "Engine::DelAllObjects()" );
	if ( ObjectContainer.empty() )
	{
		log( "Engine::DelAllObjects() : ObjectContainer already empty", WARN );
		return;
	}

	while ( !ObjectContainer.empty() )
	{
		if ( ObjectContainer[ 0 ] == nullptr )
		{
			log( "Engine::DelAllObjects() : removing nullptr object", WARN );
			ObjectContainer.erase( ObjectContainer.begin() ); // NOTE : this should not happen with proper runtime memory managment
		}
		else { delete ObjectContainer[ 0 ]; } // NOTE : the object destructor will call delFromEngine() which will remove the object from the container
	}
	ObjectContainer.clear();

	log( "Engine::DelAllObjects() : Deleted all objects" );
}