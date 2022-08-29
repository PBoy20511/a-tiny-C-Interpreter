// cin/cout
// while loop still has bug

# include <string.h>
# include <map>
# include <stdio.h>
# include <iostream>
# include <vector>
# include <string>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <iostream>  
# include <sstream>  
using namespace std;

int gLine = 1;
static int uTestCase = 0;
string gEOFoccured = "EOF occured.\n" ;
bool gNewUserInput;
string gPT;

// ================================================================
vector<string> gusedFunctions;

void PrintUsedFunctions() {
  for ( int i = 0 ; i < gusedFunctions.size() ; i++ ) {
    cout << gusedFunctions[i] << endl;
  } // for
} // PrintUsedFunctions()

void AddFunc( string name ) {
  if ( uTestCase == 69 )
    gusedFunctions.push_back( name );
} // AddFunc()

// ================================================================

// ========================

vector<string> gOutputBuffer;

void PrintOutputBuffer() {
  for ( int i = 0 ; i < gOutputBuffer.size() ; i++ )
    cout << gOutputBuffer[i];
} // end PrintOutputBuffer()

void AddOutput( string s ) {
  if ( uTestCase == 10720107 ) {
    gOutputBuffer.push_back( s );
  } // if
} // end AddOutput()

// ===========================

enum TokenType {
  IDENTIFIER = 0, // IDENT
  CONSTANT, // constant, Get a "string" or num
  INT, // int
  FLOAT, // float
  CHAR, // char
  BOOL, // bool
  STRING, // string
  VOID, // void
  IF, // if
  ELSE, // else
  WHILE, // while
  DO, // do
  RETURN, // return
  CIN, // cin
  COUT, // cout
  L_PAREN, // (
  R_PAREN, // )
  L_SQBR, // [
  R_SQBR, // ]
  L_BRACE, // {
  R_BRACE, // }
  PLS, // +
  MNS, // -
  MUL, // *
  DIV, // /
  MOD, // %
  PWR, //  ^
  G, // >
  L, // <
  GT, // >=
  LT, // <=
  EQU, // ==
  NEQ, // !=
  NOT, // !
  AND, // &&
  OR, // ||
  ARI_AND, // &
  ARI_OR, // |
  ASSIGN, // =
  PE, // +=
  ME, // -=
  TE, // *=
  DE, // /=
  RE, // %=
  PP, // ++ 
  MM, // --
  RS, // >>
  LS, // <<
  SEMICOLON, // ;
  COMMA, // ,
  QUESTION, // ?
  COLON, // :
  LEXERROR = 58, // unknown
  EOFTOKEN = 53, // EOF
  UNEXPECTED = 59, // unexpected
  UNDEFINED = 60 // undefined
} ; // enum TokenType

enum IDType {
  TYPE_INT = 9768, 
  TYPE_FLOAT, 
  TYPE_CHAR, 
  TYPE_BOOL, 
  TYPE_STRING, 
  TYPE_VOID,
  TYPE_POS,
  TYPE_NEG,
  TYPE_NOT,
  TYPE_COUT,
  LAV = 61, 
  LAF, 
  LV, 
  LF, 
  DONE = 9453, 
  UNKNOWFUNC 
};

struct Token {
  TokenType type;
  string content;
  int row;
};

typedef vector<Token> * VectorToken;
typedef vector<string> * VectorString;
typedef vector<IDType> * VectorIDType;

struct ID {
  string name;
  IDType type;
  string length;
  VectorString content; // val
  int level;
  bool callByRef;
};

map<string, ID> gIdTable; // Save all the ID user have input
typedef vector<ID> * VectorID;

struct MyFunc {
  string name;
  IDType type;
  VectorID args; // args of function
  VectorToken funcBody; // ??? a ptr of token to save all the tokens in the function body
};

map<string, MyFunc> gFuncTable; // save all the function user has defined

typedef vector<MyFunc> * VectorMyFunc;

string LexError( char c ) {
  string str = "";
  str = str + c ;
  return str;
} // LexError()

bool IsAssignOpFamily( TokenType type  ) {
  if ( type == ASSIGN || type == PE || type == ME || type == TE || type == DE || type == RE ) 
    return true; // += -= *= /= %=

  return false;
} // IsAssignOpFamily()

void GetLine() { 
  char * str = new char[100] ;
  if ( gNewUserInput ) {
    // cout << endl << gLine << "(GetLine)" << endl; ;
    gLine++; 
  } // if

  cin.getline( str, 90 );
} // GetLine()

void PrintErrorMsg( Token mToken ) {
  GetLine();
  gLine = 1;
  if ( mToken.type == LEXERROR )
    printf( "Line %d : unrecognized token with first char : '%s'\n", mToken.row, mToken.content.c_str() );
  else if ( mToken.type == UNEXPECTED )
    printf( "Line %d : unexpected token : '%s'\n", mToken.row, mToken.content.c_str() );
  else if ( mToken.type == UNDEFINED )
    printf( "Line %d : undefined identifier : '%s'\n", mToken.row, mToken.content.c_str() );
} // end PrintErrorMsg()

bool DeclaretionType( TokenType type ) {
  if ( type == INT || type == FLOAT || type == CHAR || type == BOOL || type == STRING || type == VOID )
    return true;
  else
    return false;
} // end DeclaretionType()

bool IsReserved( string name ) {
  if ( name == "ListFunction" || name == "ListVariable" )
    return true;
  else if ( name == "ListAllVariables" || name == "ListAllFunctions" || name == "Done" )
    return true;
  else
    return false;
} // end IsReserved()

bool ExistInFuncTable( string name ) {
  if ( gFuncTable.find( name ) == gFuncTable.end() )
    return false;
  else
    return true;
} // end ExistInFuncTable()

class PreetyPrinter {
  public:

  void PrintType( IDType i ) {
    if ( i == TYPE_INT )
      cout << "int";
    else if ( i == TYPE_FLOAT )
      cout << "float";
    else if ( i == TYPE_CHAR )
      cout << "char";
    else if ( i == TYPE_BOOL )
      cout << "bool";
    else if ( i == TYPE_STRING )
      cout << "string";
    else if ( i == TYPE_VOID )
      cout << "void";

  } // end PrintType()

  void PrintFuncDeclare( IDType type, string name ) {
    PrintType( type );
    cout << " " << name ;
  } // end PrintFuncDeclare()

  void PrintIdName( string name ) {
    cout << name;
  } // end PrintIdName()

  void PrintType_Name( IDType type, string name ) {
    PrintType( type );
    cout << " ";
    PrintIdName( name );
  } // end PrintType_Name()

  void PrintRequireLength( string length ) {
    cout << "[ " << length << " ]";
  } // end PrintRequireLength()

  void IfPrintComma( int i, int aSize ) { // If there is more than one argument, print comma
    if ( i != aSize - 1 )
      cout << ",";
  } // end IfPrintComma()

  void IfPrintSpace( int i, int aSize ) { // If it reaches the last argument, print space
    if ( i == aSize - 1 )
      cout << " ";
  } // end IfPrintSpace()

  void PrintIndent( int &level, bool prev ) { // Print the tabs infront of every line
    if ( ! prev )
      for ( int j = 0 ; j < 2 * level ; j++ ) 
        cout << " " ;
    else 
      for ( int j = 0 ; j < 2 * level-1 ; j++ ) 
        cout << " " ;
  } // end PrintIndent()

  void PrintDeclaration( MyFunc &func, int &i, int level ) { // DONE
    PrintIndent( level, false );
    // TypeSpecifier
    Token token = func.funcBody->at( i );
    cout << token.content << " ";
    i++;

    // RestOfDeclarators starts from IDENT
    token = func.funcBody->at( i );

    while ( token.type != SEMICOLON ) { // ;
      cout << token.content ; 
      if ( token.type == COMMA || token.type == L_SQBR ||  token.type == R_SQBR ) 
        cout << " ";
        
      i++; 
      token = func.funcBody->at( i );
    } // while

    cout << " " << token.content;
    i++;
    return;
    
  } // end PrintDeclaration()

  bool IsOperators( Token token ) { // DONE
    TokenType t = token.type;
    if ( t == PLS || t == MNS || t == MUL || t == DIV || t == MOD || t == PWR || t == ARI_AND )
      return true;
    else if ( t == G || t == L || t == GT || t == LT || t == EQU || t == NEQ || t == NOT || t == AND )
      return true;
    else if ( t == COMMA || t == QUESTION || t == COLON || t == OR || t == ARI_OR )
      return true;
    else
      return false;
  } // end IsOperators()

  bool IsPPMM( TokenType pre, TokenType t ) { // DONE
    if ( pre == IDENTIFIER && ( t == PP || t == MM ) )
      return true;
    else if ( ( pre == PP || pre == MM ) && t == IDENTIFIER )
      return true;

    return false;
  } // end IsPPMM()

  bool IsLRPAREN( TokenType pre, TokenType t ) { // DONE
    if ( pre == L_PAREN && t == R_PAREN )
      return true;
    else if ( pre == IDENTIFIER && ( t == L_PAREN || t == L_SQBR ) )
      return true;
    
    return false;
  } // IsLRPAREN()

  void PrintNextToken( string t ) {
    cout << " " << t;
  } // end PrintNextToken()

  void PrintLine( MyFunc &func, int &i ) { // DONE

    while ( func.funcBody->at( i ).type != SEMICOLON ) {
      if ( IsPPMM( func.funcBody->at( i - 1 ).type, func.funcBody->at( i ).type ) 
           || IsLRPAREN( func.funcBody->at( i - 1 ).type, func.funcBody->at( i ).type ) 
           || func.funcBody->at( i ).type == COMMA ) {
        PrintIdName( func.funcBody->at( i ).content );
      } // end if
      else if ( IsOperators( func.funcBody->at( i - 1 ) ) && 
                ( func.funcBody->at( i ).type == PLS || func.funcBody->at( i ).type == MNS 
                  || func.funcBody->at( i ).type == NOT ) ) {
        PrintNextToken( func.funcBody->at( i ).content );
        if ( func.funcBody->at( i + 1 ).type == IDENTIFIER 
             || func.funcBody->at( i + 1 ).type == CONSTANT ) {
          PrintIdName( func.funcBody->at( i + 1 ).content );
          i++;
        } // end if
      } // end if
      else
        PrintNextToken( func.funcBody->at( i ).content );
      
      i++;
    } // end while

    cout << " " << func.funcBody->at( i ).content ;
    i++;
  } // end PrintLine()

  void CountStack( TokenType &t, int &stack ) { // DONE
    if ( t == L_PAREN )
      stack++;
    else if ( t == R_PAREN )
      stack--;
  } // end CountStack()
  
  void PrintCondition( MyFunc &func, int &index ) { // DONE
    int stack = 0;
    CountStack( func.funcBody->at( index ).type, stack );
    while ( stack != 0 ) {
      if ( IsPPMM( func.funcBody->at( index - 1 ).type, func.funcBody->at( index ).type ) 
           || IsLRPAREN( func.funcBody->at( index - 1 ).type, func.funcBody->at( index ).type ) 
           || func.funcBody->at( index ).type == COMMA ) {
        PrintIdName( func.funcBody->at( index ).content );
      } // if
      else if ( IsOperators( func.funcBody->at( index - 1 ) ) && 
                ( func.funcBody->at( index ).type == PLS || func.funcBody->at( index ).type == MNS 
                  || func.funcBody->at( index ).type == NOT ) ) {
        PrintNextToken( func.funcBody->at( index ).content );
        if ( func.funcBody->at( index + 1 ).type == IDENTIFIER 
             || func.funcBody->at( index + 1 ).type == CONSTANT ) {
          PrintIdName( func.funcBody->at( index + 1 ).content );
          index++;
        } // if
      } // else if
      else
        PrintNextToken( func.funcBody->at( index ).content );
      
      index++;

      CountStack( func.funcBody->at( index ).type, stack );
    } // while

    PrintNextToken( func.funcBody->at( index ).content );
    index++;
  } // PrintCondition()
  
  void PrintStatement( MyFunc &func, int &index, int spaceLev ) { // DONE
    if ( func.funcBody->at( index ).type == L_BRACE ) { // {
      PrintCompoundStatement( func, index, spaceLev );
    } // if
    else {
      PrintIndent( spaceLev, true ) ;
      if ( func.funcBody->at( index ).type == WHILE ) { // while
        PrintNextToken( func.funcBody->at( index ).content );
        PrintCondition( func, ++index );
        if ( func.funcBody->at( index ).type != L_BRACE ) {
          cout << endl;
          PrintStatement( func, index, spaceLev+1 );
        } // if
        else {
          PrintStatement( func, index, spaceLev );
        } // end else

      } // if
      else if ( func.funcBody->at( index ).type == IF ) { // if
        PrintNextToken( func.funcBody->at( index ).content );
        PrintCondition( func, ++index );

        if ( func.funcBody->at( index ).type != L_BRACE ) { // {
          cout << endl;
          PrintStatement( func, index, spaceLev+1 );
        } // if

        else {
          PrintStatement( func, index, spaceLev );
        } // else

        if ( func.funcBody->at( index ).type == ELSE ) {
          cout << endl;
          PrintIndent( spaceLev, true ) ;
          PrintNextToken( func.funcBody->at( index ).content );
          index++;

          if ( func.funcBody->at( index ).type != L_BRACE ) {
            cout << endl;
            PrintStatement( func, index, spaceLev+1 );
          } // if
          else
            PrintStatement( func, index, spaceLev );
        } // if
        
      } // else if
      else {
        if ( func.funcBody->at( index ).type != DO )
          PrintLine( func, index );
      } // else
    } // else

  } // end PrintStatement()
  
  void PrintCompoundStatement( MyFunc &func, int &counter, int spaceLev ) { // DONE
    while ( func.funcBody->at( counter ).type != R_BRACE ) {
      if ( func.funcBody->at( counter ).type == L_BRACE ) {
        cout << " " << func.funcBody->at( counter ).content ; // the 'first' first counter should be '{'
        counter ++;
      } // if
      else if ( func.funcBody->at( counter ).type != VOID 
                && DeclaretionType( func.funcBody->at( counter ).type ) ) 
        PrintDeclaration( func, counter, spaceLev+1 );
      else 
        PrintStatement( func, counter, spaceLev+1 );

      cout << endl;
    } // end while

    PrintIndent( spaceLev, false );
    cout << func.funcBody->at( counter ).content;
    counter++;
  } // end PrintCompoundStatement()

