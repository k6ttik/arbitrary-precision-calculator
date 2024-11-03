#include "CBigNumber.h"
#include "CNumStrOper.h"

using std::logic_error;

CBigNumber::CBigNumber ( bool sign , const string & intStr )
        : _sign( sign )
{
    setIntPart( intStr );
}

CBigNumber::CBigNumber ( bool sign , const string & intStr , const string & floatStr )
        : _sign( sign )
{
    setIntPart( intStr );
    setFloatPart( floatStr );
}

CBigNumber::CBigNumber ( const CBigNumber & src )
        : _sign( src . _sign ) ,
          _intPart( src . _intPart )
{
    CNumStrOper numStrOper;

    if ( src . _floatPart . empty() ) {
        _floatPart = numStrOper . getNumFromStr( "0" );
    }
    else {
        _floatPart = src . _floatPart;
    }
}

void CBigNumber::setSign ( bool sign ) {
    _sign = sign;
}

void CBigNumber::setIntPart ( const string & intStr ) {
    if ( intStr . empty() ) {
        throw logic_error( "Integer part must not be empty" );
    }
    for ( const auto & x : intStr ) {
        if ( !isdigit( x ) ) {
            throw logic_error( "String contains not digits" );
        }
    }

    CNumStrOper numStrOper;
    size_t firstNotNull = intStr . find_first_not_of( '0' );

    if ( firstNotNull == string::npos ) {
        _sign = true;
        _intPart = numStrOper . getNumFromStr( "0" );
    }
    else {
        _intPart = numStrOper . getNumFromStr( intStr );
    }
}

void CBigNumber::setFloatPart ( const string & floatStr ) {
    if ( floatStr . empty() ) {
        throw logic_error( "Float part must not be empty" );
    }
    for ( const auto & x : floatStr ) {
        if ( !isdigit( x ) ) {
            throw logic_error( "String contains not digits" );
        }
    }
    CNumStrOper numStrOper;

    size_t firstNotNull = floatStr . find_first_not_of( '0' );

    if ( firstNotNull == string::npos ) {
        _floatPart = numStrOper . getNumFromStr( "0" );
    } else {
        string floatPart = floatStr . substr( firstNotNull );
        size_t lastNotNullPos = floatPart . find_last_not_of( '0' );
        floatPart = floatPart . substr( 0 , lastNotNullPos + 1 );
        _floatPart = numStrOper . getNumFromStr( floatPart );
        /*
         * This piece of code checks if float parts start with zeros, for example number 0.0000000001
         * */
        if ( firstNotNull != 0 ) {
            _floatPart . insert( _floatPart . begin() , CNumData( 0 , firstNotNull , true ) );
        }
    }
}

CBigNumber & CBigNumber::operator ++ () {
    string res;
    CNumStrOper numStrOper;

    if ( _sign ) {
        res = numStrOper . addNumStr( numStrOper . getStrFromNums( _intPart ) , "1" );
    }
    else {
        res = numStrOper . subtractNumStr( numStrOper . getStrFromNums( _intPart ) , "1" );
        if ( res == "0" ) {
            _sign = true;
        }
    }

    _intPart = numStrOper . getNumFromStr( res );
    return *this;
}


CBigNumber & CBigNumber::operator -- () {
    string res;
    CNumStrOper numStrOper;

    if ( _sign ) {
        if ( isNull() ) {
            _sign = false;
        }
        res = numStrOper . subtractNumStr( numStrOper . getStrFromNums( _intPart ) , "1" );
    }
    else {
        res = numStrOper . addNumStr( numStrOper . getStrFromNums( _intPart ) , "1" );
    }
    _intPart = numStrOper . getNumFromStr( res );
    return *this;
}

ostream & operator << ( ostream & out , const CBigNumber & right ) {
    right . print( out );
    return out;
}

bool CBigNumber::operator == ( const CBigNumber & right ) const {
    CNumStrOper numStrOper;

    string intPartL = numStrOper . getStrFromNums( _intPart );
    string intPartR = numStrOper . getStrFromNums( right . _intPart );
    if ( numStrOper . compIntNumInStr( intPartL , intPartR ) ) {
        return false;
    }

    string floatPartL = numStrOper . getStrFromNums( _floatPart );
    string floatPartR = numStrOper . getStrFromNums( right . _floatPart );

    if ( numStrOper . compFloatPartInStr( floatPartL , floatPartR ) ) {
        return false;
    }
    return true;
}

bool CBigNumber::operator != ( const CBigNumber & right ) const {
    return !(*this == right);
}

