/*-------------------------------------------*/
/* This is the main function of this compiler*/
/* 1. Scanner--mian function getToken()      */
/* 2. Parser                                 */
/* 3. Code Genertater                        */
/*-------------------------------------------*/

# include "type.h"
# include "scan.h"

int main( int argc, char * argv[] ){
    
    if( argc != 2){
        printf("Usage: %s <filename>", argv[0]);
        exit(1);
    }
    
    const char * filename = (const char *)argv[1];
    const char * outfile = (const char *)str_conjunction(argv[1],".out");

    const char * filename = (const char *) argv[1];
    read = fopen(filename, "rb");
    if( read == NULL){
        prinf("Can't open this file: %s", argv[1]);
        exit(1);
    }

    output = fopen(outfile, "w")
    if( output == NULL ){
        printf("Can't record.\n");
        exit(1);
    }

    /* Scanner Part*/

    while( getToken() != 0 );

    /* Parser Part*/

    /* Code generater parter*/

    /*Close file handle*/
    fclose(read);
    fclose(output);

    /*free heap*/
    free(outfile);

    return 0;

}