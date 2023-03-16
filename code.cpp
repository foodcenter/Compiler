#include "code.h"


string Code::newtemp()
{
	string rslt("~t");
			
	char num[25];//used to change the number of temprary variable into an array
	itoa(temp_counter,num,10);//temp_counter is now in the num
	temp_counter++;

	string temp(num);

	string reslt(rslt + temp);
	return reslt;
}

void Code::print()
{
	//print the values set ointo the file	
	//ofstream mcout("code.txt",ios::app);
	mcout.seekp(72*(line_num-1),ios::beg);

	mcout.setf(ios::left);
	mcout.width(5);
	mcout.fill(' ');
	mcout<<line_num;


	mcout.setf(ios::left);
	mcout.width(20);
	mcout.fill(' ');
	mcout<<this->oprator;

	mcout.setf(ios::left);
	mcout.width(20);
	mcout.fill(' ');
	mcout<<this->var1;

	mcout.setf(ios::left);
	mcout.width(15);
	mcout.fill(' ');
	mcout<<this->var2;

	mcout.setf(ios::left);
	mcout.width(10);
	mcout.fill(' ');
	mcout<<this->result<<"\n";
	//mcout.close();
	line_num++;

}


void Code::make_list(AVLnode*& a,AVLnode* t)
{
	if(t)
	{
		make_list(a,t->left);

		//create the temp or local variabl

		string nam=t->get_name();
		string tip=t->get_type();
		a->no_param++;
		a->param.push_back(nam);
		a->par_type.push_back(tip);
		
		/////////////////////
		make_list(a,t->right);
	}
	
	return;

}
string Code::get_type(stack <Avltree*>& stk,string str)
{
	stack <Avltree*> tmp;
	
	while(!stk.empty())
	{
		tmp.push(stk.top());
		stk.pop();
	}


	AVLnode* a=tmp.top()->search(tmp.top()->getroot(),str);
	
	//at the top is the global tree,search the node needed in it
	//and then get its type
	
	while(!tmp.empty())
	{
		stk.push(tmp.top());
		tmp.pop();
	}

	if(a)
	{
		string st=a->get_type();
		return st;
	}
	
	string sd("-1");
	return sd;
}
bool Code::check_global_fun(stack <Avltree*>& stk,string str)
{
	stack <Avltree*> tmp;
	
	while(!stk.empty())
	{
		tmp.push(stk.top());
		stk.pop();
	}


	AVLnode* a=tmp.top()->search(tmp.top()->getroot(),str);
	
	
	while(!tmp.empty())
	{
		stk.push(tmp.top());
		tmp.pop();
	}
	
	if(!a)
		return false;
	
	bool t=false;
	if(a->func_strt != 0)
		t=true;

	return t;

}

bool Code::check_global(stack <Avltree*>& stk,string str)
{
	stack <Avltree*> tmp;
	
	while(!stk.empty())
	{
		tmp.push(stk.top());
		stk.pop();
	}


	bool a=tmp.top()->search1(tmp.top()->getroot(),str);
	
	while(!tmp.empty())
	{
		stk.push(tmp.top());
		tmp.pop();
	}


	return a;

}

bool Code::check_scope(stack <Avltree*>& stk)
{
	string chk("0");//if an var2 is not used inany function it sets that to 0 and we chk this 
					//if we need to chyk var2 or not.

	bool a=stk.top()->search1(stk.top()->getroot(),this->var1);
	if(!a)//if not a
	{
		a=check_global(stk,var1);
		if(!a)
			return false;
		this->glo_f_v1=true;
	}
	if(var2 != chk)
	{
		bool b=stk.top()->search1(stk.top()->getroot(),this->var2);
		if(b)// if b is there
			return true;
		else// if b is not in symbol table
		{
			b=check_global(stk,var2);
			if(!b)
				return false;
			this->glo_f_v2=true;
			return true;
		}

	}
	
	return true;//if a is in ST and b is nt needed
}

