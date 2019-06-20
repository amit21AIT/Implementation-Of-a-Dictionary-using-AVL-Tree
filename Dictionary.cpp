#include <bits/stdc++.h>
using namespace std;
#define MAX 100000
class node
{
	public:	
	string ident,sc,type;
	int lineNo;
	node *next;
	node()
	{
		next=NULL;
	}
	node(string key,string value,string type,int lineNo)
	{
		this->ident=key;
		this->sc=value;
		this->type=type;
		this->lineNo=lineNo;
		next=NULL;
	}
	void print()
	{
		cout<<"\nIdentifier's Name:"<<ident
				<<"\nType:"<<type
				<<"\nScope: "<<sc
				<<"\nLine Number: "<<lineNo<<endl;
	}
};

class SymbolTable
{
	node *head[MAX];
public:
	SymbolTable()
{
		for(int i=0;i<MAX;i++)
			head[i]=NULL;
}
	int hashf(string id);
	bool insert(string id,string sc,string Type,int lineno);
	string find(string id);
	bool deleteRecord(string id);
	bool modify(string id);
};
bool SymbolTable::modify(string id)
{
	int index=hashf(id);
	node *start=head[index];
	if(start==NULL)
		return "-1";
	while(start!=NULL)
	{
		if(start->ident==id)
		{
				cout<<id<<" is present\n";
				cout<<"Enter Scope: ";
				cin>>(start->sc);
				cout<<"Enter Type: ";
				cin>>(start->type);
				cout<<"Enter Line Number: ";
				cin>>(start->lineNo);
			return true;

		}start=start->next;
	}
	return false;
}
bool SymbolTable::deleteRecord(string id)
{
	int index=hashf(id);
	node *tmp=head[index];
	node *par=head[index];
	if(tmp==NULL) 
	{
		return false;
	}
	if(tmp->ident==id && tmp->next==NULL)
	{
		tmp->next=NULL;
		delete tmp;
		return true;
	}
	while(tmp->ident!=id && tmp->next!=NULL)
	{
		par=tmp;
		tmp=tmp->next;
	}
	if(tmp->ident==id&&tmp->next!=NULL)
	{
		par->next=tmp->next;
		tmp->next=NULL;
		delete tmp;
		return true;
	}
	else
	{
		par->next=NULL;
		tmp->next=NULL;
		delete tmp;
		return true;
	}
	return false;
}
string SymbolTable::find(string id)
{
	int index=hashf(id);
	node *start=head[index];
	if(start==NULL)
		return "-1";
	while(start!=NULL)
	{
		if(start->ident==id)
		{
			start->print();
			return start->sc;

		}start=start->next;
	}
	return "-1";
}
bool SymbolTable::insert(string id,string sc,string Type,int lineno)
{
	int index=hashf(id);
	node *p=new node(id,sc,Type,lineno);

	if(head[index]==NULL)
	{
		head[index]=p;
		cout<<"\n"<<id<<"inserted. ";
		return true;
	}
	else
	{
		node *start=head[index];
		while(start->next!=NULL)
			start=start->next;

		start->next=p;
		cout<<"\n"<<id<<"inserted. ";
		return true;
	}
	return false;
}
int SymbolTable::hashf(string id)
{
	int index=0;
	for(int i=0;i<id.length();i++)
	{
		index+=id[i];
	}
	return (index%100);
}
int main() {
	SymbolTable  st;
		int choice,lineno;
		string id,sc,type;
		do
		{
			cout<<"\n------- Symbol Table ------\n"<<"1.Insert variables\n"	<<"2.Find variables\n"<<"3.Delete variables\n"	<<"4.Modify attributes\n"	<<"Enter Your Choice :";
			cin>>choice;
			switch(choice)
			{
			case 1:
				cout<<"Enter Identifer's Name: ";
				cin>>id;
				cout<<"Enter Scope: ";
				cin>>sc;
				cout<<"Enter Type: ";
				cin>>type;
				cout<<"Enter Line Number: ";
				cin>>lineno;
				if(st.insert(id,sc,type,lineno))
					cout<<endl<<id<<" inserted into Symbol Table.";
				else
					cout<<"\nFailed to insert.";
				break;
			case 2:
				cout<<"Enter Identifier to Search: ";
				cin>>id;
				sc=st.find(id);
				if(sc!="-1")
					cout<<" Identifier Is present.\n";
				else
				{
					cout<<"\n Identifier Not Present";
				}
				break;
			case 3:
				cout<<"Enter Identifier to Delete: ";
				cin>>id;
				if(st.deleteRecord(id))
					cout<<" Identifier's Record is deleted.";
				else
				{
					cout<<"\nFailed to delete "<<id;
				}
				break;
				case 4:
					cout<<"Enter Identifier to Modify: ";
					cin>>id;
					st.modify(id);
					break;
			default:
				cout<<"\nWrong Choice.";
			}

		}while(choice!=0);

	return 0;
}
