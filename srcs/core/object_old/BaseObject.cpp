#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ MEMORY METHODS

bool BaseObject::addToEngine()
{
	log( "BaseObject::addToEngine()", DEBUG, _id );

	// getting a new ID here instead of in Engine::addObject() to prevent making setID() public
	_id = GNG->getNewID();

	GNG->addObject( this );

	return true;
}

bool BaseObject::delFromEngine()
{
	log( "BaseObject::delFromEngine()", DEBUG, _id );

	GNG->delObjectByID( _id );		_id = 0;

	return true;
}
// ================================ CORE METHODS

void BaseObject::onAdd()
{
	log( "BaseObject::onAdd()", DEBUG, _id );

	_id = 0;

	addToEngine();
}

void BaseObject::onCpy( const BaseObject &obj )
{
	log( "BaseObject::onCpy()", DEBUG, _id );
	_type = obj.getType();
}

void BaseObject::onDel() // inverted call order
{
	log( "BaseObject::onDel()", DEBUG, _id );

	// NOTE : if the object is being tracked, stop tracking it
	if ( GVP != nullptr && GVP->isTracking() && GVP->getTrackedObject() == this )
	{
		log( "BaseObject::onDel() : untracking object", DEBUG, _id );
		GVP->untrackObject();
	}
	if ( _id != 0 )
	{
		if ( !delFromEngine() )
		{
			log( "BaseObject::onDel() : failed to delete object from engine", ERROR, _id );
			return;
		}
	}
}

// ================================ CONSTRUCTORS / DESTRUCTORS

BaseObject::BaseObject() : _type( E_BASEOBJ ){ BaseObject::onAdd(); }
BaseObject::BaseObject( objectType_e type ) : _type( type ){ BaseObject::onAdd(); }

BaseObject::BaseObject( const BaseObject &obj ) : _type( E_BASEOBJ )
{
	if ( this == &obj ) return;

	BaseObject::onAdd();
	BaseObject::onCpy( obj );
}

BaseObject &BaseObject::operator=( const BaseObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	return *this;
}

BaseObject::~BaseObject(){ BaseObject::onDel(); }

// ================================ TICK METHODS

void BaseObject::onShapeTick(){  log( "BaseObject::onShapeTick()  : not implemented", WARN ); }
void BaseObject::onScriptTick(){ log( "BaseObject::onScriptTick() : not implemented", WARN ); }
void BaseObject::onPhysicTick(){ log( "BaseObject::onPhysicTick() : not implemented", WARN ); }
void BaseObject::onRenderTick(){ log( "BaseObject::onRenderTick() : not implemented", WARN ); }

// ================================ ACCESSORS

objectType_e BaseObject::getType() const { return _type; }
uint         BaseObject::getID()   const { return _id; }

// ================================ MUTATORS

void BaseObject::setType( objectType_e type ){ _type = type; } // NOTE : UNSAFE
void BaseObject::setID( objID_t id ){         _id    = id;   } // NOTE : UNSAFE



