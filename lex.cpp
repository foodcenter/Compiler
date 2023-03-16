#include "lex.h"
#include "pars.h"

using namespace std;

Lex::Lex(char* add,char * add1)
{
	line_no=1;
	nextchar=0;
	lexeme_beginning=0;
	lexeme_end=0;
	state=0;
	flag=0;
//	read_ptr=0;
	error_id=false;
	error_num=false;
	read_flag=true;
	buf_flag=true;
	new_tree=false;
	size_buf=0;
	
	int aa=strlen(add);
	adrs=new char[aa];
	strcpy(adrs,add);


	aa=strlen(add1);
	dest_adr=new char[aa];
	strcpy(dest_adr,add1);
	
	ifstream mcin(adrs,ios::in);

	if(!mcin)
	{
		cout<<"input file could not be opened program will close\n";
		exit(0);
	}
	mcin.seekg(0,ios::end);
	size_buf=mcin.tellg();			//  This is working perfectly. (Ali)
//	cout<<j<<" =size of file\n";

	buffer1=new  char[size_buf];
	for(int ii=0;ii<size_buf;ii++)
		buffer1[ii]=' ';
	//buffer1[size_buf-1]=0;

	mcin.close();
	

}

Lex::~Lex()
{
	/*delete [] buffer1;
	delete [] adrs;
	delete [] dest_adr;*/
}


void Lex :: read_fil()
{
	//cout<<"give the name of the file to be opened\n";
	//cin>>filnam;

	ifstream mcin(adrs,ios::in);

	if(!mcin)
	{
		cout<<"input file could not be opened program will close\n";
		exit(0);
	}
/*	mcin.seekg(,ios::beg);
/*	int j=mcin.tellg();
	cout<<j<<" =size of file\n";

	char *ar=new char[j];

	delete []ar;
	
*/	char ch=0;//temp var used to assign value to the buffer[i]
/*	for(int i=0;!mcin.eof() ; i++)
	{
		
		mcin>>ch;
		if(ch==0)
			buffer1[i]=' ';
		else
			buffer1[i]=ch;
		//mcin>>buffer1[i];
	}
	//buffer1[i-1]=0;
	//	mcin.read((char*)&ac,sizeof(ac));
	*/mcin.read(buffer1,size_buf);//buffer1[size_buf]=0;
	mcin.close();
}

int Lex::insert_st()//may return different symbls depending 
{					//on whther symbl alredy presnt or not
	return 1;
}
void Lex::rit_fil(char * c,int siz,int token_num)//c is the name of the token and size is the size of the array
{
	ofstream mcout(dest_adr,ios::app);

	
	if(!mcout)
	{
		cout<<"\noutput file could not b opened\n";
		exit(0);
	}

	if(token_num != 0)
	{
		int size=lexeme_end - lexeme_beginning + 2;

		char * temp=new char[size];
		//int ii=strlen(temp);
		//for(int j=0;j<ii;j++)
		//	temp[j]=' ';
		for(unsigned int i=0;i<size-1;i++)
			temp[i]=buffer1[lexeme_beginning+i];
		temp[size-1]=0;
		mcout.setf(ios::left);
		mcout.width(30);
		mcout.fill(' ');
		//mcout.write(temp,(size-1));
		mcout<<temp;
		//mcout.write("     ",5);

		delete temp;
	}

	else
	{
		char  *temp=new char[8];
		temp[0]='/';
		temp[1]='*';
		temp[2]='.';
		temp[3]='.';
		temp[4]='.';
		temp[5]='*';
		temp[6]='/';
		temp[7]=0;
	
		mcout.setf(ios::left);
		mcout.width(30);
		mcout.fill(' ');
		//mcout.write(temp,(size-1));
		mcout<<temp;
		//mcout.write("     ",5);
		delete temp;
	}
	mcout.setf(ios::left);
	mcout.width(20);
	mcout.fill(' ');
	//mcout.write(c,siz);
	mcout<<c;
	//mcout.write("     ",5);
	//int num=get_number(c,siz);// get number returns the num of the token
	char no[3];
	if(token_num==40 || token_num==0)
	{
		no[0]='-';
		no[1]=0;
	}
	else itoa(token_num,no,10);
	mcout.setf(ios::left);
	mcout.width(4);
	mcout.fill(' ');
	//mcout.write(no,2);
	mcout<<no;
	mcout.write("\n",1);
	mcout.close();

}

