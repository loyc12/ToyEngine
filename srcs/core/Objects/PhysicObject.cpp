#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void PhysicObject::onAdd()
{
	log( "PhysicObject::onAdd()", DEBUG, getID() );
	_isDynamic = true;
	_isCollide = true;

	//_pos = Vector2(); // NOTE : BaseObject::onAdd() already sets the position
	_vel = Vector2();
	_acc = Vector2();

	_mass = 1.0f;
	_fric = 0.0f;
	_elas = 0.0f;
}

void PhysicObject::onCpy( const PhysicObject &obj )
{
	log( "PhysicObject::onCpy()", DEBUG, getID() );
	_isDynamic = obj.getIsDynamic();
	_isCollide = obj.getIsCollide();

	//_pos = obj.getPosition(); // NOTE : BaseObject::onCpy() already copies the position
	_vel = obj.getVelocity();
	_acc = obj.getAcceleration();

	_mass = obj.getMass();
	_fric = obj.getFriction();
	_elas = obj.getElasticity();
}

void PhysicObject::onDel()
{
	log( "PhysicObject::onDel()", DEBUG, getID() );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

PhysicObject::PhysicObject() :
	BaseObject( E_PHYSIC ),
	ShapeObject(),
	RenderObject()
{
	PhysicObject::onAdd();
}

PhysicObject::PhysicObject( const PhysicObject &obj ) :
	BaseObject( obj ),
	ShapeObject( obj ),
	RenderObject( obj )
{
	if ( this == &obj ) return;

	PhysicObject::onAdd();
	PhysicObject::onCpy( obj );
}

PhysicObject &PhysicObject::operator=( const PhysicObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	ShapeObject::onCpy( obj );
	PhysicObject::onCpy( obj );

	RenderObject::onCpy( obj );

	return *this;
}

PhysicObject::~PhysicObject() // automatic inverted call order
{
	PhysicObject::onDel();
	// RenderObject::onDel();
	// ShapeObject::onDel();
	// BaseObject::onDel();
}


// ================================ ACCESSORS ( getters )

bool PhysicObject::getIsDynamic() const { return _isDynamic; }
bool PhysicObject::getIsCollide() const { return _isCollide; }

Vector2 PhysicObject::getVelocity()     const { return _vel; }
Vector2 PhysicObject::getAcceleration() const { return _acc; }
Vector2 PhysicObject::getForce() const
{
	Vector2 force = Vector2();
	force.x = _mass * _acc.x;
	force.y = _mass * _acc.y;
	return force;
}


Vector2 PhysicObject::getRelVelocity( const PhysicObject &obj ) const
{
	Vector2 relVel = Vector2();
	relVel.x = _vel.x - obj.getVelocity().x;
	relVel.y = _vel.y - obj.getVelocity().y;
	return relVel;
}
Vector2 PhysicObject::getRelAcceleration( const PhysicObject &obj ) const
{
	Vector2 relAcc = Vector2();
	relAcc.x = _acc.x - obj.getAcceleration().x;
	relAcc.y = _acc.y - obj.getAcceleration().y;
	return relAcc;
}
Vector2 PhysicObject::getRelForce( const PhysicObject &obj ) const
{
	Vector2 relForce = Vector2();
	relForce.x = getForce().x - obj.getForce().x;
	relForce.y = getForce().y - obj.getForce().y;
	return relForce;
}

float PhysicObject::getMass()       const { return _mass; }
float PhysicObject::getFriction()   const { return _fric; }
float PhysicObject::getElasticity() const { return _elas; }

float PhysicObject::getDensity() const
{
	float area = max( getArea(), EPS );
	return _mass / area;
}
float PhysicObject::getInertia() const
{
	float area = max( getArea(), EPS );
	return ( _mass * area ) / 2.0f;
}

// ================================ ACCESSORS

bool PhysicObject::setIsDynamic( bool isDynamic ){ _isDynamic = isDynamic; return _isDynamic; }
bool PhysicObject::setIsCollide( bool isCollide ){ _isCollide = isCollide; return _isCollide; }

Vector2 PhysicObject::setVelocity( const Vector2 &vel ){ _vel = vel; return _vel; }
Vector2 PhysicObject::setAcceleration( const Vector2 &acc ){ _acc = acc; return _acc; }

float PhysicObject::setMass( float mass )
{
	if ( mass > 0 ){ _mass = mass; }
	else { mass = EPS; log( "PhysicObject::setMass() : mass cannot be negative : clamping to EPS", WARN ); }
	return mass;
}
float PhysicObject::setFriction( float friction )
{
	if ( friction >= 0 ){ _fric = friction; }
	else { _fric = 0; log( "PhysicObject::setFriction() : friction cannot be negative : clamping to 0", WARN ); }
	return _fric;
}
float PhysicObject::setElasticity( float elasticity )
{
	if ( elasticity >= 0 ){ _elas = elasticity; }
	else { _elas = 0; log( "PhysicObject::setElasticity() : elasticity cannot be negative : clamping to 0", WARN ); }
	return _elas;
}

// ================================ MUTATORS

Vector2 PhysicObject::moveVelocity( const Vector2 &delta ){ _vel.x += delta.x; _vel.y += delta.y; return _vel; }
Vector2 PhysicObject::moveAcceleration( const Vector2 &delta ){ _acc.x += delta.x; _acc.y += delta.y; return _acc; }

float PhysicObject::moveMass( float delta ){ return setMass( _mass + delta ); }
float PhysicObject::moveFriction( float delta ){ return setFriction( _fric + delta ); }
float PhysicObject::moveElasticity( float delta ){ return setElasticity( _elas + delta ); }

Vector2 PhysicObject::applyForce( const Vector2 &force )
{
	log ( "PhysicObject::ApplyForce()", DEBUG, getID() );

	Vector2 acc = Vector2();
	acc.x = force.x / _mass;
	acc.y = force.y / _mass;

	moveAcceleration( acc );
	return acc;
}

// Applies a force in the opposite direction of the object's velocity
Vector2 PhysicObject::applyBreak( const Vector2 &breakForce )
{
	log ( "PhysicObject::ApplyBreak()", DEBUG, getID() );

	Vector2 acc = Vector2();
	Vector2 vel = getVelocity();

	// if the object is not moving, no need to apply a break
	if ( vel.x == 0 && vel.y == 0 ) return acc;

	// if the object is moving, apply a break in the opposite direction of the velocity
	acc.x = sign( vel.x ) * breakForce.x / _mass;
	acc.y = sign( vel.y ) * breakForce.y / _mass;

	moveAcceleration( acc );
	return acc;
}

// ================================ OPERATORS

// ================================ METHODS

void PhysicObject::onPhysicTick() // calculates the object's physics
{
	if ( !_isDynamic ) return;
	log( "PhysicObject::onPhysicTick()", DEBUG, getID() );

	OnPhysicCall( this ); // DEBUG ?

	// apply & reset acceleration
	if ( _acc.x != 0 || _acc.y != 0 )
	{
		Vector2 acc = Vector2();
		acc.x = _acc.x / _mass;
		acc.y = _acc.y / _mass;

		moveVelocity( acc );
		setAcceleration( Vector2() );
	}

	// apply movement
	if ( _vel.x != 0 || _vel.y != 0 ){ movePosition( _vel ); }


	// apply friction
	Vector2 friction = Vector2();
	friction.x = -sign( _vel.x ) * _fric;
	friction.y = -sign( _vel.y ) * _fric;
	if ( _vel.x != 0 || _vel.y != 0 ){ applyForce( friction ); }
}
