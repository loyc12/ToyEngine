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

	E_CNTRLR, // INPUTS + SCRIPT
	E_SPRITE, // PHYSIC + RENDER

	E_OBJ2D,  // CNTRLR + SPRITE
	//E_OBJ3D,

	E_MENU,   // CNTRLR + RENDER

} objectType_e;


class BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		objectType_e _type;
		static uint _id;

	// ================================ CORE METHODS
		void onAdd();
		void onCpy();
		void ondel();

		bool addToRegister();
		bool delFromRegister();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		BaseObject();
		BaseObject( const BaseObject &obj );
		BaseObject &operator=( const BaseObject &obj );
		~BaseObject();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS



};

#endif // BASEOBJECT_HPP