int Lex::chk_kw()
{
	const char *arr[28]={ "procedure", " ", " ", " ", "integer", " ", " ",
					"function", " ", "program", "real", "and", "while",
					"else", " ", "array", "then", "mod", "if", " ", "do",
					"of" , "var", " ", " ", " ", " ", "or"};

	int array[28]={25,0,0,0,21,0,0,19,0,26,27,15,30,18,0,16,28,22,20,0,
					17,23,29,0,0,0,0,24};
	int size=lexeme_end - lexeme_beginning + 2;

	int sum=0;//used to sotr the sum of asci to chk agnst kwrds
	char * temp=new char[size];
	for(unsigned int i=0;i<size-1;i++)
			temp[i]=tolower(buffer1[lexeme_beginning+i]);
		temp[size-1]=0;

	for(int j=0;temp[j] != 0;j++)
			sum=sum+temp[j];

	sum=(sum%57)/2;
	
	//int y=strlen(arr[sum]);
	int y=strcmpi(temp,arr[sum]);
	delete []temp;

	if(y==0) return array[sum];
	else return 0;
}

int Lex::get_number(char * c,int size)
{
	/* temporarily returning this afterwards rite the code*/
	return 10;
} 


char Lex::next_char()
{
	if(nextchar < size_buf-1)
	{
		if(buffer1[nextchar] == 10) line_no++;

		return buffer1[nextchar++];
	
	}
	else 
	{
		buf_flag=false;
		return ' ';
	}
	/*if(nextchar == 1024)
	//{
		nextchar=0;
		read_fil(read_ptr++);
		return buffer1[nextchar++];
	}*/
}

void Lex::retract(int i)
{
	nextchar=nextchar-i;
} 

bool Lex::is_digit(char c)
{
	int a=(int) c;

	if(a<58 && a>47)
		return true;
	else
		return false;
}

bool Lex::is_letter(char c)
{
	int a=(int) c;

	if((a<91 && a>64) || (a<123 && a>96) )
		return true;
	else

		return false;
	
}