bool Code::marker1(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->var2=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator=":=";
	//eval_stk.pop();//pop the oprator
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();

	string temp_var1;
	bool scope=check_scope(stk);

	if(scope)
	{
		
		string type1,type2;
		
		AVLnode* a=stk.top()->search(stk.top()->getroot(),this->var1);
		
		AVLnode* b=stk.top()->search(stk.top()->getroot (),this->var2);

		if(!a)
		{
			type1=get_type(stk,this->var1);
			if(type1=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}
		}

		else
			type1=a->get_type();

		if(!b)
		{
			type2=get_type(stk,this->var2);
			if(type2=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}
		}
		else
			type2=b->get_type();
			
		
		string operator_type=type1;
		string assign(":=");
		string final;
		string com("integer");
		string us;
		if( type1 == type2 )//if both have the same types
		{
			
			if(type1==com)
				us="int_";
			else
				us="real_";

			final=us + ":=";
			this->oprator = final;
			this->result="-";
		}

		else 
		{
			string s=newtemp();
			
			AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
			stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
			node->set_type(type1);

			if(type1==com)
				this->oprator="toInt";
			else
				this->oprator="toReal";
			this->result=s;
						
			temp_var1=this->var1;
			this->var1=this->var2;
			this->var2="-";

			print();
		
			this->var2=s;
			this->var1=temp_var1;

			if(type1==com)
				us="int_";
			else
				us="real_";

			final=us + ":=";
			this->oprator = final;
			this->result="-";
			
		}


		print();
	}//end if1
	
	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;			
}

bool Code::marker2(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->var2=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator=eval_stk.top();
	eval_stk.pop();//pop the oprator
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();

	bool scope=check_scope(stk);

	if(scope)
	{
		//get the types of the two variables
		string type1,type2;
		
		AVLnode* a=stk.top()->search(stk.top()->getroot(),this->var1);
		
		AVLnode* b=stk.top()->search(stk.top()->getroot (),this->var2);

		if(!a)
		{
			type1=get_type(stk,this->var1);
			if(type1=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}

		}
		else
			type1=a->get_type();

		if(!b)
		{
			type2=get_type(stk,this->var2);
			if(type2=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}

		}
		else
			type2=b->get_type();
		while(1)
		{
			if( type1 == type2 )//if both have the same types
			{
				string com("real");
				string operator_type="int";
				if(type1==com)
					operator_type=type1;
					
				string plus("+");
				string minus("-");
				string or("or");
				string us(operator_type + "_");

				if(oprator==plus)
				{
					string final(us + "+");
					this->oprator = final;
				}

				if(oprator==minus)
				{
					string final(us + "-");
					this->oprator = final;
				}

				if(oprator==or)
				{
					string final(us + "or");
					this->oprator = final;
				}

				//create  a temporary variable n assign result to it 

				string reslt=newtemp();

				this->result=reslt;//result have 9 the name of the new temp variable
				
				AVLnode * node=new AVLnode(reslt);//make a new node of the new temp variable
				stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
				node->set_type(type1);
				//stk.top()->print(stk.top()->getroot());//insert this node to the tree of this function
					
				eval_stk.push(result);//push this variable on stack
				break;

			}

			else 
			{
				string temp_var;
				string temp_operator=this->oprator;
				string rr("integer");
				if(type1==rr)
				{
					string s=newtemp();
					
					AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
					stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
					node->set_type(type2);

					this->oprator="toReal";
					this->result=s;
								
					temp_var=this->var2;
					//this->var1=this->var2;
					this->var2="-";

					print();
					
					this->oprator=temp_operator;
					this->var1=s;
					this->var2=temp_var;
					type1="real";
								
				}

				else
				{
					string temp_var1;
					string temp_operator=this->oprator;
					string temp_var2;
					string rr("integer");
					string s=newtemp();
					
					AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
					stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
					node->set_type(type1);

					this->oprator="toReal";
					this->result=s;
								
					temp_var1=this->var1;
					//temp_var2=this->var2;

					this->var1=this->var2;
					this->var2="-";
					

					print();
					
					this->oprator=temp_operator;
					this->var2=s;
					this->var1=temp_var1;
					type2="real";
					

				}
			}

		}//end while
		print();
	}//end if1
	
	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;
}

