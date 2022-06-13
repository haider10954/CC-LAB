// HAIDER ZAMAN 01-134182-077 (DO WHILE AND PUTBACK)
#include<iostream>
#include<string>
#include<fstream>
#include <iomanip>
using namespace std;

fstream file("C:\\Users\\Haider Zaman\\source\\repos\\CC_LAB1\\cc.txt", ios::in);
char ch;

enum Tokens {
	H_ADD, H_LB_C, H_RB_C, H_LB_R, H_RB_R, H_SUBT, H_SEMI_COLON, H_MULT, H_COMMA, H_F_SLASH, H_RB_S,
	H_LB_S, H_LESS_TH, H_GR_TH, H_INC, H_DEC, H_NOT, H_ASSIGN, H_EQUALEQUAL, H_PLUS_EQUAL, H_MINUS_EQUAL,
	H_DIVID_QUAL, H_MUL_EQUAL, H_NOT_EQUAL, H_GREATER_EQUAL, H_LESS_EQUAL, H_DEFAULT, H_IF, H_ELSE, H_WHILE,
	H_FOR, H_DO, H_BEGIN, H_END, H_SWITCH, H_BREAK, H_ELSEIF, H_VAR, H_NUM, H_COMMENT, H_AND, H_OR, H_COMPAND, H_COMPOR, H_LEFTSHIFT, H_RIGHTSHIFT
};

struct TokenRecord {
	Tokens Value;
	string Token_str;
};

TokenRecord arr[100];
TokenRecord x;
TokenRecord y;
bool flag;
bool state();
bool program();
bool state_list();
bool expression();
bool term();
bool fact();
bool OREXP();
bool ANDEXP();
bool EQUALEXP();
bool COMPEXP();
bool SHFTEXP();
int size_arr = 0;
void H_ADD_entry(string H_ADD)
{
	arr[size_arr].Token_str = H_ADD;
	arr[size_arr].Value = H_VAR;
}

int search(string check)
{
	for (int i = 0; i < size_arr; i++)
	{
		if (arr[i].Token_str == check)
		{
			return i;
		}
	}
	H_ADD_entry(check);
	size_arr++;
	return 1;
}

void create_table()
{
	cout << '\t' << "-:SYMBOL TABLE:-" << '\t' << endl;
	cout << "Entry No" << "  " << "Identifier" << "      " << "Value" << endl;
	for (int i = 0; i < size_arr; i++)
	{

		cout << i + 1 << "         " << arr[i].Token_str << "            " << arr[i].Value << endl;
	}

}

