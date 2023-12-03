#include "PmergeMe.hpp"
#include <vector>

PmergeMe::PmergeMe()
{
    num_of_elements = 2;
}
PmergeMe::PmergeMe(const PmergeMe& rhs)
{
    (void)rhs;
}

PmergeMe&   PmergeMe::operator=(const PmergeMe& rhs)
{
    (void)rhs;
    return (*this);
}

void      print_pairs(std::vector<vect_int >& v)
{
    std::vector<vect_int >::iterator begin = v.begin();
    std::vector<vect_int >::iterator end = v.end();
    vect_int::iterator it;

    while (begin != end)
    {
        it = (begin->begin());
        while (it != (begin->end()))
        {
            std::cout << *it << std::endl;
            it++;
        }
        begin++;
    }
}
std::vector<vect_int> PmergeMe::make_pairs(vect_int& data)
{
    std::vector<vect_int > v;
    vect_int v2;
    vect_int::iterator begin = data.begin();
    vect_int::iterator end = data.end();
    int     i;
    
    while (begin != end)
    {
        v2.clear();
        i = -1;
        while (++i < num_of_elements)
        {
            v2.push_back(*begin);
            begin++;
        }
        v.push_back(v2);
    }
    print_pairs(v);
    return (v);
}
void    PmergeMe::sort_pairs(std::vector<vect_int>& __unused v)
{
    
}
void    PmergeMe::copy_elements_to_data(vect_int& __unused data, std::vector<vect_int>& __unused v)
{

}

void    PmergeMe::merge_sort(vect_int& data)
{
    std::vector<vect_int> v;

    v = make_pairs(data);
    // sort_pairs(v);
    // copy_elements_to_data(data, v);
    // if (v.size() < 2)
    //     return ;
    // num_of_elements *= 2;
    // merge_sort(data);
}

PmergeMe::~PmergeMe()
{
    
}