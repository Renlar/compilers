//all rights reserved Jusin VanderBrake
#ifndef COMP_VAL
#define COMP_VAL

#include <cstdlib>
#include <string>

#include "type.hpp"


// TODO: Add a stored line number so we can report informative type errors to 
// the user.  e.g. a was declared on line x with type <type> and b was declared
// on line y with type <type> used on line <line> with incompatable opeartor <op>.

class Val {
  public:
    /**
     * Generates a unique Val where the symbol is of the form "V<uid>"
     * Type must be deep cloned to prevent data corruption.
     */
    Val(const Type_sptr type);
    
    /**
     * Generates a unique Val with the given symbol
     * Type must be deep cloned to prevent data corruption.
     */
    Val(std::string name, const Type_sptr type);
    
    /**
     * Empty Destructor, no manual cleanup necessary
     */
    ~Val(){}
    
    std::string get_symbol();
    
    const Type_sptr get_type();
    
    size_t get_uid();
    
    /**
     * Compares the symbol of this val to @val
     * @arg val the value to compare with
     * @return true if this.symbol and val.symbol are equal.
     */
    bool symbol_equal(Val& val);
    
    /**
     * Compares the uid of this val to @val
     * @arg val the value to compare with
     * @return -1 if @this < @val
     *          0 if @this == @val
     *          1 if @this > @val
     */
    unsigned short val_compare(Val_sptr val);
    
    unsigned short val_compare_uid(unsigned long o_uid);
    
    /**
     * Compares the types of @this and @val
     * @return true if the types are compatable false otherwise.
     */
    bool type_equal(Val& val);
    
    /**
     * @return a valid ml representation of this value.
     */
    std::string to_string();
    
  protected:
    
    
    
  private:
    /**
     * Private since a Val without a type would make code reconstrution
     * impossible for some statements.
     * e.g. val : int list a = ... and fun get_elem(a : int, b : int list) = ...
     */
    Val();
    
    /**
     * The unique id for this val.  Note: only unique among vals.
     */
    size_t uid;
    Type_sptr type;
    //Note: if the type is a const then symbol contains the value of the const.
    std::string symbol;
    
    /**
     * Return the next available uid.
     */
    size_t get_next_uid();
};

#endif
