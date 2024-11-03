#include "CVisitorDivMod.h"

shared_ptr<CBigNumber> CVisitorDivMod::visit ( const CBigInt & left , const CBigNumber & right ) const {
    return right . divModCertain( left );
}

shared_ptr<CBigNumber> CVisitorDivMod::visit ( const CBigFloat & left , const CBigNumber & right ) const {
    return right . divModCertain( left );
}
