#include "CBigInt.h"
#include "CVisitorAdd.h"
#include "CVisitorSubtract.h"
#include "CVisitorMult.h"
#include "CVisitorDiv.h"
#include "CVisitorDivMod.h"
#include "CVisitorExponent.h"
#include "CBigFloat.h"
#include "CNumStrOper.h"

using std::logic_error;

CBigInt::CBigInt ( bool sign , const string & numStr )
        : CBigNumber( sign , numStr )
{
}

CBigInt::CBigInt ( const CBigNumber & src )
        : CBigNumber( src )
{
    _floatPart.clear();
}

CBigNumber * CBigInt::clone () const {
    return new CBigInt( *this );
}

void CBigInt::print ( ostream & out ) const {
    out << toString();
}

string CBigInt::toString () const {
    string res;

    if ( !_sign ) {
        res += '-';
    }
    for ( const auto & x : _intPart ) {
        res += x . toString();
    }
    return res;
}

bool CBigInt::isNull () const {
    return _intPart[0] . _coeff == 0;
}





shared_ptr<CBigNumber> CBigInt::add ( const CBigNumber & right ) const {
    CVisitorAdd addVisitor;
    return addVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigInt::subtract ( const CBigNumber & right ) const {
    CVisitorSubtract subVisitor;
    return subVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigInt::multiply ( const CBigNumber & right ) const {
    CVisitorMult multVisitor;
    return multVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigInt::division ( const CBigNumber & right ) const {
    if ( right . isNull() ) {
        throw logic_error( "Division by zero" );
    }
    CVisitorDiv divVisitor;
    return divVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigInt::divMod ( const CBigNumber & right ) const {
    if( right . isNull() ){
        throw logic_error( "Division by zero" );
    }
    CVisitorDivMod divModVisitor;
    return divModVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigInt::exponentiation ( const CBigNumber & right ) const {
    CVisitorExponent exponentVisitor;
    return exponentVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigInt::round () const {
    return shared_ptr<CBigNumber>( clone() );
}

shared_ptr<CBigNumber> CBigInt::factorial () const {
    if ( !_sign ) {
        throw logic_error( "Only non negative value has factorial" );
    }

    shared_ptr<CBigNumber> res( new CBigInt( true , "1" ) );
    for ( CBigInt i( *this ) ; i != CBigInt( true , "0" ) ; --i ) {
        res = res -> multiply( i );
    }
    return res;
}

shared_ptr<CBigNumber> CBigInt::addCertain ( const CBigInt & other ) const {
    CBigInt left( other );
    CBigInt right( *this );

    if ( left . _sign && ! right . _sign ) {
        auto cloneR = shared_ptr<CBigNumber>( right . clone() );
        cloneR -> setSign( true );
        auto res = left . subtract( *cloneR );
        return res;
    }
    else if ( ! left . _sign && right . _sign ) {
        auto cloneL = shared_ptr<CBigNumber>( left . clone() );
        cloneL -> setSign( true );
        auto res = right . subtract( *cloneL );
        return res;
    }

    CNumStrOper numStrOper;
    string numIntStrL = numStrOper . getStrFromNums( left . _intPart );
    string numIntStrR = numStrOper . getStrFromNums( right . _intPart );
    string newNum = numStrOper . addNumStr( numIntStrL , numIntStrR );
    bool newSign = ( left . _sign && right . _sign );

    CBigInt res( newSign , newNum );

    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigInt::addCertain ( const CBigFloat & other ) const {
    CBigFloat temp( other );
    return temp . addCertain( other );
}

shared_ptr<CBigNumber> CBigInt::subtractCertain ( const CBigInt & other ) const {
    CBigInt left( other );
    CBigInt right( *this );

    if ( (!left . _sign && right . _sign) || (left . _sign && !right . _sign) ) {
        auto tempL = shared_ptr<CBigNumber>( left . clone() );
        auto tempR = shared_ptr<CBigNumber>( right . clone() );
        tempL -> setSign( true );
        tempR -> setSign( true );
        auto res = tempL -> add( *tempR );
        res -> setSign( left . _sign );
        return res;
    }

    CNumStrOper numStrOper;
    string numStr1 = numStrOper . getStrFromNums( left . _intPart );
    string numStr2 = numStrOper . getStrFromNums( right . _intPart );
    string newNum = numStrOper . subtractNumStr( numStr1 , numStr2 );

    bool newSign = numStrOper . compIntNumInStr( numStr1 , numStr2 ) >= 0;

    CBigInt res( newSign , newNum );
    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigInt::subtractCertain ( const CBigFloat & other ) const {
    CBigFloat temp( *this );
    return temp . subtractCertain( other );
}

shared_ptr<CBigNumber> CBigInt::multCertain ( const CBigInt & other ) const {
    CBigInt left( other );
    CBigInt right( *this );
    if ( right . isNull() ) {
        return shared_ptr<CBigNumber>( new CBigInt( true , "0" ) );
    }
    CNumStrOper numStrOper;

    string intPartL = numStrOper . getStrFromNums( left . _intPart );
    string intPartR = numStrOper . getStrFromNums( right . _intPart );
    string resStr = numStrOper . multNumStr( intPartL , intPartR );

    bool newSign = ( left . _sign == right . _sign );
    CBigInt res( newSign , resStr );

    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigInt::multCertain ( const CBigFloat & other ) const {
    CBigFloat temp( *this );
    return temp . multCertain( other );
}

shared_ptr<CBigNumber> CBigInt::divCertain ( const CBigInt & other ) const {
    CBigInt left( other );
    CBigInt right( *this );
    CNumStrOper numStrOper;

    string leftN = numStrOper . getStrFromNums( left . _intPart );
    string rightN = numStrOper . getStrFromNums( right . _intPart );
    string newNum = numStrOper . divNumStr( leftN , rightN );
    bool sign = (left . _sign == right . _sign);
    CBigInt res( sign , newNum );
    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigInt::divCertain ( const CBigFloat & other ) const {
    throw logic_error( "Division of double" );
}

shared_ptr<CBigNumber> CBigInt::divModCertain ( const CBigInt & other ) const {
    CBigInt left( other );
    CBigInt right( *this );
    CNumStrOper numStrOper;

    string leftN = numStrOper . getStrFromNums( left . _intPart );
    string rightN = numStrOper . getStrFromNums( right . _intPart );

    if ( numStrOper . compIntNumInStr( leftN , rightN ) < 0 ) {
        return shared_ptr<CBigNumber>( left . clone() );
    }

    string remFromLeft = numStrOper . divNumStr( leftN , rightN );
    string multRemAndR = numStrOper . multNumStr( remFromLeft , rightN );
    string resStr = numStrOper . subtractNumStr( leftN , multRemAndR );

    bool newSign = resStr == "0" || left . _sign;
    CBigInt res( newSign , resStr );
    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigInt::divModCertain ( const CBigFloat & other ) const {
    throw logic_error( "Modulo division of float" );
}

shared_ptr<CBigNumber> CBigInt::exponentCertain ( const CBigInt & other ) const {
    CBigInt exponent( *this );

    if ( !exponent . _sign ) {
        throw logic_error( "Exponent is negative" );
    }

    shared_ptr<CBigNumber> res = shared_ptr<CBigNumber>( new CBigInt( true , "1" ) );
    for ( ; !exponent . isNull() ; --exponent ) {
        res = res -> multiply( other );
    }
    return res;
}

shared_ptr<CBigNumber> CBigInt::exponentCertain ( const CBigFloat & other ) const {
    CBigInt exponent( *this );

    if ( !exponent . _sign ) {
        throw logic_error( "Exponent is negative" );
    }

    shared_ptr<CBigNumber> res = shared_ptr<CBigNumber>( new CBigFloat( true , "1" , "0" ) );
    for ( ; !exponent . isNull() ; --exponent ) {
        res = res -> multiply( other );
    }
    return res;
}



