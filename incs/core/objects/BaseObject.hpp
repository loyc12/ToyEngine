#ifndef BASEOBJECT_HPP
# define BASEOBJECT_HPP

# include "../../base.hpp"

typedef enum : byte_t
{
	E_BASEOBJ = 0,

	E_INPUTS,
	E_SCRIPT,
	E_PHYSIC,
	E_RENDER,

	E_CNTRLR, // INPUTS + SCRIPT ?
	E_SPRITE, // PHYSIC + RENDER ?

	E_OBJ2D,  // CNTRLR + SPRITE
	//E_OBJ3D,

	E_MENU,   // CNTRLR + RENDER ???

} objectType_e;


class BaseObject
{
	private:
	// ================================ MEMORY METHODS
		bool setID( objID_t id );
		bool delID();

		bool addToRegister();
		bool delFromRegister();

		protected:
		// ================================ ATTRIBUTES
		objID_t _id;
		objectType_e _type;
		Vector2 _position;

		virtual void onAdd();
		void onCpy( const BaseObject &obj );
		virtual void onDel();

	// ================================ CORE METHODS

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		BaseObject();
		BaseObject( objectType_e type );

		BaseObject( const BaseObject &obj );
		BaseObject &operator=( const BaseObject &obj );
		virtual ~BaseObject();

	// ================================ ACCESSORS
		objectType_e getType() const;
		uint getID() const;

	// ================================ OPERATORS

	// ================================ METHODS
	virtual void onScriptTick(); // runs the object's scripts
	virtual void onPhysicTick(); // calculates the object's physics
	virtual void onRenderTick(); // (re)renders the object

	Vector2 getPosition() const;									Vector2 changePosition( const Vector2 &delta );
	Vector2 setPosition( const Vector2 &pos );		Vector2 getRelPosition( const BaseObject &Obj ) const;


};

#endif // BASEOBJECT_HPP

