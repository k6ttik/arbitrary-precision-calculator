#include "CVisitorAdd.h"

shared_ptr<CBigNumber> CVisitorAdd::visit ( const CBigInt & left , const CBigNumber & right ) const {
    return right . addCertain( left );
}

shared_ptr<CBigNumber> CVisitorAdd::visit ( const CBigFloat & left , const CBigNumber & right ) const {
    return right . addCertain( left );
}