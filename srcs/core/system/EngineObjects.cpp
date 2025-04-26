#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ OBJECTS METHODS

BaseObject *Engine::addObject( BaseObject *obj, bool checkForDupID ) // NOTE : false by default for now
{
	flog( 0 );
	if ( obj == nullptr )
	{
		log( "Object cannot be a nullptr", WARN );
		return nullptr;
	}

	if ( checkForDupID )
	{
		for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
		{
			if ( *it == obj  )
			{
				log( "Object already in container", WARN );
				return nullptr;
			}
		}
	}

	log( "Adding object");
	ObjectContainer.push_back( obj );

	return obj;
}

bool Engine::delObject( BaseObject *obj )
{
	flog( 0 );
	if ( obj == nullptr )
	{
		log( "Object cannot be a nullptr", WARN );
		return false;
	}

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( *it == obj )
		{
			log( "Deleting object" );
			ObjectContainer.erase( it );
			return true;
		}
	}

	log( "Failed to find requested object", WARN );
	return false;
}

bool Engine::delObjectByID( objID_t id )
{
	flog( 0 );
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( (*it)->getID() == id )
		{
			log( "Deleting object" );
			ObjectContainer.erase( it );
			return true;
		}
	}

	log( "Failed to find requested object", WARN );
	return false;
}

void Engine::DelAllObjects()
{
	flog( 0 );
	if ( ObjectContainer.empty() )
	{
		log( "ObjectContainer already empty", WARN );
		return;
	}

	while ( !ObjectContainer.empty() )
	{
		if ( ObjectContainer[ 0 ] == nullptr )
		{
			log( "Removing nullptr object", WARN );
			ObjectContainer.erase( ObjectContainer.begin() ); // NOTE : this should not happen with proper runtime memory managment
		}
		else { delete ObjectContainer[ 0 ]; } // NOTE : the object destructor will call delFromEngine() which will remove the object from the container
	}
	ObjectContainer.clear();

	log( "Deleted all objects" );
}