bool Code::marker3(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	string s4("&");//used to show the end of identifiers in the eva;uater stack
	string s3=eval_stk.top();//it is containig the type to b assigned
	eval_stk.pop();//pop the type that was passsd as argument

	while(eval_stk.top() != s4)
	{
		stk.top()->set_type(eval_stk.top(),s3);//get the tree at the top nd call its set_type fn
		//stk.top()->print(stk.top()->getroot());
		eval_stk.pop();//pop the element that has been assigned the value
	}
	eval_stk.pop();//pop the & symbol

	stk.top()->print(stk.top()->getroot());
	cout<<"\n";

	return true;

}

bool Code::marker4(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	return true;

}

bool Code::marker5(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	string s4("&");//used to show the end of identifiers in the eva;uater stack
	string s3=eval_stk.top();//it is containig the type to b assigned
	eval_stk.pop();//pop the type that was passsd as argument

	stack<string> temp_stk;//used to sav the vsriables and then agian put them on the stack
	temp_stk.push(s4);
	
	while(eval_stk.top() != s4)
	{
		stk.top()->set_type(eval_stk.top(),s3);//get the tree at the top nd call its set_type fn
		//stk.top()->print(stk.top()->getroot());
		temp_stk.push(eval_stk.top());
		eval_stk.pop();//pop the element that has been assigned the value
	}
	eval_stk.pop();//pop the & symbol

	stack<Avltree*> tmp;
	while(!stk.empty())
	{
		tmp.push(stk.top());
		stk.pop();
	}

	string name=eval_stk.top();//name of function

	AVLnode * aa=tmp.top()->search(tmp.top()->getroot(),name);
//	aa->func_strt=mm;//start of the code of the function
	
	while(!tmp.empty())
	{
		//aa->param.push_back(temp_stk.top());
		//aa->no_param++;
		stk.push(tmp.top());
		tmp.pop();
	}

	while(temp_stk.top() != s4)
	{
		string nam=temp_stk.top();
		aa->no_param++;
		aa->param.push_back(nam);
		aa->par_type.push_back(s3);

		temp_stk.pop();
	}
	cout<<aa->no_param;
	cout<<aa->param.front();
	cout<<aa->param.back();

	return true;

}

bool Code::marker6(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	
	string name=eval_stk.top();//name of the function
	eval_stk.pop();//pop the & symbol
	
	stack <Avltree*> tmp;
	
	while(!stk.empty())
	{
		tmp.push(stk.top());
		stk.pop();
	}


	AVLnode * aa=tmp.top()->search(tmp.top()->getroot(),name);
	
	
	while(!tmp.empty())
	{
		//aa->param.push_back(temp_stk.top());
		//aa->no_param++;
		stk.push(tmp.top());
		tmp.pop();
	}


	
	make_list(aa,stk.top()->getroot());

	cout<<aa->no_param;
	cout<<aa->param.front();
	cout<<aa->param.back();
	//stk.top()->print(stk.top()->getroot());//take the tree at top and prints its varialbe
	cout<<"\n";

	return true;

}

