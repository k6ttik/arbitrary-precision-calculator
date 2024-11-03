#include "CNumData.h"


CNumData::CNumData ( long long int coeff , size_t exponent, bool isFirstNulls )
        :   _coeff(coeff),
            _exponent(exponent),
            _isFirstNulls(isFirstNulls)

{
}

string CNumData::toString () const {
    string res;
    if( ! _isFirstNulls ) {
        res += std::to_string ( _coeff );
    }
    for ( size_t i = 0 ; i < _exponent ; ++i ){
        res += '0';
    }
    return res;
}
