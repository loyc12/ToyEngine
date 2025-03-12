#ifndef OBJECT2D_HPP
# define OBJECT2D_HPP

# include "./InputsObject.hpp"
# include "./ScriptObject.hpp"
# include "./PhysicObject.hpp"
# include "./RenderObject.hpp"

class Object2D : public InputsObject, public ScriptObject, public PhysicObject, public RenderObject
{
	protected:
	// ================================ ATTRIBUTES

	// ================================ CORE METHODS
		void onAdd();
		void onCpy();
		void ondel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		Object2D();
		Object2D( const Object2D &obj );
		Object2D &operator=( const Object2D &obj );
		~Object2D();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // OBJECT2D_HPP