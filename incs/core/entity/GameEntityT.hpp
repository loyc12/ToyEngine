#ifndef GAME_ENTITY_TPP
# define GAME_ENTITY_TPP

# pragma once
# include "./GameEntity.hpp"
# include "../system/CompManager.hpp"

extern CompManager *GCM;


TTC CompT &GameEntity::getComponent()
{
	log( "GameEntity::getComponent()", DEBUG, _id );
	return GCM->getComponent< CompT >( _id );
}
TTC CompT GameEntity::cpyComponent()
{
	log( "GameEntity::cpyComponent()", DEBUG, _id );
	return GCM->cpyComponent< CompT >( _id );
}

TTC bool GameEntity::hasComponent() const
{
	log( "GameEntity::hasComponent()", DEBUG, _id );
	return GCM->hasComponent< CompT >( _id );
}
TTC bool GameEntity::addComponent()
{
	log( "GameEntity::addComponent()", DEBUG, _id );
	return GCM->addComponent< CompT >( _id );
}
TTC bool GameEntity::delComponent()
{
	log( "GameEntity::delComponent()", DEBUG, _id );
	return GCM->delComponent< CompT >( _id );
}

TTC bool GameEntity::hasThatComponent( CompT &component ) const
{
	log( "GameEntity::hasThatComponent()", DEBUG, _id );
	return GCM->hasThatComponent< CompT >( _id, &component );
}
TTC bool GameEntity::addThatComponent( CompT *component )
{
	log( "GameEntity::addThatComponent()", DEBUG, _id );
	return GCM->addThatComponent< CompT >( _id, component );
}
TTC bool GameEntity::delThatComponent( CompT &component )
{
	log( "GameEntity::delThatComponent()", DEBUG, _id );
	return GCM->delThatComponent< CompT >( _id, &component );
}

#endif // GAME_ENTITY_TPP

