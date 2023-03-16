#include "string"
#include "Avlnode.h"
//#include "Graphnod.h"


#ifndef ARY_H
#define ARY_H


class array : public AVLnode
{
	private:
	
		int lower_limit;
		int upper_limit;

	public:								// name       // type     set by default to 0, n data type as float
		array(AVLnode* lt,AVLnode* rt,string n,string t,int ht,int low_lim=0,int up_lim=0)
			:AVLnode(n)
		//By default the constructor sets all values to zero
		{
			this->lower_limit=low_lim;
			this->upper_limit=up_lim;
		}
};

#endif