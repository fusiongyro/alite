#include <stdio.h>
#include <math.h>
#include <wchar.h>

#include "y.tab.h"

int unicodeSuperscriptToDigit(wint_t code)
{
  switch (code)
  {
    case L'⁰': return 0;    case L'¹': return 1;
    case L'²': return 2;    case L'³': return 3;
    case L'⁴': return 4;    case L'⁵': return 5;
    case L'⁶': return 6;    case L'⁷': return 7;
    case L'⁸': return 8;    case L'⁹': return 9;
    default: return -1;
  }
}

int unicodeSubscriptToDigit(wint_t code)
{
  
}

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
    else if (unicodeSuperscriptToDigit(next) >= 0)
    {
      yylval.expt = unicodeSuperscriptToDigit(next);
      while ((next = fgetwc(stdin)) && unicodeSuperscriptToDigit(next) >= 0)
        yylval.expt = yylval.expt * 10 + unicodeSuperscriptToDigit(next);
      
      ungetwc(next, stdin);
      return EXPT;
    }
    else if (next >= L'₀' && next <= L'₉')
    {
      yylval.base = next - L'₀';
      
      while ((next = fgetwc(stdin)) >= L'₀' && next <= L'₉')
        yylval.base = yylval.base * 10 + (next - L'₀');
      
      ungetwc(next, stdin);
      return BASE;
    }
    else if (next >= L'0' && next <= L'9')
    {
      // convert to some kind of integer
      yylval.value = next - L'0';
      
      // read some more text
      while ((next = fgetwc(stdin)) >= L'0' && next <= L'9')
        yylval.value = yylval.value * 10 + (next - L'0');
      
      ungetwc(next, stdin);
      return INTEGER;
    }
  }
  
  return 0;
}
