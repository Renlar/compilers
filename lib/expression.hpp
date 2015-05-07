//all rights reserved Jusin VanderBrake
#ifndef COMP_EXPRESSION
#define COMP_EXPRESSION

#include "predec.hpp"
#include "val.hpp"
#include "operator.hpp"

class Expression {
  public:
    /**
     * create a new expression.
     * @implementer must check validity of input and report debug error if not
     *              valid.  i.e. check that the operator and agrument counts match.
     */
    Expression(OPERATOR op);
    Expression(OPERATOR op, Val_sptr v1);
    Expression(OPERATOR op, Val_sptr v1, Val_sptr v2);
    
    ~Expression();
    
    OPERATOR get_op() const;
    
    /**
     * @impelmenter print debug warning if arg1 is null.
     */
    Val_sptr get_arg1() const;
    
    /**
     * @impelmenter print debug warning if arg2 is null.
     */
    Val_sptr get_arg2() const;
    
    /**
     * Find and return the type this expression generates when evaluated.
     */
     Type_sptr compute_type();
    
    /**
     * comparison operator defined in order for std::map to work correctly with 
     * Expressions as keys.  Note if the expression contains no values it exists
     * for structure information only and should never be compared using this 
     * @implementer You must take into account all elements of this class
     *              e.g. compare @this.v1.uid with @rhs.v1.uid, if they are
     *              equal continue to comparing v2s then finally the operators.
     */
    bool operator< (const Expression& rhs);
    
    /**
     * @return a valid ml representation of this expression.
     */
    std::string to_string() const;
    
  protected:
    
    
    
  private:
    Expression();
    OPERATOR op;
    Val_sptr v1;
    Val_sptr v2;
};

#endif//COMP_EXPRESSION
