// last version: myProj2_ver5

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

struct ID {
  string name;
  IDType type;
  string length;
  string content;
  int level;
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

bool ExistInIDTable( string name ) {
  if ( gIdTable.find( name ) == gIdTable.end() )
    return false;
  else
    return true;
} // end ExistInIDTable()

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
      return CIN;
    else if ( token == "cout" )
      return COUT;

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

class Parser {
  public:
  Scanner mSC;
  map<string, ID> mbackUpID_Table;
  map<string, MyFunc> mbackUpFunc_Table;
  Token mPeekToken;
  int mLevel;
  vector<Token> *mTokenBuffer; // use in GetToken to save this line of token

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
    if ( FunctionExist( mDFunc ) ) 
      cout << "New definition of " << mDFunc.name << "() entered ..." << endl;
    else 
      cout << "Definition of " << mDFunc.name << "() entered ..." << endl;

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
      
      if ( IdExist( newID.name ) ) 
        cout << "New definition of " << newID.name << " entered ..." << endl;
      else 
        cout << "Definition of " << newID.name << " entered ..." << endl; 

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

  void GetBackUpTables() { 
    // Sometimes, table will have something we don't want in it, 
    // so we need to set it back to the backup table
    gIdTable = mbackUpID_Table;
    gFuncTable = mbackUpFunc_Table;
  } // end GetBackUpTables()

  void SetBackUpTables() { // Set the backup table to the current table
    mbackUpID_Table = gIdTable;
    mbackUpFunc_Table = gFuncTable;
  } // end SetBackUpTables()

  void CopyToken( Token &target, Token source ) {
    target.content = source.content;
    target.row = source.row;
    target.type = source.type;
  } // end CopyToken()

  bool UserInput( string &value, bool &quit, IDType &returnType ) { 
    // ( definition | statement ) { definition | statement }

    IDType defType;
    VectorID myIdTable = new vector<ID>;
    MyFunc myFunc;
    
    string mSValue;
    IDType mSType;

    gLine = 1;
    mLevel = 0;
    cout << "> ";

    PeekToken();
    gNewUserInput = true;
    
    SetBackUpTables(); // Set Back up table incase error occurs and screws up the table
    if ( DeclaretionType( mPeekToken.type ) ) {
      try {
        if ( Definition( value, defType, myIdTable, myFunc ) ) {
          if ( defType == TYPE_VOID ) {
            SetDef( myFunc );
          } // end if
          else {
            SetID( myIdTable );
          } // end else
          
          CleanUpLine();
        } // end if
        else {
          GetBackUpTables();
          Token errorToken;
          CopyToken( errorToken, mPeekToken );
          errorToken.type = UNEXPECTED;
          throw errorToken;
        } // end else
      } // end try

      catch ( Token errorToken ) {
        GetBackUpTables();
        PrintErrorMsg( errorToken );
      } // end catch
    } // end if
    
    else {
      try {
        if ( Statement( mSValue, mSType ) ) {  
          CleanUpLine();
          cout << "Statement executed ..." << endl;        
        } // end if
        else {
          GetBackUpTables();
          Token errorToken;
          CopyToken( errorToken, mPeekToken );
          errorToken.type = UNEXPECTED;
          throw errorToken;
        } // end else

      } // end try
      
      catch ( Token errorToken ) {
        GetBackUpTables();
        PrintErrorMsg( errorToken );
      } // end catch
    } // end else if


    while ( ! quit ) {
      gLine = 1;
      mLevel = 0;
      cout << "> ";

      PeekToken();
      gNewUserInput = true;
      
      SetBackUpTables(); // Set Back up table incase error occurs and screws up the table
      if ( DeclaretionType( mPeekToken.type ) ) {
        try {
          if ( Definition( value, defType, myIdTable, myFunc ) ) {
            CleanUpLine();
            if ( defType == TYPE_VOID ) {
              SetDef( myFunc );
            } // end if
            else {
              SetID( myIdTable );
            } // end else

          } // end if
          else {
            GetBackUpTables();
            Token errorToken;
            CopyToken( errorToken, mPeekToken );
            errorToken.type = UNEXPECTED;
            throw errorToken;
          } // end else
        } // end try

        catch ( Token errorToken ) {
          GetBackUpTables();
          PrintErrorMsg( errorToken );
        } // end catch
      } // end if
      
      else {
        try {

          if ( Statement( mSValue, mSType ) ) {  
            CleanUpLine();
            cout << "Statement executed ..." << endl;        
          } // end if
          else {
            GetBackUpTables();
            Token errorToken;
            CopyToken( errorToken, mPeekToken );
            errorToken.type = UNEXPECTED;
            throw errorToken;
          } // end else

        } // end try
        
        catch ( Token errorToken ) {
          GetBackUpTables();
          PrintErrorMsg( errorToken );
        } // end catch
      } // end else if
      
      
    } // end while

    return false;
    
  } // end UserInput()

  bool Definition( string &value, IDType &myType, VectorID &myIdTable, MyFunc &myFunc ) { 
    //             VOID  Identifier  function_definition_without_ID 
    // | type_specifier  Identifier  function_definition_or_declarators

    PeekToken();
    if ( mPeekToken.type == VOID ) {
      Token token;
      GetToken( token );
      
      PeekToken();
      if ( mPeekToken.type == IDENTIFIER ) {
        Token idToken;
        GetToken( idToken );
        
        string mFDWIDValue;
        IDType mFDWIDType;
        if ( FunctionDefinitionWithoutID( mFDWIDValue, mFDWIDType, myFunc.args, myFunc.funcBody ) ) {
          myFunc.name = idToken.content;
          myFunc.type = TYPE_VOID;
          myType = TYPE_VOID;
          return true;
        } // end if
      } // end if
    } // end if
    
    else {
      if ( TypeSpecifier( myType ) ) {
        PeekToken();
        if ( mPeekToken.type == IDENTIFIER ) {
          Token token;
          GetToken( token );
          
          string mFDODValue;
          IDType mFDODType;
          VectorToken mFDODBody = new vector<Token>;
          if ( FunctionDefinitionOrDeclarators( mFDODValue, mFDODType, myIdTable, mFDODBody ) ) {
            if ( mFDODType == TYPE_INT ) {
              for ( int i = 0 ; i < myIdTable->size() ; i++ ) { 
                // save the IDs i got along the way into my ID table
                if ( i == 0 )
                  myIdTable->at( i ).name = token.content;
                myIdTable->at( i ).type = myType;
              } // end for

            } // end if
            
            else if ( mFDODType == TYPE_VOID ) {
              myFunc.name = token.content;
              myFunc.funcBody = mFDODBody;
              myFunc.type = myType;
              myFunc.args = myIdTable;
              myType = TYPE_VOID;
              
            } // end if
            
            return true;
          } // end if
        } // end if
      } // end if
    } // end else

    return false;
  } // end Definition()

