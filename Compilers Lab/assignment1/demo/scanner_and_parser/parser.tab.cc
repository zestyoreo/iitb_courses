// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 40 "parser.yy"

   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>
   
   
   #include "scanner.hh"
   int nodeCount = 0;

#undef yylex
#define yylex IPL::Parser::scanner.yylex


#line 60 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.yy"
namespace IPL {
#line 152 "parser.tab.cc"


  /// Build a parser object.
  Parser::Parser (Scanner  &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.move< int > (std::move (that.value));
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.copy< int > (YY_MOVE (that.value));
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.move< int > (YY_MOVE (s.value));
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.move< int > (YY_MOVE (that.value));
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.copy< int > (that.value);
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        value.move< int > (that.value);
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 4: // MNEMONIC
#line 26 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 547 "parser.tab.cc"
        break;

      case 6: // SYMBOL
#line 27 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 553 "parser.tab.cc"
        break;

      case 7: // IMMSYMBOL
#line 28 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 559 "parser.tab.cc"
        break;

      case 8: // IMMNUMBER
#line 30 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 565 "parser.tab.cc"
        break;

      case 9: // REGISTER
#line 31 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 571 "parser.tab.cc"
        break;

      case 10: // IDENTIFIER
#line 25 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 577 "parser.tab.cc"
        break;

      case 11: // NUMBER
#line 29 "parser.yy"
                 { std::cerr << yysym.value.template as < std::string > (); }
#line 583 "parser.tab.cc"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 18: // program
      case 19: // instruction_list
      case 20: // instruction
      case 21: // optional_label
      case 22: // opnd
      case 23: // register_exp
      case 24: // exp
        yylhs.value.emplace< int > ();
        break;

      case 4: // MNEMONIC
      case 5: // OTHERS
      case 6: // SYMBOL
      case 7: // IMMSYMBOL
      case 8: // IMMNUMBER
      case 9: // REGISTER
      case 10: // IDENTIFIER
      case 11: // NUMBER
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 80 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
	    std::cout << yylhs.value.as < int > () << "[label=\"program\"]\n";
	    std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";

       }
#line 849 "parser.tab.cc"
    break;

  case 3:
#line 90 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
	    std::cout << yylhs.value.as < int > () << "[label=instruction_list]\n";
	    std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";
       }
#line 859 "parser.tab.cc"
    break;

  case 4:
#line 97 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
	    std::cout << yylhs.value.as < int > () << "[label=instruction_list]\n";
	    std::cout << yylhs.value.as < int > () << " -> " << yystack_[2].value.as < int > () << "\n";
         std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
	    std::cout << nodeCount << "[label=\"\\\\n\"]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";
       }
#line 872 "parser.tab.cc"
    break;

  case 5:
#line 109 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=instruction]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[1].value.as < int > () << "\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[0].value.as < std::string > () << "]\n";
       }
#line 884 "parser.tab.cc"
    break;

  case 6:
#line 117 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=instruction]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[2].value.as < int > () << "\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[1].value.as < std::string > () << "]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";
       }
#line 897 "parser.tab.cc"
    break;

  case 7:
#line 126 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=instruction]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[4].value.as < int > () << "\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[3].value.as < std::string > () << "]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[2].value.as < int > () << "\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\",\"]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";
       }
#line 913 "parser.tab.cc"
    break;

  case 8:
#line 140 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=optional_label]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"epsilon\"]\n";
       }
#line 924 "parser.tab.cc"
    break;

  case 9:
#line 147 "parser.yy"
       {
	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=optional_label]\n";
         std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[2].value.as < std::string > () << "]\n";
	    std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\":\"]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"\\\\n\"]\n";
       }
#line 939 "parser.tab.cc"
    break;

  case 10:
#line 161 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=opnd]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";
       }
#line 949 "parser.tab.cc"
    break;

  case 11:
#line 167 "parser.yy"
       { 
	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=opnd]\n";
            std::cout << yylhs.value.as < int > () << " -> " << yystack_[0].value.as < int > () << "\n";
       }
#line 959 "parser.tab.cc"
    break;

  case 12:
#line 176 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=register_exp]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << yystack_[0].value.as < std::string > () << "\"]\n";
       }
#line 970 "parser.tab.cc"
    break;

  case 13:
#line 183 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=register_exp]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"(\"]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << yystack_[1].value.as < std::string > () << "\"]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\")\"]\n";

       }
#line 986 "parser.tab.cc"
    break;

  case 14:
#line 195 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=register_exp]\n";
            
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[3].value.as < std::string > () << "]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"(\"]\n";
            
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << yystack_[1].value.as < std::string > () << "\"]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\")\"]\n";
       }
#line 1005 "parser.tab.cc"
    break;

  case 15:
