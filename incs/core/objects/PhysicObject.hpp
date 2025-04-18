#ifndef PHYSICOBJECT_HPP
# define PHYSICOBJECT_HPP

# include <raylib.h>
# include "./RenderObject.hpp"

class PhysicObject :
	virtual public BaseObject,
	virtual public ShapeObject,
	virtual public RenderObject
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
		virtual ~PhysicObject();

	// ================================ ACCESSORS / MUTATORS
		bool getIsDynamic() const;	bool setIsDynamic( bool isDynamic );
		bool getIsCollide() const;	bool setIsCollide( bool isCollide );

		Vector2 getVelocity() const;       Vector2 setVelocity( const Vector2 &vel );       Vector2 moveVelocity( const Vector2 &delta );
		Vector2 getAcceleration() const;   Vector2 setAcceleration( const Vector2 &acc );   Vector2 moveAcceleration( const Vector2 &delta );
		Vector2 getForce() const;

		Vector2 getRelVelocity(     const PhysicObject &Obj ) const;
		Vector2 getRelAcceleration( const PhysicObject &Obj ) const;
		Vector2 getRelForce(        const PhysicObject &Obj ) const;

		float getMass() const;         float setMass( float mass );               float moveMass( float delta );
		float getFriction() const;     float setFriction( float friction );       float moveFriction( float delta );
		float getElasticity() const;   float setElasticity( float elasticity );   float moveElasticity( float delta );

		float getDensity() const;   float getInertia() const;

		Vector2 applyForce( const Vector2 &force );
		Vector2 applyBreak( const Vector2 &breakForce ); // applies a force in the opposite direction of the object's velocity

	// ================================ TICK METHODS
		void onPhysicTick() override; // ENTRYPOINT : (re)calculates the object's physics

};

#endif // PHYSICOBJECT_HPP