
Scope_sptr Scope::global = NULL;

Scope() {
}

Scope(std::string& name, Scope& parent, Scope& previous) {
  
}

~Scope() {
  
}

Scope& get_child() {
  return child;
}

Scope& get_parent() {
  return parent;
}

Scope& get_next() {
  return next;
}

Scope& get_previous() {
  return previous;
}

void set_child(Scope& child) {
  this->child = child;
  child.set_parent(*this);
}

void set_parent(Scope& child) {
}

void set_next(Scope& child) {
  
}

void set_previous(Scope& previous) {
  #ifdef DEBUG
  if (previous) {
    std:cerr << "\n";
  }
  #endif
  this->previous = previous;
  
}
