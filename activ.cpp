#include "active.h"
#include <iostream>
//using namespace std;


void activation::mk_lcl_tmp(AVLnode* t)
{

	if(t)
	{
		mk_lcl_tmp(t->left);

		//create the temp or local variabl

		string nam=t->get_name();
		string tip=t->get_type();
		
		string ss(nam.substr(0,1));
		string sss("~");
		if(ss == sss)//tempry var
		{
			temp_var_nm.push_back(nam);
			if(tip=="integer")
				temp_var_valu.push_back("0");

			else if(tip=="real")
				temp_var_valu.push_back("0.0");
		
		}
		
		else
		{
			local_var_nm.push_back(nam);
			if(tip=="integer")
				local_var_valu.push_back("0");
			else if(tip=="real")
				local_var_valu.push_back("0.0");
		
		}
		/////////////////////
		mk_lcl_tmp(t->right);
	}
	
	return;
}


/*
string activation::get_type(stack <Avltree*>& stk,string str)
{

	AVLnode* a=stk.top()->search(stk.top()->getroot(),str);
	if(a)
	{
		string st=a->get_type();
		return st;
	}
	
	else
	{
		stack <Avltree*> tmp;
	
		while(!stk.empty())
		{
			tmp.push(stk.top());
			stk.pop();
		}


		a=tmp.top()->search(tmp.top()->getroot(),str);

		//at the top is the global tree,search the node needed in it
		//and then get its type
		
		while(!tmp.empty())
		{
			stk.push(tmp.top());
			tmp.pop();
		}

		if(!a)
		{
			string str("0");
			return str;
		}

		
		string rt=a->get_type();
		return rt;
	}
	
}
*/
bool activation::create(stack<string>& eval_stk,stack<Avltree*>& stk,stack<Avltree*>& func_stk,int line)
{

	string st=func_stk.top()->get_name();//(stk.top()->getroot(),name);	
	this->function_name=st;
	AVLnode *aa=stk.top()->search(stk.top()->getroot(),st);
	int ln=aa->func_strt;
	
	for(int i=0;i < aa->param.size();i++ )
	{
		param_nm.push_back(aa->param[i]);
		string st=aa->par_type[i];

		if(st=="integer")
			parm_valu.push_back("0");
		else if(st=="real")
			parm_valu.push_back("0.0");
	}	
	
//ake local vari list
	bool tt=true;
	//if(stk.top()->get_name() == function_name)
	{
		mk_lcl_tmp(func_stk.top()->getroot());
		tt=false;
	}
	
	this->return_value="1";
	this->dynamic_link=1;
	this->static_link=1;
	this->return_offset=0;
	print();
	
	eval_stk.push("@");//to chk te function without parameters

	return true;
}



string activation::get_type(stack <Avltree*>& stk,string str)
{

	AVLnode* a=stk.top()->search(stk.top()->getroot(),str);
	if(a)
	{
		string st=a->get_type();
		return st;
	}
	
	else
	{
		stack <Avltree*> tmp;
	
		while(!stk.empty())
		{
			tmp.push(stk.top());
			stk.pop();
		}


		a=tmp.top()->search(tmp.top()->getroot(),str);

		//at the top is the global tree,search the node needed in it
		//and then get its type
		
		while(!tmp.empty())
		{
			stk.push(tmp.top());
			tmp.pop();
		}

		if(!a)
		{
			string str("0");
			return str;
		}

		
		string rt=a->get_type();
		return rt;
	}
	
}

void activation::print()
{

	mycout<<this->function_name<<"\n";
	mycout<<this->return_value<<"\n";
	mycout<<this->return_offset<<"\n\n\n";
	mycout<<"Parameters:\n";
	while(!param_nm.empty())
	{
		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->param_nm.front();
		param_nm.pop_front();
		
		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->parm_valu.front()<<"\n";
		parm_valu.pop_front();
	}
		mycout<<"\n\n";

		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<"Dynamic link";

		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->dynamic_link<<"\n";

		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<"Static link";

		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->static_link<<"\n\n";

		mycout<<"Local variables :\n";

	while(!local_var_nm.empty())
	{
		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->local_var_nm.front();
		local_var_nm.pop_front();

		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->local_var_valu.front()<<"\n";
		local_var_valu.pop_front();
	}
	
	mycout<<"\n\ntemporary variables :\n";

	while(!temp_var_nm.empty())
	{
		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->temp_var_nm.front();
		temp_var_nm.pop_front();

		mycout.setf(ios::left);
		mycout.width(20);
		mycout.fill(' ');
		mycout<<this->temp_var_valu.front()<<"\n";
		temp_var_valu.pop_front();
	}


	mycout<<"\n\n\nNext Record\n";

}
