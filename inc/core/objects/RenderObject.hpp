#ifndef RENDEROBJECT_HPP
# define RENDEROBJECT_HPP

# include "./BaseObject.hpp"

class RenderObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES

	// ================================ CORE METHODS
		void onAdd();
		void onCpy();
		void ondel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		RenderObject();
		RenderObject( const RenderObject &obj );
		RenderObject &operator=( const RenderObject &obj );
		~RenderObject();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // RENDEROBJECT_HPP