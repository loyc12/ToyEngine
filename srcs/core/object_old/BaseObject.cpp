#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ MEMORY METHODS

bool BaseObject::addToEngine()
{
	flog( _id );
	// getting a new ID here instead of in Engine::addObject() to prevent making setID() public
	_id = GNG->getNewID();

	GNG->addObject( this );

	return true;
}

bool BaseObject::delFromEngine()
{
	flog( _id );
	GNG->delObjectByID( _id );		_id = 0;

	return true;
}
// ================================ CORE METHODS

void BaseObject::onAdd()
{
	flog( _id );
	addToEngine();
}

void BaseObject::onCpy( const BaseObject &obj )
{
	flog( _id );
	_type = obj.getType();
}

void BaseObject::onDel() // inverted call order
{
	flog( _id );
	// NOTE : if the object is being tracked, stop tracking it
	if ( GVP != nullptr && GVP->isTracking() && GVP->getTrackedObject() == this )
	{
		log( "untracking object", DEBUG, _id );
		GVP->untrackObject();
	}
	if ( _id != 0 )
	{
		if ( !delFromEngine() )
		{
			log( "failed to delete object from engine", ERROR, _id );
			return;
		}
	}
}

// ================================ CONSTRUCTORS / DESTRUCTORS

BaseObject::BaseObject() : _id( 0 ), _type( E_BASEOBJ ){ flog( _id ); BaseObject::onAdd(); }
BaseObject::BaseObject( objectType_e type ) : _id( 0 ), _type( type ){ flog( _id ); BaseObject::onAdd(); }

BaseObject::BaseObject( const BaseObject &obj ) :  _id( 0 ), _type( E_BASEOBJ )
{
	flog( _id );
	if ( this == &obj ) return;

	BaseObject::onAdd();
	BaseObject::onCpy( obj );
}

BaseObject &BaseObject::operator=( const BaseObject &obj )
{
	flog( _id );
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	return *this;
}

BaseObject::~BaseObject(){ flog( _id ); BaseObject::onDel(); }

// ================================ TICK METHODS

void BaseObject::onShapeTick(){  log( "BaseObject : not implemented", WARN, _id, HERE ); }
void BaseObject::onScriptTick(){ log( "BaseObject : not implemented", WARN, _id, HERE ); }
void BaseObject::onPhysicTick(){ log( "BaseObject : not implemented", WARN, _id, HERE ); }
void BaseObject::onRenderTick(){ log( "BaseObject : not implemented", WARN, _id, HERE ); }

// ================================ ACCESSORS

objectType_e BaseObject::getType() const { return _type; }
uint         BaseObject::getID()   const { return _id; }

// ================================ MUTATORS

void BaseObject::setType( objectType_e type ){ _type = type; } // NOTE : UNSAFE
void BaseObject::setID( objID_t id ){          _id   = id;   } // NOTE : UNSAFE



