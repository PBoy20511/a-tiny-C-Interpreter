# OurC-Interpreter
OurC is a simplified but slightly extended C language. It has five primitive data types (int, float, char, bool, and string), one-dimensional array, and no struct or enum.  There are function calls, compound statements, conditional constructs (if-then-else) and loop constructs (while-loop and do-while loop).


Here is how a simple session with OurC looks like :
// Suppose we ran an OurC executable on the command level ...

 Our-C running ... // this is our output
  
  > int x; // this is our input
           
  Definition of x entered ...  
  
  > x=10;
  
  Statement executed ...
  
  > cout << x;
  
  10Statement executed ...
  
  > cout <<
  
  x
  
  << "\n"
  
  ;
  
  10              
  
  Statement executed ...
  
  > void AddThree(int)
  
  Line 1 : unexpected token : ')'  

  > {y = y + 3; }
  
  Line 1 : undefined identifier : 'y'
  
  > void AddThree(int& y)
  
  {y = y + 3;} // AddThree()  
  
  Definition of AddThree entered ...
  
  > AddThree(x);
  
  Statement executed ...
  
  > cout << x;
  
  13Statement executed ...                 
  
  > ListAllVariables();
  
  x        
  
  Statement executed ...
  
  > ListAllFunctions();
  
  AddThree()     
  
  Statement executed ...
  
  > ListVariable("x");
  
  int x ;      
  
  Statement executed ...
  
  > ListFunction("AddThree");
  
  void AddThree( int & y ) {
  
   y = y + 3 ;
  
  }
  
  Statement executed ...
  
  > Done();
  
  Our-C exited ...
  
  ================================================
  
  The OurC interpreter maintains an environment.  This environment is composed of zero or more "definitions".  A definition can be either the definition of a variable or the definition of a function.  The user enters the definitions directly.

Apart from definitions, the user can also enter one C-statement at a time on the prompt level.  There are several "extra" system-supported functions, as listed below.

  ListAllVariables();          // just the names of the (global) variables,  sorted (from smallest to greatest)
  
  ListAllFunctions();          // just the names of the (user-defined)  functions, sorted
  
  ListVariable(char name[]);   // the definition of a particular variable
  
  ListFunction(char name[]);   // the definition of a particular function
  
  Done();                      // exit the interpreter
  
  cout << ...                  // output from program
  
  cin >> ...                   // input into program

A global variable may have a value, and the system can simply store this value "together with" the definition of the variable.  With a skillful arrangement, there can be no need for a separate call stack.  However, you will need a data structure that is capable of storing arbitrary types of data.

  Project 2 : implement OurC as a syntax checker and pretty printer, with the above-mentioned system supported 
                    functions (except cin and cout)
                    
  Project 3 : implement OurC (the interpreter) without function calls, but with conditionals, loops and arrays. (include cin and cout)

