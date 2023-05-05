// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "frontend.hh"


// Unqualified %code blocks.
#line 34 "jeff.yy"

   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex

#line 63 "parser.cc"


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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "jeff.yy"
namespace jeff {
#line 137 "parser.cc"

  /// Build a parser object.
  Parser::Parser (jeff::Scanner &scanner_yyarg, jeff::ProgramNode** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
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

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
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

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
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
  Parser::yypop_ (int n) YY_NOEXCEPT
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
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
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
    YY_STACK_PRINT ();

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
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
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

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: globals
#line 160 "jeff.yy"
                  {
		  (yylhs.value.transProgram) = new ProgramNode((yystack_[0].value.transDeclList));
		  *root = (yylhs.value.transProgram);
		  }
#line 598 "parser.cc"
    break;

  case 3: // globals: globals varDecl SEMICOL
#line 166 "jeff.yy"
                  { 
	  	  (yylhs.value.transDeclList) = (yystack_[2].value.transDeclList); 
	  	  DeclNode * declNode = (yystack_[1].value.transVarDecl);
		  (yylhs.value.transDeclList)->push_back(declNode);
	  	  }
#line 608 "parser.cc"
    break;

  case 4: // globals: globals FN COLON fnDecl
#line 172 "jeff.yy"
                  {
	  	  (yylhs.value.transDeclList) = (yystack_[3].value.transDeclList); 
	  	  DeclNode * declNode = (yystack_[0].value.transFn);
		  (yylhs.value.transDeclList)->push_back(declNode);
		  }
#line 618 "parser.cc"
    break;

  case 5: // globals: %empty
#line 179 "jeff.yy"
                  {
		  (yylhs.value.transDeclList) = new std::list<DeclNode * >();
		  }
#line 626 "parser.cc"
    break;

  case 6: // varDecl: type id
#line 184 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transType)->pos(), (yystack_[0].value.transID)->pos());
		  (yylhs.value.transVarDecl) = new VarDeclNode(p, (yystack_[1].value.transType), (yystack_[0].value.transID));
		  }
#line 635 "parser.cc"
    break;

  case 7: // type: primType
#line 190 "jeff.yy"
                  {
		  (yylhs.value.transType) = (yystack_[0].value.transType);
		  }
#line 643 "parser.cc"
    break;

