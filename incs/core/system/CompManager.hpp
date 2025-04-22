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
		bool isValidType( comp_e type ) const;
		bool isValidID( NttID_t id ) const;
		bool isUsedID(  NttID_t id ) const;
		bool isFreeID(  NttID_t id ) const;

	// ================ ENTITY METHODS
		NttID_t     getEntityCount();
		GameEntity  getEntity( NttID_t id );

		bool hasEntity( NttID_t id ) const;
		bool addEntity( NttID_t id ); // NOTE : should only be called by GameEntity's AddToManager()
		bool delEntity( NttID_t id );

		bool hasThatEntity( GameEntity *Ntt ) const;
		bool addThatEntity( GameEntity *Ntt );
		bool delThatEntity( GameEntity *Ntt );

		bool cpyEntityOver( GameEntity &src, GameEntity &dst );
		bool cpyEntityOver( GameEntity &src, NttID_t     dst );
		bool cpyEntityOver( NttID_t     src, GameEntity &dst );
		bool cpyEntityOver( NttID_t     src, NttID_t     dst );

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

	// ================================ STATIC METHODS
		static GameEntity &getNullEntity(); //  NOTE : returns a null entity ( ID = 0 )
		static CompArr    &getNullCompArr(); // NOTE : returns a null array of components ( all nullptr )
		static BaseComp   &getNullComp();   //  NOTE : returns a null BaseComponent ( innactive )
		static ECpair     &getNullECpair(); //  NOTE : returns a null ECpair ( Ntt = nullptr, Comps = nullptr )

	// ================================ TICK METHODS
		void updateAllEntities(); //   calls the onTick() method of all components in the map ( one entity at a time )
		void updateAllComponents(); // calls the onTick() method of all components in the map ( each component type at a time)
		void updateComponentByType( comp_e compType ); // calls the onTick() method of all components of the given type in the map
};

extern ECpair			&NullECPair;
extern GameEntity &NullNtt;
extern CompArr    &NullCompArr;
extern BaseComp   &NullComp;

#endif // COMP_MANAGER_HPP

