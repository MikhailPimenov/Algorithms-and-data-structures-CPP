#include "adjacency_lists.h"

void get_lengths ( int &m_vertexesOut, int &n_edgesOut )
{
    std::string lengths;
    std::cout << "Enter number of vertexes and number of edges (m n): ";
    std::getline ( std::cin, lengths );

    std::size_t index = 0;
    while ( lengths[index] != ' ' && index < lengths.size() )
        ++index;

    std::string vertexes ( lengths, 0, index );
    std::string edges ( lengths, index + 1, lengths.size() - index - 1 );

    std::stringstream sstream;

    sstream << vertexes;
    sstream >> m_vertexesOut;
    sstream.clear();

    sstream << edges;
    sstream >> n_edgesOut;
}
void adjacency_lists ( std::unordered_map < char, std::unordered_set < char > > &adjacency_lists )
{
    int m = 0;
    int n = 0;
    get_lengths ( m, n );

    std::cout << "Enter all edges (A B): \n";
    for ( int index = 0; index < n; ++index )
    {
        std::string edge;
        std::getline ( std::cin, edge );

        for ( std::size_t k = 0; k < 3; k += 2 )
        {
            if ( adjacency_lists.find ( edge[k] ) == adjacency_lists.cend() )
                adjacency_lists.insert ( std::make_pair ( edge[k], std::unordered_set < char > () ) );
            adjacency_lists[edge[k]].insert ( edge[( k + 2 ) % 4] );
        }
    }
}
