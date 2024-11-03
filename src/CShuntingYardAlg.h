#ifndef SRC_CSHUNTINGYARDALG_H
#define SRC_CSHUNTINGYARDALG_H

#include "CBigNumber.h"
#include <memory>
#include <stack>
#include <map>

using std::map;
using std::stack;
using std::shared_ptr;

/**Class that parses mathematical expression*/
class CShuntingYardAlg {
public:
     /**
     * @brief Constructor that initialize map with variables
     * @param[in] variables Map of existing variables
     */
    CShuntingYardAlg ( const map<string , shared_ptr<CBigNumber>> & variables );

     /**
     * @brief Parses mathematical expression
     * @param[in] src Mathematical expression that need to be parsed
     * @throw std::logic_error if expression is incorrect
     * @return Shared pointer to the number that was calculated from expression
     * */
    shared_ptr<CBigNumber> parseExpression ( const string & src );

private:
    /**
     * @brief Calculates until operations in stack has lower or equal priority than next operation
     * @param[in] nextOp Next operation
     */
    void calculate ( char nextOp );

    /**
     * @brief Gets Shared pointer to number depending on value of numOrVar
     * @param[in] numOrVar String representing number or variable name
     * @throw std::logic_error if number is incorrect or variable does not exist
     * @return Shared pointer to number
     */
    shared_ptr<CBigNumber> getBigNum ( const string & numOrVar ) const;

     /**
     * @brief Performs unary operation
     * @param[in] oper Unary operation that need to be performed
     * @return Shared pointer to resulted number of unary operations
     */
    shared_ptr<CBigNumber> doUnaryOp ( char oper ) ;

     /**
     * @brief Performs binary operation
     * @param[in] oper Binary operation that need to be performed
     * @throw std::logic_error if in stack less than one number
     * @return Shared pointer to resulted number of binary operation
     */
    shared_ptr<CBigNumber> doBinaryOp (char oper );

    /**
     * @brief Gets operator priority
     * @param[in] op Operator
     * @return Priority of operator
     */
    int getOpPriority ( char op ) const;

    /**
     * @brief Check if expression does not have unwanted chars
     * @param[in] expression Mathematical expression
     * @return True if expression does not have unwanted chars, otherwise false
     */
    bool checkDataChars ( const string & expression ) const;

    /**
     * @brief Check if char is operand
     * @param[in] ch char
     * @return True if char is operand, otherwise false
     */
    bool isOperator ( char ch ) const;

    /**
     * @brief Check if operator is unary
     * @param[in] currOp operator
     * @return True if operator is unary, otherwise false
     */
    bool isUnaryOp ( char currOp ) const;

    /**@var map with existing variables */
    map<string , shared_ptr<CBigNumber>> _variables;
    /**@var stack of number that is used in parsing expressions */
    stack<shared_ptr<CBigNumber>> _numbers;
    /**@var stack of operators that is used in parsing expressions */
    stack<char> _operators;
};


#endif //SRC_CSHUNTINGYARDALG_H
