#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <vector>
#include <stdlib.h>
#include <functional>

template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    for (unsigned long i = vector.size()-1; i > 0; i--)
    {
        for (unsigned long j = 0; j < i; j++)
        {
            if (comp(vector[j+1], vector[j]))
            {
                std::swap(vector[j], vector[j+1]);
            }
        }
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    for (unsigned long i = 1; i < vector.size(); i++)
    {
        T tmp = vector[i];
        unsigned long j = i;
        while (j > 0)
        {
            if (comp(tmp, vector[j-1]))
            {
                vector[j] = vector[j-1];
                j--; 
            }
            else
            {
                break;
            } 
        }
        vector[j] = tmp; 
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    for (unsigned long i = 0; i < vector.size()-1; i++)
    {
        unsigned long least = i;
        for (unsigned long j = i + 1; j < vector.size(); j++)
        {
            if (comp(vector[j], vector[least]))
            {
                least = j;
            }
        }
        std::swap(vector[i], vector[least]);
    }   
}

template<typename T, typename Compare>
void merge(unsigned long left, unsigned long mid, unsigned long right, std::vector<T> &vector, Compare comp= std::less<T>()) {
    unsigned long i = left;
    unsigned long j = mid+1;
    unsigned long k = 0;
    std::vector<T> tmp_vector(right-left+1);
    while (i < mid+1 && j < right+1)
    {
        if (!comp(vector[j], vector[i]))
        {
            tmp_vector[k++]=vector[i++];
        }
        else 
        {
            tmp_vector[k++]=vector[j++];
        }
    }
    if (i == mid + 1) 
    {
        while (j < right+1)
        {
            tmp_vector[k++]=vector[j++];
        }
    }
    else
    {
        while (i < mid+1)
        {
            tmp_vector[k++]=vector[i++];
        }
    }
    for (unsigned long l = left; l < right+1; l++)
    {
        vector[l] = tmp_vector[l-left];
    }
}

template<typename T, typename Compare>
void merge_sort_helper(unsigned long left, unsigned long right, std::vector<T> &vector, Compare comp = std::less<T>()) {
    if (left >= right)
    {
        return;
    }
    unsigned long mid = (left+right)/2;
    merge_sort_helper(left, mid, vector, comp);
    merge_sort_helper(mid+1, right, vector, comp);
    merge(left, mid, right, vector, comp);
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    merge_sort_helper(0, vector.size()-1, vector, comp);
}

template<typename T, typename Compare>
unsigned long partition_extra(unsigned long left, unsigned long right, std::vector<T> &vector, Compare comp = std::less<T>()) {
    std::vector<T> tmp_vector(right-left+1);
    unsigned long tmp_left = 0;
    unsigned long tmp_right = right-left;
    for (unsigned long i = left; i <= right-1; i++)
    {
        if (comp(vector[i], vector[left-1]))
        {
            tmp_vector[tmp_left++] = vector[i];
        }
        else 
        {
            tmp_vector[tmp_right--] = vector[i];
        }
    }
    tmp_vector[tmp_left] = vector[left-1];
    for (unsigned long i = left-1; i < right; i++)
    {
        vector[i] = tmp_vector[i-left+1];
    }
    return left+tmp_left;
}

template<typename T, typename Compare>
unsigned long partition_inplace(unsigned long left, unsigned long right, std::vector<T> &vector, Compare comp = std::less<T>()) {
    unsigned long i = left;
    unsigned long j = right-1;
    while (1)
    {
        while (comp(vector[i], vector[left-1]))
        {
            i++;
        }
        while (comp(vector[left-1], vector[j]))
        {
            j--;
        }
        if (i>j)
        {
            break;
        }
        std::swap(vector[i], vector[j]);
        i++;
        j--;
    }
    std::swap(vector[left-1], vector[j]);
    return j+1;
}

template<typename T, typename Compare>
void quick_sort_helper(bool inplace, unsigned long left, unsigned long right, std::vector<T> &vector, Compare comp = std::less<T>()) {
    unsigned long pivotat;
    if (left >= right) 
    {
        return;
    }
    if (inplace==true)
    {
        pivotat = partition_inplace(left, right, vector, comp);
    }
    else 
    {
        pivotat = partition_extra(left, right, vector, comp);
    }
    quick_sort_helper(inplace, left, pivotat-1, vector, comp);
    quick_sort_helper(inplace, pivotat+1, right, vector, comp);
}

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    quick_sort_helper(0, 1, vector.size(), vector, comp);
}
template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = std::less<T>()) {
    // TODO: implement
    quick_sort_helper(1, 1, vector.size(), vector, comp);
}

#endif //VE281P1_SORT_HPP