  void PrintFunc( string name ) {
    if ( ! IsReserved( name ) )
      cout << name << "()" << endl;
  } // PrintFunc() 

  void PrintVariables( string var, int level ) {
    if ( var != "cin" && var != "cout" && level == 0 )
      cout << var << endl; 
  } // end PrintVariables()

  void PrintArgs( VectorID &args ) {
    for ( int i = 0 ; i < args->size() ; i++ ) {
      cout << " " ;
      PrintType_Name( args->at( i ).type, args->at( i ).name );

      if ( args->at( i ).length != "" ) 
        PrintRequireLength( args->at( i ).length );

      IfPrintComma( i, args->size() ); // If there is more than one argument, print comma
      IfPrintSpace( i, args->size() ); // If it reaches the last argument, print space
    } // end for

  } // end PrintArgs()

}; // class PreetyPrinter()

class Scanner { // 將input字串轉成token串
public:
  char mCh;

  Scanner() {
    mCh = 0;
  } // end Scanner()

  bool PeekChar( char &c ) {
    c = cin.peek();
    if ( c == EOF ) 
      return false;
    else 
      return true;
  } // PeekChar()

  void SkipWhiteSpace( bool &isEOF ) { // 跳過shiteSpace而且getToken前一定要用
    char pc;
    if ( PeekChar( pc ) == false ) {
      isEOF = true;
      return ;
    } // if

    while ( pc == ' ' || pc == '\t' || pc == '\n' ) {
      if ( pc == '\n' ) {
        // cout << endl << gLine << " (SkipWhiteSpace)" << endl;
        gLine++;
      } // if

      cin.get() ;  //  只讀一個字元
      if ( PeekChar( pc ) == false ) {
        isEOF = true;
        return ;
      } // if
    } // while

  } // SkipWhiteSpace()

  bool IsNum( char c ) {
    if ( c-'0' >= 0 && c-'0' <= 9 ) 
      return true;

    return false;
  } // IsNum()

  bool IsLetter( char c ) {
    // cout << "Anazling... " << c << endl ;
    if ( c >= 'A' && c <= 'Z' ) {
      return true;
    } // if
    else if ( c >= 'a' && c <= 'z' ) {
      return true;
    } // else if

    return false;
  } // IsLetter()

  bool IsIdent( string token ) {
    if ( IsLetter( token[0] ) ) {
      for ( int i = 1 ; i < token.size() ; i++ ) 
        if ( !IsLetter( token[i] ) && !IsNum( token[i] ) ) 
          return false;

      return true;
    } // if

    return false;
  } // IsIdent()
    
  bool IsSpecialSymbol( char c ) {
    if ( c == '=' || c == '>' || c == '<' || c == ':' || c == ';' || c == '+' || c == '-' )
      return true;
    else if ( c == '*' || c == '/' || c == '.' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' ) 
      return true;
    else if ( c == '}' || c == '%' || c == '^' || c == '!' || c == '&' || c == '|' || c == '?' || c == ',' ) 
      return true;
    else if ( c == '\'' || c == '"' )
      return true; 
    else
      return false;
  } // IsSpecialSymbol()

  string TokenTypeOfFirstChar( char c ) {
    if ( IsNum( c ) ) {
      return "Num";
    } // if
    else if ( IsLetter( c ) ) {
      return "Letter";
    } // else if
    else if ( IsSpecialSymbol( c ) ) {
      return "SpecialSymbol";
    } // else if
    else {
      return "LexError" ;
    } // else
  } // TokenTypeOfFirstChar()

  void GetChar( char &temp ) {
    temp = cin.get();
    if ( temp == '\n' ) {
      // cout << endl << gLine << " (GetChar)" << endl;
      gLine++ ;
    } // if
  } // GetChar() */

  string GetTokenStr( bool &lexicalError, int &line ) { 
    // 取得一token並回傳其content，若是LexicalError則回傳LexicalErrorMessage
    string content;
    char peekChar; // 用來"偷看"下一個字
    // char mCh; // 用來"取得"下一個字
    bool noDot = true;
    bool isEOF = false;
    SkipWhiteSpace( isEOF );
    // GetNonWhiteChar( false, false );
    line = gLine;

    if ( isEOF ) {
      return gEOFoccured ;
    } // if

    if ( PeekChar( peekChar ) == false ) {
      isEOF = true ;
      return gEOFoccured ;
    } // if

    string tokenType = TokenTypeOfFirstChar( peekChar );
    if ( tokenType == "LexError" ) {
      lexicalError = true;
      return LexError( peekChar );
    } // if

    while ( IsLetter( peekChar ) || IsNum( peekChar ) || IsSpecialSymbol( peekChar ) || peekChar == '_' ) { 
      // 只有Letter, Num, SpecialSymbol才有繼續讀的必要，遇到不認識的char會直接跳出去回傳目前的tokenContent並且不讀它
      if ( tokenType == "Letter" && ( IsLetter( peekChar ) || peekChar == '_' || IsNum( peekChar ) ) ) {
          
        if ( peekChar == '.' ) { // peeked char
          return content;
        } // if

        GetChar( mCh );
        content = content + mCh;

      } // if
      else if ( tokenType == "Num" && ( IsNum( peekChar ) || peekChar == '.' ) ) {
        bool charIsNum = IsNum( peekChar );
        if ( peekChar == '.' && content != "" && noDot ) {
          GetChar( mCh );
          content = content + mCh;
          noDot = false;
        } // if
        else if ( charIsNum && peekChar != '.' ) {
          GetChar( mCh );
          content = content + mCh;
        } // else if
        else if ( content == "" && charIsNum ) {
          GetChar( mCh );
          content = content + mCh;
        } // else if
        else {
          return content;
        } // else

      } // else if
      else if ( tokenType == "SpecialSymbol" && IsSpecialSymbol( peekChar ) ) {

        if ( peekChar == ';' || peekChar == ',' || peekChar == '?' || peekChar == ':' ) { // ; , ? :

          GetChar( mCh );
          content = content + mCh;
          return content;

        } // else if( peekChar == ";" )

        else if ( peekChar == ']' || peekChar == '[' || peekChar == '}' || peekChar == '{' ) { // { } [ ]

          GetChar( mCh );
          content = content + mCh;
          return content;

        } // else if( peekChar == ";" )


        else if ( peekChar == '+' ) { // +

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured ;
          } // if

          if ( peekChar == '=' || peekChar == '+' ) { // += ++
            GetChar( mCh );
            content = content + mCh;
          } // if

          return content ;

        } // else if( peekChar == "+" )

        else if ( peekChar == '-' ) { // -

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured ;
          } // if

          if ( peekChar == '=' || peekChar == '-' ) { // -= --
            GetChar( mCh );
            content = content + mCh;
          } // if

          return content ;

        } // else if( peekChar == "-" )

        else if ( peekChar == '*' ) { // *

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured ;
          } // if

          if ( peekChar == '=' ) { // *=
            GetChar( mCh );
            content = content + mCh;
          } // if

          return content ;

        } // else if( peekChar == "*" )

        else if ( peekChar == '/' ) { // /

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured ;
          } // if

          if ( peekChar == '/' ) { // 註解的 重取type && reset token
            GetLine();
            content = ""; // reset token

            SkipWhiteSpace( isEOF );
            if ( isEOF ) {
              return gEOFoccured;
            } // if

            if ( PeekChar( peekChar ) == false ) {
              isEOF = true;
              return gEOFoccured;
            } // if

            tokenType = TokenTypeOfFirstChar( peekChar ); // 重設type

          } // if
          else if ( peekChar == '=' ) {
            GetChar( mCh );
            content = content + mCh;
            return content;
          } // else if
          else {
            return content;
          } // else

        } // else if( peekChar == "/" )

        else if ( peekChar == '%' ) {
          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured ;
          } // if

          if ( peekChar == '=' ) { // *=
            GetChar( mCh );
            content = content + mCh;
          } // if

          return content ;
        } // else if ( peekChar == '%' )
        
        else if ( peekChar == '\'' ) { // 'c'
          GetChar( mCh ); // '
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if
          
          if ( peekChar == '\\' ) {
            GetChar( mCh ); 
            if ( PeekChar( peekChar ) == false ) {
              isEOF = true;
              return gEOFoccured;
            } // if

            if ( peekChar == 'n' ) {
              GetChar( mCh );
              content = content + "\\" + "n";
              PeekChar( peekChar );
            } // if

            else if ( peekChar == 'n' || peekChar == 't' || peekChar == '\\' 
                      || peekChar == '\'' || peekChar == '\"' ) {
              GetChar( mCh );
              content = content + "\\" + mCh;
              PeekChar( peekChar );
            } // else if

            if ( peekChar == '\'' ) {
              GetChar( mCh );
              content = content + mCh;
              return content;
            } // else if
            else {
              lexicalError = true;
              return LexError( peekChar );
            } // else

          } // if
          else { // normal char
            while ( PeekChar( peekChar ) && peekChar != '\'' ) {
              GetChar( mCh );
              content = content + mCh;
            } // while

            GetChar( mCh ); // '
            content = content+'\'';
            return content;
          } // else
          
          
        } // else if
        
        else if ( peekChar == '"' ) {
          GetChar( mCh );
          content = content + mCh;
          while ( PeekChar( peekChar ) && peekChar != '\n' ) {
            if ( PeekChar( peekChar ) == false ) {
              isEOF = true;
              return gEOFoccured;
            } // if
            
            if ( cin.peek() == '\\' ) {
              GetChar( mCh );

              if ( PeekChar( peekChar ) == false ) {
                isEOF = true;
                return gEOFoccured;
              } // if

              if ( peekChar == 'n' ) {
                GetChar( mCh );
                content = content + "\\" + "n";
              } // if
              else if ( peekChar == '"' ) {
                GetChar( mCh );
                mCh = 'P';
                content = content + "\\" + "\"";
              } // else if
              else {
                content = content + mCh;
              } // else
            } // if
            else {
              GetChar( mCh );
              content = content + mCh;            
            } // else

            if ( mCh == '"' )
              return content;

          } // while
        
          
          lexicalError = true;
          return LexError( '"' );
          
        } // else if
        
        else if ( peekChar == '&' ) { // &
          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if
          
          if ( peekChar == '&' ) { // &&
            GetChar( mCh );
            content = content + mCh;
          } // if
          
          return content;
        } // else if
        
        else if ( peekChar == '|' ) { // |
          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if
          
          if ( peekChar == '|' ) { // ||
            GetChar( mCh );
            content = content + mCh;
          } // if
          
          return content;
        } // else if

        else if ( peekChar == '=' ) { // =

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if
          
          if ( peekChar == '=' ) { // '=='
            GetChar( mCh );
            content = content + mCh;
          } // if

          return content;

        } // else if( peekChar == "=" )
        
        else if ( peekChar == '!' ) {
          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if
          
          if ( peekChar == '=' ) { // '!='
            GetChar( mCh );
            content = content + mCh;
          } // if

          return content;
        } // else if

        else if ( peekChar == '<' ) { // <

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if

          if ( peekChar == '=' ) { // <=
            GetChar( mCh );
            content = content + mCh;
            return content;
          } // if
          else if ( peekChar == '<' ) { // <<
            GetChar( mCh );
            content = content + mCh;
            return content;
          } // else if
          else {
            return content; // '<'
          } // else

        } // else if( peekChar == "<" )

        else if ( peekChar == '>' ) {      //   '>' '<'  '>=' 

          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if

          if ( peekChar == '=' || peekChar == '>' ) { //  '>=' 
            GetChar( mCh );
            content = content + mCh;
            return content;
          } // if 
          else {
            return content;  // '>'
          } // else

        } // else if ( choose == '>' )

        else if ( peekChar == ')' || peekChar == '(' ) { // ')' '('

          GetChar( mCh );
          content = content + mCh;
          return content;

        } // else if ( peekChar == ')' || peekChar == '(' )

        else if ( peekChar == '.' ) { // In getToken function will handle the '..5' situation
          GetChar( mCh );
          content = content + mCh;
          if ( PeekChar( peekChar ) == false ) {
            isEOF = true;
            return gEOFoccured;
          } // if

          while ( PeekChar( peekChar ) && IsNum( peekChar ) ) {
            GetChar( mCh );
            content = content + mCh;
          } // while

          return content;
        } // else if

        else {
          lexicalError = true;
          char errorToken ;
          GetChar( errorToken );
          return LexError( errorToken ) ;
        } // else

      } // else if( tokenType == "SpecialSymbol" && IsSpecialSymbol( tempChar ) )
      else {
        return content; // 接住類似a+b的情況(無空白，第一輪peek是IsLetter，下一輪peek到+，就會跑進這個else裡面)
      } // else
      
      if ( PeekChar( peekChar ) == false ) { // 收集好前一個token，結束迴圈
        isEOF = true;
        return content;
      } // if

    } // while

    return content;
  } // GetTokenStr()

  bool IsConstantNum( string token ) {
    int dotCounter = 0;
    for ( int i = 0 ; i < token.length() ; i++ ) {
      if ( token[i] == '.' ) {
        dotCounter++;
        if ( dotCounter > 1 )
          return false;
      } // if
      else if ( !IsNum( token[i] ) )
        return false;
    } // for

    return true;
  } // IsConstantNum()

  TokenType GetTokenType( string token ) { // use mTokenType to set token type
    if ( token == "int" )
      return INT;
    else if ( token == "float" )
      return FLOAT;
    else if ( token == "char" )
      return CHAR;
    else if ( token == "bool" )
      return BOOL;
    else if ( token == "string" )
      return STRING;
    else if ( token == "void" )
      return VOID;
    else if ( token == "if" )
      return IF;
    else if ( token == "else" )
      return ELSE;
    else if ( token == "while" )
      return WHILE;
    else if ( token == "do" )
      return DO;
    else if ( token == "return" )
      return RETURN;
    else if ( token == "cin" )
      return IDENTIFIER;
    else if ( token == "cout" )
      return IDENTIFIER;
    else if ( token == "true" )
      return CONSTANT;
    else if ( token == "false" )
      return CONSTANT;

    if ( token[0] == '"' && token[token.size()-1] == '"' ) // "string"
      return CONSTANT;

    if ( token[0] == '\'' && token[token.size()-1] == '\'' ) // 'char'
      return CONSTANT;

    if ( token == "(" ) 
      return L_PAREN;
    else if ( token == ")" )
      return R_PAREN;
    else if ( token == "{" )
      return L_BRACE;
    else if ( token == "}" )
      return R_BRACE;
    else if ( token == "[" )
      return L_SQBR;
    else if ( token == "]" )
      return R_SQBR;
    else if ( token == "+" )
      return PLS;
    else if ( token == "-" )
      return MNS;
    else if ( token == "*" )
      return MUL;
    else if ( token == "/" )
      return DIV;
    else if ( token == "%" )
      return MOD;
    else if ( token == "^" )
      return PWR;
    else if ( token == ">" )
      return G;
    else if ( token == "<" )
      return L;
    else if ( token == ">=" )
      return GT;
    else if ( token == "<=" )
      return LT;
    else if ( token == "==" )
      return EQU;
    else if ( token == "!=" )
      return NEQ;
    else if ( token == "!" )
      return NOT;
    else if ( token == "&&" )
      return AND;
    else if ( token == "||" )
      return OR;
    else if ( token == "&" )
      return ARI_AND;
    else if ( token == "|" )
      return ARI_OR;
    else if ( token == "=" )
      return ASSIGN;
    else if ( token == "+=" )
      return PE;
    else if ( token == "-=" )
      return ME;
    else if ( token == "*=" )
      return TE;
    else if ( token == "/=" )
      return DE;
    else if ( token == "%=" )
      return RE;
    else if ( token == "++" )
      return PP;
    else if ( token == "--" )
      return MM;
    else if ( token == ">>" )
      return RS;
    else if ( token == "<<" )
      return LS;
    else if ( token == ";" )
      return SEMICOLON;
    else if ( token == "," )
      return COMMA;
    else if ( token == "?" )
      return QUESTION;
    else if ( token == ":" )
      return COLON;
    else if ( IsConstantNum( token ) )
      return CONSTANT;
    else
      return IDENTIFIER;
  } // GetTokenType()

  void GetToken( Token &token ) { // if EOF, token status will be change to EOFOCCURED
    bool lexError = false;
    token.content = GetTokenStr( lexError, token.row );
    if ( lexError ) {
      token.type = LEXERROR;
    } // if
    else if ( token.content == gEOFoccured ) {
      token.type = EOFTOKEN;
    } // else if
    else 
      token.type = GetTokenType( token.content );

  } // GetToken()

  void PeekToken( Token &token ) {
    int lineReserved = gLine;
    bool lexError;
    token.content = GetTokenStr( lexError, token.row );
    for ( int i = token.content.size() - 1 ; i >= 0 ; i-- )
      cin.putback( token.content.at( i ) );

    if ( lexError ) 
      token.type = LEXERROR;
    else if ( token.content == gEOFoccured ) {
      token.type = EOFTOKEN;
    } // else if
    else 
      token.type = GetTokenType( token.content );

  } // PeekToken()
  
  string TokenTypeStr( TokenType t ) { // return what's behind of mTokenType's comment
    if ( t == IDENTIFIER ) 
      return "IDENTIFIER";
    else if ( t == CONSTANT )
      return "CONSTANT";
    else if ( t == INT )
      return "INT";
    else if ( t == FLOAT )
      return "FLOAT";
    else if ( t == CHAR )
      return "CHAR";
    else if ( t == BOOL )
      return "BOOL";
    else if ( t == STRING )
      return "STRING";
    else if ( t == VOID )
      return "VOID";
    else if ( t == IF )
      return "IF";
    else if ( t == ELSE )
      return "ELSE";
    else if ( t == WHILE )
      return "WHILE";
    else if ( t == DO )
      return "DO";
    else if ( t == RETURN )
      return "RETURN";
    else if ( t == CIN )
      return "CIN";
    else if ( t == COUT )
      return "COUT";
    else if ( t == L_PAREN )
      return "L_PAREN";
    else if ( t == R_PAREN )
      return "R_PAREN";
    else if ( t == L_SQBR )
      return "L_SQBR";
    else if ( t == R_SQBR )
      return "R_SQBR";
    else if ( t == L_BRACE )
      return "L_BRACE";
    else if ( t == R_BRACE )
      return "R_BRACE";
    else if ( t == PLS )
      return "PLS";
    else if ( t == MNS )
      return "MNS";
    else if ( t == MUL )
      return "MUL";
    else if ( t == DIV )
      return "DIV";
    else if ( t == MOD )
      return "MOD";
    else if ( t == PWR )
      return "PWR";
    else if ( t == EQU )
      return "EQU";
    else if ( t == NEQ )
      return "NEQ";
    else if ( t == LT )
      return "LT";
    else if ( t == GT )
      return "GT";
    else if ( t == G )
      return "G";
    else if ( t == L )
      return "L";
    else if ( t == AND )
      return "AND";
    else if ( t == OR )
      return "OR";
    else if ( t == NOT )
      return "NOT";
    else if ( t == ARI_AND )
      return "ARI_AND";
    else if ( t == ARI_OR )
      return "ARI_OR";
    else if ( t == ASSIGN )
      return "ASSIGN";
    else if ( t == PE )
      return "PE";
    else if ( t == ME )
      return "ME";
    else if ( t == TE )
      return "LE";
    else if ( t == DE )
      return "GE";
    else if ( t == RE )
      return "RE";
    else if ( t == PP )
      return "PP";
    else if ( t == MM )
      return "MM";
    else if ( t == RS )
      return "RS";
    else if ( t == LS )
      return "LS";
    else if ( t == COMMA )
      return "COMMA";
    else if ( t == SEMICOLON )
      return "SEMICOLON";
    else if ( t == QUESTION )
      return "QUESTION";
    else if ( t == COLON )
      return "COLON";
    else if ( t == EOFTOKEN )
      return "EOFOCCURED";
    else if ( t == LEXERROR )
      return "LEXERROR";
    else 
      return "ERROR";

  } // TokenTypeStr()

} ; // class Scanner

