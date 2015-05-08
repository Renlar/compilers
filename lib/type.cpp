#include "type.hpp"

Type::Type(){ //construtor is private it will never be called.
  base = NULL_B;
}

/**
 * Build a new type with the given type list. Does not clone the typelist.
 * 
 * @implementer the list of subtypes must contain:
 *              --all the same type for a list and will be reduced to a
 *                single element.
 *              --A single type for a ref.
 *              --no types for a bool, real, or int
 *              --two types for a Fun the first of which is the return type
 *                which can be any valid type except a TUPLE. The second
 *                type will be a tuple or any single type which will be
 *                converted to a tuple when @this is created.
 * 
 */
Type::Type(BASE_TYPE base, TypeList& subtypes) : base(base){
  this->subtypes.insert(this->subtypes.end(), subtypes.begin(), subtypes.end());
}

Type::Type(BASE_TYPE base) : base(base){
}

BASE_TYPE Type::get_base_type(){
    return base;
}


TypeList& Type::get_subtypes(){
    return subtypes;
}


/**
 * Check if @this and @type are compatable.
 * 
 * @implementer this method will be very long break it up into functions
 *              for each type compat check to keep it clean and easy to
 *              debug, verify, and modify as there will be errors in the
 *              initial implementaion.  See @project2 spec for which types
 *              are compatable.  Note a "ref int" and a "int" are not
 *              compatable, unless they are usd in an assignment which is
 *              handled by the can_assign method, types you
 *              must dereference the ref int to use it in an expression.
 *              This function may also be used to compare if a function call
 *              input type is valid, thus it must handle tuples.
 *              List are to be treated as if they are c arrays sublists of
 *              a list must have the same type.
 * 
 * @return true if @this is compatable with @type false otherwise.
 */
bool Type::type_compat(Type& type){
    return false;
}

/**
 * Check if an assignment can be performed.
 * 
 * @implementer this method is similar to type_compat with a few additional 
 *              rules. A value may not be assigned if the lhs is 
 *              not of the reference type.  The right hand side, @this,
 *              must be compatable with the dereferenced type of @this.
 *              Should not handle tuples.
 * 
 * @return true if @rhs can be assigned to @this.
 */
bool Type::can_assign(Type& rhs){
    return true;
}

/**
 * Compute the type for a variable or function declairation.  May take type
 * information from both sides of the declaration to generate the final type.
 * defaults to @this and check @rhs if the type is incomplete in order to
 * to determine the final type for the expression.
 * @arg rhs the type of the expression on the right hand side of the
 *      declaration.
 * @return the computed type for an assignment where @this is the var type
 *         and @rhs is the expression type.
 */
Type& Type::declare_type(Type& rhs){
    return *this;
}

/**
 * 
 * @return true if @this is a complete type.  If it is of type list, or ref
 *         it must have another base type defined i.e. int, bool, or real.
 */
 bool Type::is_complete_type(){
     return true;
 }
 
/**
 * Check if two types are equal.
 * @arg rhs the type to comare @this against.
 * @return true iff @this == @rhs
 */
bool Type::equals(Type& rhs){ // TODO : add recursive call to check subtypes.
      if(rhs.get_base_type() == base){
          return true;
      }else{
          return false;
      }
}

/**
 * Generate the type string for this type as required by the ml spec.
 * e.g. " : int ref ref list ref "
 */
std::string Type::to_string(){
  return BASE_TYPE_STRING[base];
}

/**
 * Deep clone @this type object.
 * 
 * Simply call deep clone on each type in @subtypes and add to a vactor
 * which is then passed into the type constructor.
 * 
 * @return a deep clone of this type.
 */
Type& Type::clone() {
  TypeList list(*(new TypeList()));
  
  for(auto it : this->subtypes) {
    list.insert(list.end(), it.clone());
  }
  
  return *(new Type(this->base, list));
}