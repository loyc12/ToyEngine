#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

ECpair     &NullECPair  = CompManager::GetNullECpair();
GameEntity &NullNtt     = CompManager::GetNullEntity();
CompArr    &NullCompArr = CompManager::GetNullCompArr();

// ================================ CORE METHODS

void CompManager::clearAllPairs() // TODO : TEST ME
{
	flog( 0 );
	// NOTE : mutex this if we ever multithread onTick() calls
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		ECpair &pair = it->second;
		for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
		{
			if( pair.Comps[ i ] != nullptr )
			{
				delete pair.Comps[ i ];
				pair.Comps[ i ] = nullptr;
			}
		}
		delete pair.Ntt;
		pair.Ntt = nullptr;
	}
	_NttMap.clear();
}

// ================================ ACCESSORS / MUTATORS

// ================ CHECK METHODS

bool CompManager::isUsedID( NttID_t id ) const
{
	flog( 0 );
	if( id == 0 )
	{
		qlog( "isUsedID : Entity ID cannot be 0", WARN, 0 );
		return false;
	}
	if( !hasEntity( id ) )
	{
		qlog( "isUsedID : Entity does not exist in the map", WARN, 0 );
		return false;
	}
	return true;
}
bool CompManager::isFreeID( NttID_t id ) const
{
	flog( 0 );
	if( id == 0 )
	{
		qlog( "isFreeID : Entity ID cannot be 0", WARN, 0 );
		return false;
	}
	if( hasEntity( id ) )
	{
		qlog( "isFreeID : Entity already exists in the map", WARN, 0 );
		return false;
	}
	return true;
}

// ================================ STATIC METHODS

bool CompManager::isValidID( NttID_t id )
{
	flog( 0 );
	if( id == 0 )
	{
		qlog( "isValidID : Entity ID cannot be 0", WARN, 0 );
		return false;
	}
	return true;
}
bool CompManager::isValidType( comp_e type )
{
	flog( 0 );
	if( type == COMP_BASE_TYPE )
	{
		qlog( "Component type cannot be COMP_BASE_TYPE", WARN, 0 );
		return false;
	}
	if( type >= COMP_TYPE_COUNT )
	{
		qlog( "isValidType : Component type is out of range", WARN, 0 );
		return false;
	}
	return true;
}

// ================================ STATIC METHODS

// ================ FACTORY METHODS

ECpair &CompManager::GetNullECpair()
{
	flog( 0 );
	static ECpair val = { nullptr, {} };
	return val;
}
GameEntity &CompManager::GetNullEntity()
{
	flog( 0 );
	static GameEntity val( false, 0 );
	return val;
}
CompArr &CompManager::GetNullCompArr()
{
	flog( 0 );
	static CompArr val = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	return val;
}
