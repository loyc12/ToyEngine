
#ifndef COMP_MANAGER_TPP
# define COMP_MANAGER_TPP

# pragma once
# include "./CompManager.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ CHECK METHODS

TTC bool CompManager::isUsedComp( CompT *comp ) const
{
	flog( 0 );
	if( comp == nullptr )
	{
		qlog( "isUsedComp : Component is null", DEBUG, 0 );
		return false;
	}
	if( !hasThatComponent( comp->getID(), comp ))
	{
		qlog( "isUsedComp : Component does not exist in the map", DEBUG, 0 );
		return false;
	}
	return true;
}
TTC bool CompManager::isFreeComp( CompT *comp ) const
{
	flog( 0 );
	if( comp == nullptr )
	{
		qlog( "isFreeComp : Component is null", DEBUG, 0 );
		return false;
	}
	if( hasThatComponent( comp->getID(), comp ))
	{
		qlog( "isFreeComp : Component already exists in the map", DEBUG, 0 );
		return false;
	}
	return true;
}


// ================ COMPONENT METHODS

TTC CompT *CompManager::getComponent( NttID_t id )
{
	flog( 0 );
	if( !hasEntity( id )){ return nullptr; } // NOTE : returns a null BaseComponent ( innactive )

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		qlog( "getComponent : Component does not exist in the array", WARN, 0 );
		return nullptr;
	}
	return ( CompT* )comps[ compType ];
}
TTC CompT *CompManager::cpyComponent( NttID_t id ) const
{ // NOTE : overloading of const is fine, since we are only copying the componetn via its reference, and not modifying it
	flog( 0 );

	CompT* newComp;
	&newComp = &const_cast<CompManager*>( this )->getComponent < CompT >( id );
	return newComp;
}

TTC bool CompManager::hasComponent( NttID_t id ) const
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;
	return ( comps[ CompT::getType() ] != nullptr );
}
TTC bool CompManager::addComponent( NttID_t id )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ CompT::getType() ] != nullptr )
	{
		qlog( "addComponent : Component already exists in the array", WARN, 0 );
		return false;
	}

	comps[ CompT::getType() ] = CompFactory< CompT >( id );
	return true;
}
TTC bool CompManager::rmvComponent( NttID_t id )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		qlog( "rmvComponent : Component does not exist in the array", WARN, 0 );
		return false;
	}

	qlog( "rmvComponent : Removing component of type: " + std::to_string( compType ) + " for entity ID: " + std::to_string( id ), INFO, 0 );

	comps[ compType ] = nullptr;

	return true;
}
TTC bool CompManager::delComponent( NttID_t id )
{
	flog( 0 );
	if( !hasEntity( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ compType ] == nullptr )
	{
		qlog( "delComponent : Component does not exist in the array", WARN, 0 );
		return false;
	}

	qlog( "delComponent : Deleting component of type: " + std::to_string( compType ) + " for entity ID: " + std::to_string( id ), INFO, 0 );

	delete comps[ compType ];
	comps[ compType ] = nullptr;

	return true;
}

// ================ COMPONENT METHODS ( specific comps )

TTC bool CompManager::hasThatComponent( NttID_t id, CompT *component ) const
{
	flog( 0 );
	if( component == nullptr )
	{
		qlog( "hasThatComponent : Component is null", WARN, 0 );
		return false;
	}
	if( !hasEntity( id )){ return false; }

	comp_e compType = CompT::getType();
	const CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] != nullptr ) { return false; }

	return ( component == comps[ compType ]); // NOTE : compares the component pointers
}
TTC bool CompManager::addThatComponent( NttID_t id, CompT *component )
{
	flog( 0 );
	if ( component == nullptr )
	{
		qlog( "addThatComponent : Component is null", WARN, 0 );
		return false;
	}
	if( id == 0 )
	{
		qlog( "addThatComponent : Cannot add a component to ID 0", WARN, 0 );
		return false;
	}
	if( !hasEntity( id ))
	{
		qlog( "addThatComponent : Entity does not exist in the map", WARN, 0 );
		return false;
	}
	if( hasThatComponent( id, component ))
	{
		qlog( "addThatComponent : Component already exists in the array", WARN, 0 );
		return false;
	}
	if( id != component->getID() && component->getID() != 0 )
	{
		qlog( "addThatComponent : Component ID does not match entity ID", WARN, 0 );
		return false;
	}

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] != nullptr )
	{
		qlog( "addThatComponent : Removing Previous Component", DEBUG, 0 );
		delete comps[ compType ];
	}

	comps[ compType ] = component;
	return true;
}
TTC bool CompManager::rmvThatComponent( NttID_t id, CompT *component )
{
	flog( 0 );
	if( component == nullptr )
	{
		qlog( "hasThatComponent : Component is null", WARN, 0 );
		return false;
	}
	if( !hasEntity( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		qlog( "rmvThatComponent : Component does not exist in the array", WARN, 0 );
		return false;
	}

	comps[ compType ] = nullptr;

	return true;
}
TTC bool CompManager::delThatComponent( NttID_t id, CompT *component )
{
	flog( 0 );
	if( component == nullptr )
	{
		qlog( "hasThatComponent : Component is null", WARN, 0 );
		return false;
	}
	if( !hasEntity( id )){ return false; }
	if( !hasThatComponent( id, component )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	delete comps[ compType ];
	comps[ compType ] = nullptr;

	return true;
}

// ================================ STATIC METHODS

TTC bool CompManager::isValidComp( CompT *comp )
{
	flog( 0 );
	if( comp == nullptr )
	{
		qlog( "isValidComp : Component is null", WARN, 0 );
		return false;
	}
	return true;
}

// ================ FACTORY METHODS

TTC CompT *CompManager::CompFactory()
{ // NOTE : alloc new component
	flog( 0 );
	CompT *newComp = new CompT( true, 0 );

	if( newComp == nullptr )
	{
		qlog( "CompFactory : Failed to allocate memory for new component", ERROR , 0);
		return nullptr;
	}
	return newComp;
}
TTC CompT *CompManager::CompFactory( NttID_t id )
{ // NOTE : alloc new component with given ID
	flog( 0 );
	if( id == 0 ){ return nullptr; }

	CompT *newComp = new CompT( true, id );

	if( newComp == nullptr )
	{
		qlog( "CompFactory : Failed to allocate memory for new component", ERROR, 0 );
		return nullptr;
	}
	return newComp;
}
TTC CompT *CompManager::CompFactory( CompT *component )
{ // NOTE : alloc + copy component
	flog( 0 );
	if( component == nullptr ){ return nullptr; }

	CompT *newComp = new CompT( *component );

	if( newComp == nullptr )
	{
		qlog( "CompFactory : Failed to allocate memory for new component", ERROR, 0 );
		return nullptr;
	}
	return newComp;
}

#endif // COMP_MANAGER_TPP