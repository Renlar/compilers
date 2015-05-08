#ifndef COMP_VALMAP
#define COMP_VALMAP

#include <cstdlib>
#include <string>
#include <utility>

#include "predec.hpp"
#include "operator.hpp"

class ValMap {
  public:
    /**
     * Initialize a new value map.
     */
    ValMap();
    ~ValMap();
    
    /**
     * Generates value entries in the code list to represent the values in the 
     * passed in Ast.  Reads ast from bottom to top one operator leaf pair at a
     * time.
     * 
     * @implementer Uses Val(Type) to generate a unique value assignment for each
     *              expression.  No valueson the right hand side of the three 
     *              addresss code will be used directly except when they first
     *              appear and we assign them to a new unique Val.
     * 
     * @arg input 3 address code to perform value analysis on and generate entry code
     *       list entries from.
     */
    void insert(ValExpressionList& input);
    
    /**
     * Generates a source block from @code avoids all variable names which were
     * defined in the origional code.  Prefering to use the generated values
     * stored in @code instead.  This means when we create an assignment the variable
     * name in the expresion of @code will be replaced with the variable name on
     * the right sode of @code.
     */
    std::string regenerate_code();
    
    /**
     * Applies the rules in @map to @code.  This causes a rebuild of
     * @code using any values which are previously defined in @map.  Also
     * appends all new values contained in @code to @map in order.
     * 
     * @implementer When rebuilding @code using rules from @map you must perform
     *              a replacementfor every value which is not newly defined in
     *              @code.  This involves potentially replacing/rebasing all
     *              values defined without a corresponding fun or val keyword.
     *              So if we have a value c which is assigned a val v1 and c also
     *              appears in @map as v6 we must remove the rule assigning c to 
     *              v1 and replace every occurance of v1 with v6 this includes
     *              searching the indexes of the maps for occurances of v1.
     *              Once this operation has been performed for every value in
     *              @code we then eliminate expressions from @code which also
     *              appear in @map.  Once all redundancy has been removed from
     *              @code we append @expval_map to @map and exit the function.
     * 
     * @arg map the map to use as the basis for rebuilding this map.
     */
     void update(ValMap& map);
     
     /**
      * Performs a clone of the maps and code list
      */
     ValMap clone();
    
  protected:
    
    
    
  private:
    
    /**
     * Structure definition:  Stores expression value mappings for value
     * replacement computations
     * @implementer map is only an interface definition you will need to include
     *              an actuall implementation of map in the cpp file.
     */
    ExpressionValMap expval_map;
    
    /**
     * A mapping of each value to all the expressions it is used in, used for
     * remapping values during multi block value numbering.
     */
    ValExpressionMap valexp_map;
    
    /**
     * All the structure data required to build equivalent code.  This structure
     * contains vals which should never show up in either of the maps as no
     * value replacement can be performed on them.  e.g. while, if, and fun.
     */
    ValExpressionList code;
    
    /**
     * A list of values to ignore when updating
     */
    ValList scoped_vals;
    
    //integer to keep track of most recently used arbitrary variable
    int arbCounter;
    
    void ValMap::MapNonAssign(Expression expr);
    
    void ValMap::MapAssign(Val_sptr target, Expression expr);
    
    //maps a val to an arbitrary arg name in the tables
    Val_sptr ValMap::MapArg(Val_sptr arg);
};

#endif
