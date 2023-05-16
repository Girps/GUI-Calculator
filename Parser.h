#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stdexcept>
#include <stack>
#include "Tokenizer.h"
#include <cmath>


class Parser
{
	std::stack<Token> Tokens;
	double result; // hold result of the expression 
	Token getToken();
	void  ungetToken(Token t);

	void syntax_Analysis();
	double parse_Expression();
	double parse_Term();
	double parse_Factor();
	void check_EOF();
	void syntax_Error();
	double parse_Expression2(double arg);
	double parse_Term2(double arg);
	double parse_Primary(); 
	double parse_Primary2(double arg); 

	

	public:
	
		Parser(const  std::stack<Token> &argStack);
		double getResult() ; 
		
}; 


#endif PARSER_H
