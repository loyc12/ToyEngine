#include "../../incs/core.hpp"
#include "../../incs/game.hpp"

// ================================ CORE METHODS

void RenderObject::onAdd()
{
	log( "RenderObject::onAdd()", DEBUG, _id );
	isVisible = true;
}

void RenderObject::onCpy( const RenderObject &obj )
{
	log( "RenderObject::onCpy()", DEBUG, _id );
	isVisible = obj.getIsVisible();
}

void RenderObject::onDel()
{
	log( "RenderObject::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

RenderObject::RenderObject() : BaseObject( E_RENDER ) { RenderObject::onAdd(); }

RenderObject::RenderObject( const RenderObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	RenderObject::onCpy( obj );
}

RenderObject &RenderObject::operator=( const RenderObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	RenderObject::onCpy( obj );

	return *this;
}

RenderObject::~RenderObject() // inverted call order
{
	RenderObject::onDel();
}

// ================================ ACCESSORS

bool RenderObject::getIsVisible() const { return isVisible; }
void RenderObject::setIsVisible( bool visible ) { isVisible = visible; }

// ================================ OPERATORS

// ================================ METHODS

void RenderObject::onRenderTick() // (re)renders the object
{
	if ( !isVisible ) return;
	log( "RenderObject::onRefresh()", DEBUG, _id );

	OnRenderCall( this ); // DEBUG ?
}