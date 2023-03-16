#include <fstream>
#include <string>
#include <iostream>
//#include "pars.h"
//#include "Avltree.h"
#include "Lex.h"
//#include "Graphnod.h"


#ifndef ACTIVE_H
#define ACTIVE_H

using namespace std;

class activation
{
	private:

		//union value{int intgr; float flot;}a;

		string function_name,
			   return_value;
		int return_offset;
		list<string> param_nm;
		list<string> parm_valu;
		
		int dynamic_link;
		int static_link;
		
		list<string> local_var_nm;
		list<string> local_var_valu;
		
		list<string> temp_var_nm;
		list<string> temp_var_valu;

		ofstream mycout;
	public:
		//union value{int intgr; float flot;}a;

		void print();
		void mk_lcl_tmp(AVLnode*);
		bool create(stack<string>&,stack<Avltree*>&,stack<Avltree*>&,int);
		string get_type(stack <Avltree*>& stk,string str);

		activation(){mycout.open("acti.txt");}
		~activation(){mycout.close();}
};

#endif
