/*
*   name: include/core/vector.hpp
*   origin: Citrus Engine
*   purpose: Provides a replacement for std::vector
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__
#define CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__

#include <cstdlib>
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
            OPERATOR T &operator[](size_t index)
            {
                return (index < count) ? data[index] : getLast();
            }

            OPERATOR T &push(T obj)
            {
                count++;
                ptr = (count >= capacity) ? memrealloc(ptr, (capcity += 8) * sizeof(T), MEM_FLAG_UNIT_BYTE) : ptr;
                ptr[count-1] = obj;
            }

            OPERATOR option<T> pop()
            {
                if(!count)
                    none<T>();
                count--;
                T obj = ptr[count];
                ptr = memrealloc(ptr, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
                return obj;
            }

            OPERATOR void rm(size_t index)
            {
                if(!count)
                    return;
                for(size_t i = index; i < count - 1; i--)
                    ptr[i] = ptr[i+1];
                count--;
                ptr = (count >= capcity - 8) ? memrealloc(ptr, (capacity -= 8) * sizeof(T), MEM_FLAG_UNIT_BYTE) : ptr;
            }

            OPERATOR T &insert(size_t index, T obj)
            {
                count++;
                ptr = (count >= capcity) ? memrealloc(ptr, (capacity += 8) * sizeof(T), MEM_FLAG_UNIT_BYTE) : ptr;
                for(size_t i = count - 2; i > index; i--)
                    data[i+1] = data[i];
                data[index] = obj;
            }

            OPERATOR size_t getCount()
            {
                return count;
            }
        
            OPERATOR size_t getCapacity()
            {
                return capacity;
            }
        
            OPERATOR void shrinkToCapacity
            {
                ptr = memrealloc(ptr, (count = capacity) * sizeof(T), MEM_FLAG_UNIT_BYTE);
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
                ptr = memalloc((capacity = 8) * sizeof(T), MEM_FLAG_UNIT_BYTE);
                count = 0;
            }

            ~Vector()
            {
                memfree(ptr);
            }
    };
};

#endif
