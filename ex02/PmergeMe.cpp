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

void    PmergeMe::sort_each_pair(std::vector<vect_int>& v)
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
	    if ((int)it->size() == num_of_elements 
              && it->back() < begin->back())
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
    comp_num++;
    return (main_chain.back() <= pend.back());
}

void    PmergeMe::update_iterators(pend_vec::iterator begin, std::vector<vect_int>::iterator pos)
{
    pend_vec::iterator end = _pend.end();

    while (begin != end)
    {
        if (begin->second >= pos)
        {
            begin->second++;
        }
        begin++;
    }
}

void    PmergeMe::insert_pend_to_chain()
{
    pend_vec::iterator begin = _pend.begin();
    std::vector<vect_int>::iterator it;
    
    long int     jacob_sthal[] = { 
	   2, 2, 6, 10, 22, 42, 86, 170, 342, 682, 1366,
        2730, 5462, 10922, 21846, 43690, 87382, 174762, 349526, 699050,
        1398102, 2796202, 5592406, 11184810, 22369622, 44739242, 89478486,
        178956970, 357913942, 715827882, 1431655766, 2863311530, 5726623062,
        11453246122, 22906492246, 45812984490 };

   int		i = 0;
    // int     j = -1;
    
    // with jacob sthal number we will what we have to push first 
    // we will push more than 1 element at time
    	// from end to begin

    while (_pend.size())
    {  
        begin = _pend.begin();
        begin += (jacob_sthal[i] - 1);
        if (begin >= _pend.end())
            begin = _pend.end() - 1;
        while (true)
        {
            it = std::lower_bound(_main_chain.begin(), begin->second, 
            begin->first, compare);
            _main_chain.insert(it, begin->first);
            _pend.erase(begin);
            update_iterators(_pend.begin(), it);
            if (begin == _pend.begin())
                break ;
            begin--;
        }
        i++;
    }

}

// void    PmergeMe::insert_pend_to_chain()
// {
//     pend_vec::iterator begin = _pend.begin();
//     pend_vec::iterator end = _pend.end();
//     std::vector<vect_int>::iterator it;
    
//     while (begin != end)
//     {   
//         it = std::lower_bound(_main_chain.begin(), begin->second, begin->first, compare);
//         _main_chain.insert(it, begin->first);
//         update_iterators(begin + 1, it);
//         begin++;
//     }

// }

int     PmergeMe::getComparisonsNum() const
{
    return (comp_num);
}


    
void    PmergeMe::insertion_sort(vect_int& data)
{
    std::vector<vect_int> v;
    vect_int temp;
    std::vector<vect_int>::iterator it;
    std::vector<vect_int>::iterator tmp;
    int     i = -1;
    // int     j = -1;
    
    v = make_pairs(data);

    // std::cout << "element size : " << num_of_elements << std::endl;
    // std::cout << "BEFORE INSERTION TO MAIN CHAIN" << std::endl;

    // while (++i < (int)v.size())
    // {
    //     j = -1;
    //     while (++j < (int)v[i].size())
    //     {
    //         std::cout << v[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "*******************************" << std::endl;

    _main_chain.clear();
    _pend.clear();
    _main_chain.reserve(v.size());
    
    
    
    // std::cout << std::endl;
    // std::cout << std::endl;

    temp.clear();
    if ((int)v.back().size() != num_of_elements)
    {
        temp = v.back();
        v.pop_back();
    }
    it = v.begin();

    while (it != v.end() && ++i < 2)
        _main_chain.push_back(*(it++));
    while (it != v.end())
    {
        if (it + 1 == v.end())
        {
            _pend.push_back(make_pair(*(it), _main_chain.end())); 
            break ; 
        }
        tmp = _main_chain.insert(_main_chain.end(), *(it + 1));
        _pend.push_back(make_pair(*(it), tmp));  
        it += 2;
    }
    insert_pend_to_chain();
    
    if (temp.size())
        {
            // it = std::lower_bound(_main_chain.begin(), _main_chain.end(), temp , compare);
            _main_chain.insert(_main_chain.end(), temp);
        }

    // std::cout << "******* MAIN CHAIN**********" << std::endl;
    // print_pairs(_main_chain);
    // std::cout << "******* END CHAIN**********" << std::endl;
    // std::cout << std::endl;

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

    // std::cout << "BEFORE SORT" << std::endl;
    // print_pairs(v);
    // std::cout << "***********" << std::endl;
    sort_each_pair(v);
    // std::cout << "AFTER SORT" << std::endl;
    // print_pairs(v);
    // std::cout << "***********" << std::endl;

    copy_elements_to_data(data, v);
    if (v.size() >= 4 || (int)v.back().size() == num_of_elements) 
    {
        num_of_elements *= 2;
        merge_sort(data);
    }
    insertion_sort(data);
   
}

PmergeMe::~PmergeMe()
{
    
}
