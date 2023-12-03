#include "PmergeMe.hpp"
#include <vector>

PmergeMe::PmergeMe()
{
    num_of_elements = 1;
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
            std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
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
        while (begin != end && ++i < num_of_elements)
        {
            v2.push_back(*begin);
            begin++;
        }
        v.push_back(v2);
    }
    return (v);
}

void    PmergeMe::sort_pairs(std::vector<vect_int>& v)
{
    vect_int tmp;
    std::vector<vect_int>::iterator it;
    std::vector<vect_int>::iterator begin = v.begin();
    std::vector<vect_int>::iterator end = v.end();

    while (begin != end)
    {
	    if (begin + 1 == end)
		    break ;
	    it = begin;
	    ++it;
	    if (*(it->end() - 1) < *(begin->end() - 1))
	    {
		tmp = *begin;
		*begin = *it;
		*it = tmp;
	    }
            begin += 2;
    }

}
void    PmergeMe::copy_elements_to_data(vect_int& data, std::vector<vect_int>& v)
{
	std::vector<vect_int>::iterator begin = v.begin();
	vect_int::iterator data_begin = data.begin();
	vect_int::iterator data_end = data.end();
	vect_int::iterator it;

	while (data_begin != data_end)
	{
		it = begin->begin();
		while (it != begin->end())
		{
			*data_begin = *it;
			it++;
			data_begin++;
		}
		begin++;
	}

}

void    PmergeMe::merge_sort(vect_int& data)
{
    std::vector<vect_int> v;

    v = make_pairs(data);
    //print_pairs(v);
    sort_pairs(v);
    //std::cout << "\n";
   // print_pairs(v);
    copy_elements_to_data(data, v);
    //std::cout << "\n";
    //std::cout << "original vector" << std::endl;
    //vect_int::iterator it = data.begin();
    /*while (it != data.end())
    {
	std::cout << *it << std::endl;
	it++;
    }*/	    
    if (v.size() < 2)
         return ;
    num_of_elements *= 2;
    std::cout << "hh" << std::endl;
    merge_sort(data);
}

PmergeMe::~PmergeMe()
{
    
}
