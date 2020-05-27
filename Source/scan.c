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
                    "ID", "ERROR"};

/* 定义In_range内联函数*/
inline int In_range( char temp, char x, char y){
    if( temp >= x && temp <= y)
        return True;
    else
        return False;
}

/* 判断是否为间隔符*/
inline int Isinter( char temp){
    if( Inrange(temp,'(','+') || Inrange(temp,';','>')) return True;
    else if ( temp == '-' || temp == '/' )              return True;
    else if ( temp == '\n' || temp == ' ' || temp == '\t')  return True;
    else return False;
}

/*If it's legal word*/
inline int Isid( char temp ){
    if( In_range(temp, '0','9') || In_range(temp, 'a','z') || In_range(temp,'A','Z'))
        return True;
    else if( temp == '_')
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
        printf("%c",String_buffer[i]);
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
/*两个函数非常重要，fgetc fprintf*/
/*通过这两个函数 可以实现读取filename.tiny文件以及输出到.out文件中*/
/*由于linux的系统原因，feof存在延后性 所以使用fgets判断文件末尾*/
TokenType getToken(){
    
    /*temp用于从file中读取一个字符*/
    int temp = 0;
    if( (temp=fgetc(read)) != -1 ){ //EOF == -1
        
        char convert = (char)temp;
        State current_state = start;
        int accept = False;
        int save = True;
        string_position = 0;

        while( accept != True ){

            save = True;

            switch (current_state)
            {
                case start/* 开始状态 */:
                    if(convert=='0')
                        current_state = zero;
                    else if( In_range(convert,'1','9'))
                        current_state = INT10;
                    else if( In_range(convert,'a','z') || In_range(convert, 'A','Z')){
                        if( convert == 'd') current_state = md;
                        else if( convert == 'e')    current_state = me;
                        else if( convert == 'i')    current_state = mi;
                        else if( convert == 't')    current_state = mt;
                        else if( convert == 'w')    current_state = mw;
                        else                        current_state = ID;
                    }
                    else if( Inrange(convert,'(','+') || In_range(convert,';','>') || convert=='-' || convert=='/'){
                        if( convert=='+')  current_state = PLUS;
                        else if( convert=='-')  current_state = MINUS;
                        else if( convert=='*')  current_state = TIMES;
                        else if( convert=='/')  current_state = DIVIDE;
                        else if( convert=='(')  current_state = LP;
                        else if( convert==')')  current_state = RP;
                        else if( convert=='<')  current_state = LT;
                        else if( convert=='>')  current_state = GT;
                        else                    current_state = SEMI;
                        
                        accept = True;
                    }
                    else if( convert=='=' ) current_state = ASSIGN;/*Assign 即是完成状态又是中间状态*/
                    else if( convert=='\n' || convert=='\t' || convert==' ' || convert=='\r'){
                        //keep fetching.
                        save = False;
                    }
                    else    current_state = ERROR;

                    break;
                case zero/*0*/:
                    if( In_range(convert,'0','7') )  current_state = INT8;
                    else if( convert == 'X' )       current_state = ox;
                    else if( convert == '.' )       current_state = dtf;
                    else if( Isinter(convert) ){
                        current_state = INT10;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    
                    break;
                case INT10:
                    if( In_range(convert,'0','9'))  current_state = INT10;
                    else if ( convert=='.' )        current_state = dtf;
                    else if ( Isinter(convert) ){
                        current_state = INT10;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case ox:
                    if( In_range(convert,'0','9') || In_range(convert,'A','F')) current_state = INT16;
                    else if( Isinter(convert) ){
                        current_state = ERROR;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case INT16:
                    if( In_range(convert,'0','9') || In_range(convert,'A','F')) current_state = INT16;
                    else if ( Isinter(convert) ){
                        current_state = INT16;
                        accept = True;
                        save = False;
                    }
                    else if( convert=='.')  current_state = htf;
                    else    current_state = ERROR;
                    break;
                case INT8:
                    if( In_range(convert,'0','7'))  current_state = INT8;
                    else if( convert=='.')          current_state = otf;
                    else if( Isinter(convert) ){
                        current_state = INT8;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case dtf:/*Decimal to Float Middle state*/
                    if( In_range(convert,'0','9') ) current_state = F10;
                    else if( Isinter(convert) ){
                        current_state = ERROR;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case F10:/*Decimal Float Accept state*/
                    if( In_range(convert,'0','9') ) current_state = F10;
                    else if( Isinter(convert) ){
                        current_state = F10;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case htf:/*Hex to Float Middle state*/
                    if( In_range(convert,'0','9') || In_range(convert,'A','Z') )
                        current_state = F16;
                    else if( Isinter(convert) ){
                        current_state = ERROR;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case F16:/*Hex Float Accept state*/
                    if( In_range(convert,'0','9') || In_range(convert,'A','Z') )
                        current_state = F16;
                    else if( Isinter(convert) ){
                        current_state = F16;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case otf:/*Octal to Float Middle state*/
                    if( In_range(convert,'0','7') ) current_state = F8;
                    else if( Isinter(convert) ){
                        current_state = ERROR;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case F8:/*Octal Float Accept state*/
                    if( In_range(convert,'0','7') ) current_state = F8;
                    else if( Isinter(convert) ){
                        current_state = F8;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case ASSIGN:
                    if( convert == '=' )
                        current_state = EQUAL;
                    else
                        current_state = ASSIGN;
                    
                    accept = True;
                    break;
                case md:
                    if( convert == 'o') current_state = DO;
                    else if( Isid(convert))     current_state = ID;
                    else if( Isinter(convert) ) {
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case DO:
                    if( Isid(convert) ) current_state = ID;
                    else if( Isinter(convert)){
                        current_state = DO;
                        accept = True;
                    }
                    else    current_state = ERROR;
                    break;
                case me:
                    if( convert == 'l') current_state = mel;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mel:
                    if( convert == 's') current_state = mels;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mels:
                    if( convert == 'e') current_state = ELSE;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case ELSE:
                    if( Isid(convert) ) current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ELSE;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mi:
                    if( convert == 'f') current_state = IF;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case IF:
                    if( Isid(convert) ) current_state = ID;
                    else if( Isinter(convert)){
                        current_state = IF;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mt:
                    if( convert == 'h') current_state = mth;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mth:
                    if( convert == 'e') current_state = mthe;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                    }
                    else    current_state = ERROR;
                    break;
                case mthe:
                    if( convert == 'n') current_state = THEN;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case THEN:
                    if( Isid(convert) ) current_state = ID;
                    else if( Isinter(convert)){
                        current_state = THEN;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mw:
                    if( convert == 'h') current_state = mwh;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mwh:
                    if( convert == 'i') current_state = mwhi;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                    }
                    else    current_state = ERROR;
                    break;
                case mwhi:
                    if( convert == 'l') current_state = mwhil;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case mwhil:
                    if( convert == 'e') current_state = WHILE;
                    else if( Isid(convert) )    current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case WHILE:
                    if( Isid(convert) ) current_state = ID;
                    else if( Isinter(convert)){
                        current_state = WHILE;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case ID:/*Identifier Accept state*/
                    if( Isid(convert) ) current_state = ID;
                    else if( Isinter(convert)){
                        current_state = ID;
                        accept = True;
                        save = False;
                    }
                    else    current_state = ERROR;
                    break;
                case ERROR:
                    if( Isinter(convert) ){
                        current_state = ERROR;
                        accept = True;
                        save = False;
                    }
                    else
                    {
                        current_state = ERROR;
                    }
                    break;
                case END:
                    return ENDFI;
                default:
                    break;
            }

            if( save == True ){
                if( string_position < Max_Va_Length-1)
                    String_buffer[string_position++] = convert;
                else{
                    //多出来的部分不计入
                }
                convert = (char)fgetc(read);
            }
            else{
                if( accept == True )
                    String_buffer[string_position] = '\0';
            }
            
        }
        printToken(current_state);
        printString();

    }
    else{
        return ENDFI;
    }

}