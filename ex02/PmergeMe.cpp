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
	// vect_int::iterator data_end = data.end();
	vect_int::iterator it;
    // std::cout << "main chain" << std::endl;
    // print_pairs(v);
    int i = -1;
    int j = -1;

    // std::cout << "******MAIN CHAIN*******" << std::endl;
	while (++i < (int)v.size())
	{
		it = begin->begin();
        j = -1;
		while (++j < (int)begin->size())
		{
            // std::cout << "num : " << *it << ", ";
			*data_begin = *it;
			it++;
			data_begin++;
		}
        // std::cout << std::endl;
		begin++;
	}
    // std::cout << "******END CHAIN*******" << std::endl;

    // std::cout << "**********" << std::endl;

    // int		j = -1;
    // std::cout << "original vector" << std::endl;
    
    // while (++j < (int)v.size())
    // {
	//     std::cout << data[j] << std::endl;
    // }
    // std::cout << "************" << std::endl;
}

bool    compare(const vect_int& main_chain, const vect_int& pend) 
{
    if (pend.back() < main_chain.back())
        {
            std::cout << pend.back() << "-" << main_chain.back() << std::endl;
            return (1);
        }
    std::cout << "not inserted" << std::endl;
    return (0);
}

void    PmergeMe::insert_pend_to_chain(std::vector<vect_int>& main_chain, pend_vec& pend)
{
    pend_vec::iterator begin = pend.begin();
    pend_vec::iterator end = pend.end();
    std::vector<vect_int>::iterator it;

    std::cout << "----before isertion-----" << std::endl;
    std::cout << "******MAIN CHAIN*******" << std::endl;
    print_pairs(main_chain);
    std::cout << "*********END CHAIN***********" << std::endl;
    pend_vec::iterator i;
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
    std::cout << "*****END PEND*****" << std::endl;

    while (begin != end)
    {
        it = std::lower_bound(main_chain.begin(), main_chain.end(), begin->first, compare);
        
        main_chain.insert(it, begin->first);
       
        if (it != main_chain.end())
        {
            std::cout << "******MAIN CHAIN*******" << std::endl;
            print_pairs(main_chain);
            std::cout << "*********END***********" << std::endl;
        }
         exit(0);
        begin++;
    }
    std::cout <<  std::endl;

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
    // int j= 1;
    // it = v.begin();
    // if (v.size() == 8 || v.size() == 4)
    // {
    //     while (it < v.end())
    //     {
    //         std::cout << (*it).back() << " " << std::endl;
    //         it++;
    //     }
    // }
    // std::cout << std::endl;
    it = v.begin();

    // //back to it
    //      main_chain.reserve(v.size());
    // std::cout << v.size() << std::endl;
    main_chain.push_back(*(it++));
    main_chain.push_back(*(it++));
    // std::cout << "******MAIN CHAIN*******" << std::endl;
    // print_pairs(main_chain);
    // std::cout << "******END**************" << std::endl;
    // // print_pairs(main_chain);
    while (it != v.end())
    {
        tmp = main_chain.insert(main_chain.end(), *(it + (it + 1 != v.end())));
        if (it + 1 != v.end())
        {
            pend.push_back(make_pair(*(it), tmp));  
        }
        else 
        {
            break ;   
        }
        it += 2;
    }
    // std::cout << "******MAIN CHAIN*******" << std::endl;
    // print_pairs(main_chain);
    // // std::cout << "size of main chain : " << main_chain.size() << std::endl;
    // std::cout << "*********END***********" << std::endl;
    // exit(0);
    
    insert_pend_to_chain(main_chain, pend);
    std::cout << "----after isertion-----" << std::endl;
    std::cout << "******MAIN CHAIN*******" << std::endl;
    print_pairs(main_chain);
    // std::cout << "size of main chain : " << main_chain.size() << std::endl;
    std::cout << "*********END***********" << std::endl;
    // i = pend.begin();
    // std::cout << "PEND" << std::endl;
    // while (i != pend.end())
    // {
    //     vect_int::iterator t = i->first.begin();
    //     while (t != i->first.end())
    //     {
    //         std::cout << *t << " ";
    //         t++;
    //     }
    //     std::cout << std::endl;
    //     i++;
    // }
    // std::cout << "******END*******" << std::endl;
    
    // insert pend to chain 
    // insert last element

    // when u test with a fixed range u have to update iterator of pend elements 
        // if it have a pos >= inserted position  u have to decale it by 1
    // std::cout << "\n";
    // std::cout << "insertion : " << std::endl;
    
    copy_elements_to_data(data, main_chain);
    
    // vect_int::iterator t = data.begin();
    // std::cout << "original vector" << std::endl;
    // while (t < data.end())
    // {
    //     std::cout << *t << std::endl;
    //     t++;
    // }
    // std::cout << "end vector" << std::endl;
    // std::cout << "end insertion" << std::endl;
    num_of_elements /= 2;
    // std::cout << "size of element : " << num_of_elements << std::endl;
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
