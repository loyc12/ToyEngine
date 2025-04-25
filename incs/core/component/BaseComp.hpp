#ifndef BASE_COMP_HPP
# define BASE_COMP_HPP

# include <raylib.h>
# include "../../base.hpp"

typedef byte_t CompC_t;
typedef enum : CompC_t
{
	COMP_SCRIPT = 0,
	COMP_PHYSIC,
	COMP_MOVEMENT,
	COMP_POSITION,
	COMP_COLLIDE,
	COMP_RENDER,
	COMP_TYPE_COUNT,
	COMP_BASE_TYPE = 255, // NOTE : should never be used for actual Components

} comp_e;

typedef uint32_t NttID_t;

// NOTE : Components, like Entities, are created and destroyed via the Component Manager
class BaseComp
{
	protected:
	// ================================ ATTRIBUTES
		NttID_t _id; //  NOTE : if the ID is 0, the component is not supposed to be in CompManager's map
		bool _active; // NOTE : mutex this if we ever multithread onTick() calls

		inline virtual void onAdd(){} //                                              NOTE : ovveride this in derived classes
		inline virtual void onDel(){} //                                              NOTE : ovveride this in derived classes
		inline virtual void onCpy( const BaseComp &rhs ){ _active = rhs._active; } // NOTE : ovveride this in derived classes

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline virtual ~BaseComp(){ onDel(); };

		inline BaseComp() : _active( true ){ onAdd(); }
		inline BaseComp( bool isActive, NttID_t id = 0) : _id( id ), _active( isActive ){ onAdd(); }

		inline BaseComp( const BaseComp &rhs ){ *this = rhs; }
		inline BaseComp &operator=( const BaseComp &rhs ){ onCpy( rhs ); return *this; }

	// ================================ ACCESSORS / MUTATORS
		inline NttID_t getID() const { return _id; } //                 NOTE : should only be called by CompManager
		inline bool    delID(){             _id = 0;  return true; } // NOTE : should only be called by CompManager
		inline bool    setID( NttID_t id ){ _id = id; return true; } // NOTE : should only be called by CompManager

	  inline static comp_e getType(){ return COMP_BASE_TYPE; } //     NOTE : ovveride this in derived classes

		inline bool isActive(){ return _active; }
		inline bool isActive( bool activate ){ _active = activate; return _active; }

	// ================================ TICK METHODS
	// NOTE : should return false if the component did not tick ( for example, if the "_active" flag is set to false )
	// NOTE : use CRTP if onTick() becomes a performance bottleneck
	// NOTE : should only be called by CompManager
	inline virtual bool onTick(){ return _active; } // NOTE : ovveride this in derived classes
};

typedef array< BaseComp*, COMP_TYPE_COUNT > CompArr; // NOTE : Components should be stored

// ================================ TEMPLATES

#include <concepts>
#include <type_traits>

// NOTE : this is a concept to check if a type is derived from BaseComp
template <typename T>
concept IsBaseComp = std::is_base_of<BaseComp, T>::value;

// NOTE : this is shorthand to define a template that requires the type to be derived from BaseComp
# define TTC template <typename CompT> requires IsBaseComp< CompT >



#endif // BASE_COMP_HPP