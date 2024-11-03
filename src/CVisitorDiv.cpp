#include "CVisitorDiv.h"

shared_ptr<CBigNumber> CVisitorDiv::visit ( const CBigInt & left , const CBigNumber & right ) const {
    return right . divCertain( left );
}

shared_ptr<CBigNumber> CVisitorDiv::visit ( const CBigFloat & left , const CBigNumber & right ) const {
    return right . divCertain( left );
}
