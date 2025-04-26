#include <raylib.h>
#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ OBJECTS METHODS

BaseObject *Engine::addObject( BaseObject *obj, bool checkForDupID ) // NOTE : false by default for now
{
	flog( 0 );
	if ( obj == nullptr )
	{
		qlog( "addObject : Object cannot be a nullptr", WARN, 0 );
		return nullptr;
	}

	if ( checkForDupID )
	{
		for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
		{
			if ( *it == obj  )
			{
				qlog( "addObject : Object already in container", WARN, obj->getID() );
				return nullptr;
			}
		}
	}

	qlog( "addObject : Adding object", DEBUG, obj->getID() );
	ObjectContainer.push_back( obj );

	return obj;
}

bool Engine::delObject( BaseObject *obj )
{
	flog( 0 );
	if ( obj == nullptr )
	{
		qlog( "delObject : Object cannot be a nullptr", WARN, 0 );
		return false;
	}

	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( *it == obj )
		{
			qlog( "delObject : Deleting object", DEBUG, obj->getID() );
			ObjectContainer.erase( it );
			return true;
		}
	}

	qlog( "delObject : Failed to find requested object", WARN, obj->getID() );
	return false;
}

bool Engine::delObjectByID( objID_t id )
{
	flog( 0 );
	for ( auto it = ObjectContainer.begin(); it != ObjectContainer.end(); it++ )
	{
		if ( (*it)->getID() == id )
		{
			qlog( "delObjectByID : Deleting object", DEBUG, id );
			ObjectContainer.erase( it );
			return true;
		}
	}

	qlog( "delObjectByID : Failed to find requested object", WARN, id );
	return false;
}

void Engine::DelAllObjects()
{
	flog( 0 );
	if ( ObjectContainer.empty() )
	{
		qlog( "DelAllObjects : ObjectContainer already empty", INFO, 0 );
		return;
	}

	while ( !ObjectContainer.empty() )
	{
		if ( ObjectContainer[ 0 ] == nullptr )
		{
			qlog( "DelAllObjects : Removing nullptr object", WARN, 0 );
			ObjectContainer.erase( ObjectContainer.begin() ); // NOTE : this should not happen with proper runtime memory managment
		}
		else { delete ObjectContainer[ 0 ]; } // NOTE : the object destructor will call delFromEngine() which will remove the object from the container
	}
	ObjectContainer.clear();

	qlog( "DelAllObjects : Deleted all objects", INFO, 0 );
}