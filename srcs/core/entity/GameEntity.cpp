#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

bool GameEntity::addToManager()
{
	log( "GameEntity::addToManager()", DEBUG, _id );
	GCM->addThatEntity( this );
	return true;
}
bool GameEntity::delFromManager()
{
	log( "GameEntity::delFromManager()", DEBUG, _id );
	if ( _id == 0 ){ return false; } // NOTE : if the ID is 0, the entity is not supposed to be in the map

	GCM->rmvThatEntity( this ); // TODO : make sure this doesn't lead to an infinite loop
	_id = 0;
	return true;
}
void GameEntity::onCpy( const GameEntity &rhs )
{
	log( "GameEntity::onCpy()" );

	if( this == &rhs ){ return; } // NOTE : check if the object is the same

	// go through each component associated with rhs and copy their date over to thoes associated with this
}

// ================================ CONSTRUCTORS / DESTRUCTORS

GameEntity::~GameEntity()
{
	log( "GameEntity::~GameEntity()", DEBUG, _id );
	delFromManager();
}

GameEntity::GameEntity()
{
	log( "GameEntity::GameEntity(1)", DEBUG);
	addToManager();
}
GameEntity::GameEntity( bool addEntityToManager, NttID_t id ) : _id( id ) // NOTE : should only be called by CompManager
{
	log( "GameEntity::GameEntity(2)", DEBUG, _id );
	if ( addEntityToManager ){ addToManager(); }
}

GameEntity::GameEntity( const GameEntity &rhs )
{
	addToManager();
	*this = rhs; // NOTE : calls the copy assignment operator
}
GameEntity &GameEntity::operator=( const GameEntity &rhs )
{
	log( "GameEntity::operator=()", DEBUG, _id );
	onCpy( rhs );
	return *this;
}

// ================================ ACCESSORS / MUTATORS

NttID_t GameEntity::getID() const
{
	log( "GameEntity::getID()", DEBUG, _id );
	return _id;
}
bool GameEntity::setID( NttID_t id ) // NOTE : should only be called by CompManager
{
	log( "GameEntity::setID()", DEBUG, _id );
	if ( id == 0 ){ return false; }

	_id = id;
	return true;
}

bool GameEntity::delID() // NOTE : should only be called by CompManager
{
	log( "GameEntity::delID()", DEBUG, _id );
	if ( _id == 0 ){ return false; }

	_id = 0;
	return true;
}

// ================ ACCESSORS / MUTATORS ( redirects )

CompC_t GameEntity::getCompCount()
{
	log( "GameEntity::getCompCount()", DEBUG, _id );
	return GCM->getCompCount( _id );
}
CompArr &GameEntity::getCompArr()
{
	log( "GameEntity::getCompArr()", DEBUG, _id );
	return GCM->getNttCompArr( _id );
}
