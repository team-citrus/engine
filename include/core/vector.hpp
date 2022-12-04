#ifndef CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__
#define CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__

#include <cstdlib>
#include "include/core/extensions.hpp"

namespace engine
{
    template <typename T>
    class Vector
    {
        private:
            T *data;
            int count;
        public:
            OPERATOR T &operator[](int index)
            {
                return (index < count) ? data[index] : getLast();
            }

            OPERATOR void push(T obj)
            {
                count++;
                data = realloc(data, count * sizeof(T));
                data[count-1] = obj;
            }

            OPERATOR T pop()
            {
                if(!count)
                    return;
                count--;
                T obj = data[count];
                data = realloc(data, count * sizeof(T));
                return obj;
            }

            OPERATOR void rm(int index)
            {
                if(!count)
                    return;
                for(int i = index; i < count - 1; i--)
                    data[i] = data[i+1];
                count--;
                data = realloc(data, count * sizeof(T));
            }

            OPERATOR void insert(int index, T obj)
            {
                if(!count)
                    return;
                count++;
                data = realloc(data, count * sizeof(T));
                for(int i = count - 2; i > index; i--)
                    data[i+1] = data[i];
                data[index] = obj;
            }

            OPERATOR int getCount()
            {
                return count;
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

            Vector()
            {
                data = malloc(1);
                count = 0;
            }

            ~Vector()
            {
                free(data);
            }
    };
};

#endif