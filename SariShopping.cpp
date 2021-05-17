#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#define endl "\n"
using namespace std;

/* Class Declarations */
class extraWork;
class Form;
class HashCode;
class Database;


/*Session Variables*/
string _NAME = "";
string  _EMAIL = "";
string _MOBILE = "";
string _DOB = "";
bool flagLogin = false;

/*Function Declaration*/
void MainMenu();
void SignUp();
void SignIn();
void SignOut();

class extraWork{
public:
	void _wait();
	int _option();
	void _clear();
	void print(string in,bool end);
};

void extraWork :: _wait(){
		cout<<"Press Key To Continue ..!!";
		getch();
	}

int extraWork :: _option(){
		cout<<"Enter Option : ";
		int n;cin>>n;
		return n;
	}

void extraWork :: _clear(){
		system("cls");
	}

void extraWork :: print(string in,bool end=false){
		if(end) cout<<in<<"\n";
		else cout<<in;
	}

void extraWork :: print(string in,bool end=false){
		if(end) cout<<in<<"\n";
		else cout<<in;
	}
/* Classes */
class Node{

};

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


/*	Hash Code 	*/
class HashCode{
private:
	string code;
public:
	HashCode(string S){
		long long int codeResult = 1;
		for(int i=0;S[i]!='\0';i++){
			codeResult *= ((((int)S[i] + 2) - 3)+1);
		}
		this->code = to_string(codeResult);  
	}
	
	string getPass(){
		return this->code;
	}
};

/* DataBase
	1. Authentication
	2. Inserting Data in Files
*/
class DataBase{
private:
	string filename,data;
public:

	/* Inserting Data in Files */
	void insertData(string filename,string Data){
		fstream file;
		file.open(filename,ios::app);
		file<<Data;
		file<<"\n";
		file.close();
	}

	/* Authentication - Matching username and password from File Database System*/
	bool authenticate(string username,string password,string filename[3]){
		fstream file1,file2,file3;
		string user,pass,name,line,dob,mob;
		file1.open(filename[0],ios::in);
		file2.open(filename[1],ios::in);
		file3.open(filename[2],ios::in);
		file1>>user>>pass;
		cout<<endl<<password<<endl;
		while(!file1.eof()){
			getline(file2,name,'\n');
			file3>>dob>>mob;
			if(user == username && pass == password){
				flagLogin = true;
				_NAME = name;
				_DOB = dob;
				_MOBILE = mob;
				_EMAIL = user;
				return true;
			}
			file1>>user>>pass;
		}
		return false;
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

/*	MainMenu	*/
void MainMenu(){
	extraWork obj;
	while(1){
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Men             **"<<endl;
		cout<<"**            2.       Women           **"<<endl;
		if(flagLogin){
		cout<<"**            3.       SignOut         **"<<endl;
		}else{
		cout<<"**            3.       SignIn          **"<<endl;
		cout<<"**            4.       SignUp          **"<<endl;
		}
		cout<<"**            5.       Exit            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		if(flagLogin){
			cout<<endl;
			cout<<"Welcome, "<<_NAME<<endl;
			cout<<"User : "<<_EMAIL<<endl;
			cout<<"Mobile : "<<_MOBILE<<endl;
			cout<<endl;
		}
		int option;
		option = obj._option();
		switch(option){
			case 1: break;
			case 2: break;
			case 3: {
				if(flagLogin) SignOut();
				else SignIn();
			};break;
			case 4: SignUp();break;
			case 5: exit(0);break;
			default: break;
		}
	}
}

/*	SignUp Form	 */
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
	

	string pass;
	HashCode hash(signup.get('p'));
	pass = hash.getPass();
	// return - true -> print signup successfully
	DataBase db;
	db.insertData("data/authenticate.sr",signup.get('e')+ ' ' + pass);
	db.insertData("data/name.sr",signup.get('n'));
	db.insertData("data/dob_mobile.sr",signup.get('d')+ ' '+signup.get('m'));
	obj._wait();
}

/*	SignIn Form	  */
void SignIn(){
	extraWork obj;
	obj._clear();
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"**            SIGNIN                 **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"** CustomerCare: 18001800102         **"<<endl;
	cout<<"**                                   **"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"***************************************"<<endl;
	Form signin;
	signin.input('e');
	signin.input('p');
	string files[] = {"data/authenticate.sr","data/name.sr","data/dob_mobile.sr"};
	DataBase db;
	bool check;

	string pass;
	HashCode hash(signin.get('p'));
	pass = hash.getPass();
	cout<<pass;
	check = db.authenticate(signin.get('e'),pass,files);
	if(check){
		cout<<"\nLogin Successfull.\n";
		
	}else{
		cout<<"Authentication Failed, Wrong Username and Password\n";
	}
	obj._wait();
}

/* SignOut */
void SignOut(){
	_NAME = _MOBILE = _EMAIL = _DOB = "";
	flagLogin = false;
}