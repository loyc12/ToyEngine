
#ifndef COMP_MANAGER_TPP
# define COMP_MANAGER_TPP

# pragma once
# include "./CompManager.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ CHECK METHODS

TTC bool CompManager::isFreeComp( CompT *comp ) const
{
	if( comp == nullptr )
	{
		log( "Component is null", WARN );
		return false;
	}
	if( comp->getID() == 0 )
	{
		log( "Component ID cannot be 0", WARN );
		return false;
	}
	if( hasThatComponent( comp->getID(), comp ))
	{
		log( "Component already exists in the map", WARN );
		return false;
	}
	return true;
}
TTC bool CompManager::isUsedComp( CompT *comp ) const
{
	if( comp == nullptr )
	{
		log( "Component is null", WARN );
		return false;
	}
	if( comp->getID() == 0 )
	{
		log( "Component ID cannot be 0", WARN );
		return false;
	}
	if( !hasThatComponent( comp->getID(), comp ))
	{
		log( "Component does not exist in the map", WARN );
		return false;
	}
	return true;
}

// ================ COMPONENT METHODS

TTC CompT &CompManager::getComponent( NttID_t id )
{
	if( !isUsedID( id )){ return GetNullComp< CompT >(); } // NOTE : returns a null BaseComponent ( innactive )

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		log( "Component does not exist in the array", ERROR );
		return GetNullComp< CompT >();
	}
	return ( CompT& )*comps[ compType ];
}
TTC CompT CompManager::cpyComponent( NttID_t id ) const
{ // NOTE : overloading of const is fine, since we are only copying the componetn via its reference, and not modifying it
	return const_cast<CompManager*>( this )->getComponent< CompT >( id );
}

TTC bool CompManager::hasComponent( NttID_t id ) const
{
	if( !isUsedID( id )){ return false; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;
	return ( comps[ CompT::getType() ] != nullptr );
}
TTC bool CompManager::addComponent( NttID_t id )
{
	if( !isUsedID( id )){ return false; }

	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ CompT::getType() ] != nullptr )
	{
		log( "CompManager::addComponent() : Component already exists in the array", ERROR );
		return false;
	}

	comps[ CompT::getType() ] = CompFactory< CompT >( id );
	return true;
}
TTC bool CompManager::rmvComponent( NttID_t id )
{
	if( !isUsedID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		log( "CompManager::rmvComponent() : Component does not exist in the array", WARN );
		return false;
	}
	comps[ compType ] = nullptr;

	return true;
}
TTC bool CompManager::delComponent( NttID_t id )
{
	if( !isUsedID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;
	if( comps[ compType ] == nullptr )
	{
		log( "CompManager::delComponent() : Component does not exist in the array", ERROR );
		return false;
	}
	delete comps[ compType ];
	comps[ compType ] = nullptr;

	return true;
}

// ================ COMPONENT METHODS ( specific comps )

TTC bool CompManager::hasThatComponent( NttID_t id, CompT *component ) const
{
	if( !isUsedID( id )){ return false; }

	comp_e compType = CompT::getType();
	const CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] != nullptr ) { return false; }

	return ( component == comps[ compType ]); // NOTE : compares the component pointers
}
TTC bool CompManager::addThatComponent( NttID_t id, CompT *component )
{
	if( !isUsedID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] != nullptr )
	{
		log( "CompManager::addThatComponent() : Removing Previous Component", INFO );
		delete comps[ compType ];
	}

	comps[ compType ] = *component;
	return true;
}
TTC bool CompManager::rmvThatComponent( NttID_t id, CompT *component )
{
	if( !isUsedID( id )){ return false; }

	comp_e compType = CompT::getType();
	CompArr &comps = _NttMap.find( id )->second.Comps;

	if( comps[ compType ] == nullptr )
	{
		log( "CompManager::rmvThatComponent() : Component does not exist in the array", WARN );
		return false;
	}

	comps[ compType ] = nullptr;

	return true;
}
TTC bool CompManager::delThatComponent( NttID_t id, CompT *component )
{
	if( !isUsedID( id )){ return false; }

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

// ================================ STATIC METHODS

TTC bool CompManager::isValidComp( CompT *comp )
{
	if( comp == nullptr )
	{
		log( "Component is null", WARN );
		return false;
	}
	return true;
}

// ================ FACTORY METHODS

TTC CompT &CompManager::GetNullComp()
{
	static CompT val( false, 0 );
	return val;
}

TTC CompT *CompManager::CompFactory()
{ // NOTE : alloc new component
	CompT *newComp = new CompT( true, 0 );

	if( newComp == nullptr )
	{
		log( "CompManager::CompFactory(1) : Failed to allocate memory for new component", ERROR );
		return nullptr;
	}
	return newComp;
}
TTC CompT *CompManager::CompFactory( NttID_t id )
{ // NOTE : alloc new component with given ID
	if( id == 0 ){ return nullptr; }

	CompT *newComp = new CompT( true, id );

	if( newComp == nullptr )
	{
		log( "CompManager::CompFactory(2) : Failed to allocate memory for new component", ERROR );
		return nullptr;
	}
	return newComp;
}
TTC CompT *CompManager::CompFactory( CompT *component )
{ // NOTE : alloc + copy component
	if( component == nullptr ){ return nullptr; }

	CompT *newComp = new CompT( *component );

	if( newComp == nullptr )
	{
		log( "CompManager::CompFactory(2) : Failed to allocate memory for new component", ERROR );
		return nullptr;
	}
	return newComp;
}

#endif // COMP_MANAGER_TPP