  case 8: // primType: INT
#line 195 "jeff.yy"
                  { 
		  (yylhs.value.transType) = new IntTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 651 "parser.cc"
    break;

  case 9: // primType: BOOL
#line 199 "jeff.yy"
                  {
		  (yylhs.value.transType) = new BoolTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 659 "parser.cc"
    break;

  case 10: // primType: VOID
#line 203 "jeff.yy"
                  {
		  (yylhs.value.transType) = new VoidTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 667 "parser.cc"
    break;

  case 11: // primType: FILE
#line 207 "jeff.yy"
                  {
		  (yylhs.value.transType) = new FileTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 675 "parser.cc"
    break;

  case 12: // fnDecl: LPAREN formals RPAREN type id LCURLY stmtList RCURLY
#line 212 "jeff.yy"
                  {
		  auto pos = new Position((yystack_[7].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transFn) = new FnDeclNode(pos, (yystack_[6].value.transFormalList), (yystack_[4].value.transType), (yystack_[3].value.transID), (yystack_[1].value.transStmts));
		  }
#line 684 "parser.cc"
    break;

  case 13: // fnDecl: LPAREN RPAREN type id LCURLY stmtList RCURLY
#line 217 "jeff.yy"
                  {
		  const auto pos = new Position((yystack_[6].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  auto args = new std::list<FormalDeclNode *>();
		  TypeNode * r = (yystack_[4].value.transType);
		  IDNode * i = (yystack_[3].value.transID);
		  std::list<StmtNode *> * body = (yystack_[1].value.transStmts);
		  (yylhs.value.transFn) = new FnDeclNode(pos, args, r, i, body);
		  }
#line 697 "parser.cc"
    break;

  case 14: // formals: formalDecl
#line 227 "jeff.yy"
                  {
		  (yylhs.value.transFormalList) = new std::list<FormalDeclNode *>();
		  (yylhs.value.transFormalList)->push_back((yystack_[0].value.transFormal));
		  }
#line 706 "parser.cc"
    break;

  case 15: // formals: formals COMMA formalDecl
#line 232 "jeff.yy"
                  {
		  (yylhs.value.transFormalList) = (yystack_[2].value.transFormalList);
		  (yylhs.value.transFormalList)->push_back((yystack_[0].value.transFormal));
		  }
#line 715 "parser.cc"
    break;

  case 16: // formalDecl: type id
#line 238 "jeff.yy"
                  {
		  const Position * pos = new Position((yystack_[1].value.transType)->pos(), (yystack_[0].value.transID)->pos());
		  (yylhs.value.transFormal) = new FormalDeclNode(pos, (yystack_[1].value.transType), (yystack_[0].value.transID));
		  }
#line 724 "parser.cc"
    break;

  case 17: // stmtList: %empty
#line 244 "jeff.yy"
                  {
		  (yylhs.value.transStmts) = new std::list<StmtNode *>();
	   	  }
#line 732 "parser.cc"
    break;

  case 18: // stmtList: stmtList stmt SEMICOL
#line 248 "jeff.yy"
                  {
		  (yylhs.value.transStmts) = (yystack_[2].value.transStmts);
		  (yylhs.value.transStmts)->push_back((yystack_[1].value.transStmt));
	  	  }
#line 741 "parser.cc"
    break;

  case 19: // stmtList: stmtList blockStmt
#line 253 "jeff.yy"
                  {
		  (yylhs.value.transStmts) = (yystack_[1].value.transStmts);
		  (yylhs.value.transStmts)->push_back((yystack_[0].value.transStmt));
	  	  }
#line 750 "parser.cc"
    break;

  case 20: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 259 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[6].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new WhileStmtNode(p, (yystack_[4].value.transExp), (yystack_[1].value.transStmts));
		  }
#line 759 "parser.cc"
    break;

  case 21: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 264 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[6].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new IfStmtNode(p, (yystack_[4].value.transExp), (yystack_[1].value.transStmts));
		  }
#line 768 "parser.cc"
    break;

  case 22: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 269 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[10].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new IfElseStmtNode(p, (yystack_[8].value.transExp), (yystack_[5].value.transStmts), (yystack_[1].value.transStmts));
		  }
#line 777 "parser.cc"
    break;

  case 23: // stmt: varDecl
#line 275 "jeff.yy"
                  {
		  const Position * p = (yystack_[0].value.transVarDecl)->pos();
		  (yylhs.value.transStmt) = new VarDeclNode(p, (yystack_[0].value.transVarDecl)->getTypeNode(), (yystack_[0].value.transVarDecl)->ID());
		  }
#line 786 "parser.cc"
    break;

  case 24: // stmt: loc ASSIGN exp
#line 280 "jeff.yy"
                  {
		  const auto p = new Position((yystack_[2].value.transLoc)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transStmt) = new AssignStmtNode(p, (yystack_[2].value.transLoc), (yystack_[0].value.transExp)); 
		  }
#line 795 "parser.cc"
    break;

  case 25: // stmt: OPEN READ loc STRINGLITERAL
#line 285 "jeff.yy"
                  {
		  auto p = new Position((yystack_[3].value.transToken)->pos(), (yystack_[0].value.transStrToken)->pos());
		  std::string path = (yystack_[0].value.transStrToken)->str();
		  (yylhs.value.transStmt) = new OpenStmtNode(p, (yystack_[1].value.transLoc), path, true);
		  }
#line 805 "parser.cc"
    break;

  case 26: // stmt: OPEN WRITE loc STRINGLITERAL
#line 291 "jeff.yy"
                  {
		  auto p = new Position((yystack_[3].value.transToken)->pos(), (yystack_[0].value.transStrToken)->pos());
		  std::string path = (yystack_[0].value.transStrToken)->str();
		  (yylhs.value.transStmt) = new OpenStmtNode(p, (yystack_[1].value.transLoc), path, false);
		  }
#line 815 "parser.cc"
    break;

  case 27: // stmt: CLOSE loc
#line 297 "jeff.yy"
                  {
		  auto p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transLoc)->pos());
		  (yylhs.value.transStmt) = new CloseStmtNode(p, (yystack_[0].value.transLoc));
		  }
#line 824 "parser.cc"
    break;

  case 28: // stmt: loc POSTDEC
#line 302 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transLoc)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new PostDecStmtNode(p, (yystack_[1].value.transLoc));
		  }
#line 833 "parser.cc"
    break;

  case 29: // stmt: loc POSTINC
#line 307 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transLoc)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new PostIncStmtNode(p, (yystack_[1].value.transLoc));
		  }
#line 842 "parser.cc"
    break;

