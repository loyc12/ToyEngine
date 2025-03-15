#ifndef RENDEROBJECT_HPP
# define RENDEROBJECT_HPP

# include "./BaseObject.hpp"

class RenderObject : virtual public BaseObject
{
	protected:
	// ================================ ATTRIBUTES
		bool isVisible; // whether this object should be rendered

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy( const RenderObject &obj );
		void onDel() override;

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		RenderObject();
		RenderObject( objID_t id );
		RenderObject( const RenderObject &obj );
		RenderObject &operator=( const RenderObject &obj );
		~RenderObject();

	// ================================ ACCESSORS
		bool getIsVisible() const;			void setIsVisible( bool visible );

	// ================================ OPERATORS

	// ================================ METHODS
		void onRefresh(); // ENTRYPOINT : (re)renders the object
};

#endif // RENDEROBJECT_HPP