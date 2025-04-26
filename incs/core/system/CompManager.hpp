#ifndef COMP_MANAGER_HPP
# define COMP_MANAGER_HPP

# include <raylib.h>
# include "../../base.hpp"
# include "../component/BaseComp.hpp"

// ================================ FORWARD DECLARATIONS
class GameEntity;
typedef vector< GameEntity > NttVec;

// =============================== CORE

typedef struct
{
	GameEntity* Ntt;
	CompArr     Comps;
}             ECpair;

typedef std::unordered_map< NttID_t, ECpair > ECmap_t;


class CompManager
{
	private:
	// ================================ ATTRIBUTES
		ECmap_t _NttMap;
		NttID_t _maxID;

	// ================================ CORE METHODS
		inline NttID_t getMaxID() const { return _maxID; }
		inline NttID_t getNewID()
		{
			qlog( "getNewID : assigning new ID: " + std::to_string( _maxID + 1 ), INFO, 0 );
			return ++_maxID;
		}

		void clearAllPairs();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline CompManager(){ _maxID = 0; };
		inline ~CompManager(){ clearAllPairs(); };

	// ================================ ACCESSORS / MUTATORS

	// ================ CHECK METHODS
		// NOTE : these log errors if the check fails ( returns false )
		bool isUsedNtt( GameEntity *Ntt ) const; // NOTE : Checks if the entity is is in the map
		bool isFreeNtt( GameEntity *Ntt ) const; // NOTE : Checks if the entity is is not in the map

		TTC bool isUsedComp( CompT *comp ) const; // NOTE : Checks if the component is in the map
		TTC bool isFreeComp( CompT *comp ) const; // NOTE : Checks if the component is not in the map

	// ================ ENTITY METHODS
		NttID_t    getEntityCount();
		GameEntity *getEntity( NttID_t id );

		bool hasEntity( NttID_t id ) const;
		bool addEntity( NttID_t id ); // NOTE : should only be called by GameEntity's AddToManager()
		bool rmvEntity( NttID_t id );
		bool delEntity( NttID_t id ); // NOTE : also frees the memory of the entity

		bool hasThatEntity( GameEntity *Ntt ) const;
		bool addThatEntity( GameEntity *Ntt );
		bool rmvThatEntity( GameEntity *Ntt );
		bool delThatEntity( GameEntity *Ntt ); // NOTE : also frees the memory of the entity

		// NOTE : ( add if not there ) + copy entity and its components
		bool cpyEntityOver( NttID_t     src, NttID_t     dst );
		bool cpyEntityOver( GameEntity *src, NttID_t     dst );
		bool cpyEntityOver( NttID_t     src, GameEntity *dst );
		bool cpyEntityOver( GameEntity *src, GameEntity *dst );

		// NOTE : add + copy entity and its components
		bool dupEntity( NttID_t src );
		bool dupEntity( GameEntity *src );

	// ================ COMPONENT METHODS
		CompArr *getNttCompArr( GameEntity *Ntt );
		CompArr *getNttCompArr( NttID_t id );

		CompC_t    getCompCount( NttID_t id ) const;
		TTC CompT *getComponent( NttID_t id );
		TTC CompT *cpyComponent( NttID_t id ) const;

		TTC bool hasComponent( NttID_t id ) const;
		TTC bool addComponent( NttID_t id );
		TTC bool rmvComponent( NttID_t id );
		TTC bool delComponent( NttID_t id ); // NOTE : also frees the memory of the component

		TTC bool hasThatComponent( NttID_t id, CompT *component ) const;
		TTC bool addThatComponent( NttID_t id, CompT *component );
		TTC bool rmvThatComponent( NttID_t id, CompT *component );
		TTC bool delThatComponent( NttID_t id, CompT *component ); // NOTE : also frees the memory of the component

		//TTC CompT &getNewComponentByType( NttID_t id, comp_e compType );

	// ================================ STATIC METHODS

		// NOTE : these log errors if the check fails ( returns false )
		static bool isValidID( NttID_t id ); //        NOTE : Checks if the ID is above the current ID use range ( _maxID )
		static bool isValidType( comp_e type ); //     NOTE : Checks if the type is valid ( 0 <= type < COMP_TYPE_COUN
		static bool isValidNtt( GameEntity *Ntt ); //  NOTE : Checks if the entity is valid ( ID != 0 )
		TTC static bool isValidComp( CompT *comp ); // NOTE : Checks if the component is valid ( ID != 0 )

	// ================ FACTORY METHODS

		TTC static CompT  *CompFactory(); //                   NOTE : allocs new component
		TTC static CompT  *CompFactory( NttID_t id ); //       NOTE : allocs new component with given ID
		TTC static CompT  *CompFactory( CompT *component ); // NOTE : allocs + copies component

		static GameEntity *NttFactory(); //                  NOTE : allocs new entity ( ID = 0 )
		static GameEntity *NttFactory( NttID_t id ); //      NOTE : allocs new entity with given ID
		static GameEntity *NttFactory( GameEntity *Ntt ); // NOTE : allocs + copies entity

	// ================================ UPDATE METHODS
		void updateAllEntities(); //   NOTE : calls the onTick() method of all components in the map ( one entity at a time )
		void updateAllComponents(); // NOTE : calls the onTick() method of all components in the map ( each component type at a time)

		void updateComponentByType( comp_e compType ); // NOTE : calls the onTick() method of all components of the given type in the map
};

# include "./CompManagerT.hpp"

#endif // COMP_MANAGER_HPP

