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

		bool isSpherical() const;			bool setSpherical( bool isSpherical );

	  Vector2 getTop() const;				Vector2 getBot() const;
		Vector2 getLeft() const;			Vector2 getRight() const;
		Vector2 getCenter() const;		// same as getPosition()

		Vector2 getTopLeft() const;		Vector2 getTopRight() const;
		Vector2 getBotLeft() const;		Vector2 getBotRight() const;

		Vector2 getPosition() const;									Vector2 changePosition( const Vector2 &delta );
		Vector2 setPosition( const Vector2 &pos );		Vector2 getRelPosition( const BaseObject &Obj ) const;

		Vector2 getSize() const;											Vector2 changeSize( const Vector2 &delta );
		Vector2 setSize( const Vector2 &size );				Vector2 getRelSize( const BaseObject &Obj ) const;

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


		// TODO : IMPLEMENT US

		// ================================ IS_ON_SHAPE METHODS

		bool isOnShape(  V2Vect_t const &shape ) const; // checks if the given point overlaps the given shape
		bool isOnTri(	   Vector2 const &p1,     Vector2 const &p2, Vector2 const &p3 ) const; // checks if the given point overlaps the given triangle

		bool isOnSquare( Vector2 const &center, float radius ) const; //           checks if the given point overlaps the given square
		bool isOnRect(   Vector2 const &center, float radX, float radY ) const; // checks if the given point overlaps the given rectangle
		bool isOnRect(   Vector2 const &p1,     Vector2 const &p2 ) const; //          checks if the given point overlaps the given rectangle

		bool isOnCircle( Vector2 const &center, float radius ) const; //           checks if the given point overlaps the given circle
		bool isOnCircle( Vector2 const &center, Vector2 const &Edge ) const; //    checks if the given point overlaps the given circle
		bool isOnElipse( Vector2 const &center, float radX, float radY ) const; // checks if the given point overlaps the given elipse

		bool isOnLine(   Vector2 const &p1,     Vector2 const &p2 ) const; //                 checks if the given point overlaps the given line
		bool isOnLine(   Vector2 const &start,  Vector2 const &dir, float dist ) const; // checks if the given point overlaps the given line with a distance

		// ================================ IS_IN_SHAPE METHODS

		bool isInShape(  V2Vect_t const &shape ) const; // checks if the given point is in the given shape
		bool isInTri(	   Vector2 const &p1,     Vector2 const &p2, Vector2 const &p3 ) const; // checks if the given point is in the given triangle

		bool isInSquare( Vector2 const &center, float radius ) const; //           checks if the given point is in the given square
		bool isInRect(   Vector2 const &center, float radX, float radY ) const; // checks if the given point is in the given rectangle
		bool isInRect(   Vector2 const &p1,     Vector2 const &p2 ) const; //          checks if the given point is in the given rectangle

		bool isInCircle( Vector2 const &center, float radius ) const; //           checks if the given point is in the given circle
		bool isInCircle( Vector2 const &center, Vector2 const &Edge ) const; //    checks if the given point is in the given circle
		bool isInElipse( Vector2 const &center, float radX, float radY ) const; // checks if the given point is in the given elipse


		// ================================ OVERLAP METHODS

		bool isInside( const BaseObject &obj ) const; // checks if this object is within the given object
		bool overlaps( const BaseObject &obj ) const; // checks if this object overlaps with the given object
		bool englobes( const BaseObject &obj ) const; // checks if this object contains the given object entirely

		objVect_t getIsInsideVect() const; // returns a list of objects this one is inside of
		objVect_t getOverlapsVect() const; // returns a list of objects that overlap with this one
		objVect_t getEnglobesVect() const; // returns a list of objects that are inside this one

		bool isClosebyPoint(     const Vector2 &point, float dist ) const; // checks if this object is close to the given point ( linear distance )
		bool isClosebyPointCart( const Vector2 &point, float dist ) const; // checks if this object is close to the given point ( cartesian distance )

		bool isCloseby(     const BaseObject &obj, float dist ) const; // checks if this object is close to the given object ( linear distance )
		bool isClosebyCart( const BaseObject &obj, float dist ) const; // checks if this object is close to the given object ( cartesian distance )

};

#endif // BASEOBJECT_HPP

