#ifndef SHAPEOBJECT_HPP
# define SHAPEOBJECT_HPP

# include <raylib.h>
# include "./BaseObject.hpp"

class ShapeObject :
	virtual public BaseObject
{
	// this class is used to calculate the physics of an object
	protected:
	// ================================ ATTRIBUTES
		bool _isTangible; // whether this object has a shape

		Shape2 _shape; // the pos and shape of the object

	// ================================ CORE METHODS

		void onAdd() override;
		void onCpy(  const ShapeObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		ShapeObject();
		ShapeObject( const ShapeObject &obj );
		ShapeObject &operator=( const ShapeObject &obj );
		virtual ~ShapeObject();

	// ================================ ACCESSORS
		inline bool getIsTangible()      const { return _isTangible; }
		inline const Shape2 &getShape()  const { return _shape; }
		inline sh2_type_e getShapeType() const { return _shape.getType(); }

		inline Vector2 getPosition() const { return _shape.getCenter(); }
		inline Vector2 getCenter()   const { return _shape.getCenter(); }
		inline Vector2 getScale()    const { return _shape.getScales(); }
		inline float   getAngle()    const { return _shape.getAngle(); }

		inline Vector2 getRelPosition( const ShapeObject &Obj ) const { return getRelPosition( Obj.getCenter() ); }
		inline Vector2 getRelScale(    const ShapeObject &Obj ) const { return getRelScale(    Obj.getScale() ); }
		inline float   getRelAngle(    const ShapeObject &Obj ) const { return getRelAngle(  Obj.getAngle() ); }

		Vector2 getRelPosition( Vector2 pos ) const;
		Vector2 getRelScale(    Vector2 scl ) const;
		float   getRelAngle(    float angle ) const;

		inline float getArea()  const { return _shape.getArea(); }
		inline float getPerim() const { return _shape.getPerim(); }

		inline float getMinRadius() const { return _shape.getMinRadius(); }
		inline float getMaxRadius() const { return _shape.getMaxRadius(); }
		inline float getAvgRadius() const { return _shape.getAvgRadius(); }

		// ================================ MUTATORS
		inline bool setIsTangible( bool isTangible ){ _isTangible = isTangible; return _isTangible; }
		inline void setShape( const Shape2 &shape ){  _shape = shape; }

		Vector2 setPosition(  const Vector2 &pos );
		Vector2 movePosition( const Vector2 &delta );
		//Vector2 changePosition( const Vector2 &pos );

		Vector2 setScale(    const Vector2 &scl );
		Vector2 moveScale(   const Vector2 &delta );
		Vector2 changeScale( const Vector2 &scl );

		float   setAngle(    float angle );
		float   moveAngle(   float delta );
		//float   changeAngle( float angle );

		// ================================ TICK METHODS
		void onShapeTick() override; // ENTRYPOINT : (re)calculates the object's shape

	};

#endif // SHAPEOBJECT_HPP