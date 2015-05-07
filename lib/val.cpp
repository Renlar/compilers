#include "val.hpp"

/**
 * The unique id for this val.  Note: only unique among vals.
 */
size_t uid;
Type_sptr type;
//Note: if the type is a const then symbol contains the value of the const.
std::string symbol;

/**
 * Private since a Val without a type would make code reconstrution
 * impossible for some statements.
 * e.g. val : int list a = ... and fun get_elem(a : int, b : int list) = ...
 */
Val::Val(){
  type = NULL;
  uid = get_next_uid();
}

/**
 * Generates a unique Val where the symbol is of the form "V<uid>"
 * Type must be deep cloned to prevent data corruption.
 */
Val::Val(const Type_sptr type){
  this->type = type->clone();
  uid = get_next_uid();
}

/**
 * Generates a unique Val with the given symbol
 * Type must be deep cloned to prevent data corruption.
 */
Val::Val(std::string name, const Type_sptr type){
  symbol = name;
  this->type = type->clone();
  uid = get_next_uid();
}


size_t Val::get_next_uid() {
    static size_t next_uid = -1;
    next_uid++;
    return next_uid;
}

std::string Val::get_symbol(){
  return symbol;
}

const Type_sptr Val::get_type(){
  return type;
}

size_t Val::get_uid(){
  return uid;
}

/**
 * Compares the symbol of this val to @val
 * @arg val the value to compare with
 * @return true if this.symbol and val.symbol are equal.
 */
bool Val::symbol_equal(Val& val){
  return symbol.compare(val.get_symbol()) == 0;
}

/**
 * Compares the uid of this val to @val
 * @arg val the value to compare with
 * @return -1 if @this < @val
 *          0 if @this == @val
 *          1 if @this > @val
 */
unsigned short Val::val_compare(Val_sptr val){
  if(val != NULL){
    unsigned long o_uid = val->get_uid();
    return val_compare_uid(o_uid);
  }else{
    return 1;
  }
}

unsigned short Val::val_compare_uid(unsigned long o_uid){
    if(uid < o_uid){
      return -1;
    }else if(uid == o_uid){
      return 0;
    }else{
      return 1;
    } 
}

/**
 * Compares the types of @this and @val
 * @return true if the types are compatable false otherwise.
 */
bool Val::type_equal(Val& val){
  return type == val.get_type();
}

std::string Val::to_string(){
  return symbol + ":" + type->to_string();
}