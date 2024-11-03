#include "CBigFloat.h"
#include "CBigInt.h"
#include "CVisitorAdd.h"
#include "CVisitorSubtract.h"
#include "CVisitorMult.h"
#include "CVisitorDiv.h"
#include "CVisitorDivMod.h"
#include "CVisitorExponent.h"
#include "CNumStrOper.h"

using std::logic_error;

CBigFloat::CBigFloat ( bool sign , const string & numInt , const string & numFloat )
        : CBigNumber( sign , numInt , numFloat ) {
}

CBigFloat::CBigFloat ( const CBigNumber & src )
        : CBigNumber( src ) {
}

CBigNumber * CBigFloat::clone () const {
    return new CBigFloat( *this );
}

void CBigFloat::print ( ostream & out ) const {
    out << toString();
}

string CBigFloat::toString () const {
    string res;
    if ( !_sign ) {
        res += '-';
    }
    for ( const auto & x : _intPart ) {
        res += x . toString();
    }
    res += '.';
    for ( const auto & x : _floatPart ) {
        res += x . toString();
    }
    return res;
}

bool CBigFloat::isNull () const {
    return (_intPart[0] . _coeff == 0 && !_floatPart[0] . _isFirstNulls && _floatPart[0] . _coeff == 0);
}

shared_ptr<CBigNumber> CBigFloat::add ( const CBigNumber & right ) const {
    CVisitorAdd addVisitor;
    return addVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigFloat::subtract ( const CBigNumber & right ) const {
    CVisitorSubtract subVisitor;
    return subVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigFloat::multiply ( const CBigNumber & right ) const {
    CVisitorMult multVisitor;
    return multVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigFloat::division ( const CBigNumber & right ) const {
    throw logic_error( "Division of float" );
}

shared_ptr<CBigNumber> CBigFloat::divMod ( const CBigNumber & right ) const {
    throw logic_error( "Modulo division by float" );
}

shared_ptr<CBigNumber> CBigFloat::exponentiation ( const CBigNumber & right ) const {
    CVisitorExponent exponentVisitor;
    return exponentVisitor . visit( *this , right );
}

shared_ptr<CBigNumber> CBigFloat::round () const {
    CBigInt res( *this );
    res . setSign( true );
    CNumStrOper numStrOper;

    string _floatPartStr = numStrOper . getStrFromNums( _floatPart );
    if ( _floatPartStr[0] > '5' ) {
        ++res;
    }
    res . setSign( _sign );
    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigFloat::factorial () const {
    throw logic_error( "Factorial of float does not exist" );
}

shared_ptr<CBigNumber> CBigFloat::addCertain ( const CBigInt & other ) const {
    return addCertain( CBigFloat( other ) );
}

shared_ptr<CBigNumber> CBigFloat::addCertain ( const CBigFloat & other ) const {
    CBigFloat left( other );
    CBigFloat right( *this );

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

    pair<string , string> leftNum( numStrOper . getStrFromNums( left . _intPart ) ,
                                   numStrOper . getStrFromNums( left . _floatPart ) );
    pair<string , string> rightNum( numStrOper . getStrFromNums( right . _intPart ) ,
                                    numStrOper . getStrFromNums( right . _floatPart ) );
    auto resPair = numStrOper . addFloatNumStr( leftNum , rightNum );

    CBigFloat res( left . _sign , resPair . first , resPair . second );
    return shared_ptr<CBigNumber>( res . clone() );;
}

shared_ptr<CBigNumber> CBigFloat::subtractCertain ( const CBigInt & other ) const {
    return subtractCertain( CBigFloat( other ) );
}

shared_ptr<CBigNumber> CBigFloat::subtractCertain ( const CBigFloat & other ) const {
    CBigFloat left( other );
    CBigFloat right( *this );
    //+- -+
    if ( (!left . _sign && right . _sign) || (left . _sign && !right . _sign) ) {
        auto tempL = shared_ptr<CBigNumber>( left . clone() );
        auto tempR = shared_ptr<CBigNumber>( right . clone() );
        tempL -> setSign( true );
        tempR -> setSign( true );
        auto res = tempL -> add( *tempR );
        res -> setSign( left . _sign );
        return res;
    }
    //-- ++
    CNumStrOper numStrOper;

    pair<string , string> leftNum( numStrOper . getStrFromNums( left . _intPart ) ,
                                   numStrOper . getStrFromNums( left . _floatPart ) );
    pair<string , string> rightNum( numStrOper . getStrFromNums( right . _intPart ) ,
                                    numStrOper . getStrFromNums( right . _floatPart ) );
    bool isSwapped = false;
    if ( numStrOper . compFloatNumsInStr( leftNum , rightNum ) < 0 ) {
        swap( leftNum , rightNum );
        isSwapped = true;
    }

    auto resPair = numStrOper . subtractFloatNumStr( leftNum , rightNum );
    bool newSign = !isSwapped;
    CBigFloat res( newSign , resPair . first , resPair . second );
    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigFloat::multCertain ( const CBigInt & other ) const {
    return multCertain( CBigFloat( other ) );
}

shared_ptr<CBigNumber> CBigFloat::multCertain ( const CBigFloat & other ) const {
    CBigFloat left( other );
    CBigFloat right( *this );
    if ( right . isNull() ) {
        return shared_ptr<CBigNumber>( new CBigFloat( true , "0" , "0" ) );
    }
    CNumStrOper numStrOper;

    string floatPartL = numStrOper . getStrFromNums( left . _floatPart );
    string floatPartR = numStrOper . getStrFromNums( right . _floatPart );
    size_t decPos = floatPartL . length() + floatPartR . length();
    string intPartL = numStrOper . getStrFromNums( left . _intPart );
    string intPartR = numStrOper . getStrFromNums( right . _intPart );

    string fullStrL = intPartL + floatPartL;
    string fullStrR = intPartR + floatPartR;

    size_t nullCountL = fullStrL . find_first_not_of( '0' );
    size_t nullCountR = fullStrR . find_first_not_of( '0' );
    nullCountL = nullCountL == string::npos ? 0 : nullCountL;
    nullCountR = nullCountR == string::npos ? 0 : nullCountR;

    string resStr = numStrOper . multNumStr( fullStrL , fullStrR );
    resStr = string( nullCountL + nullCountR , '0' ) + resStr;
    string resIntPart = resStr . substr( 0 , resStr . length() - decPos );

    string resFloatPart = resStr . substr( resStr . length() - decPos );
    bool newSign = (left . _sign == right . _sign);

    CBigFloat res( newSign , resIntPart , resFloatPart );
    return shared_ptr<CBigNumber>( res . clone() );
}

shared_ptr<CBigNumber> CBigFloat::divCertain ( const CBigInt & other ) const {
    throw logic_error( "Division by float" );
}

shared_ptr<CBigNumber> CBigFloat::divCertain ( const CBigFloat & other ) const {
    throw logic_error( "Division of float" );
}

shared_ptr<CBigNumber> CBigFloat::divModCertain ( const CBigInt & other ) const {
    throw logic_error( "Modulo division by float" );
}

shared_ptr<CBigNumber> CBigFloat::divModCertain ( const CBigFloat & other ) const {
    throw logic_error( "Modulo division by float" );
}

shared_ptr<CBigNumber> CBigFloat::exponentCertain ( const CBigInt & other ) const {
    throw logic_error( "Exponent is not integer" );
}

shared_ptr<CBigNumber> CBigFloat::exponentCertain ( const CBigFloat & other ) const {
    throw logic_error( "Exponent is not integer" );
}