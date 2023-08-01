
   class Scanner : public yyFlexLexer
   {
   public:
      Scanner(std::istream& in, std::ostream& out) : yyFlexLexer(in, out)
      {
         
      };
      virtual int yylex();
}; 



