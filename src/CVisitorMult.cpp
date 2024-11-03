#include "CVisitorMult.h"

shared_ptr<CBigNumber> CVisitorMult::visit ( const CBigInt & left , const CBigNumber & right ) const {
    return right . multCertain( left );
}

shared_ptr<CBigNumber> CVisitorMult::visit ( const CBigFloat & left , const CBigNumber & right ) const {
    return right . multCertain( left );
}
