#ifndef RENDEROBJECT_HPP
# define RENDEROBJECT_HPP

# include "./BaseObject.hpp"

class RenderObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		bool isVisible; // whether this object should be rendered

	// ================================ CORE METHODS
		void onRefresh(); // ENTRYPOINT : (re)renders the object

		virtual void onAdd();
		virtual void onCpy( const RenderObject &obj );
		virtual void onDel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		RenderObject();
		RenderObject( const RenderObject &obj );
		RenderObject &operator=( const RenderObject &obj );
		~RenderObject();

	// ================================ ACCESSORS
		bool getIsVisible() const;			void setIsVisible( bool visible );

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // RENDEROBJECT_HPP