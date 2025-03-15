#include "../../inc/core.hpp"

// ================================ CORE METHODS

void PhysicObject::onAdd()
{
	log( "PhysicObject::onAdd()" );
	isDynamic = true;
	isCollide = true;

	position = Vector2();
	velocity = Vector2();
	acceleration = Vector2();
}

void PhysicObject::onCpy( const PhysicObject &obj )
{
	log( "PhysicObject::onCpy()" );
	isDynamic = obj.getIsDynamic();
	isCollide = obj.getIsCollide();

	position = obj.getPosition();
	velocity = obj.getVelocity();
	acceleration = obj.getAcceleration();
}

void PhysicObject::onDel()
{
	log( "PhysicObject::onDel()" );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

PhysicObject::PhysicObject() : BaseObject( E_PHYSIC ){ PhysicObject::onAdd();}
PhysicObject::PhysicObject( objID_t id ) : BaseObject( id, E_PHYSIC ){ PhysicObject::onAdd();}

PhysicObject::PhysicObject( const PhysicObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	PhysicObject::onCpy( obj );
}

PhysicObject &PhysicObject::operator=( const PhysicObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	PhysicObject::onCpy( obj );

	return *this;
}

PhysicObject::~PhysicObject() // inverted call order
{
	PhysicObject::onDel();
}


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

void PhysicObject::onTick() // calculates the object's physics
{
	if ( !isDynamic ) return;
	log( "PhysicObject::onTick()" );
}
