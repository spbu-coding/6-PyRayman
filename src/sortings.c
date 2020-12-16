#include "sortings.h"
#include <stdlib.h>
#include <string.h>
#define ASCII_NUM 128

void swap(char **xp, char **yp) 
{ 
    char *temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
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


void quick(strings_array_t strings, array_size_t size, comparator_func_t cmp) {

    int left = 0; 
    int right = size - 1;
    char *mid, *temp;

    mid = strings[size / 2];
    
    do {
        while(cmp(strings[left],mid)<0) left++;
  
        while(cmp(strings[right],mid)>0) right--;

        if (left <= right) {  
            temp = strings[left];
            strings[left] = strings[right];
            strings[right] = temp;
            left++;
            right--;
        }
    } while (left <= right);
  
    if(right > 0){
        quick(strings, right + 1, cmp);
    }
    if (left < (int)size){  
        quick(&strings[left], size - left, cmp);
    }
}


void radix_realize( char **strings , array_size_t size , int max , comparator_func_t cmp)
{
    int comparer = ( cmp( "A" , "B" ) < 0 ) ? 1 : 2 ;

    for (int i = max - 1; i >= 0; i--) {
        char *temp_array[size];
        int count[ASCII_NUM] = { 0 };

        for (int j = 0; j < (int) size; j++) {
            count[(int) strings[j][i]]++;
        }
        for (int j = 1; j < ASCII_NUM; j++) {
            count[j] += count[j - 1];
        }
        for (int j = (int)size - 1; j >= 0; j--) {
            temp_array[count[(int) strings[j][i]] - 1] = strings[j];
            count[(int) strings[j][i]]--;
        }
        for (int j = (int)size - 1; j >= 0; j--) {
            if (i > 0 || comparer == 1) {
                strings[j] = temp_array[j];
            }
            else {
                strings[size - 1 - j] = temp_array[j];
            }
        }
    }
}

void radix( strings_array_t strings , array_size_t size , comparator_func_t cmp )
{
    int max = 0;
    for( int i = 0 ; i < (int)size ; i++ )
    {
        if( max < (int)strlen( strings[i] ) )
        max = (int)strlen(strings[i]);
    }
    radix_realize( strings , size , max , cmp );
}