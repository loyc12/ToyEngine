#ifndef COMP_MANAGER_HPP
# define COMP_MANAGER_HPP

# include <raylib.h>
# include "../component/BaseComp.hpp"
# include "../entity/GameEntity.hpp"
# include "../../base.hpp"

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
		inline NttID_t getNewID() { return     ++_maxID; }

		void clearAllPairs();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		inline CompManager(){ _maxID = 0; };
		inline ~CompManager(){ clearAllPairs(); };

	// ================================ ACCESSORS / MUTATORS

	// ================ CHECK METHODS
		// NOTE : these log errors if the check fails ( returns false )
		bool isUsedID( NttID_t id ) const; // NOTE : Checks if the ID is used in the map
		bool isFreeID( NttID_t id ) const; // NOTE : Checks if the ID is unused in the map

		bool isUsedNtt( GameEntity *Ntt ) const; // NOTE : Checks if the entity is valid ( ID != 0 )
		bool isFreeNtt( GameEntity *Ntt ) const; // NOTE : Checks if the entity is valid ( ID != 0 )

		TTC bool isFreeComp( CompT *comp ) const; // NOTE : Checks if the component is valid ( ID != 0 )
		TTC bool isUsedComp( CompT *comp ) const; // NOTE : Checks if the component is valid ( ID != 0 )

	// ================ ENTITY METHODS
		NttID_t    getEntityCount();
		GameEntity getEntity( NttID_t id );

		bool hasEntity( NttID_t id ) const;
		bool addEntity( NttID_t id ); // NOTE : should only be called by GameEntity's AddToManager()
		bool delEntity( NttID_t id );

		bool hasThatEntity( GameEntity *Ntt ) const;
		bool addThatEntity( GameEntity *Ntt );
		bool delThatEntity( GameEntity *Ntt );

		// NOTE : ( add if not there ) + copy entity and its components
		bool cpyEntityOver( GameEntity &src, GameEntity &dst );
		bool cpyEntityOver( GameEntity &src, NttID_t     dst );
		bool cpyEntityOver( NttID_t     src, GameEntity &dst );
		bool cpyEntityOver( NttID_t     src, NttID_t     dst );

		// NOTE : add + copy entity and its components
		bool dupEntity( GameEntity &src );
		bool dupEntity( NttID_t src );

	// ================ COMPONENT METHODS
		CompArr  &getNttCompArr( GameEntity &Ntt );
		CompArr  &getNttCompArr( NttID_t id );

		CompC_t    getCompCount( NttID_t id ) const;
		TTC CompT &getComponent( NttID_t id );
		TTC CompT  cpyComponent( NttID_t id ) const;

		TTC bool hasComponent( NttID_t id ) const;
		TTC bool addComponent( NttID_t id );
		TTC bool delComponent( NttID_t id );

		TTC bool hasThatComponent( NttID_t id, CompT *component ) const;
		TTC bool addThatComponent( NttID_t id, CompT *component );
		TTC bool delThatComponent( NttID_t id, CompT *component );

		//TTC CompT &getNewComponentByType( NttID_t id, comp_e compType );

	// ================ STATIC METHODS

		// NOTE : these log errors if the check fails ( returns false )
		static bool isValidID( NttID_t id ); //        NOTE : Checks if the ID is above the current ID use range ( _maxID )
		static bool isValidType( comp_e type ); //     NOTE : Checks if the type is valid ( 0 <= type < COMP_TYPE_COUN
		static bool isValidNtt( GameEntity *Ntt ); //  NOTE : Checks if the entity is valid ( ID != 0 )
		TTC static bool isValidComp( CompT *comp ); // NOTE : Checks if the component is valid ( ID != 0 )

	// ================================ FACTORY METHODS
		static GameEntity &GetNullEntity(); //  NOTE : returns a null entity ( ID = 0 )
		static CompArr    &GetNullCompArr(); // NOTE : returns a null array of components ( all nullptr )
		static BaseComp   &GetNullComp();   //  NOTE : returns a null BaseComponent ( innactive )
		static ECpair     &GetNullECpair(); //  NOTE : returns a null ECpair ( Ntt = nullptr, Comps = nullptr )

		TTC static CompT  *CompFactory(); //                   NOTE : allocs new component
		TTC static CompT  *CompFactory( CompT *component ); // NOTE : allocs + copies component

		static GameEntity *NttFactory(); //                  NOTE : allocs new entity ( ID = 0 )
		static GameEntity *NttFactory( NttID_t id ); //      NOTE : allocs new entity with given ID
		static GameEntity *NttFactory( GameEntity *Ntt ); // NOTE : allocs + copies entity

	// ================================ TICK METHODS
		void updateAllEntities(); //   NOTE : calls the onTick() method of all components in the map ( one entity at a time )
		void updateAllComponents(); // NOTE : calls the onTick() method of all components in the map ( each component type at a time)

		void updateComponentByType( comp_e compType ); // NOTE : calls the onTick() method of all components of the given type in the map
};



extern ECpair			&NullECPair;
extern GameEntity &NullNtt;
extern CompArr    &NullCompArr;
extern BaseComp   &NullComp;

#endif // COMP_MANAGER_HPP

