#include "Tokenizer.h"


Tokenizer::Tokenizer(std::string str_List)
	:raw_String{ str_List }
{
	// Call function to convert strings to tokens 
	Lexical_Analysis();
	Tokens_Stack.push(Token(ENDOFFILE,0));
	reOrderStack(); 
}

/* Initliaze our tokens initalize arg to 0 assuming token is not a literal number */
Token::Token(Types t, double arg = 0)
	:value{ arg }, kind{t}
{
}

/*	Tokenize each string on the stack holding raw strings */
void Tokenizer::Lexical_Analysis() 
{
	// We have the string now traverse each character convert it into tokens 

	for (auto it = raw_String.begin(); it != raw_String.end(); ++it)
	{
		// Check if character matches any of the REGEX
		// First check for the special symbols and operators 
		switch (*it) 
		{
		case('+'):
			this->Tokens_Stack.push(Token(PLUS)); 
			this->Tokens_List.push_back(Token(PLUS));
			break;
		case('-'):
			this->Tokens_Stack.push(Token(MINUS));
			this->Tokens_List.push_back(Token(MINUS));
			break; 
		case('*'):
			this->Tokens_Stack.push(Token(MULIIPLY));
			this->Tokens_List.push_back(Token(MULIIPLY));
			break;
		case('/'):
			this->Tokens_Stack.push(Token(DIVIDE));
			this->Tokens_List.push_back(Token(DIVIDE));
			break;
		case('('):
			this->Tokens_Stack.push(Token(LEFTPAREN));
			this->Tokens_List.push_back(Token(LEFTPAREN));
			break;
		case(')'):
			this->Tokens_Stack.push(Token(RIGHTPAREN));
			this->Tokens_List.push_back(Token(RIGHTPAREN));
			break;
		case('^'):
			this->Tokens_Stack.push(Token(EXPONENT)); 
			this->Tokens_List.push_back(Token(EXPONENT));
		case(' '):
			break; 
				// do nothing
		default :	// if none of these cases make sure its a real number other wise a tokenizer error 
			num_Tokenizer(it);
			break; 
		}
	}
}


/*
	Void function will help tokenize
*/ 
void Tokenizer::num_Tokenizer(std::string::iterator& it) 
{
	std::regex int_Reg(INT_EXP);
	std::regex dol_Reg(DOUBLE_EX);
	std::string temp{""};
	// Iterate the string any matches add it to a string and put it in token 
	for (auto ptr = it; ptr != raw_String.end(); ++ptr)
	{
		switch (*ptr) 
		{
			case('.'):
			case('0'): 
			case('1'):
			case('2'): 
			case('3'): 
			case('4'):
			case('5'):
			case('6'):
			case('7'):
			case('8'):
			case('9'):
				// Now add it to the string
				temp += *ptr;
				break;
			default:		// default will check if it matches any of our REGEX if not throw error
				
				if (std::regex_search(temp, int_Reg))
				{
					this->Tokens_Stack.push(Token(DOUBLE, std::stod(temp)));
					this->Tokens_List.push_back(Token(DOUBLE, std::stod(temp)));
					it = ptr;
					--it; 
					return;
				}
				else if (std::regex_search(temp, dol_Reg))
				{
					this->Tokens_Stack.push(Token(DOUBLE, std::stod(temp)));
					this->Tokens_List.push_back(Token(DOUBLE, std::stod(temp)));
					it = ptr;
					--it; 
					return;
				}
				else
				{
					throw std::runtime_error("Tokenizer Error");
				}
				break; 
		}
	}

	// Reached end of the character array case now check if it is valid
	if (std::regex_search(temp, int_Reg))
	{
		this->Tokens_Stack.push(Token(DOUBLE, std::stod(temp)));
		this->Tokens_List.push_back(Token(DOUBLE, std::stod(temp)));
		it = raw_String.end(); 
		--it; 
		return;
	}
	else if (std::regex_search(temp, dol_Reg))
	{
		this->Tokens_Stack.push(Token(DOUBLE, std::stod(temp)));
		this->Tokens_List.push_back(Token(DOUBLE, std::stod(temp)));
		it = raw_String.end();
		--it; 
		return;
	}
	else
	{
		throw std::runtime_error("Tokenizer Error");
	}
}


// Return of a vector of tokens 
std::vector<Token>  Tokenizer::getVector() 
{
	return this->Tokens_List; 
}

// Return a stack of tokens 
std::stack<Token> Tokenizer::getStack() 
{
	return this->Tokens_Stack; 
}

void Tokenizer::reOrderStack()
{
	std::stack<Token> lcl;
	while (this->Tokens_Stack.empty() == false)
	{
		lcl.push(Tokens_Stack.top());
		Tokens_Stack.pop();
	}
	// Done
	Tokens_Stack = lcl;
}