bool Code::marker9(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	bool chk_addop=false;
	string str1=eval_stk.top();//to chk if any addop symbol is on stack
	
	if(str1=="+" || str1=="-" || str1=="or")
	{
		chk_addop=true;
		eval_stk.pop();//extra pop
	}

	this->var2=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator=eval_stk.top();
	eval_stk.pop();//pop the oprator
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();

	bool scope=check_scope(stk);

	if(scope)
	{
		//get the types of the two variables
		string type1,type2;
		
		AVLnode* a=stk.top()->search(stk.top()->getroot(),this->var1);
		
		AVLnode* b=stk.top()->search(stk.top()->getroot (),this->var2);

		if(!a)
		{
			type1=get_type(stk,this->var1);
			if(type1=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}
		
		}
		else
			type1=a->get_type();

		if(!b)
		{
			type2=get_type(stk,this->var2);
			if(type2=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}

		}
		else
			type2=b->get_type();


		while(1)
		{
			if( type1 == type2 )//if both have the same types
			{
				string operator_type=type1;
				string mul("*");
				string div("/");
				string and("and");
				string mod("mod");
				string us(operator_type + "_");

				if(oprator==mul)
				{
					string final(us + "*");
					this->oprator = final;
				}

				if(oprator==div)
				{
					string final(us + "/");
					this->oprator = final;
				}

				if(oprator==and)
				{
					string final(us + "and");
					this->oprator = final;
				}

				if(oprator==mod)
				{
					string final(us + "mod");
					this->oprator = final;
				}
				string reslt=newtemp();

				this->result=reslt;//result have 9 the name of the new temp variable
				AVLnode * node=new AVLnode(reslt);//make a new node of the new temp variable
				stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
				node->set_type(type1);
				eval_stk.push(result);//push this variable on stack

				if(chk_addop)
					eval_stk.push(str1);//push back the addop symbol where it should be
				break;
			}

			else 
			{
				string temp_var;
				string temp_operator=this->oprator;
				string rr("integer");
				if(type1==rr)
				{
					string s=newtemp();
					
					AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
					stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
					node->set_type(type2);

					this->oprator="toReal";
					this->result=s;
								
					temp_var=this->var2;
					//this->var1=this->var2;
					this->var2="-";

					print();
					
					this->oprator=temp_operator;
					this->var1=s;
					this->var2=temp_var;
					type1="real";
								
				}

				else
				{
					string temp_var1;
					string temp_operator=this->oprator;
					string temp_var2;
					string rr("integer");
					string s=newtemp();
					
					AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
					stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
					node->set_type(type1);

					this->oprator="toReal";
					this->result=s;
								
					temp_var1=this->var1;
					//temp_var2=this->var2;

					this->var1=this->var2;
					this->var2="-";
					

					print();
					
					this->oprator=temp_operator;
					this->var2=s;
					this->var1=temp_var1;
					type2="real";
					

				}//else 2
			}//else 1

		}//end while

		print();
	}//end if1
	
	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;
}

bool Code::marker10(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	/*this function createscode for evaluation of the 
	relop for the two given var and pushes result back 
	on the evaluate screen */

	this->var2=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator=eval_stk.top();
	eval_stk.pop();//pop the oprator
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();

	bool scope=check_scope(stk);

	if(scope)
	{
		//get the types of the two variables
				string type1,type2;
		
		AVLnode* a=stk.top()->search(stk.top()->getroot(),this->var1);
		
		AVLnode* b=stk.top()->search(stk.top()->getroot (),this->var2);

		if(!a)
		{
			type1=get_type(stk,this->var1);
			if(type1=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}
		
		}
		else
			type1=a->get_type();

		if(!b)
		{
			type2=get_type(stk,this->var2);
			if(type1=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}
		
		}
		else
			type2=b->get_type();


		while(1)
		{
			if( type1 == type2 )//if both have the same types
			{
				string operator_type("int");
				if(type1=="real")
					operator_type=type1;
				string not_eq("<>");
				string less("<");
				string les_eq("<=");
				string gretr(">");
				string gretr_eq(">=");
				string eq("=");



				string us(operator_type + "_");

				if(oprator==not_eq)
				{
					string final(us + "<>");
					this->oprator = final;
				}

				if(oprator==less)
				{
					string final(us + "<");
					this->oprator = final;
				}

				if(oprator==les_eq)
				{
					string final(us + "<=");
					this->oprator = final;
				}

				if(oprator==gretr)
				{
					string final(us + ">");
					this->oprator = final;
				}

				if(oprator==gretr_eq)
				{
					string final(us + ">=");
					this->oprator = final;
				}
				
				if(oprator==eq)
				{
					string final(us + "=");
					this->oprator = final;
				}

				//create  a temporary variable n assign result to it 

				
				string reslt=newtemp();

				this->result=reslt;//result have 9 the name of the new temp variable
				AVLnode * node=new AVLnode(reslt);//make a new node of the new temp variable
				stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
				node->set_type(type1);
				eval_stk.push(result);//push this variable on stack
				break;
				
			}

			else 
			{
				string temp_var;
				string temp_operator=this->oprator;
				string rr("integer");
				if(type1==rr)
				{
					string s=newtemp();
					
					AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
					stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
					node->set_type(type2);

					this->oprator="toReal";
					this->result=s;
								
					temp_var=this->var2;
					//this->var1=this->var2;
					this->var2="-";

					print();
					
					this->oprator=temp_operator;
					this->var1=s;
					this->var2=temp_var;
					type1="real";
								
				}

				else
				{
					string temp_var1;
					string temp_operator=this->oprator;
					string temp_var2;
					string rr("integer");
					string s=newtemp();
					
					AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
					stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
					node->set_type(type1);

					this->oprator="toReal";
					this->result=s;
								
					temp_var1=this->var1;
					//temp_var2=this->var2;

					this->var1=this->var2;
					this->var2="-";
					

					print();
					
					this->oprator=temp_operator;
					this->var2=s;
					this->var1=temp_var1;
					type2="real";
					

				}//else 2			
			}//else1

		}//end while
		print();
	}//end if1
	
	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;
}


