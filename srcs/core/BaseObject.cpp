#include "../../incs/core.hpp"

// ================================ MEMORY METHODS

bool BaseObject::addToRegister()
{
	log( "BaseObject::addToRegister()", DEBUG, _id );

	Engine *engine = Engine::getEngine();

	_id = Engine::getEngine()->getNewID();

	engine->addObject( this );

	return EXIT_SUCCESS;
}

bool BaseObject::delFromRegister()
{
	log( "BaseObject::delFromRegister()", DEBUG, _id );

	Engine::getEngine()->delObjectByID( _id ); _id = 0;

	return EXIT_SUCCESS;
}
// ================================ CORE METHODS

void BaseObject::onAdd()
{
	log( "BaseObject::onAdd()", DEBUG, _id );
	addToRegister();
	_position = { 0, 0 };
}

void BaseObject::onCpy( const BaseObject &obj )
{
	log( "BaseObject::onCpy()", DEBUG, _id );
	_type = obj.getType();
}

void BaseObject::onDel() // inverted call order
{
	log( "BaseObject::onDel()", DEBUG, _id );
	if ( _id != 0 ) delFromRegister();
}


// ================================ CONSTRUCTORS / DESTRUCTORS

BaseObject::BaseObject() : _id( 0 ), _type( E_BASEOBJ ){ BaseObject::onAdd(); }
BaseObject::BaseObject( objectType_e type ) : _id( 0 ),  _type( type ){ BaseObject::onAdd(); }

BaseObject::BaseObject( const BaseObject &obj ) : _type( E_BASEOBJ )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
}

BaseObject &BaseObject::operator=( const BaseObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	return *this;
}

BaseObject::~BaseObject() { BaseObject::onDel(); }

// ================================ ACCESSORS

objectType_e BaseObject::getType() const { return _type; }
uint BaseObject::getID() const { return _id; }

// ================================ OPERATORS

// ================================ METHODS

void BaseObject::onInput()   { return; }
void BaseObject::onUpdate()  { return; }
void BaseObject::onTick()    { return; }
void BaseObject::onRefresh() { return; }

Vector2 BaseObject::getPosition() const { return _position; }
Vector2 BaseObject::setPosition( const Vector2 &pos ) { _position = pos; return _position; }

Vector2 BaseObject::changePosition( const Vector2 &delta ) { _position.x += delta.x; _position.y += delta.y; return _position; }
Vector2 BaseObject::getRelPosition( const BaseObject &obj ) const
{
	Vector2 relPos = Vector2();
	relPos.x = _position.x - obj.getPosition().x;
	relPos.y = _position.y - obj.getPosition().y;
	return relPos;
}
