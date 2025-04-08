#ifndef BASEOBJECT_HPP
# define BASEOBJECT_HPP

# include <raylib.h>
# include "../../base.hpp"

class BaseObject;

typedef enum : byte_t
{
	E_BASEOBJ = 0,

	E_SHAPE,
	E_PHYSIC,
	E_RENDER,
	E_SCRIPT,

	//E_CNTRLR, // INPUTS + SCRIPT ?
	//E_SPRITE, // PHYSIC + RENDER ?

	E_OBJ2D,  // CNTRLR + SPRITE
	//E_OBJ3D,

	//E_MENU,   // CNTRLR + RENDER ???

} objectType_e;

typedef vector< BaseObject * > objVect_t; //  TODO : move me

class BaseObject
{
	private:
	// ================================ ATTRIBUTES
		objID_t      _id;
		objectType_e _type;

	// ================================ CORE METHODS
		bool delID();

		bool addToEngine();
		bool delFromEngine();

	protected:

		virtual void onAdd();
		void         onCpy( const BaseObject &obj );
		virtual void onDel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		BaseObject();
		BaseObject( objectType_e type );

		BaseObject( const BaseObject &obj );
		BaseObject &operator=( const BaseObject &obj );
		virtual ~BaseObject();

	// ================================ TICK METHODS
		virtual void onShapeTick();  // (re)calculates the object's shape
		virtual void onPhysicTick(); // (re)calculates the object's physics
		virtual void onRenderTick(); // (re)renders the object
		virtual void onScriptTick(); // (re)runs the object's scripts

	// ================================ ACCESSORS
		uint getID() const;
		objectType_e getType() const;

	private:
	// ================================ MUTATORS
		void setID( objID_t id );
		void setType( objectType_e type );
};

#endif // BASEOBJECT_HPP

