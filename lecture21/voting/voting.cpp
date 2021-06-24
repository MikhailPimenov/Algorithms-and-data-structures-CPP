#include "voting.h"

int get_size ( const std::string &stream, int &indexOut )
{
    std::size_t index = 0;

    while ( stream[index] != ' ' && index < stream.size() )
        ++index;

    std::string number ( stream, 0, index );
    ++index;
    indexOut = static_cast < signed > ( index );

    std::stringstream sstream;
    sstream << number;

    int result = 0;
    sstream >> result;


    return result;
}

void get_candidate ( const std::string &stream, std::string &candidate, int &indexInOut )
{
    std::size_t index = static_cast < unsigned > ( indexInOut );

    while ( stream[index] != ' ' && index < stream.size() )
        ++index;

    std::size_t length = index - static_cast < unsigned > ( indexInOut );

    candidate = std::string ( stream, static_cast < unsigned > ( indexInOut ), length );
    indexInOut = static_cast < signed > ( index + 1 );
}

void voting ( const std::string &stream, std::unordered_map < std::string, int > &dbOut )
{
    int start_index = 0;
    get_size ( stream, start_index );

    int index = start_index;
    while ( static_cast < unsigned > ( index ) < stream.size() )
    {
        std::string candidate;
        get_candidate ( stream, candidate, index );

        if ( dbOut.find ( candidate ) == dbOut.cend() )
            dbOut.insert ( std::pair < std::string, int > ( candidate, 1 ) );
        else
            dbOut[candidate] += 1;
    }
}