bool Code::marker11(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator="write";
	this->var2="0";//assign var 2  to 0 so tht check_scope 9 that this is not used and its scope need nt b checked
	
	bool scope=check_scope(stk);
	this->var2="-";//asin - for printing purpose
	this->result="-";
	if(scope)
	{
		print();
	}

	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;
}

bool Code::marker12(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator="read";
	this->var2="0";//assign var 2  to 0 so tht check_scope 9 that this is not used and its scope need nt b checked
	
	bool scope=check_scope(stk);
	this->var2="-";//asin - for printing purpose
	this->result="-";
	if(scope)
	{
		print();
	}

	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;
}

bool Code::marker13(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();//pop the var 1
	this->oprator="if=";
	this->var2="0";//assign var 2  to 0 so tht check_scope 9 that this is not used and its scope need nt b checked
	
	bool scope=check_scope(stk);
	this->var2="1";//asin - for printing purpose
	this->result="-";//at ths stage we do not 9 where to jump this will b done by backpatching
	bkpch_stk.push(line_num);//put line num on backpatch stack
	if(scope)
	{
		print();
	}

	else
	{
		cout<<"\nout of scope variable  ";
		return false;
	}
	//AVLnode * t=new AVLnode();
	return true;
}


bool Code::marker14(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	int a=bkpch_stk.top()-1;//gt line whr bkpch is to b dn
	bkpch_stk.pop();

	int size=70;//size of 1 line in the code genrated

	char num[25];//used to change the number of temprary variable into an array
	itoa(line_num,num,10);//line_num is now in the num
						  //this is to b replaced bk	

	string temp(num);
    //set the output place
	
//	ofstream mcout("code.txt");
//	mcout.seekp(0);
	mcout.seekp(((72*a)+60),ios::beg);//1st move to line whr bkpch,thn move to result portion where current lin num is to b put
	
	mcout.setf(ios::left);
	mcout.width(10);
	mcout.fill(' ');
//	mcout.write(num,10);
	mcout<<temp<<"\n";


//	mcout.close();
	return true;

}

bool Code::marker15(stack <string>& eval_stk , stack <Avltree*>& stk)
{

	
	//arange the back patch stack
	int a=bkpch_stk.top();//gt previous line no as it is to b put above the line no that is to be put in this marker
	bkpch_stk.pop();//pop it temporarily

	bkpch_stk.push(line_num);//push the current line num
	bkpch_stk.push(a);//push the previous that was poped 

	this->oprator="goto";
	this->var1="-";
	this->var2="-";
	this->result="-";

	print();

//	mcout.close();
	return true;

}

bool Code::marker16(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	int a=bkpch_stk.top();//gt line whr bkpch is to b dn
	bkpch_stk.pop();

	int size=70;//size of 1 line in the code genrated

	char num[25];//used to change the number of temprary variable into an array
	itoa(line_num,num,10);//line_num is now in the num
						  //this is to b replaced bk	

	string temp(num);

//we mk these and change the current line no to the preious temporarily and call
//print() and when it return we agin change the line num to original line num

	int temp_line_num=line_num;//assign it to temp var

	line_num=a;//line_num changed to line at whiah it is to be replaced
	this->oprator="goto";
	this->var1=temp;
	this->var2="-";
	this->result="-";

	print();

	line_num=temp_line_num;
	return true;

}

bool Code::marker18(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->oprator="return";
	this->var1="return_offset";
	this->var2="-";
	this->result="-";

	print();

	return true;

}