  void SetExpType( TokenType &type, IDType &returnType ) {
    if ( type == INT ) 
      returnType = TYPE_INT;
    else if ( type == CHAR ) 
      returnType = TYPE_CHAR;
    else if ( type == FLOAT ) 
      returnType = TYPE_FLOAT;
    else if ( type == STRING ) 
      returnType = TYPE_STRING;
    else if ( type == BOOL ) 
      returnType = TYPE_BOOL;
  } // SetExpType()

  bool TypeSpecifier( IDType &returnType ) { // Get the Type Token
    // INT | CHAR | FLOAT | STRING | BOOL
    
    PeekToken();
    if ( mPeekToken.type != VOID && DeclaretionType( mPeekToken.type ) ) {
      Token token;
      GetToken( token );
      SetExpType( token.type, returnType );
      return true;
    } // end if
    
    return false;
  } // end TypeSpecifier()

  bool FunctionDefinitionOrDeclarators( string &value, IDType &returnType, 
                                        VectorID &ids, VectorToken &body ) {
    // function_definition_without_ID | rest_of_declarators

    PeekToken();
    if ( mPeekToken.type == L_PAREN ) {
      VectorID mFDWIDArgs = new vector<ID>;
      VectorToken mFDWIDBody = new vector<Token>;
      if ( FunctionDefinitionWithoutID( value, returnType, mFDWIDArgs, mFDWIDBody ) ) {
        returnType = TYPE_VOID;
        ids = mFDWIDArgs;
        body = mFDWIDBody;
        return true;
      } // end if
    } // end if
    else {
      VectorID mRODIDs = new vector<ID>;
      if ( RestOfDeclarators( value, returnType, mRODIDs ) ) {
        returnType = TYPE_INT;
        ids = mRODIDs;
        return true;
      } // end if
    } // end else
    
    return false;
    
  } // end FunctionDefinitionOrDeclarators()

  bool GetArg( ID &id ) {
    Token numToken;
    GetToken( numToken ); // save '['
    
    PeekToken();
    if ( mPeekToken.type == CONSTANT ) {
      GetToken( numToken );
      PeekToken();
      if ( mPeekToken.type == R_SQBR ) { // ]
        id.length = numToken.content;
        GetToken( numToken );      
      } // end if
      else {
        return false;
      } // end else
    } // end if
    else {
      return false;
    } // end else

    return true;
  } // GetArg()

  bool RestOfDeclarators( string &value, IDType &returnType, VectorID &ids ) {
    // [ '[' Constant ']' ]
    // { ',' Identifier [ '[' Constant ']' ] }
    // ';'

    PeekToken();
    ID id;
    id.length = "";
    id.name = "";
    id.type = TYPE_INT;
    id.content = "";
    id.level = mLevel;
    
    if ( mPeekToken.type == L_SQBR ) { // [
      if ( ! GetArg( id ) )
        return false;
    } // end if
    
    ids->push_back( id ); // use for save function
    
    PeekToken();
    while ( mPeekToken.type == COMMA ) {
      Token token;
      GetToken( token );
      PeekToken();

      ID id;
      id.length = "";
      id.name = "";
      id.type = TYPE_INT;
      id.content = "";
      id.level = mLevel;
      
      if ( mPeekToken.type == IDENTIFIER ) {
        Token nameToken;
        GetToken( nameToken );
        id.name =  nameToken.content;
        
        PeekToken();
        if ( mPeekToken.type == L_SQBR ) {
          if ( ! GetArg( id ) )
            return false;
        } // end if
      } // end if
      else {
        return false;
      } // end else
      
      ids->push_back( id );
      PeekToken();
      
    } // end while
    
    PeekToken();
    if ( mPeekToken.type == SEMICOLON ) {
      Token token;
      GetToken( token );
      return true;
    } // end if
    else {
      return false;
    } // end else
    
  } // end RestOfDeclarators()

  bool FunctionDefinitionWithoutID( string &value, IDType &returnType, VectorID &args, VectorToken &body ) {
    // '(' [ VOID | formal_parameter_list ] ')' compound_statement

    PeekToken();
    map<string, ID> mTempID_Table = gIdTable; // Set back up table
    if ( mPeekToken.type == L_PAREN ) {
      Token token;
      GetToken( token );
      PeekToken();

      string mFPLValue;
      IDType mFPLType;
      VectorID mFPLArgs = new vector<ID>;
      if ( mPeekToken.type == VOID ) 
        GetToken( token );
      else if ( FormalParameterList( mFPLValue, mFPLType, mFPLArgs ) ) 
        args = mFPLArgs; // if there is any args, save it
      
      PeekToken();
      if ( mPeekToken.type == R_PAREN ) { // )
        GetToken( token );
      
        string mCSValue;
        IDType mCSType;
        VectorToken mCSBody = new vector<Token>();
        if ( CompoundStatement( mCSValue, mCSType, mCSBody ) ) {
          body = mCSBody;
          value = mCSValue;
          gIdTable = mTempID_Table; // set the real table back to back up table
          return true;
        } // end if
      } // end if
    } // end if
    
    gIdTable = mTempID_Table; // set the real table back to back up table
    return false;
  } // end FunctionDefinitionWithoutID()

  bool GetRestOfArray( ID &id ) {
    Token token;
    PeekToken();
    if ( mPeekToken.type == CONSTANT ) { // num
      Token tokenOfArraysLenth;
      GetToken( tokenOfArraysLenth );
      PeekToken();
      if ( mPeekToken.type == R_SQBR ) { // ]
        GetToken( token );
        id.length = tokenOfArraysLenth.content;
        return true;
      } // end if
      else {
        return false;
      } // end else

    } // end if
    else {
      return false;
    } // end else

    return true;
  } // end GetRestOfArray()

