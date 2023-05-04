%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace{jeff}
%define api.parser.class {Parser}
%define parse.error verbose
%output "parser.cc"
%token-table

%code requires{
	#include <list>
	#include "tokens.hpp"
	#include "ast.hpp"
	namespace jeff {
		class Scanner;
	}

//The following definition is required when 
// we don't have the %locations directive
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

//End "requires" code
}

%parse-param { jeff::Scanner &scanner }
%parse-param { jeff::ProgramNode** root }
%code{
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
}

%union {
   bool                                 transBool;
   jeff::Token*                         transToken;
   jeff::Token*                         lexeme;
   jeff::IDToken*                       transIDToken;
   jeff::IntLitToken*                   transIntToken;
   jeff::IntLitToken*                   transShortToken;
   jeff::StrToken*                      transStrToken;
   jeff::ProgramNode*                   transProgram;
   jeff::DeclNode *                     transDecl;
   std::list<jeff::DeclNode *> *        transDeclList;
   jeff::VarDeclNode *                  transVarDecl;
   std::list<jeff::TypeNode *> *        transTypeList;
   std::list<jeff::VarDeclNode *> *     transVarDeclList;
   jeff::FormalDeclNode *               transFormal;
   std::list<jeff::FormalDeclNode *> *  transFormalList;
   jeff::TypeNode *                     transType;
   jeff::LocNode *                      transLoc;
   jeff::IDNode *                       transID;
   jeff::FnDeclNode *                   transFn;
   std::list<jeff::VarDeclNode *> *     transVarDecls;
   std::list<jeff::StmtNode *> *        transStmts;
   jeff::StmtNode *                     transStmt;
   jeff::ExpNode *                      transExp;
   jeff::CallExpNode *                  transCallExp;
   std::list<jeff::ExpNode *> *         transActuals;
}

%define parse.assert

%token                   END	   0 "end file"
%token	<transToken>     AND
%token	<transToken>     ASSIGN
%token	<transToken>     BOOL
%token	<transToken>     CLOSE
%token	<transToken>     COLON
%token	<transToken>     COMMA
%token	<transToken>     CONSOLE
%token	<transToken>     DASH
%token	<transToken>     ELSE
%token	<transToken>     EQUALS
%token	<transToken>     FALSE
%token	<transToken>     FILE
%token	<transToken>     FN
%token	<transToken>     GREATER
%token	<transToken>     GREATEREQ
%token	<transIDToken>   ID
%token	<transToken>     IF
%token	<transToken>     INT
%token	<transIntToken>  INTLITERAL
%token	<transToken>     LCURLY
%token	<transToken>     LESS
%token	<transToken>     LESSEQ
%token	<transToken>     LPAREN
%token	<transToken>     LBRACE
%token	<transToken>     NOT
%token	<transToken>     NOTEQUALS
%token	<transToken>     OR
%token	<transToken>     OPEN
%token	<transToken>     CROSS
%token	<transToken>     POSTDEC
%token	<transToken>     POSTINC
%token	<transToken>     QUESTION
%token	<transToken>     READ
%token	<transToken>     RETURN
%token	<transToken>     RBRACE
%token	<transToken>     RCURLY
%token	<transToken>     RPAREN
%token	<transToken>     SEMICOL
%token	<transToken>     SLASH
%token	<transToken>     STAR
%token	<transStrToken>  STRINGLITERAL
%token	<transToken>     TRUE
%token	<transToken>     VOID
%token	<transToken>     WHILE
%token	<transToken>     WRITE

%type <transProgram> program
%type <transDeclList> globals
%type <transVarDecl> varDecl
%type <transFn> fnDecl
%type <transExp> term
%type <transExp> exp
%type <transActuals> actualsList
%type <transCallExp> callExp
%type <transID> id
%type <transLoc> loc
%type <transStmt> stmt
%type <transStmt> blockStmt
%type <transStmts> stmtList
%type <transType> type
%type <transFormal> formalDecl
%type <transFormalList> formals
%type <transType> primType

