#ifndef FIXEDPOINT_HPP
# define FIXEDPOINT_HPP

# include "../defs.hpp"

class FixedPoint
{
	private:

	// ================================ ATTRIBUTES

	bit_t       _isNeg;
	uint        _rawValue;
	const byte_t _shift = 10;

	public:

	// ================================ CONSTRUCTORS

	FixedPoint();
	FixedPoint( const FixedPoint &fp );
	FixedPoint &operator=( const FixedPoint &fp );
	~FixedPoint() = default;

	FixedPoint( byte_t value );
	FixedPoint( word_t value );
	FixedPoint( int    value );
	FixedPoint( long   value );
	FixedPoint( float  value );
	FixedPoint( double value );


	// ================================ ACCESSORS

	int    toInt()    const;
	long   toLong()   const;
	float  toFloat()  const;
	double toDouble() const;

	byte_t getShift() const;
	bit_t  getSign()  const;

	uint   getRawValue() const;
	void   setSign(      const bit_t &sign );
	void   setRawValue(  const uint &rawValue );

	// ================================ OPERATORS

	bool isNegative() const;
	bool isPositive() const;

	FixedPoint operator+( const FixedPoint &fp ) const;
	FixedPoint operator-( const FixedPoint &fp ) const;
	FixedPoint operator*( const FixedPoint &fp ) const;
	FixedPoint operator/( const FixedPoint &fp ) const;
	FixedPoint operator%( const FixedPoint &fp ) const;

	FixedPoint &operator+=( const FixedPoint &fp );
	FixedPoint &operator-=( const FixedPoint &fp );
	FixedPoint &operator*=( const FixedPoint &fp );
	FixedPoint &operator/=( const FixedPoint &fp );
	FixedPoint &operator%=( const FixedPoint &fp );

	FixedPoint operator++( int );
	FixedPoint operator--( int );
	FixedPoint &operator++();
	FixedPoint &operator--();

	FixedPoint operator<<(   const byte_t &shift );
	FixedPoint operator>>(   const byte_t &shift );
	FixedPoint &operator<<=( const byte_t &shift );
	FixedPoint &operator>>=( const byte_t &shift );

	bool operator!() const;

	bool operator!=( const FixedPoint &fp ) const;
	bool operator<(  const FixedPoint &fp ) const;
	bool operator<=( const FixedPoint &fp ) const;
	bool operator==( const FixedPoint &fp ) const;
	bool operator>=( const FixedPoint &fp ) const;
	bool operator>(  const FixedPoint &fp ) const;

	FixedPoint &operator=( const byte_t &b );
	FixedPoint &operator=( const word_t &w );
	FixedPoint &operator=( const int &i );
	FixedPoint &operator=( const long &l );
	FixedPoint &operator=( const float &f );
	FixedPoint &operator=( const double &d );
};

ostream &operator<<( ostream &out, const FixedPoint &fp );

#endif // FIXEDPOINT_HPP
