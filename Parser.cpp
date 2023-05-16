#include "Parser.h"




/*
	Parse constructor passes argStack to initalize memeber stack
*/
Parser::Parser(const std::stack<Token> &argStack)
	:Tokens{ argStack }, result{0}
{
	// push last token to end of the stack 
	syntax_Analysis(); 
}


/*
	Returns the result of the calculation 
*/
double Parser::getResult()  
{
	return this->result; 
}

/*
	Void function parses the tokens on the stack and checks if 
	it is a valid parsing tree 
*/
void Parser::syntax_Analysis()

{
	
	// starts here 
	result = parse_Expression();	// start the expression 
	// check end of file 
	check_EOF(); 
}

/*
	Void function parses each token asscoiated with rule Expression 
		
	exp -> term exp2 

*/
double Parser::parse_Expression()
{
	Token t = getToken();
	double left = 0.0; 
	if (t.kind == DOUBLE || t.kind == LEFTPAREN || t.kind == MINUS) 
	{
		ungetToken(t);
		left = parse_Term(); // always returns a number 
		left = parse_Expression2(left); // pass the number 
		return left; 
	}
	else 
	{
		syntax_Error(); 
	}

}

/*
	exp2 -> PLUS term exp2 
	exp2 -> MINUS term exp2 
	exp2 -> EPSION 
*/
double Parser::parse_Expression2(double arg)
{
	Token t = getToken(); 
	if (t.kind == PLUS) 
	{
		// Consume + 
		arg += parse_Term(); 
		arg = parse_Expression2(arg); 
		return arg; 
	}
	else if (t.kind == MINUS)
	{
		// Consume - 
		arg -= parse_Term();
		arg = parse_Expression2(arg);
		return arg; 
	}
	else if (t.kind == ENDOFFILE || t.kind == RIGHTPAREN)  // epsilion 
	{
		ungetToken(t);
		return arg; 
	}
	else 
	{
		syntax_Error(); 
	}
}



/*
	Returns a double while consumes tokens from the stack 
	calls corresponding rules

	
	term -> primary term2  
*/
double Parser::parse_Term() 
{
	double left = 0; 
	Token t = getToken(); 
	if (t.kind == DOUBLE || t.kind == LEFTPAREN || t.kind == MINUS) 
	{
		ungetToken(t);
		left = parse_Primary(); 
		left = parse_Term2(left); // pass the primary for evaluation? 
		return left; 
	}
	else 
	{
		syntax_Error(); 
	}
}


/*
	term2 -> MULT primary term2 
	term2 -> DIV primary term2
	term2 -> ( exp ) primary2 term2 
	term2 -> EPSILON 
	
*/
double Parser::parse_Term2(double arg) 
{
	Token t = getToken();
	if (t.kind == MULIIPLY) 
	{
		// consumed * 
		arg *= parse_Primary();
		arg = parse_Term2(arg);
		return arg; 
	}
	else if (t.kind == DIVIDE) 
	{
		// consumed /
		double res  = parse_Primary();
		if (res == 0) 
		{
			throw std::runtime_error("ERROR: DIVIDE BY 0");
		}
		arg /= res; 
		arg = parse_Term2(arg);
		return arg;
		
	}
	else if (t.kind == LEFTPAREN) 
	{
		double mult = arg; 
		// consumed ( 
		arg = parse_Expression();
		// Consume ) 
		t = getToken();
		if (t.kind != RIGHTPAREN) 
		{
			syntax_Error(); 
		}
		
		arg = mult * parse_Primary2(arg) ;
		arg = parse_Term2(arg);
		return arg;
	}
	else if (t.kind == ENDOFFILE || t.kind == MINUS ||
		t.kind == PLUS || t.kind == RIGHTPAREN) 
	{
		ungetToken(t);
		return arg; 
	}
	else 
	{
		syntax_Error(); 
	}
	
}


/*
	primary -> factor primary2 
*/
double Parser::parse_Primary() 
{
	Token t = getToken();
	double left = 0.0; 
	if (t.kind == LEFTPAREN || t.kind == DOUBLE || t.kind == MINUS) 
	{
		ungetToken(t);
		left = parse_Factor(); 
		left = parse_Primary2(left); // pass arg for exponent evaluation
		return left; 
	}
	else 
	{
		syntax_Error(); 
	}
}

/*
	primary2 -> EXPONENT factor primary2
	primary2 -> EPSILON 
*/
double Parser::parse_Primary2(double arg) 
{
	Token t = getToken(); 
	double exp = 0.0;
	if (t.kind == EXPONENT) 
	{
		// consume EXPONENT
		exp = parse_Factor();
		exp = parse_Primary2(exp); 
		// evluate the exponent 
		exp = std::pow(arg,exp); 
			return exp; 
	}
	else if (t.kind == ENDOFFILE || t.kind == DIVIDE || t.kind == MINUS || t.kind == EXPONENT || 
		t.kind == PLUS || t.kind == RIGHTPAREN || t.kind == MULIIPLY || t.kind == LEFTPAREN)	// epsilon
	{
		ungetToken(t);
		return arg; 
	}
	else 
	{
		syntax_Error(); 
	}
}

/*
	Factor -> NUMBER
	Factor -> LEFTPAREN exp RIGHTPAREN
	Factor -> MINUS LEFTPAREN exp RIGHTPAREN 
	Factor -> MINUS primary 
	Should only return a literal number 
*/
double Parser::parse_Factor()
{
	double left = 0; 
	Token t = getToken();
	Token t2 = getToken(); 
	if (t.kind == DOUBLE) 
	{
		ungetToken(t2); 
		return t.value; 
	}
	else if (t.kind == LEFTPAREN) 
	{
		ungetToken(t2);
		// Consume leftParen
		left = parse_Expression(); 
		if (getToken().kind != RIGHTPAREN) 
		{
			syntax_Error(); 
		}
		return left; 
	}
	else if (t.kind == MINUS && t2.kind == LEFTPAREN) 
	{
		// Consume both - ( 
		left = parse_Expression();
		
		Token t = getToken(); 
		if (t.kind != RIGHTPAREN) 
		{
			syntax_Error(); 
		}
		left = parse_Primary2(left);
		left *= -1; 
		return left; 
	}
	else if (t.kind == MINUS && ( t2.kind == DOUBLE ||
			t2.kind == MINUS))	// first of primary in t2 
	{
		// unget t2
		ungetToken(t2);
		left = parse_Primary(); 
		left *= -1; 
		return left; 
	}
	else 
	{
		syntax_Error(); 
	}
}


/*
	Void function checks if last token is EOF if not then error 
*/
void Parser::check_EOF()
{
	// Get and consume the token 
	Token t = getToken(); 
	if (t.kind != ENDOFFILE)
	{
		syntax_Error(); 
	}
}


/*
	Void function throws a syntax error 
*/
void Parser::syntax_Error()
{
	throw std::runtime_error("Syntax Error");
}



/*
	Pops token from the stack and returns it to the caller 
*/
Token Parser::getToken() 
{
	Token t = this->Tokens.top(); 
	this->Tokens.pop(); 
	return t; 
}


/*	
	Adds token back to the stack
*/
void Parser::ungetToken(Token t) 
{
	this->Tokens.push(t); 
}

