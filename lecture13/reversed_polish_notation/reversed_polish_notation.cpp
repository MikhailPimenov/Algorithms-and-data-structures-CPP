#include "reversed_polish_notation.h"

int reversed_polish_notation ( const std::vector < Symbol * > &vector )
{
    if ( vector.empty() )
        return -1;

    std::stack < Symbol * > stack;

    for ( const auto &element : vector )
    {
        if ( dynamic_cast < Number * > ( element ) )
            stack.push ( element );
        else
        {
            assert ( dynamic_cast < Action * > ( element ) );
            char action = dynamic_cast < Action * > ( element )->get_action();

            assert ( dynamic_cast < Number * > ( stack.top() ) );
            int y = dynamic_cast < Number * > ( stack.top() )->get_number();
            stack.pop();

            assert ( dynamic_cast < Number * > ( stack.top() ) );
            int x = dynamic_cast < Number * > ( stack.top() )->get_number();

            int result = 0;
            switch ( action )
            {
            case '+': result = x + y;          break;
            case '-': result = x - y;          break;
            case '*': result = x * y;          break;
            case '/': if ( y ) result = x / y; break;
            }
            dynamic_cast < Number * > ( stack.top() )->set_number ( result );
        }
    }
    assert ( dynamic_cast < Number * > ( stack.top() ) );
    return dynamic_cast < Number * > ( stack.top() )->get_number();
}