  bool FormalParameterList( string &value, IDType &returnType, VectorID &args ) { // "int a" / "int a[10]" 
    // type_specifier [ '&' ] Identifier [ '[' Constant ']' ]
    // { ',' type_specifier [ '&' ] Identifier [ '[' Constant ']' ] }

    ID id;
    id.length = "";
    id.content = "";
    id.level = 1;
    if ( TypeSpecifier( id.type ) ) {
      Token token;
      PeekToken();
      if ( mPeekToken.type == ARI_AND ) {
        GetToken( token );
      } // end if

      PeekToken();
      if ( mPeekToken.type == IDENTIFIER ) { // must be ID after type
        GetToken( token );
        id.name = token.content; // SetIdName

        PeekToken();
        if ( mPeekToken.type == L_SQBR ) { // If it's array or not
          Token tokenSQBR;
          GetToken( tokenSQBR );
          if ( ! GetRestOfArray( id ) ) 
            return false;
        } // if
        
        gIdTable[token.content] = id; // Add to ID_Table
        args->push_back( id ); // Add to args of function
        
        while ( true ) {
          id.length = "";
          id.content = "";

          PeekToken();
          if ( mPeekToken.type != COMMA ) { // has no more args
            return true;
          } // end if
          
          Token commaToken;
          GetToken( commaToken );
          if ( TypeSpecifier( id.type ) ) {
            
            PeekToken();
            if ( mPeekToken.type == ARI_AND ) {
              GetToken( token );
            } // end if

            PeekToken();
            if ( mPeekToken.type == IDENTIFIER ) {
              Token tokenIdName;
              GetToken( tokenIdName );
              id.name = tokenIdName.content;
              
              PeekToken();
              if ( mPeekToken.type == L_SQBR ) { // If it's array or not
                Token tokenSQBR;
                GetToken( tokenSQBR );
                if ( ! GetRestOfArray( id ) ) 
                  return false;
              } // if
              
              gIdTable[tokenIdName.content] = id;
              args->push_back( id );
            } // end if 
            else 
              return false;
          } // end if 
          else 
            return false;

        } // end while
      } // end if
    } // end if
    
    mPeekToken.type = UNEXPECTED;
    throw mPeekToken;
    return false;
    
  } // end FormalParameterList()

  void SetFuncBody( string value, int startIndex, VectorToken &body ) {
    for ( int i = startIndex ; i < mTokenBuffer->size() ; i++ ) {
      value += " " + mTokenBuffer->at( i ).content; 
      body->push_back( mTokenBuffer->at( i ) );
    } // for
  } // SetFuncBody()

  bool CompoundStatement( string &value, IDType &returnType, VectorToken &body ) {
    // '{' { declaration | statement } '}'

    map<string, MyFunc> mTempFunc_Table = gFuncTable;
    map<string, ID> mTempID_Table = gIdTable;
    Token token;

    PeekToken();
    if ( mPeekToken.type == L_BRACE ) { // {
      mLevel++; // set the level inside the function
      GetToken( token );

      int startIndex = mTokenBuffer->size() - 1;
      // inorder to handle the case of mutiple '{' '}' in one userInput
      PeekToken();
      while ( mPeekToken.type != R_BRACE ) {
        if ( DeclaretionType( mPeekToken.type ) ) {
          string dValue;
          IDType declaretionType;
          VectorID declaretionIdTable = new vector<ID>;
          if ( Declaration( dValue, declaretionType, declaretionIdTable ) ) {
            for ( int i = 0 ; i < declaretionIdTable->size() ; i++ ) {
              ID newID = declaretionIdTable->at( i );
              gIdTable[newID.name] = newID;
            } // end for
          } // end if
          else {
            // Get back bakup table
            gFuncTable = mTempFunc_Table;
            gIdTable = mTempID_Table;
            mLevel--;
            return false;
          } // else
          
        } // end if
        else if ( mPeekToken.type != EOFTOKEN ) {
          string mSValue;
          IDType mSType;
          if ( Statement( mSValue, mSType ) )
            ;
          else {
            gFuncTable = mTempFunc_Table; // Get back bakup table
            gIdTable = mTempID_Table; // Get back bakup table
            mLevel--;
            return false;
          } // else
        } // end else if

        PeekToken(); 
      } // end while

      GetToken( token ); // }
      gFuncTable = mTempFunc_Table; // Get back bakup table
      gIdTable = mTempID_Table; // Get back bakup table
      SetFuncBody( value, startIndex, body );
      mLevel--;
      return true;
    } // end if

    mLevel--;
    return false;
  } // end CompoundStatement()

  void SetDeclarationsType( string name, IDType type, VectorID &mRODIDs ) {
    for ( int i = 0 ; i < mRODIDs->size() ; i++ ) {
      if ( i == 0 )
        mRODIDs->at( i ).name = name;
      mRODIDs->at( i ).type = type;
    } // end for
  } // SetDeclarationsType()

  bool Declaration( string &value, IDType &returnType, VectorID &ids ) { // int a
    // type_specifier
    // Identifier
    // rest_of_declarators

    IDType myType;
    if ( TypeSpecifier( myType ) ) {
      PeekToken();
      if ( mPeekToken.type == IDENTIFIER ) {
        Token token;
        GetToken( token );
        string mRODValue;
        IDType mRODType;
        VectorID mRODIDs = new vector<ID>;
        if ( RestOfDeclarators( mRODValue, mRODType, mRODIDs ) ) {
          SetDeclarationsType( token.content, myType, mRODIDs );
          ids = mRODIDs;
          returnType = myType;
          return true;
        } // end if
      } // end if
    } // end if
    
    return false;
  } // end Declaration()

  bool GetRestOfStatement( string &value, IDType &myStatementType, 
                           VectorMyFunc &anyBuiltInFunc, bool isIf ) {
    // for if statement and while statement
    PeekToken();
    Token token;
    if ( mPeekToken.type == L_PAREN ) {
      GetToken( token );
      
      if ( Expression( value, myStatementType, anyBuiltInFunc ) ) {
        PeekToken();
        if ( mPeekToken.type == R_PAREN ) {
          GetToken( token );
          
          if ( Statement( value, myStatementType ) ) {
            if ( isIf ) {
              PeekToken();
              if ( mPeekToken.type == ELSE ) {
                GetToken( token );
                if ( Statement( value, myStatementType ) ) {
                  return true;
                } // end if
                
                return false;
              } // end if
            } // if

            return true;
          } // end if
        } // end if
        else {
          mPeekToken.type = UNEXPECTED;
          throw mPeekToken;
          return false;
        } // end else
      } // end if
    } // end if
    else {
      mPeekToken.type = UNEXPECTED;
      throw mPeekToken;
    } // else

    return false;
  } // end GetRestOfStatement()

