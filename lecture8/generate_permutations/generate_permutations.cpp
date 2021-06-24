#include "generate_permutations.h"

void printPermutation ( const int *permutation, int permutation_length )
{
    for ( int index = 0; index < permutation_length; ++index )
    {
        if ( permutation + index )
            std::cout << permutation[index] << ' ';
        else
            return;
    }
    std::cout << '\n';
}
bool find ( const int *array, int length, int element )
{
    for ( int index = 0; index < length; ++index )
    {
        if ( array + index )
        {
            if ( array[index] == element )
                return true;
        }
        else
            break;
    }
    return false;
}
void _generate_permutations ( const int *elements, int *usedElementsIndexes, int length, int *permutation, int initial_permutation_length, int permutation_length_decreasing, int permutation_length )
{
    if ( permutation_length < permutation_length_decreasing + 1 )
    {
        printPermutation ( permutation, initial_permutation_length - permutation_length_decreasing );
        return;
    }

    for ( int indexOfElement = 0; indexOfElement < length; ++indexOfElement )
    {
        if ( ! find ( usedElementsIndexes, initial_permutation_length - permutation_length, indexOfElement ) )//FIXME
        {
            permutation[initial_permutation_length - permutation_length] = elements[indexOfElement];
            usedElementsIndexes[initial_permutation_length - permutation_length] = indexOfElement;
            _generate_permutations ( elements, usedElementsIndexes, length, permutation,
                                     initial_permutation_length,
                                     permutation_length_decreasing, permutation_length - 1 );
        }
        else
            _generate_permutations ( elements, usedElementsIndexes, length, permutation,
                                     initial_permutation_length,
                                     permutation_length_decreasing + 1, permutation_length );
    }
}
void generate_permutations ( const int *elements, int length, int max_permutation_length )
{
    int *permutation = new int[static_cast < unsigned > ( max_permutation_length )];
    int *usedElementsIndexes = new int[static_cast < unsigned > ( max_permutation_length )];

    _generate_permutations ( elements, usedElementsIndexes, length, permutation, max_permutation_length, 0, max_permutation_length );

    delete [] usedElementsIndexes;
    delete [] permutation;
}
