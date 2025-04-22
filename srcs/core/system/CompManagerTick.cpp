#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ METHODS UPDATE METHODS

void CompManager::updateAllEntities()
{	// NOTE : calls the onTick() method of all components in the map ( one entity at a time )
	// NOTE : mutex this if we ever multithread onTick() calls
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		ECpair &pair = it->second;
		for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
		{
			if( pair.Comps[ i ] != nullptr ){ pair.Comps[ i ]->onTick(); }
		}
	}
}
void CompManager::updateAllComponents()
{	// NOTE : calls the onTick() method of all components in the map ( each component type at a time)
	// NOTE : mutex this if we ever multithread onTick() calls
	for ( byte_t i = 0; i < COMP_TYPE_COUNT; ++i )
	{
		for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
		{
			ECpair &pair = it->second;
			if( pair.Comps[ i ] != nullptr ){ pair.Comps[ i ]->onTick(); }
		}
	}
}

void CompManager::updateComponentByType( comp_e compType )
{	// NOTE : calls the onTick() method of all components of the given type in the map
	if( !isValidType( compType) )
	for( auto it = _NttMap.begin(); it != _NttMap.end(); ++it )
	{
		ECpair &pair = it->second;
		if( pair.Comps[ compType ] != nullptr ){ pair.Comps[ compType ]->onTick(); }
	}
}