  case 30: // stmt: loc READ loc
#line 312 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transLoc)->pos(), (yystack_[1].value.transToken)->pos());
		  (yylhs.value.transStmt) = new ReadStmtNode(p, (yystack_[2].value.transLoc), (yystack_[0].value.transLoc));
		  }
#line 851 "parser.cc"
    break;

  case 31: // stmt: loc WRITE exp
#line 317 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transLoc)->pos(), (yystack_[1].value.transToken)->pos());
		  (yylhs.value.transStmt) = new WriteStmtNode(p, (yystack_[2].value.transLoc), (yystack_[0].value.transExp));
		  }
#line 860 "parser.cc"
    break;

  case 32: // stmt: RETURN exp
#line 322 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transStmt) = new ReturnStmtNode(p, (yystack_[0].value.transExp));
		  }
#line 869 "parser.cc"
    break;

  case 33: // stmt: RETURN
#line 327 "jeff.yy"
                  {
		  (yylhs.value.transStmt) = new ReturnStmtNode((yystack_[0].value.transToken)->pos(), nullptr);
		  }
#line 877 "parser.cc"
    break;

  case 34: // stmt: callExp
#line 331 "jeff.yy"
                  { 
		  (yylhs.value.transStmt) = new CallStmtNode((yystack_[0].value.transCallExp)->pos(), (yystack_[0].value.transCallExp)); 
		  }
#line 885 "parser.cc"
    break;

  case 35: // exp: exp DASH exp
#line 336 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new MinusNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 894 "parser.cc"
    break;

  case 36: // exp: LPAREN exp QUESTION exp COLON exp RPAREN
#line 341 "jeff.yy"
                  {
	  	  auto p = new Position((yystack_[6].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transExp) = new TernaryExpNode(p, (yystack_[5].value.transExp), (yystack_[3].value.transExp), (yystack_[1].value.transExp));
		  }
#line 903 "parser.cc"
    break;

  case 37: // exp: exp CROSS exp
#line 346 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new PlusNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 912 "parser.cc"
    break;

  case 38: // exp: exp STAR exp
#line 351 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new TimesNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 921 "parser.cc"
    break;

  case 39: // exp: exp SLASH exp
#line 356 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new DivideNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 930 "parser.cc"
    break;

  case 40: // exp: exp AND exp
#line 361 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new AndNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 939 "parser.cc"
    break;

  case 41: // exp: exp OR exp
#line 366 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new OrNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 948 "parser.cc"
    break;

  case 42: // exp: exp EQUALS exp
#line 371 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new EqualsNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 957 "parser.cc"
    break;

  case 43: // exp: exp NOTEQUALS exp
#line 376 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new NotEqualsNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 966 "parser.cc"
    break;

  case 44: // exp: exp GREATER exp
#line 381 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new GreaterNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 975 "parser.cc"
    break;

  case 45: // exp: exp GREATEREQ exp
#line 386 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new GreaterEqNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 984 "parser.cc"
    break;

  case 46: // exp: exp LESS exp
#line 391 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new LessNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 993 "parser.cc"
    break;

  case 47: // exp: exp LESSEQ exp
#line 396 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new LessEqNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 1002 "parser.cc"
    break;

  case 48: // exp: NOT exp
#line 401 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new NotNode(p, (yystack_[0].value.transExp));
		  }
#line 1011 "parser.cc"
    break;

  case 49: // exp: DASH term
#line 406 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new NegNode(p, (yystack_[0].value.transExp));
		  }
#line 1020 "parser.cc"
    break;

  case 50: // exp: term
#line 411 "jeff.yy"
                  { (yylhs.value.transExp) = (yystack_[0].value.transExp); }
#line 1026 "parser.cc"
    break;

  case 51: // callExp: id LPAREN RPAREN
