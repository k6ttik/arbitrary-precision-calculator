#ifndef SRC_CBIGNUMBER_H
#define SRC_CBIGNUMBER_H

#include <vector>
#include <ostream>
#include <memory>
#include "CNumData.h"

using std::vector;
using std::ostream;
using std::shared_ptr;

class CBigInt;
class CBigFloat;


/** Abstract class that represents big number
 */
class CBigNumber {
public:
    /**
     * @brief Constructor with sign and integer part.
     * @param[in] sign Sign of number
     * @param[in] intStr Integer part of number that is in string
     */
    CBigNumber ( bool sign , const string & intStr );

    /**
     * @brief Constructor with sign, integer part and float part
     * @param[in] sign Sign of number
     * @param[in] intStr Integer part of number
     * @param[in] floatStrStr Float part of number
     */
    CBigNumber ( bool sign , const string & intStr , const string & floatStr );

    /**
     * @brief Copy constructor
     * @param[in] src Source object that need to be copied
     */
    CBigNumber ( const CBigNumber & src );

    /**
    * @brief Default virtual destructor
    */
    virtual ~CBigNumber () = default;

    /**
    * @brief Sets signs of number
    */
    void setSign ( bool sign );

    /**
    * @brief Sets integer part of number
    * @param[in] intStr Integer part of number
    * @throw std::logic_error if intStr is empty or contains not digits
    */
    void setIntPart ( const string & intStr );

    /**
    * @brief Sets float part of number
    * @param[in] floatStrStr Float part of number
    * @throw std::logic_error if intStr is empty or contains not digits
    */
    void setFloatPart ( const string & floatStr );

    /**
    * @brief Increments value by one
    * @return reference to current object
    */
    CBigNumber & operator ++ ();

    /**
    * @brief Decrements value by one
    * @return Reference to current object
    */
    CBigNumber & operator -- ();

    /**
    * @brief Compares two numbers
    * @param[in] right Number to compare
    * @return True if numbers is equal, otherwise false
    */
    bool operator == ( const CBigNumber & right ) const;

    /**
    * @brief Compares two numbers
    * @param[in] right Number to compare
    * @return True if numbers is not equal, otherwise false
    */
    bool operator != ( const CBigNumber & right ) const;

    /**
     * @brief Overloaded operator for CBigNumber output
     * @param[out] out Ostream where number will be output
     * @param[in] right number that need to be output
     * @return Reference of ostream where number will be output
     */
    friend ostream & operator << ( ostream & out , const CBigNumber & right );

    /**
     * @brief Creates instance of the derived class that is copy of the current object.
     * @return Pointer to newly created object.
     */
    virtual CBigNumber * clone () const = 0;

    /**
     * @brief Prints number
     * @param[out] out Ostream where number need to be output
     */
    virtual void print ( ostream & out ) const = 0;

    /**
     * @brief Transform number to string
     * @return String representation of number
     */
    virtual string toString () const = 0;

    /**
     * @brief Checks if number is zero
     * @return True if number is zero, otherwise false
     */
    virtual bool isNull () const = 0;

    /**
     * @brief Finds sum of current and specific number
     * @param[in] right Number to be added.
     * @return Shared pointer to the sum of the two numbers.
     */
    virtual shared_ptr<CBigNumber> add ( const CBigNumber & right ) const = 0;

    /**
     * @brief Finds differences between current and specific number
     * @param[in] right Number to be subtracted
     * @return Shared pointer to the differences of two number
     */
    virtual shared_ptr<CBigNumber> subtract ( const CBigNumber & right ) const = 0;

    /**
     * @brief Finds multiplication of current and specific number
     * @param[in] right Number to multiply by
     * @return Shared pointer to the multiplication of two number
     */
    virtual shared_ptr<CBigNumber> multiply ( const CBigNumber & right ) const = 0;

    /**
     * @brief Finds result of division of current number by specific number
     * @param[in] right Number to divided by
     * @return Shared pointer to the division of two number
     */
    virtual shared_ptr<CBigNumber> division ( const CBigNumber & right ) const = 0;

