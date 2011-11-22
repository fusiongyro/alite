#include "util.h"

/* This should eventually actually implement converting from one base
   to another, but the API will probably have to change first. */
int baseconvert(int value, int base)
{
  if (base == 10)
    return value;
  
  else
    return value / 2;
}
