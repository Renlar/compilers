#ifndef COMP_TYPE
#define COMP_TYPE

#include <string>

#include "predec.hpp"

typedef enum {NULL_B, VOID_B, BOOL_B, INT_B, REAL_B, LIST_B, TUPLE_B, VAL_B, FUN_B} BASE_TYPE;
static const std::string BASE_TYPE_STRING[] = {"NULL", "VOID", "BOOL", "INT", "REAL", "LIST", "TUPLE", "VAL", "FUN"};


class Type {
  public:
    
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
    Type(BASE_TYPE base);//create an empty typelist.
    Type(BASE_TYPE base, TypeList& subtypes);
    ~Type();
    
    
    BASE_TYPE get_base_type();
    
    
    TypeList& get_subtypes();
    
    
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
    bool type_compat(Type& type);
    
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
    bool can_assign(Type& rhs);
    
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
    Type& declare_type(Type& rhs);
    
    /**
     * 
     * @return true if @this is a complete type.  If it is of type list, or ref
     *         it must have another base type defined i.e. int, bool, or real.
     */
     bool is_complete_type();
     
     /**
      * Check if two types are equal.
      * @arg rhs the type to comare @this against.
      * @return true iff @this == @rhs
      */
      bool equals(Type& rhs);
    
    /**
     * Generate the type string for this type as required by the ml spec.
     * e.g. " : int ref ref list ref "
     */
    std::string to_string();
    
    /**
     * Deep clone @this type object.
     * 
     * Simply call deep clone on each type in @subtypes and add to a vactor
     * which is then passed into the type constructor.
     * 
     * @return a deep clone of this type.
     */
    Type& clone();
    
  protected:
    
    
    
  private:
    Type();
    
    BASE_TYPE base;
    TypeList subtypes;
};

#endif