/* NOTE: Make sure to add precedence and associativity 
 * declarations
 */
%right ASSIGN
%left OR
%left AND
%nonassoc LESS GREATER LESSEQ GREATEREQ EQUALS NOTEQUALS
%left DASH CROSS
%left STAR SLASH
%left NOT 

%%

program 	: globals
		  {
		  $$ = new ProgramNode($1);
		  *root = $$;
		  }

globals 	: globals varDecl SEMICOL
	  	  { 
	  	  $$ = $1; 
	  	  DeclNode * declNode = $2;
		  $$->push_back(declNode);
	  	  }
		| globals FN COLON fnDecl
		  {
	  	  $$ = $1; 
	  	  DeclNode * declNode = $4;
		  $$->push_back(declNode);
		  }
		
		| /* epsilon */
		  {
		  $$ = new std::list<DeclNode * >();
		  }

varDecl 	: type id
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new VarDeclNode(p, $1, $2);
		  }

type		: primType
		  {
		  $$ = $1;
		  }

primType 	: INT
	  	  { 
		  $$ = new IntTypeNode($1->pos());
		  }
		| BOOL
		  {
		  $$ = new BoolTypeNode($1->pos());
		  }
		| VOID
		  {
		  $$ = new VoidTypeNode($1->pos());
		  }
		| FILE
		  {
		  $$ = new FileTypeNode($1->pos());
		  }

fnDecl  : LPAREN formals RPAREN type id LCURLY stmtList RCURLY
		  {
		  auto pos = new Position($1->pos(), $8->pos());
		  $$ = new FnDeclNode(pos, $2, $4, $5, $7);
		  }
		| LPAREN RPAREN type id LCURLY stmtList RCURLY
		  {
		  const auto pos = new Position($1->pos(), $7->pos());
		  auto args = new std::list<FormalDeclNode *>();
		  TypeNode * r = $3;
		  IDNode * i = $4;
		  std::list<StmtNode *> * body = $6;
		  $$ = new FnDeclNode(pos, args, r, i, body);
		  }

formals 	: formalDecl
		  {
		  $$ = new std::list<FormalDeclNode *>();
		  $$->push_back($1);
		  }
		| formals COMMA formalDecl
		  {
		  $$ = $1;
		  $$->push_back($3);
		  }

formalDecl 	: type id
		  {
		  const Position * pos = new Position($1->pos(), $2->pos());
		  $$ = new FormalDeclNode(pos, $1, $2);
		  }

stmtList 	: /* epsilon */
	   	  {
		  $$ = new std::list<StmtNode *>();
	   	  }
		| stmtList stmt SEMICOL
	  	  {
		  $$ = $1;
		  $$->push_back($2);
	  	  }
		| stmtList blockStmt
	  	  {
		  $$ = $1;
		  $$->push_back($2);
	  	  }

blockStmt	: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
		  const Position * p = new Position($1->pos(), $7->pos());
		  $$ = new WhileStmtNode(p, $3, $6);
		  }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
		  const Position * p = new Position($1->pos(), $7->pos());
		  $$ = new IfStmtNode(p, $3, $6);
		  }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
		  {
		  const Position * p = new Position($1->pos(), $11->pos());
		  $$ = new IfElseStmtNode(p, $3, $6, $10);
		  }

