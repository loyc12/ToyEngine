#include "../../incs/core.hpp"

// ================================ CORE METHODS

void PhysicObject::onAdd()
{
	log( "PhysicObject::onAdd()", DEBUG, _id );
	_isDynamic = true;
	_isCollide = true;

	//_position = Vector2(); // NOTE : BaseObject::onAdd() already sets the position
	_velocity = Vector2();
	_acceleration = Vector2();

	_mass = EPS;
	_radius = EPS;
	_friction = 0.0f;
	_elasticity = 0.0f;
}

void PhysicObject::onCpy( const PhysicObject &obj )
{
	log( "PhysicObject::onCpy()", DEBUG, _id );
	_isDynamic = obj.getIsDynamic();
	_isCollide = obj.getIsCollide();

	//_position = obj.getPosition(); // NOTE : BaseObject::onCpy() already copies the position
	_velocity = obj.getVelocity();
	_acceleration = obj.getAcceleration();

	_mass = obj.getMass();
	_radius = obj.getRadius();
	_friction = obj.getFriction();
	_elasticity = obj.getElasticity();
}

void PhysicObject::onDel()
{
	log( "PhysicObject::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

PhysicObject::PhysicObject() : BaseObject( E_PHYSIC ){ PhysicObject::onAdd();}

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


// ================================ ACCESSORS ( getters )

bool PhysicObject::getIsDynamic() const { return _isDynamic; }
bool PhysicObject::getIsCollide() const { return _isCollide; }

Vector2 PhysicObject::getPosition() const { return BaseObject::getPosition(); }
Vector2 PhysicObject::getVelocity() const { return _velocity; }
Vector2 PhysicObject::getAcceleration() const { return _acceleration; }
Vector2 PhysicObject::getForce() const
{
	Vector2 force = Vector2();
	force.x = _mass * _acceleration.x;
	force.y = _mass * _acceleration.y;
	return force;
}

Vector2 PhysicObject::getRelPosition( const PhysicObject &obj ) const
{
	return BaseObject::getRelPosition( obj );
}
Vector2 PhysicObject::getRelVelocity( const PhysicObject &obj ) const
{
	Vector2 relVel = Vector2();
	relVel.x = _velocity.x - obj.getVelocity().x;
	relVel.y = _velocity.y - obj.getVelocity().y;
	return relVel;
}
Vector2 PhysicObject::getRelAcceleration( const PhysicObject &obj ) const
{
	Vector2 relAcc = Vector2();
	relAcc.x = _acceleration.x - obj.getAcceleration().x;
	relAcc.y = _acceleration.y - obj.getAcceleration().y;
	return relAcc;
}
Vector2 PhysicObject::getRelForce( const PhysicObject &obj ) const
{
	Vector2 relForce = Vector2();
	relForce.x = getForce().x - obj.getForce().x;
	relForce.y = getForce().y - obj.getForce().y;
	return relForce;
}

float PhysicObject::getMass() const { return _mass; }
float PhysicObject::getRadius() const { return _radius; }
float PhysicObject::getFriction() const { return _friction; }
float PhysicObject::getElasticity() const { return _elasticity; }

float PhysicObject::getArea() const { return M_PI * _radius * _radius; }
float PhysicObject::getDensity() const { return _mass / getArea(); }
float PhysicObject::getInertia() const { return _mass * _radius * _radius; }

// ================================ ACCESSORS ( setters )

bool PhysicObject::setIsDynamic( bool isDynamic ) { _isDynamic = isDynamic; return _isDynamic; }
bool PhysicObject::setIsCollide( bool isCollide ) { _isCollide = isCollide; return _isCollide; }

Vector2 PhysicObject::setPosition( const Vector2 &pos ) { return BaseObject::setPosition( pos ); }
Vector2 PhysicObject::setVelocity( const Vector2 &vel ) { _velocity = vel; return _velocity; }
Vector2 PhysicObject::setAcceleration( const Vector2 &acc ) { _acceleration = acc; return _acceleration; }

float PhysicObject::setMass( float mass )
{
	if ( mass > 0 ){ _mass = mass; }
	else { mass = EPS; }
	return mass;
}
float PhysicObject::setRadius( float radius )
{
	if ( radius > 0 ){ _radius = radius; }
	else { _radius = EPS; }
	return _radius;
}
float PhysicObject::setFriction( float friction )
{
	if ( friction >= 0 ){ _friction = friction; }
	else { _friction = 0; }
	return _friction;
}
float PhysicObject::setElasticity( float elasticity )
{
	if ( elasticity >= 0 ){ _elasticity = elasticity; }
	else { _elasticity = 0; }
	return _elasticity;
}

// ================================ ACCESSORS ( changers )

Vector2 PhysicObject::changePosition( const Vector2 &delta ) { return BaseObject::changePosition( delta ); }
Vector2 PhysicObject::changeVelocity( const Vector2 &delta ) { _velocity.x += delta.x; _velocity.y += delta.y; return _velocity; }
Vector2 PhysicObject::changeAcceleration( const Vector2 &delta ) { _acceleration.x += delta.x; _acceleration.y += delta.y; return _acceleration; }

float PhysicObject::changeMass( float delta ) { return setMass( _mass + delta ); }
float PhysicObject::changeRadius( float delta ) { return setRadius( _radius + delta ); }
float PhysicObject::changeFriction( float delta ) { return setFriction( _friction + delta ); }
float PhysicObject::changeElasticity( float delta ) { return setElasticity( _elasticity + delta ); }

Vector2 PhysicObject::applyForce( const Vector2 &force )
{
	log ( "PhysicObject::ApplyForce()", DEBUG, _id );

	Vector2 acc = Vector2();
	acc.x = force.x / _mass;
	acc.y = force.y / _mass;

	changeAcceleration( acc );
	return acc;
}

// Applies a force in the opposite direction of the object's velocity
Vector2 PhysicObject::applyBreak( const Vector2 &breakForce )
{
	log ( "PhysicObject::ApplyBreak()", DEBUG, _id );

	Vector2 acc = Vector2();
	Vector2 vel = getVelocity();

	// if the object is not moving, no need to apply a break
	if ( vel.x == 0 && vel.y == 0 ) return acc;

	// if the object is moving, apply a break in the opposite direction of the velocity
	acc.x = sign( vel.x ) * breakForce.x / _mass;
	acc.y = sign( vel.y ) * breakForce.y / _mass;

	changeAcceleration( acc );
	return acc;
}

// ================================ OPERATORS

// ================================ METHODS

void PhysicObject::onTick() // calculates the object's physics
{
	if ( !_isDynamic ) return;
	log( "PhysicObject::onTick()", DEBUG, _id );

	// apply friction
	Vector2 friction = Vector2();
	friction.x = -sign( _velocity.x ) * _friction;
	friction.y = -sign( _velocity.y ) * _friction;
	applyForce( friction );

	// apply & resetacceleration
	changeVelocity( _acceleration );
	changePosition( _velocity );
	_acceleration.x = 0;
	_acceleration.y = 0;

}