bool Lex::is_separator(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/' ||c=='%' || c=='(' || c=='[' || c=='{' || c==';' || c==':' || c==' ' || c=='\n' || c=='<' || c=='>' || c=='=' || c==')' ||c==']' || c==',' )
		return true;
	else 
		return false;

}

char* Lex::get_lexeme()
{
		int size=lexeme_end - lexeme_beginning + 2;

		char* temp=new char[size];
		//int ii=strlen(temp);
		//for(int j=0;j<ii;j++)
		//	temp[j]=' ';
		for(unsigned int i=0;i<size-1;i++)
			temp[i]=buffer1[lexeme_beginning+i];
		temp[size-1]=0;

		return temp;

}


int Lex::analyse(stack<Avltree*> &stk,stack<string> &evaluate_stack)
{
//	static AVltree a;
	static char c=' ';
	static int ii=0;
	while(1)
	{
		switch(state)
		{
			case 0:	
				if(read_flag)
					c=next_char();
				if(c==9 || c==10 || c==32)
				{
					//if(c==10) line_no++;
						
					state = 0;
					read_flag=true;
					if(buf_flag==false)
					{
					//////////////
						
					/////////////		///
						return 50;

					}
					//lexeme_beginning++;
				}
				else
					state=get_state(c);
					lexeme_beginning=nextchar-1;

				break;

			case 1:
				//lexeme_beginning=nextchar-1;//the beginning of this lexeme 
				c=next_char();
				if(c == '=') state=2;
				else if(c == '>') state=3;
				else if(c == '<') state=39;

				else state=4;

				break;

			case 2:
				/* 
				   the code 4 saving and the num. pattern and symbol table etc.
				*/
				lexeme_end=nextchar - 1;
				rit_fil("less_equal",11,7);
				evaluate_stack.push("<=");
				tokens.push_back(7);
				state=0;
				read_flag=true;
				return 7;
			
			case 39:
				/* 
				   the code 4 saving and the num. pattern and symbol table etc.
				*/
				lexeme_end=nextchar - 1;
				rit_fil("stream_ex",9,41);
				tokens.push_back(41);
				state=0;
				read_flag=true;
				return 41;
			
			case 3 :
				lexeme_end=nextchar - 1;
				rit_fil("not_equal",10,5);
				evaluate_stack.push("<>");
				tokens.push_back(5);
				state=0;
				read_flag=true;
				return 5;

			case 4:
				read_flag=false;
				lexeme_end=nextchar - 2;
				rit_fil("less_then",10,6);
				evaluate_stack.push("<");
				tokens.push_back(6);
				state=0;
				
				return 6;

			case 5:
				lexeme_end=nextchar - 1;
				rit_fil("equal",6,4);
				evaluate_stack.push("=");
				tokens.push_back(4);
				state=0;
				read_flag=true;
				return 4;
				
			case 6:
				c=next_char();
				if(c == '=') state=7;
				else if(c == '>') state=40;
				else state=8;
				break;
				
			case 7:
				lexeme_end=nextchar - 1;
				rit_fil("greater_equal",14,8);
				evaluate_stack.push(">=");
				tokens.push_back(8);
				state=0;
				read_flag=true;
				return 8;
			
			case 40:
				lexeme_end=nextchar - 1;
				rit_fil("stream_ins",10,42);
				tokens.push_back(42);
				state=0;
				read_flag=true;
				return 42;
				
			case 8:
				read_flag=false;
				
				lexeme_end=nextchar - 2;
				rit_fil("greater",8,9);
				evaluate_stack.push(">");
				tokens.push_back(9);
				state=0;
				return 9;
			case 9:
				//lexeme_beginning=nextchar-1;//the beg. of lexeme is saved in order to compare the lexeme against the keywords
				c=next_char();
				if(is_digit(c) || is_letter(c)) state=9;
				else 
					if(is_separator(c))state =10;
					else
					{
						error_id=true;
						state=9;
					}
				break;

			case 10:
				read_flag=false;
				lexeme_end=nextchar-2;
				if(!error_id) 
				{
					int a=chk_kw();
					if(a == 0)//in case it is not a keyword
					{
						bool t=false;
						string s(get_lexeme());
					
						//t=stk.top()->search(stk.top()->getroot(),s);//chk if already dded or not

						if(!t && add_st)
						{
							//string tt(" ");

							AVLnode * node = new AVLnode(s);
						
							insert_st();//stub 4 ST
							t=stk.top()->search1(stk.top()->getroot(),s);
							if(!t)
								stk.top()->insert(stk.top()->getroot(),node);
							else
							{
								cout<<"double declaration of lexeme: "<<s<<"  ";
								return 51;//string repition error
							}
						}

						evaluate_stack.push(s);
						
						rit_fil("id\0",3,1);

						tokens.push_back(1);
						state=0;
						return 1;
					}
					else// in case it is a keywrd
					{
						int size=lexeme_end - lexeme_beginning + 2;

						char * temp=new char[size];
						for(unsigned int i=0;i<size-1;i++)
							temp[i]=buffer1[lexeme_beginning+i];
						temp[size-1]=0;

//						insert_st();//stub 4 St
						
						string s1("function");
						string s2("procedure");
						string s3(temp);
						string s4("or");
						string s5("and");
						string s6("mod");

					/*	if(s3==s1 || s3==s2)//if a function a procedure strts push a new avltree on top
						{
							Avltree* t=new Avltree();
							stk.push(t);
						}

					*/	if(s3==s4 || s3==s5 || s6==s3)
						{
							evaluate_stack.push(s3);
						}
						
						rit_fil(temp,size,a);
						tokens.push_back(a);
						state=0;
						delete []temp;
						return a;
					}
				}
				else
				{
					rit_fil("error\0",6,40);
					tokens.push_back(40);
					error_id=false;
					state=0;

					///////*
					int size=lexeme_end - lexeme_beginning + 2;

					char * temp=new char[size];
					for(unsigned int i=0;i<size-1;i++)
						temp[i]=buffer1[lexeme_beginning+i];
					temp[size-1]=0;

					cout<<"\nthe wrong lexeme is:"<<temp<<"\n";
					delete temp;

					///////*/
					return 40;
				}


				// check 4 key word etc here

			case 11:
				c=next_char();
				if(is_digit(c)) state=11;
				else if(c=='.') state=13;
				else if(c== 'E') state=15;
				else if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' ||  c==';' || c==':' || c==' ' || c=='\n' || c=='<' || c=='>' || c=='=' || c==')' ||c==']' || c=='.')
						state=12;
					 else
					 {
						error_num=true;
						state=11;
					 }	
				break;

			case 12:
				read_flag=false;
				lexeme_end=nextchar - 2;
				if(!error_num)
				{
					rit_fil("int_num",8,3);
					//char num[25];//used to change the number of temprary variable into an array
					//itoa(use_this,num,10);//line_num is now in the num
						  //this is to b replaced bk	

					string temp(get_lexeme());
					evaluate_stack.push(temp);

					tokens.push_back(3);
					state=0;
					return 3;
				}

				else
				{
					rit_fil("error_num",10,40);
					tokens.push_back(40);
					state=0;
					error_num=false;
					return 40;		
				}

			case 13:
				c=next_char();
				if(is_digit(c)) state=14;
				else 
				{
					if(c=='.')
					{
						nextchar=nextchar-1;
						state=12;
					}
				
					else 
					{
							error_num=true;
							state=14;
					 }	
				}

				//else it should be some error code or like this here
				break;

			case 14:
				c=next_char();
				if(is_digit(c)) state=14;
				else if(c=='E') state=15;
				else if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' ||  c==';' || c==':' || c==' ' || c=='\n' || c=='<' || c=='>' || c=='=' || c==')' ||c==']' )
						state=18;
					 else
					 {
						error_num=true;
						state=14;
					 }	
				
				break;

			case 15:
				c=next_char();
				if(c=='+' || c=='-' ) state=16;
				else if(is_digit(c)) state=17;
				     else
					 {
						error_num=true;
						state=17;
					 }
				break;

			case 16:
				c=next_char();
				if(is_digit(c)) state=17;
				else
				{
					error_num=true;
					state=17;
				}

				break;