bool Code::marker19(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	bkpch_stk.push(line_num);//push line whr where goto will be diverted
	return true;

}

bool Code::marker20(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	//1st arrange stack bcoz the var needed here is pushed below 1
	//element ,so pop the above 1 and get the required and 
	//then push the poped 1 back again
	
	int a=bkpch_stk.top();//gt line whr bkpch is to b dn
	bkpch_stk.pop();
	
	int use_this=bkpch_stk.top();//this the actual needed var
	bkpch_stk.pop();

	bkpch_stk.push(a);//push thee extra back
	
	char num[25];//used to change the number of temprary variable into an array
	itoa(use_this,num,10);//line_num is now in the num
						  //this is to b replaced bk	

	string temp(num);

//we mk these and change the current line no to the preious temporarily and call
//print() and when it return we agin change the line num to original line num

	this->oprator="goto";
	this->var1=temp;
	this->var2="-";
	this->result="-";

	print();

	return true;

}


bool Code::marker21(stack <string>& eval_stk , stack <Avltree*>& stk)
{

	string reslt(newtemp());

	
	AVLnode * node=new AVLnode(reslt);//make a new node of the new temp variable
	stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
	string sttr("integer");
	node->set_type(sttr);
	
	this->oprator="int_:=";
	this->var1=reslt;
	this->var2=eval_stk.top();
	this->result="-";//result have 9 the name of the new temp variable
	
	print();

	eval_stk.pop();//pop the number at tos
	eval_stk.push(reslt);//push this variable on stack

	return true;
}

bool Code::marker22(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	string reslt(newtemp());

	
	AVLnode * node=new AVLnode(reslt);//make a new node of the new temp variable
	stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
	string sttr("real");
	node->set_type(sttr);
	
	this->oprator="real_:=";
	this->var1=reslt;
	this->var2=eval_stk.top();
	this->result="-";//result have 9 the name of the new temp variable
	
	print();

	eval_stk.pop();//pop the number at tos
	eval_stk.push(reslt);//push this variable on stack

	return true;
}


bool Code::marker24(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	this->oprator="goto";
	this->var1="-";
	this->var2="-";
	this->result="-";

	print();
	return true;
}

bool Code::marker25(stack <string>& eval_stk , stack <Avltree*>& stk)
{
	
	char num[25];//used to change the number of temprary variable into an array
	itoa(line_num,num,10);//temp_counter is now in the num
	

	string temp(num);
	
	this->oprator="goto";
	this->var1=temp;
	this->var2="-";
	this->result="-";

	int temp_li=line_num;
	line_num=1;


	print();

	line_num=temp_li;
	return true;
}

bool Code::marker26(stack <string>& eval_stk, stack <Avltree*>& stk)
{
	this->var2="0";//assign vari 1 to var1
	this->var1=eval_stk.top();//assign vari 1 to var1
	eval_stk.pop();

	bool scope=check_scope(stk);

	if(scope)
	{
		this->oprator="not";
		this->var2="-";

		char num[25];//used to change the number of temprary variable into an array
		itoa(temp_counter,num,10);//temp_counter is now in the num
		temp_counter++;

		string temp(num);
		string rslt("~t");
		string reslt(rslt + temp);
		string type1;

		AVLnode* a=stk.top()->search(stk.top()->getroot(),this->var1);
			
		if(!a)
		{
			type1=get_type(stk,this->var1);
			if(type1=="-1")
			{
				cout<<"\nundeclared var ";
				return false;
			}
		
		}
		else
			type1=a->get_type();
		
		AVLnode * node=new AVLnode(reslt);//make a new node of the new temp variable
		stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
		//string sttr("");
		node->set_type(type1);
		
		this->result=reslt;
		eval_stk.push(reslt);
	}
		
	else 
	{		
		cout<<"\ntype mismatch eror in operands "<<var1<<" & "<<var2;
		return false;
	}

	
	print();
	return true;

}

bool Code::marker27(stack <string>& eval_stk, stack <Avltree*>& stk)
{
	bool a=check_global(stk,eval_stk.top());
	if(a)
		return true;
	else
	{
		cout<<"\nthis function '"<<eval_stk.top()<<"' does nt exist ";
		return false;
	}

}

