#include "CNumStrOper.h"
#include <stdexcept>

using std::swap;
using std::to_string;


vector<CNumData> CNumStrOper::getNumFromStr ( const string & numStr ) const {
    vector<CNumData> res;
    for ( size_t i = 0 ; i < numStr . length() ; ) {
        size_t countNextNulls = 0;
        string subStr = numStr . substr( i , MAX_COEFF_LEN );
        i += MAX_COEFF_LEN;

        for ( size_t j = i ; j < numStr . length() ; ++j ) {
            if ( numStr[j] == '0' ) {
                ++countNextNulls;
            } else {
                break;
            }
        }
        i += countNextNulls;
        res . emplace_back( stoll( subStr ) , countNextNulls , false );
    }

    return res;
}

string CNumStrOper::getStrFromNums ( const vector<CNumData> & src ) const {
    string res = "";
    for ( const auto & x : src ) {
        res += x . toString();
    }

    return res;
}

string CNumStrOper::addNumStr ( const string & left , const string & right ) const {
    string res = "";
    int64_t ll = (int64_t) left . length() - 1;
    int64_t rl = (int64_t) right . length() - 1;

    for ( int64_t carry = 0 ; ll >= 0 || rl >= 0 || carry > 0 ; --rl , --ll ) {
        int64_t num1 = ( ll >= 0 ) ? ( left[ll] - '0' ) : 0;
        int64_t num2 = ( rl >= 0 ) ? ( right[rl] - '0' ) : 0;
        int64_t sum = num1 + num2 + carry;
        carry = sum / 10;
        int64_t num = sum % 10;
        res = char( num + '0' ) + res;
    }

    size_t pos = res . find_first_not_of( '0' );
    res = pos != string::npos ? res . substr( pos ) : "0";

    return res;
}

string CNumStrOper::subtractNumStr ( const string & left , const string & right ) const {
    string str1 = left;
    string str2 = right;
    //if str1 is less than str2 we swapped, the sign of resulting number will be determined in class where current method was called
    if ( compIntNumInStr( str1 , str2 ) < 0 ) {
        swap( str1 , str2 );
    }

    string res;
    int64_t ll = (int64_t) str1 . length() - 1;
    int64_t rl = (int64_t) str2 . length() - 1;

    for ( int64_t carry = 0 ; ll >= 0 || rl >= 0 || carry != 0 ; --ll , --rl ) {
        int64_t num1 = (ll >= 0) ? (str1[ll] - '0') : 0;
        int64_t num2 = (rl >= 0) ? (str2[rl] - '0') : 0;
        int64_t diff = num1 - num2 - carry;

        carry = (diff < 0) ? 1 : 0;
        diff = (diff < 0) ? (diff + 10) : diff;

        res = char( diff + '0' ) + res;
    }

    size_t pos = res . find_first_not_of( '0' );
    res = pos != string::npos ? res . substr( pos ) : "0";

    return res;
}

string CNumStrOper::multNumStr ( const string & left , const string & right ) const {
    int64_t ll = (int64_t) left . length();
    int64_t rl = (int64_t) right . length();
    string res( rl + ll , '0' );

    for ( int64_t i = ll - 1 ; i >= 0 ; i-- ) {
        int carry = 0;
        for ( int64_t j = rl - 1 ; j >= 0 ; j-- ) {
            int mult = (left[i] - '0') * (right[j] - '0') + (res[i + j + 1] - '0') + carry;
            carry = mult / 10;
            res[i + j + 1] = char( (mult % 10) + '0' );
        }
        res[i] += carry;
    }

    size_t pos = res . find_first_not_of( '0' );
    res = pos != string::npos ? res . substr( pos ) : "0";

    return res;
}

string CNumStrOper::divNumStr ( const string & left , const string & right ) const {
    if ( right == "0" ) {
        throw std::logic_error( "Division by zero" );
    }

    int cmpRes = compIntNumInStr( left , right );
    if ( !cmpRes ) {
        return "1";
    }
    else if ( cmpRes < 0 ) {
        return "0";
    }
    string res;
    string remainder;
    for ( size_t i = 0 , repeat = 0 ; i < left . length() ; ++i ) {
        remainder += left[i];

        for ( ; compIntNumInStr( remainder , right ) >= 0 ; ++repeat ) {
            remainder = subtractNumStr( remainder , right );
        }
        size_t pos = remainder . find_first_not_of( '0' );
        remainder = pos != string::npos ? remainder . substr( pos ) : "";
        res += to_string( repeat );
        repeat = 0;
    }

    res = res . substr( res . find_first_not_of( '0' ) );
    return res;
}

