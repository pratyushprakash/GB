#include "color.hpp"

GBColor get_color(uint val){
  switch(val){
  case 0:
    return GBColor::Color0 ;
  case 1:
    return GBColor::Color1 ;
  case 2:
    return GBColor::Color2 ;
  case 3:
    return GBColor::Color3 ;
  default:
    printf("Invalid color value %d\n", val);
  }
}
