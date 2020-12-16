#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sortings.h"

int check_count_of_strings(char* input_file, array_size_t count_of_strings){
    FILE *file = fopen(input_file, "r");
    array_size_t count_of_strings_in_file = 0;
    char* input_file_strings = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);

    while(feof(file)){
        if(fgets(input_file_strings, MAX_INPUT_STRING_SIZE, file) != NULL){
            count_of_strings_in_file++;
        }
    }
    free(input_file_strings);

    if(count_of_strings_in_file < count_of_strings){
        fclose(file);
        return -1;
    }
    return 0;
}

int get_params(int argc, char** argv, char *input_file, char *output_file, array_size_t* number_of_strings ,int *sort_method, int *comparator){
    if(argc < 6) return -1;
    if(argc > 6) return -1;

    char* end;
    *number_of_strings = strtoul(argv[1], &end, 10);
    if (*number_of_strings < 0){
        return -1;
    }
    
    if(*end != '\0') {
        return -1;
    }
    
    if ((strstr(argv[2], ".txt") != NULL)  && (strstr(argv[3], ".txt") != NULL) ){          
        FILE *file = fopen(argv[2],"r");

        if (file == NULL){
            printf("input file not found\n");
            return -1;
        }
        else{
        strcpy(input_file,argv[2]);
        strcpy(output_file,argv[3]);
        }
        fclose(file);
    }
    else{return -1;}

    check_count_of_strings(input_file,*number_of_strings);


    if( (strncmp(argv[4]  , "bubble" , 6) == 0))    
    {
        *sort_method = 1;
    }

    else if( (strncmp(argv[4]  , "insertion" , 9) == 0))    
    {
        *sort_method = 2;
    }

    else if( (strncmp(argv[4]  , "merge" , 5) == 0))    
    {
        *sort_method = 3;
    }

    else if( (strncmp(argv[4]  , "quick" , 5) == 0))    
    {
        *sort_method = 4;
    }

    else if( (strncmp(argv[4]  , "radix" , 5) == 0))    
    {
        *sort_method = 5;
    }
    else{return -1;}


    if( (strncmp(argv[5]  , "asc" , 3) == 0))    
    {
        *comparator = 1;
    }
    else if( (strncmp(argv[5]  , "des" , 3) == 0))    
    {
        *comparator = 2;
    }
    else{return -1;}

    return 0;
}



comparator_func_t comparator_choose(int comparator){
    if(comparator == 1 ){
        return asc_cmp;
    }

    else {
        return des_cmp;
    }
}

void sort_call(int sort_method, array_size_t size, int comparator, strings_array_t strings){
    switch (sort_method)
    {
        case 1:
            bubble(strings,size,comparator_choose(comparator));
            break;
        
        case 2:
            insertion(strings,size,comparator_choose(comparator));
            break;
        
        case 3:
            merge(strings,size,comparator_choose(comparator));
            break;
        
        case 4:
            quick(strings,size,comparator_choose(comparator));
            break;
        
        case 5:
            radix(strings,size,comparator_choose(comparator));
            break;  
    }
}


int read_file(char** strings_array, char *filename, array_size_t lines_count){
    FILE *file = fopen(filename,"r");

    if(file == NULL){
        printf("Считываемый файл пуст\n");
        return -1;
    }

    for (array_size_t i = 0; i < lines_count; i++)
    {   
        fgets(strings_array[i], MAX_INPUT_STRING_SIZE, file);
    }
    fclose(file);
    return 0; 
}

int write_file(strings_array_t strings_array, char *filename, array_size_t array_len){
    FILE *file = fopen(filename,"w");

    if(file == NULL){
        printf("Ошибка открытия файла");
        return -1;
    }
    if (array_len == 0) {
        fputs("\n", file);
    }

    for (array_size_t i = 0; i < array_len; i++)  
    {
        fputs(strings_array[i], file);
    }
 
    fclose(file);
    return 0;
}

int main(int argc, char** argv){
    array_size_t array_size;
    int sort_method;
    int comparator;
    char input_file[256];
    char output_file[256];
    int check = get_params(argc,argv,input_file,output_file,&array_size,&sort_method,&comparator);
    if (check != 0){
        return check;
    }
    get_params(argc,argv,input_file,output_file,&array_size,&sort_method,&comparator);

    char **strings = malloc(sizeof(char*) * array_size);
    for(array_size_t i = 0; i < array_size; i++)
    {
        strings[i] = malloc(sizeof(char) * MAX_INPUT_STRING_SIZE);
    }

    read_file(strings,input_file,array_size);
    sort_call(sort_method,array_size,comparator,strings);
    write_file(strings,output_file,array_size);

    for(array_size_t i = 0; i < array_size; i++)
    {
        free(strings[i]);
    }
    free(strings);
    return 0;
}