#ifndef RENDEROBJECT_HPP
# define RENDEROBJECT_HPP

# include <raylib.h>
# include "./BaseObject.hpp"

typedef enum shape_e
{
	SHAPE_CIRCLE,
	SHAPE_RECT,
	SHAPE_LINE,
	SHAPE_BOX,
} shape_e;


class RenderObject : virtual public BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		bool _isVisible; // whether this object should be rendered
		shape_e _shape;
		Color   _color;

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy(  const RenderObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		RenderObject();
		RenderObject( const RenderObject &obj );
		RenderObject &operator=( const RenderObject &obj );
		~RenderObject();

	// ================================ ACCESSORS
		bool getIsVisible() const;		void setIsVisible( bool _isVisible );
		shape_e getShape() const;			void setShape( shape_e shape );
		Color getColor() const;				void setColor( Color color );

	// ================================ OPERATORS

	// ================================ METHODS
		void onRenderTick() override; // ENTRYPOINT : (re)renders the object
};

#endif // RENDEROBJECT_HPP