#line 414 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transID)->pos(), (yystack_[0].value.transToken)->pos());
		  std::list<ExpNode *> * noargs =
		    new std::list<ExpNode *>();
		  (yylhs.value.transCallExp) = new CallExpNode(p, (yystack_[2].value.transID), noargs);
		  }
#line 1037 "parser.cc"
    break;

  case 52: // callExp: id LPAREN actualsList RPAREN
#line 421 "jeff.yy"
                  {
		  const Position * p = new Position((yystack_[3].value.transID)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transCallExp) = new CallExpNode(p, (yystack_[3].value.transID), (yystack_[1].value.transActuals));
		  }
#line 1046 "parser.cc"
    break;

  case 53: // actualsList: exp
#line 427 "jeff.yy"
                  {
		  std::list<ExpNode *> * list =
		    new std::list<ExpNode *>();
		  list->push_back((yystack_[0].value.transExp));
		  (yylhs.value.transActuals) = list;
		  }
#line 1057 "parser.cc"
    break;

  case 54: // actualsList: actualsList COMMA exp
#line 434 "jeff.yy"
                  {
		  (yylhs.value.transActuals) = (yystack_[2].value.transActuals);
		  (yylhs.value.transActuals)->push_back((yystack_[0].value.transExp));
		  }
#line 1066 "parser.cc"
    break;

  case 55: // term: loc
#line 440 "jeff.yy"
                  { (yylhs.value.transExp) = (yystack_[0].value.transLoc); }
#line 1072 "parser.cc"
    break;

  case 56: // term: INTLITERAL
#line 442 "jeff.yy"
                  { (yylhs.value.transExp) = new IntLitNode((yystack_[0].value.transIntToken)->pos(), (yystack_[0].value.transIntToken)->num()); }
#line 1078 "parser.cc"
    break;

  case 57: // term: STRINGLITERAL
#line 444 "jeff.yy"
                  { (yylhs.value.transExp) = new StrLitNode((yystack_[0].value.transStrToken)->pos(), (yystack_[0].value.transStrToken)->str()); }
#line 1084 "parser.cc"
    break;

  case 58: // term: TRUE
#line 446 "jeff.yy"
                  { (yylhs.value.transExp) = new TrueNode((yystack_[0].value.transToken)->pos()); }
#line 1090 "parser.cc"
    break;

  case 59: // term: FALSE
#line 448 "jeff.yy"
                  { (yylhs.value.transExp) = new FalseNode((yystack_[0].value.transToken)->pos()); }
#line 1096 "parser.cc"
    break;

  case 60: // term: LPAREN exp RPAREN
#line 450 "jeff.yy"
                  { (yylhs.value.transExp) = (yystack_[1].value.transExp); }
#line 1102 "parser.cc"
    break;

  case 61: // term: callExp
#line 452 "jeff.yy"
                  { (yylhs.value.transExp) = (yystack_[0].value.transCallExp); }
#line 1108 "parser.cc"
    break;

  case 62: // loc: id
#line 455 "jeff.yy"
                  {
		  (yylhs.value.transLoc) = (yystack_[0].value.transID);
		  }
#line 1116 "parser.cc"
    break;

  case 63: // id: ID
#line 460 "jeff.yy"
                  {
		  const Position * pos = (yystack_[0].value.transIDToken)->pos();
		  (yylhs.value.transID) = new IDNode(pos, (yystack_[0].value.transIDToken)->value()); 
		  }
#line 1125 "parser.cc"
    break;

  case 64: // id: CONSOLE
#line 465 "jeff.yy"
                  {
		  const Position * pos = (yystack_[0].value.transToken)->pos();
		  (yylhs.value.transID) = new IDNode(pos, "console"); 
		  }
#line 1134 "parser.cc"
    break;


