#ifndef _PARSE_H_
#define _PARSE_H_

# include "type.h"
# include "scan.h"

/*进制转换*/

/*convert interger*/
int convertI(const char *, int radix, int start);

/*convert float*/
float convertF(const char *, int radix, int start);

/*Main function of parsing*/
TreeNode * parse();

/*新建节点*/

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);

/*输出语法树*/

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

#endif