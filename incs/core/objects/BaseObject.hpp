#ifndef BASEOBJECT_HPP
# define BASEOBJECT_HPP

# include <raylib.h>
# include "../../base.hpp"

class BaseObject;

typedef enum : byte_t
{
	E_BASEOBJ = 0,

	E_INPUTS,
	E_SCRIPT,
	E_PHYSIC,
	E_RENDER,

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
	// ================================ MEMORY METHODS
		bool setID( objID_t id );
		bool delID();

		bool addToEngine();
		bool delFromEngine();

		protected:
		// ================================ ATTRIBUTES
		objID_t      _id;
		objectType_e _type;

		Vector2 _pos;
		Vector2 _size; // half width and half height
		bool    _isSpherical;

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
		virtual void onScriptTick(); // runs the object's scripts
		virtual void onPhysicTick(); // calculates the object's physics
		virtual void onRenderTick(); // (re)renders the object

	// ================================ OPERATORS

	// ================================ ACCESSORS
		objectType_e getType() const;
		uint getID() const;

		// TODO : MOVE THESE BELLOW TO EITHER PHYSICOBJECT OR SHAPE2

		bool isSpherical() const;			bool setSpherical( bool isSpherical );

	  Vector2 getTop() const;				Vector2 getBot() const;
		Vector2 getLeft() const;			Vector2 getRight() const;

		inline Vector2 getCenter() const { return BaseObject::getPosition(); }

		Vector2 getTopLeft() const;		Vector2 getTopRight() const;
		Vector2 getBotLeft() const;		Vector2 getBotRight() const;

		Vector2 getPosition() const;									Vector2 movePosition(   const Vector2 &delta );
		Vector2 setPosition(  const Vector2 &pos );		Vector2 getRelPosition( const BaseObject &Obj ) const;

		Vector2 getSize() const;											Vector2 moveSize(   const Vector2 &delta );
		Vector2 setSize(  const Vector2 &size );			Vector2 getRelSize( const BaseObject &Obj ) const;

		// ================================ DIMENSIONS GETTERS

		float getWidth()  const { return _size.x * 2; }
		float getHeight() const { return _size.y * 2 ; }

		float getPerim()  const;
		float getArea()   const;

		float getMinSide() const { return ( _size.x < _size.y ? _size.x : _size.y ) * 2; }
		float getMaxSide() const { return ( _size.x > _size.y ? _size.x : _size.y ) * 2; }
		float getAvgSide() const { return ( _size.x + _size.y ); }

		float getMinRadius() const;
		float getMaxRadius() const;
		float getAvgRadius() const;

		float getHalfDiago() const; // returns the distance between the center and the +x,+y corner
		float getFullDiago() const; // returns the distance between the -x,-y corner and the +x,+y corner


};

#endif // BASEOBJECT_HPP

