#include "PmergeMe.hpp"
#include <vector>

int     main()
{
    int arr[] = { 10, 20, 30 , 40, 50 , 60};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    std::vector<int> v(arr, arr + n);
    
    PmergeMe a;
    a.make_pairs(v);
}