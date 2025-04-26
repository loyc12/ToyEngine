#ifndef COMP_POS_HPP
# define COMP_POS_HPP

# include <raylib.h>
# include "../component/BaseComp.hpp"

class CompPos : public BaseComp
{
	protected:
	// ================================ ATTRIBUTES
		Vector2 _pos; // NOTE : position of the component

	// ================================ CORE METHODS
		inline virtual void onAdd() override {} // NOTE : No additional behavior for CompPos
		inline virtual void onDel() override {} // NOTE : No additional behavior for CompPos
		//virtual void onCpy( const BaseComp &rhs );
		virtual void onCpy( const CompPos  &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		virtual ~CompPos();

		CompPos();
		CompPos( bool isActive, NttID_t id = 0, Vector2 pos = { 0, 0 });

		//CompPos( const BaseComp &rhs );
		CompPos( const CompPos  &rhs );

		//CompPos &operator=( const BaseComp &rhs );
		CompPos &operator=( const CompPos  &rhs );

	// ================================ ACCESSORS / MUTATORS
		inline Vector2 getPos() const { return _pos; }

		inline void setPos( Vector2 pos ){ _pos = pos; }
		inline void setPos( float x, float y ){ _pos.x = x; _pos.y = y; }

		inline void changePos( Vector2 pos ){ _pos.x += pos.x; _pos.y += pos.y; }
		inline void changePos( float x, float y ){ _pos.x += x; _pos.y += y; }

		inline static comp_e getType(){ return COMP_POSITION; }

	// ================================ TICK METHODS
		inline virtual bool onTick() override { return _active; } // NOTE : No additional behavior for CompPos
};

#endif // COMP_POS_HPP