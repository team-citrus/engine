/*
*   name: include/core/vector.hpp
*   origin: Citrus Engine
*   purpose: Provides a replacement for std::vector
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__
#define CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__

#include <cstddef>
#include <cstdlib>
#include <iterator>
#include "core/extensions.h"
#include "core/mem.hpp"
#include "core/option.hpp"

namespace engine
{
    template <typename T>
    class Vector
    {
        private:
            T *ptr;
            size_t count;
            size_t capacity;
        public:
            struct iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using difference_type = ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                friend bool operator== (const Vector::iterator& a, const Vector::iterator& b) { return v == v; };
                friend bool operator!= (const Vector::iterator& a, const Vector::iterator& b) { return v != v; };

                private:
                Vector<T> &v;
                ptrdiff_t diff;
            }

            OPERATOR T &operator[](size_t index)
            {
                return (index < count) ? data[index] : getLast();
            }

            OPERATOR T &push(T obj)
            {
                count++;
                ptr = (count >= capacity) ? memrealloc(ptr, (capcity += 8) * sizeof(T)) : ptr;
                ptr[count-1] = obj;
                return ptr[count-1];
            }

            OPERATOR Option<T> pop()
            {
                if(!count)
                    return none<T>();
                count--;
                T obj = ptr[count];
                ptr = memrealloc(ptr, count * sizeof(T));
                return Option::some(obj);
            }

            OPERATOR void rm(size_t index)
            {
                if(!count)
                    return;
                for(size_t i = index; i < count - 1; i--)
                    ptr[i] = ptr[i+1];
                count--;
                ptr = (count >= capcity - 8) ? memrealloc(ptr, (capacity -= 8) * sizeof(T)) : ptr;
            }

            OPERATOR T &insert(size_t index, T obj)
            {
                count++;
                ptr = (count >= capcity) ? memrealloc(ptr, (capacity += 8) * sizeof(T)) : ptr;
                for(size_t i = count - 2; i > index; i--)
                    data[i+1] = data[i];
                data[index] = obj;
                return data[index];
            }

            OPERATOR size_t getCount()
            {
                return count;
            }
        
            OPERATOR size_t getCapacity()
            {
                return capacity;
            }
        
            OPERATOR void shrinkToCapacity()
            {
                ptr = memrealloc(ptr, (capacity = count) * sizeof(T));
            }

            OPERATOR T &getLast()
            {
                if(count)
                    return data[count-1];
            }
            OPERATOR T &getFirst()
            {
                if(count)
                    return data[0];
            }

            OPERATOR T *data()
            {
                return ptr;
            }

            Vector()
            {
                ptr = memalloc((capacity = 8) * sizeof(T));
                count = 0;
            }
        
            Vector(T arr[], size_t c)
            {
                ptr = memalloc((capacity = (c % 8) ? c + c % 8 : c) * sizeof(T));
                memcpy(ptr, arr, c * sizeof(T));
            }
        
            Vector(const Vector &v)
            {
                count = v.count;
                capacity = v.capacity;
                ptr = memalloc(capacity * sizeof(T));
                memcpy(ptr, v.ptr, count);
            }

            ~Vector()
            {
                memfree(ptr);
            }
    };
    
    template<class T>
    using Vec = Vector<T>;
};

#endif
