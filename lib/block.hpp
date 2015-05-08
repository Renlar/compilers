#ifndef COMP_BLOCK
#define COMP_BLOCK

#include <iostream>
#include <string>
#include <utility>

#include "predec.hpp"

class Block {
  public:
    
    Block(Scope& parent);
    
    ~Block();
    
    /**
     * One or both pointers may be null depending on the block's position
     * in the flow graph.
     */
    std::pair<Block&, Block&> get_follow();
    
    Scope& get_parent();
    
    std::string& get_name() const;
    
    void set_parent(Scope& parent);
    
    void set_ast(Ast& ast);
    
    Ast& get_ast();
    
    
    
  protected:
    
    
    
  private:
    
    Block();
    
    static size_type available_uid = 0;
    size_type uid;
    Scope_wptr parent;
    
    /**
     * For backtracking purposes
     */
    WeakBlockList previous;
    
    std::pair<Block, Block> follow;
    
    /**
     * Stores the entire origional text for the block.
     */
    std::stringstream raw;
    
    /**
     * Stores the entire ast for the block;
     */
    Ast ast;
    
    /**
     * Stores the value numbering for all expressions in the block.  This 
     * is enought to regenerate an equivalent block of code with redundant
     * values eliminated.  Assigns arbitrary names to each value may create 
     * additional assignments to facilitate redundant value elimination.
     */
    ValMap valmap;
};

#endif