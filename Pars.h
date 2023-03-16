#include "lex.h"
#include "code.h"
#include "active.h"
#include <String>
#include <stack>
#include <iostream>
#include <fstream>
//#include <conio>
#include <string>
#include <cstdlib>

using namespace std;//use it in every header file or only in 1......?



#ifndef pars_h
#define pars_h

class Parser
{
	private:
		int token,//used to save the token
		    ileft,// used to save the index of left array
			iup,//used to save the index of up array
			size_up;

		 stack <Avltree*> func_stack;	
		 string pars_tabl[41][43];// save the pars table
		 string left[41];// save the non-terminals
		 string up[75];//save the terminals & the markers, 43 terminals 
		 string marker;//used to save the marker to b called when next terminal comes
		 stack<string> pars_stack;// stack used 4 the productions
		 stack<string> evaluate_stack;//stack used to evaluate the expressions,to form a logical parsetree
		 bool call_marker;//used to decide whether sm marker is to b called or not
		 bool input_flag;// it keeps chk whther next input should b takeb or not yet it is 
		                   //false till the non-terminal com at tos and matches the input
		 bool read_flag;
		 Code mark;//object of  code used to call the functions for markers
		 activation act;//used to call when need to create object

	public:
		Parser();
		void call_mrkr(stack <Avltree*> &);//utility function to call the mrkr
		int is_terminal(string);// returns the index if it is terminal else 43
		int is_non_terminal(string);// returns the index if it is terminal else 40
		void set_left_up();// sets the left and up for the production 2 b fired
		void initialiaze(Lex);// initializez stack with '$' symbol and start production
		int get_up(int);// gets the index of token given in non-terminal arrray
		void parse(Lex&,stack <Avltree*> &);// main function that do the job of parsing
		int check(stack <Avltree*> &,Lex&);// chks whether to pop or fire production this is called by parser(lex)
		int fire_production();// fires prsoduction whn called and returns int depending on cond after exec.
};
#endif