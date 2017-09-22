#include<string>
#include<iostream>
#include<cstdlib>
 
using namespace std;
 
class IRose
{
public:
	virtual string Color(void)=0;
};
 
class RedRose: public IRose
{
public:
	string Color(void)
	{
		return "Red";
	}
};
 
class YellowRose: public IRose
{
public:
	string Color(void)
	{
		return "Yellow";
	}
};
 
class IFactory
{
public:
	virtual IRose* Create(string type)=0; 
	//The factory create method in 90% of cases will take a parameter which 
	//determines what kind of the object the factory will return.	
};
 
class Factory: public IFactory
{
public:
	IRose* Create(string type)
	{
		if ("Red" == type)
			return new RedRose();
 
        if ("Yellow" == type)
			return new YellowRose();
		
        return NULL;
	}
};
 
int main()
{
	IRose* p = NULL;
	IFactory* f = NULL;
 
	f = new Factory();	//You have to create an INSTANCE of the factory
 
	p = f->Create("Red");
    cout<<"\nColor is: "<<p->Color()<<"\n";
	delete p;
	p = f->Create("Yellow");
    cout<<"\nColor is: "<<p->Color()<<"\n";
	delete p;
	return 1;
}
