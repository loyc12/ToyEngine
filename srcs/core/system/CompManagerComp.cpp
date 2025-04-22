#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ ACCESSORS / MUTATORS

// ================ COMPONENT METHODS

CompArr &CompManager::getNttCompArr( GameEntity &Ntt ){ return getNttCompArr( Ntt.getID() ); }
CompArr &CompManager::getNttCompArr( NttID_t id )
{
	if( !isUsedID( id )){ return NullCompArr; } // NOTE : returns a null array of components ( all nullptr )
	return _NttMap.find( id )->second.Comps;
}

CompC_t CompManager::getCompCount( NttID_t id ) const
{
	if( !isUsedID( id )){ return 0; }

	const CompArr &comps = _NttMap.find( id )->second.Comps;

	CompC_t count = 0;
	for( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		if( comps[ i ] != nullptr ){ count++; }
	}
	return count;
}

