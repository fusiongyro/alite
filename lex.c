#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <wctype.h>
#include <stdbool.h>

#define MAX_IDENT 1024

/*
 * Lexing module. Converts input characters into tokens handled by yacc.
 */

#include "y.tab.h"

/* Convert a unicode superscript into a digit */
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

/* Convert a unicode subscript into a digit */
int unicodeSubscriptToDigit(wint_t code)
{
  
}

bool isASimpleToken(wchar_t tok)
{
  return tok == L'+'  ||   tok == L'-'  ||
         tok == L'*'  ||   tok == L'/'  || 
         tok == L'^'  ||   tok == L'('  || 
         tok == L')'  ||   tok == L'\n' || 
         tok == L'×'  ||   tok == L'÷'  ||
         tok == L'↑'  ||   tok == L'←';
}

/* Gateway method: return the next token in standard input. */
int yylex()
{
  wint_t next;
  
  while ((next = fgetwc(stdin)) != WEOF)
  {
    /* simple tokens */
    if (next == L'+')                       return PLUS;
    else if (next == L'-')                  return MINUS;
    else if (next == L'×' || next == L'*')  return TIMES;
    else if (next == L'÷' || next == L'/')  return DIVIDES;
    else if (next == L'↑' || next == L'^')  return RAISED;
    else if (next == L'(')                  return LPAREN;
    else if (next == L')')                  return RPAREN;
    else if (next == L'\n')                 return NEWLINE;
    else if (next == L'←')                  return ASSIGN;

    /* compound tokens */
    else if (next == L':')
    {
      if ((next = fgetwc(stdin)) == L'=')
	return ASSIGN;
      else
	return -1;
    }

    /* unicode superscripts */
    else if (unicodeSuperscriptToDigit(next) >= 0)
    {
      yylval.expt = unicodeSuperscriptToDigit(next);
      while ((next = fgetwc(stdin)) && unicodeSuperscriptToDigit(next) >= 0)
        yylval.expt = yylval.expt * 10 + unicodeSuperscriptToDigit(next);
      
      ungetwc(next, stdin);
      return EXPT;
    }

    /* unicode subscripts */
    else if (next >= L'₀' && next <= L'₉')
    {
      yylval.base = next - L'₀';
      
      while ((next = fgetwc(stdin)) >= L'₀' && next <= L'₉')
        yylval.base = yylval.base * 10 + (next - L'₀');
      
      ungetwc(next, stdin);
      return BASE;
    }

    /* integers */
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

    /* identifiers */
    else if (iswalpha(next))
    {
      // start loading up an identifier
      yylval.ident = malloc(sizeof(wchar_t) * MAX_IDENT);
      
      int i = 0;
      yylval.ident[i++] = next;
      
      // read some more text
      while ((next = fgetwc(stdin)) && iswgraph(next) && !isASimpleToken(next) && i < 1023)
	yylval.ident[i++] = next;
      yylval.ident[i] = L'\0';

      ungetwc(next, stdin);
      return IDENT;
    }
  }
  
  return 0;
}
