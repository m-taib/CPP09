#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>

typedef  std::vector<int> vect_int;
typedef  std::vector< std::pair<vect_int, std::vector<vect_int>::iterator> > pend_vec;
 
class   PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& rhs);
        PmergeMe&   operator=(const PmergeMe& rhs);
        ~PmergeMe();

        void    merge_sort(std::vector<int>& data);
        std::vector<std::vector<int> >     make_pairs(std::vector<int>& data);
        void    sort_pairs(std::vector<std::vector<int> >& v);
        void    copy_elements_to_data(std::vector<int>& data, std::vector<std::vector<int> >& v);
        void    insertion_sort(vect_int& data);
        void    insert_pend_to_chain(std::vector<vect_int>& main_chain, pend_vec& pend);

    private:
        int     num_of_elements;
        std::vector<int> _v;

};
#endif