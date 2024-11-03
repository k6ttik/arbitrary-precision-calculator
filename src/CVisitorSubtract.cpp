#include "CVisitorSubtract.h"

shared_ptr<CBigNumber> CVisitorSubtract::visit ( const CBigInt & left , const CBigNumber & right ) const {
    return right . subtractCertain( left );
}

shared_ptr<CBigNumber> CVisitorSubtract::visit ( const CBigFloat & left , const CBigNumber & right ) const {
    return right . subtractCertain( left );
}
