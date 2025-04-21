#ifndef BASE_COMP_HPP
# define BASE_COMP_HPP

# include <raylib.h>
# include "../../base.hpp"

typedef byte_t CompC_t;
typedef enum : CompC_t
{
	COMP_POSITION = 0,
	COMP_MOVEMENT,
	COMP_COLLIDE,
	COMP_PHYSIC,
	COMP_RENDER,
	COMP_SCRIPT,
	COMP_TYPE_COUNT,
	COMP_BASE_TYPE = 255, // NOTE : should never be used for actual Components

} comp_e;

// NOTE : Components, like Entities, are created and destroyed via the Component Manager
class BaseComp
{
	protected:
	// ================================ ATTRIBUTES
		bool _active; // NOTE : mutex this if we ever multithread onTick() calls

		inline virtual void onAdd(){} //                                              NOTE : ovveride this in derived classes
		inline virtual void onDel(){} //                                              NOTE : ovveride this in derived classes
		inline virtual void onCpy( const BaseComp &rhs ){ _active = rhs._active; } // NOTE : ovveride this in derived classes

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline BaseComp( ){ _active = true; onAdd(); }
		inline virtual ~BaseComp(){         onDel(); };

		inline BaseComp( bool isActive ) : _active( isActive ){ onAdd(); }
		inline BaseComp( const BaseComp &rhs ){   onAdd(); onCpy( rhs ); }
		inline BaseComp &operator=( const BaseComp &rhs ){ onCpy( rhs ); return *this; }

	// ================================ ACCESSORS / MUTATORS
	  inline virtual comp_e getStaticType() const { return COMP_BASE_TYPE; } // NOTE : ovveride this in derived classes
		inline comp_e         getType() const {       return getStaticType(); }

		inline bool isActive(){ return _active; }
		inline bool isActive( bool activate ){ _active = activate; return _active; }

	// ================================ TICK METHODS
	// NOTE : should return false if the component did not tick ( for example, if the "_active" flag is set to false )
	// NOTE : use CRTP if onTick() becomes a performance bottleneck
	// NOTE : should only be called by CompManager
	inline virtual bool onTick(){ return false; }
};

typedef array< BaseComp*, COMP_TYPE_COUNT > CompArr; // NOTE : Components should be stored

# define TTC template <typename CompT> // NOTE : shorthand for template usage

#endif // BASE_COMP_HPP