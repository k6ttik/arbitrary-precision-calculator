#ifndef SRC_CNUMDATA_H
#define SRC_CNUMDATA_H

#include <string>
#include <cstdio>

#define MAX_COEFF_LEN 18

using std::string;
using std::size_t;

/**
 * Struct CNumData
 * represents part of big number in calculator
 *
 */
struct CNumData {
    /** Constructor of CNumData
     * @param[in] coeff part of number that has from 1 to 18 digits
     * @param[in] exponent count of nulls after coeff
     * @param[in] isFirstNulls shows if number starts from zeros
     */
    CNumData ( long long coeff , size_t exponent , bool isFirstNulls );

    /**
     * Method that transform CNumData to string
     * @return string representation of CNumData
     */

    string toString () const;

    /** @var part of big number that has from 1 to 18 digits
     */
    size_t _coeff;
    /** @var count of nulls after _coeff */
    size_t _exponent;
    /** @var indicates if number starts with zeros, this needed for representing floatPart of number */
    bool _isFirstNulls;
};



#endif //SRC_CNUMDATA_H
