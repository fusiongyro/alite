#include <stdio.h>
#include <math.h>
#include <wchar.h>

#include "y.tab.h"

int yylex()
{
  wint_t next;
  
  while ((next = fgetwc(stdin)) != WEOF)
  {
    if (next == L'+')
      return PLUS;
    else if (next == L'-')
      return MINUS;
    else if (next == L'×' || next == L'*')
      return TIMES;
    else if (next == L'÷' || next == L'/')
      return DIVIDES;
    else if (next == L'↑' || next == L'^')
      return RAISED;
    else if (next == L'\n')
      return NEWLINE;
    else if (next >= L'0' && next <= L'9')
    {
      // convert to some kind of integer
      yylval = next - L'0';
      
      // read some more text
      while ((next = fgetwc(stdin)) >= L'0' && next <= L'9')
        yylval = yylval * 10 + (next - L'0');
      
      ungetwc(next, stdin);
      return INTEGER;
    }
  }
  
  return 0;
}
