#include "val.hpp"

/**
 * Generates a unique Val where the symbol is of the form "V<uid>"
 * Type must be deep cloned to prevent data corruption.
 */
Val::Val(Type& type) : uid(get_next_uid()), type(type.clone()){}

/**
 * Generates a unique Val with the given symbol
 * Type must be deep cloned to prevent data corruption.
 */
Val::Val(std::string name, Type& type) : uid(get_next_uid()), type(type.clone()), symbol(name){}


size_t Val::get_next_uid() {
    static size_t next_uid = 0;
    size_t uid = next_uid;
    next_uid++;
    return uid;
}

std::string Val::get_symbol(){
  return symbol;
}

Type& Val::get_type(){
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
short Val::val_compare(Val& val){
  return val_compare_uid(val.get_uid());
}

short Val::val_compare_uid(size_t o_uid){
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
  return type.equals(val.get_type());
}

std::string Val::to_string(){
  return symbol + ":" + type.to_string();
}
