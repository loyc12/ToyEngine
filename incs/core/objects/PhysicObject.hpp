#ifndef PHYSICOBJECT_HPP
# define PHYSICOBJECT_HPP

# include <raylib.h>
# include "./BaseObject.hpp"

class PhysicObject : virtual public BaseObject
{
	// this class is used to calculate the physics of an object
	protected:
	// ================================ ATTRIBUTES
		bool _isDynamic; // whether this object should calculate physics
		bool _isCollide; // whether other objects can collide with this object // add a collision mask ???

		Vector2 _vel;
		Vector2 _acc;

		float _mass;
		float _fric;
		float _elas; // TODO : implement me

	// ================================ CORE METHODS
		void collideWith( BaseObject *other );

		void onAdd() override;
		void onCpy(  const PhysicObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		PhysicObject();
		PhysicObject( const PhysicObject &obj );
		PhysicObject &operator=( const PhysicObject &obj );
		~PhysicObject();

	// ================================ ACCESSORS
		bool getIsDynamic() const;	bool setIsDynamic( bool isDynamic );
		bool getIsCollide() const;	bool setIsCollide( bool isCollide );

		Vector2 getPosition() const;			Vector2 setPosition( const Vector2 &pos );			Vector2 changePosition( const Vector2 &delta );
		Vector2 getVelocity() const;			Vector2 setVelocity( const Vector2 &vel );			Vector2 changeVelocity( const Vector2 &delta );
		Vector2 getAcceleration() const;	Vector2 setAcceleration( const Vector2 &acc );	Vector2 changeAcceleration( const Vector2 &delta );
		Vector2 getForce() const;

		Vector2 getRelPosition( const PhysicObject &Obj ) const;
		Vector2 getRelVelocity( const PhysicObject &Obj ) const;
		Vector2 getRelAcceleration( const PhysicObject &Obj ) const;
		Vector2 getRelForce( const PhysicObject &Obj ) const;

		float getMass() const;				float setMass( float mass );							float changeMass( float mass );
		float getFriction() const;		float setFriction( float friction );			float changeFriction( float friction );
		float getElasticity() const;	float setElasticity( float elasticity );	float changeElasticity( float elasticity );

		float getDensity() const;
		float getInertia() const;

		Vector2 applyForce( const Vector2 &force );
		Vector2 applyBreak( const Vector2 &breakForce ); // applies a force in the opposite direction of the object's velocity

	// ================================ OPERATORS

	// ================================ METHODS
		void onPhysicTick() override; // ENTRYPOINT : calculates the object's physics

};

#endif // PHYSICOBJECT_HPP