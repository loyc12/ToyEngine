#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

bool GameEntity::addToManager()
{
	log( "GameEntity::addToManager()" );
	GCM->addThatEntity( this );
	return true;
}
bool GameEntity::delFromManager()
{
	log( "GameEntity::delFromManager()" );
	if ( _id == 0 ){ return false; } // NOTE : if the ID is 0, the entity is not supposed to be in the map

	GCM->delThatEntity( this ); // TODO : make sure this doesn't lead to an infinite loop
	return true;
}
void GameEntity::onCpy( const GameEntity &rhs )
{
	log( "GameEntity::onCpy()" );

	if( this == &rhs ){ return; } // NOTE : check if the object is the same

	// go through each component associated with rhs and copy their date over to thoes associated with this
}

// ================================ CONSTRUCTORS / DESTRUCTORS

GameEntity::GameEntity()
{
	log( "GameEntity::GameEntity()" );
	addToManager();
}
GameEntity::GameEntity( bool addEntity, NttID_t id ) : _id( id ) // NOTE : should only be called by CompManager
{
	log( "GameEntity::GameEntity( bool, NttID_t )" );
	if ( addEntity ){ addToManager(); }
}
GameEntity::GameEntity( const GameEntity &rhs )
{
	log( "GameEntity::GameEntity( const GameEntity & )" );
	addToManager();
	onCpy( rhs );
}
GameEntity &GameEntity::operator=( const GameEntity &rhs )
{
	log( "GameEntity::operator=( const GameEntity & )" );
	onCpy( rhs );
	return *this;
}
GameEntity::~GameEntity()
{
	log( "GameEntity::~GameEntity()", DEBUG );
	delFromManager();
}

// ================================ ACCESSORS / MUTATORS

NttID_t GameEntity::getID() const
{
	log( "GameEntity::getID()" );
	return _id;
}
bool GameEntity::setID( NttID_t id ) // NOTE : should only be called by CompManager
{
	log( "GameEntity::setID()" );
	if ( id == 0 ){ return false; }

	_id = id;
	return true;
}

bool GameEntity::delID() // NOTE : should only be called by CompManager
{
	log( "GameEntity::delID()" );
	if ( _id == 0 ){ return false; }

	_id = 0;
	return true;
}

// ================ ACCESSORS / MUTATORS ( redirects )

CompC_t GameEntity::getCompCount()
{
	log( "GameEntity::getCompCount()" );
	return GCM->getCompCount( _id );
}
CompArr &GameEntity::getCompArr()
{
	log( "GameEntity::getCompArr()" );
	return GCM->getNttCompArr( _id );
}

TTC CompT &GameEntity::getComponent()
{
	log( "GameEntity::getComponent()" );
	return GCM->getComponent< CompT >( _id );
}
TTC CompT GameEntity::cpyComponent()
{
	log( "GameEntity::cpyComponent()" );
	return GCM->cpyComponent< CompT >( _id );
}

TTC bool GameEntity::hasComponent() const
{
	log( "GameEntity::hasComponent()" );
	return GCM->hasComponent< CompT >( _id );
}
TTC bool GameEntity::addComponent()
{
	log( "GameEntity::addComponent()" );
	return GCM->addThatComponent( _id, this );
}
TTC bool GameEntity::delComponent()
{
	log( "GameEntity::delComponent()" );
	return GCM->delThatComponent( _id, this );
}

TTC bool GameEntity::hasThatComponent( CompT &component ) const
{
	log( "GameEntity::hasThatComponent()" );
	return GCM->hasThatComponent< CompT >( _id, &component );
}
TTC bool GameEntity::addThatComponent( CompT *component )
{
	log( "GameEntity::addThatComponent()" );
	return GCM->addThatComponent< CompT >( _id, component );
}
TTC bool GameEntity::delThatComponent( CompT &component )
{
	log( "GameEntity::delThatComponent()" );
	return GCM->delThatComponent< CompT >( _id, &component );
}


