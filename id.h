#include "string"
#include "Avlnode.h"
//#include "Graphnod.h"


#ifndef ID_H
#define ID_H


class identifier : public AVLnode
{
	
	private:
	
		union value{int intgr; float flot;}a;

	public:								// name     type    set by default to 0, n data type as float
		identifier(AVLnode* lt,AVLnode* rt,string n,string s,int ht,int g=0,float f=0,bool t=false)
			:AVLnode(s)
		//By default the constructor sets all values to zero
		{
			if(t)// if flag id true then the value given is an integer
				a.intgr=g;
			else
				a.flot=f;
		}

		int get_intgr(){return this->a.intgr;}

		float get_flot(){return this->a.flot;}

		//~AVLnode(){}


};

#endif