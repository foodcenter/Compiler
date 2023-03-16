////#include "AVLnode.h"
#include "Avltree.h"
//#include "id.h"
//#include "ary.h"
//#include "func.h"
//#include "pars.h"
//#include "lex.h"
#include "math.h"
#include <string>
//enum boolean{false,true};
//static int rollno=0;

static int dx=0;
static int dy=0;


/*this function is used to return maximum two integers,used to return max of
two heights
*/
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}



/*this function returns height of node
for which it is called,depending whether
is leaf or not,if leaf '0' is returned
otherwise height of that node is returned that
was previously set.
*/

int Avltree::height(AVLnode* ta) const
{
	int a= ta==NULL? 0:ta->height;
	return a;
}


 /*gives single left rotation,the middle
value comes as parent other two depending upon
their value r shifted to left and right children
if the rotating node is root,then root is again set
*/


void Avltree :: setroot(AVLnode * k)
{
	this->root=k;
}

/*
Insert function is the same as given by sir no special changes made,
the student pointer is passed it's id is checked and the node is placed at
it's proper place,

(1)afterwards Balance Factor is checked and the corresponding rotations
   are called

(2)simple left rotation
(3)double left rottion
(4)after any insertion the height of every node in the path is set again,
   the path that was used to reach that place where node is inserted
*/


					//            s is the node to b inserted 
void Avltree::insert(AVLnode* &t,AVLnode* &s)//1st time "t" is the root of the tree, afterwrds it is the node to b compared with
{
	//static int index=0;
	if(t==NULL)
	{
		t=s;
//		AVLnode * v=this->getroot();
//		AVLnode * u=this->Findparent(v,st);
	}
	else
	{
		if(s->get_name() <  t->get_name() )
		{
			insert(t->left,s);
			//(1)
			if((height(t->left))-(height(t->right))>1 || (height(t->left))-(height(t->right))<-1)
			{ 
				if(s->get_name() < t->left->get_name())
				{
					rotatewithleft(t);
				}

				else
				{
					doublewithleft(t);
				}
			}
		}
		else if(t->get_name() < s->get_name())
			{

				insert(t->right,s);
				if((height(t->left))-(height(t->right))>1 || (height(t->left))-(height(t->right))<-1)
				{
					 if(t->right->get_name() < s->get_name())
					 {
							rotatewithright(t);
						   
					 }
					 else
					 {
							  //	graph_rep_double_right_rotation(t);
							doublewithright(t);
						 //	print_in_node(t->right);

					}
				}
			}
			 
		else if(t->get_name() == s->get_name())	// in this case add it to the list.
			{
				//t->lineNum.push_back(s->get_name()); //temporarily name is added in the list, afterwards, we will add linenumber
				t->lineNum.push_back(s->get_name());
			}
		else
				return;

		//end else
	}//end main else
	  //(4)
	t->height=max(height(t->left),height(t->right))+1;
}

void Avltree::rotatewithleft(AVLnode* &k2)
{
	AVLnode* k1=k2->left;

	k2->left=k1->right;


	k1->right=k2;
	
	k2->height=max(height(k2->left),height(k2->right)) + 1;
	k1->height=max(height(k1->left),height(k1->right)) + 1;

	if(k2 == this->root)
		this->root=k1;
	k2=k1;

}  


void Avltree::rotatewithright(AVLnode* &k2)
{
	AVLnode* k1=k2->right;

	k2->right=k1->left; //bring k2 to (100,80)
	k1->left=k2;

	k2->height=max(height(k2->left),height(k2->right)) + 1;
	k1->height=max(height(k1->left),height(k1->right)) + 1;



	if(k2==this->root)
		this->root=k1;


	k2=k1;
}

void Avltree::doublewithright(AVLnode* &k3)
{
	rotatewithleft(k3->right);
	rotatewithright(k3);
}

/*
same as above only difference is the inverse rotations
*/

void Avltree::doublewithleft(AVLnode* &k3)
{
	rotatewithright(k3->left);
	rotatewithleft(k3);
}


void Avltree::print(AVLnode* t)
{
	if(t)
	{
		print(t->left);
		cout<<t->get_name()<<"\n";
		print(t->right);
	}
	
	return;
}


bool Avltree::set_type(string id,string type)// this will set the type of the id 
{
	AVLnode* a=search(this->root , id);

	if(a != 0)
	{
//		a->set_type(type);
		return true;
	}

	return false;//this node not found
}
//AVLnode*&  ret;//this is currentle used to return rhe found node

AVLnode*& Avltree::search(AVLnode* t,string id1)//first time will b root
{
	static AVLnode* ret;//this is currentle used to return rhe found node
	static AVLnode* ret1=0;
	if(!t)// if root is not yet specified
		return ret1;

	if(t->get_name() == id1)
	{
		return t;
	}
	
	else
	{
		if(t->get_name() < id1)
		{

			if(t->right)//cheks if nodes has finished on right side and value still not found
				ret=search(t->right,id1);
			else
			{
				return ret1;
			}
		}
		else
		{
			if(t->get_name() > id1)
				if(t->left) //cheks if nodes has finished on left side and value still not found
					ret=search(t->left,id1);
			else
			{
				return ret1;
			}
		}
	}
	return ret;
}

bool Avltree::search1(AVLnode* t,string id1)//first time will b root
{

	while(t)
	{
		if(t->get_name() == id1)
		{
			return true;
		}

		else
		{
			if(t->get_name() < id1)
			{
				if(t->right)//cheks if nodes has finished on right side and value still not found
					t=t->right;
				else
					return false;	
			}
			
			else
			{
				if(t->get_name() > id1)
					if(t->left) //cheks if nodes has finished on left side and value still not found
						t=t->left;
				else
					return false;
			}
		}
		
			
	}
	return false;
}


/*
   1st of all this function finds the node to be deleted, then cheks
   whether it has any childs or not,if leaf then simply deleted,otherwise
   finds max of it's left replaces the value and the student pointer
   delets that displaced node and it's student pointer,always a leaf node is
   deleted,so we have to only set the parent left or riught node to 'NULL'
   no pointers has to be changed,whgile coming back (returning) after
   deleting,the height of each node in thAT PATH IS set agin,also the
   BF is cheked and the corresponding rotations made

*/


/*
this is a utility function traverses in right ti8ll it gets a null
the last node in the right will bear the max val and that one is returned

*/
AVLnode* Avltree::max1(AVLnode* q) const
{

	while(q->right)
	{
		q=q->right;
	}
	return q;
}

int select=0;


void Avltree::destroy(AVLnode* de)
{
	//cout<<"\ninside destroy";
	if(de->left)
	{
		destroy(de->left);
		de->left=NULL;
	}

	if(de->right)
	{
		destroy(de->right);
		de->right=NULL;
	}


    if(de->left==NULL && de->right==NULL)
    {
	delete de;
	//delete rep;

    }

}


Avltree::~Avltree()
{

	destroy(this->root);


}



AVLnode * Avltree :: Findparent(AVLnode * s)
{
/*	if(s->left->id == t.get_id() || s->right->id== t.get_id())
	{
		return s;
	}
	if(t.get_id() < s->id)
	{
		return Findparent(s->left,t);
	}
	if(t.get_id() > s->id)
	{
		return Findparent(s->right,t);
	}
*/	return 0;
}