#line 1138 "parser.cc"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


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
    YY_STACK_PRINT ();
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
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -37;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -37,     7,    24,   -37,   -37,   -37,     9,   -37,   -37,   -29,
      -5,   -37,     0,   -37,   -37,   -37,   -37,    63,   -37,     3,
      -5,     4,   -37,    -5,   -37,     3,     3,    -2,   -37,    -5,
     -37,     2,   100,   -37,    -5,     1,   -25,   451,   -37,     5,
     -37,   -37,    10,   -37,    -1,    15,   123,   -37,   -37,   451,
      -5,    -5,   200,   -37,   -37,   451,   451,   -37,   -37,   404,
     -37,   -37,   -37,   451,   -37,   451,   -37,   -37,    -5,   451,
     438,   -37,   250,     6,    22,   451,   -37,   217,   -37,   451,
     451,   451,   451,   451,   451,   451,   451,   451,   451,   451,
     451,   283,   404,   -37,   404,   -37,   404,    25,    23,   -37,
     -37,   316,   451,   -37,   473,   -36,   493,   493,   493,   493,
     493,   493,   426,   -36,   -37,   -37,    44,   451,   -37,   -37,
     349,   -37,   404,   146,   451,   169,    56,   371,   -37,    48,
     -37,   -37,   192,   -37
  };

  const signed char
  Parser::yydefact_[] =
  {
       5,     0,     2,     1,     9,    11,     0,     8,    10,     0,
       0,     7,     0,     3,    64,    63,     6,     0,     4,     0,
       0,     0,    14,     0,    16,     0,     0,     0,    15,     0,
      17,     0,     0,    17,     0,     0,     0,    33,    13,     0,
      23,    19,     0,    34,     0,    62,     0,    27,    62,     0,
       0,     0,     0,    59,    56,     0,     0,    57,    58,    32,
      61,    50,    55,     0,    18,     0,    28,    29,     0,     0,
       0,    12,     0,     0,     0,     0,    49,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    24,    30,    31,    51,    53,     0,     0,    25,
      26,     0,     0,    60,    40,    35,    42,    44,    45,    46,
      47,    43,    41,    37,    39,    38,     0,     0,    52,    17,
       0,    17,    54,     0,     0,     0,    21,     0,    20,     0,
      36,    17,     0,    22
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -37,   -37,   -37,    69,    98,   -37,   -37,   -37,    47,   -24,
     -37,   -37,   -28,   -31,   -37,    26,   -32,    53
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,    40,    10,    11,    18,    21,    22,    32,
      41,    42,    59,    60,    97,    61,    62,    45
  };

  const short
  Parser::yytable_[] =
  {
      44,    43,    47,    65,    14,    89,    90,     3,     4,    46,
      50,    13,    25,    15,    44,    43,    12,     5,    73,    74,
      30,    72,    51,     7,    33,    17,    49,    77,    78,     4,
      63,    66,    67,   117,    68,    91,    93,    92,     5,     6,
      70,    94,    96,    26,     7,   119,    69,   101,     8,    99,
      64,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    16,   118,   100,   121,   129,     4,     8,
     131,     9,    28,    24,   120,     0,    27,     5,    76,     0,
       0,     0,    31,     7,     0,     0,     0,    48,     0,   122,
       0,    44,    43,    44,    43,   123,   127,   125,     0,     0,
      44,    43,    19,    48,    48,     4,    34,   132,     8,    14,
       0,     0,     0,     0,     5,    20,     0,    23,    15,    35,
       7,    48,     0,    20,    29,     0,     0,     0,     4,    34,
      36,     0,    14,     0,     0,     0,    37,     5,    38,     0,
       0,    15,    35,     7,     0,     8,    39,     0,     0,     0,
       0,     4,    34,    36,     0,    14,     0,     0,     0,    37,
       5,    71,     0,     0,    15,    35,     7,     0,     8,    39,
       0,     0,     0,     0,     4,    34,    36,     0,    14,     0,
       0,     0,    37,     5,   126,     0,     0,    15,    35,     7,
       0,     8,    39,     0,     0,     0,     0,     4,    34,    36,
       0,    14,     0,     0,     0,    37,     5,   128,     0,    14,
      15,    35,     7,    53,     8,    39,     0,     0,    15,     0,
      79,    54,    36,     0,     0,    75,     0,    80,    37,    81,
     133,     0,     0,    82,    83,     0,     0,     8,    39,     0,
      84,    85,     0,    57,    58,    86,    87,     0,    88,     0,
       0,   102,     0,    79,     0,     0,   103,     0,    89,    90,
      80,     0,    81,     0,     0,     0,    82,    83,     0,     0,
       0,     0,     0,    84,    85,     0,     0,     0,    86,    87,
       0,    88,     0,     0,     0,     0,    79,     0,     0,    98,
       0,    89,    90,    80,     0,    81,     0,     0,     0,    82,
      83,     0,     0,     0,     0,     0,    84,    85,     0,     0,
       0,    86,    87,     0,    88,     0,     0,     0,     0,    79,
       0,     0,   116,     0,    89,    90,    80,     0,    81,     0,
       0,     0,    82,    83,     0,     0,     0,     0,     0,    84,
      85,     0,     0,     0,    86,    87,     0,    88,     0,     0,
       0,     0,    79,     0,     0,   103,   124,    89,    90,    80,
       0,    81,     0,     0,     0,    82,    83,     0,     0,     0,
       0,     0,    84,    85,    79,     0,     0,    86,    87,     0,
      88,    80,     0,    81,     0,     0,     0,    82,    83,     0,
      89,    90,     0,     0,    84,    85,     0,     0,     0,    86,
      87,     0,    88,     0,     0,     0,     0,    79,     0,     0,
     130,     0,    89,    90,    80,     0,    81,     0,     0,     0,
      82,    83,     0,     0,     0,     0,     0,    84,    85,    79,
       0,     0,    86,    87,     0,    88,    80,     0,    81,     0,
       0,     0,    82,    83,     0,    89,    90,    14,    52,    84,
      85,    53,     0,     0,    86,     0,    15,    88,     0,    54,
      14,    52,     0,    55,    53,    56,     0,    89,    90,    15,
       0,     0,    54,     0,     0,     0,    55,    95,    56,     0,
       0,    57,    58,    80,     0,    81,     0,     0,     0,    82,
      83,     0,     0,     0,    57,    58,    84,    85,     0,     0,
       0,    86,     0,    80,    88,    -1,     0,     0,     0,    -1,
      -1,     0,     0,     0,    89,    90,    -1,    -1,     0,     0,
       0,    -1,     0,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90
  };

  const short
  Parser::yycheck_[] =
  {
      32,    32,    34,     4,     9,    41,    42,     0,     5,    33,
      35,    40,     8,    18,    46,    46,     7,    14,    50,    51,
      22,    49,    47,    20,    22,    25,    25,    55,    56,     5,
      25,    32,    33,     8,    35,    63,    68,    65,    14,    15,
      25,    69,    70,    39,    20,    22,    47,    75,    45,    43,
      40,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    10,    39,    43,    22,    11,     5,    45,
      22,     2,    25,    20,   102,    -1,    23,    14,    52,    -1,
      -1,    -1,    29,    20,    -1,    -1,    -1,    34,    -1,   117,
      -1,   123,   123,   125,   125,   119,   124,   121,    -1,    -1,
     132,   132,    39,    50,    51,     5,     6,   131,    45,     9,
      -1,    -1,    -1,    -1,    14,    17,    -1,    19,    18,    19,
      20,    68,    -1,    25,    26,    -1,    -1,    -1,     5,     6,
      30,    -1,     9,    -1,    -1,    -1,    36,    14,    38,    -1,
      -1,    18,    19,    20,    -1,    45,    46,    -1,    -1,    -1,
      -1,     5,     6,    30,    -1,     9,    -1,    -1,    -1,    36,
      14,    38,    -1,    -1,    18,    19,    20,    -1,    45,    46,
      -1,    -1,    -1,    -1,     5,     6,    30,    -1,     9,    -1,
      -1,    -1,    36,    14,    38,    -1,    -1,    18,    19,    20,
      -1,    45,    46,    -1,    -1,    -1,    -1,     5,     6,    30,
      -1,     9,    -1,    -1,    -1,    36,    14,    38,    -1,     9,
      18,    19,    20,    13,    45,    46,    -1,    -1,    18,    -1,
       3,    21,    30,    -1,    -1,    25,    -1,    10,    36,    12,
      38,    -1,    -1,    16,    17,    -1,    -1,    45,    46,    -1,
      23,    24,    -1,    43,    44,    28,    29,    -1,    31,    -1,
      -1,    34,    -1,     3,    -1,    -1,    39,    -1,    41,    42,
      10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    -1,    28,    29,
      -1,    31,    -1,    -1,    -1,    -1,     3,    -1,    -1,    39,
      -1,    41,    42,    10,    -1,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,
      -1,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    39,    -1,    41,    42,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    23,
      24,    -1,    -1,    -1,    28,    29,    -1,    31,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    39,     7,    41,    42,    10,
      -1,    12,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,
      -1,    -1,    23,    24,     3,    -1,    -1,    28,    29,    -1,
      31,    10,    -1,    12,    -1,    -1,    -1,    16,    17,    -1,
      41,    42,    -1,    -1,    23,    24,    -1,    -1,    -1,    28,
      29,    -1,    31,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      39,    -1,    41,    42,    10,    -1,    12,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,    23,    24,     3,
      -1,    -1,    28,    29,    -1,    31,    10,    -1,    12,    -1,
      -1,    -1,    16,    17,    -1,    41,    42,     9,    10,    23,
      24,    13,    -1,    -1,    28,    -1,    18,    31,    -1,    21,
       9,    10,    -1,    25,    13,    27,    -1,    41,    42,    18,
      -1,    -1,    21,    -1,    -1,    -1,    25,    39,    27,    -1,
      -1,    43,    44,    10,    -1,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    43,    44,    23,    24,    -1,    -1,
      -1,    28,    -1,    10,    31,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    41,    42,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    49,    50,     0,     5,    14,    15,    20,    45,    51,
      52,    53,     7,    40,     9,    18,    65,    25,    54,    39,
      52,    55,    56,    52,    65,     8,    39,    65,    56,    52,
      22,    65,    57,    22,     6,    19,    30,    36,    38,    46,
      51,    58,    59,    61,    64,    65,    57,    64,    65,    25,
      35,    47,    10,    13,    21,    25,    27,    43,    44,    60,
      61,    63,    64,    25,    40,     4,    32,    33,    35,    47,
      25,    38,    60,    64,    64,    25,    63,    60,    60,     3,
      10,    12,    16,    17,    23,    24,    28,    29,    31,    41,
      42,    60,    60,    64,    60,    39,    60,    62,    39,    43,
      43,    60,    34,    39,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    39,     8,    39,    22,
      60,    22,    60,    57,     7,    57,    38,    60,    38,    11,
      39,    22,    57,    38
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    48,    49,    50,    50,    50,    51,    52,    53,    53,
      53,    53,    54,    54,    55,    55,    56,    57,    57,    57,
      58,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    64,    65,    65
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     3,     4,     0,     2,     1,     1,     1,
       1,     1,     8,     7,     1,     3,     2,     0,     3,     2,
       7,     7,    11,     1,     3,     4,     4,     2,     2,     2,
       3,     3,     2,     1,     1,     3,     7,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     4,     1,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end file\"", "error", "\"invalid token\"", "AND", "ASSIGN", "BOOL",
  "CLOSE", "COLON", "COMMA", "CONSOLE", "DASH", "ELSE", "EQUALS", "FALSE",
  "FILE", "FN", "GREATER", "GREATEREQ", "ID", "IF", "INT", "INTLITERAL",
  "LCURLY", "LESS", "LESSEQ", "LPAREN", "LBRACE", "NOT", "NOTEQUALS", "OR",
  "OPEN", "CROSS", "POSTDEC", "POSTINC", "QUESTION", "READ", "RETURN",
  "RBRACE", "RCURLY", "RPAREN", "SEMICOL", "SLASH", "STAR",
  "STRINGLITERAL", "TRUE", "VOID", "WHILE", "WRITE", "$accept", "program",
  "globals", "varDecl", "type", "primType", "fnDecl", "formals",
  "formalDecl", "stmtList", "blockStmt", "stmt", "exp", "callExp",
  "actualsList", "term", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   159,   159,   165,   171,   179,   183,   189,   194,   198,
     202,   206,   211,   216,   226,   231,   237,   244,   247,   252,
     258,   263,   268,   274,   279,   284,   290,   296,   301,   306,
     311,   316,   321,   326,   330,   335,   340,   345,   350,   355,
     360,   365,   370,   375,   380,   385,   390,   395,   400,   405,
     410,   413,   420,   426,   433,   439,   441,   443,   445,   447,
     449,   451,   454,   459,   464
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
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

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
    };
    // Last valid token kind.
    const int code_max = 302;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "jeff.yy"
} // jeff
#line 1818 "parser.cc"

#line 470 "jeff.yy"


void jeff::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
