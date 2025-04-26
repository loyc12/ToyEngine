#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

bool GameEntity::addToManager()
{
	flog( _id );
	GCM->addThatEntity( this );
	return true;
}
bool GameEntity::delFromManager()
{
	flog( _id );
	if ( _id == 0 ){ return false; } // NOTE : if the ID is 0, the entity is not supposed to be in the map

	qlog( "delFromManager : Deleting entity with ID: " + std::to_string( _id ), INFO, 0 );

	GCM->rmvThatEntity( this ); // TODO : make sure this doesn't lead to an infinite loop
	_id = 0;
	return true;
}
void GameEntity::onCpy( const GameEntity &rhs )
{
	flog( _id );
	if( this == &rhs ){ return; } // NOTE : check if the object is the same

	// go through each component associated with rhs and copy their date over to thoes associated with this
}

// ================================ CONSTRUCTORS / DESTRUCTORS

GameEntity::~GameEntity()
{
	flog( _id );
	delFromManager();
}

GameEntity::GameEntity() : _id( 0 )
{
	flog( _id );
	addToManager();
}
GameEntity::GameEntity( bool addEntityToManager, NttID_t id ) : _id( id ) // NOTE : should only be called by CompManager
{
	flog( _id );
	if ( addEntityToManager ){ addToManager(); }
}

GameEntity::GameEntity( const GameEntity &rhs ) : _id( 0 )
{
	flog( _id );
	addToManager();
	*this = rhs; // NOTE : calls the copy assignment operator
}
GameEntity &GameEntity::operator=( const GameEntity &rhs )
{
	flog( _id );
	onCpy( rhs );
	return *this;
}

// ================================ ACCESSORS / MUTATORS

NttID_t GameEntity::getID() const
{
	flog( _id );
	return _id;
}
bool GameEntity::setID( NttID_t id ) // NOTE : should only be called by CompManager
{
	flog( _id );
	if ( id == 0 ){ return false; }

	_id = id;
	return true;
}

bool GameEntity::delID() // NOTE : should only be called by CompManager
{
	flog( _id );
	if ( _id == 0 ){ return false; }

	_id = 0;
	return true;
}

// ================ ACCESSORS / MUTATORS ( redirects )

bool GameEntity::rmvEntity()
{
	flog( _id );
	return GCM->rmvEntity( _id );
}
bool GameEntity::delEntity()
{
	flog( _id );;
	return GCM->delEntity( _id );
}

CompC_t GameEntity::getCompCount()
{
	flog( _id );
	return GCM->getCompCount( _id );
}
CompArr *GameEntity::getCompArr()
{
	flog( _id );
	return GCM->getNttCompArr( _id );
}
