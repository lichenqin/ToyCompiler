# include <stdio.h>
# include <stdlib.h>
# include "test_v.h"

/*Test Token Type*/ /*accept*/
typedef enum{
    /* Reserve Word*/
    WHILE, IF, THEN, ELSE, DO, END, IN, OUT,
    /* Special Symbol*/
    //PLUS, SUB, MULTIPLE, DIVIDE, BIGGER, LESSER, ASSIGN, EQUAL, SEMI,
    PLUS, MINUS, TIMES, DIVIDE, LP, RP, EQUAL, ASSIGN, LT, GT, SEMI,
    /* Integer Decimal Octal Hex*/
    INT10, INT8, INT16,
    /* Float Decimal Octal Hex*/
    FLO10, FLO8, FLO16,
    /* Identifier*/
    ID,
    /* Error*/
    ERROR
}TokenType;

/* test tokenTable */ /*accept*/
const char * tokenTable[26]={"WHILE", "IF", "THEN", "ELSE", "DO","END","IN","OUT",
                    "PLUS", "MINUS", "TIMES", "DIVID", "LP", "RP", "EQUAL", "ASIGN", "LT", "GT", "SEMI",
                    "INT10", "INT8", "INT16",
                    "FLO10", "FLO8", "FLO16",
                    "ID"};

/* test enum type */
/*
typedef enum{
    plus, minus, multiple, divide
}operator;
*/

/* Test String Cat in Safe mode*/ /*accept*/
char * str_conjunction(char * pre_array, const char * appendex){
    const char * char_tmp = pre_array;

    /*count total length*/
    int count = 0;
    while( *char_tmp++ != '\0' ) count++;    
    char_tmp = appendex;
    while ( *char_tmp++ != '\0' ) count++;

    /*allocate memorary for new string and copy*/
    char * array = (char *)calloc((count+1),sizeof(char));
    char * tmp = array;
    while( (*tmp++ = *pre_array++) != '\0');
    tmp--;
    while( (*tmp++ = *appendex++) != '\0');

    return array;
}


void printToken( TokenType object ){
    printf("%s\n",tokenTable[object]);
}

/* 定义In_range内联函数*/
int In_range( char temp, char x, char y){
    if( temp >= x && temp <= y)
        return 1;
    else
        return 0;
}

/* 判断间隔符*/
int Isinter(char temp){
    if( In_range(temp,'(','+') || In_range(temp,';','>')) return 1;
    else if ( temp == '-' || temp == '/' )              return 1;
    else if ( temp == '\n' || temp == ' ' || temp == '\t')  return 1;
    else return 0;
}

/*If it's legal word*/
int Isid( char temp ){
    if( In_range(temp, '0','9') || In_range(temp, 'a','z') || In_range(temp,'A','Z'))
        return 1;
    else if( temp == '_')
        return 1;
    else
        return 0;
}

int main( int argc, char * argv[]){

    //printf("number_test_v: %d\n", number_test_v);
    //cannot directly use other file's declaration variable.

    if( argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    const char * filename = (const char *)argv[1];
    char * outfile = str_conjunction(argv[1],".out");

    FILE * read = fopen(filename, "rb");
    if( read == NULL ){
        printf("Can't open this file: %s\n", argv[1]);
        exit(1);
    }

    FILE * out = fopen(outfile, "w");
    if( out == NULL ){
        printf("Can't record.\n");
        exit(1);
    }
    
    //char array[16] = {}; //如果定义buff最大为16 那每行的实际字符为14个
    int temp = 0;
    while( (temp = fgetc(read)) != -1 ){
        if( Isid(temp) ){
            printf("%c is id\n",temp);
            fprintf(out,"%c",temp);
        }
    }
    printf("End of File\n");


    /*Close file handle*/
    fclose(read);
    fclose(out);

    /*free heap*/
    free(outfile);

    return 0;
}