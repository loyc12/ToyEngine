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
		bool addToRegister();
		bool delFromRegister();

		protected:
		// ================================ ATTRIBUTES
		objectType_e _type;
		uint _id;

		virtual void onAdd() = 0;
		void onCpy( const BaseObject &obj );
		virtual void onDel() = 0;;

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



};

#endif // BASEOBJECT_HPP

