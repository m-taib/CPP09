#include "PmergeMe.hpp"
#include <vector>

int     main()
{
    int arr[] = { 40, 30, 10 , 20, 50 , 60, 23, 18};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    std::vector<int> v(arr, arr + n);
    
    PmergeMe a;
    // int		i = -1;
    // std::cout << "original vector before : " << std::endl;
    
    // while (++i < (int)v.size())
    // {
	//     std::cout << v[i] << " ";
    // }
    // std::cout << std::endl;
    a.merge_sort(v);
    // i = -1;
    // std::cout << "original vector after :" << std::endl;
    
    // while (++i < (int)v.size())
    // {
	//     std::cout << v[i] << " ";
    // }
}
