#ifndef GAME_ENTITY_TPP
# define GAME_ENTITY_TPP

# pragma once
# include "./GameEntity.hpp"
# include "../system/CompManager.hpp"

extern CompManager *GCM;


TTC CompT *GameEntity::getComponent()
{
	flog( _id );
	return GCM->getComponent< CompT >( _id );
}
TTC CompT *GameEntity::cpyComponent()
{
	flog( _id );
	return GCM->cpyComponent< CompT >( _id );
}

TTC bool GameEntity::hasComponent() const
{
	flog( _id );
	return GCM->hasComponent< CompT >( _id );
}
TTC bool GameEntity::addComponent()
{
	flog( _id );
	return GCM->addComponent< CompT >( _id );
}
TTC bool GameEntity::delComponent()
{
	flog( _id );
	return GCM->delComponent< CompT >( _id );
}

TTC bool GameEntity::hasThatComponent( CompT *component ) const
{
	flog( _id );
	return GCM->hasThatComponent< CompT >( _id, component );
}
TTC bool GameEntity::addThatComponent( CompT *component )
{
	flog( _id );
	return GCM->addThatComponent< CompT >( _id, component );
}
TTC bool GameEntity::delThatComponent( CompT *component )
{
	flog( _id );
	return GCM->delThatComponent< CompT >( _id, component );
}

#endif // GAME_ENTITY_TPP

