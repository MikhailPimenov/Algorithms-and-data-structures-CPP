#include "adjacency_matrix.h"

void allocate_all ( int *&matrixOut, char *&vertexesOut, int *&indexesOut, int m_vertexes, int n_edges )
{
    vertexesOut = new char[static_cast < unsigned > ( m_vertexes )];
    indexesOut  = new int[static_cast < unsigned > ( n_edges )];
    matrixOut   = new int[static_cast < unsigned > ( ( m_vertexes + 1 ) * ( m_vertexes + 1 ) )];
    for ( int index = 0; index < ( m_vertexes + 1 ) * ( m_vertexes + 1 ); ++index )
        matrixOut[index] = 0;
}
int find_vertex ( const char *vertexes, int length, char vertex )
{
    for ( int index = 0; index < length; ++index )
    {
        if ( vertexes[index] == vertex )
            return index;
    }
    return -1;
}
int get_index ( const int *indexes, const char *vertexes, int length, char vertex )
{
    return indexes[find_vertex ( vertexes, length, vertex )];
}
int adjacency_matrix_allocating ( int *&matrixOut, char *&vertexesOut, int *&indexesOut )
{
    int m = 0;
    int n = 0;

    std::cout << "Enter number of vertexes: ";
    std::cin >> m;

    std::cout << "\nEnter number of edges: ";
    std::cin >> n;
    std::cin.ignore ( 32678, '\n' );

    allocate_all ( matrixOut, vertexesOut, indexesOut, m, n );

    std::cout << "Enter all edges (A B): \n";
    int vertex_index = 0;
    for ( int i = 0; i < n; ++i )
    {
        char edge[4];
        std::cin.getline ( edge, 4 );

        if ( find_vertex ( vertexesOut, vertex_index, edge[0] ) == -1 )
        {
            vertexesOut[vertex_index] = edge[0];
            indexesOut[vertex_index] = vertex_index + 1;
            ++vertex_index;
        }
        int v1_index = get_index ( indexesOut, vertexesOut, vertex_index, edge[0] );

        if ( find_vertex ( vertexesOut, vertex_index, edge[2] == -1 ) )
        {
            vertexesOut[vertex_index] = edge[2];
            indexesOut[vertex_index] = vertex_index + 1;
            ++vertex_index;
        }
        int v2_index = get_index ( indexesOut, vertexesOut, vertex_index, edge[2] );

        if ( v1_index != -1 && v2_index != -1 )
        {
            matrixOut[v1_index + v2_index * ( m + 1 )] += 1;
            matrixOut[v2_index + v1_index * ( m + 1 )] += 1;
        }
    }

    return m + 1;
}
