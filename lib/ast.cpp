#include "ast.hpp"

#include <string>
#include <>
//all rights reserved Jusin VanderBrake

/**
 * Constructs a leaf node which may then be paired with another leaf and 
 * an operator to begin constructing the ast.
 */
Ast::Ast(Val leaf)
{
  Node head;
  head.leaf = true;
  head.op = NULL;
  head.left = NULL;
  head.right = NULL;
  head.data = leaf;
}//Ast

Ast::~Ast()
{
  //delete head; //smart pointers will kill themselves
}// ~Ast



/**
 * Navigates the tree and reduces it to a series of expressions.
 * @implementer This function is allowed to generate additional vals to
 *              facilitate creating expressions(two address code) provided
 *              it does not change any of the existing values in the tree
 *              as they will be used by valmap to do value replacement.
 * @return a list of val expression pairs starting at the bottom of the ast
 *          working upwards.  Every expression will be assigned a unique
 *          value here which may be eliminated later by the valmap when
 *          value numbering is preformed.
 */
ValExpressionList Ast::generate_expressions()
{
  // yay recurtion.
  return traverse_Tree(head);
  // return NULL // just for alex. B-) but really this ---
  // --- std::pair<v22, v11 + v13>
}



/**
  * Adds the passed in operator Ast pair as the parent of the current ast
  * with the @this as the left node and @right as the right node
  * @arg op the operator to place at the top of the new tree.
  * @arg left the left node for the top of the new tree
  * @this the right node for the top of the new tree.
  * @return the augmented Ast.
  */
Ast_sptr Ast::add_parent_left(OPERATOR op, Ast_sptr left)
{
  #ifdef DEBUG
    if (left == NULL)
    {
      fprintf(stderr, "DEBUG: ast.cpp: add_parent_left(OPERATOR op, Ast left): left is NULL");
    }
    if (left->head == NULL)
    {
      fprintf(stderr, "DEBUG: ast.cpp: add_parent_left(OPERATOR op, Ast left): left->head is NULL");
    }
  #endif
  Node temp = newNode();
  temp.op = op;
  temp.left = left->head;
  head = temp;
  return this;
}

/**
 * same as the left but right(as opposed to wrong...)
 */
Ast_sptr Ast::add_parent_right(OPERATOR op, Ast_sptr right)
{
  #ifdef DEBUG
    if (right == NULL)
    {
      fprintf(stderr, "DEBUG: ast.cpp: add_parent_right(OPERATOR op, Ast right): right is NULL");
    }
    if (right->head == NULL)
    {
      fprintf(stderr, "DEBUG: ast.cpp: add_parent_right(OPERATOR op, Ast right): right->head is NULL");
    }
  #endif
  Node temp = newNode();
  temp.op = op;
  temp.right = right->head;
  head = temp;
  return this;
}


//allocates a new node on the heap and sets some default values
Ast::Node Ast::newNode()
{
  Node temp = malloc(sizeof(struct node));
  temp.leaf = false;
  temp.op = -1;
  temp.left = NULL;
  temp.right = NULL;
  temp.data = NULL;
  return temp;
}


/**
 * traverses the tree in a left->right->current...ish it uses data from three
 * nodes at once to make an expression list and it's RECURSIVE yay.
 * the definition of a ValExpressionList is:
 * typedef std::vector<std::pair<Val_sptr, Expression_sptr> > ValExpressionList;
 */
ValExpressionList Ast::traverse_Tree(Node current);
{
  // just the idea right now. NOT functional!
  if ((current->left == NULL) && (current->right == NULL))
  {// create a new list because we are at the bottom of the tree.
    ValExpressionList VEList = new ValExpressionList;
    std::pair <Val_sptr, Expression_sptr> aPair;
    aPair = std::make_pair(current.data ,NULL);
    VEList.push_back (aPair);
    return VEList;
  }
  else if (current->left == NULL)
  {
    ValExpressionList rightData = traverse_Tree(current->right);
    std::pair <Val_sptr, Expression_sptr> aPair;
    aPair = std::make_pair(new Val(/*Type_sptr type*/),
      new Expression(current->op, current->right->data, NULL));
    rightData.push_back (aPair);
  }
  else if (current->right == NULL)
  {
    ValExpressionList leftData = traverse_Tree(current->left);
    std::pair <Val_sptr, Expression_sptr> aPair;
    aPair = std::make_pair(new Val(/*Type_sptr type*/),
      new Expression(current->op, current->left->data, NULL));
    leftData.push_back (aPair);
  }
  else
  {
    ValExpressionList combined;
    ValExpressionList leftData = traverse_Tree(current->left);
    ValExpressionList rightData = traverse_Tree(current->right);
    combined.reserve(leftData.size() + rightData.size);
    combined.insert(combined.end(), leftData.begin(), leftData.end());
    combined.insert(combined.end(), rightData.begin(), rightData.end());
    std::pair <Val_sptr, Expression_sptr> aPair;
    
    aPair = std::make_pair(new Val(/*Type_sptr type*/),
      new Expression(current->op, current->left->data, current->right->data));
    combined.push_back (aPair);
  }
  
  return combined;
}


/**
 * if you don't know what a to_String is...  well...
 */
std::string Ast::to_string()
{
  
}
