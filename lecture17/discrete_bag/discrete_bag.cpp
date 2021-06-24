#include "discrete_bag.h"

int discrete_bag ( const std::vector < std::pair < int, int > > &items, int bag_mass )
{
    std::vector < std::vector < int > > cost;
    unsigned int max_item_index = static_cast < unsigned > ( items.size() + 1 );
    unsigned int max_mass_index = static_cast < unsigned > ( bag_mass + 1 );

    cost.resize ( max_item_index );
    for ( auto &element : cost )
        element.resize ( max_mass_index );

    for ( size_t i = 1; i < max_item_index; ++i )
    {
        for ( size_t m = 1; m < max_mass_index; ++m )
        {
            unsigned item_mass = static_cast < unsigned > ( items[i - 1].first );
            int     item_value = items[i - 1].second;

            if ( item_mass <= m )
                cost[i][m] = Common::max ( cost[i - 1][m - item_mass] + item_value, cost[i - 1][m] );
            else
                cost[i][m] = cost[i - 1][m];
        }
    }

    return cost[max_item_index - 1][max_mass_index - 1];
}
