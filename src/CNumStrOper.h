#ifndef SRC_CNUMSTROPER_H
#define SRC_CNUMSTROPER_H

#include <string>
#include <vector>
#include "CNumData.h"

using std::string;
using std::vector;
using std::pair;


/**Class that do arithmetical operations with numbers that are represented as strings*/
class CNumStrOper {
public:
    CNumStrOper () = default;

    /**
     * @brief Transforms number represented as string to vector of CNumData
     * @param[in] numStr String that need to be transformed
     * @return Vector of CNumData that represents number
     */
    vector<CNumData> getNumFromStr ( const string & numStr ) const;

    /**
     * @brief Transforms number represented as vector of CNumData to string
     * @param[in] src Number that need to be transformed
     * @return Number represented as string
     */
    string getStrFromNums ( const vector<CNumData> & src ) const;

     /**
     * @brief Finds sums of two integer numbers that are in string
     * @param[in] left First number string
     * @param[in] right Second number string
     * @return String of sum of two string number
     */

    string addNumStr ( const string & left , const string & right ) const;

     /**
     * @brief Finds differences of two integer numbers that are in string
     * @param[in] left First number string
     * @param[in] right Second number string
     * @return String of differences of two string number
     */
    string subtractNumStr ( const string & left , const string & right ) const;

    /**
     * @brief Finds multiplication of two integer numbers that are in string
     * @param[in] left First number string
     * @param[in] right Second number string
     * @return String of product of two string number
     */
    string multNumStr ( const string & left , const string & right ) const;

    /**
     * @brief Finds division of two integer numbers that are in string
     * @param[in] left First number string
     * @param[in] right Second number string
     * @return String of differences of two string number
     */
    string divNumStr ( const string & left , const string & right ) const;

    /**
     * @brief Finds sum of two float numbers that are in string
     * @param[in] left First number represented as pair of strings( integer part and float part)
     * @param[in] right Second number represented as pair of strings( integer part and float part)
     * @return Sum of two float number represented as pair of strings
     */
    pair<string , string> addFloatNumStr ( const pair<string , string> & left , const pair<string , string> & right ) const;

    /**
     * @brief Finds differences of two float numbers that are in string
     * @param[in] left First number represented as pair of strings( integer part and float part)
     * @param[in] right Second number represented as pair of strings( integer part and float part)
     * @return Difference of two float number represented as pair of strings
     */
    pair<string , string> subtractFloatNumStr ( const pair<string , string> & left , const pair<string , string> & right ) const;

    /**
     * @brief Compares two integer numbers
     * @param[in] left First number string
     * @param[in] right Second number string
     * @return Zero if numbers are equals,
     *         1 if First number ( left operand ) is more than second number ( right operand)
     *         -1 if First number ( left operand ) is less than second number ( right operand)
     */
    int compIntNumInStr ( const string & left , const string & right ) const;

    /**
     * @brief Compares float parts of two number
     * @param[in] left First number float part
     * @param[in] right Second number float part
     * @return Zero if parts are equals,
     *         1 if First part ( left operand ) is more than second part ( right operand)
     *         -1 if First part ( left operand ) is less than second part ( right operand)
     */
    int compFloatPartInStr ( const string & left , const string & right ) const;

    /**
     * @brief Compares two float numbers
     * @param[in] left First number represented as pair of strings( integer part and float part)
     * @param[in] right Second number represented as pair of strings( integer part and float part)
     * @return Zero if numbers are equals,
     *         1 if First number ( left operand ) is more than second number ( right operand)
     *         -1 if First number ( left operand ) is less than second number ( right operand)
     */
    int compFloatNumsInStr ( const pair<string , string> & left , const pair<string , string> & right ) const;
};


#endif //SRC_CNUMSTROPER_H
