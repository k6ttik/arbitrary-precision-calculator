#ifndef SRC_CVISITORADD_H
#define SRC_CVISITORADD_H

#include "CVisitor.h"

class CVisitorAdd: public CVisitor{
public:
    /**
     * @brief Calls add method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigInt & left , const CBigNumber & right ) const override;

    /**
     * @brief Calls add method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigFloat & left , const CBigNumber & right ) const override;
};


#endif //SRC_CVISITORADD_H
