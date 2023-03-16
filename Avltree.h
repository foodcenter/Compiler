#include <iostream>
#include "AVLnode.h"
//#include <conio>
//#include <stdlib>
//#include "LEX.H"
//#//include "pars.h"


#ifndef AVLTREE_H
#define AVLTREE_H


class Avltree
{
	private:
		string name;//name of the function whose tree this is;
		AVLnode* root;
		AVLnode* max1(AVLnode*) const;//utility function returns max node after the node given as input

	public:
		Avltree(AVLnode* rot=0)
		//:AVLnode()
		{
//			string n(" ");
			root=rot;
//			rot->set_left();
//			rot->set_right();
//			rot->set_name(n);
//			rot->set_type(n);
		}//,avlnode* lft,avlnode* rit,int idn,STU* std)
		
		void set_name(string st){this->name=st;}
		string get_name(){return this->name;}

		void insert(AVLnode* &,AVLnode* &);//root n node to b inserted
		void rotatewithleft(AVLnode* &k2);
		void rotatewithright(AVLnode* &k2);
		void doublewithleft(AVLnode* &k3);
		void doublewithright(AVLnode* &k3);
		bool Avltree::search1(AVLnode*,string);//first time will b root




		AVLnode*& getroot(){return this->root;}
		AVLnode*& search(AVLnode*,string);
		int height(AVLnode*) const;

		AVLnode * Findparent(AVLnode * s);
		void print(AVLnode*);

		void setroot(AVLnode * k);

		int deletea(int,AVLnode*);
		void destroy(AVLnode* de);

		bool set_type(string,string);//set the type to the given id return true on success and false on unsuccessful


		//Avltree(AVLnode* rot=0){root=rot;}//,avlnode* lft,avlnode* rit,int idn,STU* std)
		
		~Avltree();
};

#endif
