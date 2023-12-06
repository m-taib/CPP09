#include "PmergeMe.hpp"
#include <algorithm>
#include <ostream>
#include <vector>

int     comp_num;

PmergeMe::PmergeMe()
{
    num_of_elements = 1;
    comp_num = 0;
    rest = -1;
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
        comp_num++;
	    if (it->back() < begin->back())
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
	vect_int::iterator it;
    
    int i = -1;
    int j = -1;

	while (++i < (int)v.size())
	{
		it = begin->begin();
        j = -1;
		while (++j < (int)begin->size())
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
    /// ask if its in class or not

    // if (pend.back() <= main_chain.back())
    //     {
    //         std::cout << pend.back() << "-" << main_chain.back() << std::endl;
    //         return (1);
    //     }
    // std::cout << "not inserted" << std::endl;
    comp_num++;
    return (main_chain.back() < pend.back());
}

void    PmergeMe::update_iterators(pend_vec::iterator begin)
{
    pend_vec::iterator end = _pend.end();

    while (begin != end)
    {
        begin->second++;
        begin++;
    }
}
int     PmergeMe::getComparisonsNum() const
{
    return (comp_num);
}

void    PmergeMe::insert_pend_to_chain()
{
    pend_vec::iterator begin = _pend.begin();
    pend_vec::iterator end = _pend.end();
    std::vector<vect_int>::iterator it;

    while (begin != end)
    {   
        it = std::lower_bound(_main_chain.begin(), begin->second, begin->first, compare);
        _main_chain.insert(it, begin->first);
        
        update_iterators(begin + 1);
        begin++;
    }

}
    
void    PmergeMe::insertion_sort(vect_int& data)
{
    std::vector<vect_int> v;
    vect_int temp;
    std::vector<vect_int>::iterator it;
    std::vector<vect_int>::iterator tmp;

    v = make_pairs(data);
    
    _main_chain.clear();
    _pend.clear();
    _main_chain.reserve(v.size());
    
    it = v.begin();
    if ((int)v.back().size() != num_of_elements)
    {
        temp = v.back();
        v.pop_back();
    }

    _main_chain.push_back(*(it++));
    _main_chain.push_back(*(it++));

    while (it != v.end())
    {
        if (it + 1 == v.end())
        {
            _pend.push_back(make_pair(*(it), _main_chain.end())); 
            break ; 
        }
        tmp = _main_chain.insert(_main_chain.end(), *(it + (it + 1 != v.end())));
        if (it + 1 != v.end())
            _pend.push_back(make_pair(*(it), tmp));  
        it += 2;
    }
    // if (num_of_elements == 1 && rest != -1)
    // {  
    //     vect_int v2(1, rest);
    //     _pend.push_back(make_pair(v2, _main_chain.end()));
    // }
    insert_pend_to_chain();
    // std::cout << "*****MAIN CHAIN*****\n";
    // print_pairs(_main_chain);
    // std::cout << "*****END CHAIN*****\n";
    // insert pend to chain 
    // insert last element

    // when u test with a fixed range u have to update iterator of pend elements 
        // if it have a pos >= inserted position  u have to decale it by 1
    
    copy_elements_to_data(data, _main_chain);
     
    num_of_elements /= 2;
}

/*
 * make_pairs : create vector of vectors, every vector has n elements depends on num of elements must have of every call
 * sort_pairs : compare elements of every pair : compare last element of every one
 * copy_to_original_data : copy elements to the original data to process it again 
 * if we dont have a pair of elements then we stop 
 *
 *
*/
void    PmergeMe::merge_sort(vect_int& data)
{
    std::vector<vect_int> v;
    
  
    v = make_pairs(data);

   
    if (data.size() % 2 && rest == -1)
    {
        std::cout << "rr" << std::endl;
        rest = data.back();
        data.pop_back();
    }


    sort_pairs(v);
    copy_elements_to_data(data, v);
 
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
