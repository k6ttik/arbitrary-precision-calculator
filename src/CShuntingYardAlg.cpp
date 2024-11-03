#include "CShuntingYardAlg.h"
#include "CBigFloat.h"
#include "CBigInt.h"
#include <regex>

using std::regex;
using std::sregex_token_iterator;
using std::logic_error;

CShuntingYardAlg::CShuntingYardAlg ( const map<string , shared_ptr<CBigNumber>> & variables )
        : _variables( variables ) {
}


shared_ptr<CBigNumber> CShuntingYardAlg::parseExpression ( const string & src ) {
    string str = src;

    if ( !checkDataChars( str ) ) {
        throw logic_error( "Input contains unwanted characters" );
    }

    string numOrVar;
    bool isPrevOpBracket = true;
    size_t frontBracketCount = 0;
    size_t backBracketCount = 0;
    for ( char i : str ) {
        if ( i == ' ' ) {
            continue;
        }
        if ( isOperator( i ) ) {
            if ( isPrevOpBracket && i == ')' ) {
                throw logic_error( "Incorrect input" );
            }
            else if ( i == '-' && isPrevOpBracket ) {
                _numbers . emplace( CBigInt( true , "0" ) . clone() );
                isPrevOpBracket = false;
            }

            if ( !numOrVar . empty() ) {
                _numbers . emplace( getBigNum( numOrVar ) );
                numOrVar = "";
            }

            if ( isUnaryOp( i ) ) {
                if ( _numbers . empty() ) {
                    throw logic_error( "Incorrect input" );
                }
                _numbers . emplace( doUnaryOp( i ) );
                continue;
            }

            if ( !_operators . empty() && i != '(' ) {
                char prevOp = _operators . top();
                if ( (prevOp != '(' && getOpPriority( prevOp ) >= getOpPriority( i )) || i == ')' ) {
                    calculate( i );
                }
            }

            if ( i != ')' ) {
                _operators . push( i );
            }
            else {
                ++backBracketCount;
            }

            if ( i == '(' ) {
                isPrevOpBracket = true;
                ++frontBracketCount;
            }
        } else {
            isPrevOpBracket = false;
            numOrVar += i;
        }
    }
    if ( !numOrVar . empty() ) {
        _numbers . emplace( getBigNum( numOrVar ) );
    }

    if ( !_operators . empty() ) {
        calculate( '+' );
    }
    if ( frontBracketCount != backBracketCount ) {
        throw logic_error( "Incorrect input" );
    }
    else if ( _numbers . size() != 1 ) {
        throw logic_error( "Incorrect input" );
    }
    return _numbers . top();
}

void CShuntingYardAlg::calculate ( char nextOp ) {
    if ( nextOp == ')' ) {
        for ( char currOp = _operators . top() ; currOp != '(' && !_operators . empty() ; ) {
            _numbers . emplace( doBinaryOp( currOp ) );
            _operators . pop();
            currOp = _operators . top();
        }
        _operators . pop();
    }
    else {
        for ( char currOp = _operators . top() ;
                                            getOpPriority( currOp ) >= getOpPriority( nextOp ) && !_operators . empty() ; ) {
            _numbers . emplace( doBinaryOp( currOp ) );
            _operators . pop();
            if ( !_operators . empty() ) {
                currOp = _operators . top();
            }
        }
    }
}

shared_ptr<CBigNumber> CShuntingYardAlg::getBigNum ( const string & numOrVar ) const {
    bool isNum = isdigit( numOrVar[0] );
    if ( isNum ) {
        size_t pointPos = numOrVar . find_first_of( '.' );
        if ( pointPos == string::npos ) {
            return shared_ptr<CBigNumber>( new CBigInt( true , numOrVar ) );
        }
        string intPart = numOrVar . substr( 0 , pointPos );
        string floatPart = numOrVar . substr( pointPos + 1 );

        return shared_ptr<CBigNumber>( new CBigFloat( true , intPart , floatPart ) );
    }

    if ( _variables . find( numOrVar ) == _variables . end() ) {
        throw logic_error( numOrVar + " Variable does not exist" );
    }
    return shared_ptr<CBigNumber>( _variables . find( numOrVar ) -> second -> clone() );
}

shared_ptr<CBigNumber> CShuntingYardAlg::doUnaryOp ( char oper ) {
    shared_ptr<CBigNumber> res;
    auto number = _numbers . top();
    _numbers . pop();

    if ( oper == '!' ) {
        res = number -> factorial();
    }
    else if ( oper == '~' ) {
        res = number -> round();
    }
    return res;
}

shared_ptr<CBigNumber> CShuntingYardAlg::doBinaryOp ( char oper ) {
    shared_ptr<CBigNumber> res;
    if(_numbers.size() < 2){
        throw logic_error("Incorrect input");
    }
    auto right = _numbers . top();
    _numbers . pop();
    auto left = _numbers . top();
    _numbers . pop();
    if ( oper == '+' ) {
        res = left -> add( *right );
    }
    else if ( oper == '-' ) {
        res = left -> subtract( *right );
    }
    else if ( oper == '*' ) {
        res = left -> multiply( *right );
    }
    else if ( oper == '/' ) {
        res = left -> division( *right );
    }
    else if ( oper == '^' ) {
        res = left -> exponentiation( *right );
    }
    else if ( oper == '%' ) {
        res = left -> divMod( *right );
    }

    return res;
}

int CShuntingYardAlg::getOpPriority ( char op ) const {
    if ( op == '(' || op == ')' ) {
        return 0;
    }
    if ( op == '+' || op == '-' ) {
        return 1;
    } else if ( op == '*' || op == '/' || op == '%' ) {
        return 2;
    } else if ( op == '^' || op == '~' || op == '!' ) {
        return 3;
    }
    return 4;
}

bool CShuntingYardAlg::checkDataChars ( const string & expression ) const {
    regex check( R"((\+)|(\-)|(\*)|(\/)|(\%)|(\~)|(\!)|(\^)|(\.)|(\()|(\))|(\ )|([a-zA-Z0-9]))" );
    sregex_token_iterator it( expression . begin() , expression . end() , check , -1 );
    sregex_token_iterator itend;
    for ( auto i = it ; i != itend ; ++i ) {
        if ( *i != "" ) {
            return false;
        }
    }
    return true;
}

bool CShuntingYardAlg::isOperator ( char ch ) const {
    return (ch == '+'
            || ch == '-'
            || ch == '/'
            || ch == '*'
            || ch == '%'
            || ch == '~'
            || ch == '^'
            || ch == '!'
            || ch == '('
            || ch == ')'
    );
}

bool CShuntingYardAlg::isUnaryOp ( char currOp ) const {
    return ( currOp == '~' || currOp == '!' );
}

