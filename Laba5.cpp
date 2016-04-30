// ConsoleApplication30.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class folder;
class file
{
protected:
	string name;
	string info;
public:
	friend folder;
    file(string n, string in)
	{
		name=n;
		info=in;
	}
	void printinfo()
	{
		cout<<info<<endl;
	}
	string copyinfo()
	{
		return info;
	}
	void setinfo(string s)
	{
		this->info=s;
	}
	bool operator==(file & f1)
	{
		if( (name == f1.name) && ( info == f1.info))
			return 1;
		else
			return 0;

	}
};
class folder
{
protected:
	string name;
	vector<folder>v1;
	vector<file>v2;
public:
	folder(void){}
	folder(string n)
	{
		name=n;
	}
	~folder(void){}
	void crfol(string n)
	{
		folder* pnew=new folder(n);
		this->v1.push_back(*pnew);
	}
	void crfile(string n, string inf)
	{
		file* pnew=new file(n,  inf);
		v2.push_back(*pnew);
	} 
	folder* remove(folder* main, string n)
	{
	   folder* item; 
	   item=main;
	   if(main->name != n)
	   { 	  
		 for(int i=0; i<main->v1.size(); i++)
			if(main->v1[i].name==n)
			{
				item=&(main->v1[i]);
				break;
			}
			else
			{
				if(main->v1[i].v1.size() != 0)
				 item=remove(&(main->v1[i]), n);
				if( (item != main) && (item !=&(main->v1[i])))
					break;
			}
	   }
	   return item;
	}
	string get_name()
	{
		  return name;
	}	
	
	file* findfi(folder* main, string n)
	{
		file* ptr=NULL;
		int i=0;
		int k=1;
		while(i<main->v2.size())
		{
			if (main->v2[i].name == n)
			{
		     ptr=&(main->v2[i]);
			 k=0;
			}
			i++;
		}
		if(k)
		{
			i=0;
			while(i<main->v1.size())
			{
				ptr=findfi(&(main->v1[i]), n);
				i++;
			}
		}
		return ptr;

	}
	folder* findfo(folder* main, string n)
	{
		folder* ptr=NULL;
		int i=0;
		int k=1;
		while(i<main->v2.size())
		{
			if (main->v2[i].name == n)
			{
		     ptr=main;
			 k=0;
			}
			i++;
		}
		if(k)
		{
			i=0;
			while(i<main->v1.size())
			{
				ptr=findfo(&(main->v1[i]), n);
				i++;
			}
		}
		return ptr;
	}
	void delfi(folder* ptr1, file* ptr2)
	{
	  for(int i=0; i<ptr1->v2.size(); i++)
		 if(ptr1->v2[i].name == ptr2->name)
			 ptr1->v2.erase(ptr1->v2.begin()+i);
	}
	void delfo(folder* ptr1)
	{
		int i=0;
		while(ptr1->v2.size() != 0)
		 ptr1->v2.erase(ptr1->v2.begin()+i);
		if(ptr1->v1.size() != 0)
		{
			int i=0;
			while(i<ptr1->v1.size())	 
			{
			  delfo(&(ptr1->v1[i]));
			  i++;
			}	    
	 	    i=0;
		    while(ptr1->v1.size() != 0)
		    ptr1->v1.erase(ptr1->v1.begin()+i);	 
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	char a;
	string copy="";
	string name; 
	string cmd=""; 
	string info;
	cout<<"enter the name of the main directory:  ";
	cin>>name;
	folder f(name);
	folder* item;
	item=&f;
	while(cmd != "end")
	{
		cin>>cmd;
		if(cmd == "CFO") // To create the folder(directory)
		{
			cout<<"Enter the name of the directory:  ";
			cin>>name;
			item->crfol(name);
			cout<<"Enter the name of the directory where you want to work: ";
            cin>>name;
			item=item->remove(&f, name);
		}
		else
		if(cmd == "CFI")  // To create the file
		{
			cout<<"Enter name of the file:  ";
			cin>>name;
			cout<<"Enter iformation:  ";
			cin>>info;
			item->crfile(name,info);
		}
		else
		if(cmd == "CD") // To change the installation directory
		{
			cout<<"Enter the name of the directory where you want to work: ";
			cin>>name;
			item=item->remove(&f, name);
		}
		else
		if(cmd == "OF") // To open the file
		{
			cout<<"Enter the name of the file:  ";
			cin>>name;	
			if(item->findfi(&f, name) != NULL)
			  (item->findfi(&f, name))->printinfo();	
			else
              cout<<"this file doesn't exist"<<endl;
		}
		else
		if(cmd == "CP") // To copy from file
		{
			cout<<"Enter the name of the file:  ";
			cin>>name;
			if(item->findfi(&f, name) != NULL)
			  copy=(item->findfi(&f, name))->copyinfo();	
			else
              cout<<"this file doesn't exist"<<endl;
		}
		else
		if(cmd == "IN") // To insert in file
		{
			cout<<"Enter the name of the file:  ";
			cin>>name;
			if(item->findfi(&f, name) != NULL)
			{
				cout<<"Do you want to insert information from your previous file?(Y or N):  ";
			    cin>>a;
				if(a == 'Y')
				 (item->findfi(&f, name))->setinfo(copy);
			    else
			    {
				 cout<<"Enter information:  ";
				 cin>>info;
				 (item->findfi(&f, name))->setinfo(info);
			    }
			}
			else
             cout<<"this file doesn't exist"<<endl;
		}
		else
		if(cmd == "DFI")        // To delete the file
		{
			cout<<"Enter the name of the file: ";
			cin>>name;
			if(item->findfi(&f, name) != NULL)
			   item->delfi(item->findfo(&f, name), item->findfi(&f, name));
			else
               cout<<"this file doesn't exist"<<endl;

		}
		else
		if(cmd == "DFO") // To delete the folder
		{
			cout<<"Enter the name of the folder:  ";
			cin>>name;
			item=item->remove(&f, name);
			item->delfo(item);
		}
		else
		if(cmd != "end")
		 cout<<"enter correct command"<<endl; 
		cout<<"Now you are in the directory   "<<item->get_name()<<endl;
		
	}
	system("pause");
	return 0;
}

