#ifndef SRC_CBIGFLOAT_H
#define SRC_CBIGFLOAT_H

#include "CBigNumber.h"

class CBigFloat : public CBigNumber {
public:
     /**
     * @brief Constructor with sign, integer and float parts
     * @param[in] sign Sign of number
     * @param[in] numInt Integer part represented as string
     * @param[in] numFloat Float par represented as string
     */
    CBigFloat ( bool sign , const string & numInt , const string & numFloat );

     /**
     * @brief Copy constructor
     * @param[in] src Source object that need to be copied
     */
    CBigFloat ( const CBigNumber & src );

     /**
     * @brief Creates instance of the big integer number that is copy of the current object.
     * @return Pointer to newly created object. (Pointer to CBigFloat)
     */
    CBigNumber * clone () const override;

     /**
     * @brief Prints float number
     * @param[out] out Ostream where integer number need to be output
     */
    void print ( ostream & out ) const override;

     /**
     * @brief Transform float number to string
     * @return String representation of float number
     */
    string toString () const override;

     /**
     * @brief Checks if float number is zero
     * @return True if float number is zero, otherwise false
     */
    bool isNull () const override;

     /**
     * @brief Finds sum of current float number and specific number
     * @param[in] right Number to be added.
     * @return Shared pointer to the sum of the two numbers. (Pointer to CBigFloat)
     */
    shared_ptr<CBigNumber> add ( const CBigNumber & right ) const override;

    /**
     * @brief Finds differences between current float number and specific number
     * @param[in] right Number to be subtracted
     * @return Shared pointer to the differences of two number (Pointer to CBigFloat)
     */
    shared_ptr<CBigNumber> subtract ( const CBigNumber & right ) const override;

    /**
     * @brief Finds multiplication of current float number and specific number
     * @param[in] right Number to multiply by
     * @return Shared pointer to the multiplication of two number (Pointer to CBigFloat)
     */
    shared_ptr<CBigNumber> multiply ( const CBigNumber & right ) const override;

    /**
    * @brief Finds result of division of current float number by specific number
    * @param[in] right Number to divided by
    * @throw std::logic_error always, because division of float does not implemented
    * @return Shared pointer to the division of two number (Pointer to CBigFloat)
    */
    shared_ptr<CBigNumber> division ( const CBigNumber & right ) const override;

    /**
    * @brief Finds result of modulo division of current float number by specific number
    * @param[in] right Number to divided by
    * @throw std::logic_error modulo division for float does not exist
    * @return Shared pointer to the modulo division of two number (Pointer to CBigFloat)
    */
    shared_ptr<CBigNumber> divMod ( const CBigNumber & right ) const override;

     /**
     * @brief Finds degree of current float number with specific exponent
     * @param[in] right Exponent
     * @return Shared pointer to the exponentiation of number (Pointer to CBigFloat)
     */
    shared_ptr<CBigNumber> exponentiation ( const CBigNumber & right ) const override;

    /**
    * @brief Finds rounded value of current number
    * @return Shared pointer to the rounded number (Pointer to CBigInt)
    */
    shared_ptr<CBigNumber> round () const override;

    /**
    * @brief Finds factorial of current number
    * @throw std::logic_error always, because factorial of float does not exist
    * @return Shared pointer to the result of factorial of current number
    */
    shared_ptr<CBigNumber> factorial () const override;

    /**
     * @brief Finds sum of specific integer number and current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number from be added.
     * @return Shared pointer to the sum of the two numbers (Pointer to CBigFloat).
     */
    shared_ptr<CBigNumber> addCertain ( const CBigInt & other ) const override;

    /**
        * @brief Finds sum of specific float number and current float number
        * @details This method is needed for achieving polymorphism
        * @param[in] other Float number from be added.
        * @return Shared pointer to the sum of the two numbers (Pointer to CBigFloat).
        */
    shared_ptr<CBigNumber> addCertain ( const CBigFloat & other ) const override;

    /**
     * @brief Finds differences of specific integer number and current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number from be subtracted
     * @return Shared pointer to the differences of two number (Pointer to CBigFloat).
     */
    shared_ptr<CBigNumber> subtractCertain ( const CBigInt & other ) const override;

    /**
     * @brief Finds differences of specific float number and current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number from be subtracted
     * @return Shared pointer to the differences of two number (Pointer to CBigFloat).
     */
    shared_ptr<CBigNumber> subtractCertain ( const CBigFloat & other ) const override;

     /**
     * @brief Finds multiplication of specific integer number and current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number to multiply by
     * @return Shared pointer to the multiplication of two number (Pointer to CBigFloat).
     */
    shared_ptr<CBigNumber> multCertain ( const CBigInt & other ) const override;

     /**
     * @brief Finds multiplication of specific float number and current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number to multiply by
     * @return Shared pointer to the multiplication of two number (Pointer to CBigFloat).
     */
    shared_ptr<CBigNumber> multCertain ( const CBigFloat & other ) const override;

     /**
     * @brief Finds result of division of specific integer number by current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number for division
     * @throw std::logic_error always, because division of float is not implemented
     * @return Shared pointer to the division of float number by current number
     */
    shared_ptr<CBigNumber> divCertain ( const CBigInt & other ) const override;

    /**
     * @brief Finds result of division of specific float number by current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number for division
     * @throw std::logic_error always, because division by float is not implemented
     * @return Shared pointer to the division of float number by current float number
     */
    shared_ptr<CBigNumber> divCertain ( const CBigFloat & other ) const override;

     /**
     * @brief Finds result of modulo division of integer number by current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Integer number for division
     * @throw std::logic_error always, because modulo division by float does not exist
     * @return Shared pointer to the division of integer number by current integer number
     */
    shared_ptr<CBigNumber> divModCertain ( const CBigInt & other ) const override;

    /**
     * @brief Finds result of modulo division of integer number by current float number
     * @details This method is needed for achieving polymorphism
     * @param[in] other Float number for division
     * @throw std::logic_error always, because modulo division by float does not exist
     * @return Shared pointer to the division of integer number by current integer number
     */
    shared_ptr<CBigNumber> divModCertain ( const CBigFloat & other ) const override;

    /**
    * @brief Finds degree of integer number with specific exponent(current float number)
    * @details This method is needed for achieving polymorphism
    * @param[in] other Base of exponent
    * @throw std::logic_error always, because exponent can not be float number
    * @return Shared pointer to the exponentiation of number
    */
    shared_ptr<CBigNumber> exponentCertain ( const CBigInt & other ) const override;

    /**
    * @brief Finds degree of float number with specific exponent(current float number)
    * @details This method is needed for achieving polymorphism
    * @param[in] other Base of exponent
    * @throw std::logic_error always, because exponent can not be float number
    * @return Shared pointer to the exponentiation of number
    */
    shared_ptr<CBigNumber> exponentCertain ( const CBigFloat & other ) const override;


};


#endif //SRC_CBIGFLOAT_H
