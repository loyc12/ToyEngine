#ifndef OBJECT2D_HPP
# define OBJECT2D_HPP

# include <raylib.h>
# include "./ScriptObject.hpp"

class Object2D :
	virtual public BaseObject,
	virtual public ShapeObject,
	virtual public RenderObject,
	virtual public PhysicObject,
	virtual public ScriptObject
{
	protected:
	// ================================ ATTRIBUTES
		// bool _isTangible; // whether this object has a shape
		// bool _isVisible;  // whether this object should be rendered
		// bool _isDynamic;  // whether this object should calculate physics
		// bool _isCollide;  // whether other objects can collide with this object
		// bool _isActive;   // whether this object should run its scripts

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


	// ================================ TICK METHODS
		//void onShapeTick()  override; // (re)calculates the object's shape
		//void onRenderTick() override; // (re)renders the object
		//void onPhysicTick() override; // (re)calculates the object's physics
		//void onScriptTick() override; // (re)runs the object's scripts
};

// ================================== OBJECTS FACTORY

void GenerateObject2D( Shape2 shape, Color color, bool isTangible = true, bool isDynamic = true, bool isCollide = true, bool isVisible = true, bool isActive = true );

#endif // OBJECT2D_HPP