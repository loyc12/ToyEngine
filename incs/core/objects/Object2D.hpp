#ifndef OBJECT2D_HPP
# define OBJECT2D_HPP

# include <raylib.h>
# include "./ScriptObject.hpp"

class Object2D :
	virtual public BaseObject,
	virtual public PhysicObject,
	virtual public RenderObject,
	virtual public ScriptObject
{
	protected:
	// ================================ ATTRIBUTES
		// bool _isActive;		// whether this object should run its scripts
		// bool _isDynamic;		// whether this object should calculate physics
		// bool _isCollide;		// whether other objects can collide with this object
		// bool _isVisible;		// whether this object should be rendered

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy(  const Object2D &obj );
		void onDel() override;

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

// ================================== OBJECTS FACTORY

void GenerateObject2D( shape_e shape, Color color, Vector2 size, Vector2 pos = { 0, 0 }, bool isActive = true, bool isDynamic = true, bool isCollide = true, bool isVisible = true );

#endif // OBJECT2D_HPP