#include "CVisitorExponent.h"

shared_ptr<CBigNumber> CVisitorExponent::visit ( const CBigInt & left , const CBigNumber & right ) const {
    return right . exponentCertain( left );
}

shared_ptr<CBigNumber> CVisitorExponent::visit ( const CBigFloat & left , const CBigNumber & right ) const {
    return right . exponentCertain( left );
}
