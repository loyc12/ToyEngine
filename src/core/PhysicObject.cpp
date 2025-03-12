#include "../../inc/core.hpp"

// ================================ CORE METHODS

void PhysicObject::onTick()
{
	if ( !isDynamic ) return;

	// calculates the object's physics
}

void PhysicObject::collideWith( BaseObject *other )
{
	if ( !isCollide ) return;

	// checks for collision with another object
}

void PhysicObject::onAdd()
{
	BaseObject::onAdd();
	_type = E_PHYSIC;
}
void PhysicObject::onCpy( const PhysicObject &obj )
{
	BaseObject::onCpy( obj );
	isDynamic = obj.isDynamic;
	isCollide = obj.isCollide;
	position = obj.position;
	velocity = obj.velocity;
	acceleration = obj.acceleration;
}
void PhysicObject::onDel()
{
	BaseObject::onDel();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

// ================================ ACCESSORS

bool PhysicObject::getIsDynamic() const { return isDynamic; }
void PhysicObject::setIsDynamic( bool dynamic ) { isDynamic = dynamic; }

bool PhysicObject::getIsCollide() const { return isCollide; }
void PhysicObject::setIsCollide( bool collide ) { isCollide = collide; }

Vector2 PhysicObject::getPosition() const { return position; }
Vector2 PhysicObject::getVelocity() const { return velocity; }
Vector2 PhysicObject::getAcceleration() const { return acceleration; }

void PhysicObject::setPosition( const Vector2 &pos ) { position = pos; }
void PhysicObject::setVelocity( const Vector2 &vel ) { velocity = vel; }
void PhysicObject::setAcceleration( const Vector2 &acc ) { acceleration = acc; }

// ================================ OPERATORS

// ================================ METHODS