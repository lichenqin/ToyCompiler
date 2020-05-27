# include <stdio.h>
# include <stdlib.h>

/*Test Token Type*/ /*accept*/
typedef enum{
    /* Reserve Word*/
    WHILE, IF, THEN, ELSE, DO,
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
const char * tokenTable[23]={"WHILE", "IF", "THEN", "ELSE", "DO",
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

int main( int argc, char * argv[]){

    if( argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    const char * filename = (const char *)argv[1];
    //const char * outfile = (const char *)str_conjunction(argv[1],".out");

    FILE * read = fopen(filename, "rb");
    if( read == NULL ){
        printf("Can't open this file: %s\n", argv[1]);
        exit(1);
    }

    // FILE * out = fopen(outfile, "w")
    // if( out == NULL ){
    //     printf("Can't record.\n");
    //     exit(1);
    // }
    
    //char array[16] = {}; //如果定义buff最大为16 那每行的实际字符为14个
    int temp = 0;
    while( (temp = fgetc(read)) != -1 ){
        printf("%c",temp);
    }
    printf("End of File\n");


    /*Close file handle*/
    fclose(read);
    //fclose(out);

    /*free heap*/
    //free(outfile);

    return 0;
}