//all rights reserved Jusin VanderBrake
#ifndef COMP_AST
#define COMP_AST

#include "predec.hpp"
#include "operator.hpp"
#include "expression.hpp"

class Ast {
  public:
    /**
     * Constructs a leaf node which may then be paired with another leaf and 
     * an operator to begin constructing the ast.
     */
    Ast(Val leaf);
    ~Ast();
    
    /**
     * Navigates the tree and reduces it to a series of expressions.
     * @implementer This function is allowed to generate additional vals to
     *              facilitate creating expressions(two address code) provided
     *              it does not change any of the existing values in the tree
     *              as they will be used by valmap to do value replacement.
     * @return a list of val expression pairs starting at the bottom of the ast
     *          working upwards.  Most but not all expressions will be assigned
     *          a value i.e. those which it does not make sense to assign a
     *          value too, while, if, list or tuple elemenets, ...
     */
     ValExpressionList generate_expressions() const;
     
     /**
      * Adds the passed in operator Ast pair as the parent of the current ast
      * with the @this as the right node and @left as the left node
      * @arg op the operator to place at the top of the new tre.
      * @arg left the left node for the top of the new tree.
      * @this the right node for the top of the new tree.
      * @return the augmented Ast.
      */
     Ast_sptr add_parent_left(OPERATOR op, Ast_sptr left);
     
     /**
      * Adds the passed in operator Ast pair as the parent of the current ast
      * with the @this as the left node and @right as the right node
      * @arg op the operator to place at the top of the new tree.
      * @arg right the right node for the top of the new tree.
      * @this the left node for the top of the new tree.
      * @return the augmented Ast.
      */
     Ast_sptr add_parent_right(OPERATOR op, Ast_sptr right);
     
     /**
      * @return a deep clone of @this.
      */
     Ast_sptr clone();
     
     /**
      * Generates a string representation of this ast for printing purposes.
      * Please see the project 3 requirements on the output format.
      */
     std::string to_string();
    
  protected:
    
    
    
  private:
    Ast();
  /**
   * If l_leaf left is a Val
   * If r_leaf right is a Val
   * If operator only takes one argument right will be null.
   */
    typedef struct node {
      bool leaf;
      OPERATOR op;
      struct node* left;
      struct node* right;
      Val_sptr data;
    } node;
    typedef node* Node;
    /**
     * The top of the ast.
     */
    Node head;
    
    Node newNode();
    ValExpressionList traverseTree();
};

#endif
