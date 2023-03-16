#include <string>
#include <list>
#include "Avlnode.h"
#include "id.h"
//#include "Graphnod.h"


#ifndef FUNC_H
#define FUNC_H


class function : public AVLnode
{
	
	private:
		list < string > parameters_nm;//a list of identifiers is used as the parameter list of the function
		list < string > parameters_tp;//a list of identifiers is used as the parameter list of the function
					 
		
	public:								// name   return  type     set by default to 0, n data type as float
		function(AVLnode* lt,AVLnode* rt,string n,string t,int ht,list < identifier > list)
			:AVLnode(n)
		//By default the constructor sets all values to zero
		{
			this->parameters=list;	
		}

		

};

#endif