#include "../../inc/core.hpp"

// ================================ CORE METHODS

void RenderObject::onAdd()
{
	log( "RenderObject::onAdd()" );
	isVisible = true;
}

void RenderObject::onCpy( const RenderObject &obj )
{
	log( "RenderObject::onCpy()" );
	isVisible = obj.getIsVisible();
}

void RenderObject::onDel()
{
	log( "RenderObject::onDel()" );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

RenderObject::RenderObject() : BaseObject( E_RENDER )
{
	BaseObject::onAdd();
	RenderObject::onAdd();
}

RenderObject::RenderObject( const RenderObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	RenderObject::onCpy( obj );
}

RenderObject &RenderObject::operator=( const RenderObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::operator=( obj );
	RenderObject::onCpy( obj );

	return *this;
}

RenderObject::~RenderObject() // inverted call order
{
	RenderObject::onDel();
	BaseObject::onDel();
}

// ================================ ACCESSORS

bool RenderObject::getIsVisible() const { return isVisible; }
void RenderObject::setIsVisible( bool visible ) { isVisible = visible; }

// ================================ OPERATORS

// ================================ METHODS

void RenderObject::onRefresh() // (re)renders the object
{
	log( "RenderObject::onRefresh()" );
	if ( !isVisible ) return;
}