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

    if (size == 1) return;
    array_size_t left_size = (size - size / 2);
    array_size_t right_size = size / 2;
    strings_array_t array_left = malloc(left_size * sizeof(char *));
 
    for (unsigned i = 0; i < left_size; i++) array_left[i] = strings[i];
    strings_array_t array_right = malloc(right_size * sizeof(char *));

    for (unsigned i = left_size; i < size; i++) array_right[i - left_size] = strings[i];

    merge(array_left, left_size, cmp);
    merge(array_right, right_size, cmp);

    unsigned i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {

        if (cmp(array_left[i], array_right[j])) {

            strings[k] = array_right[j];
            j++;
            k++;
        } else {

            strings[k] = array_left[i];
            i++;
            k++;
        }
    }
    while (i < left_size) {

        strings[k] = array_left[i];
        i++;
        k++;
    }
    while (j < right_size) {

        strings[k] = array_right[j];
        j++;
        k++;
    }
    free(array_left);
    free(array_right);
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