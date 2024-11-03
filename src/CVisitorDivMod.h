//
// Created by User on 30.05.2023.
//

#ifndef SRC_CVISITORDIVMOD_H
#define SRC_CVISITORDIVMOD_H

#include "CVisitor.h"

class CVisitorDivMod : public CVisitor {
public:
    /**
     * @brief Calls modulo division method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigInt & left , const CBigNumber & right ) const override;

    /**
     * @brief Calls modulo division method of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    shared_ptr<CBigNumber> visit( const CBigFloat & left , const CBigNumber & right ) const override;
};


#endif //SRC_CVISITORDIVMOD_H
