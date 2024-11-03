#ifndef SRC_CVISITOR_H
#define SRC_CVISITOR_H

#include <memory>
#include "CBigNumber.h"
#include "CBigInt.h"
#include "CBigFloat.h"

using std::shared_ptr;

/**Abstract class for implementation double dispatch*/
class CVisitor {
public:
    /**
     * @brief Calls methods of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    virtual shared_ptr<CBigNumber> visit( const CBigInt & left , const CBigNumber & right ) const = 0;

    /**
     * @brief Calls methods of the right operand depending on implementation
     * @param[in] left Left Operand
     * @param[in] right Right Operand
     * @return Shared pointer to resulting number from the called method
     */
    virtual shared_ptr<CBigNumber> visit( const CBigFloat & left , const CBigNumber & right ) const = 0;
};


#endif //SRC_CVISITOR_H
