#ifndef SRC_CVISITORSUBTRACT_H
#define SRC_CVISITORSUBTRACT_H

#include "CVisitor.h"

class CVisitorSubtract : public CVisitor {
public:
    /**
     * @brief Calls subtraction method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigInt & left , const CBigNumber & right ) const override;

    /**
     * @brief Calls subtraction method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigFloat & left , const CBigNumber & right ) const override;
};


#endif //SRC_CVISITORSUBTRACT_H
