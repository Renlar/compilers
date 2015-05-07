//all rights reserved Jusin VanderBrake
#include "expression.hpp"

/**
 * create a new expression.
 * @implementer must check validity of input and report debug error if not
 *              valid.  i.e. check that the operator and agrument counts match.
 */
Expression::Expression(OPERATOR op){
  #ifdef DEBUG
    if (OPERAND_COUNT[op] != 0) {
      fprintf(stderr, "DEBUG: expression.c: Expression(OPERATOR op): op, %s, requires %u arguments.", OPERATOR_STRING[op], OPERAND_COUNT[op]);
    }
  #endif
  this->op = op;
  v1 = NULL;
  v2 = NULL;
}

Expression::Expression(OPERATOR op, Val_sptr v1){
  #ifdef DEBUG
    if (OPERAND_COUNT[op] != 1) {
      fprintf(stderr, "DEBUG: expression.c: Expression(OPERATOR op, Val_sptr v1): op, %s, requires %u arguments.", OPERATOR_STRING[op], OPERAND_COUNT[op];
    }
  #endif
  this->op = op;
  this->v1 = v1;
  this->v2 = NULL;
}

Expression::Expression(OPERATOR op, Val_sptr v1, Val_sptr v2){
  #ifdef DEBUG
  if (OPERAND_COUNT[op] != 2) {
    fprintf(stderr, "DEBUG: expression.c: Expression(OPERATOR op, Val_sptr v1): op, %s, requires %u arguments.", OPERATOR_STRING[op], OPERAND_COUNT[op];
  }
  #endif
  this->op = op;
  this->v1 = v1;
  this->v2 = v2;
}

Expression::~Expression(){
  v1 = NULL;
  v2 = NULL;
}

OPERATOR Expression::get_op() const{
  return op;
}

Val_sptr Expression::get_arg1() const{
  return v1;
}

/**
 * @impelmenter print debug warning if arg2 is null.
 */
Val_sptr Expression::get_arg2() const{
  return v2;
}

Type_sptr Expression::compute_type(){
  if(v1 != NULL && v2 != NULL){
    Type_sptr v1Type = v1->get_type();
    Type_sptr v2Type = v2->get_type();
    if(v1Type->get_base_type() == v2Type->get_base_type()){
      return v1Type;
    }else{
      if(v1Type->get_base_type() == FUNCALL){
        return v1Type;
      }
    }
  }else{
    // Both values are NULL;
    return NULL;;
  }
}

/**
 * @return a valid ml representation of this expression.
 */
std::string Expression::to_string() const{
  std::string output;
  if(v1 != NULL){
    output += v1->to_string();
  }
  
  output += OPERATOR_STRING[op];
  
  if(v2 != NULL){
    output += v2->to_string();
  }
  return output;
}

/**
 * comparison operator defined in order for std::map to work correctly with 
 * Expressions as keys.
 * @implementer You must take into account all elements of this class
 *              e.g. compare @this->v1.uid with @rhs.v1.uid, if they are
 *              equal continue to comparing v2s then finally the operators.
 */
bool Expression::operator< (const Expression& rhs){
    Val_sptr ov1 = rhs.get_arg1();
    Val_sptr ov2 = rhs.get_arg2();
    
    unsigned long ov1Compare;
    unsigned long ov2Compare;
    if(ov1 != NULL){
      ov1Compare = v1->val_compare(ov1);
    }else{
      ov1Compare = v1->val_compare_uid(-1);
    }
    
    if(ov2 != NULL){
      ov2Compare = v2->val_compare(ov1);
    }else{
      ov2Compare = v2->val_compare_uid(-1);
    }
    
    if(ov1Compare < 0 || ov2Compare < 0){
      return true;
    }else if(ov1Compare > 0 || ov2Compare > 0){
      return false;
    }else{
      ov1Compare = OPERAND_COUNT[op];
      ov2Compare = OPERAND_COUNT[rhs.get_op()];
      if(ov1Compare < ov2Compare){
        return true;
      }else{
        return false;
      }
  }
}