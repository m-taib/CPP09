#include "PmergeMe.hpp"
#include <algorithm>
#include <ostream>
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

	while (data_begin != data_end && begin != v.end())
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

bool    compare(const vect_int& main_chain, const vect_int& pend) 
{
    return (pend.back() < main_chain.back());
}

void    PmergeMe::insert_pend_to_chain(std::vector<vect_int>& main_chain, pend_vec& pend)
{
    pend_vec::iterator begin = pend.begin();
    pend_vec::iterator end = pend.end();
    std::vector<vect_int>::iterator it;
    
    while (begin != end)
    {
        it = std::lower_bound(main_chain.begin(), main_chain.end(), begin->first, compare);
        main_chain.insert(it, begin->first);
        begin++;
    }
}
    
void    PmergeMe::insertion_sort(vect_int& data)
{
    std::vector<vect_int> v;
    std::vector<vect_int> main_chain;
    std::vector<vect_int>::iterator it;
    std::vector<vect_int>::iterator tmp;

    pend_vec    pend;
    pend_vec::iterator i;
    v = make_pairs(data);

    it = v.begin();
    main_chain.reserve(data.size());
    main_chain.push_back(*(it++));
    main_chain.push_back(*(it++));

    while (it != v.end())
    {
        tmp = main_chain.insert(main_chain.end(), *(it + (it + 1 != v.end())));
        if (it + 1 != v.end())
            pend.push_back(make_pair(*(it), tmp));  
        else 
            break ;   
        it += 2;
    }
    // print_pairs(main_chain);
    
    insert_pend_to_chain(main_chain, pend);
    i = pend.begin();
    std::cout << "PEND" << std::endl;
    while (i != pend.end())
    {
        vect_int::iterator t = i->first.begin();
        while (t != i->first.end())
        {
            std::cout << *t << " ";
            t++;
        }
        std::cout << std::endl;
        i++;
    }
    std::cout << "******END*******" << std::endl;
    
    // insert pend to chain 
    // insert last element

    // when u test with a fixed range u have to update iterator of pend elements 
        // if it have a pos >= inserted position  u have to decale it by 1
    // std::cout << "\n";
    copy_elements_to_data(data, main_chain);
    num_of_elements /= 2;
}

void    PmergeMe::merge_sort(vect_int& data)
{
    std::vector<vect_int> v;
    
    v = make_pairs(data);
    // print_pairs(v);
    sort_pairs(v);
    copy_elements_to_data(data, v);
    // std::cout << "\n";
    // print_pairs(v);
    if (v.size() >= 4) //size ) 
    {
        //insert
        
        //make_pairs
        //main chain pend;
        num_of_elements *= 2;
        merge_sort(data);
        //copy
        //elmn_size /= 2;
    }
    insertion_sort(data);
    // print_pairs(v);
    // std::cout << "\n";
    // std::cout << "original vector" << std::endl;
    //vect_int::iterator it = data.begin();
    /*while (it != data.end())
    {
	std::cout << *it << std::endl;
	it++;
    }*/	    
   
}

PmergeMe::~PmergeMe()
{
    
}