PreetyPrinter gPreety;

void ListVariable( string name ) {
  ID id = gIdTable[name.substr( 1, name.size()-2 )];
  gPreety.PrintType_Name( id.type, id.name ); // "type name"
  
  if ( id.length != "" )
    gPreety.PrintRequireLength( id.length );
    
  cout << " ;" << endl;
  
} // end ListVariable()

void ListFunction( string name ) {
  MyFunc func = gFuncTable[name.substr( 1, name.size()-2 )];
  gPreety.PrintFuncDeclare( func.type, func.name ); 
  cout << "(";
  gPreety.PrintArgs( func.args );
  cout << ")";
  int i = 0;
  gPreety.PrintCompoundStatement( func, i, 0 );  // { statement's' }
  cout << endl;
} // end ListFunction()

void ListAllVariables() {
  for ( map<string, ID>::iterator it = gIdTable.begin() ; it != gIdTable.end() ; ++it ) 
    gPreety.PrintVariables( it->first, it->second.level );
} // end ListAllVariables()

void ListAllFunctions() {
  for ( map<string, MyFunc>::iterator it = gFuncTable.begin() ; it != gFuncTable.end() ; ++it ) 
    gPreety.PrintFunc( it->first );
} // end ListAllFunctions()

int StrToInt( string value ) {
  int result;
  sscanf( value.c_str(), "%d", &result );
  return result;
} // end StrToInt()

float StrToFloat( string value ) {
  float result;
  sscanf( value.c_str(), "%f", &result );
  return result;
} // end StrToFloat()

bool StrToBool( string value ) {
  return value == "true";
} // end StrToBool()

class Eval {
  public:
  stringstream mConvertStr;

  void EvalNOTorNEG( IDType &signType, IDType &myType, string &value ) {
    if ( signType == TYPE_POS )
      ;
    else if ( signType == TYPE_NEG && ( myType == TYPE_INT || myType == TYPE_FLOAT ) ) {
      if ( myType == TYPE_INT ) {
        int result = StrToInt( value );
        result = -1 * result;
        mConvertStr.str( string() );
        mConvertStr << result;
        value = mConvertStr.str();
      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float result = StrToFloat( value );
        result = -1 * result;
        mConvertStr.str( string() );
        mConvertStr << result;
        value = mConvertStr.str();
      } // end if
      
    } // end else if
    
    else if ( signType == TYPE_NOT && ( myType == TYPE_BOOL ) ) {
      bool result = StrToBool( value );
      if ( result == true ) value = "false";
      else if ( result == false ) value = "true";
    } // end else if
  } // EvalNOTorNEG()

  void EvalPPMM( Token t, IDType &myType, string &value, int index, string name ) {
    if ( t.type == PP ) {
      if ( myType == TYPE_FLOAT ) {
        float a = StrToFloat( value ) + 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        value = mConvertStr.str();
        gIdTable[ name ].content->at( index ) = value;
      } // end if
      
      else if ( myType == TYPE_INT ) {
        int a = StrToInt( value ) + 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        value = mConvertStr.str();
        gIdTable[ name ].content->at( index ) = value;
      } // end else if
    } // end if
    
    else if ( t.type == MM ) {
      if ( myType == TYPE_FLOAT ) {
        float a = StrToFloat( value ) - 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        value = mConvertStr.str();
        gIdTable[ name ].content->at( index ) = value;
      } // end if
      
      else if ( myType == TYPE_INT ) {
        int a = StrToInt( value ) - 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        value = mConvertStr.str();
        gIdTable[ name ].content->at( index ) = value;
      } // end else if
    } // end else if
  } // end EvalPPMM()

  void EvalAssign( TokenType &type1, string &value, IDType &myType, 
                   string &value2, IDType &type2 ) {
    if ( type1 == ASSIGN )
      value = value2, myType = type2;
      
    else if ( type1 == TE ) {
      
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a * b;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a * b;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if

      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float a = StrToInt( value );
        myType = TYPE_FLOAT;
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a * b;
          value = mConvertStr.str();
        } // end if

        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a * b;
          value = mConvertStr.str();
        } // end else if
      } // end else if
    
    } // end else if
    
    else if ( type1 == DE ) {
      
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a / b;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a / b;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if

      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float a = StrToInt( value );
        myType = TYPE_FLOAT;
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a / b;
          value = mConvertStr.str();
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a / b;
          value = mConvertStr.str();
        } // end else if
      } // end else if
    
    } // end else if
    
    else if ( type1 == RE ) {
      
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a % b;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if
      } // end if
      
    } // end else if
    
    else if ( type1 == PE ) {
      
      if ( myType == TYPE_STRING || type2 == TYPE_STRING ) {
        string a = value, b = value2;
        if ( myType == TYPE_STRING || myType == TYPE_CHAR )
          a = a.substr( 1, a.size()-2 );
        if ( type2 == TYPE_STRING || type2 == TYPE_CHAR )
          b = b.substr( 1, b.size()-2 );
        
        value = '"' + a + b + '"';
        myType = TYPE_STRING;
      } // end if
      
      else if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a + b;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a + b;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if

      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float a = StrToInt( value );
        myType = TYPE_FLOAT;
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a + b;
          value = mConvertStr.str();
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a + b;
          value = mConvertStr.str();
        } // end else if
      } // end else if
    
    } // end else if
    
    else if ( type1 == ME ) {
      
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a - b;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a - b;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if

      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float a = StrToInt( value );
        myType = TYPE_FLOAT;
        if ( type2 == TYPE_INT ) {
          int b = StrToInt( value2 );
          mConvertStr.str( string() );
          mConvertStr << a - b;
          value = mConvertStr.str();
        } // end if
        
        else if ( type2 == TYPE_FLOAT ) {
          float b = StrToFloat( value2 );
          mConvertStr.str( string() );
          mConvertStr << a - b;
          value = mConvertStr.str();
        } // end else if
      } // end else if
    
    } // end else if
  } // EvalAssign()

  void EvalBool( IDType &t1, string &value, IDType &t2, string &v2 ) {
    if ( t1 == TYPE_BOOL ) {
      bool a = StrToBool( value );
      if ( t2 == TYPE_BOOL ) {
        bool b = StrToBool( v2 );
        if ( a || b ) 
          value = "true";
        else
          value = "false";
      } // end if
    } // end if
  } // EvalBool()

  void EvalANDBool( IDType &t1, string &value, IDType &t2, string &v2 ) {
    if ( t1 == TYPE_BOOL ) {
      bool a = StrToBool( value );
      if ( t2 == TYPE_BOOL ) {
        bool b = StrToBool( v2 );
        if ( a && b ) 
          value = "true";
        else
          value = "false";
      } // end if
    } // end if
  } // EvalANDBool()

  void EvalEquality( Token token, string &value, string &v2 ) {
    if ( token.type == EQU ) {
      if ( value == v2 )
        value = "true";
      else 
        value = "false";
    } // end if
    
    else if ( token.type == NEQ ) {
      if ( value != v2 )
        value = "true";
      else 
        value = "false";
    } // end else if
  } // EvalEquality()

  void EvalMaybeAdd( Token token, IDType &t1, IDType &t2, 
                     string &value, string &v2, IDType &myType ) {
    if ( token.type == PLS ) {
      if ( t1 == TYPE_STRING || t2 == TYPE_STRING ) {
        string a = value, b = v2;
        if ( t1 == TYPE_STRING || t1 == TYPE_CHAR )
          a = a.substr( 1, a.size()-2 );
        if ( t2 == TYPE_STRING || t2 == TYPE_CHAR )
          b = b.substr( 1, b.size()-2 );
        
        value = '"' + a + b + '"';
        myType = TYPE_STRING;
      } // end if
      
      else if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if
      
      } // end if
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToFloat( value );
        myType = TYPE_FLOAT;
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          float result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end else if
      
      } // end else if
      
    } // end if
  
    else if ( token.type == MNS ) {
      if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if
      
      } // end if
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToFloat( value );
        myType = TYPE_FLOAT;
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          float result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end else if
      
      } // end else if
    } // end else if
  } // EvalMaybeAdd()

  void EvalCompare( Token token, IDType &t1, string &value, 
                    IDType &t2, string &v2 ) {
    if ( token.type == G ) {
      if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a > b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a > b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end if 
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a > b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a > b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end else if 
    } // end if
    
    else if ( token.type == L ) {
      if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a < b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a < b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end if 
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a < b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a < b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end else if 
    } // end if
    
    else if ( token.type == GT ) {
      if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a >= b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a >= b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end if 
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a >= b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a >= b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end else if 
    } // end if
    
    else if ( token.type == LT ) {
      if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a <= b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a <= b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end if 
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          if ( a <= b )
            value = "true";
          else 
            value = "false";
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToInt( v2 );
          if ( a <= b )
            value = "true";
          else 
            value = "false";
        } // end else if
      } // end else if 
    } // end if
  } // EvalCompare()

  void EvalRestOfMaybeAdd( Token token, IDType &t1, IDType &t2, 
                           string &value, string &v2, IDType &myType ) {
    if ( token.type == PLS ) {
      if ( t1 == TYPE_STRING || t2 == TYPE_STRING ) {
        string a = value, b = v2;
        if ( t2 == TYPE_STRING || t2 == TYPE_CHAR )
          b = b.substr( 1, b.size()-2 );
        if ( t1 == TYPE_STRING || t1 == TYPE_CHAR )
          a = a.substr( 1, a.size()-2 );

        value = '"' + a + b + '"';
        myType = TYPE_STRING;
      } // end if
      
      else if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if
      
      } // end else if
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToFloat( value );
        myType = TYPE_FLOAT;
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          float result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end else if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a + b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end else if
      
      } // end else if
      
    } // end if
  
    else if ( token.type == MNS ) {
      if ( t1 == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_FLOAT;
        } // end else if
      
      } // end if
      
      else if ( t1 == TYPE_FLOAT ) {
        float a = StrToFloat( value );
        myType = TYPE_FLOAT;
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          float result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end if 
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a - b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
        } // end else if
      
      } // end else if
      
    } // end if
  } // EvalRestOfMaybeAdd()

  void EvalPPMM_NOval( Token op, IDType &myType, Token name, int idx, string &value ) {
    // it did not save the result to value, so i did not change it
    if ( op.type == PP ) {
      if ( myType == TYPE_FLOAT ) {
        float a = StrToFloat( value ) + 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        gIdTable[ name.content ].content->at( idx ) = mConvertStr.str();
      } // end if
      
      else if ( myType == TYPE_INT ) {
        int a = StrToInt( value ) + 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        gIdTable[ name.content ].content->at( idx ) = mConvertStr.str();
      } // end else if
    } // end if
    
    else if ( op.type == MM ) {
      if ( myType == TYPE_FLOAT ) {
        float a = StrToFloat( value ) - 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        gIdTable[ name.content ].content->at( idx ) = mConvertStr.str();
      } // end if
      
      else if ( myType == TYPE_INT ) {
        int a = StrToInt( value ) - 1;
        mConvertStr.str( string() );
        mConvertStr << a;
        gIdTable[ name.content ].content->at( idx ) = mConvertStr.str();
      } // end else if
    } // end else if
  } // EvalPPMM_NOval()

  void EvalMULDIV( Token token, IDType &myType, string &value, IDType &t2, string &v2 ) {
    if ( token.type == MUL ) {
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a * b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
          myType = TYPE_INT;
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a * b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
          myType = TYPE_FLOAT;
        } // end if
      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float a = StrToInt( value );
        myType = TYPE_FLOAT;
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          float result = a * b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a * b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
        } // end if
      } // end if
        
    } // end if
    
    else if ( token.type == DIV ) {
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a / b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
          myType = TYPE_INT;
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a / b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
          myType = TYPE_FLOAT;
        } // end if
      } // end if
      
      else if ( myType == TYPE_FLOAT ) {
        float a = StrToInt( value );
        myType = TYPE_FLOAT;
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          float result = a / b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
        } // end if
        
        else if ( t2 == TYPE_FLOAT ) {
          float b = StrToFloat( v2 );
          float result = a / b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
        } // end if
      } // end if
        
    } // end if
    
    else if ( token.type == MOD ) {
      if ( myType == TYPE_INT ) {
        int a = StrToInt( value );
        if ( t2 == TYPE_INT ) {
          int b = StrToInt( v2 );
          int result = a % b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str(); 
          myType = TYPE_INT;
        } // end if
        
      } // end if
      
    } // end else if
  } // EvalMULDIV()

  void EvalShiftINT( int &a, int &b, string &value, IDType &myType ) {
    if ( b != 0 ) {
      int result = a << b;
      mConvertStr.str( string() );
      mConvertStr << result;
      value = mConvertStr.str();
      myType = TYPE_INT;
    } // end if 
  } // EvalShiftINT()

  void EvalShiftCout( string &v, IDType &t, string &result ) {
    if ( t == TYPE_STRING || t == TYPE_CHAR ) { 
      result = result.substr( 1, result.size() - 2 );
      for ( int j = 0 ; j < result.size() - 1 ; j++ ) {
        if ( result[j] == '\\' && result[j+1] == 'n' ) {
          result.replace( j, 2, "\n" );
        } // end if
      } // end for
    } // end if 
  } // EvalShiftCout()

  void EvalRShift( IDType &t1, string &value, IDType &t2, string &v2, IDType &myType ) {
    if ( t1 == TYPE_INT ) { // a >> b
      int a = StrToInt( value );
      if ( t2 == TYPE_INT ) {
        int b = StrToInt( v2 );
        if ( b != 0 ) {
          int result = a >> b;
          mConvertStr.str( string() );
          mConvertStr << result;
          value = mConvertStr.str();
          myType = TYPE_INT;
        } // end if 
      } // end if
    } // end if
  } // EvalRShift()

} ; // class Eval

