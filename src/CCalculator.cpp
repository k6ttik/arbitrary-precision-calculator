#include "CCalculator.h"
#include "CShuntingYardAlg.h"
#include "CBigInt.h"
#include "CBigFloat.h"
#include <regex>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::cin;
using std::regex;
using std::sregex_token_iterator;
using std::stringstream;
using std::cout;
using std::endl;
using std::logic_error;

void CCalculator::work () {
    cout << "Write your expression" << endl;
    while ( true ) {
        try {
            string input;
            getline( cin , input );
            if ( cin . eof() ) {
                break;
            }

            clearStrFromConsecSpaces( input );

            if ( input[0] == '#' ) {
                input = input . substr( 1 );
                if( ! executeCommand( input ) ){
                    break;
                }
            }
            else {
                calculate( input );
            }
        }

        catch ( const logic_error & e ) {
            cout << e . what() << std::endl;
        }

        catch ( const std::exception & ex ) {
            cout << "Something gone wrong, check you input" << endl;
        }
    }
}

void CCalculator::calculate ( const string & src ) {
    string str = src;
    size_t assignmentPos = str . find_first_of( '=' );
    string variableName;

    if ( assignmentPos != string::npos ) {
        variableName = str . substr( 0 , assignmentPos );
        clearStrFromConsecSpaces( variableName );
        str = str . substr( assignmentPos + 1 );
        clearStrFromConsecSpaces( str );
        if ( !checkVariableName( variableName ) ) {
            throw logic_error( "Incorrect name for variable" );
        }
    }

    CShuntingYardAlg shuntingYardAlg( _variables );
    auto res = shuntingYardAlg . parseExpression( str );
    if ( variableName . empty() ) {
        std::cout << "RESULT: " << *res << std::endl;
    }
    else {
        _variables[variableName] = res;
        std::cout << variableName << " = " << *res << std::endl;
    }
}

bool CCalculator::executeCommand( const string & command ) {
    auto tokens = splitString(command);
    string commandName = tokens[0];

    if ( tokens[0] == "EXIT" ) {
        if ( tokens . size() != 1 ) {
            throw logic_error( "EXIT does not have parameters" );
        }
        cout << "Thanks for using my calculator" << endl;
        return false;
    }
    else if ( commandName == "IMPORT" ) {
        if ( tokens . size() != 2 ) {
            throw logic_error( "IMPORT has one argument" );
        }
        importFromFile( tokens[1] );
    }
    else if ( commandName == "EXPORT" ) {
        if ( tokens . size() != 2 ) {
            throw logic_error( "EXPORT has one argument" );
        }
        exportToFile( tokens[1] );
    }
    else if ( commandName == "PRINT" ) {
        if ( tokens . size() != 2 ) {
            throw logic_error( "PRINT has one argument" );
        }
        printVar( tokens[1] );
    }
    else if ( commandName == "PRINT_ALL" ) {
        if ( tokens . size() != 1 ) {
            throw logic_error( "PRINT_ALL does not have arguments" );
        }
        printAll();
    }
    else {
        throw logic_error( "Unknown command" );
    }
    return true;
}

void CCalculator::exportToFile ( const string & pathToFile ) const {
    ofstream writer( pathToFile );

    if ( !writer . is_open() ) {
        writer . close();
        throw logic_error( "File could not be opened" );
    }

    for ( const auto & x : _variables ) {
        writer << x . first << " " << *x . second << std::endl;
        if( writer . bad() ) {
            writer . close();
            throw logic_error( "Error in exporting" );
        }
    }

    cout << "Export to file completed" << endl;
    writer . close();
}

void CCalculator::importFromFile ( const string & pathToFile ) {
    ifstream reader( pathToFile );

    if ( ! reader . is_open() ) {
        reader . close();
        throw logic_error( "File could not be opened" );
    }

    string input;
    map<string , shared_ptr<CBigNumber>> newVars;

    while ( getline( reader , input ) ) {
        auto tokens = splitString( input );

        if ( tokens . size() != 2 ) {
            reader.close();
            throw logic_error( "File is corrupted" );
        }

        string varName = tokens[0];
        string number = tokens[1];
        if ( !checkVariableName( varName ) ) {
            reader.close();
            throw logic_error( "Incorrect name for variable" );
        }

        if( reader . bad() ){
            reader.close();
            throw logic_error( "Error in importing" );
        }

        shared_ptr<CBigNumber> numberPtr;
        bool sign = number[0] != '-';

        if ( !sign ) {
            number = number . substr( 1 );
        }

        size_t pointPos = number . find_first_of( '.' );
        if ( pointPos == string::npos ) {
            numberPtr = shared_ptr<CBigNumber>( new CBigInt( sign , number ) );
        }
        else {
            string intPart = number . substr( 0 , pointPos );
            string floatPart = number . substr( pointPos + 1 );

            numberPtr = shared_ptr<CBigNumber>( new CBigFloat( sign , intPart , floatPart ) );
        }

        newVars[varName] = numberPtr;
    }

    reader . close();
    _variables = newVars;
    cout << "Import from file completed" << endl;
    printAll();
}

bool CCalculator::checkVariableName ( const string & name ) const {
    if ( isdigit( name[0] ) ) {
        return false;
    }

    regex check( R"(([a-zA-Z0-9])|(\_))" );
    sregex_token_iterator it( name . begin() , name . end() , check , -1 );
    sregex_token_iterator itend;

    for ( auto i = it ; i != itend ; ++i ) {
        if ( *i != "" ) {
            return false;
        }
    }

    return true;

}

void CCalculator::printVar ( const string & varName ) const {
    auto it = _variables . find( varName );

    if ( it == _variables . end() ) {
        throw logic_error( "Variable does not exist" );
    }

    cout << it -> first << " = " << *it -> second << endl;
}

void CCalculator::printAll () const {
    if ( _variables . empty() ) {
        cout << "Variables does not exist" << endl;
    }
    for ( const auto & x : _variables ) {
        cout << x . first << " = " << *x . second << endl;
    }
}

void CCalculator::clearStrFromConsecSpaces ( string & str ) {
    string res;
    size_t start = str . find_first_not_of( ' ' );
    size_t end = str . find_last_not_of( ' ' );

    if ( start == string::npos ) {
        str = str . substr( 0 , end + 1 );
    }
    else {
        str = str . substr( start , end - start + 1 );
    }

    unique_copy( str . begin() , str . end() , back_inserter( res ) ,
                 [] ( char a , char b ) { return a == ' ' && b == ' '; } );
    str = res;
}

vector<string> CCalculator::splitString ( const string & src ) const {
    stringstream ss( src );
    string token;
    vector<string> res;
    while ( getline( ss , token , ' ' ) ) {
        res . push_back( token );
    }
    return res;
}