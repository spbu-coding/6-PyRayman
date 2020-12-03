
#include <string.h>
#define ASCII_NUM 128

void swap(char *xp, char *yp) 
{ 
    char     temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void bubble(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size - 1 - i; j++) {
            if (cmp(strings[j], strings[j + 1]) > 0) {
                swap(strings[j], strings[j + 1])
            }
        }
    }
}

void insertion(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    for (unsigned int i = 1; i < size; i++) {
        for (unsigned int j = i; j > 0 && cmp(strings[j - 1], strings[j]) > 0; j--) {
            swap(strings[j - 1], strings[j])
        }
    }
}


void merge(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    for (unsigned int parts_num = size; parts_num > 1; parts_num = (unsigned int) ceil(parts_num / 2.0)) {
        size_t part_len = (size_t) ceil(size / (double)parts_num);
        for (unsigned int i = 0; i < parts_num - 1; i += 2) {
            size_t len1 = part_len, len2 = (((i + 2) * part_len) <= size) ? part_len : (size - (i + 1) * part_len), buf_len = len1 + len2;
            unsigned int ind1 = i * part_len, ind2 = (i + 1) * part_len;
            char* buf[buf_len];
            while (len1 > 0 && len2 > 0) {
                if (cmp(strings[ind1], strings[ind2]) <= 0) {
                    buf[buf_len - (len1-- + len2)] = strings[ind1++];
                } else {
                    buf[buf_len - (len1 + len2--)] = strings[ind2++];
                }
            }
            if (len1 > 0) {
                memcpy(&buf[buf_len - len1], &strings[ind1], len1 * sizeof(char*));
            } else {
                memcpy(&buf[buf_len - len2], &strings[ind2], len2 * sizeof(char*));
            }
            memcpy(&strings[i * part_len], buf, buf_len * sizeof(char*));
        }
    }
}


void quick(strings_array_t strings, array_size_t size, comparator_func_t cmp) {
    unsigned mid = size / 2, i = 0, j = size - 1;
    do {

        while (cmp(strings[mid], strings[i])) i++;
        while (cmp(strings[j], strings[mid])) j--;
        if (i <= j) {

            swap(&strings[i], &strings[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0) quick(strings, j + 1, cmp);
    if (i < size - 1) quick&strings[i], size - i, cmp);
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