class Parser {
  public:
  Scanner mSC;
  map<string, ID> mbackUpID_Table;
  map<string, MyFunc> mbackUpFunc_Table;
  Token mPeekToken;
  int mLevel;
  vector<Token> *mTokenBuffer; // use in GetToken to save this line of token
  string mCoutStr;
  Eval mEval;

  void CopyIDTables( map<string, ID> &target, map<string, ID> source ) {
    target.clear();
    for ( map<string, ID>::iterator it = source.begin(); it != source.end() ; it++ ) {
      ID id = it->second;
      VectorString val = id.content;
      target[ it->first ];
      target[ it->first ].name = id.name;
      target[ it->first ].length = id.length;
      target[ it->first ].type = id.type;
      target[ it->first ].content = new vector<string>( *val );
      target[ it->first ].callByRef = id.callByRef;
      target[ it->first ].level = id.level;
      
    } // end for
  } // end CopyIDTables()

  void CopyFuncTables( map<string, MyFunc> &to, map<string, MyFunc> from ) {
    to.clear();
    to.insert( from.begin(), from.end() );
  } // end CopyFuncTables()

  Parser() {
    mLevel = 0;
  } // Parser()

  void SetTokenBuffer() {
    mTokenBuffer = new vector<Token>() ;
  } // SetTokenBuffer()

  void Execute( string name, IDType type ) {
    if ( type == LV )
      ListVariable( name );
    else if ( type == LF )
      ListFunction( name );
    else if ( type == LAV )
      ListAllVariables();
    else if ( type == LAF )
      ListAllFunctions();
    else if ( type == DONE )
      throw "Our-C exited ...";
    else
      ;
  } // Execute()

  void SetBuiltInFunc( MyFunc &f, string name, IDType type ) {
    f.name = name;
    f.type = type;
  } // SetBuiltInFunc()
  
  void PeekToken() {
    mSC.PeekToken( mPeekToken );
    gPT = mPeekToken.content;
    if ( mPeekToken.type == EOFTOKEN ) {
      throw "EOFOCCURED";
    } // if
  } // PeekToken()

  void GetToken( Token &token ) {
    mSC.GetToken( token );
    if ( token.type == EOFTOKEN ) {
      throw "EOFOCCURED";
    } // if
    else if ( token.type == LEXERROR ) {
      throw token;
    } // else if
    else 
      mTokenBuffer->push_back( token );
  } // GetToken()

  bool FunctionExist( MyFunc mDFunc ) {
    if ( gFuncTable.find( mDFunc.name ) == gFuncTable.end() ) {
      return false;
    } // if
    else {
      return true;
    } // else
  } // end FunctionExist()

  void SetDef( MyFunc &mDFunc ) {
    if ( FunctionExist( mDFunc ) ) {
      cout << "New definition of " << mDFunc.name << "() entered ..." << endl;
      AddOutput( "New definition of " + mDFunc.name + "() entered ...\n" );
    } // if
    else {
      cout << "Definition of " << mDFunc.name << "() entered ..." << endl;
      AddOutput( "Definition of " + mDFunc.name + "() entered ...\n" );
    } // else

    gFuncTable[mDFunc.name] = mDFunc;
  } // end SetDef()

  bool IdExist( string mId ) {
    if ( gIdTable.find( mId ) == gIdTable.end() ) 
      return false;
    else 
      return true;
  } // end IdExist()

  void SetID( VectorID &mDID ) { // Given a vector of ID, set every ID in ID table
    for ( int i = 0 ; i < mDID->size() ; i++ ) {
      ID newID = mDID->at( i );
      
      if ( IdExist( newID.name ) ) {
        cout << "New definition of " << newID.name << " entered ..." << endl;
        AddOutput( "New definition of " + newID.name + " entered ...\n" );
      } // if
      else {
        cout << "Definition of " << newID.name << " entered ..." << endl; 
        AddOutput( "Definition of " + newID.name + " entered ...\n" );
      } // else

      gIdTable[newID.name] = newID;
    } // end for
  } // end SetID()

  void CleanUpLine() {
    while ( cin.peek() == ' ' || cin.peek() == '\t' ) {
      cin.get();
    } // end while

    if ( cin.peek() == '\n' ) {
      cin.get();
    } // end if
    else if ( cin.peek() == '/' ) {
      cin.get();
      if ( cin.peek() == '/' ) { // comment
        while ( cin.peek() != '\n' ) 
          cin.get();
        cin.get();
      } // end if
      else
        cin.putback( '/' );
    } // else if

  } // end CleanUpLine()

  void CopyToken( Token &target, Token source ) {
    target.content = source.content;
    target.row = source.row;
    target.type = source.type;
  } // end CopyToken()

  void MyCout() {
    if ( mCoutStr.size() > 0 ) {
      cout << mCoutStr;
      AddOutput( mCoutStr );
      mCoutStr.clear();
    } // end if
  } // end MyCout()

  void BackUp_gTables( map <string, ID> &idTable, map <string, MyFunc> &funcTable ) {
    CopyIDTables( idTable, gIdTable );
    CopyFuncTables( funcTable, gFuncTable );
  } // end BackUp_gTables()

  void Set_gTables( map <string, ID> &idTable, map <string, MyFunc> &funcTable ) {
    CopyIDTables( gIdTable, idTable );
    CopyFuncTables( gFuncTable, funcTable );
  } // end Set_gTables()

  bool UserInput() { 
    // ( definition | statement ) { definition | statement }

    IDType defType;
    VectorID myIdTable = new vector<ID>;
    MyFunc myFunc;
    bool quit;
    string mSValue;
    IDType mSType;
    string value;

    gLine = 1;
    mLevel = 0;
    mCoutStr = "";
    if ( uTestCase == 107 )
      PrintUsedFunctions();
    gusedFunctions.clear();
    cout << "> " ;
    AddOutput( "> " );

    PeekToken();
    gNewUserInput = true;

    BackUp_gTables( mbackUpID_Table, mbackUpFunc_Table );
    if ( DeclaretionType( mPeekToken.type ) ) {
      try {
        if ( Definition( defType, myIdTable, myFunc ) ) {
          if ( defType == TYPE_VOID ) {
            SetDef( myFunc );
          } // end if
          else {
            SetID( myIdTable );
          } // end else
          
          CleanUpLine();
        } // end if
        else {
          Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
          Token errorToken;
          CopyToken( errorToken, mPeekToken );
          errorToken.type = UNEXPECTED;
          throw errorToken;
        } // end else
      } // end try

      catch ( Token errorToken ) {
        Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
        PrintErrorMsg( errorToken );
      } // end catch
    } // end if
    
    else {
      try {
        if ( Statement() ) {  
          CleanUpLine();
          MyCout();
          cout << "Statement executed ..." << endl;
          AddOutput( "Statement executed ...\n" );        
        } // end if
        else {
          Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
          Token errorToken;
          CopyToken( errorToken, mPeekToken );
          errorToken.type = UNEXPECTED;
          throw errorToken;
        } // end else

      } // end try
      
      catch ( Token errorToken ) {
        Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
        PrintErrorMsg( errorToken );
      } // end catch
    } // end else if

    while ( ! quit ) {
      gLine = 1;
      mLevel = 0;
      if ( uTestCase == 107 )
        PrintUsedFunctions();
      gusedFunctions.clear();
      cout << "> ";
      AddOutput( "> " );

      PeekToken();
      gNewUserInput = true;
      mCoutStr = "";
      
      BackUp_gTables( mbackUpID_Table, mbackUpFunc_Table );
      if ( DeclaretionType( mPeekToken.type ) ) {
        try {
          if ( Definition( defType, myIdTable, myFunc ) ) {
            CleanUpLine();
            if ( defType == TYPE_VOID ) {
              SetDef( myFunc );
            } // end if
            else {
              SetID( myIdTable );
            } // end else

          } // end if
          else {
            Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
            Token errorToken;
            CopyToken( errorToken, mPeekToken );
            errorToken.type = UNEXPECTED;
            throw errorToken;
          } // end else
        } // end try

        catch ( Token errorToken ) {
          Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
          PrintErrorMsg( errorToken );
        } // end catch
      } // end if
      
      else {
        try {
          if ( Statement() ) {  
            CleanUpLine();
            MyCout();
            cout << "Statement executed ..." << endl;   
            AddOutput( "Statement executed ...\n" );     
          } // end if
          else {
            Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
            Token errorToken;
            CopyToken( errorToken, mPeekToken );
            errorToken.type = UNEXPECTED;
            throw errorToken;
          } // end else

        } // end try
        catch ( Token errorToken ) {
          Set_gTables( mbackUpID_Table, mbackUpFunc_Table );
          PrintErrorMsg( errorToken );
        } // end catch
      } // end else if
      
    } // end while

    return false;
  } // end UserInput()

  IDType GetCONSTANTtype( string value ) {
    if ( value == "true" || value == "false" ) 
      return TYPE_BOOL;
    
    else if ( value[0] == '"' ) 
      return TYPE_STRING;
    
    else if ( value[0] == '\'' ) 
      return TYPE_CHAR;
    
    else if ( strchr( value.c_str(), '.' ) )
      return TYPE_FLOAT;
      
    else 
      return TYPE_INT;
  } // end GetCONSTANTtype()

  bool PeekTokenType( TokenType type ) {
    PeekToken();
    if ( mPeekToken.type == type ) {
      return true;
    } // end if
    else {
      return false;
    } // end else
  } // end PeekTokenType()

