#include<iostream>
using namespace std;
class A{
private:
	string name;
public:
	
	void setname(string x){
		if(x=="Alto"){
			this->name = x;
		}else{
			cout<<"ERROR";
		}
	}
	string getname(){
		return this->name; 
	}
};
int main(){
	A a;
	a.setname("Alto");
	cout<<a.name;
}