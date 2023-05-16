#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <stack>
#include <vector>
#include<stdexcept>
#include <sstream> 
#include <regex>

#define DOUBLE_EX "([0-9]\.[0-9]+)|([1-9]+\.[0-9]+)"	// For double representation 
#define INT_EXP		"([0-9]|[1-9]+)"					// Integer representation 
#define PLUS_EX	"+"
#define	MINUS_EX "-"
#define MULT_EX "*"
#define DIV_EX "/"
#define LPAREN_EXP "("
#define RPAREN_EXP ")"

// Hold the type determining what are token is 
enum Types
{
	 DOUBLE, DIVSOR,PLUS, MINUS, DIVIDE, MULIIPLY, LEFTPAREN, RIGHTPAREN, EXPONENT, ENDOFFILE
};

/*
	Token struct will hold information about the token on whether it is a value
	or an operator in the grammar
*/
struct Token
{
	// Token holding data of the token 
	Types kind;
	double value;

	Token (Types t, double v_Arg);
};

/*
	Tokenizer class will receive a data structure of unparsed string and tokenize each string and
	check for any token errors  
*/

class Tokenizer
{

	std::vector<Token> Tokens_List;
	std::stack<Token>  Tokens_Stack;
	std::string raw_String;

	
	/*
		Private function will tokenize a series of bytes and add them to the vector and on the stack 
	*/
	void Lexical_Analysis(); 
	void num_Tokenizer(std::string::iterator &it);
	void reOrderStack(); 
	public:

	Tokenizer(std::string str_List);


		// Return of a vector of tokens 
		std::vector<Token>  getVector() ; 
		
		// Return a stack of tokens 
		std::stack<Token> getStack() ; 
}; 





#endif TOKENIZER_H