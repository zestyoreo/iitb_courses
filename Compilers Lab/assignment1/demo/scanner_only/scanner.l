%{

#include "scanner.hh"
#include <fstream>
#include <string>
#define YY_DECL int Scanner::yylex()

struct token
    {
      enum yytokentype
      {
        MNEMONIC = 258,
        NUMBER = 259,
        IMMNUMBER = 260,
        REGISTER = 261,
        SYMBOL = 262,
        IMMSYMBOL = 263,
        EOFILE = 264,
        OTHERS = 265,
      };
    };
%}


/* %option debug */
%option nodefault
%option yyclass="Scanner"
%option noyywrap
%option c++

%%

%{          /** Code executed at the beginning of yylex **/
      FlexLexer::yy_flex_debug = 1;
%}
[ \t]                                       //skip
(push|mov|and|sub)l|call|leave|ret          return token::MNEMONIC;
(-?)[[:digit:]]+                            return token::NUMBER;
"$"(-?)[[:digit:]]+                         return token::IMMNUMBER;  
"%"(ebp|esp|edx|eax|esp)                    return token::REGISTER;     
[[:alpha:]][[:alnum:]]*                     return token::SYMBOL;
"$"("."?)[[:alpha:]][[:alnum:]]*            return token::IMMSYMBOL;
"+"                                         return '+';
","                                         return ',';
"("                                         return '(';
")"                                         return ')';
":"                                         return ':';    
"\n"                                        return '\n';
<<EOF>>                                  yyterminate();
.				                          return token::OTHERS;
%%

std::string tok_to_string(int tok) 

{
  std::string strval;
   if (tok < 255)
    {
      
      strval = (char)tok;
      return strval;
    }
   else 
    {
      switch ((token::yytokentype) tok) 
      {
        case token::MNEMONIC: return "MNEMONIC";
        case token::NUMBER: return "NUMBER";
        case token::IMMNUMBER: return "IMMNUMBER";
        case token::REGISTER: return "REGISTER";
        case token::SYMBOL: return "SYMBOL";
        case token::IMMSYMBOL: return "IMMSYMBOL";
        case token::EOFILE: return "EOFILE";
        case token::OTHERS : return "OTHERS";        
    }
  }
  return "";
}

int main( int /* argc */, char** /* argv */ )
{ 
  using namespace std;
  fstream in_file, out_file;
  in_file.open("test-assembly.s", ios::in);
  out_file.open("test-assembly-output", ios::out);
  Scanner scanner(in_file, out_file);
  int tok = scanner.yylex ();

  while(tok != 0)
    {
      out_file << "_______________________________" << endl;
      out_file << "The token is:" << endl;
      out_file << tok_to_string(tok) << endl;
      out_file << "The lexeme is:" << endl;
      out_file << scanner.YYText() << endl;
      tok = scanner.yylex();
    }
  return 0;

}
