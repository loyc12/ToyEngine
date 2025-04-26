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
		log( "Entity ID cannot be 0", WARN );
		return true;
	}
	if( !hasEntity( id ) )
	{
		log( "Entity does not exist in the map", WARN );
		return false;
	}
	return true;
}
bool CompManager::isFreeID( NttID_t id ) const
{
	flog( 0 );
	if( id == 0 )
	{
		log( "Entity ID cannot be 0", WARN );
		return false;
	}
	if( hasEntity( id ) )
	{
		log( "Entity already exists in the map", WARN );
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
		log( "Entity ID cannot be 0", WARN );
		return false;
	}
	return true;
}
bool CompManager::isValidType( comp_e type )
{
	flog( 0 );
	if( type == COMP_BASE_TYPE )
	{
		log( "Component type cannot be COMP_BASE_TYPE", WARN );
		return false;
	}
	if( type >= COMP_TYPE_COUNT )
	{
		log( "Component type is out of range", WARN );
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
