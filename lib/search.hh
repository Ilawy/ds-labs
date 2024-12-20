#include <type_traits>
#include <iostream>
#include "linked_list.hh"

namespace dst
{
    namespace search
    {
        template <typename T>
        int linear(T data[], int length, T target);
        template <typename T>
        dst::list::LinkedList<int> &linearMany(T data[], int length, T target);

        template <typename T>
        int linear(T data[], int length, T target)
        {
            int iters = 0;
            // static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type");
            for (int i = 0; i < length; i++)
            {
                iters++;
                if (data[i] == target)
                {
                    std::cout << "Linear search finished after " << iters << " on array of " << length << " elements" << std::endl;
                    return i;
                }
            }
            std::cout << "Linear search finished after " << iters << " on array of " << length << " elements (target not found)" << std::endl;
            return -1;
        }

        template <typename T>
        dst::list::LinkedList<int> &linearMany(T data[], int length, T target)
        {
            dst::list::LinkedList<int> *result = new dst::list::LinkedList<int>;

            // static_assert(std::is_arithmetic<T>::value, "Not an arithmetic type");
            for (int i = 0; i < length; i++)
            {
                if (data[i] == target)
                {
                    result->add(i);
                }
            }
            return *result;
        }

        template <typename T>
        int binary(T data[], int size, T target)
        {
            int left = 0,
                right = size - 1,
                iters = 0;
            if (target < data[left] || target > data[right])
                return -1;
            while (left <= right)
            {
                iters++;
                int middle = (left + right) / 2;
                if (data[middle] == target)
                {
                    std::cout << "Binary search found the target at index " << middle << " after " << iters << " iteration(s) with data of size " << size << std::endl;
                    return middle;
                }
                else if (data[middle] < target)
                {
                    left = middle + 1;
                }
                else
                {
                    right = middle - 1;
                }
            }
            std::cout << "Binary search did NOT found the target after " << iters << " iteration(s) with data of size " << size << std::endl;
            return -1;
        }
    } // namespace search

} // namespace dst