  void SetMyFunc( MyFunc &fun, string &name, IDType type, 
                  VectorToken &idTable, VectorID &funcTable ) {
    fun.name = name;
    fun.type = type;
    fun.funcBody = idTable;
    fun.args = funcTable;
  } // end SetMyFunc()

  void SetDeclarators( VectorID &dIDlist, string name, IDType type, int i  ) {
    if ( i == 0 )
      dIDlist->at( i ).name = name;
    dIDlist->at( i ).type = type;
    dIDlist->at( i ).content = new vector<string>();
    
    for ( int j = 0 ; j < StrToInt( dIDlist->at( i ).length ) ; j++ ) {
      dIDlist->at( i ).content->push_back( "" );
    } // for
  } // end SetDeclarators()


  bool Definition( IDType &myType, VectorID &myDeclarators, MyFunc &myfun ) {
    // :           VOID Identifier function_definition_without_ID 
    // | type_specifier Identifier function_definition_or_declarators

    AddFunc( "Definition: " );
    if ( PeekTokenType( VOID ) ) {
      Token token;
      GetToken( token ); // get void token

      if ( PeekTokenType( IDENTIFIER ) ) {
        Token idToken;
        GetToken( idToken ); // get identifier token
        
        string tempV;
        VectorID argsList = new vector<ID>;
        VectorToken bodyList = new vector<Token>;
        if ( FunctionDefinitionWithoutID( tempV, argsList, bodyList ) ) {
          SetMyFunc( myfun, idToken.content, TYPE_VOID, bodyList, argsList );
          myType = TYPE_VOID; // means that it's a function
          return true;
        } // end if
      } // end if
    } // end if
    
    else {
      IDType getType;
      if ( TypeSpecifier( getType ) ) {
        if ( PeekTokenType( IDENTIFIER ) ) {
          Token token;
          GetToken( token ); // get identifier token
          
          string decValue;
          IDType decType;
          VectorID dIDlist = new vector<ID>;
          VectorToken dBodyList = new vector<Token>;
          if ( FunctionDefinitionOrDeclarators( decValue, decType, dIDlist, dBodyList ) ) {
            if ( decType == TYPE_INT ) {
              for ( int i = 0 ; i < dIDlist->size() ; i++ ) {
                SetDeclarators( dIDlist, token.content, getType, i );
              } // end for
              
              myType = getType;
              myDeclarators = dIDlist;
            } // end if
            
            else if ( decType == TYPE_VOID ) {
              SetMyFunc( myfun, token.content, getType, dBodyList, dIDlist );
              myType = TYPE_VOID;
            } // end if
            
            return true;
          } // end if
        } // end if
      } // end if
    } // end else

    return false;
  } // end Definition()

  bool IsDefType() {
    if ( mPeekToken.type == INT || mPeekToken.type == CHAR || mPeekToken.type == FLOAT || 
         mPeekToken.type == STRING || mPeekToken.type == BOOL || mPeekToken.type == VOID ) {
      return true;
    } // end if

    return false;
  } // end IsDefType()

  IDType TokenTypeToIDType( TokenType type ) {
    if ( type == INT ) 
      return TYPE_INT;
    else if ( type == CHAR ) 
      return TYPE_CHAR;
    else if ( type == FLOAT ) 
      return TYPE_FLOAT;
    else if ( type == STRING ) 
      return TYPE_STRING;
    else if ( type == BOOL ) 
      return TYPE_BOOL;

    return TYPE_VOID;
  } // end TokenTypeToIDType()


  bool TypeSpecifier( IDType &myType ) {
    // : INT | CHAR | FLOAT | STRING | BOOL
    AddFunc( "TypeSpecifier" );
    PeekToken();
    if ( IsDefType() && mPeekToken.type != VOID ) {
      Token token;
      GetToken( token );
      myType = TokenTypeToIDType( token.type );
      return true;
    } // end if
    
    return false;
  } // end TypeSpecifier()

  IDType TypeFunc() {
    return TYPE_VOID;
  } // TypeFunc()

  IDType TypeDec() {
    return TYPE_INT;
  } // end TypeDec()

  bool FunctionDefinitionOrDeclarators( string &value, IDType &myType, 
                                        VectorID &ids, VectorToken &body ) {
    // : function_definition_without_ID
    // | rest_of_declarators

    AddFunc( "FunctionDefinitionOrDeclarators: " + value );
    if ( PeekTokenType( L_PAREN ) ) {
      string funcValue;
      VectorID funcArgs = new vector<ID>;
      VectorToken funcBody = new vector<Token>;
      if ( FunctionDefinitionWithoutID( funcValue, funcArgs, funcBody ) ) {
        myType = TypeFunc();
        value = funcValue;
        ids = funcArgs;
        body = funcBody;
        return true;
      } // end if
    } // end if
    
    else {
      IDType decT;
      VectorID decIds = new vector<ID>;
      if ( RestOfDeclarators( decT, decIds ) ) {
        myType = TypeDec();
        ids = decIds;
        return true;
      } // end if
    } // end else
    
    return false;
  } // end FunctionDefinitionOrDeclarators()

  void InitId( ID &id ) {
    id.content = new vector<string>();
    id.length = "1";
    id.name = "";
    id.type = TypeDec(); // default is Delacorator
    id.content->push_back( "" );
    id.level = mLevel;
  } // end InitId()

  bool RestOfDeclarators( IDType &myType, VectorID &ids ) {
    // : [ '[' Constant ']' ] 
    // { ',' Identifier [ '[' Constant ']' ] } ';'

    AddFunc( "RestOfDeclarators: " );
    ID id;
    InitId( id );
    if ( PeekTokenType( L_SQBR ) ) {
      Token token;
      GetToken( token );
      if ( PeekTokenType( CONSTANT ) ) {
        Token numToken;
        GetToken( numToken );
        if ( PeekTokenType( R_SQBR ) ) {
          GetToken( token );      
          id.length = numToken.content;
        } // end if
        else {
          return false;
        } // end else
      } // end if
      else {
        return false;
      } // end else
    } // end if
    
    ids->push_back( id );
    while ( PeekTokenType( COMMA ) ) {
      Token token;
      GetToken( token );
      ID id;
      InitId( id );
      if ( PeekTokenType( IDENTIFIER ) ) {
        Token idToken;
        GetToken( idToken );
        id.name = idToken.content;
        if ( PeekTokenType( L_SQBR ) ) {
          GetToken( token );
          if ( PeekTokenType( CONSTANT ) ) {
            Token numToken;
            GetToken( numToken );
            if ( PeekTokenType( R_SQBR ) ) {
              GetToken( token );    
              id.length = numToken.content;
            } // end if
            else {
              return false;
            } // end else
          } // end if
          else {
            return false;
          } // end else
        } // end if
        
      } // end if
      else {
        return false;
      } // end else
      
      ids->push_back( id );
    } // end while
    
    if ( PeekTokenType( SEMICOLON ) ) {
      Token token;
      GetToken( token );
      return true;
    } // end if
    else {
      return false;
    } // end else
    
    return false;
  } // end RestOfDeclarators()

  bool FunctionDefinitionWithoutID( string &value, VectorID &args, VectorToken &body ) {
    // : '(' [ VOID | formal_parameter_list ] ')' compound_statement

    AddFunc( "FunctionDefinitionWithoutID: " + value );
    
    map<string, ID> tempIdTable;
    CopyIDTables( tempIdTable, gIdTable );
    if ( PeekTokenType( L_PAREN ) ) {
      Token token;
      GetToken( token ); // (
      if ( PeekTokenType( VOID ) ) {
        Token token2;
        GetToken( token2 );
      } // end if
      else {
        VectorID argList = new vector<ID>;
        if ( FormalParameterList( argList ) ) {
          args = argList;
        } // end if 
        
      } // end else
      
      if ( PeekTokenType( R_PAREN ) ) {
        Token token2;
        GetToken( token2 );
        string csV;
        VectorToken csB = new vector<Token>();
        if ( CompoundStatement( csV, csB ) ) {
          body = csB;
          value = csV;
          CopyIDTables( gIdTable, tempIdTable );
          return true;
        } // end if
      } // end if
    } // end if
    
    CopyIDTables( gIdTable, tempIdTable );
    return false;
  } // end FunctionDefinitionWithoutID()

  bool FormalParameterList( VectorID &args ) {
    // : type_specifier [ '&' ] Identifier [ '[' Constant ']' ] 
    //   { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }

    AddFunc( "FormalParameterList: " );
    IDType mTSType;
    if ( TypeSpecifier( mTSType ) ) {
      ID id;
      InitId( id );
      id.type = mTSType;
      id.level = 1;
      id.callByRef = false;
      
      if ( PeekTokenType( ARI_AND ) ) {
        Token token;
        GetToken( token );
        id.callByRef = true;
      } // end if

      if ( PeekTokenType( IDENTIFIER ) ) {
        Token idToken;
        GetToken( idToken );
        id.name = idToken.content;
        if ( PeekTokenType( L_SQBR ) ) {
          Token token2;
          GetToken( token2 );
          if ( PeekTokenType( CONSTANT ) ) {
            Token numToken;
            GetToken( numToken );
            if ( PeekTokenType( R_SQBR ) ) {
              GetToken( token2 );
              id.length = numToken.content;
            } // end if
            else {
              return false;
            } // end else
          } // end if
          
          else {
            return false;
          } // end else
        } // end if
        
        gIdTable[idToken.content] = id;
        args->push_back( id );
        
        while ( PeekTokenType( COMMA ) ) {
          Token token2;
          GetToken( token2 );
          IDType mTS2Type;
          if ( TypeSpecifier( mTS2Type ) ) {
            ID id;
            InitId( id );
            id.type = mTS2Type;
            id.level = 1;
            id.callByRef = false;
              
            if ( PeekTokenType( ARI_AND ) ) {
              Token token3;
              GetToken( token3 );
              id.callByRef = true;
            } // end if
            
            if ( PeekTokenType( IDENTIFIER ) ) {
              Token idToken;
              GetToken( idToken );
              id.name = idToken.content;
              if ( PeekTokenType( L_SQBR ) ) {
                GetToken( token2 );
                if ( PeekTokenType( CONSTANT ) ) {
                  Token numToken;
                  GetToken( numToken );
                  if ( PeekTokenType( R_SQBR ) ) {
                    GetToken( token2 );   
                    id.length = numToken.content;
                  } // end if
                  else {
                    return false;
                  } // end else
                } // end if
                else {
                  return false;
                } // end else
              } // end if
              
              gIdTable[idToken.content] = id;
              args->push_back( id );
            } // end if 
            else {
              return false;
            } // end else
          } // end if 
          else {
            return false;
          } // end else
        } // end while

        return true;
      } // end if
    } // end if
    
    return false;
  } // end FormalParameterList()

  void RedefineIDingIDTable( ID &id, string index ) {
    VectorString val = id.content;
    gIdTable[ index ];
    gIdTable[ index ].name = id.name;
    gIdTable[ index ].length = id.length;
    gIdTable[ index ].type = id.type;
    gIdTable[ index ].content = new vector<string>( *val );
    gIdTable[ index ].callByRef = id.callByRef;
    gIdTable[ index ].level = id.level;
  } // end RedefineIDingIDTable()

  bool CompoundStatement( string &value, VectorToken &body ) {
    // : '{' { declaration | statement } '}'

    AddFunc( "CompoundStatement: " + value );
    value = "";
    if ( PeekTokenType( L_BRACE ) ) {
      mLevel++;
      Token token;
      GetToken( token );
      
      map<string, ID> tempIdTable;
      CopyIDTables( tempIdTable, gIdTable );
      int startIndex = mTokenBuffer->size() - 1;

      PeekToken();
      while ( mPeekToken.type != R_BRACE ) {        
        if ( IsDefType() ) {
          IDType dT;
          VectorID dIds = new vector<ID>;
          if ( Declaration( dT, dIds ) ) {
            for ( int i = 0 ; i < dIds->size() ; i++ ) {
              ID newID = dIds->at( i );
              gIdTable[newID.name] = newID;
            } // end for

          } // end if
          else {
            mLevel--;
            return false;
          } // end else
          
        } // end if
        else if ( mPeekToken.type != EOFTOKEN ) {
          if ( ! Statement() ) {
            mLevel--;
            return false;
          } // if
        } // end else if

        PeekToken();
      } // end while

      Token token2;
      GetToken( token2 );
      mLevel--;
      for ( map<string, ID>::iterator it = gIdTable.begin() ; it != gIdTable.end() ; ++it ) {
        if ( gIdTable[ it->first ].level > mLevel ) { // if level is bigger than current level
          if ( tempIdTable.find( it->first ) != tempIdTable.end() ) { // if it is in the temp table
            // redefine the ID in the uID_table
            ID id = tempIdTable[ it->first ];
            RedefineIDingIDTable( id, it->first );
          } // end if
          else {
            gIdTable.erase( it-- ); 
          } // else
        } // end if
      } // end for
      
      for ( int i = startIndex ; i < mTokenBuffer->size() ; i++ ) {
        body->push_back( mTokenBuffer->at( i ) );
      } // for
      
      return true;
      
    } // end if
    
    mLevel--;
    return false;
  } // end CompoundStatement()

  bool Declaration( IDType &myType, VectorID &ids ) {
    // type_specifier Identifier rest_of_declarators

    AddFunc( "Declaration: " );
    IDType mTSType;
    if ( TypeSpecifier( mTSType ) ) {
      if ( PeekTokenType( IDENTIFIER ) ) {
        Token token;
        GetToken( token );
        
        IDType decTypes;
        VectorID decIds = new vector<ID>;
        if ( RestOfDeclarators( decTypes, decIds ) ) {
          decIds->at( 0 ).name = token.content;
          for ( int i = 0 ; i < decIds->size() ; i++ ) { // set mutiple IDs
            decIds->at( i ).type = mTSType;
          } // end for
          
          ids = decIds;
          myType = mTSType;
          return true;
        } // end if
      } // end if
    } // end if
    
    return false;
  } // end Declaration()

