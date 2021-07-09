#include "binary_search4.h"

namespace Binary_search4 {
    int left_boundary(const int* a, int length, int item) {
        int left = -1;
        int right = length;

        while (left < right - 1) {
            int middle = (left + right) / 2;
            
            if (a[middle] < item)
                left = middle;
            else
                right = middle;
        }

        return left;
    }
    int right_boundary(const int* a, int length, int item) {
        int left = -1;
        int right = length;

        while (left < right - 1) {
            int middle = (left + right) / 2;

            if (a[middle] > item)
                right = middle;
            else
                left = middle;
        }

        return right;
    }

}

bool binary_search4(const int* a, int length, int item, int& left_out, int& right_out) {
    left_out = Binary_search4::left_boundary(a, length, item);
    right_out = Binary_search4::right_boundary(a, length, item);
    
    return (right_out - left_out) > 1;
}
