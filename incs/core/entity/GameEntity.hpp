#ifndef GAME_ENTITY_HPP
# define GAME_ENTITY_HPP

# include <raylib.h>
# include "../component/BaseComp.hpp"
# include "../../base.hpp"

// NOTE : Entities, like Components, are created and destroyed via the CompManager
// NOTE : However, creating an entity anywhere adds calls the apropriate CompManager functions and adds it to the map
class GameEntity
{
	private:
	// ================================ ATTRIBUTES
		NttID_t _id; // NOTE : if the ID is 0, the entity is not supposed to be in CompManager's map

	// ================================ CORE METHODS
		// NOTE : mutex these is multithreading is implemented
		bool addToManager(); //   NOTE : automatically adds this instance to CompManager's map
		bool delFromManager(); // NOTE : automatically removes this instance to CompManager's map
		void onCpy( const GameEntity &rhs );

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		~GameEntity();

		GameEntity();
		GameEntity( bool addEntityToManager, NttID_t id = 0); // NOTE : should only be called by CompManager

		GameEntity( const GameEntity &rhs );
		GameEntity &operator=( const GameEntity &rhs );

	// ================================ ACCESSORS / MUTATORS
		NttID_t getID() const;
		bool    setID( NttID_t id ); // NOTE : should only be called by CompManager
		bool    delID(); //             NOTE : should only be called by CompManager

		CompC_t  getCompCount(); // redirects to CompManager method
		CompArr &getCompArr(); //   redirects to CompManager method

		TTC CompT &getComponent(); // redirects to CompManager method
		TTC CompT  cpyComponent(); // redirects to CompManager method
		TTC CompT *dupComponent(); // redirects to CompManager method

		TTC bool hasComponent() const; // redirects to CompManager method
		TTC bool addComponent(); //       redirects to CompManager method
		TTC bool delComponent(); //       redirects to CompManager method

		TTC bool hasThatComponent( CompT &component ) const; // redirects to CompManager method
		TTC bool addThatComponent( CompT *component ); //       redirects to CompManager method
		TTC bool delThatComponent( CompT &component ); //       redirects to CompManager method

};
typedef vector< GameEntity > NttVec;

#endif // GAME_ENTITY_HPP

