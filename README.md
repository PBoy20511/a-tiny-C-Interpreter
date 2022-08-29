# OurC-Interpreter
OurC is a simplified but slightly extended C language. It has five primitive data types (int, float, char, bool, and string), one-dimensional array, and no struct or enum.  There are function calls, compound statements, conditional constructs (if-then-else) and loop constructs (while-loop and do-while loop).


Here is how a simple session with OurC looks like :
// Suppose we ran an OurC executable on the command level ...

 Our-C running ... 
  
  > int x;
           
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