stmt		: varDecl
		  {
		  const Position * p = $1->pos();
		  $$ = new VarDeclNode(p, $1->getTypeNode(), $1->ID());
		  }
		| loc ASSIGN exp
		  {
		  const auto p = new Position($1->pos(), $3->pos());
		  $$ = new AssignStmtNode(p, $1, $3); 
		  }
		| OPEN READ loc STRINGLITERAL
		  {
		  auto p = new Position($1->pos(), $4->pos());
		  std::string path = $4->str();
		  $$ = new OpenStmtNode(p, $3, path, true);
		  }
		| OPEN WRITE loc STRINGLITERAL
		  {
		  auto p = new Position($1->pos(), $4->pos());
		  std::string path = $4->str();
		  $$ = new OpenStmtNode(p, $3, path, false);
		  }
		| CLOSE loc
		  {
		  auto p = new Position($1->pos(), $2->pos());
		  $$ = new CloseStmtNode(p, $2);
		  }
		| loc POSTDEC
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new PostDecStmtNode(p, $1);
		  }
		| loc POSTINC
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new PostIncStmtNode(p, $1);
		  }
		| loc READ loc
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new ReadStmtNode(p, $1, $3);
		  }
		| loc WRITE exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new WriteStmtNode(p, $1, $3);
		  }
		| RETURN exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new ReturnStmtNode(p, $2);
		  }
		| RETURN
		  {
		  $$ = new ReturnStmtNode($1->pos(), nullptr);
		  }
		| callExp
		  { 
		  $$ = new CallStmtNode($1->pos(), $1); 
		  }

exp		: exp DASH exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new MinusNode(p, $1, $3);
		  }
		| LPAREN exp QUESTION exp COLON exp RPAREN
		  {
	  	  auto p = new Position($1->pos(), $7->pos());
		  $$ = new TernaryExpNode(p, $2, $4, $6);
		  }
		| exp CROSS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new PlusNode(p, $1, $3);
		  }
		| exp STAR exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new TimesNode(p, $1, $3);
		  }
		| exp SLASH exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new DivideNode(p, $1, $3);
		  }
		| exp AND exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new AndNode(p, $1, $3);
		  }
		| exp OR exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new OrNode(p, $1, $3);
		  }
		| exp EQUALS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new EqualsNode(p, $1, $3);
		  }
		| exp NOTEQUALS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new NotEqualsNode(p, $1, $3);
		  }
		| exp GREATER exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new GreaterNode(p, $1, $3);
		  }
		| exp GREATEREQ exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new GreaterEqNode(p, $1, $3);
		  }
		| exp LESS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new LessNode(p, $1, $3);
		  }
		| exp LESSEQ exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new LessEqNode(p, $1, $3);
		  }
		| NOT exp
	  	  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new NotNode(p, $2);
		  }
		| DASH term
	  	  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new NegNode(p, $2);
		  }
		| term
	  	  { $$ = $1; }

callExp		: id LPAREN RPAREN
		  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  std::list<ExpNode *> * noargs =
		    new std::list<ExpNode *>();
		  $$ = new CallExpNode(p, $1, noargs);
		  }
		| id LPAREN actualsList RPAREN
		  {
		  const Position * p = new Position($1->pos(), $4->pos());
		  $$ = new CallExpNode(p, $1, $3);
		  }

actualsList	: exp
		  {
		  std::list<ExpNode *> * list =
		    new std::list<ExpNode *>();
		  list->push_back($1);
		  $$ = list;
		  }
		| actualsList COMMA exp
		  {
		  $$ = $1;
		  $$->push_back($3);
		  }

term 		: loc
		  { $$ = $1; }
		| INTLITERAL 
		  { $$ = new IntLitNode($1->pos(), $1->num()); }
		| STRINGLITERAL 
		  { $$ = new StrLitNode($1->pos(), $1->str()); }
		| TRUE
		  { $$ = new TrueNode($1->pos()); }
		| FALSE
		  { $$ = new FalseNode($1->pos()); }
		| LPAREN exp RPAREN
		  { $$ = $2; }
		| callExp
		  { $$ = $1; } 

loc		: id
		  {
		  $$ = $1;
		  }

id		: ID
		  {
		  const Position * pos = $1->pos();
		  $$ = new IDNode(pos, $1->value()); 
		  }
		| CONSOLE
		  {
		  const Position * pos = $1->pos();
		  $$ = new IDNode(pos, "console"); 
		  }
	
%%

void jeff::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