  bool Statement( string &value, IDType &myStatementType ) { // DONE.
    // ';' 
    // | expression ';'
    // | RETURN [ expression ] ';'
    // | compound_statement
    // | IF '(' expression ')' statement [ ELSE statement ]
    // | WHILE '(' expression ')' statement
    // | DO statement WHILE '(' expression ')' ';'

    Token token;
    VectorMyFunc anyBuiltInFunc;
    VectorToken tempBody = new vector<Token>();
    PeekToken();
    if ( mPeekToken.type == SEMICOLON ) {
      GetToken( token );
      return true;
    } // end if
    else if ( mPeekToken.type == RETURN ) {
      GetToken( token );
      
      if ( Expression( value, myStatementType, anyBuiltInFunc ) )
        ;
      
      PeekToken();
      if ( mPeekToken.type == SEMICOLON ) {
        GetToken( token );
        return true;
      } // end if
      else {
        mPeekToken.type = UNEXPECTED;
        throw mPeekToken;
      } // else
    } // end else if
    else if ( mPeekToken.type == L_BRACE ) {
      if ( CompoundStatement( value, myStatementType, tempBody ) ) 
        return true;
    } // else if
    else if ( mPeekToken.type == IF || mPeekToken.type == WHILE ) {
      GetToken( token );
      return GetRestOfStatement( value, myStatementType, anyBuiltInFunc, token.type == IF );
    } // end else if
    else if ( mPeekToken.type == DO ) {
      GetToken( token );
      
      if ( Statement( value, myStatementType ) ) {
        PeekToken();
        if ( mPeekToken.type == WHILE ) {
          GetToken( token );
          
          PeekToken();
          if ( mPeekToken.type == L_PAREN ) {
            GetToken( token );

            if ( Expression( value, myStatementType, anyBuiltInFunc ) ) {
              PeekToken();
              if ( mPeekToken.type == R_PAREN ) {
                GetToken( token );
                PeekToken();
                if ( mPeekToken.type == SEMICOLON ) {
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
      VectorMyFunc myFunctions;
      if ( Expression( value, myStatementType, myFunctions ) ) {
        
        PeekToken();
        if ( mPeekToken.type == SEMICOLON ) {
          GetToken( token );
          for ( int i = 0 ; i < myFunctions->size() ; i++ ) 
            Execute( myFunctions->at( i ).name, myFunctions->at( i ).type );
          
          return true;
        } // end if
      } // end if
      
    } // end else
    
    return false;
  } // end Statement()

  bool GetRestOfCin() {
    PeekToken();
    if ( mPeekToken.type == IDENTIFIER ) {
      Token token;
      GetToken( token );
      
      if ( ! ExistInIDTable( token.content ) ) {
        Token errorToken;
        CopyToken( errorToken, token );
        errorToken.type = UNDEFINED;
        throw errorToken;
      } // end if
      
      PeekToken();
      if ( mPeekToken.type == L_SQBR ) {
        GetToken( token );
        
        string mEValue;
        IDType mEType;
        VectorMyFunc mEHandler;
        if ( Expression( mEValue, mEType, mEHandler ) ) {
          PeekToken();
          if ( mPeekToken.type == R_SQBR ) {
            GetToken( token );
          } // end if
          else {
            return false;
          } // else
        } // end if
      } // end if
    } // end if
    else {
      return false;
    } // end else

    return true;
  } // end GetRestOfCin()

  bool Expression( string &value, IDType &myExpType, VectorMyFunc &vecForBuiltInFunc ) {
    // basic_expression { ',' basic_expression }
    vecForBuiltInFunc = new vector<MyFunc>();
    Token token;
    PeekToken();
    if ( mPeekToken.type == CIN ) {
      GetToken( token );
      PeekToken();
      if ( mPeekToken.type == RS ) {
        GetToken( token );
        if ( ! GetRestOfCin() )
          return false;
        
        PeekToken();
        while ( mPeekToken.type == RS ) {
          GetToken( token );
          if ( ! GetRestOfCin() )
            return false;

          PeekToken();
        } // end while

        return true;
      } // end if
    } // end if
    
    else if ( mPeekToken.type == COUT ) {
      GetToken( token );
      
      PeekToken();
      if ( mPeekToken.type == LS ) {
        GetToken( token );
  
        VectorMyFunc mEHandler;
        IDType myEType;
        if ( ! Expression( value, myEType, mEHandler ) ) {
          return false;
        } // end if
        
        PeekToken();
        while ( mPeekToken.type == LS ) {
          GetToken( token );
          VectorMyFunc mEHandler;
          IDType myEType;
          if ( ! Expression( value, myEType, mEHandler ) ) 
            return false;

          PeekToken();
        } // end while

        return true;
      } // end if
    } // end else if
  
    else {
      MyFunc newBuiltInFunc;
      IDType myEType;
      if ( BasicExpression( value, myEType, newBuiltInFunc ) ) {
        vecForBuiltInFunc->push_back( newBuiltInFunc );
        PeekToken();
        while ( mPeekToken.type == COMMA ) {
          Token token;
          GetToken( token );
          
          MyFunc mBE2Handler;
          IDType myBEType;
          if ( BasicExpression( value, myBEType, mBE2Handler ) ) {
            vecForBuiltInFunc->push_back( mBE2Handler );
          } // end if
          else {
            return false;
          } // end else

          PeekToken();
        } // end while

        return true;
      } // end if
      
    } // end else 
    
    return false;
    
  } // end Expression()

  void SetNewArgs( string name, VectorID newArgs, MyFunc &myFunc ) {
    if ( name == "Done" && newArgs->empty() ) {
      SetBuiltInFunc( myFunc, "", DONE );
    } // if
    else if ( name == "ListFunction" && newArgs->size() == 1 ) {
      SetBuiltInFunc( myFunc, newArgs->at( 0 ).content, LF );
    } // else if
    else if ( name == "ListVariable" && newArgs->size() == 1 ) {
      SetBuiltInFunc( myFunc, newArgs->at( 0 ).content, LV );
    } // else if
    else if ( name == "ListAllVariables" ) {
      SetBuiltInFunc( myFunc, "", LAV );
    } // else if
    else if ( name == "ListAllFunctions" ) {
      SetBuiltInFunc( myFunc, "", LAF );
    } // else if
  } // end SetNewArgs()

  bool BasicExpression( string &value, IDType &myType, MyFunc &returnHandler ) { // ex: ListVariavle()
    // Identifier rest_of_Identifier_started_basic_exp
    // ( PP | MM ) Identifier rest_of_PPMM_Identifier_started_basic_exp
    // sign { sign } signed_unary_exp romce_and_romloe
    // ( Constant | '(' expression ')' ) romce_and_romloe
    // Could be better

    Token token;
    PeekToken();
    if ( mPeekToken.type == L_PAREN || mPeekToken.type == CONSTANT ) {
      GetToken( token );
      if ( token.type == L_PAREN ) {
        string mEValue;
        IDType mEType;
        VectorMyFunc mEHandler;
        if ( Expression( mEValue, mEType, mEHandler ) ) {
          PeekToken();
          if ( mPeekToken.type == R_PAREN ) {
            Token token2;
            GetToken( token2 );
          } // end if
          else
            return false;
        } // end if
        else
          return false;
      } // if

      value = token.content;
      string mRARValue;
      IDType mRARType;
      if ( RomceAndRomloe( mRARValue, mRARType ) ) {
        return true;
      } // end if
    } // if
    else if ( mPeekToken.type == IDENTIFIER ) {
      GetToken( token );

      if ( ! ExistInIDTable( token.content ) && ! ExistInFuncTable( token.content ) ) {
        Token errorToken;
        CopyToken( errorToken, token );
        errorToken.type = UNDEFINED;
        throw errorToken;
      } // end if 
    

      VectorID newArgs = new vector<ID>;
      if ( RestOfIdentifierStartedBasicExp( value, myType, newArgs ) ) {
        if ( ( myType == TYPE_INT && ! ExistInIDTable( token.content ) ) 
             || ( myType == TYPE_VOID && ! ExistInFuncTable( token.content ) ) ) {
          Token errorToken;
          CopyToken( errorToken, token );
          errorToken.type = UNDEFINED;
          throw errorToken;
        } // end if

        if ( mLevel == 0 && myType == TYPE_VOID ) 
          SetNewArgs( token.content, newArgs, returnHandler );

        return true;
      } // end if
    } // end else if
    else if ( mPeekToken.type == PP || mPeekToken.type == MM ) {
      GetToken( token );
      
      PeekToken();
      if ( mPeekToken.type == IDENTIFIER ) {
        Token idToken;
        GetToken( idToken );
        if ( ! ExistInIDTable( idToken.content ) && ! ExistInFuncTable( idToken.content ) ) {
          Token errorToken;
          CopyToken( errorToken, idToken );
          errorToken.type = UNDEFINED;
          throw errorToken;
        } // end if
        
        if ( RestOfPPMMIdentifierStartedBasicExp( value, myType ) ) {
          if ( ! ExistInIDTable( idToken.content ) ) {
            Token errorToken;
            CopyToken( errorToken, idToken );
            errorToken.type = UNDEFINED;
            throw errorToken;
          } // end if
          
          return true;
        } // end if
      } // end if
    } // end else if
    else {
      string sValue;
      IDType sType;
      if ( Sign( sValue, sType ) ) {
        while ( Sign( sValue, sType ) ) {
          ; 
        } // end while
        
        if ( SignedUnaryExp( sValue, sType ) ) {
          if ( RomceAndRomloe( sValue, sType ) ) {
            return true;
          } // end if
        } // end if
      } // end if
    } // end else
    
    return false;
  } // end BasicExpression()

  bool RestOfIdentifierStartedBasicExp( string &value, IDType &returnType, VectorID &args ) {
    // [ '[' expression ']' ]
    // ( assignment_operator basic_expression | [ PP | MM ] romce_and_romloe )
    // '(' [ actual_parameter_list ] ')' romce_and_romloe

    PeekToken();
    Token token;

    if ( mPeekToken.type == L_SQBR ) { // [
      GetToken( token );
      
      string mEValue;
      IDType mEType;
      VectorMyFunc mEHandler;
      if ( Expression( mEValue, mEType, mEHandler ) ) {
        PeekToken();
        if ( mPeekToken.type == R_SQBR ) {
          Token token2;
          GetToken( token2 );
        } // end if
        else {
          return false;
        } // end else
      } // end if
      else {
        return false;
      } // end else
    } // if

    else if ( mPeekToken.type == L_PAREN ) { // (
      GetToken( token );
      
      VectorID newArgs = new vector<ID>;
      if ( ActualParameterList( newArgs ) ) 
        args = newArgs;    
      
      PeekToken();
      if ( mPeekToken.type == R_PAREN ) {
        GetToken( token );
        returnType = TYPE_VOID;
        IDType rType;
        return RomceAndRomloe( value, rType );
      } // end if
      
      return false;
    } // end else if

    if ( mPeekToken.type == PP || mPeekToken.type == MM ) {
      GetToken( token );
      
      string rValue;
      IDType rrType;
      if ( RomceAndRomloe( rValue, rrType ) ) {
        returnType = TYPE_INT;
        return true;
      } // end if

    } // end if
    
    else {
      string vvvalue;
      IDType tttType;
      MyFunc mfff;
      
      PeekToken();
      if ( IsAssignOpFamily( mPeekToken.type ) ) {
        if ( AssignmentOperator( vvvalue, tttType ) ) {
          if ( BasicExpression( vvvalue, tttType, mfff ) ) {
            returnType = TYPE_INT;
            return true;
          } // end if
        } // end if
      } // end if

      else if ( RomceAndRomloe( vvvalue, tttType ) ) {
        returnType = TYPE_INT;
        return true;
      } // end else if
    } // end else
    
    return false;
  } // end RestOfIdentifierStartedBasicExp()

  bool RestOfPPMMIdentifierStartedBasicExp( string &value, IDType &myType ) {
    // [ '[' expression ']' ] romce_and_romloe

    PeekToken();
    if ( mPeekToken.type == L_SQBR ) {
      Token token;
      GetToken( token );
      
      string expV;
      IDType expT;
      VectorMyFunc moreF;
      if ( Expression( expV, expT, moreF ) ) {
        PeekToken();
        if ( mPeekToken.type == R_SQBR ) 
          GetToken( token );
        
        else 
          return false;
      } // end if
      
      else 
        return false;
    } // end if
    
    return RomceAndRomloe( value, myType ) ;
  } // end RestOfPPMMIdentifierStartedBasicExp()

  bool Sign( string &value, IDType &returnType ) {
    // '+' | '-' | '!'
    PeekToken();
    Token token;
    if ( mPeekToken.type == PLS || mPeekToken.type == MNS || mPeekToken.type == NOT ) {
      GetToken( token ); 
      return true;
    } // end if
    
    return false;
  } // end Sign()

  bool ActualParameterList( VectorID &args ) {
    // basic_expression { ',' basic_expression }

    MyFunc bF;
    ID newArg;
    if ( BasicExpression( newArg.content, newArg.type, bF ) ) {
      args->push_back( newArg );
      
      PeekToken();
      while ( mPeekToken.type == COMMA ) {
        Token token;
        GetToken( token );
        ID moreArg;
        MyFunc nbF;
        if ( BasicExpression( moreArg.content, moreArg.type, nbF ) ) 
          args->push_back( moreArg );

        else 
          return false;

        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end ActualParameterList()

  bool AssignmentOperator( string &v, IDType &t ) {
    // '=' | TE | DE | RE | PE | ME

    PeekToken();
    if ( IsAssignOpFamily( mPeekToken.type ) ) {
      Token token;
      GetToken( token ); 
      return true;
    } // end if
    
    return false;
  } // end AssignmentOperator()

  bool RomceAndRomloe( string &value, IDType &returnType ) {
    // rest_of_maybe_logical_OR_exp [ '?' basic_expression ':' basic_expression ]

    string mROMLOEValue;
    IDType mROMLOEType;
    if ( RestOfMaybeLogicalOrExp( mROMLOEValue, mROMLOEType ) ) {
      PeekToken();
      if ( mPeekToken.type == QUESTION ) { // ?
        Token token;
        GetToken( token );
        
        string bV;
        IDType bT;
        MyFunc bF;
        if ( BasicExpression( bV, bT, bF ) ) {
          PeekToken();
          if ( mPeekToken.type == COLON ) { // :
            GetToken( token );
            return BasicExpression( bV, bT, bF );
          } // end if
        } // end if
        
        return false;
      } // end if
      
      return true;
    } // end if
    
    return false;
    
  } // end RomceAndRomloe()

  bool RestOfMaybeLogicalOrExp( string vt, IDType t ) {
    // rest_of_maybe_logical_AND_exp { OR maybe_logical_AND_exp }
    // cout << "RestOfMaybeLogicalOrExp" << endl;
    string vvalue;
    IDType ttype;
    if ( RestOfMaybeLogicalAndExp( vvalue, ttype ) ) {
      PeekToken();
      while ( mPeekToken.type == OR ) {
        Token token;
        GetToken( token );
        
        string vvvalue;
        IDType tttype;
        if ( ! MaybeLogicalAndExp( vvvalue, tttype ) ) 
          return false;
             
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeLogicalOrExp()

  bool MaybeLogicalAndExp( string v, IDType t ) {
    // maybe_bit_OR_exp { AND maybe_bit_OR_exp }
    // cout << "MaybeLogicalAndExp" << endl;
    string mV;
    IDType mT;
    if ( MaybeBitOrExp( mV, mT ) ) {
      PeekToken();
      while ( mPeekToken.type == AND ) {
        
        Token token;
        GetToken( token );
        
        string vv;
        IDType tt;
        if ( ! MaybeBitOrExp( vv, tt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeLogicalAndExp()

  bool RestOfMaybeLogicalAndExp( string v, IDType t ) {
    // rest_of_maybe_bit_OR_exp { AND maybe_bit_OR_exp }
    // cout << "RestOfMaybeLogicalAndExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeBitOrExp( vv, tt ) ) {
      PeekToken();
      while ( mPeekToken.type == AND ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( !MaybeBitOrExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeLogicalAndExp()

  bool MaybeBitOrExp( string v, IDType t ) {
    // maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
    // cout << "MaybeBitOrExp" << endl;
    string vv;
    IDType tt;
    if ( MaybeBitExOrExp( vv, tt ) ) {
      PeekToken();
      while ( mPeekToken.type == ARI_OR ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( !MaybeBitExOrExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
  } // end MaybeBitOrExp()

  bool RestOfMaybeBitOrExp( string v, IDType t ) {
    // rest_of_maybe_bit_ex_OR_exp { '|' maybe_bit_ex_OR_exp }
    // cout << "RestOfMaybeBitOrExp" << endl;
    string v2;
    IDType t2;
    if ( RestOfMaybeBitExOrExp( v2, t2 ) ) {
      PeekToken();
      while ( mPeekToken.type == ARI_OR ) {
        
        Token token;
        GetToken( token );
        
        string v3;
        IDType t3;
        if ( !MaybeBitExOrExp( v3, t3 ) ) 
          return false;

        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeBitOrExp()

  bool MaybeBitExOrExp( string myV, IDType myT ) {
    // maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
    // cout << "MaybeBitExOrExp" << endl;
    string secV;
    IDType secT;
    if ( MaybeBitAndExp( secV, secT ) ) {
      PeekToken();
      while ( mPeekToken.type == PWR ) {
        Token token;
        GetToken( token );
        
        string thirdV;
        IDType thirdT;
        if ( MaybeBitAndExp( thirdV, thirdT ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
  } // end MaybeBitExOrExp()

  bool RestOfMaybeBitExOrExp( string v, IDType t ) {
    // rest_of_maybe_bit_AND_exp { '^' maybe_bit_AND_exp }
    // cout << "RestOfMaybeBitExOrExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeBitAndExp( vv, tt ) ) {
      PeekToken();
      while ( mPeekToken.type == PWR ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( !MaybeBitAndExp( vvv, ttt ) ) 
          return false;

        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeBitExOrExp()

  bool MaybeBitAndExp( string v, IDType t ) {
    // maybe_equality_exp { '&' maybe_equality_exp }
    // cout << "MaybeBitAndExp" << endl;
    string vv;
    IDType ttType;
    if ( MaybeEqualityExp( vv, ttType ) ) {
      PeekToken();
      while ( mPeekToken.type == ARI_AND ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( ! MaybeEqualityExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeBitAndExp()

  bool RestOfMaybeBitAndExp( string v, IDType t ) {
    // rest_of_maybe_bit_AND_exp 
    // cout << "RestOfMaybeBitAndExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeEqualityExp( vv, tt ) ) {
      PeekToken();
      while ( mPeekToken.type == ARI_AND ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( ! MaybeEqualityExp( vvv, ttt ) ) 
          return false;

        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
  } // end RestOfMaybeBitAndExp()

  bool MaybeEqualityExp( string v, IDType t ) {
    // maybe_relational_exp { '=' maybe_relational_exp }
    // cout << "MaybeEqualityExp" << endl;
    string vv;
    IDType tt;
    if ( MaybeRelationalExp( vv, tt ) ) {
      PeekToken();
      while ( mPeekToken.type == EQU || mPeekToken.type == NEQ ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( ! MaybeRelationalExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeEqualityExp()

  bool RestOfMaybeEqualityExp( string v, IDType t ) {
    // rest_of_maybe_equality_exp { '=' maybe_relational_exp }
    // cout << "RestOfMaybeEqualityExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeRelationalExp( vv, tt ) ) {
      PeekToken();
      while ( mPeekToken.type == EQU || mPeekToken.type == NEQ ) {
        Token token;
        GetToken( token );
        string vvv;
        IDType ttt;
        if ( ! MaybeRelationalExp( vvv, ttt ) ) 
          return false;
      
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeEqualityExp()

  bool ComparisonOp( TokenType t ) {
    if ( t == L || t == G || t == LT || t == GT )
      return true;

    return false;
  } // end ComparisonOp()

  bool MaybeRelationalExp( string v, IDType t ) {
    // maybe_additive_exp { '<' maybe_additive_exp }
    // cout << "MaybeRelationalExp" << endl;
    string vv;
    IDType tt;
    if ( MaybeShiftExp( vv, tt ) ) {
      PeekToken();
      while ( ComparisonOp( mPeekToken.type ) ) { // <, >, <=, >=
        Token token;
        GetToken( token );
        string vvv;
        IDType ttt;
        if ( !MaybeShiftExp( vvv, ttt ) ) 
          return false;

        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end MaybeRelationalExp()

  bool RestOfMaybeRelationalExp( string v, IDType t ) {
    // rest_of_maybe_relational_exp { '<' maybe_additive_exp }
    // cout << "RestOfMaybeRelationalExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeShiftExp( vv, tt ) ) { 
      PeekToken();
      while ( ComparisonOp( mPeekToken.type ) ) { // <, >, <=, >=
        
        Token token;
        GetToken( token );
        string vvv;
        IDType ttt;
        if ( ! MaybeShiftExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;
    
  } // end RestOfMaybeRelationalExp()

  bool CINCOUTop( TokenType t ) {
    if ( t == LS || t == RS )
      return true;
    
    return false;
  } // end CINCOUTop()

  bool MaybeShiftExp( string &value, IDType &returnType ) {
    // maybe_additive_exp { '<<' maybe_additive_exp }
    // cout << "MaybeShiftExp" << endl;
    string vv;
    IDType tt;
    if ( MaybeAdditiveExp( vv, tt ) ) {
      PeekToken();
      while ( CINCOUTop( mPeekToken.type ) ) { // <<, >>
        Token token;
        GetToken( token );

        string vvv;
        IDType ttt;
        if ( ! MaybeAdditiveExp( vvv, ttt ) ) 
          return false;

        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;  
  } // end MaybeShiftExp()

  bool RestOfMaybeShiftExp( string v, IDType t ) {
    // rest_of_maybe_shift_exp { '<<' maybe_additive_exp }
    // cout << "RestOfMaybeShiftExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeAdditiveExp( vv, tt ) ) {
      PeekToken();
      while ( CINCOUTop( mPeekToken.type ) ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( ! MaybeAdditiveExp( vvv, ttt ) ) 
          return false;
      
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;  
  } // end RestOfMaybeShiftExp()

  bool PLUSorMINUS( TokenType t ) {
    if ( t == PLS || t == MNS )
      return true;
    
    return false;
  } // end PLUSorMINUS()

  bool MaybeAdditiveExp( string v, IDType t ) {
    // maybe_multiplicative_exp { '+' maybe_multiplicative_exp }
    // cout << "MaybeAdditiveExp" << endl;
    string vv;
    IDType tt;
    if ( MaybeMultExp( vv, tt ) ) {
      PeekToken();
      while ( PLUSorMINUS( mPeekToken.type ) ) {
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( !MaybeMultExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;  
  } // end MaybeAdditiveExp()

  bool RestOfMaybeAdditiveExp( string v, IDType t ) {
    // rest_of_maybe_additive_exp { '+' maybe_multiplicative_exp }
    // cout << "RestOfMaybeAdditiveExp" << endl;
    string vv;
    IDType tt;
    if ( RestOfMaybeMultExp( vv, tt ) ) {
      PeekToken();
      while ( PLUSorMINUS( mPeekToken.type ) ) {     
        Token token;
        GetToken( token );
        
        string vvv;
        IDType ttt;
        if ( ! MaybeMultExp( vvv, ttt ) ) 
          return false;
        
        PeekToken();
      } // end while

      return true;
    } // end if
    
    return false;  
  } // end RestOfMaybeAdditiveExp()

  bool MaybeMultExp( string v, IDType t ) {
    string vv;
    IDType tt;
    if ( UnaryExp( vv, tt ) ) {
      string vvv;
      IDType ttt;
      if ( RestOfMaybeMultExp( vvv, ttt ) ) 
        return true;

    } // end if
    
    return false;
  } // end MaybeMultExp()

  bool MDMop( TokenType t ) {
    if ( t == MUL || t == DIV || t == MOD )
      return true;
    
    return false;
  } // end MDMop()

  bool RestOfMaybeMultExp( string v, IDType t ) {
    // rest_of_maybe_multiplicative_exp { '*' maybe_multiplicative_exp }
    // cout << "RestOfMaybeMultExp" << endl;
    PeekToken();
    while ( MDMop( mPeekToken.type ) ) {
      Token token;
      GetToken( token );
      
      string vv;
      IDType tt;
      if ( !UnaryExp( vv, tt ) ) 
        return false;
      
      PeekToken();
    } // end while

    return true;
  } // end RestOfMaybeMultExp()

  bool UnaryExp( string &value, IDType &returnType ) {
    // sign { sign } signed_unary_exp
    // | unsigned_unary_exp
    // ( PP | MM ) Identifier [ '[' expression ']' ]

    // cout << "UnaryExp" << endl;
    string v;
    IDType t;
    PeekToken();
    // cout << mPeekToken.content << " " << mSC.TokenTypeStr( mPeekToken.type ) << endl;
    if ( mPeekToken.type == PP || mPeekToken.type == MM ) {
      Token idToken;
      GetToken( idToken );

      PeekToken();
      if ( mPeekToken.type == IDENTIFIER ) {
        GetToken( idToken );
        if ( ! ExistInFuncTable( idToken.content ) && ! ExistInIDTable( idToken.content ) ) {
          Token errorToken;
          CopyToken( errorToken, idToken );
          errorToken.type = UNDEFINED;
          throw errorToken;
        } // end if

        PeekToken();
        if ( mPeekToken.type == L_SQBR ) {
          Token temp;
          GetToken( temp );
          
          string ev;
          IDType eT;
          VectorMyFunc eF;
          if ( Expression( ev, eT, eF ) ) {
            PeekToken();
            if ( mPeekToken.type == R_SQBR ) {
              GetToken( temp );
              
              if ( ! ExistInIDTable( idToken.content ) ) {
                Token errorToken;
                CopyToken( errorToken, idToken );
                errorToken.type = UNDEFINED;
                throw errorToken;
              } // end if
              
              return true;
            } // end if
          } // end if
          
          return false;
        } // end if
        
        return true;
      } // end if
    } // end if
    else if ( mPeekToken.type == PLS || mPeekToken.type == MNS || mPeekToken.type == NOT ) {
      string sv;
      IDType st;
      if ( Sign( sv, st ) ) {
        while ( Sign( sv, st ) ) 
          ;
        
        string suv;
        IDType sut;
        if ( SignedUnaryExp( suv, sut ) ) 
          return true;

      } // end if

    } // else if
    else if ( UnsignedUnaryExp( v, t ) ) {
      return true;
    } // end else if
    
    return false; 
  } // end UnaryExp()

  bool SignedUnaryExp( string &value, IDType t ) {
    // '+' unsigned_unary_exp
    // | '-' unsigned_unary_exp
    // | '!' unsigned_unary_exp
    // cout << "SignedUnaryExp" << endl;

    PeekToken();
    Token temp;

    if ( mPeekToken.type == CONSTANT ) {
      Token token;
      GetToken( token );
      value = token.content;
      return true;
    } // end if

    else if ( mPeekToken.type == IDENTIFIER ) {
      Token idToken;
      GetToken( idToken );
      
      if ( ! ExistInFuncTable( idToken.content ) && ! ExistInIDTable( idToken.content ) ) {
        Token errorToken;
        CopyToken( errorToken, idToken );
        errorToken.type = UNDEFINED;
        throw errorToken;
      } // end if
          
      PeekToken();
      if ( mPeekToken.type == L_PAREN ) {
        GetToken( temp );
        
        VectorID getArg = new vector<ID>;
        ActualParameterList( getArg );
        
        PeekToken();
        if ( mPeekToken.type == R_PAREN ) {
          Token rToken;
          GetToken( rToken );
          
          if ( ! ExistInFuncTable( idToken.content ) ) {
            Token errorToken;
            CopyToken( errorToken, idToken );
            errorToken.type = UNDEFINED;
            throw errorToken;
          } // end if
          else if ( idToken.content == "Done" && getArg->empty() ) {
            throw "Our-C exited ...";
          } // end if
          
          return true;
        } // end if
        
        return false;
      } // end if
      
      else if ( mPeekToken.type == L_SQBR ) {
        GetToken( temp );
        
        string meV;
        IDType meT;
        VectorMyFunc mEF;
        if ( Expression( meV, meT, mEF ) ) {
          PeekToken();
          if ( mPeekToken.type == R_SQBR ) {
            GetToken( temp );
            
            if ( ! ExistInIDTable( idToken.content ) ) {
              Token errorToken;
              CopyToken( errorToken, idToken );
              errorToken.type = UNDEFINED;
              throw errorToken;
            } // end if
            
            return true;
          } // end if
        } // end if
        
        return false;
      } // end else if
    
      if ( ! ExistInIDTable( idToken.content ) ) {
        Token errorToken;
        CopyToken( errorToken, idToken );
        errorToken.type = UNDEFINED;
        throw errorToken;
      } // end if
      
      return true;
    } // end if

    else if ( mPeekToken.type == L_PAREN ) {
      GetToken( temp );
      
      string evv;
      IDType ett;
      VectorMyFunc biF;
      if ( Expression( evv, ett, biF ) ) {
        
        PeekToken();
        if ( mPeekToken.type == R_PAREN ) {
          GetToken( temp );
          return true;
        } // end if
      } // end if
    } // end else if
    
    
    
    return false;
  } // end SignedUnaryExp()

  bool UnsignedUnaryExp( string &value, IDType t ) {
    // cout << "UnsignedUnaryExp" << endl;
    PeekToken();
    Token temp;
    if ( mPeekToken.type == IDENTIFIER ) {
      Token idToken;
      GetToken( idToken );

      if ( ! ExistInFuncTable( idToken.content ) && ! ExistInIDTable( idToken.content ) ) {
        Token errorToken;
        CopyToken( errorToken, idToken );
        errorToken.type = UNDEFINED;
        throw errorToken;
      } // end if
          
      PeekToken();
      if ( mPeekToken.type == L_PAREN ) {
        Token token2;
        GetToken( token2 );
        
        VectorID alist = new vector<ID>;
        ActualParameterList( alist );
        
        
        PeekToken();
        if ( mPeekToken.type == R_PAREN ) { // )
          GetToken( temp );
          
          if ( ! ExistInFuncTable( idToken.content ) ) {
            Token errorToken;
            CopyToken( errorToken, idToken );
            errorToken.type = UNDEFINED;
            throw errorToken;
          } // end if
          
          if ( idToken.content == "Done" && alist->empty() ) {
            throw "Our-C exited ...";
          } // end if
            
          return true;
        } // end if
        
        return false;
      } // end if
      
      else if ( mPeekToken.type == L_SQBR ) {
        GetToken( temp );
        
        string epv;
        IDType ept;
        VectorMyFunc eFunc;
        if ( Expression( epv, ept, eFunc ) ) {
          PeekToken();
          if ( mPeekToken.type == R_SQBR ) {
            GetToken( temp );
            
            PeekToken();
            if ( mPeekToken.type == PP || mPeekToken.type == MM ) 
              GetToken( temp );
            
            if ( ! ExistInIDTable( idToken.content ) ) {
              Token errorToken;
              CopyToken( errorToken, idToken );
              errorToken.type = UNDEFINED;
              throw errorToken;
            } // end if

            return true;
          } // end if
        } // end if
        
        return false;
      } // end else if
      
      else if ( mPeekToken.type == PP || mPeekToken.type == MM ) {
        GetToken( temp );
      } // end else if

      if ( ! ExistInIDTable( idToken.content ) ) {
        Token errorToken;
        CopyToken( errorToken, idToken );
        errorToken.type = UNDEFINED;
        throw errorToken;
      } // end if

      return true;
    } // end if
    
    else if ( mPeekToken.type == CONSTANT ) {
      GetToken( temp );
      value = temp.content;
      return true;
    } // end else if
    
    else if ( mPeekToken.type == L_PAREN ) {
      GetToken( temp );
      
      string eVV;
      IDType eTy;
      VectorMyFunc funcs;
      if ( Expression( eVV, eTy, funcs ) ) {
        PeekToken();
        if ( mPeekToken.type == R_PAREN ) {
          GetToken( temp );
          return true;
        } // end if
      } // end if
    } // end else if
    
    return false;
  } // end UnsignedUnaryExp()

}; // Parser

class OurC{
  public:
  bool mcorrect;
  string mvalue;
  bool mquit;
  IDType mreturnType;
  Parser mpr;

  void InitTables() {
    gIdTable["cin"];
    gIdTable["cout"];
    
    gFuncTable["Done"];
    gFuncTable["ListAllFunctions"];
    gFuncTable["ListAllVariables"];
    gFuncTable["ListFunction"];
    gFuncTable["ListVariable"];
    mvalue = "";
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
          mpr.UserInput( mvalue, mquit, mreturnType );
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