pair<string , string> CNumStrOper::addFloatNumStr ( const pair<string , string> & left , const pair<string , string> & right ) const {
    string floatPartL = left . second;
    string floatPartR = right . second;

    size_t maxFloatLen = (floatPartL . length() > floatPartR . length() ? floatPartL . length()
                                                                        : floatPartR . length());
    floatPartL += string( maxFloatLen - floatPartL . length() , '0' );
    floatPartR += string( maxFloatLen - floatPartR . length() , '0' );

    size_t lastNotNullL = floatPartL . find_first_not_of( '0' );
    size_t lastNotNullR = floatPartR . find_first_not_of( '0' );

    floatPartL = lastNotNullL == string::npos ? "0" : floatPartL . substr( lastNotNullL );
    floatPartR = lastNotNullR == string::npos ? "0" : floatPartR . substr( lastNotNullR );


    string newIntPart = addNumStr( left . first , right . first );
    string newFloatPart = addNumStr( floatPartL , floatPartR );


    if ( newFloatPart . length() > maxFloatLen ) {
        newFloatPart = newFloatPart . substr( 1 );
        newIntPart = addNumStr( newIntPart , "1" );
    }

    if ( newFloatPart . length() < maxFloatLen ) {
        newFloatPart = string( maxFloatLen - newFloatPart . length() , '0' ) + newFloatPart;
    }

    size_t lastNotNullInd = newFloatPart . find_last_not_of( '0' );
    newFloatPart = (lastNotNullInd == string::npos) ? "0" : newFloatPart . substr( 0 , lastNotNullInd + 1 );

    pair<string , string> res( newIntPart , newFloatPart );

    return res;
}

pair<string , string> CNumStrOper::subtractFloatNumStr ( const pair<string , string> & left , const pair<string , string> & right ) const {
    string floatPartL = left . second;
    string floatPartR = right . second;

    size_t maxFloatLen = (floatPartL . length() > floatPartR . length() ? floatPartL . length()
                                                                        : floatPartR . length());
    floatPartL += string( maxFloatLen - floatPartL . length() , '0' );
    floatPartR += string( maxFloatLen - floatPartR . length() , '0' );

    size_t lastNotNullL = floatPartL . find_first_not_of( '0' );
    size_t lastNotNullR = floatPartR . find_first_not_of( '0' );

    floatPartL = lastNotNullL == string::npos ? "0" : floatPartL . substr( lastNotNullL );
    floatPartR = lastNotNullR == string::npos ? "0" : floatPartR . substr( lastNotNullR );

    string intPartRes = subtractNumStr( left . first , right . first );

    string floatPartRes = subtractNumStr( floatPartL , floatPartR );
    if ( compIntNumInStr( left . first , right . first ) > 0 && compIntNumInStr( floatPartL , floatPartR ) < 0 ) {
        string hlavni = '1' + string( maxFloatLen , '0' );
        floatPartRes = subtractNumStr( hlavni , floatPartRes );
        intPartRes = subtractNumStr( intPartRes , "1" );
    }

    if ( floatPartRes . length() < maxFloatLen ) {
        floatPartRes = string( maxFloatLen - floatPartRes . length() , '0' ) + floatPartRes;
    }
    size_t lastNotNullInd = floatPartRes . find_last_not_of( '0' );
    floatPartRes = (lastNotNullInd == string::npos) ? "0" : floatPartRes . substr( 0 , lastNotNullInd + 1 );

    return pair<string , string>( intPartRes , floatPartRes );
}

int CNumStrOper::compIntNumInStr ( const string & left , const string & right ) const {
    if ( left . length() < right . length() ) {
        return -1;
    }
    else if ( left . length() > right . length() ) {
        return 1;
    }

    for ( size_t i = 0 ; i < left . length() ; ++i ) {
        if ( left[i] < right[i] ) {
            return -1;
        }
        else if ( left[i] > right[i] ) {
            return 1;
        }
    }

    return 0;
}

int CNumStrOper::compFloatPartInStr ( const string & left , const string & right ) const {
    string floatPartL = left;
    string floatPartR = right;
    size_t maxFloatLen = (floatPartL . length() > floatPartR . length() ? floatPartL . length()
                                                                        : floatPartR . length());
    floatPartL += string( maxFloatLen - floatPartL . length() , '0' );
    floatPartR += string( maxFloatLen - floatPartR . length() , '0' );

    size_t lastNotNullL = floatPartL . find_first_not_of( '0' );
    size_t lastNotNullR = floatPartR . find_first_not_of( '0' );

    floatPartL = lastNotNullL == string::npos ? "0" : floatPartL . substr( lastNotNullL );
    floatPartR = lastNotNullR == string::npos ? "0" : floatPartR . substr( lastNotNullR );

    return compIntNumInStr( floatPartL , floatPartR );
}

int CNumStrOper::compFloatNumsInStr ( const pair<string , string> & left , const pair<string , string> & right ) const {
    if ( !compIntNumInStr( left . first , right . first ) ) {
        return compFloatPartInStr( left . first , left . second );
    }
    return compIntNumInStr( left . first , right . first );
}