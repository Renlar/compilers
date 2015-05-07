#include "valmap.hpp"

#include "expression.hpp"
#include "val.hpp"

ValMap::ValMap(){
  //placeholder
  //pick map implementation
  valexp_map = *(new ValExpressionMap());
  expval_map = *(new ExpressionValMap());
  arbCounter = 0;
}
  
void ValMap::insert(ValExpressionList& input){  #ifdef DEBUG
  if (input == NULL){
    fprintf(stderr, "DEBUG: ValMap.cpp: insert(const Ast_sptr): NULL POINTER";
  }
  #endif
  for(auto line : input){
    // storage register from three address code
    Val_sptr varAssn = line.first;
    // what to store in register from three address code
    Expression_sptr expr = line.second;
    
    if(varAssn == NULL){
      MapNonAssign(expr);
    }else{
      MapAssign(target, expr);
    }
  }//endfor
}

void ValMap::MapNonAssign(Expression expr){
  //direct store the expression
  code.insert(code.end(), new ValExpression(new Val_sptr(NULL), expr);
}

void ValMap::MapAssign(Val_sptr target, Expression expr){
  //map all variables in the expression and store expression
  
  /* integer containing enum value of operator */
  OPERATOR lineOp = expr.get_op();
  /* Val containing value replace target */
  Val_sptr arg1 = expr.get_arg1();
  /* Val containing value replace target */
  Val_sptr arg2 = expr.get_arg2();
  
  if(arg2 != NULL){ //if we have 2 args
    //linepart1 will never be null here
    Val_sptr new1 = MapArg(arg1);
    Val_sptr new2 = MapArg(arg2);
    Map2Args(linePart1, lineOp, new1, new2);
  }else if(arg1 != NULL){ //if we have 1 arg
    //linepart1 may be null here
    MapArg(arg1);
    Map1Arg(linePart1, lineOp, arg1);
  }else{//if we have no args and only an operator
    //linepart1 should be null here
    //if (linepart1 != NULL) return;
    //this should be used on instructions that should not be operated on
    code.insert(code.end(), new ValExpression(target, expr);
  }
}

void ValMap::update(ValMap& map){
  //multi block value mapping
}
  
std::string ValMap::regenerate_code(){
  //take val map and generate code
  return "";
}
  
ValMap ValMap::clone(){
  ValMap newValMap = *(new ValMap());
  newValMap.valexp_map = valexp_map;
  newValMap.expval_map = expval_map;
  newValMap.code = code;
  return newValMap;
}

Val_sptr ValMap::MapArg(Val_sptr arg){
  Val_sptr sTmp(new Val(arg->get_type()));
  
  expval_map.emplace(*sTmp, arg);
  valexp_map.emplace(arg, *sTmp);
  return new ValSptr(sTmp);
}