/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__
#define CITRUS_ENGINE_STD_VECTOR_REPLACEMENT_HPP__

#include <cstdlib>
#include "include/core/extensions.hpp"
#include "include/core/mem.hpp"

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
                data = memrealloc(data, count * sizeof(T));
                data[count-1] = obj;
            }

            OPERATOR T pop()
            {
                if(!count)
                    return;
                count--;
                T obj = data[count];
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
                return obj;
            }

            OPERATOR void rm(int index)
            {
                if(!count)
                    return;
                for(int i = index; i < count - 1; i--)
                    data[i] = data[i+1];
                count--;
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
            }

            OPERATOR void insert(int index, T obj)
            {
                if(!count)
                    return;
                count++;
                data = memrealloc(data, count * sizeof(T), MEM_FLAG_UNIT_BYTE);
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
                data = memalloc(1, MEM_FLAG_UNIT_BYTE);
                count = 0;
            }

            ~Vector()
            {
                free(data);
            }
    };
};

#endif