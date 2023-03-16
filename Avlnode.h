#include <string>
#include <list>
#include <vector>
//#include "Graphnod.h"


#ifndef AVLNODE_H
#define AVLNODE_H

class avltree;//forward declaration
//class student;//forward declaration

using namespace std;

class AVLnode
{
	friend class Avltree;

	public:
		AVLnode* left;
		AVLnode* right;

		string name;//name of the lexeme
		string type;//type of the lexeme
		
		vector<string> param;
		vector<string> par_type;

		int no_param;
		int func_strt;
		int height;	
		
									// name       // type
		AVLnode(string n)//By default the constructor sets all values to zero
		{
			this->left=0;
			this->right=0;
			this->name=n;
			this->type=n;
			this->height=0;
			this->no_param=0;
			this->func_strt=0;
		}

		AVLnode()//By default the constructor sets all values to zero
		{
			string n(" ");
			this->left=0;
			this->right=0;
			this->name=n;
			this->type=n;
			this->height=0;
			this->no_param=0;
			this->func_strt=0;
		}


		void set_name(string s){this->name=s;}
		string get_name(){return this->name;}


		void set_type(string s){this->type=s;}
		string get_type(){return this->type;}

		void set_left(){this->left=0;}
		//string get_name(){return this->name;}

		void set_right(){this->right=0;}
		//string get_name(){return this->name;}


	//	~AVLnode(){}


};

#endif