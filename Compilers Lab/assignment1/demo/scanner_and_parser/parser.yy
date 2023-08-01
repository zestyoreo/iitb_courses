%skeleton "lalr1.cc"
%require  "3.0.1"

%defines 
%define api.namespace {IPL}
%define api.parser.class {Parser}

%define parse.trace

%code requires{
   namespace IPL {
      class Scanner;
   }

  // # ifndef YY_NULLPTR
  // #  if defined __cplusplus && 201103L <= __cplusplus
  // #   define YY_NULLPTR nullptr
  // #  else
  // #   define YY_NULLPTR 0
  // #  endif
  // # endif

}

%printer { std::cerr << $$; } IDENTIFIER
%printer { std::cerr << $$; } MNEMONIC
%printer { std::cerr << $$; } SYMBOL
%printer { std::cerr << $$; } IMMSYMBOL
%printer { std::cerr << $$; } NUMBER
%printer { std::cerr << $$; } IMMNUMBER
%printer { std::cerr << $$; } REGISTER


%parse-param { Scanner  &scanner  }
%locations
%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>
   
   
   #include "scanner.hh"
   int nodeCount = 0;

#undef yylex
#define yylex IPL::Parser::scanner.yylex

}




%define api.value.type variant
%define parse.assert

%start program



%token '\n'
%token <std::string> MNEMONIC OTHERS
%token <std::string> SYMBOL 
%token <std::string> IMMSYMBOL 
%token <std::string> IMMNUMBER 
%token <std::string> REGISTER 
%token <std::string> IDENTIFIER 
%token <std::string> NUMBER
%token ',' ':' '(' ')' '+' 

%nterm <int> program instruction_list instruction optional_label opnd register_exp exp

%%
program: 
       instruction_list
       { 
	    $$ = ++nodeCount;
	    std::cout << $$ << "[label=\"program\"]\n";
	    std::cout << $$ << " -> " << $1 << "\n";

       } 
       ;

instruction_list: 
         instruction 
       { 
	    $$ = ++nodeCount;
	    std::cout << $$ << "[label=instruction_list]\n";
	    std::cout << $$ << " -> " << $1 << "\n";
       }

       | instruction '\n' instruction_list
       { 
	    $$ = ++nodeCount;
	    std::cout << $$ << "[label=instruction_list]\n";
	    std::cout << $$ << " -> " << $1 << "\n";
         std::cout << $$ << " -> " << ++nodeCount << "\n";
	    std::cout << nodeCount << "[label=\"\\\\n\"]\n";
            std::cout << $$ << " -> " << $3 << "\n";
       }
       ;

instruction:
         optional_label MNEMONIC 
       { 
	    $$ = ++nodeCount;
            std::cout << $$ << "[label=instruction]\n";
            std::cout << $$ << " -> " << $1 << "\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $2 << "]\n";
       }
       | optional_label MNEMONIC opnd
       { 
	    $$ = ++nodeCount;
            std::cout << $$ << "[label=instruction]\n";
            std::cout << $$ << " -> " << $1 << "\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $2 << "]\n";
            std::cout << $$ << " -> " << $3 << "\n";
       } 
       | optional_label MNEMONIC opnd ',' opnd
       { 
	    $$ = ++nodeCount;
            std::cout << $$ << "[label=instruction]\n";
            std::cout << $$ << " -> " << $1 << "\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $2 << "]\n";
            std::cout << $$ << " -> " << $3 << "\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\",\"]\n";
            std::cout << $$ << " -> " << $5 << "\n";
       } 
       ;

optional_label:
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=optional_label]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"epsilon\"]\n";
       }
       | SYMBOL':' '\n'
       {
	    $$ = ++nodeCount;
            std::cout << $$ << "[label=optional_label]\n";
         std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $1 << "]\n";
	    std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\":\"]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"\\\\n\"]\n";
       }
       ;

opnd:
         register_exp
       { 
	    $$ = ++nodeCount;
            std::cout << $$ << "[label=opnd]\n";
            std::cout << $$ << " -> " << $1 << "\n";
       }
       | exp
       { 
	    $$ = ++nodeCount;
            std::cout << $$ << "[label=opnd]\n";
            std::cout << $$ << " -> " << $1 << "\n";
       }
       ;
       
register_exp:
         REGISTER
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=register_exp]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << $1 << "\"]\n";
       }
       | '(' REGISTER ')'
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=register_exp]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"(\"]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << $2 << "\"]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\")\"]\n";

       }
       | NUMBER '(' REGISTER ')'
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=register_exp]\n";
            
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $1 << "]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"(\"]\n";
            
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << $3 << "\"]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\")\"]\n";
       }
       ;

exp:
         SYMBOL
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=exp]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $1 << "]\n";            
            
       }
       | IMMSYMBOL
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=exp]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << $1 << "\"]\n"; 
       }
       | NUMBER
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=exp]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $1 << "]\n"; 
       }
       | IMMNUMBER
       {
       	    $$ = ++nodeCount;
            std::cout << $$ << "[label=exp]\n";
            std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << $1 << "\"]\n"; 
       }
       | SYMBOL '+' NUMBER
       {
       	$$ = ++nodeCount;
          std::cout << $$ << "[label=exp]\n";
          std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $1 << "]\n"; 
          std::cout << $$ << " -> " << ++nodeCount << "\n";
          std::cout << nodeCount << "[label=\"+\"]\n";
          std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $3 << "]\n"; 
       }
       | IMMSYMBOL '+' NUMBER
       {
       	 $$ = ++nodeCount;
          std::cout << $$ << "[label=exp]\n";
          std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << $1 << "\"]\n"; 
          std::cout << $$ << " -> " << ++nodeCount << "\n";
          std::cout << nodeCount << "[label=\"+\"]\n";
          std::cout << $$ << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << $3 << "]\n"; 
       }
       ;
%%
void IPL::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}


