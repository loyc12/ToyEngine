#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS
void CompManager::clearAllPairs() // TODO : TEST ME
{
	// NOTE : mutex this if we ever multithread onTick() calls
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		NCpair &pair = it->second;
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

bool CompManager::isValidID( NttID_t id ) const // NOTE : Checks if the ID is above the current ID use range ( _maxID )
{
	if( id == 0 )
	{
		log( "Entity ID is 0", ERROR );
		return false;
	}
	if( id <= _maxID )
	{
		log( "Entity ID must be greater than curretn maxID", ERROR );
		return false;
	}
	return true;
}
bool CompManager::isUsedID( NttID_t id ) const // NOTE : Checks if the ID is used in the map
{
	if( id == 0 )
	{
		log( "Entity ID is 0", ERROR );
		return true;
	}
	if( !hasEntityByID( id ) )
	{
		log( "Entity does not exist in the map", ERROR );
		return false;
	}
	return true;
}
bool CompManager::isFreeID( NttID_t id ) const // NOTE : Checks if the ID is unused in the map
{
	if( id == 0 )
	{
		log( "Entity ID is 0", ERROR );
		return false;
	}
	if( hasEntityByID( id ) )
	{
		log( "Entity already exists in the map", ERROR );
		return false;
	}
	return true;
}

// ================ ENTITY METHODS // TODO : TEST US

GameEntity &CompManager::getNullEntity(){ return *NullNTT; }

NttID_t CompManager::getEntityCount(){ return _NttMap.size(); }
bool CompManager::hasEntity( GameEntity &Ntt ) const { return hasEntityByID( Ntt.getID() );}
bool CompManager::addEntity( GameEntity &Ntt )
{
	NttID_t id = Ntt.getID();
	if ( isUsedID( id )){ return false; }

	_NttMap[ id ] = { &Ntt, {} };
	return true;
}
bool CompManager::delEntity( GameEntity &Ntt ){ return delEntityByID( Ntt.getID() ); }

GameEntity &CompManager::getEntityByID( NttID_t id )
{
	if ( isFreeID( id )){ return *NullNTT; }
	return *_NttMap.find( id )->second.Ntt;
}
bool CompManager::hasEntityByID( NttID_t id ) const
{
	if ( id == 0 ){ return false; }
	return _NttMap.find( id ) != _NttMap.end();
}
bool CompManager::addEntityByID( NttID_t id )
{
	if ( isUsedID( id )){ return false; }

	GameEntity *Ntt = new GameEntity( false, id );
	_NttMap[ id ] = { Ntt, {} };

	if ( id >= _maxID ){ _maxID = id + 1; }
	return true;
}
bool CompManager::delEntityByID( NttID_t id )
{
	if ( isFreeID( id )){ return false; }

	NCpair &pair = _NttMap.find( id )->second;

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

	_NttMap.erase( id );
	return true;
}

// ================ COMPONENT METHODS (ID) // TODO : TEST US

BaseComp &CompManager::getNullComp(){    return *NullCMP; }
CompArr  &CompManager::getNullCompArr(){ return  NullNTT->getCompArr(); }

CompArr &CompManager::getNttCompArr( GameEntity &Ntt ){ return getNttCompArr( Ntt.getID() ); }
CompArr &CompManager::getNttCompArr( NttID_t id )
{
	if ( isFreeID( id )){ return NullNTT->getCompArr(); }
	return _NttMap.find( id )->second.Comps;
}

CompC_t CompManager::getCompCount( NttID_t id ) const
{
	if ( isFreeID( id )){ return 0; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;
	CompC_t count = 0;

	for( byte_t i = 0; i < COMP_TYPE_COUNT; ++i ){ if( comps[ i ] != nullptr ){ count++; }}
	return count;
}
TTC bool CompManager::hasComponent( NttID_t id, CompT &component ) const
{
	if( isFreeID( id )){ return false; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;
	return ( comps[ component.getType() ] != nullptr );
}
TTC bool CompManager::addComponent( NttID_t id, CompT &component )
{
	if( isUsedID( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if ( comps[ component.getType() ] != nullptr )
	{
		log( "Component already exists in the array", ERROR );
		return false;
	}

	comps[ component.getType() ] = new CompT( component );
	return true;
}
TTC bool CompManager::delComponent( NttID_t id, CompT &component )
{
	if( isFreeID( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ component.getType() ] == nullptr )
	{
		log( "Component does not exist in the array", ERROR );
		return false;
	}

	delete comps[ component.getType() ];
	comps[ component.getType() ] = nullptr;
	return true;
}

// ================ COMPONENT METHODS (TYPE) // TODO : TEST US

TTC CompT &CompManager::getComponentByType( NttID_t id, comp_e component_type )
{
	if ( isFreeID( id )){ return *NullCMP; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if ( comps[ component_type ] == nullptr )
	{
		log( "Component does not exist in the array", ERROR );
		return *comps[ 0 ];
	}
	return *comps[ component_type ];
}
bool CompManager::hasComponentByType( NttID_t id, comp_e component_type ) const
{
	if ( isFreeID( id )){ return false; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;
	return ( comps[ component_type ] != nullptr );
}
bool CompManager::addComponentByType( NttID_t id, comp_e component_type )
{
	if ( isFreeID( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if ( comps[ component_type ] != nullptr )
	{
		log( "Component already exists in the array", ERROR );
		return false;
	}

	comps[ component_type ] = new BaseComp();
	return true;
}
bool CompManager::delComponentByType( NttID_t id, comp_e component_type )
{
	if ( isFreeID( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if ( comps[ component_type ] == nullptr )
	{
		log( "Component does not exist in the array", ERROR );
		return false;
	}

	delete comps[ component_type ];
	comps[ component_type ] = nullptr;
	return true;
}
