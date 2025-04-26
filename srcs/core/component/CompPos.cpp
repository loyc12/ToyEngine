#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

/* void CompPos::onCpy( const BaseComp &rhs )
{
	log( "CompPos::onCpy()", DEBUG, _id );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	BaseComp::onCpy( rhs );
	_pos = { 0, 0 };
} */
void CompPos::onCpy( const CompPos &rhs )
{
	log( "CompPos::onCpy()", DEBUG, _id );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	BaseComp::onCpy( rhs );
	_pos = rhs._pos;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompPos::~CompPos()
{
	log( "CompPos::~CompPos()", DEBUG, _id );
	onDel();
}

CompPos::CompPos() : BaseComp(), _pos({ 0, 0 })
{
	log( "CompPos::CompPos(1)", DEBUG, _id );
	onAdd();
}
CompPos::CompPos( bool isActive, NttID_t id, Vector2 pos ) : BaseComp( isActive, id ), _pos( pos )
{
	log( "CompPos::CompPos(3)", DEBUG, _id );
	onAdd();
}

/* CompPos::CompPos( const BaseComp &rhs ) : BaseComp( rhs )
{
	log( "CompPos::CompPos(B)", DEBUG, _id );
	*this = rhs;
} */
CompPos::CompPos( const CompPos &rhs ) : BaseComp( rhs )
{
	log( "CompPos::CompPos(C)", DEBUG, _id );
	*this = rhs;
}

/* CompPos &CompPos::operator=( const BaseComp &rhs )
{
	log( "CompPos::operator=()", DEBUG, _id );
	onCpy( rhs );
	return *this;
} */
CompPos &CompPos::operator=( const CompPos &rhs )
{
	log( "CompPos::operator=()", DEBUG, _id );
	onCpy( rhs );
	return *this;
}