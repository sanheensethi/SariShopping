
#include "headers/extrawork.h"
#define endl "\n"
using namespace std;

string userName = "";
/*Function Declaration*/
void MainMenu();
void SignUp();
void SignIn();

/* Classes */


class Form{
private:
	string name,email,password,dob,mobile;
public:
	void input(char s){
		extraWork obj;
		obj.print("Enter ");
		int num = (int)s;
		string what;
		switch(num){
			case 110:what = "Name : ";break;
			case 101:what = "Email : ";break;
			case 112:what = "Passowrd : ";break;
			case 100:what = "DOB : ";break;
			case 109:what = "Mobile : ";break;
		}
		obj.print(what);
		switch(num){
			case 110:
				getchar(); 
				getline(cin,what);
				this->name = what;
				break;
			case 101:
				cin>>what;
				this->email = what;
				break;
			case 112:
				cin>>what;
				this->password = what;
				break;
			case 100:
				cin>>what;
				this->dob = what;
				break;
			case 109:
				cin>>what;
				this->mobile = what;
				break;
		}
		
	}

	string get(char s){
		int num = (int)s;
		string x;
		switch(num){
			case 110:x = name;break;
			case 101:x = email;break;
			case 112:x = password;break;
			case 100:x = dob;break;
			case 109:x = mobile;break;
		}
		return x;
	}
};

class DataBase{
private:
	string filename,data;
public:
	void insertData(string filename,string Data){
		fstream file;
		file.open(filename,ios::app);
		file<<Data;
		file<<"\n";
		file.close();
	}
	string authenticate(string username,string password,string filename[3]){
		fstream file1,file2,file3;
		string user,pass,name;
		cout<<"IN Authenticate : \n";
		cout<<"Username INPUT : "<<username<<"\n";
		cout<<"Password INPUT : "<<password<<"\n";
		file1.open(filename[0],ios::in);
		file2.open(filename[1],ios::in);
		file3.open(filename[2],ios::in);
		while(getline(file1,user,'\n')){
			getline(file2,pass,'\n');
			getline(file3,name,'\n');
			cout<<"user : "<<user<<" Pass : "<<pass<<" Name : "<<name<<"\n";
			if(user == username && pass == password){
				return name;
			}
		}
		return "";
	}
};


int main(){
	extraWork obj;

	/*Main Menu*/
	cout<<"*********************************"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"**                             **"<<endl;
	cout<<"**         SariShopping        **"<<endl;
	cout<<"**        --------------       **"<<endl;
	cout<<"**    A place to buy Clothes   **"<<endl;
	cout<<"**            and              **"<<endl;
	cout<<"**          FootWears          **"<<endl;
	cout<<"**                             **"<<endl;
	cout<<"*********************************"<<endl;
	cout<<"*********************************"<<endl;
	obj._wait();

	MainMenu();

	return 0;
}

void MainMenu(){
	extraWork obj;
	obj._clear();
	cout<<"Welcome "<<userName<<endl;
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"**          Option | Function        **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"**            1.       Men           **"<<endl;
	cout<<"**            2.       Women         **"<<endl;
	cout<<"**            3.       SignIn        **"<<endl;
	cout<<"**            4.       SignUp        **"<<endl;
	cout<<"**            5.       Exit          **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"** CustomerCare: 18001800102         **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	int option;
	option = obj._option();
	switch(option){
		case 1: break;
		case 2: break;
		case 3: SignIn();break;
		case 4: SignUp();break;
		case 5: return;break;
		default: MainMenu();break;
	}
}

void SignUp(){
	extraWork obj;
	obj._clear();
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"**            SIGNUP                 **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"** CustomerCare: 18001800102         **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	Form signup;
	signup.input('n');
	signup.input('e');
	signup.input('p');
	signup.input('d');
	signup.input('m');
	/*Signup Backend*/
	cout<<signup.get('e');
	DataBase db;
	// return - true -> print signup successfully
	db.insertData("data/registration.txt",signup.get('e'));
	db.insertData("data/password.txt",signup.get('p'));
	db.insertData("data/name.txt",signup.get('n'));
	obj._wait();
	MainMenu();
}

void SignIn(){
	extraWork obj;
	obj._clear();
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"**            SIGNUP                 **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"** CustomerCare: 18001800102         **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	Form signin;
	signin.input('e');
	signin.input('p');
	string files[] = {"data/registration.txt","data/password.txt","data/name.txt"};
	string name;
	DataBase db;
	cout<<signin.get('e')<<endl;
	cout<<signin.get('p')<<endl;
	name = db.authenticate(signin.get('e'),signin.get('p'),files);
	if(name == ""){
		cout<<"Authentication Failed, Wrong Username and Password\n";
	}else{
		cout<<"\nLogin Successfull\n";
		cout<<"Name : "<<name;
		userName = name;
	}
	obj._wait();
	MainMenu();
}