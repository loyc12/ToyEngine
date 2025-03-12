#ifndef PHYSICOBJECT_HPP
# define PHYSICOBJECT_HPP

# include "./BaseObject.hpp"

class PhysicObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		bool isDynamic; // whether this object should calculate physics
		bool isCollide; // whether other objects can collide with this object // add a collision mask ???

		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;

	// ================================ CORE METHODS
		void onTick(); // ENTRYPOINT : calculates the object's physics
		void collideWith( BaseObject *other );

		virtual void onAdd();
		virtual void onCpy( const PhysicObject &obj );
		virtual void onDel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		PhysicObject();
		PhysicObject( const PhysicObject &obj );
		PhysicObject &operator=( const PhysicObject &obj );
		~PhysicObject();

	// ================================ ACCESSORS
	bool getIsDynamic() const;						void setIsDynamic( bool dynamic );
	bool getIsCollide() const;						void setIsCollide( bool collide );
	Vector2 getPosition() const;					void setPosition( const Vector2 &pos );
	Vector2 getVelocity() const;					void setVelocity( const Vector2 &vel );
	Vector2 getAcceleration() const;			void setAcceleration( const Vector2 &acc );

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // PHYSICOBJECT_HPP