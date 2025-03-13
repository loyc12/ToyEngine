#include "../../../inc/class/FixedPoint.hpp"

ostream &operator<<( ostream &out, const FixedPoint &fp )
{
	out << std::fixed << std::setprecision( 3 ) << fp.toDouble();
	return out;
}

// ================================ CONSTRUCTORS

FixedPoint::FixedPoint() :  _isNeg( 0 ), _rawValue( 0 ) {}
FixedPoint::FixedPoint( const FixedPoint &fp ) : _isNeg( fp.getSign() ), _rawValue( fp.getRawValue() ) {}
FixedPoint &FixedPoint::operator=( const FixedPoint &fp )
{
	_isNeg = fp._isNeg;
	_rawValue = fp._rawValue;
	return *this;
}

FixedPoint::FixedPoint( byte_t value )
{
	_isNeg = 0;
	_rawValue = value << _shift;
}

FixedPoint::FixedPoint( word_t value )
{
	_isNeg = 0;
	_rawValue = value << _shift;
}

FixedPoint::FixedPoint( int value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		value = -value;
	}
	else
		_isNeg = 0;

	_rawValue = value << _shift;
}

FixedPoint::FixedPoint( long value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		value = -value;
	}
	else
		_isNeg = 0;

	_rawValue = value << _shift;
}

FixedPoint::FixedPoint( float value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		value = -value;
	}
	else
		_isNeg = 0;

	_rawValue = value * ( 1 << _shift );
}

FixedPoint::FixedPoint( double value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		value = -value;
	}
	else
		_isNeg = 0;

	_rawValue = value * ( 1 << _shift );
}

// ================================ ACCESSORS

int FixedPoint::toInt() const
{
	if ( _isNeg ) return -( _rawValue >> _shift );
	else          return  ( _rawValue >> _shift );
}

long FixedPoint::toLong() const
{
	if ( _isNeg ) return -( _rawValue >> _shift );
	else          return  ( _rawValue >> _shift );
}

float FixedPoint::toFloat() const
{
	if ( _isNeg ) return -(( float )_rawValue / ( 1 << _shift ));
	else          return  (( float )_rawValue / ( 1 << _shift ));
}

double FixedPoint::toDouble() const
{
	if ( _isNeg ) return -(( double )_rawValue / ( 1 << _shift ));
	else          return  (( double )_rawValue / ( 1 << _shift ));
}

byte_t FixedPoint::getShift()    const { return _shift; }
bit_t  FixedPoint::getSign()     const { return _isNeg; }
uint   FixedPoint::getRawValue() const { return _rawValue; }

void FixedPoint::setSign(     const bit_t &sign )   { _isNeg = sign; }
void FixedPoint::setRawValue( const uint &rawValue ) { _rawValue = rawValue; }

// ================================ OPERATORS

bool FixedPoint::isNegative() const { return  _isNeg; }
bool FixedPoint::isPositive() const { return !_isNeg; }

// ================ ARITHMETIC OPERATORS

FixedPoint FixedPoint::operator+( const FixedPoint &fp ) const
{
	FixedPoint result;
	if ( _isNeg == fp._isNeg )
	{
		result.setSign( _isNeg );
		result.setRawValue( _rawValue + fp._rawValue );
	}
	else
	{
		if ( _rawValue > fp._rawValue )
		{
			result.setSign( _isNeg );
			result.setRawValue( _rawValue - fp._rawValue );
		}
		else
		{
			result.setSign( !fp._isNeg );
			result.setRawValue( fp._rawValue - _rawValue );
		}
	}
	return result;
}

FixedPoint FixedPoint::operator-( const FixedPoint &fp ) const
{
	FixedPoint result;
	if ( _isNeg != fp._isNeg )
	{
		result.setSign( _isNeg );
		result.setRawValue( _rawValue + fp._rawValue );
	}
	else
	{
		if ( _rawValue > fp._rawValue )
		{
			result.setSign( _isNeg );
			result.setRawValue( _rawValue - fp._rawValue );
		}
		else
		{
			result.setSign( !fp._isNeg );
			result.setRawValue( fp._rawValue - _rawValue );
		}
	}
	return result;
}

FixedPoint FixedPoint::operator*( const FixedPoint &fp ) const
{
	FixedPoint result;
	result._isNeg = _isNeg ^ fp._isNeg;
	result._rawValue = ( _rawValue * fp._rawValue ) >> _shift;
	return result;
}

FixedPoint FixedPoint::operator/( const FixedPoint &fp ) const
{
	FixedPoint result;
	result._isNeg = _isNeg ^ fp._isNeg;
	result._rawValue = ( _rawValue << _shift ) / fp._rawValue;
	return result;
}

FixedPoint FixedPoint::operator%( const FixedPoint &fp ) const
{
	FixedPoint result;
	result._isNeg = _isNeg;
	result._rawValue = _rawValue % fp._rawValue;
	return result;
}

// ================ ASSIGNMENT OPERATORS

FixedPoint &FixedPoint::operator+=( const FixedPoint &fp )
{
	if ( _isNeg == fp._isNeg )
		_rawValue += fp._rawValue;
	else
	{
		if ( _rawValue > fp._rawValue )
			_rawValue -= fp._rawValue;
		else
		{
			_isNeg = fp._isNeg;
			_rawValue = fp._rawValue - _rawValue;
		}
	}
	return *this;
}