bool Code::marker28(stack <string>& eval_stk, stack <Avltree*>& stk)
{
	this->oprator="end";
	this->var1="-";
	this->var2="-";
	this->result="-";

	print();
	return true;
}
	
int Code::func(stack<string>& eval_stk,stack<Avltree*> stk,stack<Avltree*> func_stack,int line)
{

	stack<string> tmp;
	stack<string> tmp1;
	int count=0;
	while(eval_stk.top() != "&")
	{
		tmp.push(eval_stk.top());
		tmp1.push(eval_stk.top());

		count++;
		eval_stk.pop();
	}
	eval_stk.pop();//pop &

	string name=eval_stk.top();//nmae of the function

	eval_stk.push("&");
	
	while(!tmp1.empty())
	{
		eval_stk.push(tmp1.top());
		tmp1.pop();
	}


	this->oprator="push_ari";
	this->var1=name;
	this->var2="-";
	this->result="-";

	print();

	this->oprator="function_name";
	this->var1=name;
	this->var2="-";
	this->result="-";

	print();

	char num[25];//used to change the number of temprary variable into an array
	itoa(line+count,num,10);//line_num is now in the num
						  //this is to b replaced bk	

	string temp1(num);

	this->oprator="return_offset";
	this->var1=temp1;
	this->var2="-";
	this->result="-";

	print();
	
	this->oprator="static_link";
	this->var1="1";
	this->var2="-";
	this->result="-";

	print();

	this->oprator="dynamic_link";
	this->var1="1";
	this->var2="-";
	this->result="-";

	print();

	//mcout.close();
	stack<Avltree*> temp;
	while(!stk.empty())
	{
		temp.push(stk.top());
		stk.pop();
	}

//	string name=eval_stk.top();//name of function

	AVLnode * aa=temp.top()->search(temp.top()->getroot(),name);	
	
	int ln=aa->func_strt;
	while(!temp.empty())
	{
		//aa->param.push_back(temp_stk.top());
		//aa->no_param++;
		stk.push(temp.top());
		temp.pop();
	}
	
	for(int i=0;i < aa->param.size();i++ )
	{
		
		if(tmp.empty())
		{
			cout<<"\nno of arguements varying  ";
			return -1;
		}

		string type1=aa->par_type[i];
		string type2;
		AVLnode*  aaa=stk.top()->search(stk.top()->getroot(),tmp.top());
		if(aaa)
			type2=aaa->get_type();
		else
			type2=get_type(stk,tmp.top());

		if(type2=="-1")
		{
			cout<<"\nundeclared var ";
			return -1;
		}
		this->oprator="param";
		this->var1=aa->param[i];
		this->var2=tmp.top();
		this->result="-";

		if(type1 != type2)
		{
			string temp_var1;
			string temp_operator=this->oprator;
			string temp_var2;
			string rr("integer");
			string s=newtemp();
			
			AVLnode * node=new AVLnode(s);//make a new node of the new temp variable
			stk.top()->insert(stk.top()->getroot(),node);//insert this node to the tree of this function
			node->set_type(type1);

			if(type1==rr)
			{
				this->oprator="toInt";
				type2="integer";
			}
			else
			{
				this->oprator="toReal";
				type2="real";
			}
			this->result=s;
			this->var2=tmp.top();			
			temp_var1=this->var1;
			//temp_var2=this->var2;

			this->var1=this->var2;
			this->var2="-";
			

			//print();
			
			this->oprator=temp_operator;
			this->var2=s;
			this->var1=temp_var1;
			this->result="-";
			//type2="real";
		}
		print();
		tmp.pop();
	}
	
		if(!tmp.empty())
		{
			cout<<"\nno of arguements varying  ";
			return -1;		
		}
	
		itoa(count,num,10);//line_num is now in the num
						  //this is to b replaced bk	

		temp1=num;

		itoa(ln,num,10);//line_num is now in the num
						  //this is to b replaced bk	

		string temp2(num);

		this->oprator="call_function";
		this->var1=temp2;
		this->var2=temp1;
		this->result="-";

		print();

		this->oprator="pop_ari";
		this->var1=name;
		this->var2="-";
		this->result="-";

		print();


	return count;
}