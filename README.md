# GUI-Calculator
Implemented a calculator using the QT framework 

Calculator application evaluates arthmetic expression using PEMDAS rules. 
The application evaluates expressions through recursive function calls corresponding
to the following grammar rules. 

math -> exp @
exp -> term exp2 @

exp2 -> PLUS term exp2 @
exp2 -> MINUS term exp2 @
exp2 -> EPSILON @

term -> primary term2 @
term2 -> MULT primary term2 @
term2 -> DIV primary  term2 @
term2 -> LEFTPAREN exp RIGHTPAREN primary2 term2 @
term2 -> EPSILON @ 

primary -> factor primary2 @
primary2 -> EXPONENT factor primary2 @
primary2 -> EPSILON @  

factor -> NUMBER @
factor -> LEFTPAREN exp RIGHTPAREN @
factor -> MINUS LEFTPAREN exp RIGHTPAREN primary2 @
factor -> MINUS primary @ 

#
PLUS
MINUS
EPSILON
MULT
DIV
NUMBER
LEFTPAREN
RIGHTPAREN
EXPONENT

The given grammmar is a predictive recursive descent parser were a function 
called to implement each rule is determined by the grammars first and follow
sets. Expressions are considered valid if it can be generated with the grammar 
otherwise an exception is thrown. This grammar is implemented through the Parser.cpp
file.

Each character is evaluated to match a potenetial token in the Tokenizer.cpp file. 
Strings made up of these characters are tokenized with regular expressions and add-
ed to the stack otherwise an exeception is thrown. When the expressions has been 
analyzied by the lexer a stack is tokens is created and used to pass on the Parser
obect for syntax anaylsis. 