/*			case 17:
				c=next_char();
				if(is_digit(c)) state=17;
				else if(c==' ' || c=='+' || c=='-' || c=='*' || c=='/' || c=='(' ||  c==';' || c==':' || c==' ' || c=='\n' || c=='<' || c=='>' || c=='=' || c==')' ||c==']' )
						state=18;
						
					 else
					 {
						error_num=true;
						state=17;
					 }

				break;
*/
			case 17:
				if(c==' ' || c=='+' || c=='-' || c=='*' || c=='/' || c=='(' ||  c==';' || c==':' || c==' ' || c=='\n' || c=='<' || c=='>' || c=='=' || c==')' ||c==']' )
						state=18;
				else 
				{
					c=next_char();
					if(is_digit(c)) state=17;

					 else
					 {
						error_num=true;
						state=17;
					 }

				}
				break;

			case 18:
				read_flag=false;
				lexeme_end=nextchar - 2;
				if(!error_num)
				{
					rit_fil("float_num",10,2);
					tokens.push_back(2);

					string temp(get_lexeme());
					evaluate_stack.push(temp);

					state=0;
					return 2;
				}

				else
				{
					rit_fil("error_num",10,40);
					tokens.push_back(40);
					state=0;
					error_num=false;

					//////////*

					int size=lexeme_end - lexeme_beginning + 2;

					char * temp=new char[size];
					for(unsigned int i=0;i<size-1;i++)
						temp[i]=buffer1[lexeme_beginning+i];
					temp[size-1]=0;

					cout<<"\nthe wrong lexeme is:"<<temp<<"\n";
					delete temp;
					///////////*/
					return 40;
				}

		/*	case 19:
				lexeme_end=nextchar-1;
				rit_fil("{",2,34);
				tokens.push_back(34);

				Avltree* t=new Avltree();
				stk.push(t);

				state=0;
				read_flag=true;
				return 34;

		*/	case 20:
				lexeme_end=nextchar-1;
				rit_fil("}",2,35);
				tokens.push_back(35);
				state=0;
				read_flag=true;
				return 35;
			
			case 21:
				lexeme_end=nextchar-1;
				rit_fil("[",2,36);
				tokens.push_back(36);
				state=0;
				read_flag=true;
				return 36;
				
			case 22:
				lexeme_end=nextchar-1;
				rit_fil("]",2,37);
				tokens.push_back(37);
				state=0;
				read_flag=true;
				return 37;
			
			case 23:
				lexeme_end=nextchar-1;
				rit_fil("(",2,32);
				tokens.push_back(32);
				state=0;
				read_flag=true;
				return 32;
			
			case 24:
				lexeme_end=nextchar-1;
				rit_fil(")",2,33);
				tokens.push_back(33);
				state=0;
				read_flag=true;
				return 33;
			
			case 25:
				lexeme_end=nextchar-1;
				rit_fil(",",2,31);
				tokens.push_back(31);
				state=0;
				read_flag=true;
				return 31;
			
			case 26:
				lexeme_end=nextchar-1;
				rit_fil(";",2,38);
				tokens.push_back(38);
				state=0;
				read_flag=true;
				return 38;
			
			case 27:
				c=next_char();
				if(c=='=') state=36;
				else state=37;

				break;
			case 28:
				c=next_char();
				if(c=='*') 
					state=29;
				else state=35;

				break;

			case 29:
				c=next_char();
				if(!buf_flag)
					return 50;
				//if(c==10)
				//	line_no++;

				if(c != '*') state=29;
				else state=30;

				break;

			case 30:
				c=next_char();
				if(c == '/')
					state=31;
				else state=29;

				break;


			case 31:
				lexeme_end=nextchar-1;
				rit_fil("skip",5,0);
				state=0;
				//return 0;
				break;

			case 32:
				lexeme_end=nextchar-1;
				rit_fil("+",2,10);
				
				if(1)//put the plus symbol on the evaluate stack
				{
					string plus("+");
					evaluate_stack.push(plus);
				}
				
				tokens.push_back(10);
				state=0;
				read_flag=true;
				return 10;

			case 33:
				lexeme_end=nextchar-1;
				rit_fil("-",2,11);
				if(1)//put the - symbol on the stack
				{
					string minus("-");
					evaluate_stack.push(minus);
				}
				tokens.push_back(11);
				state=0;
				read_flag=true;
				return 11;

			case 34:
				lexeme_end=nextchar-1;
				rit_fil("*",2,12);
				evaluate_stack.push("*");
				tokens.push_back(12);
				state=0;
				read_flag=true;
				return 12;
			
		    case 35:
				read_flag=false;
				lexeme_end=nextchar-2;
				evaluate_stack.push("/");
				rit_fil("/",2,13);
				tokens.push_back(13);
				state=0;
				return 13;

			case 36:
				lexeme_end=nextchar-1;
				rit_fil(":=",3,14);
				tokens.push_back(14);
				state=0;
				read_flag=true;
				return 14;
			
			case 37:
				read_flag=false;
				lexeme_end=nextchar-2;
				rit_fil(":",2,39);
				tokens.push_back(39);
				state=0;
				return 39;
			
			case 38:
				c=next_char();
				if(!buf_flag)
				{
					/////////
					int size=lexeme_end - lexeme_beginning + 2;

					char * temp=new char[size];
					for(unsigned int i=0;i<size-1;i++)
						temp[i]=buffer1[lexeme_beginning+i];
					temp[size-1]=0;

					cout<<"\nthe wrong lexeme is:"<<temp<<"\n";
					delete temp;

					//////////////////////////
					return 50;

				}
				if(is_separator(c))
				{
					read_flag=false;
					lexeme_end=nextchar-1;
					rit_fil("error\0",6,40);
					tokens.push_back(40);
					state=0;	int size=lexeme_end - lexeme_beginning + 2;
					
					//////////////
					char * temp=new char[size];
					for(unsigned int i=0;i<size-1;i++)
						temp[i]=buffer1[lexeme_beginning+i];
					temp[size-1]=0;

					cout<<"\nthe wrong lexeme is:"<<temp<<"\n";
					delete temp;
					/////////////////////
					return 40;
				}

				else state=38;

			break;

			
			case 41:
				lexeme_end=nextchar - 1;
				rit_fil("not",3,43);
				tokens.push_back(43);
				state=0;
				read_flag=true;
				return 43;

			case 42:
				c=next_char();
				if(c == '.') state=43;
				else state=38;
				break;
				
			case 43:
				lexeme_end=nextchar - 1;
				rit_fil("array_op",8,44);
				tokens.push_back(44);
				state=0;
				read_flag=true;
				return 44;
				
			case 19:
				lexeme_end=nextchar-1;

				//cout<<stk.top()->getroot()->get_name()<<"\n";
				//stk.top()->print(stk.top()->getroot());
				//ii=0;