TokenRecord GetTokenRecord()
{
	TokenRecord Token_Array;
	while (!file.eof())
	{
		file.get(ch);
		if (isspace(ch))
		{
			continue;
		}
		else
		{
			if (isalpha(ch))
			{
				string check;
				do {
					check += ch;
					file.get(ch);
				} while (isalpha(ch) || isdigit(ch));
				file.putback(ch);
				if (check == "if")
				{
					Token_Array.Token_str = "if";
					Token_Array.Value = H_IF;

					return Token_Array;
				}
				else if (check == "else")
				{
					file.get(ch);
					if (check == " ")
					{
						if (check == "if")
						{
							Token_Array.Token_str = "else if";
							Token_Array.Value = H_ELSEIF;
							return Token_Array;
						}
						else
							file.putback(ch);
					}
					file.putback(ch);
					Token_Array.Token_str = "else";
					Token_Array.Value = H_ELSE;
					return Token_Array;
				}
				else if (check == "do")
				{
					Token_Array.Token_str = "do";
					Token_Array.Value = H_DO;
					return Token_Array;
				}
				else if (check == "while")
				{
					Token_Array.Token_str = "while";
					Token_Array.Value = H_WHILE;
					return Token_Array;
				}
				else if (check == "for")
				{
					Token_Array.Token_str = "for";
					Token_Array.Value = H_FOR;
					return Token_Array;
				}
				else if (check == "BEGIN")
				{
					Token_Array.Token_str = "BEGIN";
					Token_Array.Value = H_BEGIN;
					return Token_Array;
				}
				else if (check == "END")
				{
					Token_Array.Token_str = "END";
					Token_Array.Value = H_END;
					return Token_Array;
				}
				else
				{
					//search(check);
					Token_Array.Token_str = "variable";
					Token_Array.Value = H_VAR;
					return Token_Array;
				}
			}
			else if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
			{
				string num;
				num += ch;
				file.get(ch);
				if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
				{
					num += ch;

				}
				else
					file.putback(ch);
				Token_Array.Token_str = "DIGIT";
				Token_Array.Value = H_NUM;
				return Token_Array;
			}
			else
			{
				switch (ch)
				{
				case ',':
				{
					Token_Array.Token_str = ",";
					Token_Array.Value = H_COMMA;
					return Token_Array;
				}
				case '*':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "*=";
						Token_Array.Value = H_MUL_EQUAL;
						return Token_Array;
					}
					else
					{

						file.putback(ch);
					}
					Token_Array.Token_str = "*";
					Token_Array.Value = H_MULT;
					return Token_Array;
				}
				case '+':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "+=";
						Token_Array.Value = H_PLUS_EQUAL;
						return Token_Array;
					}
					else if (ch == '+')
					{
						Token_Array.Token_str = "++";
						Token_Array.Value = H_INC;
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = "+";
					Token_Array.Value = H_ADD;
					return Token_Array;
				}
				case '-':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "-=";
						Token_Array.Value = H_MINUS_EQUAL;
						return Token_Array;
					}
					else if (ch == '-')
					{
						Token_Array.Token_str = "--";
						Token_Array.Value = H_DEC;
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = "-";
					Token_Array.Value = H_SUBT;
					return Token_Array;
				}
				case '/':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "/=";
						Token_Array.Value = H_DIVID_QUAL;
						return Token_Array;
					}
					else if (ch == '/')
					{
						Token_Array.Token_str = "//";
						Token_Array.Value = H_COMMENT;
						while (file.get() != '\n')
						{
							continue;
						}
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = "/";
					Token_Array.Value = H_F_SLASH;
					return Token_Array;
				}
				case '[':
				{
					Token_Array.Token_str = "[";
					Token_Array.Value = H_LB_S;
					return Token_Array;
				}
				case ']':
				{
					Token_Array.Token_str = "]";
					Token_Array.Value = H_RB_S;
					return Token_Array;
				}
				case '{':
				{
					Token_Array.Token_str = "{";
					Token_Array.Value = H_LB_C;
					return Token_Array;
				}
				case '}':
				{
					Token_Array.Token_str = "}";
					Token_Array.Value = H_RB_C;
					return Token_Array;
				}
				case ')':
				{
					Token_Array.Token_str = ")";
					Token_Array.Value = H_RB_R;
					return Token_Array;
				}
				case '(':
				{
					Token_Array.Token_str = "(";
					Token_Array.Value = H_LB_R;
					return Token_Array;
				}
				case ';':
				{
					Token_Array.Token_str = ";";
					Token_Array.Value = H_SEMI_COLON;
					return Token_Array;
				}
				case '>':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = ">=";
						Token_Array.Value = H_GREATER_EQUAL;
						return Token_Array;
					}
					else if (ch == '>')
					{
						Token_Array.Token_str = ">>";
						Token_Array.Value = H_RIGHTSHIFT;
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = ">";
					Token_Array.Value = H_GR_TH;
					return Token_Array;
				}
				case '<':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "<=";
						Token_Array.Value = H_LESS_EQUAL;
						return Token_Array;
					}
					else if (ch == '<')
					{
						Token_Array.Token_str = "<<";
						Token_Array.Value = H_LEFTSHIFT;
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = "<";
					Token_Array.Value = H_LESS_TH;
					return Token_Array;
				}
				case '=':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "==";
						Token_Array.Value = H_EQUALEQUAL;
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = "=";
					Token_Array.Value = H_ASSIGN;
					return Token_Array;
				}
				case '&':
				{
					file.get(ch);
					if (ch == '&')
					{
						Token_Array.Value = H_COMPAND;
						Token_Array.Token_str = "&&";
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Value = H_AND;
					Token_Array.Token_str = "&";
					return Token_Array;
				}
				case '|':
				{
					file.get(ch);
					if (ch == '|')
					{
						Token_Array.Value = H_COMPOR;
						Token_Array.Token_str = "||";
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Value = H_OR;
					Token_Array.Token_str = "|";
					return Token_Array;
				}

				case '!':
				{
					file.get(ch);
					if (ch == '=')
					{
						Token_Array.Token_str = "!=";
						Token_Array.Value = H_NOT_EQUAL;
						return Token_Array;
					}
					else
					{
						file.putback(ch);
					}
					Token_Array.Token_str = "!";
					Token_Array.Value = H_NOT;
					return Token_Array;
				}
				default:
				{
					Token_Array.Value = H_DEFAULT;
				}

				}
			}
		}
	}
	return Token_Array;
}

TokenRecord get_next()
{
	if (flag == false)
	{
		x = GetTokenRecord();
		return x;
	}
	else
	{
		flag = false;
		return x;
	}
}

