int main() 
{
  setlocale(LC_ALL, "");
  int token;

  while (token = yylex())
  {
    switch (token)
    {
      case PLUS:
        printf("PLUS\n");
        break;
      
      case MINUS:
        printf("MINUS\n");
        break;
      
      case TIMES:
        printf("TIMES\n");
        break;
      
      case DIVIDES:
        printf("DIVIDES\n");
        break;
      
      case RAISED:
        printf("RAISED\n");
        break;
      
      case INTEGER:
        printf("INTEGER(%d)\n", yylval);
        break;
    }
  }
}