//				cout<<"waiting";
//				cin>>ii;
				cout<<"\n";

				rit_fil("{",2,34);
				tokens.push_back(34);
				state=0;
				read_flag=true;
				return 34;

			//default:
			//	cout<<"this string is not recognized as valid.\n";
			//	return 50;
		}//end switch
	}//end while
}//end func


int Lex::get_state(char c)
{
	int start=0;
	if(c == '<') start=1;
	else if(c == '=') start=5;
	else if(c == '>') start=6;

	else if(is_letter(c)) start=9;
	else if(is_digit(c)) start=11;

	else if(c== '{') start=19;
	else if(c== '}') start=20;
	else if(c== '[') start=21;
	else if(c== ']') start=22;
	else if(c== '(') start=23;
	else if(c== ')') start=24;
	else if(c== ',') start=25;
	else if(c== ';') start=26;
	else if(c== ':') start=27;
	else if(c== '/') start=28;
	else if(c =='+') start=32;
	else if(c =='-') start=33;
	else if(c =='*') start=34;
	else if(c =='!') start=41;
	else if(c =='.') start=42;
	else start=38;

	return start;
	
}

void printlist(const list <int> &listref)
{
	if(listref.empty())
		cout<<"list is empty\n";

	else
	{
		ostream_iterator <int> output(cout," " );
		copy(listref.begin(),listref.end(),output);
	}
}

