#include "../../inc/core.hpp"

// ================================ CORE METHODS

void RenderObject::onRefresh()
{
	if ( !isVisible ) return;

	// (re)renders the object
}

void RenderObject::onAdd()
{
	BaseObject::onAdd();
	_type = E_RENDER;
}
void RenderObject::onCpy( const RenderObject &obj )
{
	BaseObject::onCpy( obj );
	isVisible = obj.isVisible;
}
void RenderObject::onDel()
{
	BaseObject::onDel();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

// ================================ ACCESSORS

bool RenderObject::getIsVisible() const { return isVisible; }
void RenderObject::setIsVisible( bool visible ) { isVisible = visible; }

// ================================ OPERATORS

// ================================ METHODS