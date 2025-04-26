#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ CHECK METHODS



bool CompManager::isUsedNtt( GameEntity *Ntt ) const
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "isUsedNtt : Entity is null", WARN, 0 );
		return false;
	}
	if( !hasEntity( Ntt->getID() )){ return false; }
	return true;
}
bool CompManager::isFreeNtt( GameEntity *Ntt ) const
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "isFreeNtt : Entity is null", WARN, 0 );
		return false;
	}
	if( hasEntity( Ntt->getID() )){ return false; }
	return true;
}

// ================ ENTITY METHODS

NttID_t CompManager::getEntityCount(){ return _NttMap.size(); }
GameEntity *CompManager::getEntity( NttID_t id )
{
	flog( 0 );
	if( id == 0 ){ return nullptr; }
	if( !hasEntity( id )){ return nullptr; } // NOTE : returns a null entity ( ID = 0 )
	return _NttMap.find( id )->second.Ntt;
}

bool CompManager::hasEntity( NttID_t id ) const
{
	flog( 0 );
	if( id == 0 ){ return false; }
	return ( _NttMap.find( id ) != _NttMap.end() );
}
bool CompManager::addEntity( NttID_t id )
{
	flog( 0 );
	if( id == 0 ){ return false; }
	if( hasEntity( id ))
	{
		qlog( "addEntity : Entity already exists in the map", WARN, 0 );
		return false;
	}

	qlog( "addEntity : Adding entity with ID: " + std::to_string( id ), INFO, 0 );

	_NttMap[ id ] = { NttFactory( id ), {} };

	qlog( "addEntity : Added entity with ID: " + std::to_string( id ), INFO, 0 );

	if( id > _maxID ){ _maxID = id; }
	return true;
}
bool CompManager::rmvEntity( NttID_t id )
{
	flog( 0 );
	if( id == 0 ){ return false; }
	if( !hasEntity( id )){ return false; }

	ECpair &pair = _NttMap.find( id )->second;

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( pair.Comps[ i ] != nullptr ){ pair.Comps[ i ] = nullptr; }
	}

	qlog( "rmvEntity : Removing entity with ID: " + std::to_string( id ), INFO, 0 );

	pair.Ntt->delID();
	return true;
}
bool CompManager::delEntity( NttID_t id )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	ECpair &pair = _NttMap.find( id )->second;

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( pair.Comps[ i ] != nullptr )
		{
			delete pair.Comps[ i ];
			pair.Comps[ i ] = nullptr;
		}
	}
	// NOTE: prevents the entity from trying to remove itself from the map ( aka infinite loop )
	pair.Ntt->delID();

	qlog( "delEntity : Deleting entity with ID: " + std::to_string( id ), INFO, 0 );

	delete pair.Ntt;
	pair.Ntt = nullptr;

	_NttMap.erase( id );
	return true;
}

bool CompManager::hasThatEntity( GameEntity *Ntt ) const
{
	flog( 0 );
	if( isFreeNtt( Ntt )){ return false; }
	return _NttMap.find( Ntt->getID() ) != _NttMap.end();
}
bool CompManager::addThatEntity( GameEntity *Ntt )
{
	flog( 0 );

	if ( Ntt == nullptr )
	{
		qlog( "addThatEntity : Entity is null", WARN, 0 );
		return false;
	}

	if ( Ntt->getID() == 0 )
	{
		qlog( "addThatEntity : Assigning a new ID to entity", INFO, 0 );
		Ntt->setID( getNewID() );
	}
	elif( isUsedNtt( Ntt ))
	{
		qlog( "addThatEntity : Entity already exists in the map", WARN, 0 );
		return false;
	}

	qlog( "addThatEntity : Adding entity with ID: " + std::to_string( Ntt->getID()), DEBUG, 0 );

	_NttMap[ Ntt->getID() ] = { Ntt, {} };

	qlog( "addThatEntity : Added entity with ID: " + std::to_string( Ntt->getID()), INFO, 0 );

	if( Ntt->getID() > _maxID ){ _maxID = Ntt->getID(); }
	return true;
}
bool CompManager::rmvThatEntity( GameEntity *Ntt )
{
	flog( 0 );
	if( isFreeNtt( Ntt )){ return false; }
	return rmvEntity( Ntt->getID() );
}
bool CompManager::delThatEntity( GameEntity *Ntt )
{
	flog( 0 );
	if( isFreeNtt( Ntt )){ return false; }
	return delEntity( Ntt->getID() );
}

