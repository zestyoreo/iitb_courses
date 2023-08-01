%{
// This part goes directly into the generated parser

#include "scanner.hh"
#include "parser.tab.hh"

// YY_DECL is bound to the type of the scanner. The default is 
// #define YY_DECL int Scanner::yylex()
// which is generated anyway.

//If you want the type of the generated scanner to be different, do this

#undef  YY_DECL
#define YY_DECL int IPL::Scanner::yylex( IPL::Parser::semantic_type * const lval, IPL::Parser::location_type *location )

//We want these to be the first action after a token is recognized. 

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

// token_type is a short hand for IPL::Parser::token

using token_type = IPL::Parser::token;

%}


/* %option debug */
%option nodefault
%option yyclass="Scanner"
%option noyywrap
%option c++

%%

%{ /** Code executed at the beginning of yylex **/

      yylval = lval;

%}

[ \t]                             //skip
(push|mov|and|sub)l|call|leave|ret          {   
       yylval->emplace< std::string >( YYText() );
       return token_type::MNEMONIC;
}
(-?)[[:digit:]]+                            {   
       yylval->emplace< std::string >( YYText() );
       return token_type::NUMBER;
}
"$"(-?)[[:digit:]]+                         {   
       yylval->emplace< std::string >( YYText() );
       return token_type::IMMNUMBER;  
}
"%"(ebp|esp|edx|eax|esp)                    {   
       yylval->emplace< std::string >( YYText() );
       return token_type::REGISTER;    
} 
[[:alpha:]][[:alnum:]]*                     {   
       yylval->emplace< std::string >( YYText() );
       return token_type::SYMBOL;
}
"$"("."?)[[:alpha:]][[:alnum:]]*            {
      yylval->emplace< std::string >( YYText() );
      return token_type::IMMSYMBOL;
}
"+"                                         return '+';
","                                         return ',';
"("                                         return '(';
")"                                         return ')';
":"                                         return ':';    
"\n"                                        return '\n';
<<EOF>>         yyterminate();
.				        ;


%%

