#ifndef RENDEROBJECT_HPP
# define RENDEROBJECT_HPP

# include <raylib.h>
# include "./ShapeObject.hpp"

class RenderObject :
	virtual public BaseObject,
	virtual public ShapeObject
{
	// this class is used to render an object
	protected:
	// ================================ ATTRIBUTES
		bool  _isVisible; // whether this object should be rendered
		Color _color;

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy(  const RenderObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		RenderObject();
		RenderObject( const RenderObject &obj );
		RenderObject &operator=( const RenderObject &obj );
		virtual ~RenderObject();

	// ================================ ACCESSORS / MUTATORS
		bool getIsVisible() const;   void setIsVisible( bool _isVisible );
		Color getColor() const;      void setColor( Color color );

	// ================================ TICK METHODS
		bool renderSelf();
		void onRenderTick() override; // ENTRYPOINT : (re)renders the object
};

#endif // RENDEROBJECT_HPP