FixedPoint &FixedPoint::operator-=( const FixedPoint &fp )
{
	if ( _isNeg != fp._isNeg )
		_rawValue += fp._rawValue;
	else
	{
		if ( _rawValue > fp._rawValue )
			_rawValue -= fp._rawValue;
		else
		{
			_isNeg = !fp._isNeg;
			_rawValue = fp._rawValue - _rawValue;
		}
	}
	return *this;
}

FixedPoint &FixedPoint::operator*=( const FixedPoint &fp )
{
	_isNeg = _isNeg ^ fp._isNeg;
	_rawValue = ( _rawValue * fp._rawValue ) >> _shift;

	if ( _rawValue == 0 ) _isNeg = 0;

	return *this;
}

FixedPoint &FixedPoint::operator/=( const FixedPoint &fp )
{
	_isNeg = _isNeg ^ fp._isNeg;
	_rawValue = ( _rawValue << _shift ) / fp._rawValue;
	return *this;
}

FixedPoint &FixedPoint::operator%=( const FixedPoint &fp )
{
	_rawValue = _rawValue % fp._rawValue;

	if ( _rawValue == 0 ) _isNeg = 0;

	return *this;
}

// ================ INCREMENT AND DECREMENT OPERATORS

FixedPoint FixedPoint::operator++( int )
{
	FixedPoint temp = *this;

	if ( _isNeg ) _rawValue -= 1;
	else _rawValue += 1;

	if ( _rawValue == 0 ) _isNeg = 0;

	return temp;
}

FixedPoint FixedPoint::operator--( int )
{
	FixedPoint temp = *this;

	if ( _rawValue == 0 ) _isNeg = 1;

	if ( _isNeg ) _rawValue += 1;
	else _rawValue -= 1;

	return temp;
}

FixedPoint &FixedPoint::operator++()
{
	if ( _isNeg ) _rawValue -= 1;
	else _rawValue += 1;

	if ( _rawValue == 0 ) _isNeg = 0;

	return *this;
}

FixedPoint &FixedPoint::operator--()
{
	if ( _rawValue == 0 ) _isNeg = 1;

	if ( _isNeg ) _rawValue += 1;
	else _rawValue -= 1;

	return *this;
}

// ================ BITWISE OPERATORS

FixedPoint FixedPoint::operator<<( const byte_t &shift )
{
	FixedPoint result = *this;

	result._rawValue <<= shift;

	return result;

}

FixedPoint FixedPoint::operator>>( const byte_t &shift )
{
	FixedPoint result = *this;

	result._rawValue >>= shift;

	return result;
}

FixedPoint &FixedPoint::operator<<=( const byte_t &shift )
{
	_rawValue <<= shift;
	return *this;
}

FixedPoint &FixedPoint::operator>>=( const byte_t &shift )
{
	_rawValue >>= shift;
	return *this;
}

// ================ LOGICAL OPERATORS

bool FixedPoint::operator!() const { return _rawValue == 0; }



// ================ COMPARISON OPERATORS

bool FixedPoint::operator!=( const FixedPoint &fp ) const
{
	if ( _isNeg != fp._isNeg ) return 1;
	else return _rawValue != fp._rawValue;
}

bool FixedPoint::operator<( const FixedPoint &fp ) const
{
	if ( _isNeg != fp._isNeg ) return _isNeg;
	else return _rawValue < fp._rawValue;
}

bool FixedPoint::operator<=( const FixedPoint &fp ) const
{
	if ( _isNeg != fp._isNeg ) return _isNeg;
	else return _rawValue <= fp._rawValue;
}

bool FixedPoint::operator==( const FixedPoint &fp ) const
{
	if ( _isNeg != fp._isNeg ) return 0;
	else return _rawValue == fp._rawValue;
}

bool FixedPoint::operator>=( const FixedPoint &fp ) const
{
	if ( _isNeg != fp._isNeg ) return !_isNeg;
	else return _rawValue >= fp._rawValue;
}

bool FixedPoint::operator>( const FixedPoint &fp ) const
{
	if ( _isNeg != fp._isNeg ) return !_isNeg;
	else return _rawValue > fp._rawValue;
}

// ================ ASSIGNMENT OPERATORS ( REDEFINITION )

FixedPoint &FixedPoint::operator=( const byte_t &value )
{
	_isNeg = 0;
	_rawValue = (  value << _shift );

	return *this;
}

FixedPoint &FixedPoint::operator=( const word_t &value )
{
	_isNeg = 0;
	_rawValue = (  value << _shift );

	return *this;
}

FixedPoint &FixedPoint::operator=( const int &value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		_rawValue = ( -value << _shift );
	}
	else
	{
		_isNeg = 0;
		_rawValue = (  value << _shift );
	}
	return *this;
}

FixedPoint &FixedPoint::operator=( const long &value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		_rawValue = ( -value << _shift );
	}
	else
	{
		_isNeg = 0;
		_rawValue = (  value << _shift );
	}
	return *this;
}

FixedPoint &FixedPoint::operator=( const float &value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		_rawValue = ( int )( -value * ( 1 << _shift ));
	}
	else
	{
		_isNeg = 0;
		_rawValue = ( int )(  value * ( 1 << _shift ));
	}
	return *this;
}

FixedPoint &FixedPoint::operator=( const double &value )
{
	if ( value < 0 )
	{
		_isNeg = 1;
		_rawValue = ( int )( -value * ( 1 << _shift ));
	}
	else
	{
		_isNeg = 0;
		_rawValue = ( int )(  value * ( 1 << _shift ));
	}
	return *this;
}