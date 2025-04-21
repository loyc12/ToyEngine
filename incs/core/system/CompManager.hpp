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
}             NCpair;

typedef std::unordered_map< NttID_t, NCpair > ECmap_t;


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
		inline ~CompManager(){ clearAllPairs(); }; // TODO : TEST ME

	// ================================ ACCESSORS / MUTATORS
		bool        isValidID( NttID_t id ) const;
		bool        isUsedID(  NttID_t id ) const;
		bool        isFreeID(  NttID_t id ) const;

	// ================ ENTITY METHODS // TODO : TEST US
		GameEntity &getNullEntity();

		NttID_t     getEntityCount();
		bool        hasEntity( GameEntity &Ntt ) const;
		bool        addEntity( GameEntity &Ntt );
		bool        delEntity( GameEntity &Ntt );

		GameEntity &getEntityByID( NttID_t id );
		bool        hasEntityByID( NttID_t id ) const;
		bool        addEntityByID( NttID_t id );
		bool        delEntityByID( NttID_t id );

		// ================ COMPONENT METHODS // TODO : TEST US
		BaseComp &getNullComp();
		CompArr  &getNullCompArr();

		CompArr  &getNttCompArr( GameEntity &Ntt );
		CompArr  &getNttCompArr( NttID_t id );

		CompC_t     getCompCount( NttID_t id ) const;
		TTC bool    hasComponent( NttID_t id, CompT &component ) const;
		TTC bool    addComponent( NttID_t id, CompT &component );
		TTC bool    delComponent( NttID_t id, CompT &component );

		TTC CompT  &getComponentByType( NttID_t id, comp_e component_type );
		bool        hasComponentByType( NttID_t id, comp_e component_type ) const;
		bool        addComponentByType( NttID_t id, comp_e component_type );
		bool        delComponentByType( NttID_t id, comp_e component_type );

	// ================================ TICK METHODS

};

#endif // COMP_MANAGER_HPP

