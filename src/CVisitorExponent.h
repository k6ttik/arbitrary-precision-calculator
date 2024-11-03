#ifndef SRC_CVISITOREXPONENT_H
#define SRC_CVISITOREXPONENT_H

#include "CVisitor.h"

class CVisitorExponent : public CVisitor {
public:
    /**
     * @brief Calls exponentiation method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit ( const CBigInt & left , const CBigNumber & right ) const override;

    /**
     * @brief Calls exponentiation method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit ( const CBigFloat & left , const CBigNumber & right ) const override;
};


#endif //SRC_CVISITOREXPONENT_HX
