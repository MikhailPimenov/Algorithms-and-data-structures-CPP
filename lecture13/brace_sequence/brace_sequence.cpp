#include "brace_sequence.h"
//"asd([[()]])asd"
bool brace_sequence ( const char *cString )
{
    if ( ! cString )
        return false;

    int length = Common::length ( cString ) - 1;

    std::stack < char > stack;

    char b1o = '(';
    char b1c = ')';
    char b2o = '[';
    char b2c = ']';

    for ( int index = 0; index < length; ++index )
    {
        if ( cString[index] != b1o &&
             cString[index] != b2o &&
             cString[index] != b1c &&
             cString[index] != b2c )
            continue;

        if ( cString[index] == b1o || cString[index] == b2o )
            stack.push ( cString[index] );
        else
        {
            if ( stack.empty() )
                return false;
            if ( cString[index] == b1c )
            {
                if ( stack.top() == b1o )
                    stack.pop();
                else
                    return false;
            }
            else
            {
                if ( stack.top() == b2o )
                    stack.pop();
                else
                    return false;
            }
        }
    }

    return stack.empty();
}