  bool Statement() {
    AddFunc( "Statement: " );
    if ( PeekTokenType( SEMICOLON ) ) {
      Token token;
      GetToken( token );
      return true;
    } // end if
    
    else if ( PeekTokenType( RETURN ) ) {
      Token token;
      GetToken( token );
      
      VectorString eV;
      VectorIDType eT = new vector<IDType>();
      VectorMyFunc eFunc;
      Expression( eV, eT, eFunc );
      if ( PeekTokenType( SEMICOLON ) ) {
        Token token2;
        GetToken( token2 );
        return true;
      } // end if
    } // end else if
    
    else if ( PeekTokenType( IF ) ) {
      Token token;
      GetToken( token );

      map<string, ID> tempIdTable;
      map<string, ID> ifIdTable;
      map<string, ID> elseIdTable;
      CopyIDTables( tempIdTable, gIdTable );
      CopyIDTables( ifIdTable, gIdTable );
      CopyIDTables( elseIdTable, gIdTable );
      string tempCoutStr = mCoutStr;
      string ifCoutStr = "";
      string elseCoutStr = "";

      if ( PeekTokenType( L_PAREN ) ) {
        GetToken( token );
        VectorString eV;
        VectorIDType eT = new vector<IDType>();
        VectorMyFunc eF;
        if ( Expression( eV, eT, eF ) ) {
          if ( PeekTokenType( R_PAREN ) ) {
            GetToken( token );
            CopyIDTables( gIdTable, ifIdTable );
            mCoutStr = ifCoutStr ;
            if ( Statement() ) {
              CopyIDTables( ifIdTable, gIdTable ) ;
              ifCoutStr = mCoutStr;

              if ( PeekTokenType( ELSE ) ) {
                GetToken( token );
                CopyIDTables( gIdTable, elseIdTable ) ;
                mCoutStr = elseCoutStr;
                if ( Statement() ) {
                  CopyIDTables( elseIdTable, gIdTable );
                  elseCoutStr = mCoutStr;
                  mCoutStr = tempCoutStr;

                  if ( StrToBool( eV->at( eV->size()-1 ) ) ) {
                    CopyIDTables( gIdTable, ifIdTable );
                    mCoutStr += ifCoutStr;
                  } // end if
                  else {
                    CopyIDTables( gIdTable, elseIdTable );
                    mCoutStr += elseCoutStr;
                  } // end else

                  return true;
                } // end if

                return false;
              } // end if
              
              mCoutStr = tempCoutStr;
              if ( StrToBool( eV->at( eV->size()-1 ) ) ) {
                CopyIDTables( gIdTable, ifIdTable );
                mCoutStr += ifCoutStr;
              } // end if
              else {
                CopyIDTables( gIdTable, tempIdTable );
              } // end else

              return true;
            } // end if
          } // end if
        } // end if
      } // end if
    } // end if 
    
    else if ( mPeekToken.type == WHILE ) {
      ;
    } // end else if
    
    else if ( mPeekToken.type == DO ) {
      Token token;
      GetToken( token );
      
      if ( Statement() ) {
        if ( PeekTokenType( WHILE ) ) {
          GetToken( token );
          if ( PeekTokenType( L_PAREN ) ) {
            GetToken( token );
            VectorString eV;
            VectorIDType eT = new vector<IDType>();
            VectorMyFunc eF;
            if ( Expression( eV, eT, eF ) ) {
              if ( PeekTokenType( R_PAREN ) ) {
                GetToken( token );
                if ( PeekTokenType( SEMICOLON ) ) {
                  GetToken( token );
                  return true;
                } // end if
              } // end if
            } // end if
          } // end if
        } // end if
      } // end if
    } // end else if
  
    else {
      if ( PeekTokenType( L_BRACE ) ) { // {
        string vvv;
        VectorToken bbb = new vector<Token>();
        if ( CompoundStatement( vvv, bbb ) ) {
          return true;
        } // end if
      } // end if
      else {
        VectorString expVList;
        VectorIDType expTList = new vector<IDType>();
        VectorMyFunc expFList;
        if ( Expression( expVList, expTList, expFList ) ) {
          if ( PeekTokenType( SEMICOLON ) ) {
            Token token;
            GetToken( token );
            for ( int i = 0 ; i < expFList->size() ; i++ ) {
              Execute( expFList->at( i ).name, expFList->at( i ).type );
            } // end for

            return true;
          } // end if
        } // end if
      } // end else
    } // end else

    return false;
  } // end Statement()

