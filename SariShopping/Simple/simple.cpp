#include<conio.h>
#include<iostream>
#include<fstream>
using namespace std;

/*
Session Variables
After Login it will be Updated.
*/
static string _NAME = "";
static string _EMAIL = "";
static string _MOB = "";
static string _DOB = "";

/*
	Tools class having functions -
	1. wait
	2. clear
	3. option
	4. signup
	5. signin
*/
class tools{
private:
	string name,email,mobile,dob,password;
public:
	string x;
 
 /* Wait Function */
 void _wait(){
 	cout<<endl<<"press enter to continue...";
 	getch();
 }

 /* Clear Screen */
 void _clear(){
 	system("cls");
 }

 /*Option Taker*/
 int _option(){
 	int n;
 	cout<<"enter option: ";
 	cin>>n;
 	return n;
 }

 /* Signup Form */
 void _signup(){
 	cout<<"Enter Name: "<<endl;
 	getchar();
 	getline(cin,x);
 	this->name=x;
 	cout<<"Email-id: "<<endl;
 	cin>>x;
 	this->email=x;
 	cout<<"Password: "<<endl;
 	cin>>x;
 	this->password=x;
 	cout<<"DOB: "<<endl;
 	cin>>x;
 	this->dob=x;
 	cout<<"Mobile no.: "<<endl;
 	cin>>x;
 	this->mobile=x;
 	/*
		Files in which it is saved - 
		1. username
		2. password
		3. name
		4. dob
		5. mobile

		ios::app
 	*/
 	ofstream fout;
 	
 	fout.open("UserData/username.sari",ios::app);
 	fout<<this->email;
 	fout<<"\n";
 	fout.close();

 	fout.open("UserData/password.sari",ios::app);
 	fout<<this->password;
 	fout<<"\n";
 	fout.close();

 	fout.open("UserData/name.sari",ios::app);
 	fout<<this->name;
 	fout<<"\n";
 	fout.close();

 	fout.open("UserData/dob.sari",ios::app);
 	fout<<this->dob;
 	fout<<"\n";
 	fout.close();

 	fout.open("UserData/mobile.sari",ios::app);
 	fout<<this->mobile;
 	fout<<"\n";
 	fout.close();
 }

/*Sign in Form*/
 void _signin(){
 	cout<<"Email-id: "<<endl;
 	cin>>x;
 	this->email=x;
 	cout<<"Password: "<<endl;
 	cin>>x;
 	this->password=x;

 	/* CHECK DATA */

 	ifstream fin1,fin2,fin3,fin4,fin5;
 	string user,pass,name,mob,dob;
 	fin1.open("UserData/username.sari",ios::in);
	fin2.open("UserData/password.sari",ios::in);
	fin3.open("UserData/name.sari",ios::in);
	fin4.open("UserData/dob.sari",ios::in);
	fin5.open("UserData/mobile.sari",ios::in);

 	while(getline(fin1,user,'\n')){

 		/*User Authentication*/
 		getline(fin2,pass,'\n');

 		/*User Data*/
 		getline(fin3,name,'\n');
 		getline(fin4,dob,'\n');
 		getline(fin5,mob,'\n');

 		if(this->email == user && this->password == pass){
 			cout<<"\nLogin Successfull ... \n";
 			_NAME = name;
 			_EMAIL = user;
 			_DOB = dob;
 			_MOB = mob;
 			break;
 		}
 	}
 }
};
int main(){
  tools obj;

  MainMenu:
	obj._clear();
	cout<<"     *WELCOME\n     **TO*\n** SARREE SHOPPING **";
	cout<<endl;
	cout<<"WELCOME..."<<_NAME;
	cout<<endl;
	cout<<"MAIN_MENU\n1. MEN\n2. WOMEN\n3. SIGNIN\n4. SIGNUP\n5. EXIT ";
	int option=obj._option();
		switch(option){
			case 1: break;
			case 2: break;
			case 3: goto signin;break;
			case 4: goto signup; break;
			case 5: return 0;
		}
	signup:
		cout<<endl<<"***SIGN UP**"<<endl;
		cout<<"       PAGE        ";
		obj._wait();
		obj._clear();
		obj._signup();
		obj._wait();
		goto MainMenu;
	signin:
		cout<<endl<<"***SIGN IN**"<<endl;
		cout<<"       PAGE        ";
		obj._wait();
		obj._clear();
		obj._signin();
 		obj._wait();
		goto MainMenu;

		return 0;
	}