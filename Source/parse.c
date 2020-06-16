# include "parse.h"

/*This language Design doesn't consider minus situation*/

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * while_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * in_stmt(void);
static TreeNode * out_stmt(void);
static TreeNode * exp_stmt(void);
static TreeNode * exp1(void);
static TreeNode * exp_2(void);
static TreeNode * exp3(void);

static void syntaxError(char * message)
{ printf("\n>>> ");
  printf("Syntax error : %s",message);
  //Error = TRUE;
}

static void match(TokenType expected)
{ 
  printf("Token in parse is: ");
  printToken(token);
  printf("expected in parse is: ");
  printToken(expected);
  printf("\n");
  if (token == expected) token = getToken();
  else {
    syntaxError("unexpected token -> ");
    printToken(token);
    //fprintf(listing,"      ");
  }
}

TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  TreeNode * p = t;
  while ((token!=ENDFI) && (token!=END) &&
         (token!=ELSE) )
  { TreeNode * q;
    match(SEMI);
    q = statement();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else /* now p cannot be NULL either */
      { p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}

TreeNode * statement(void)
{ TreeNode * t = NULL;
  switch (token) {
    case IF : t = if_stmt(); break;
    case WHILE : t = while_stmt(); break;
    case ID : t = assign_stmt(); break;
    case IN : t = in_stmt(); break;
    case OUT : t = out_stmt(); break;
    default : syntaxError("unexpected token -> ");
              printToken(token);
              token = getToken();
              break;
  } /* end case */
  return t;
}

TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
  match(IF);
  if (t!=NULL) t->child[0] = exp_stmt();
  match(THEN);
  if (t!=NULL) t->child[1] = stmt_sequence();
  if (token==ELSE) {
    match(ELSE);
    if (t!=NULL) t->child[2] = stmt_sequence();
  }
  match(END);
  return t;
}

TreeNode * while_stmt(void)
{ TreeNode * t = newStmtNode(WhileK);
  match(WHILE);
  if (t!=NULL) t->child[0] = exp_stmt();
  match(DO);
  if (t!=NULL) t->child[1] = stmt_sequence();
  match(END);
  return t;
}

TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString();
  match(ID);
  match(ASSIGN);
  if (t!=NULL) t->child[0] = exp_stmt();
  return t;
}

TreeNode * in_stmt(void)
{ TreeNode * t = newStmtNode(InK);
  match(IN);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString();
  match(ID);
  return t;
}

TreeNode * out_stmt(void)
{ TreeNode * t = newStmtNode(InK);
  match(OUT);
  if (t!=NULL) t->child[0] = exp_stmt();
  return t;
}

TreeNode * exp_stmt(void)
{ TreeNode * t = exp1();
  if ((token==LT)||(token==GT)||(token==EQUAL)) {
    TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t!=NULL)
      t->child[1] = exp1();
  }
  return t;
}

TreeNode * exp1(void)
{ TreeNode * t = exp_2();
  while ((token==PLUS)||(token==MINUS))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = exp_2();
    }
  }
  return t;
}

TreeNode * exp_2(void)
{ TreeNode * t = exp3();
  while ((token==TIMES)||(token==DIVIDE))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = exp3();
    }
  }
  return t;
}

TreeNode * exp3(void)
{ TreeNode * t = NULL;
  switch (token) {
    case INT10 :
      t = newExpNode(InterK);
      if ((t!=NULL) && (token==INT10))
        t->attr.ival = convertI(String_buffer,10,0);
      match(INT10);
      break;
    case INT8 :
      t = newExpNode(InterK);
      if ((t!=NULL) && (token==INT8))
        t->attr.ival = convertI(String_buffer,8,1);
      match(INT8);
      break;
    case INT16 :
      t = newExpNode(InterK);
      if ((t!=NULL) && (token==INT16))
        t->attr.ival = convertI(String_buffer,16,2);
      match(INT16);
      break;
    case FLO10 :
      t = newExpNode(FloK);
      if ((t!=NULL) && (token==FLO10))
        t->attr.fval = convertF(String_buffer,10,0);
      match(FLO10);
      break;
    case FLO8 :
      t = newExpNode(FloK);
      if ((t!=NULL) && (token==FLO8))
        t->attr.fval = convertF(String_buffer,8,1);
      match(FLO8);
      break;
    case FLO16 :
      t = newExpNode(FloK);
      if ((t!=NULL) && (token==FLO16))
        t->attr.fval = convertF(String_buffer,16,2);
      match(FLO16);
      break;
    case ID :
      t = newExpNode(IdK);
      if ((t!=NULL) && (token==ID))
        t->attr.name = copyString();
      match(ID);
      break;
    case LP :
      match(LP);
      t = exp_stmt();
      match(RP);
      break;
    default:
      syntaxError("unexpected token -> ");
      printToken(token);
      token = getToken();
      break;
    }
  return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly 
 * constructed syntax tree
 */
TreeNode * parse(void)
{ TreeNode * t;
  token = getToken();
  //printf("Token in parse is: ");
  //printToken(token);
  t = stmt_sequence();
  if (token!=ENDFI)
    syntaxError("Code ends before file\n");
  return t;
}

/*convert random radix interger to decimal interger*/
int convertI(const char * array, int radix, int start){
    int sum = 0;
    int number[32] = {0};

    for( int i = start; array[i] != '\0'; ++i){
        if( array[i] >= 'A'){
            number[i] = array[i] - 55;  //convert 16 to 10
            continue;
        }
        number[i] = array[i] - 48;
    }

    for( int i = start; array[i] != '\0'; ++i)
        sum = sum*radix + number[i];
    
    return sum;
}

/*convert random radix float to decimal float*/
float convertF(const char * array, int radix, int start){
    float sum = 0.0;
    float dots = 0.0;
    float number[32] = {0.0};
    int i = start;

    /*Caculate total number before dot*/
    for( i = start; array[i] != '.'; ++i){
        if( array[i] >= 'A'){
            number[i] = array[i] - 55;  //convert 16 to 10
            continue;
        }
        number[i] = array[i] - 48;
    }

    for( i = start; array[i] != '.'; ++i)
        sum = sum*radix + number[i];
    
    /*Caculate total number behind dot*/
    float f_radix = radix*1.0;
    float reciprocal = 1/f_radix;

    for( i = i+1; array[i] != '\0'; ++i){
        if( array[i] >= 'A'){
            number[i] = array[i] - 55;  //convert 16 to 10
            continue;
        }
        number[i] = array[i] - 48;
    }

    for( i-=1; array[i] != '.'; --i)
        dots = dots*reciprocal + number[i];
    
    dots *= reciprocal;

    printf("float number is: %lf\n",sum+dots);

    return sum+dots;
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error\n");    //输出ERROR
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    printf("Out of memory error\n");    //输出ERROR
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->type = Void;
  }
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    printf(" ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          printf("If\n");
          break;
        case WhileK:
           printf( "While\n");
          break;
        case AssignK:
           printf( "Assign to: %s\n",tree->attr.name);
          break;
        case InK:
           printf( "In: %s\n",tree->attr.name);
          break;
        case OutK:
           printf( "Out\n");
          break;
        default:
           printf( "Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
           printf( "Op: ");
          printToken(tree->attr.op);
          break;
        case InterK:
           printf( "Integer: %d\n",tree->attr.ival);
          break;
        case FloK:
           printf( "Float: %lf\n",tree->attr.fval);
        break;
        case IdK:
           printf( "Id: %s\n",tree->attr.name);
          break;
        default:
           printf( "Unknown ExpNode kind\n");
          break;
      }
    }
    else  printf( "Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}