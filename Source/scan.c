# include "type.h"
# include "scan.h"

/* 作为 identifier\number 缓冲区使用*/
char String_buffer[Max_Va_Length];

/* 定义 identifier\number 缓冲区当前状态值*/
int string_position = 0;

/* 作为 line 缓冲区使用*/
char Line_buffer[Max_Line];

/* 定义 line 缓冲区当前的状态值*/
int line_position = 0;

/* 建立token类型表*/
const char * tokenTable[24]={"WHILE", "IF", "THEN", "ELSE", "DO",
                    "PLUS", "MINUS", "TIMES", "DIVID", "LP", "RP", "EQUAL", "ASIGN", "LT", "GT", "SEMI",
                    "INT10", "INT8", "INT16",
                    "FLO10", "FLO8", "FLO16",
                    "ID", "ID_"};

/* 定义In_range内联函数*/
inline bool In_range( char temp, char x, char y){
    if( temp >= x && temp <= y)
        return True;
    else
        return False;
}

/* 打印字符类型 */
void printToken(TokenType token){
    printf("%s\n",tokenTable[token]);
}

/* printString 打印identifier或者number*/
void printString(){
    for(int i = 0; i < string_position; ++i)
        printf("%c",Buffer[i]);
    printf("\n");
}

/* 安全模式下的strcat实现 避免指针溢出*/
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

/* getToken是scanner的主函数*/
TokenType getToken(){
    /*两个函数非常重要，fgets fprintf*/
    /*通过这两个函数 可以实现读取filename.tiny文件以及输出到.out文件中*/
    
    /*由于linux的系统原因，feof存在延后性 所以使用fgets判断文件末尾*/
    if( fgets( Line_buffer, Max_Line, read) != NULL ){
        
        bool accept = False;
        State character = start;

        while( accept == False )
    }
    else{
        return ENDFI;
    }

}