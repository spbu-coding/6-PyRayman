#include "sortings.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define ASCII_NUM 128

void swap(char **xp, char **yp) 
{ 
    char *temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

int asc_cmp(const char *first_string, const char *second_string)
{
    char first_string_char, second_string_char;
    do
    {
        first_string_char = *first_string++;
        second_string_char = *second_string++;
        if(first_string_char == '\0')
        {
            return (first_string_char - second_string_char) > 0;
        }
    } while(first_string_char == second_string_char);
    return (first_string_char - second_string_char) > 0;
}

int des_cmp(const char *first_string, const char *second_string)
{
    char first_string_char, second_string_char;
    do
    {
        first_string_char = *first_string++;
        second_string_char = *second_string++;
        if(first_string_char == '\0')
        {
            return (first_string_char - second_string_char) < 0;
        }
    } while(first_string_char == second_string_char);
    return (first_string_char - second_string_char) < 0;
}

void bubble(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size - 1 - i; j++) {
            if (cmp(strings[j], strings[j + 1]) > 0) {
                swap(&strings[j], &strings[j + 1]);
            }
        }
    }
}

void insertion(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    for (unsigned int i = 1; i < size; i++) {
        for (unsigned int j = i; j > 0 && cmp(strings[j - 1], strings[j]) > 0; j--) {
            swap(&strings[j - 1], &strings[j]);
        }
    }
}

void merge(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    array_size_t step = 1;
    strings_array_t new_array = malloc(sizeof(char *) * size);

    while(step < size)
    {
        array_size_t index = 0, left = 0, middle = left + step, right = left + step * 2;
        do{
            if(middle > size)
            {
                middle = size;
            }
            if(right > size)
            {
                right = size;
            }

            array_size_t i = left, j = middle;
            while(i < middle && j < right)
            {
                if(cmp(strings[j], strings[i]))
                {
                    new_array[index++] = strings[i++];
                }
                else
                {
                    new_array[index++] = strings[j++];
                }
            }

            while(i < middle)
            {
                new_array[index++] = strings[i++];
            }
            while(j < right)
            {
                new_array[index++] = strings[j++];
            }

            left += step * 2;
            middle += step * 2;
            right += step * 2;
        } while (left < size);

        for(array_size_t i = 0; i < size; i++)
        {
            strings[i] = new_array[i];
        }
        step *= 2;
    }

    free(new_array);
}


void quick_sort(strings_array_t strings, int left, int right, comparator_func_t cmp)
{
    int i = left, j = right;
    char *middle = strings[(left + right) / 2];

    do
    {
        while(cmp(middle, strings[i]) && (i < right))
        {
            i++;
        }
        while(cmp(strings[j], middle) && (j > left))
        {
            j--;
        }
        if(i <= j)
        {
            char* swapper = strings[i];
            strings[i] = strings[j];
            strings[j] = swapper;
            i++;
            j--;
        }
    } while(i <= j);

    if(left < j)
    {
        quick_sort(strings, left, j, cmp);
    }
    if(i < right)
    {
        quick_sort(strings, i, right, cmp);
    }
}

void quick(strings_array_t strings, array_size_t size, comparator_func_t cmp)
{
    quick_sort(strings, 0, (int) size - 1, cmp);
}


void radix_sort(strings_array_t strings, array_size_t size, int position)
{
    array_size_t count[UCHAR_MAX + 1], mode, i;
    strings_array_t bucket[UCHAR_MAX + 1], top[UCHAR_MAX + 1];
    while(size > 1)
    {
        memset(count, 0, sizeof(array_size_t) * (UCHAR_MAX + 1));
        for(i = 0; i < size; i++)
        {
            count[(int) strings[i][position]]++;
        }

        mode = 1;
        for(i = 2; i <= UCHAR_MAX; i++)
            if(count[i] > count[mode])
            {
                mode = i;
            }

        if(count[mode] < size)
        {
            bucket[0] = strings;
            top[0] = strings;
            for(i = 1; i <= UCHAR_MAX; i++)
            {
                top[i] = bucket[i] = bucket[i - 1] + count[i - 1];
            }

            for(i = 0; i <= UCHAR_MAX; i++)
            {
                while(top[i] < bucket[i] + count[i])
                    if((array_size_t) top[i][0][position] == i)
                    {
                        top[i]++;
                    }
                    else
                    {
                        swap(top[i], top[(int) top[i][0][position]]++);
                    }
            }

            for(i = 1; i <= UCHAR_MAX; i++)
                if(i != mode)
                {
                    radix_sort(bucket[i], count[i], position + 1);
                }

            size = count[mode];
            strings = bucket[mode];
            position++;
        }
        else
        {
            position++;
        }
    }
}

void radix(strings_array_t strings, array_size_t size, comparator_func_t cmp)
{
    radix_sort(strings, size, 0);
    if(cmp == des_cmp)
    {
        for(array_size_t i = 0; i < size / 2; i++)
        {
            char *swapper = strings[i];
            strings[i] = strings[size - i - 1];
            strings[size - i - 1] = swapper;
        }
    }
}