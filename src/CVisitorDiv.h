#ifndef SRC_CVISITORDIV_H
#define SRC_CVISITORDIV_H

#include "CVisitor.h"

class CVisitorDiv : public CVisitor{
public:
     /**
     * @brief Calls division method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigInt & left , const CBigNumber & right ) const override;

    /**
     * @brief Calls division method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigFloat & left , const CBigNumber & right ) const override;
};


#endif //SRC_CVISITORDIV_H
