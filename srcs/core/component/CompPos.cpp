#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

/* void CompPos::onCpy( const BaseComp &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	BaseComp::onCpy( rhs );
	_pos = { 0, 0 };
} */
void CompPos::onCpy( const CompPos &rhs )
{
	flog( 0 );
	if( this == &rhs ){ return; } // NOTE : checks if the objects are the same

	BaseComp::onCpy( rhs );
	_pos = rhs._pos;
}

// ================================ CONSTRUCTORS / DESTRUCTORS

CompPos::~CompPos()
{
	flog( 0 );
	onDel();
}

CompPos::CompPos() : BaseComp(), _pos({ 0, 0 })
{
	flog( 0 );
	onAdd();
}
CompPos::CompPos( bool isActive, NttID_t id, Vector2 pos ) : BaseComp( isActive, id ), _pos( pos )
{
	flog( 0 );
	onAdd();
}

/* CompPos::CompPos( const BaseComp &rhs ) : BaseComp( rhs )
{
	flog( 0 );
	*this = rhs;
} */
CompPos::CompPos( const CompPos &rhs ) : BaseComp( rhs )
{
	flog( 0 );
	*this = rhs;
}

/* CompPos &CompPos::operator=( const BaseComp &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
} */
CompPos &CompPos::operator=( const CompPos &rhs )
{
	flog( 0 );
	onCpy( rhs );
	return *this;
}