    /**
     * @brief Finds result of modulo division of current number by specific number
     * @param[in] right Number to divided by
     * @return Shared pointer to the modulo division of two number
     */

    virtual shared_ptr<CBigNumber> divMod ( const CBigNumber & right ) const = 0;

    /**
     * @brief Finds degree of current number with specific exponent
     * @param[in] right Exponent
     * @return Shared pointer to the exponentiation of number
     */
    virtual shared_ptr<CBigNumber> exponentiation ( const CBigNumber & right ) const = 0;

    /**
    * @brief Finds rounded value of  current number
    * @return Shared pointer to the rounded number
    */
    virtual shared_ptr<CBigNumber> round () const = 0;

    /**
    * @brief Finds factorial of current number
    * @return Shared pointer to the result of factorial of current number
    */
    virtual shared_ptr<CBigNumber> factorial () const = 0;

    /**
     * @brief Finds sum of specific integer number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number from be added.
     * @return Shared pointer to the sum of the two numbers.
     */
    virtual shared_ptr<CBigNumber> addCertain ( const CBigInt & other ) const = 0;

    /**
     * @brief Finds sum of specific float number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number from be added.
     * @return Shared pointer to the sum of the two numbers.
     */
    virtual shared_ptr<CBigNumber> addCertain ( const CBigFloat & other ) const = 0;

    /**
     * @brief Finds differences of specific integer number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number from be subtracted
     * @return Shared pointer to the differences of two number
     */
    virtual shared_ptr<CBigNumber> subtractCertain ( const CBigInt & other ) const = 0;

    /**
     * @brief Finds differences of specific float number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number from be subtracted
     * @return Shared pointer to the differences of two number
     */
    virtual shared_ptr<CBigNumber> subtractCertain ( const CBigFloat & other ) const = 0;

    /**
     * @brief Finds multiplication of integer number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number to multiply by
     * @return Shared pointer to the multiplication of two number
     */
    virtual shared_ptr<CBigNumber> multCertain ( const CBigInt & other ) const = 0;

    /**
     * @brief Finds multiplication of float number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number to multiply by
     * @return Shared pointer to the multiplication of two number
     */
    virtual shared_ptr<CBigNumber> multCertain ( const CBigFloat & other ) const = 0;

    /**
     * @brief Finds result of division of specific integer number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number for division
     * @return Shared pointer to the division of integer number by current number
     */
    virtual shared_ptr<CBigNumber> divCertain ( const CBigInt & other ) const = 0;

    /**
     * @brief Finds result of division of specific float number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number for division
     * @return Shared pointer to the division of float number by current number
     */
    virtual shared_ptr<CBigNumber> divCertain ( const CBigFloat & other ) const = 0;

    /**
     * @brief Finds result of modulo division of integer number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number for division
     * @return Shared pointer to the division of float number by current number
     */
    virtual shared_ptr<CBigNumber> divModCertain ( const CBigInt & other ) const = 0;

    /**
     * @brief Finds result of modulo division of integer float number and current number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number for modulo division
     * @return Shared pointer to the modulo division of float number by current number
     */
    virtual shared_ptr<CBigNumber> divModCertain ( const CBigFloat & other ) const = 0;

    /**
    * @brief Finds degree of integer number with specific exponent(current number)
    * @details This method is needed for achieving polymorphism
    * @param[in] other Base of exponent
    * @return Shared pointer to the exponentiation of number
    */
    virtual shared_ptr<CBigNumber> exponentCertain ( const CBigInt & other ) const = 0;
/**
    * @brief Finds degree of float number with specific exponent(current number)
    * @details This method is needed for achieving polymorphism
    * @param[in] other Base of exponent
    * @return Shared pointer to the exponentiation of number
    */
    virtual shared_ptr<CBigNumber> exponentCertain ( const CBigFloat & other ) const = 0;


protected:
    /**@var Represents sign of number, value is false, if number is negative, otherwise false*/
    bool _sign;
    /**@var Represents integer part of number*/
    vector<CNumData> _intPart;
    /**@var Represents float part of number, for integer number _floatPart will be empty*/
    vector<CNumData> _floatPart;
};


#endif //SRC_CBIGNUMBER_H
