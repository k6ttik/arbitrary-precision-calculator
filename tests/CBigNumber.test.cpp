#include <cassert>
#include "CBigInt.h"
#include "CBigFloat.h"

int main () {
    CBigInt intNum1( true , "10" );
    CBigInt intNum2( true , "3" );

    assert( *intNum1 . add( intNum2 ) == CBigInt( true , "13" ) );
    assert( *intNum2 . subtract( intNum1 ) == CBigInt( false , "7" ) );
    intNum2 . setSign( false );
    assert( *intNum2 . multiply( intNum1 ) == CBigInt( false , "30" ) );
    intNum2 . setIntPart( "0" );
    try {
        intNum1 . division( intNum2 );
        assert( "Exception was not thrown" == nullptr );
    } catch ( const std::logic_error & e ) {

    }

    CBigFloat floatNum1(true,"4","9999999999999999");
    CBigFloat floatNum2(true,"0","0000000000000001");

    assert( * floatNum1 . add(floatNum2) == CBigFloat(true, "5", "0") );
    assert( * floatNum1 . round() == CBigInt( true , "5") );

    return 0;
}