bool CompManager::cpyEntityOver( NttID_t     src, NttID_t     dst ){ return ( cpyEntityOver( getEntity( src ), getEntity( dst ))); }
bool CompManager::cpyEntityOver( GameEntity *src, NttID_t     dst ){ return ( cpyEntityOver( src,              getEntity( dst ))); }
bool CompManager::cpyEntityOver( NttID_t     src, GameEntity *dst ){ return ( cpyEntityOver( getEntity( src ), dst )); }
bool CompManager::cpyEntityOver( GameEntity *src, GameEntity *dst )
{ // NOTE : ( add if not there ) + copy entity and its components
	flog( 0 );
	if( isFreeNtt( src )){ return false; }
	if( isFreeNtt( dst )){ return false; }

	ECpair &srcPair = _NttMap.find( src->getID() )->second;
	ECpair &dstPair = _NttMap.find( dst->getID() )->second;

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( srcPair.Comps[ i ] == nullptr )
		{
			if ( dstPair.Comps[ i ] != nullptr )
			{
				delete dstPair.Comps[ i ];
				dstPair.Comps[ i ] = nullptr;
			}
		}
		else
		{
			if( dstPair.Comps[ i ] == nullptr )
			{
				dstPair.Comps[ i ] = CompFactory( srcPair.Comps[ i ] );
				if( dstPair.Comps[ i ] == nullptr )
				{
					qlog( "cpyEntityOver : Failed to allocate memory for new component", ERROR, 0 );
					return false;
				}
			}
			else
			{
				*dstPair.Comps[ i ] = *srcPair.Comps[ i ];
			}
		}
	}
	return true;
}

bool CompManager::dupEntity( GameEntity *src ){ return dupEntity( src->getID() ); }
bool CompManager::dupEntity( NttID_t src )
{
	flog( 0 );
	if( !hasEntity( src )){ return false; }

	ECpair &srcPair = _NttMap.find( src )->second;
	NttID_t newID = getNewID();

	_NttMap[ newID ] = { NttFactory( srcPair.Ntt ), {} };

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( srcPair.Comps[ i ] != nullptr )
		{
			_NttMap[ newID ].Comps[ i ] = CompFactory( srcPair.Comps[ i ] );
			if( _NttMap[ newID ].Comps[ i ] == nullptr )
			{
				qlog( "dupEntity : Failed to allocate memory for new component", ERROR, 0 );
				return false;
			}
		}
	}
	return true;
}

// ================================ FACTORY METHODS

GameEntity *CompManager::NttFactory()
{ // NOTE : alloc new entity ( ID = 0 )
	flog( 0 );
	GameEntity *newNtt = new GameEntity( false, 0 );

	if( newNtt == nullptr )
	{
		qlog( "NttFactory : Failed to allocate memory for new entity", ERROR, 0 );
		return nullptr;
	}
	qlog( "NttFactory : Created new entity with ID: " + std::to_string( newNtt->getID()), INFO, 0 );
	return newNtt;
}
GameEntity *CompManager::NttFactory( NttID_t id )
{ // NOTE : alloc new entity with given ID
	flog( 0 );
	if( !isValidID( id )){ return nullptr; }

	GameEntity *newNtt = new GameEntity( false, id );

	if( newNtt == nullptr )
	{
		qlog( "NttFactory : Failed to allocate memory for new entity", ERROR, 0 );
		return nullptr;
	}
	qlog( "NttFactory : Created new entity with ID: " + std::to_string( id ), INFO, 0 );
	return newNtt;
}
GameEntity *CompManager::NttFactory( GameEntity *Ntt )
{ // NOTE : alloc + copy entity
	flog( 0 );
	if( Ntt == nullptr ){ return nullptr; }

	GameEntity *newNtt = new GameEntity( *Ntt );

	if( newNtt == nullptr )
	{
		qlog( "NttFactory : Failed to allocate memory for new entity", ERROR, 0 );
		return nullptr;
	}
	qlog( "NttFactory : Created new entity with ID: " + std::to_string( newNtt->getID()), INFO, 0 );
	return newNtt;
}

// ================================ STATIC METHODS

bool CompManager::isValidNtt( GameEntity *Ntt )
{
	flog( 0 );
	if( Ntt == nullptr )
	{
		qlog( "isValidNtt : Entity is null", WARN, 0 );
		return false;
	}
	return true;
}