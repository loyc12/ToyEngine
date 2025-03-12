#ifndef PHYSICOBJECT_HPP
# define PHYSICOBJECT_HPP

# include "./BaseObject.hpp"

class PhysicObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES

	// ================================ CORE METHODS
		void onAdd();
		void onCpy();
		void ondel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		PhysicObject();
		PhysicObject( const PhysicObject &obj );
		PhysicObject &operator=( const PhysicObject &obj );
		~PhysicObject();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // PHYSICOBJECT_HPP