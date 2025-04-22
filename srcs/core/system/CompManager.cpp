#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

ECpair     &NullECPair  = CompManager::getNullECpair();
GameEntity &NullNtt     = CompManager::getNullEntity();
CompArr    &NullCompArr = CompManager::getNullCompArr();
BaseComp   &NullComp    = CompManager::getNullComp();

// ================================ CORE METHODS
void CompManager::clearAllPairs() // TODO : TEST ME
{
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

bool CompManager::isValidType( comp_e type ) const // NOTE : Checks if the type is valid ( 0 <= type < COMP_TYPE_COUNT )
{
	if( type == COMP_BASE_TYPE )
	{
		log( "Component type cannot be COMP_BASE_TYPE", ERROR );
		return false;
	}
	if( type >= COMP_TYPE_COUNT )
	{
		log( "Component type is out of range", ERROR );
		return false;
	}
	return true;
}

bool CompManager::isValidID( NttID_t id ) const // NOTE : Checks if the ID is above the current ID use range ( _maxID )
{
	if( id == 0 )
	{
		log( "Entity ID cannot be 0", ERROR );
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
		log( "Entity ID cannot be 0", ERROR );
		return true;
	}
	if( !hasEntity( id ) )
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
		log( "Entity ID cannot be 0", ERROR );
		return false;
	}
	if( hasEntity( id ) )
	{
		log( "Entity already exists in the map", ERROR );
		return false;
	}
	return true;
}

// ================ ENTITY METHODS

NttID_t CompManager::getEntityCount(){ return _NttMap.size(); }
GameEntity CompManager::getEntity( NttID_t id )
{
	if( isFreeID( id )){ return NullNtt; } // NOTE : returns a null entity ( ID = 0 )
	return *_NttMap.find( id )->second.Ntt;
}

bool CompManager::hasEntity( NttID_t id ) const
{
	if( id == 0 ){ return false; }
	return _NttMap.find( id ) != _NttMap.end();
}
bool CompManager::addEntity( NttID_t id )
{
	if( isUsedID( id )){ return false; }

	GameEntity *Ntt = new GameEntity( false, id );
	_NttMap[ id ] = { Ntt, {} };

	if( id >= _maxID ){ _maxID = id + 1; }
	return true;
}
bool CompManager::delEntity( NttID_t id )
{
	if( isFreeID( id )){ return false; }

	ECpair &pair = _NttMap.find( id )->second;

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( pair.Comps[ i ] != nullptr )
		{
			delete pair.Comps[ i ];
			pair.Comps[ i ] = nullptr;
		}
	}

	pair.Ntt->delID(); // NOTE: prevents the entity from trying to remove itself from the map ( aka infinite loop )
	delete pair.Ntt;
	pair.Ntt = nullptr;

	_NttMap.erase( id );
	return true;
}

bool CompManager::hasThatEntity( GameEntity *Ntt ) const { return hasEntity( Ntt->getID() );}
bool CompManager::addThatEntity( GameEntity *Ntt )
{
	NttID_t id = Ntt->getID();
	if( isUsedID( id )){ return false; }

	_NttMap[ id ] = { Ntt, {} };
	return true;
}
bool CompManager::delThatEntity( GameEntity *Ntt ){ return delEntity( Ntt->getID() ); }

bool CompManager::cpyEntityOver( GameEntity &src, GameEntity &dst ){ return ( cpyEntityOver( src.getID(), dst.getID() )); }
bool CompManager::cpyEntityOver( GameEntity &src, NttID_t     dst ){ return ( cpyEntityOver( src.getID(), dst )); }
bool CompManager::cpyEntityOver( NttID_t     src, GameEntity &dst ){ return ( cpyEntityOver( src,         dst.getID() )); }
bool CompManager::cpyEntityOver( NttID_t     src, NttID_t     dst )
{
	if( isFreeID( src )){ return false; }
	if( isFreeID( dst )){ return false; }

	ECpair &srcPair = _NttMap.find( src )->second;
	ECpair &dstPair = _NttMap.find( dst )->second;

	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if(   srcPair.Comps[ i ] == nullptr && dstPair.Comps[ i ] == nullptr ){ continue; }
		elif( srcPair.Comps[ i ] != nullptr && dstPair.Comps[ i ] == nullptr )
		{
			dstPair.Comps[ i ] = new BaseComp(  *srcPair.Comps[ i ] ); // WIP NOTE : probably does not return the correct type
		}
		elif( srcPair.Comps[ i ] == nullptr && dstPair.Comps[ i ] != nullptr )
		{
			delete dstPair.Comps[ i ];
			dstPair.Comps[ i ] = nullptr;
		}
		elif( srcPair.Comps[ i ] != nullptr && dstPair.Comps[ i ] != nullptr )
		{
			*dstPair.Comps[ i ] = *srcPair.Comps[ i ];
		}
	}
	return true;
}



