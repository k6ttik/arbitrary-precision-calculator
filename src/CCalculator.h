#ifndef SRC_CCALCULATOR_H
#define SRC_CCALCULATOR_H

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "CBigNumber.h"

using std::map;
using std::string;
using std::vector;
using std::shared_ptr;

/**Class that represents calculator*/
class CCalculator {
public:
    CCalculator () = default;

    /**
     * @brief Starts work of calculator and reads input
     * @details depending on input, calls calculation of expression or command execution
     *                               commands start with #
     */
    void work ();

private:

    /**
     * @brief Calculates mathematical expression
     * @param[in] src mathematical expression represented as string
     * */
    void calculate ( const string & src );

    /**
     * @brief Executes commands
     * @param[in] command command with it is argument
     * @brief there is 5 commands
     *                          EXIT close program
     *                          EXPORT exports variables to file
     *                          IMPORT imports variables from file
     *                          PRINT prints variable
     *                          PRINT_ALL prints all variables
     * @throw std::logic_error if command does not exist and argument count is incorrect
     * @return True is command is not EXIT, otherwise false
     * */
    bool executeCommand ( const string & command );

    /**
     * @brief Exports variables of calculator to file
     * @param[in] pathToFile Path to file
     * @details
     * @throw std::logic_error if file could not be opened or error showed up while exporting
     * */
    void exportToFile ( const string & pathToFile ) const;

    /**
     * @brief Imports variables from file to calculator
     * @param[in] pathToFile Path to file
     * @throw std::logic_error if file could not be opened
     *                         or file is corrupted
     *                         or variable has incorrect names
     *                         or error showed up while importing
     * */
    void importFromFile ( const string & pathToFile ) ;

    /**
     * @brief Checks variable name for incorrect chars
     * @param[in] name Variable name that need to be checked
     * @return True if name does not contain incorrect chars, otherwise false
     * */
    bool checkVariableName ( const string & name ) const;

    /**
     * @brief Prints specific variable
     * @throw std::logic_error if variable does not exist
     */
    void printVar ( const string & varName ) const;

    /**
     * @brief Prints all variables
     */
    void printAll () const;

    /**
     * @brief Clears string from consecutive spaces
     * @param[out] str String that need to be cleared
     */
    void clearStrFromConsecSpaces ( string & str );

    /**
     * @brief Split strings by space
     * @param[in] src String that need to be splitted
     * @return Vector of strings after splitting initial string
     */
    vector<string> splitString ( const string & src ) const;

    /**@var map that contains variable name and variable value */
    map<string , shared_ptr<CBigNumber>> _variables;
};


#endif //SRC_CCALCULATOR_H
