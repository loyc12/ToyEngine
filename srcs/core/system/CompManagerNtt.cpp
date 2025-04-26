#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ CHECK METHODS

bool CompManager::isUsedNtt( GameEntity *Ntt ) const
{
	if( Ntt == nullptr )
	{
		log( "Entity is null", WARN );
		return false;
	}
	if( Ntt->getID() == 0 )
	{
		log( "Entity ID cannot be 0", WARN );
		return false;
	}
	if( !hasEntity( Ntt->getID() ))
	{
		log( "Entity does not exist in the map", WARN );
		return false;
	}
	return true;
}
bool CompManager::isFreeNtt( GameEntity *Ntt ) const
{
	if( Ntt == nullptr )
	{
		log( "Entity is null", WARN );
		return false;
	}
	if( Ntt->getID() == 0 )
	{
		log( "Entity ID cannot be 0", WARN );
		return false;
	}
	if( hasEntity( Ntt->getID() ))
	{
		log( "Entity already exists in the map", WARN );
		return false;
	}
	return true;
}

// ================ ENTITY METHODS

NttID_t CompManager::getEntityCount(){ return _NttMap.size(); }
GameEntity CompManager::getEntity( NttID_t id )
{
	if( !isUsedID( id )){ return NullNtt; } // NOTE : returns a null entity ( ID = 0 )
	return *_NttMap.find( id )->second.Ntt;
}

bool CompManager::hasEntity( NttID_t id ) const
{
	if( id == 0 ){ return false; }
	return _NttMap.find( id ) != _NttMap.end();
}
bool CompManager::addEntity( NttID_t id )
{
	if( !isFreeID( id )){ return false; }

	_NttMap[ id ] = { NttFactory( id ), {} };

	if( id >= _maxID ){ _maxID = id + 1; }
	return true;
}
bool CompManager::rmvEntity( NttID_t id )
{
	if( !isUsedID( id )){ return false; }

	ECpair &pair = _NttMap.find( id )->second;

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( pair.Comps[ i ] != nullptr ){ pair.Comps[ i ] = nullptr; }
	}

	pair.Ntt->delID();
	return true;
}
bool CompManager::delEntity( NttID_t id )
{
	if( !isUsedID( id )){ return false; }

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

	delete pair.Ntt;
	pair.Ntt = nullptr;

	_NttMap.erase( id );
	return true;
}

bool CompManager::hasThatEntity( GameEntity *Ntt ) const
{
	if( !isUsedNtt( Ntt )){ return false; }
	return _NttMap.find( Ntt->getID() ) != _NttMap.end();
}
bool CompManager::addThatEntity( GameEntity *Ntt )
{
	if( !isFreeNtt( Ntt ))
	{
		log( "CompManager::addThatEntity() : Entity already exists in the map", WARN );
		return false;
	}
	Ntt->setID( getNewID() );
	log( "CompManager::addThatEntity()", DEBUG, Ntt->getID() );

	_NttMap[ Ntt->getID() ] = { Ntt, {} };
	return true;
}
bool CompManager::rmvThatEntity( GameEntity *Ntt )
{
	if( !isUsedNtt( Ntt )){ return false; }
	return rmvEntity( Ntt->getID() );
}
bool CompManager::delThatEntity( GameEntity *Ntt )
{
	if( !isUsedNtt( Ntt )){ return false; }
	return delEntity( Ntt->getID() );
}

bool CompManager::cpyEntityOver( GameEntity &src, GameEntity &dst ){ return ( cpyEntityOver( src.getID(), dst.getID() )); }
bool CompManager::cpyEntityOver( GameEntity &src, NttID_t     dst ){ return ( cpyEntityOver( src.getID(), dst )); }
bool CompManager::cpyEntityOver( NttID_t     src, GameEntity &dst ){ return ( cpyEntityOver( src,         dst.getID() )); }
bool CompManager::cpyEntityOver( NttID_t     src, NttID_t     dst )
{ // NOTE : ( add if not there ) + copy entity and its components
	if( !isUsedID( src )){ return false; }
	if( !isUsedID( dst )){ return false; }

	ECpair &srcPair = _NttMap.find( src )->second;
	ECpair &dstPair = _NttMap.find( dst )->second;

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
					log( "CompManager::cpyEntityOver() : Failed to allocate memory for new component", ERROR );
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

bool CompManager::dupEntity( GameEntity &src ){ return dupEntity( src.getID() ); }
bool CompManager::dupEntity( NttID_t src )
{
	if( !isUsedID( src )){ return false; }

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
				log( "CompManager::dupEntity() : Failed to allocate memory for new component", ERROR );
				return false;
			}
		}
	}
	return true;
}

// ================================ FACTORY METHODS

GameEntity *CompManager::NttFactory()
{ // NOTE : alloc new entity ( ID = 0 )
	GameEntity *newNtt = new GameEntity( false, 0 );

	if( newNtt == nullptr )
	{
		log( "CompManager::NttFactory(1) : Failed to allocate memory for new entity", ERROR );
		return nullptr;
	}
	return newNtt;
}
GameEntity *CompManager::NttFactory( NttID_t id )
{ // NOTE : alloc new entity with given ID
	if( !isValidID( id )){ return nullptr; }

	GameEntity *newNtt = new GameEntity( false, id );

	if( newNtt == nullptr )
	{
		log( "CompManager::NttFactory(2) : Failed to allocate memory for new entity", ERROR );
		return nullptr;
	}
	return newNtt;
}
GameEntity *CompManager::NttFactory( GameEntity *Ntt )
{ // NOTE : alloc + copy entity
	if( Ntt == nullptr ){ return nullptr; }

	GameEntity *newNtt = new GameEntity( *Ntt );

	if( newNtt == nullptr )
	{
		log( "CompManager::NttFactory(3) : Failed to allocate memory for new entity", ERROR );
		return nullptr;
	}
	return newNtt;
}

// ================================ STATIC METHODS

bool CompManager::isValidNtt( GameEntity *Ntt )
{
	if( Ntt == nullptr )
	{
		log( "Entity is null", WARN );
		return false;
	}
	return true;
}