void put_back()
{
	flag = true;
}

int main()
{
	if (file.is_open())
	{
		file.seekg(0);
		bool cor;
		cor = program();
		if (cor)
		{
			cout << "All Ok" << endl;
		}
		else
		{
			cout << "The Code in File in Incorrect" << endl;
		}
		//create_table();
		file.close();
	}
	else
	{
		cout << "Can't open the file" << endl;
		return 0;
	}
	return 0;
}

bool program()
{
	y = get_next();
	if (y.Value == H_BEGIN)
	{
		if (state_list())
		{
			y = get_next();
			if (y.Value == H_END)
			{
				return true;
			}
		}
	}
	return false;
}
bool state_list() // statement list 
{
	if (state())
	{
		do
		{
			y = get_next();
			if (y.Value == H_IF || y.Value == H_DO || y.Value == H_VAR)
			{
				put_back();
				return false;
			}
			else
			{
				put_back();
				break;
			}
		} while (1);
		return true; // if , not, uid not equal then may be else
	}
	return false; //otherwise false
}
bool state()
{
	y = get_next();
	if (y.Value == H_VAR)
	{
		y = get_next();
		if (y.Value == H_ASSIGN || y.Value == H_NOT_EQUAL || y.Value == H_PLUS_EQUAL ||
			y.Value == H_MINUS_EQUAL)
		{
			if (OREXP())
			{
				y = get_next();
				if (y.Value == H_SEMI_COLON)
				{
					return true;
				}
			}
		}
		put_back();

	}
	else if (y.Value == H_IF)
	{
		y = get_next();
		if (y.Value == H_LB_R)
		{
			if (OREXP())
			{
				y = get_next();
				if (y.Value == H_RB_R)
				{
					y = get_next();
					if (y.Value == H_LB_C)
					{
						if (state_list())
						{
							y = get_next();
							if (y.Value == H_RB_C)
							{
								y = get_next();
								if (y.Value == H_ELSE)
								{
									y = get_next();
									if (y.Value == H_LB_C)
									{
										if (state_list())
										{
											y = get_next();
											if (y.Value == H_RB_C)
											{
												return true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		put_back();
	}
	else if (y.Value == H_DO)
	{
		y = get_next();
		if (y.Value == H_LB_C)
		{
			if (state_list())
			{
				y = get_next();
				if (y.Value == H_RB_C)
				{
					y = get_next();
					if (y.Value = H_LB_R)
					{
						if (OREXP())
						{
							y = get_next();
							if (y.Value == H_SEMI_COLON)
							{
								return true;
							}
						}
					}
				}

			}
		}
	}
}







bool OREXP()
{
	do
	{
		if (!ANDEXP())
			return false;
		y = get_next();
	} while (y.Value == H_COMPOR);
	put_back();
	return true;
}
bool ANDEXP()
{
	do
	{
		if (!EQUALEXP())
			return false;
		y = get_next();
	} while (y.Value == H_COMPAND);
	put_back();
	return true;
}
bool EQUALEXP()
{
	do
	{
		if (!COMPEXP())
			return false;
		y = get_next();
	} while (y.Value == H_EQUALEQUAL || y.Value == H_NOT_EQUAL);
	put_back();
	return true;
}
bool COMPEXP()
{
	do
	{
		if (!SHFTEXP())
			return false;
		y = get_next();
	} while (y.Value == H_GREATER_EQUAL || y.Value == H_LESS_EQUAL || y.Value == H_LESS_TH
		|| y.Value == H_GR_TH);
	put_back();
	return true;
}
bool SHFTEXP()
{
	do
	{
		if (!expression())
			return false;
		y = get_next();
	} while (y.Value == H_RIGHTSHIFT || y.Value == H_LEFTSHIFT);
	put_back();
	return true;
}

bool expression()
{
	bool string = false;
	do
	{
		string = term();
		y = get_next();
	} while (y.Value == H_ADD || y.Value == H_SUBT);
	put_back();
	return string;
}

bool term()
{
	bool string = false;
	do {
		string = fact();
		y = get_next();
	} while (y.Value == H_MULT || y.Value == H_F_SLASH);
	put_back();
	return string;
}

bool fact()
{
	y = get_next();
	if (y.Value == H_NUM)
		return true;
	else if (y.Value == H_VAR)
		return true;
	else if (y.Value == H_LB_R)
	{
		expression();
		y = get_next();
		if (x.Value == H_RB_R)
			return true;
		else
			return false;
	}
	return false;
}