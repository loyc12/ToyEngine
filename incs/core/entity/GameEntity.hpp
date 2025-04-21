#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <raylib.h>
# include "../component/BaseComp.hpp"
# include "../../base.hpp"

typedef uint32_t NttID_t;

// NOTE : Entities, like Components, are created and destroyed via the CompManager
// NOTE : However, creating an entity anywhere adds calls the apropriate CompManager functions and adds it to the map
class GameEntity
{
	private:
	// ================================ ATTRIBUTES
		NttID_t _id;

	// ================================ CORE METHODS
		// NOTE : mutex these is multithreading is implemented
		bool addToManager(); //   NOTE : automatically adds this instance to the CompManager's map
		bool delFromManager(); // NOTE : automatically removes this instance to the CompManager's map
		void onCpy( const GameEntity &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline GameEntity(){ addToManager(); }
		inline GameEntity( bool addEntity, NttID_t id = 0) : _id( id ){ if( addEntity ) addToManager(); } // NOTE : should only be called by CompManager
		inline GameEntity( const GameEntity &rhs ){ addToManager(); onCpy( rhs ); }
		inline GameEntity &operator=( const GameEntity &rhs ) { onCpy( rhs ); return *this; }
		inline ~GameEntity(){ delFromManager(); }

	// ================================ ACCESSORS / MUTATORS
		NttID_t   getID() const;
		bool      setID( NttID_t id ); // NOTE : should only be called by CompManager

		CompC_t   getCompCount(); //                              redirects to CompManager method
		bool      hasComponent( comp_e component_type ) const; // redirects to CompManager method
		bool      addComponent( comp_e component_type ); //       redirects to CompManager method
		bool      delComponent( comp_e component_type ); //       redirects to CompManager method
		BaseComp &getComponent( comp_e component_type ); //       redirects to CompManager method
		CompArr  &getCompArr(); //                                redirects to CompManager method
};
typedef vector< GameEntity > NttVec;

#endif // GAME_ENTITY_HPP

