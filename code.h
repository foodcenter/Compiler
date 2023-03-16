#include "string"
#include <stack>
#include <iostream>
#include <fstream>
//#include "pars.h"
#include "Avltree.h"
#include "Lex.h"
//#include "Graphnod.h"


#ifndef CODE_H
#define CODE_H

//using namespace std;

class Code
{
	private:
		string oprator,
			   var1,
			   var2,
			   result;
		int line_num,
			temp_counter;
		stack <int> bkpch_stk;
		ofstream mcout;
		bool glo_f_v1;
		bool glo_f_v2;

	public:
		Code()
		{
			string s1(" ");
			var1=s1;
			var2=s1;
			result=s1;
			oprator=s1;
			line_num=1;
			temp_counter=1;
			bool glo_f_v1=false;
			bool glo_f_v2=false;
			mcout.open("code.txt");
		}
		int get_line(){return this->line_num;}

		string newtemp();
		~Code()
		{
			mcout.close();
		}

		void make_list(AVLnode*&,AVLnode* );
		string get_type(stack <Avltree*>&,string);		
		bool check_scope(stack <Avltree*>&);
		bool check_global(stack <Avltree*>&,string);
		bool check_global_fun(stack <Avltree*>&,string);
		void print();//print the values set by marker to the file
		bool marker1(stack <string>& , stack <Avltree*>&);
		bool marker2(stack <string>& , stack <Avltree*>&);
		bool marker3(stack <string>& , stack <Avltree*>&);
		bool marker4(stack <string>& , stack <Avltree*>&);
		bool marker5(stack <string>& , stack <Avltree*>&);
		bool marker6(stack <string>& , stack <Avltree*>&);
		bool marker9(stack <string>& , stack <Avltree*>&);
		bool marker10(stack <string>& , stack <Avltree*>&);
		bool marker11(stack <string>& , stack <Avltree*>&);
		bool marker12(stack <string>& , stack <Avltree*>&);
		bool marker13(stack <string>& , stack <Avltree*>&);
		bool marker14(stack <string>& , stack <Avltree*>&);
		bool marker15(stack <string>& , stack <Avltree*>&);
		bool marker16(stack <string>& , stack <Avltree*>&);
		bool marker18(stack <string>& , stack <Avltree*>&);

		bool marker19(stack <string>& , stack <Avltree*>&);
		bool marker20(stack <string>& , stack <Avltree*>&);

		bool marker21(stack <string>& , stack <Avltree*>&);
		bool marker22(stack <string>& , stack <Avltree*>&);

		bool marker24(stack <string>& , stack <Avltree*>&);
		bool marker25(stack <string>& , stack <Avltree*>&);
		bool marker26(stack <string>& , stack <Avltree*>&);
		bool marker27(stack <string>& , stack <Avltree*>&);
		bool marker28(stack <string>& , stack <Avltree*>&);
		int func(stack<string>&,stack<Avltree*>,stack<Avltree*>,int);
};

#endif
