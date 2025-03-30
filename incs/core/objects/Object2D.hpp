#ifndef OBJECT2D_HPP
# define OBJECT2D_HPP

# include "./BaseObject.hpp"
# include "./ScriptObject.hpp"
# include "./PhysicObject.hpp"
# include "./RenderObject.hpp"

class Object2D :
	virtual public BaseObject,
	virtual public ScriptObject,
	virtual public PhysicObject,
	virtual public RenderObject
{
	protected:
	// ================================ ATTRIBUTES
		// bool isControlled;	// whether this object should check for input
		// bool isActive;			// whether this object should run its scripts
		// bool isDynamic;		// whether this object should calculate physics
		// bool isVisible;		// whether this object should be rendered

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy( const Object2D &obj );
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
		//virtual void onScriptTick() override; // ENTRYPOINT : runs the object's scripts
		//virtual void onPhysicTick() override; // ENTRYPOINT : calculates the object's physics
		//virtual void onRenderTick() override; // ENTRYPOINT : (re)renders the object
};

#endif // OBJECT2D_HPP