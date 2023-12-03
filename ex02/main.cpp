#include "PmergeMe.hpp"
#include <vector>

int     main()
{
    int arr[] = { 40, 30, 10 , 20, 50 , 60};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    std::vector<int> v(arr, arr + n);
    
    PmergeMe a;
    a.merge_sort(v);
    int		i = -1;
    while (++i < (int)v.size())
    {
	std::cout << v[i] << std::endl;
    }
}
