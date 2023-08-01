
/*If FlexLexer.h has not been included before */

#if !defined(yyFlexLexerOnce)
 #include <FlexLexer.h>
#endif
// parser.tab.hh defines 
// struct token
//     {
//       enum yytokentype
//       {
//         MNEMONIC = 258,
//         SYMBOL = 259,
//         ...
#include "parser.tab.hh"
#include "location.hh"

namespace IPL
{
   class Scanner : public yyFlexLexer
   {
   public:
      Scanner(std::istream& in) : yyFlexLexer(in, std::cout)
      {
         loc = new IPL::Parser::location_type();
      };


      virtual int yylex(IPL::Parser::semantic_type *const lval,
                        IPL::Parser::location_type *location);

   private:
      /* yyval ptr */
      IPL::Parser::semantic_type *yylval = nullptr;
      /* location ptr */
      IPL::Parser::location_type *loc = nullptr;
   };

} /* end namespace IPL */

//#endif /* END __IPLSCANNER_HPP__ */


