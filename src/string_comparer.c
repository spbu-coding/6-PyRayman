#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "sortings.h"

int get_params(int argc, char* argv[], char* input_file, char* output_file, array_size_t* number_of_strings ,int *sort_method, int *comparator){

    if(argc < 5){ return -1;}
    if(argc > 5){ return -1;}

   
    if( atoi(argv[1]) != 0 )    
    {
        *number_of_strings = (unsigned long int)atoi(argv[1]);   
    }
    else{return -1;}
    


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

    if (number_of_strings == 0) {

        FILE *output = fopen(output_file, "w");
        fputs("\n", output);
        fclose(output);
        return 0;
    }


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

// ---------------------------------------------------
    if( (strncmp(argv[5]  , "asc" , 3) == 0))    
    {
        *comparator = 1;
    }
    else if( (strncmp(argv[5]  , "des" , 3) == 0))    
    {
        *comparator = 2;
    }
    else{return -1;}

// -------------------------------------------------------

    return 0;
}

int asc_cmp(const char* first_line, const char* second_line)
{
    return strcmp(first_line, second_line );
}

int des_cmp(const char* first_line, const char* second_line)
{
    return -strcmp(first_line, second_line);
}

comparator_func_t comparator_choose(int comparator){
    if(comparator == 1 ){
        return asc_cmp;
    }

    else if(comparator == 2){
        return des_cmp;
    }
}

int sort_call(int sort_method, array_size_t size, int comparator, strings_array_t strings){
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


int read_file(strings_array_t strings_array, char* filename, array_size_t lines_count){
    FILE *file = fopen(filename,"r");

    if(file == NULL){
        printf("Считываемый файл пуст\n");
        return -1;
    }

    for (unsigned i = 0; i < lines_count; i++)
    {   
        if(fgets(strings_array[i], MAX_INPUT_STRING_SIZE, file) == NULL) {
            fprintf(stderr, "Ошибка чтения строки %d/%lu\n", i,  lines_count);
            return -1;
        }
        if(strchr(strings_array[i], '\n') == NULL){ strcat(strings_array[i], "\n");}
    }
    fclose(file);
}

int write_file(strings_array_t strings_array, char* filename, int array_len){
    FILE *file = fopen(filename,"w");

    if(file == NULL){
        printf("Ошибка открытия файла");
        return -1;
    }
    for (int i = 0; i < array_len; i++){
        fputs(strings_array[i],file);
    }   
}

int main(int argc, char** argv){
    strings_array_t strings;
    array_size_t array_size;
    
    int sort_method;
    int comparator;
    char input_file[255];
    char output_file[255];

    get_params(argc,argv,input_file,output_file,&array_size,&sort_method,&comparator);
    
    strings = (char**)malloc( sizeof( char *) * array_size );

    read_file(strings,input_file,array_size);

    sort_call(sort_method,array_size,comparator,strings);

    write_file(strings,output_file,array_size);


    return 0;


}