#line 213 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=exp]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[0].value.as < std::string > () << "]\n";            
            
       }
#line 1017 "parser.tab.cc"
    break;

  case 16:
#line 221 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=exp]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << yystack_[0].value.as < std::string > () << "\"]\n"; 
       }
#line 1028 "parser.tab.cc"
    break;

  case 17:
#line 228 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=exp]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[0].value.as < std::string > () << "]\n"; 
       }
#line 1039 "parser.tab.cc"
    break;

  case 18:
#line 235 "parser.yy"
       {
       	    yylhs.value.as < int > () = ++nodeCount;
            std::cout << yylhs.value.as < int > () << "[label=exp]\n";
            std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << yystack_[0].value.as < std::string > () << "\"]\n"; 
       }
#line 1050 "parser.tab.cc"
    break;

  case 19:
#line 242 "parser.yy"
       {
       	yylhs.value.as < int > () = ++nodeCount;
          std::cout << yylhs.value.as < int > () << "[label=exp]\n";
          std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[2].value.as < std::string > () << "]\n"; 
          std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
          std::cout << nodeCount << "[label=\"+\"]\n";
          std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[0].value.as < std::string > () << "]\n"; 
       }
#line 1065 "parser.tab.cc"
    break;

  case 20:
#line 253 "parser.yy"
       {
       	 yylhs.value.as < int > () = ++nodeCount;
          std::cout << yylhs.value.as < int > () << "[label=exp]\n";
          std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=\"" << yystack_[2].value.as < std::string > () << "\"]\n"; 
          std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
          std::cout << nodeCount << "[label=\"+\"]\n";
          std::cout << yylhs.value.as < int > () << " -> " << ++nodeCount << "\n";
            std::cout << nodeCount << "[label=" << yystack_[0].value.as < std::string > () << "]\n"; 
       }
#line 1080 "parser.tab.cc"
    break;


#line 1084 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char Parser::yypact_ninf_ = -8;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      -2,    -7,     7,    -8,     6,     8,    10,    -8,    -2,    -6,
      -8,    -8,    -5,    -1,    -8,    -8,    -4,     5,     4,    -8,
      -8,     9,    11,    12,     2,    -6,    -8,    -8,     3,    -8,
      -8,    -8
  };

  const signed char
  Parser::yydefact_[] =
  {
       8,     0,     0,     2,     3,     0,     0,     1,     8,     5,
       9,     4,    15,    16,    18,    12,    17,     0,     6,    10,
      11,     0,     0,     0,     0,     0,    19,    20,     0,    13,
       7,    14
  };

  const signed char
  Parser::yypgoto_[] =
  {
      -8,    -8,    15,    -8,    -8,     0,    -8,    -8
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     5,    18,    19,    20
  };

  const signed char
  Parser::yytable_[] =
  {
      12,    13,    14,    15,     1,    16,     6,     7,    17,     8,
      23,    21,     9,    10,    24,    22,    25,    29,    31,     0,
      26,    28,    27,    11,     0,    30
  };

  const signed char
  Parser::yycheck_[] =
  {
       6,     7,     8,     9,     6,    11,    13,     0,    14,     3,
      14,    16,     4,     3,     9,    16,    12,    15,    15,    -1,
      11,     9,    11,     8,    -1,    25
  };

  const signed char
  Parser::yystos_[] =
  {
       0,     6,    18,    19,    20,    21,    13,     0,     3,     4,
       3,    19,     6,     7,     8,     9,    11,    14,    22,    23,
      24,    16,    16,    14,     9,    12,    11,    11,     9,    15,
      22,    15
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    17,    18,    19,    19,    20,    20,    20,    21,    21,
      22,    22,    23,    23,    23,    24,    24,    24,    24,    24,
      24
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     3,     2,     3,     5,     0,     3,
       1,     1,     1,     3,     4,     1,     1,     1,     1,     3,
       3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "'\\n'", "MNEMONIC", "OTHERS", "SYMBOL",
  "IMMSYMBOL", "IMMNUMBER", "REGISTER", "IDENTIFIER", "NUMBER", "','",
  "':'", "'('", "')'", "'+'", "$accept", "program", "instruction_list",
  "instruction", "optional_label", "opnd", "register_exp", "exp", YY_NULLPTR
  };


  const unsigned char
  Parser::yyrline_[] =
  {
       0,    79,    79,    89,    96,   108,   116,   125,   140,   146,
     160,   166,   175,   182,   194,   212,   220,   227,   234,   241,
     252
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      14,    15,     2,    16,    12,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    13,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,     7,     8,     9,    10,    11
    };
    const int user_token_number_max_ = 265;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

#line 5 "parser.yy"
} // IPL
#line 1440 "parser.tab.cc"

#line 264 "parser.yy"

void IPL::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}


