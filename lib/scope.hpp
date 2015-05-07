#ifndef COMP_SCOPE
#define COMP_SCOPE

#include <iostream>
#include <string>
#include <vector>

#include "predec.hpp"

class Scope {
  public:
    
    Scope(std::string& name, Scope_wptr parent);
    
    ~Scope();
    
    std::string& get_name();
    
    BlockList& get_blocks();
    
    Scope_wptr get_parent();
    
    Block_sptr get_current_block();
    
    Block_sptr get_first_block();
    
    bool identifier_defined();
    
    
    
  protected:
    
    
    
  private:
    
    Scope();
    static Scope_sptr global;
    std::string name;
    Scope_wptr parent;
    Block_sptr current;
    BlockList& blocks;
    ScopeList& scopes;
    std::vector<Val> identifiers;
};

#endif//COMP_SCOPE