void Lex::print_headings(char * adr)
{
	ofstream mcout(adr,ios::app);
	mcout.setf(ios::left);
	char temp1[7]={"Lexeme"};
	temp1[6]=0;
	mcout.width(30);
	mcout.fill(' ');
		//mcout.write(temp,(size-1));
	mcout<<temp1;
	
	strncpy(temp1,"Token",5);
	temp1[5]=0;
	mcout.width(20);
	mcout.fill(' ');
	mcout<<temp1;

	strncpy(temp1,"Number",6);
	temp1[6]=0;
	mcout.width(4);
	mcout.fill(' ');
	mcout<<temp1;
	
	mcout<<"\n";
	mcout.close();

}

//Avltree * global_tree=new Avltree();
void main(int no,char *args[])
{

	Lex lex1(args[1],args[2]);

	
	lex1.read_fil();
	Avltree *a=new Avltree();

	stack <Avltree*> stk;
	stk.push(a);
	//global_tree=a;

	//lex1.print_headings(args[2]);
	

//	for(int i=0;lex1.getbuf_flag() ;i=lex1.get_lexeme_end())
//		lex1.analyse(stk);

//	printlist(lex1.tokens);
//	cout<<"\n";

	Parser p;
	p.initialiaze(lex1);
	p.parse(lex1,stk);
	


}









