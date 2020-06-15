# include "parse.h"

/*This language Design doesn't consider minus situation*/

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