  bool Expression( VectorString &value, VectorIDType &myType, VectorMyFunc &myfunc ) {
    // basic_expression { ',' basic_expression }

    AddFunc( "Expression: " );
    myfunc = new vector<MyFunc>();
    myType = new vector<IDType>();
    value = new vector<string>();
    
    PeekToken();
    string beV;
    IDType beT;
    MyFunc befunc;
    if ( BasicExpression( beV, beT, befunc ) ) {
      myfunc->push_back( befunc );
      value->push_back( beV );
      myType->push_back( beT );
      while ( PeekTokenType( COMMA ) ) {
        Token token;
        GetToken( token );
        string moreBeV;
        IDType moreBeT;
        MyFunc morebeFunc;
        if ( BasicExpression( moreBeV, moreBeT, morebeFunc ) ) {
          myfunc->push_back( morebeFunc );
          value->push_back( moreBeV );
          myType->push_back( moreBeT );
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
  } // end Expression()

  void SetNewArgs( string name, VectorID newArgs, MyFunc &myFunc ) {
    if ( name == "Done" && newArgs->empty() ) {
      SetBuiltInFunc( myFunc, "", DONE );
    } // if
    else if ( name == "ListFunction" && newArgs->size() == 1 ) {
      SetBuiltInFunc( myFunc, newArgs->at( 0 ).content->at( 0 ), LF );
    } // else if
    else if ( name == "ListVariable" && newArgs->size() == 1 ) {
      SetBuiltInFunc( myFunc, newArgs->at( 0 ).content->at( 0 ), LV );
    } // else if
    else if ( name == "ListAllVariables" ) {
      SetBuiltInFunc( myFunc, "", LAV );
    } // else if
    else if ( name == "ListAllFunctions" ) {
      SetBuiltInFunc( myFunc, "", LAF );
    } // else if
  } // end SetNewArgs()

  bool IsArray( string name ) {
    if ( gIdTable[ name ].length == "1" ) {
      return false;
    } // if
    else {
      return true;
    } // else
  } // end IsArray()

  bool BasicExpression( string &value, IDType &myType, MyFunc &returnFunc ) {
    // : Identifier rest_of_Identifier_started_basic_exp
    // | ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
    // | sign { sign } signed_unary_exp romce_and_romloe
    // | ( Constant | '(' expression ')' ) romce_and_romloe

    AddFunc( "BasicExpression: " + value );
    if ( PeekTokenType( IDENTIFIER ) ) {
      Token token;
      GetToken( token );
      if ( ! IdExist( token.content ) && ! ExistInFuncTable( token.content ) ) {
        token.type = UNDEFINED;
        throw token;
      } // end if

      if ( IdExist( token.content ) ) {
        value = gIdTable[ token.content ].content->at( 0 );
        myType = gIdTable[ token.content ].type;
      } // end if
      
      string restValue = value;
      IDType restType = myType;
      VectorID restArgs = new vector<ID>;
      bool restAssign = false;
      IDType funcOrID;
      string idName = token.content;
      int index = 0;
      if ( RestOfIdentifierStartedBasicExp( restValue, restAssign, restType, restArgs, 
                                            funcOrID, idName, index ) ) {
        value = restValue;
        myType = funcOrID;
        if ( myType == TYPE_INT && ! IdExist( token.content ) ) {
          token.type = UNDEFINED;
          throw token;
        } // end if

        else if ( myType == TYPE_VOID && ! ExistInFuncTable( token.content ) ) {
          token.type = UNDEFINED;
          throw token;
        } // end else if 
        
        if ( restAssign && myType == TYPE_INT && IdExist( token.content ) ) {
          gIdTable[ token.content ].content->at( index ) = restValue;
        } // end if
        
        else if ( mLevel == 0 && myType == TYPE_VOID ) {
          SetNewArgs( token.content, restArgs, returnFunc );
        } // end if
        
        myType = restType;
        return true;
      } // end if
    } // end if
    
    else if ( PeekTokenType( PP ) || PeekTokenType( MM ) ) {
      Token token;
      GetToken( token );
      if ( PeekTokenType( IDENTIFIER ) ) {
        Token idToken;
        GetToken( idToken );
        if ( ! IdExist( idToken.content ) && ! ExistInFuncTable( idToken.content ) ) {
          idToken.type = UNDEFINED;
          throw idToken;
        } // end if
        
        if ( IdExist( idToken.content ) && ! IsArray( idToken.content ) ) {
          myType = gIdTable[ idToken.content ].type;
          value = gIdTable[ idToken.content ].content->at( 0 );
          mEval.EvalPPMM( token, myType, value, 0, idToken.content );
        } // end if
          
        string v2 = value;
        IDType t2 = myType;
        TokenType op = token.type;
        string s = idToken.content;
        if ( RestOfPPMMIdentifierStartedBasicExp( v2, t2, op, s ) ) {
          if ( ! IdExist( idToken.content ) ) {
            idToken.type = UNDEFINED;
            throw idToken;
          } // end if
          
          value = v2;
          myType = t2;
          return true;
        } // end if
      } // end if
    } // end else if
    
    else if ( PeekTokenType( CONSTANT ) ) {
      Token token;
      GetToken( token );
      value = token.content;
      myType = GetCONSTANTtype( value );
      
      string rrrV = value;
      IDType rrrT = myType;
      if ( RomceAndRomloe( rrrV, rrrT ) ) {
        value = rrrV;
        myType = rrrT;
        return true;
      } // end if
    } // end else if
    
    else if ( PeekTokenType( L_PAREN ) ) {
      Token token;
      GetToken( token );
      
      VectorString eV;
      VectorIDType eT = new vector<IDType>();
      VectorMyFunc eF;
      if ( Expression( eV, eT, eF ) ) {
        if ( PeekTokenType( R_PAREN ) ) {
          Token token2;
          GetToken( token2 );
          value = eV->at( eV->size()-1 );
          myType = eT->at( eT->size()-1 );

          string rV = value;
          IDType rT = myType;
          if ( RomceAndRomloe( rV, rT ) ) {
            value = rV;
            myType = rT;
            return true;
          } // end if
        } // end if
      } // end if
    } // end else if
    
    else {
      string sV;
      IDType sT;
      
      vector<IDType> *sList = new vector<IDType>();
      if ( Sign( sV, sT ) ) {
        sList->push_back( sT );
        string sV2;
        IDType sT2;
        while ( Sign( sV2, sT2 ) ) {
          sList->push_back( sT2 );
        } // end while

        string suV;
        IDType suT;
        if ( SignedUnaryExp( suV, suT ) ) {
          value = suV;
          myType = suT;
          
          for ( int i = 0 ; i < sList->size() ; i++ ) {
            IDType signType = sList->at( i );
            mEval.EvalNOTorNEG( signType, myType, value );
          } // end for
            
          string rrV = value;
          IDType rrT = myType;
          if ( RomceAndRomloe( rrV, rrT ) ) {
            value = rrV;
            myType = rrT;
            return true;
          } // end if
        } // end if
      } // end if
    } // end else
    
    return false;
  } // end BasicExpression()

  bool IsAssignOp( TokenType type ) {
    if ( mPeekToken.type == ASSIGN || mPeekToken.type == TE || mPeekToken.type == DE || 
         mPeekToken.type == RE || mPeekToken.type == PE || mPeekToken.type == ME ) {
      return true;
    } // end if

    return false;
  } // end IsAssignOp()

  bool RestOfIdentifierStartedBasicExp( string &value, bool &assign,
                                        IDType &myType, VectorID &args,
                                        IDType &funcOrID,
                                        string idName, int &index ) {

    AddFunc( "RestOfIdentifierStartedBasicExp: " + value );
    if ( PeekTokenType( L_PAREN ) ) {
      Token token;
      GetToken( token );
      
      VectorID mAPLArgs = new vector<ID>;
      if ( ActualParameterList( mAPLArgs ) ) {
        args = mAPLArgs;
      } // end if
      
      if ( PeekTokenType( R_PAREN ) ) {
        GetToken( token );
        funcOrID = TYPE_VOID;
        string rrV = value;
        IDType rrT = myType;
        if ( RomceAndRomloe( rrV, rrT ) ) {
          value = rrV;
          myType = rrT;
          return true;
        } // end if
      } // end if
      
    } // end if
    
    else {
      if ( PeekTokenType( L_SQBR ) ) {
        Token token;
        GetToken( token );
        VectorString eVlist;
        VectorIDType eTlist = new vector<IDType>();
        VectorMyFunc eFlist;
        if ( Expression( eVlist, eTlist, eFlist ) ) {
          if ( PeekTokenType( R_SQBR ) ) {
            GetToken( token );
            index = StrToInt( eVlist->at( eVlist->size()-1 ) );
            value = gIdTable[ idName ].content->at( index ); 
            myType = gIdTable[ idName ].type;
          } // end if
          else {
            return false;
          } // end else
        } // end if
        else {
          return false;
        } // end else
      } // end else if
      

      if ( PeekTokenType( PP ) || PeekTokenType( MM ) ) {
        Token token;
        GetToken( token );
        Token var;
        var.content = idName;
        mEval.EvalPPMM_NOval( token, myType, var, index, value );
        string rV = value;
        IDType rT = myType;
        if ( RomceAndRomloe( rV, rT ) ) {
          funcOrID = TYPE_INT;
          myType = rT;
          value = rV;
          return true;
        } // end if
      } // end else if
      
      else {
        string aoV;
        TokenType aoT;
        string rrV = value;
        IDType rrT = myType;
        PeekToken();
        if ( IsAssignOp( mPeekToken.type ) ) {
          if ( AssignmentOperator( aoV, aoT ) ) {
            assign = true;
            string beV;
            IDType beT;
            MyFunc beF;
            if ( BasicExpression( beV, beT, beF ) ) {
              funcOrID = TYPE_INT;
              value = gIdTable[ idName ].content->at( index );
              mEval.EvalAssign( aoT, value, myType, beV, beT );
              myType = beT;
              return true;
            } // end if
          } // end if
        } // end if
        
        else if ( RomceAndRomloe( rrV, rrT ) ) {
          funcOrID = TYPE_INT;
          myType = rrT;
          value = rrV;
          return true;
        } // end else if
      } // end else
    } // end else
    
    return false;
  } // end RestOfIdentifierStartedBasicExp()

  bool RestOfPPMMIdentifierStartedBasicExp( string &value, IDType &myType,
                                            TokenType ppOrMM, string idName ) {
    AddFunc( "RestOfPPMMIdentifierStartedBasicExp: " + value );
    int index = 0;
    if ( PeekTokenType( L_SQBR ) ) {
      Token token;
      GetToken( token );
      VectorString vList;
      VectorIDType tList = new vector<IDType>();
      VectorMyFunc fList;
      if ( Expression( vList, tList, fList ) ) {
        if ( PeekTokenType( R_SQBR ) ) {
          GetToken( token );
          index = StrToInt( vList->at( vList->size()-1 ) );
          value = gIdTable[ idName ].content->at( index );
          myType = gIdTable[ idName ].type;
          Token pmToken;
          pmToken.type = ppOrMM;
          mEval.EvalPPMM( pmToken, myType, value, index, idName );
        } // end if
        
        else { 
          return false;
        } // end else
      } // end if
      
      else {
        return false;
      } // end else
    } // end if

    string rrV = value;
    IDType rrT = myType;
    if ( RomceAndRomloe( rrV, rrT ) ) {
      value = rrV;
      myType = rrT;
      return true;
    } // end if
    
    return false;
  } // end RestOfPPMMIdentifierStartedBasicExp()

  bool Sign( string &value, IDType &myType ) {
    if ( PeekTokenType( PLS ) || PeekTokenType( MNS ) || PeekTokenType( NOT ) ) {
      Token token;
      GetToken( token ); 
      
      if ( token.type == PLS )
        myType = TYPE_POS;
        
      if ( token.type == MNS )
        myType = TYPE_NEG;
        
      if ( token.type == NOT )
        myType = TYPE_NOT;
      
      return true;
    } // end if
    
    return false;
  } // end Sign()

  bool ActualParameterList( VectorID &aList ) {
    AddFunc( "ActualParameterList: " );
    string beV;
    IDType beT;
    MyFunc beF;
    if ( BasicExpression( beV, beT, beF ) ) {
      ID tempID;
      tempID.content = new vector<string>();
      tempID.content->push_back( beV );
      tempID.type = beT;
      aList->push_back( tempID );
      
      while ( PeekTokenType( COMMA ) ) {
        Token token;
        GetToken( token );
        string beVV;
        IDType beTT;
        MyFunc beFF;
        if ( BasicExpression( beVV, beTT, beFF ) ) {
          ID tempId;
          tempId.content = new vector<string>();
          tempId.content->push_back( beVV );
          tempId.type = beTT;
          aList->push_back( tempId );
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end ActualParameterList()

  bool AssignmentOperator( string &value, TokenType &myType ) {
    AddFunc( "AssignmentOperator: " + value );
    
    PeekToken();
    if ( IsAssignOp( mPeekToken.type ) ) {
      Token token;
      GetToken( token ); 
      myType = token.type;
      return true;
    } // end if
    
    return false;
  } // end AssignmentOperator()

  bool RomceAndRomloe( string &value, IDType &myType ) {
    AddFunc( "RomceAndRomloe: " + value );
    string expV = value;
    IDType expT = myType;
    if ( RestOfMaybeLogicalOrExp( expV, expT ) ) { // get Expression( or logical )
      value = expV;
      myType = expT;
      if ( PeekTokenType( QUESTION ) ) {
        Token token;
        GetToken( token );
        map<string, ID> ifTempTable, elseTempTable;
        CopyIDTables( ifTempTable, gIdTable );
        CopyIDTables( elseTempTable, gIdTable );

        string beV;
        IDType beT;
        MyFunc beF;
        CopyIDTables( gIdTable, ifTempTable );
        if ( BasicExpression( beV, beT, beF ) ) {
          CopyIDTables( ifTempTable, gIdTable );
          if ( PeekTokenType( COLON ) ) {
            Token token2;
            GetToken( token2 );
            string beVV;
            IDType beTT;
            MyFunc beFF;
            CopyIDTables( gIdTable, elseTempTable );
            if ( BasicExpression( beVV, beTT, beFF ) ) {
              CopyIDTables( elseTempTable, gIdTable );
              if ( StrToBool( expV ) ) {
                value = beV;
                myType = beT;
                CopyIDTables( gIdTable, ifTempTable );
              } // end if
              
              else {
                value = beVV;
                myType = beTT;
                CopyIDTables( gIdTable, elseTempTable );
              } // end else
              
              return true;
            } // end if
          } // end if
        } // end if

        return false;
      } // end if

      return true;
    } // end if
    
    return false;
  } // end RomceAndRomloe()

  bool RestOfMaybeLogicalOrExp( string &value, IDType &myType ) {
    AddFunc( "RestOfMaybeLogicalOrExp: " + value );
    string rV = value;
    IDType rT = myType;
    if ( RestOfMaybeLogicalAndExp( rV, rT ) ) {
      value = rV;
      myType = rT;
      while ( PeekTokenType( OR ) ) {
        Token token;
        GetToken( token );
        string expV;
        IDType expT;
        if ( MaybeLogicalAndExp( expV, expT ) ) {
          mEval.EvalBool( rT, value, expT, expV );
          myType = TYPE_BOOL;
        } // end if
        
        else {
          return false;
        } // end else      
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeLogicalOrExp()

  bool MaybeLogicalAndExp( string &value, IDType &myType ) {
    AddFunc( "MaybeLogicalAndExp: " + value );
    string expV;
    IDType expT;
    if ( MaybeBitOrExp( expV, expT ) ) {
      value = expV;
      myType = expT;
      while ( PeekTokenType( AND ) ) {
        Token token;
        GetToken( token );
        string andExpV;
        IDType andExpT;
        if ( MaybeBitOrExp( andExpV, andExpT ) ) {
          mEval.EvalANDBool( expT, value, andExpT, andExpV );
          myType = TYPE_BOOL;
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeLogicalAndExp()

  bool RestOfMaybeLogicalAndExp( string &value, IDType &myType ) {
    AddFunc( "RestOfMaybeLogicalAndExp: " + value );
    string rExpV = value;
    IDType rExpT = myType;
    if ( RestOfMaybeBitOrExp( rExpV, rExpT ) ) {
      value = rExpV;
      myType = rExpT;
      while ( PeekTokenType( AND ) ) {
        Token token;
        GetToken( token );
        string expVV;
        IDType expTT;
        if ( MaybeBitOrExp( expVV, expTT ) ) {
          mEval.EvalANDBool( rExpT, value, expTT, expVV );
          myType = TYPE_BOOL;
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeLogicalAndExp()

  bool MaybeBitOrExp( string &value, IDType &myType ) {
    // : maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }

    AddFunc( "MaybeBitOrExp: " + value );
    string eV;
    IDType eT;
    if ( MaybeBitExOrExp( eV, eT ) ) {
      value = eV;
      myType = eT;
      while ( PeekTokenType( ARI_OR ) ) {
        Token token;
        GetToken( token );
        string eVV;
        IDType eTT;
        if ( MaybeBitExOrExp( eVV, eTT ) ) {
          ;
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeBitOrExp()

  bool RestOfMaybeBitOrExp( string &value, IDType &myType ) {
    // rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }

    AddFunc( "RestOfMaybeBitOrExp: " + value );
    string rV = value;
    IDType rT = myType;
    if ( RestOfMaybeBitExOrExp( rV, rT ) ) {
      value = rV;
      myType = rT;
      while ( PeekTokenType( ARI_OR ) ) {
        Token token;
        GetToken( token );
        string eVV;
        IDType eTT;
        if ( MaybeBitExOrExp( eVV, eTT ) ) {
          // TODO:
          ;
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
  } // end RestOfMaybeBitOrExp()

  bool MaybeBitExOrExp( string &value, IDType &myType ) {
    //  maybe_bit_AND_exp { '^' maybe_bit_AND_exp }

    AddFunc( "MaybeBitExOrExp: " + value );
    string eV;
    IDType eT;
    if ( MaybeBitAndExp( eV, eT ) ) {
      value = eV;
      myType = eT;
      while ( PeekTokenType( PWR ) ) {
        Token token;
        GetToken( token );
        string eVV;
        IDType eTT;
        if ( MaybeBitAndExp( eVV, eTT ) ) {
          ;
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeBitExOrExp()

  bool RestOfMaybeBitExOrExp( string &value, IDType &myType ) {
    // rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }

    AddFunc( "RestOfMaybeBitExOrExp: " + value );
    string reV = value;
    IDType reT = myType;
    if ( RestOfMaybeBitAndExp( reV, reT ) ) {
      value = reV;
      myType = reT;
      while ( PeekTokenType( PWR ) ) {
        Token token;
        GetToken( token );
        string eVV;
        IDType eTT;
        if ( MaybeBitAndExp( eVV, eTT ) ) {
          ;
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeBitExOrExp()

  bool MaybeBitAndExp( string &value, IDType &myType ) {
    // : maybe_equality_exp { '&' maybe_equality_exp }

    AddFunc( "MaybeBitAndExp: " + value );
    string eqV;
    IDType eqT;
    if ( MaybeEqualityExp( eqV, eqT ) ) {
      value = eqV;
      myType = eqT;
      while ( PeekTokenType( ARI_AND ) ) {
        Token token;
        GetToken( token );
        string eqVV;
        IDType eqTT;
        if ( MaybeEqualityExp( eqVV, eqTT ) ) {
          ;
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeBitAndExp()

  bool RestOfMaybeBitAndExp( string &value, IDType &myType ) {
    // : rest_of_maybe_equality_exp { '&' maybe_equality_exp }
    AddFunc( "RestOfMaybeBitAndExp: " + value );
    string eqV = value;
    IDType eqT = myType;
    if ( RestOfMaybeEqualityExp( eqV, eqT ) ) {
      value = eqV;
      myType = eqT;
      while ( PeekTokenType( ARI_AND ) ) {
        Token token;
        GetToken( token );
        string eqVV;
        IDType eqTT;
        if ( MaybeEqualityExp( eqVV, eqTT ) ) {
          ;
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeBitAndExp()

  bool MaybeEqualityExp( string &value, IDType &myType ) {
    // maybe_relational_exp 
    // { ( EQ | NEQ ) maybe_relational_exp}
    AddFunc( "MaybeEqualityExp: " + value );
    string rV;
    IDType rT;
    if ( MaybeRelationalExp( rV, rT ) ) {
      value = rV;
      myType = rT;
      while ( PeekTokenType( EQU ) || PeekTokenType( NEQ ) ) {
        Token token;
        GetToken( token );
        string rVV;
        IDType rTT;
        if ( MaybeRelationalExp( rVV, rTT ) ) {
          mEval.EvalEquality( token, value, rVV );
          myType = TYPE_BOOL;
        } // end if
        
        else {
          return false;
        } // end else

      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeEqualityExp()

  bool RestOfMaybeEqualityExp( string &value, IDType &myType ) {
    // rest_of_maybe_relational_exp 
    // { ( EQ | NEQ ) maybe_relational_exp }

    AddFunc( "RestOfMaybeEqualityExp: " + value );
    string rV = value;
    IDType rT = myType;
    if ( RestOfMaybeRelationalExp( rV, rT ) ) {
      value = rV;
      myType = rT;
      while ( PeekTokenType( EQU ) || PeekTokenType( NEQ ) ) {
        Token token;
        GetToken( token );
        string rVV;
        IDType rTT;
        if ( MaybeRelationalExp( rVV, rTT ) ) {
          mEval.EvalEquality( token, value, rVV );
          myType = TYPE_BOOL;
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeEqualityExp()

  bool PeekCompareOP() {
    PeekToken();
    if ( mPeekToken.type == L || mPeekToken.type == G ||
         mPeekToken.type == LT || mPeekToken.type == GT ) {
      return true;
    } // end if

    return false;
  } // end PeekCompareOP()

  bool MaybeRelationalExp( string &value, IDType &myType ) {
    // maybe_shift_exp 
    // { ( '<' | '>' | LE | GE ) maybe_shift_exp }

    AddFunc( "MaybeRelationalExp: " + value );
    string sV;
    IDType sT;
    if ( MaybeShiftExp( sV, sT ) ) {
      value = sV;
      myType = sT;
      while ( PeekCompareOP() ) {
        Token token;
        GetToken( token );
        string sVV;
        IDType sTT;
        if ( MaybeShiftExp( sVV, sTT ) ) {
          mEval.EvalCompare( token, sT, value, sTT, sVV );
          myType = TYPE_BOOL;
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
  } // end MaybeRelationalExp()

  bool RestOfMaybeRelationalExp( string &value, IDType &myType ) {
    // rest_of_maybe_shift_exp 
    // { ( '<' | '>' | LE | GE ) maybe_shift_exp }

    AddFunc( "RestOfMaybeRelationalExp: " + value );
    string sV = value;
    IDType sT = myType;
    if ( RestOfMaybeShiftExp( sV, sT ) ) {
      value = sV;
      myType = sT;
      while ( PeekCompareOP() ) {
        Token token;
        GetToken( token );
        string sVV;
        IDType sTT;
        if ( MaybeShiftExp( sVV, sTT ) ) {
          mEval.EvalCompare( token, sT, value, sTT, sVV );
          myType = TYPE_BOOL;
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
  } // end RestOfMaybeRelationalExp()

  bool MaybeShiftExp( string &value, IDType &myType ) {
    // maybe_additive_exp { ( LS | RS ) maybe_additive_exp }

    AddFunc( "MaybeShiftExp: "+ value  );
    string addV;
    IDType addT;  
    if ( MaybeAdditiveExp( addV, addT ) ) {
      value = addV;
      myType = addT;
      while ( PeekTokenType( LS ) || PeekTokenType( RS ) ) {
        Token opToken;
        GetToken( opToken );
        string addVV;
        IDType addTT;
        if ( MaybeAdditiveExp( addVV, addTT ) ) {
          if ( opToken.type == LS ) { // <<

            if ( addT == TYPE_INT ) { // a << b
              int a = StrToInt( value );
              if ( addTT == TYPE_INT ) {
                int b = StrToInt( addVV );
                mEval.EvalShiftINT( a, b, value, myType );
              } // end if
            } // end if
          
            else if ( addT == TYPE_COUT ) { // cout
              string output = addVV;
              mEval.EvalShiftCout( addVV, addTT, output );
              mCoutStr += output;
            } // end else if
          } // end if
          
          else if ( opToken.type == RS ) { // >>
            mEval.EvalRShift( addT, value, addTT, addVV, myType );
          } // end if
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;  
  } // end MaybeShiftExp()

  bool RestOfMaybeShiftExp( string &value, IDType &myType ) {
    AddFunc( "RestOfMaybeShiftExp: " + value );
    string addV = value;
    IDType addT = myType;
    if ( RestOfMaybeAdditiveExp( addV, addT ) ) {
      value = addV;
      myType = addT;
      while ( PeekTokenType( LS ) || PeekTokenType( RS ) ) {
        Token opToken;
        GetToken( opToken );
        string addVV;
        IDType addTT;
        if ( MaybeAdditiveExp( addVV, addTT ) ) {
          if ( opToken.type == LS ) {
            if ( addT == TYPE_INT ) {
              int a = StrToInt( value );
              if ( addTT == TYPE_INT ) {
                int b = StrToInt( addVV );
                mEval.EvalShiftINT( a, b, value, myType );
              } // end if
            } // end if
            
            else if ( addT == TYPE_COUT ) {
              string output = addVV;
              mEval.EvalShiftCout( addVV, addTT, output );
              mCoutStr += output;
            } // end else if
            
          } // end if
          
          else if ( opToken.type == RS ) {
            mEval.EvalRShift( addT, value, addTT, addVV, myType );
          } // end if
        } // end if
        
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;  
  } // end RestOfMaybeShiftExp()

  bool PeekAdditiveOP() {
    PeekToken();
    if ( mPeekToken.type == PLS || mPeekToken.type == MNS ) {
      return true;
    } // if

    return false;
  } // end PeekAdditiveOP()

  bool MaybeAdditiveExp( string &value, IDType &myType ) {
    AddFunc( "MaybeAdditiveExp: " + value );
    string mV;
    IDType mT;
    if ( MaybeMultExp( mV, mT ) ) {
      value = mV;
      myType = mT;
      while ( PeekAdditiveOP() ) {
        Token opToken;
        GetToken( opToken );
        string mVV;
        IDType mTT;
        if ( MaybeMultExp( mVV, mTT ) ) {
          mEval.EvalMaybeAdd( opToken, mT, mTT, value, mVV, myType );
        } // end if
        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if
    
    return false;
  } // end MaybeAdditiveExp()

  bool RestOfMaybeAdditiveExp( string &value, IDType &myType ) {
    AddFunc( "RestOfMaybeAdditiveExp: " + value );
    string mV = value;
    IDType mT = myType;
    if ( RestOfMaybeMultExp( mV, mT ) ) {
      value = mV;
      myType = mT;
      while ( PeekAdditiveOP() ) {
        Token opToken;
        GetToken( opToken );
        string mVV;
        IDType mTT;
        if ( MaybeMultExp( mVV, mTT ) ) {
          mEval.EvalRestOfMaybeAdd( opToken, mT, mTT, value, mVV, myType );
        } // end if

        else {
          return false;
        } // end else
      } // end while

      return true;
    } // end if

    return false; 
  } // end RestOfMaybeAdditiveExp()

  bool MaybeMultExp( string &value, IDType &myType ) {
    AddFunc( "MaybeMultExp: " + value );
    string uV;
    IDType uT;
    if ( UnaryExp( uV, uT ) ) {
      string uVV = uV;
      IDType uTT = uT;
      if ( RestOfMaybeMultExp( uVV, uTT ) ) {
        value = uVV;
        myType = uTT;
        return true;
      } // end if
    } // end if
    
    return false;
    
  } // end MaybeMultExp()

  bool RestOfMaybeMultExp( string &value, IDType &myType ) {
    PeekToken();
    AddFunc( "RestOfMaybeMultExp: "+ value + mPeekToken.content );
    while ( PeekTokenType( MUL ) || PeekTokenType( DIV ) || PeekTokenType( MOD ) ) {
      Token opToken;
      GetToken( opToken );
      string uV;
      IDType uT;
      if ( UnaryExp( uV, uT ) ) {
        mEval.EvalMULDIV( opToken, myType, value, uT, uV );
      } // end if
      
      else {
        return true;
      } // end else
      
    } // end while

    return true;
  } // end RestOfMaybeMultExp()

  bool UnaryExp( string &value, IDType &myType ) {
    AddFunc( "UnaryExp: " + value );
    if ( PeekTokenType( PP ) || PeekTokenType( MM ) ) {
      Token token;
      GetToken( token );

      if ( PeekTokenType( IDENTIFIER ) ) {
        Token idToken;
        GetToken( idToken );
        
        if ( ! IdExist( idToken.content ) ) {
          idToken.type = UNDEFINED;
          throw idToken;
        } // end if
        
        else if ( gIdTable[ idToken.content ].length == "1" ) {
          value = gIdTable[ idToken.content ].content->at( 0 );
          myType = gIdTable[ idToken.content ].type;
          mEval.EvalPPMM( token, myType, value, 0, idToken.content );
        } // end else if
        
        int index = 0;
        if ( PeekTokenType( L_SQBR ) ) {
          Token tempT;
          GetToken( tempT );
          VectorString vList;
          VectorIDType tList = new vector<IDType>();
          VectorMyFunc fList;
          if ( Expression( vList, tList, fList ) ) {
            if ( PeekTokenType( R_SQBR ) ) {
              GetToken( tempT );

              index = StrToInt( vList->at( vList->size()-1 ) );
              value = gIdTable[ idToken.content ].content->at( index );
              myType = gIdTable[ idToken.content ].type;
              mEval.EvalPPMM( token, myType, value, index, idToken.content );
              
              if ( ! IdExist( idToken.content ) ) {
                idToken.type = UNDEFINED;
                throw idToken;
              } // end if
              
              return true;
            } // end if
          } // end if
          
          return false;
        } // end if
        
        return true;
      } // end if
    } // end if
    
    else {
      string sV;
      IDType sT;
      string uuV; // for UnsignedUnaryExp
      IDType uuT;
      
      vector<IDType> *sList = new vector<IDType>();
      
      if ( PeekTokenType( PLS ) || PeekTokenType( MNS ) || PeekTokenType( NOT ) ) {
        if ( Sign( sV, sT ) ) {
          sList->push_back( sT );
          string ssV;
          IDType ssT;
          while ( Sign( ssV, ssT ) ) {
            sList->push_back( ssT );
          } // end while
          
          string suV;
          IDType suT;
          if ( SignedUnaryExp( suV, suT ) ) {
            value = suV;
            myType = suT;
            for ( int i = 0 ; i < sList->size() ; i++ ) {
              IDType signType = sList->at( i );
              mEval.EvalNOTorNEG( signType, myType, value );
            } // end for
            
            return true;
          } // end if      
        } // end if
      } // end if
      
      else {
        if ( UnsignedUnaryExp( uuV, uuT ) ) {
          value = uuV;
          myType = uuT;
          return true;
        } // end else if
      } // end else
      
    } // end else
    
    return false;
  } // end UnaryExp()

  bool SignedUnaryExp( string &value, IDType &myType ) {
    AddFunc( "SignedUnaryExp: "+ value  ) ;
    int index = 0;
    if ( PeekTokenType( IDENTIFIER ) ) {
      Token token;
      GetToken( token );
      
      if ( ! IdExist( token.content ) &&
           ! ExistInFuncTable( token.content ) ) {
        token.type = UNDEFINED;
        throw token;
      } // end if
          
      if ( IdExist( token.content ) ) {
        value = gIdTable[ token.content ].content->at( 0 );
        myType = gIdTable[ token.content ].type;
      } // end if
      
      if ( PeekTokenType( L_PAREN ) ) {
        Token tempToken;
        GetToken( tempToken );
        VectorID argList = new vector<ID>;
        
        if ( ActualParameterList( argList ) ) {
          ;
        } // end if
        
        if ( PeekTokenType( R_PAREN ) ) {
          GetToken( tempToken );
          
          if ( ! ExistInFuncTable( token.content ) ) {
            token.type = UNDEFINED;
            throw token;
          } // end if
          
          if ( token.content == "Done" && argList->empty() ) {
            throw "Our-C exited ...";
          } // end if
          
          return true;
        } // end if
        
        return false;
      } // end if
      
      else if ( PeekTokenType( L_SQBR ) ) {
        Token tempToken;
        GetToken( tempToken );
        VectorString vList;
        VectorIDType tList = new vector<IDType>();
        VectorMyFunc fList;
        if ( Expression( vList, tList, fList ) ) {
          if ( PeekTokenType( R_SQBR ) ) {
            GetToken( tempToken );
            index = StrToInt( vList->at( vList->size()-1 ) );
            value = gIdTable[ token.content ].content->at( index );
            if ( ! IdExist( token.content ) ) {
              token.type = UNDEFINED;
              throw token;
            } // end if
            
            return true;
          } // end if
        } // end if
        
        return false;
      } // end else if
    
    
      if ( ! IdExist( token.content ) ) {
        token.type = UNDEFINED;
        throw token;
      } // end if
      
      return true;
    } // end if
    
    else if ( PeekTokenType( CONSTANT ) ) {
      Token numToken;
      GetToken( numToken );
      value = numToken.content;
      myType = GetCONSTANTtype( value );
      return true;
    } // end else if
    
    else if ( PeekTokenType( L_PAREN ) ) {
      Token token;
      GetToken( token );
      VectorString vList;
      VectorIDType tList = new vector<IDType>();
      VectorMyFunc fList;
      if ( Expression( vList, tList, fList ) ) {
        if ( PeekTokenType( R_PAREN ) ) {
          GetToken( token );
          value = vList->at( vList->size()-1 );
          myType = tList->at( tList->size()-1 );
          return true;
        } // end if
      } // end if
    } // end else if
    
    return false;
  } // end SignedUnaryExp()

  bool UnsignedUnaryExp( string &value, IDType &myType ) {
    AddFunc( "UnsignedUnaryExp: "+ value ) ;
    if ( PeekTokenType( IDENTIFIER ) ) {
      Token idToken;
      GetToken( idToken );
      
      if ( ! ExistInFuncTable( idToken.content ) &&
           ! IdExist( idToken.content ) ) {
        idToken.type = UNDEFINED;
        throw idToken;
      } // end if
              
      if ( IdExist( idToken.content ) ) {
        value = gIdTable[ idToken.content ].content->at( 0 );
        myType = gIdTable[ idToken.content ].type;
      } // end if
          
      int index = 0;
      if ( PeekTokenType( L_PAREN ) ) {
        Token token2;
        GetToken( token2 );
        VectorID argList = new vector<ID>;
        if ( ActualParameterList( argList ) ) {
          ;
        } // end if

        if ( PeekTokenType( R_PAREN ) ) {
          GetToken( token2 );
          if ( ! ExistInFuncTable( idToken.content ) ) {
            idToken.type = UNDEFINED;
            throw idToken;
          } // end if
          
          if ( idToken.content == "Done" && argList->empty() ) {
            throw "Our-C exited ...";
          } // end if
            
          return true;
        } // end if
        
        return false;
      } // end if ( mPeekToken.type == L_PAREN )
      
      else if ( mPeekToken.type == L_SQBR ) {
        Token token2;
        GetToken( token2 );
        VectorString vList;
        VectorIDType tList = new vector<IDType>();
        VectorMyFunc fList;
        if ( Expression( vList, tList, fList ) ) {
          if ( PeekTokenType( R_SQBR ) ) {
            GetToken( token2 );
            index = StrToInt( vList->at( vList->size()-1 ) );
            value = gIdTable[ idToken.content ].content->at( index );
            if ( PeekTokenType( PP ) || PeekTokenType( MM ) ) {
              Token opToken;
              GetToken( opToken );
              // it did not save the result to value, so i did not change it
              // inside []
              mEval.EvalPPMM_NOval( opToken, myType, idToken, index, value );
            } // end if
            
            if ( ! IdExist( idToken.content ) ) {
              idToken.type = UNDEFINED;
              throw idToken;
            } // end if
            
            return true;
          } // end if ( mPeekToken.type == R_SQBR ) 
        } // end if Expression ( mECorrect, mEValue, mEType, mEHandler )

        return false;
      } // end else if ( mPeekToken.type == L_SQBR )
      
      else if ( PeekTokenType( PP ) || PeekTokenType( MM ) ) {
        Token token2;
        GetToken( token2 );
        mEval.EvalPPMM_NOval( token2, myType, idToken, index, value );
      } // end else if ( mPeekToken.type == PP || mPeekToken.type == MM )
      
      if ( ! IdExist( idToken.content ) ) {
        idToken.type = UNDEFINED;
        throw idToken;
      } // end if ( uID_Table.find( token.val ) == uID_Table.end() )
      
      return true;
    } // end if ( mPeekToken.type == IDENTIFIER )
    
    else if ( PeekTokenType( CONSTANT ) ) {
      Token numToken;
      GetToken( numToken );
      value = numToken.content;
      myType = GetCONSTANTtype( value );
      return true;
    } // end else if
    
    else if ( PeekTokenType( L_PAREN ) ) {
      Token token;
      GetToken( token );
      VectorString vList;
      VectorIDType tList = new vector<IDType>();
      VectorMyFunc fList;
      if ( Expression( vList, tList, fList ) ) {
        if ( PeekTokenType( R_PAREN ) ) {
          GetToken( token );
          value = vList->at( vList->size()-1 );
          myType = tList->at( tList->size()-1 );
          return true;
        } // end if
      } // end if
    } // end else if
    
    return false;
  } // end UnsignedUnaryExp()

}; // Parser

class OurC{
  public:
  bool mquit;
  Parser mpr;

  void InitTables() {
    gIdTable["cin"];
    gIdTable["cin"].content = new vector<string>();
    gIdTable["cin"].content->push_back( "" );
    gIdTable["cout"];
    gIdTable["cout"].content = new vector<string>();
    gIdTable["cout"].content->push_back( "" );
    gIdTable["cout"].type = TYPE_COUT;
    
    gFuncTable["Done"];
    gFuncTable["ListAllFunctions"];
    gFuncTable["ListAllVariables"];
    gFuncTable["ListFunction"];
    gFuncTable["ListVariable"];
    mquit = false;
  }  // InitTables()


  void StartOurC() {

    mpr.SetTokenBuffer();
    mpr.mPeekToken.type = LEXERROR;
    mpr.mPeekToken.content = "";
    InitTables();
    try { // catch quit
      while ( ! mquit ) {
        try {
          gNewUserInput = false;
          mpr.UserInput();
        } // end try
        catch ( Token errorToken ) {
          PrintErrorMsg( errorToken );
        } // end catch
      } // end while
        
    } // end try
    catch ( char const* s ) {
      cout << s << endl;
    } // end catch
    
  } // StartOurC()
  
} ; // class OurC

int main() {
  scanf( "%d", &uTestCase );
  char enter;
  scanf( "%c", &enter );
  cout << "Our-C running ...\n" ;
  OurC compiler;
  compiler.StartOurC();
} // end main()