// ================ COMPONENT METHODS

CompArr &CompManager::getNttCompArr( GameEntity &Ntt ){ return getNttCompArr( Ntt.getID() ); }
CompArr &CompManager::getNttCompArr( NttID_t id )
{
	if( isFreeID( id )){ return NullCompArr; } // NOTE : returns a null array of components ( all nullptr )
	return _NttMap.find( id )->second.Comps;
}

CompC_t CompManager::getCompCount( NttID_t id ) const
{
	if( isFreeID( id )){ return 0; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;

	CompC_t count = 0;
	for( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( comps[ i ] != nullptr ){ count++; }
	}
	return count;
}
TTC CompT &CompManager::getComponent( NttID_t id )
{
	if( isFreeID( id )){ return ( CompT )NullComp; } // NOTE : returns a null BaseComponent ( innactive )

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		log( "Component does not exist in the array", ERROR );
		return NullComp;
	}
	return *comps[ compType ];
}

TTC CompT CompManager::cpyComponent( NttID_t id ) const
{ // NOTE : overloading of const is fine, since we are only copying the componetn via its reference, and not modifying it
	return const_cast<CompManager*>( this )->getComponent< CompT >( id );
}

TTC bool CompManager::hasThatComponent( NttID_t id, CompT *component ) const
{
	if( isFreeID( id )){ return false; }

	comp_e compType = CompT::getType();
	const CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] != nullptr ) { return false; }

	return ( component == comps[ compType ]); // NOTE : compares the component pointers
}

TTC bool CompManager::addThatComponent( NttID_t id, CompT *component )
{
	if( isFreeID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] != nullptr )
	{
		log( "CompManager::addThatComponent() : Removing Previous Component", DEBUG );
		delete comps[ compType ];
	}

	comps[ compType ] = *component;
	return true;
}

TTC bool CompManager::delThatComponent( NttID_t id, CompT *component )
{
	if( isFreeID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		log( "CompManager::delThatComponent() : Component does not exist in the array", ERROR );
		return false;
	}

	delete comps[ compType ];
	comps[ compType ] = nullptr;

	return true;
}

// ================ COMPONENT METHODS ( specific comps )

TTC bool CompManager::hasComponent( NttID_t id ) const
{
	if( isFreeID( id )){ return false; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;
	return ( comps[ CompT::getType() ] != nullptr );
}

TTC bool CompManager::addComponent( NttID_t id )
{
	if( isFreeID( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ CompT::getType() ] != nullptr )
	{
		log( "CompManager::addComponent() : Component already exists in the array", ERROR );
		return false;
	}

	comps[ CompT::getType() ] = new BaseComp();
	return true;
}

TTC bool CompManager::delComponent( NttID_t id )
{
	if( isFreeID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ compType ] == nullptr )
	{
		log( "CompManager::delComponent() : Component does not exist in the array", ERROR );
		return false;
	}
	delete comps[ compType];
	comps[ compType ] = nullptr;

	return true;
}

// ================================ STATIC METHODS

GameEntity &CompManager::getNullEntity()
{
	static GameEntity val( false, 0 );
	return val;
}
CompArr &CompManager::getNullCompArr()
{
	static CompArr val = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	return val;
}
BaseComp &CompManager::getNullComp()
{
	static BaseComp val( false );
	return val;
}
ECpair &CompManager::getNullECpair()
{
	static ECpair val = { nullptr, {} };
	return val;
}

// ================================ TICK METHODS

void CompManager::updateAllEntities()
{
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		ECpair &pair = it->second;
		for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
		{
			if( pair.Comps[ i ] != nullptr ){ pair.Comps[ i ]->onTick(); }
		}
	}
}

void CompManager::updateAllComponents()
{
	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
		{
			ECpair &pair = it->second;
			if( pair.Comps[ i ] != nullptr ){ pair.Comps[ i ]->onTick(); }
		}
	}
}

void CompManager::updateComponentByType( comp_e compType )
{
	if( !isValidType( compType) )
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		ECpair &pair = it->second;
		if( pair.Comps[ compType ] != nullptr ){ pair.Comps[ compType ]->onTick(); }
	}
}