#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ MEMORY METHODS

bool BaseObject::addToEngine()
{
	log( "BaseObject::addToEngine()", DEBUG, _id );

	// getting a new ID here instead of in Engine::addObject() to prevent making setID() public
	_id = GNG->getNewID();

	GNG->addObject( this );

	return EXIT_SUCCESS;
}

bool BaseObject::delFromEngine()
{
	log( "BaseObject::delFromEngine()", DEBUG, _id );

	GNG->delObjectByID( _id );		_id = 0;

	return EXIT_SUCCESS;
}
// ================================ CORE METHODS

void BaseObject::onAdd()
{
	log( "BaseObject::onAdd()", DEBUG, _id );

	_pos =  { 0, 0 };
	_size = { 1, 1 };
	_isSpherical = true;

	addToEngine();
}

void BaseObject::onCpy( const BaseObject &obj )
{
	log( "BaseObject::onCpy()", DEBUG, _id );
	_type = obj.getType();
	_pos = obj.getPosition();
}

void BaseObject::onDel() // inverted call order
{
	log( "BaseObject::onDel()", DEBUG, _id );

	// NOTE : if the object is being tracked, stop tracking it
	if ( GVP != nullptr && GVP->isTracking() && GVP->getTrackedObject() == this )

	if ( _id != 0 ) delFromEngine();
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

// ================================ OPERATORS

// ================================ TICK METHODS

void BaseObject::onScriptTick() { log( "BaseObject::onScriptTick() : not implemented", WARN ); }
void BaseObject::onPhysicTick() { log( "BaseObject::onPhysicTick() : not implemented", WARN ); }
void BaseObject::onRenderTick() { log( "BaseObject::onRenderTick() : not implemented", WARN ); }

// ================================ ACCESSORS

objectType_e BaseObject::getType() const { return _type; }
uint BaseObject::getID() const { return _id; }

bool BaseObject::isSpherical() const { return _isSpherical; }
bool BaseObject::setSpherical( bool isSpherical ){ _isSpherical = isSpherical; return _isSpherical; }

Vector2 BaseObject::getTop()    const { return { _pos.x, (_pos.y - _size.y) }; }
Vector2 BaseObject::getBot()    const { return { _pos.x, (_pos.y + _size.y) }; }
Vector2 BaseObject::getLeft()   const { return { (_pos.x - _size.x), _pos.y }; }
Vector2 BaseObject::getRight()  const { return { (_pos.x + _size.x), _pos.y }; }
Vector2 BaseObject::getCenter() const { return _pos; }

Vector2 BaseObject::getTopLeft()  const { return { (_pos.x - _size.x), (_pos.y - _size.y) }; }
Vector2 BaseObject::getTopRight() const { return { (_pos.x + _size.x), (_pos.y - _size.y) }; }
Vector2 BaseObject::getBotLeft()  const { return { (_pos.x - _size.x), (_pos.y + _size.y) }; }
Vector2 BaseObject::getBotRight() const { return { (_pos.x + _size.x), (_pos.y + _size.y) }; }

Vector2 BaseObject::getPosition()   const { return _pos; }
Vector2 BaseObject::setPosition(    const Vector2 &pos ){ _pos = pos; return _pos; }
Vector2 BaseObject::changePosition( const Vector2 &delta ) { _pos.x += delta.x; _pos.y += delta.y; return _pos; }

// returns the position difference between this object and the given object
Vector2 BaseObject::getRelPosition( const BaseObject &obj ) const
{
	Vector2 relPos = Vector2();
	relPos.x = obj.getPosition().x - _pos.x;
	relPos.y = obj.getPosition().y - _pos.y;
	return relPos;
}

Vector2 BaseObject::getSize() const { return _size; }
Vector2 BaseObject::setSize(  const Vector2 &size )
{
	if ( size.x < 0 || size.y < 0 ){ log( "BaseObject::setSize() : size cannot be negative : clamping to EPS", WARN ); }

	_size = size;
	if ( _size.x <= 0 ) { _size.x = EPS; }
	if ( _size.y <= 0 ) { _size.y = EPS; }
	return _size;
}

Vector2 BaseObject::changeSize( const Vector2 &delta )
{
	_size.x += delta.x; _size.y += delta.y;
	if ( _size.x <= 0 ) { _size.x = EPS; }
	if ( _size.y <= 0 ) { _size.y = EPS; }
	return _size;
}

// returns the size difference between this object and the given object
Vector2 BaseObject::getRelSize( const BaseObject &obj ) const
{
	Vector2 relSize = Vector2();
	relSize.x = obj.getSize().x - _size.x;
	relSize.y = obj.getSize().y - _size.y;
	return relSize;
}

// ================================ DIMENSIONS GETTERS


float BaseObject::getPerim() const
{
	if ( _isSpherical ) // calculate the perimiter of an elliptic shape
	{
		if ( _size.x == _size.y ) { return PI * _size.x * 2; } // circle

		// if not a perfect circle, we use Ramanujan's approximation
		return PI * ( 3 * ( _size.x + _size.y ) - sqrt( ( 3 * _size.x + _size.y ) * ( _size.x + 3 * _size.y )));
	}
	return ( _size.x + _size.y ) * 4;
}
float BaseObject::getArea() const
{
	if ( _isSpherical ) { return PI * _size.x * _size.y; }
	return _size.x * _size.y * 4;
}

float BaseObject::getMinRadius() const { return getMinSide(); }
float BaseObject::getMaxRadius() const
{
	if ( _isSpherical ) { return ( _size.x > _size.y ? _size.x : _size.y); }

  // for a rectangle, the corner is the furthest point from the center
	return getHalfDiago();
}
float BaseObject::getAvgRadius() const
{
	if ( _isSpherical ) { return ( _size.x + _size.y ) / 2; }

	// if not a circle, we use the average between the diagonal and the smallest side, because fuck it we ballin'
	return ( getHalfDiago() + getMinSide() ) / 2;
}

float BaseObject::getHalfDiago() const { return ( sqrt( sqr( _size.x ) + sqr( _size.y ))); }
float BaseObject::getFullDiago() const { return getHalfDiago() * 2; }
