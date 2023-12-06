#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void    merge(std::vector<int>& left_part, std::vector<int>& right_part, std::vector<int>& v);


void    print(std::vector<int>& left_part, std::vector<int>& right_part)
{
    int     i;

    std::cout << "|";
    i = -1;
    while (++i < left_part.size())
    {
        std::cout << left_part[i] << "|" ;
    }
    std :: cout << "\t" ;
    std::cout << "|";
    i = -1;
    while (++i < right_part.size())
    {
        std::cout << right_part[i] << "|" ;
    }
}

void    divide(std::vector<int>& v)
{
    if (v.size() <= 1)
        return ;

    int     middle = v.size() / 2;
   
    std::vector<int> left_part;
    std::vector<int> right_part;
 
    left_part.reserve(middle);
    right_part.reserve(v.size() - middle);

    int     i = 0;
    while (i < v.size())
    {
        if (i < middle)
        {
            left_part.push_back(v[i]);
        }
        else {
            right_part.push_back(v[i]);
        }
        i++;
    }
    // print(left_part, right_part);
    divide(left_part);
    divide(right_part);
    merge(left_part, right_part, v);
}

void    merge(std::vector<int>& left_part, std::vector<int>& right_part, std::vector<int>& v)
{
    int     i;
    int     r;
    int     l;
    int     left_size;
    int     right_size;

    left_size = v.size() / 2;
    right_size = v.size() - left_size;
    i = 0;
    l = 0;
    r = 0;
    while (l < left_size && r < right_size)
    {
        if (left_part[l] < right_part[r])
        {
            v[i] = left_part[l];
            l++;
        }
        else 
        {
            v[i] = right_part[r];
            r++;
        }
        i++;
    }
    while (l < left_size)
    {
        v[i++] = left_part[l++];
    }
    while (r < right_size)
    {
        v[i++] = right_part[r++];
    }
}

bool    compare(int a, int b)
{
    if (b >= a)
        return true;
    return false;
}
int main()
{
    int arr[] = { 1, 2,3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    std::vector<int> v(arr, arr + n);
    // divide(v);
    // std::vector<int>::iterator it = v.begin();
    // while (it != v.end())
    // {
    //     std::cout << *it << " ";
    //     it++;
    // }
    std::vector<int>::iterator it = v.begin();
    // it++;
    // v.erase(it);
    //  std::vector<int>::iterator i = v.begin();
    // while (i != v.end())
    // {
    //     std::cout << *i << " ";
    //     i++;
    // }
    it = std::lower_bound(v.begin(), v.end(), 6, compare);
    std::cout << *it << std::endl;
}