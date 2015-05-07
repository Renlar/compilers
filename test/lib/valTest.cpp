#include <stdio.h>
#include <iostream>
#include <string>
#include </home/ubuntu/workspace/proj4/lib/val.hpp>

int main(){
  Type_sptr type1(new Type(INT_T));
  Type_sptr type2(new Type(REAL_T));
  Val_sptr val(new Val(type1));
  Val_sptr val1(new Val(type2));
  std::cout << val1->get_uid();
}