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
class Material;
class Cart;
class CartNode;

/*Static Material Id Auto Increment*/
static int _IDIncrementer = 376;
const float _GST1 = 5.0;
const float _GST2 = 12.0;
const float _GST3 = 18.0;

/*Session Variables*/
string _NAME = "";
string  _EMAIL = "";
string _MOBILE = "";
string _DOB = "";
string _Address = "";
Material *_MenClothItem = NULL;
Material *_WomenClothItem = NULL;
Material *_MenClothItemD = NULL;
Material *_WomenClothItemD = NULL;
Material *_MenFootwearItem = NULL;
Material *_WomenFootwearItem = NULL;
Material *_MenFootwearItemD = NULL;
Material *_WomenFootwearItemD = NULL;
CartNode *_CartAddress = NULL;
bool flagLogin = false;
bool AddressInput = false;
bool flagPlaced = false;

/*Function Declaration*/
void MainMenu();
void SignUp();
void SignIn();
void SignOut();
int Men();
int Women();
int Discounted(char);
int nonDiscounted(char);
int MenClothing();
int WomenClothing();
int FootDiscounted(char);
int FootnonDiscounted(char);
int MenFootwear();
int WomenFootwear();
int cart();
int placeOrder();
int deleteItem();

/* Classes */
class extraWork{
public:
	void _wait(){
		cout<<"Press Key To Continue ..!!";
		getch();
	}

	int _option(){
			cout<<"Enter Option : ";
			int n;cin>>n;
			return n;
		}

	void _clear(){
			system("cls");
		}

	void print(string in,bool end=false){
			if(end) cout<<in<<"\n";
			else cout<<in;
		}

};


/* Clothes Insert Section */
class Material{
public:
	int _MaterialID;
	int _MaterailType; // 1- Cloth , 0 - Footwear
	string _MaterialName;
	int materialFor; // 1 - Men , 0 - Women
	bool isDicounted; // true - Yes , false - No
	int Discount;
	bool printedOnBoot; // printed On Boot have GST
	float Price;
	float GST;
	Material *nextItem; // connecting second Item
	Material(){
		_MaterialID = _IDIncrementer++;
		isDicounted = false;
		printedOnBoot = false;
	}
};

class Clothes{
public:
	void AddItem(Material **last,int Mtype,string MName,int Mfor,float price,int discount,bool isDicounted=false,bool printedOnBoot=false){
		/*Item Initialize*/
		Material *new_item = new Material();
		new_item->_MaterailType = Mtype;
		new_item->_MaterialName = MName;
		new_item->materialFor = Mfor;
		new_item->isDicounted = isDicounted;
		new_item->Discount = discount;
		new_item->Price = price;
		if(Mtype && price>1000){ // cloth price > 1000 gst = 12%
			new_item->GST = _GST2;
		}else if(Mtype && price<=1000){ // cloth price <= 1000 gst = 5%
			new_item->GST = _GST1;
		}else if(!Mtype && price<=500 && printedOnBoot){ // boot price <= 500 and price printed on boot then gst = 5%
			new_item->GST = _GST1;
		}else if(!Mtype && price>500){ 	// boot price > 500, printed or not printed on boot, gst = 18%
			new_item->GST = _GST3;
		}else{
			new_item->GST = _GST1;
		}
		new_item->nextItem = NULL;
		if(*last == NULL){ 
			*last = new_item;
		}else{
			(*last)->nextItem = new_item;
			*last = new_item;
			}
	}

	void DisplayItems(Material *start){
		Material *temp = start;
		float buy;
		cout<<"Item ID\tItem Name\tPrice\t\tDiscount\tGST\tBuy Price\n";
		while(temp != NULL){
			cout<<temp->_MaterialID<<"\t";
			cout<<temp->_MaterialName<<"\t";
			cout<<"Rs."<<temp->Price<<"\t\t";
			cout<<temp->Discount<<"%"<<"\t\t";
			cout<<temp->GST<<"%"<<"\t";
			
			buy = ((temp->Price) - ((temp->Price)*(temp->Discount))/100);
			buy = buy + (((buy)*(temp->GST))/100);

			cout<<"Rs."<<buy;
			cout<<endl;
			temp = temp->nextItem;
		}
	}

	void MaterialSearch(int id,int *materialid,string *materialname,float *price,Material *searchin){
		while(searchin->_MaterialID != id){
			searchin = searchin->nextItem;
		}
		*materialid = searchin->_MaterialID;
		*materialname = searchin->_MaterialName;
		*price = searchin->Price + ((searchin->Price*searchin->GST)/100);
	}

};

/* Class - Form Create Section */
class Form{
private:
	string name,email,password,dob,mobile,address;
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
			case 97:what = "Address : ";break;
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
			case 97:
				getchar();
				getline(cin,what);
				this->address = what;
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
			case 97: x = address;break;
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
	bool authenticate(string username,string password,string filename[4]){
		fstream file1,file2,file3,file4;
		string user,pass,name,line,dob,mob,address;
		file1.open(filename[0],ios::in);
		file2.open(filename[1],ios::in);
		file3.open(filename[2],ios::in);
		file4.open(filename[3],ios::in);
		file1>>user>>pass;
		while(!file1.eof()){
			getline(file2,name,'\n');
			getline(file4,address,'\n');
			file3>>dob>>mob;
			if(user == username && pass == password){
				flagLogin = true;
				_NAME = name;
				_DOB = dob;
				_MOBILE = mob;
				_EMAIL = user;
				_Address = address;
				AddressInput = true;
				return true;
			}
			file1>>user>>pass;
		}
		return false;
	}
};

class ShoppingItems{
private:
	float discount;
public:
	ShoppingItems(){
		/*Material **address,
		int Mtype,	1- Cloth , 0 - Footwear
		string MName,
		int Mfor,	1 - Men , 0 - Women
		float price,
		int discount,
		bool isDicounted,	true - Yes , false - No By Defalut - false
		bool printedOnBoot By Default - False
		*/

		/***********************     MEN Section    **************************/

		/* Men Cloth Non Discounted */
		this->discount = 0.0;
		Material *start = NULL;
		Material *end = NULL;
		// First Item
		Clothes MenNonD;
		MenNonD.AddItem(&end,1,"Shirt 01",1,650.0,this->discount,false,false);
		start = end;
		_MenClothItem = start;

		//rest items
		MenNonD.AddItem(&end,1,"Shirt 02",1,450.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Shirt 03",1,1050.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Shirt 04",1,1650.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Shirt 05",1,700.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Pant  01",1,750.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Pant  02",1,600.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Pant  03",1,950.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Pant  04",1,850.0,this->discount,false,false);
		MenNonD.AddItem(&end,1,"Pant  05",1,1000.0,this->discount,false,false);

		/* Men Cloth Discounted */
		Material *mdstart = NULL;
		Material *mdend = NULL;
		// First Item
		Clothes MenD;
		MenD.AddItem(&mdend,1,"Shirt 06",1,650.0,20,false,false);
		mdstart = mdend;
		_MenClothItemD = mdstart;

		//rest items
		MenD.AddItem(&mdend,1,"Shirt 07",1,450.0,10,true,false);
		MenD.AddItem(&mdend,1,"Shirt 08",1,1050.0,15,true,false);
		MenD.AddItem(&mdend,1,"Shirt 09",1,1650.0,10,true,false);
		MenD.AddItem(&mdend,1,"Shirt 10",1,700.0,20,true,false);
		MenD.AddItem(&mdend,1,"Pant  06",1,750.0,18,true,false);
		MenD.AddItem(&mdend,1,"Pant  07",1,600.0,30,true,false);
		MenD.AddItem(&mdend,1,"Pant  08",1,950.0,25,true,false);
		MenD.AddItem(&mdend,1,"Pant  09",1,850.0,16,true,false);
		MenD.AddItem(&mdend,1,"Pant  10",1,1000.0,60,true,false);

		/* Men Footwear Non Discounted */
		this->discount = 0.0;
		Material *mfNstart = NULL;
		Material *mfNend = NULL;
		// First Item
		Clothes MenFND;
		MenFND.AddItem(&mfNend,0,"Boot 01   ",1,650.0,this->discount,false,false);
		mfNstart = mfNend;
		_MenFootwearItem = mfNstart;

		//rest items
		MenFND.AddItem(&mfNend,0,"Boot 02*  ",1,450.0,this->discount,false,true);
		MenFND.AddItem(&mfNend,0,"Boot 03   ",1,1050.0,this->discount,false,false);
		MenFND.AddItem(&mfNend,0,"Boot 04*  ",1,300.0,this->discount,false,true);
		MenFND.AddItem(&mfNend,0,"Boot 05   ",1,350.0,this->discount,false,false);
		MenFND.AddItem(&mfNend,0,"Boot 06*  ",1,500.0,this->discount,false,true);
		MenFND.AddItem(&mfNend,0,"Boot 07   ",1,600.0,this->discount,false,false);
		MenFND.AddItem(&mfNend,0,"Boot 08*  ",1,1100.0,this->discount,false,true);
		MenFND.AddItem(&mfNend,0,"Boot 09   ",1,2500.0,this->discount,false,false);
		MenFND.AddItem(&mfNend,0,"Boot 10   ",1,350.0,this->discount,false,false);

		/* Men Footwear Discounted */
		Material *mfstart = NULL;
		Material *mfend = NULL;
		// First Item
		Clothes MenFD;
		MenFD.AddItem(&mfend,1,"Boot 11*  ",1,650.0,15,true,true);
		mfstart = mfend;
		_MenFootwearItemD = mfstart;

		//rest items
		MenFD.AddItem(&mfend,1,"Boot 12   ",1,450.0,8,true,false);
		MenFD.AddItem(&mfend,1,"Boot 13   ",1,1050.0,12,true,false);
		MenFD.AddItem(&mfend,1,"Boot 14*  ",1,300.0,10,true,true);
		MenFD.AddItem(&mfend,1,"Boot 15   ",1,350.0,15,true,false);
		MenFD.AddItem(&mfend,1,"Boot 16*  ",1,500.0,25,true,true);
		MenFD.AddItem(&mfend,1,"Boot 17   ",1,600.0,30,true,false);
		MenFD.AddItem(&mfend,1,"Boot 18*  ",1,1100.0,20,true,true);
		MenFD.AddItem(&mfend,1,"Boot 19   ",1,2500.0,60,true,false);
		MenFD.AddItem(&mfend,1,"Boot 20   ",1,350.0,16,true,false);

		/*Material **address,
		int Mtype,	1- Cloth , 0 - Footwear
		string MName,
		int Mfor,	1 - Men , 0 - Women
		float price,
		int discount,
		bool isDicounted,	true - Yes , false - No By Defalut - false
		bool printedOnBoot By Default - False
		*/

		/***********************   WOMEN Section    **************************/

		/* Women Cloth Non Discounted */
		this->discount = 0.0;
		Material *wstart = NULL;
		Material *wend = NULL;
		// First Item
		Clothes WomenNonD;
		WomenNonD.AddItem(&wend,1,"Kurti   01",0,650.0,this->discount,false,false);
		wstart = wend;
		_WomenClothItem = wstart;

		//rest items
		WomenNonD.AddItem(&wend,1,"Kurti   02",0,450.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Shirt   01",0,1050.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Shirt   02",0,1650.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Trouser 01",0,700.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Trouser 02",0,750.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Trouser 03",0,600.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Tshirt  01",0,950.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Tshirt  02",0,850.0,this->discount,false,false);
		WomenNonD.AddItem(&wend,1,"Tshirt  03",0,1000.0,this->discount,false,false);

		/* WomenMen Cloth Discounted */
		Material *wdstart = NULL;
		Material *wdend = NULL;
		// First Item
		Clothes WomenD;
		MenD.AddItem(&wdend,1,"Shirt 06",0,650.0,20,false,false);
		wdstart = wdend;
		_WomenClothItemD = wdstart;

		//rest items
		WomenD.AddItem(&wdend,1,"Kurti   02",0,450.0,10,true,false);
		WomenD.AddItem(&wdend,1,"Shirt   01",0,1050.0,15,true,false);
		WomenD.AddItem(&wdend,1,"Shirt   02",0,1650.0,10,true,false);
		WomenD.AddItem(&wdend,1,"Trouser 01",0,700.0,20,true,false);
		WomenD.AddItem(&wdend,1,"Trouser 02",0,750.0,18,true,false);
		WomenD.AddItem(&wdend,1,"Trouser 03",0,600.0,30,true,false);
		WomenD.AddItem(&wdend,1,"Tshirt  01",0,950.0,25,true,false);
		WomenD.AddItem(&wdend,1,"Tshirt  02",0,850.0,16,true,false);
		WomenD.AddItem(&wdend,1,"Tshirt  03",0,1000.0,60,true,false);

		/* Women Footwear Non Discounted */
		this->discount = 0.0;
		Material *wfnstart = NULL;
		Material *wfnend = NULL;
		// First Item
		Clothes WenFND;
		MenFND.AddItem(&wfnend,0,"Boot 01   ",0,650.0,this->discount,false,false);
		wfnstart = wfnend;
		_WomenFootwearItem = wfnstart;

		//rest items
		WenFND.AddItem(&wfnend,0,"Boot 02   ",0,450.0,this->discount,false,false);
		WenFND.AddItem(&wfnend,0,"Boot 03   ",0,1050.0,this->discount,false,false);
		WenFND.AddItem(&wfnend,0,"Boot 04*  ",0,300.0,this->discount,false,true);
		WenFND.AddItem(&wfnend,0,"Boot 05   ",0,350.0,this->discount,false,false);
		WenFND.AddItem(&wfnend,0,"Boot 06*  ",0,500.0,this->discount,false,true);
		WenFND.AddItem(&wfnend,0,"Boot 07   ",0,600.0,this->discount,false,false);
		WenFND.AddItem(&wfnend,0,"Boot 08*  ",0,1100.0,this->discount,false,true);
		WenFND.AddItem(&wfnend,0,"Boot 09   ",0,2500.0,this->discount,false,false);
		WenFND.AddItem(&wfnend,0,"Boot 10   ",0,1000.0,this->discount,false,false);

		/* Women Footwear Discounted */
		Material *wfstart = NULL;
		Material *wfend = NULL;
		// First Item
		Clothes WenFD;
		MenFD.AddItem(&wfend,1,"Boot 11*  ",1,650.0,15,true,true);
		wfstart = wfend;
		_WomenFootwearItemD = wfstart;

		//rest items
		WenFD.AddItem(&wfend,1,"Boot 12   ",1,450.0,8,true,false);
		WenFD.AddItem(&wfend,1,"Boot 13   ",1,1050.0,12,true,false);
		WenFD.AddItem(&wfend,1,"Boot 14*  ",1,300.0,10,true,true);
		WenFD.AddItem(&wfend,1,"Boot 15   ",1,350.0,15,true,false);
		WenFD.AddItem(&wfend,1,"Boot 16*  ",1,500.0,25,true,true);
		WenFD.AddItem(&wfend,1,"Boot 17   ",1,600.0,30,true,false);
		WenFD.AddItem(&wfend,1,"Boot 18*  ",1,1100.0,20,true,true);
		WenFD.AddItem(&wfend,1,"Boot 19   ",1,2500.0,60,true,false);
		WenFD.AddItem(&wfend,1,"Boot 20   ",1,1000.0,16,true,false);



	}
};

class CartNode{
public:
	int MaterailId;
	string MaterialName;
	float price;
	CartNode *nextItem;
};

class Cart{
public:
	void AddItem(int id,char searchin,char clothfoot,bool discount){ // searchin m - mens f - womens , discount - true,false, clothfoot : c-cloth,f-foot
		int materialid;
		string materialname;
		float price;
		Clothes cloth;
		Material *searchIN = NULL;
		if(searchin == 'm'){
			if(discount){
				if(clothfoot == 'c'){
					searchIN = _MenClothItemD;
				}else if(clothfoot == 'f'){
					searchIN = _MenFootwearItemD;
				}
			}else{
				if(clothfoot == 'c'){
					searchIN = _MenClothItem;
				}else if(clothfoot == 'f'){
					searchIN = _MenFootwearItem;
				}
			}
		}else if(searchin == 'f'){
			if(discount){
				if(clothfoot == 'c'){
					searchIN = _WomenClothItemD;
				}else if(clothfoot == 'f'){
					searchIN = _WomenFootwearItemD;
				}
			}else{
				if(clothfoot == 'c'){
					searchIN = _WomenClothItem;
				}else if(clothfoot == 'f'){
					searchIN = _WomenFootwearItem;
				}
			}
		}

			cloth.MaterialSearch(id,&materialid,&materialname,&price,searchIN);
			
			CartNode *new_node = new CartNode();
			new_node->MaterailId = materialid;
			new_node->MaterialName = materialname;
			new_node->price = price;
			new_node->nextItem = NULL;

			CartNode *head = _CartAddress;

			if(head == NULL){ 
				head = new_node;
				_CartAddress = head;
			}
			else{
				CartNode *temp = head;
				while(temp->nextItem != NULL){
					temp = temp->nextItem;
				}
				temp->nextItem = new_node;
			}
			CartNode *temp = _CartAddress;
	}

	void DisplayCart(CartNode *head){
		CartNode *temp = head;
		float buy = 0;
		cout<<"Item ID\tItem Name\tPrice\n";
		while(temp != NULL){
			cout<<temp->MaterailId<<"\t";
			cout<<temp->MaterialName<<"\t";
			cout<<"Rs."<<temp->price<<"\t\t";
			buy+=temp->price;
			cout<<endl;
			temp = temp->nextItem;
		}
		cout<<endl;
		cout<<"\t\t\t\tTotal Bill : Rs."<<buy<<endl;
		cout<<endl;
	}

	void DeleteFromCart(int id){
		CartNode *temp = _CartAddress;
		CartNode *temp2 = NULL;
		
		if(id == _CartAddress->MaterailId){
			temp2 = _CartAddress;
			_CartAddress = temp2->nextItem;
			delete temp2;
		}else{
			while(temp->MaterailId != id){
				temp2 = temp;
				temp = temp->nextItem;
			}
			temp2->nextItem = temp->nextItem;
			delete temp;
		}

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
	ShoppingItems *ShoppingDatabase = new ShoppingItems();
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
		cout<<"**            3.       Cart            **"<<endl;
		cout<<"**            4.       SignOut         **"<<endl;
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
			case 1: Men();break;
			case 2: Women();break;
			case 3: {
				if(flagLogin) cart();
				else SignIn();
			};break;
			case 4: {
				if(flagLogin) SignOut();
				else SignUp();
			};break;
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
	signup.input('a');
	/*Signup Backend*/
	

	string pass;
	HashCode hash(signup.get('p'));
	pass = hash.getPass();
	// return - true -> print signup successfully
	DataBase db;
	db.insertData("data/authenticate.sr",signup.get('e')+ ' ' + pass);
	db.insertData("data/name.sr",signup.get('n'));
	db.insertData("data/dob_mobile.sr",signup.get('d')+ ' '+signup.get('m'));
	db.insertData("data/address.sr",signup.get('a'));
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
	string files[] = {"data/authenticate.sr","data/name.sr","data/dob_mobile.sr","data/address.sr"};
	DataBase db;
	bool check;

	string pass;
	HashCode hash(signin.get('p'));
	pass = hash.getPass();
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

int Men(){
	extraWork obj;
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Cloths          **"<<endl;
		cout<<"**            2.       Footwear        **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: MenClothing();break;
			case 2: MenFootwear();break;
			case 3: return 0;break;
		}
		return 0;
}

int Women(){
	extraWork obj;
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Cloths          **"<<endl;
		cout<<"**            2.       Footwear        **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: WomenClothing();break;
			case 2: WomenFootwear();break;
			case 3: return 0;break;
		}
		return 0;
}

/* Men */
int MenClothing(){
	extraWork obj;
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Discounted      **"<<endl;
		cout<<"**            2.       Non Discounted  **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: Discounted('m');break;
			case 2: nonDiscounted('m');break;
			case 3: return 0;break;
		}
		return 0;
}

int MenFootwear(){
	extraWork obj;
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Discounted      **"<<endl;
		cout<<"**            2.       Non Discounted  **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: FootDiscounted('m');break;
			case 2: FootnonDiscounted('m');break;
			case 3: return 0;break;
		}
		return 0;
}

int WomenFootwear(){
	extraWork obj;
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Discounted      **"<<endl;
		cout<<"**            2.       Non Discounted  **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: FootDiscounted('f');break;
			case 2: FootnonDiscounted('f');break;
			case 3: return 0;break;
		}
		return 0;
}

int WomenClothing(){
	extraWork obj;
		obj._clear();
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       Discounted      **"<<endl;
		cout<<"**            2.       Non Discounted  **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: Discounted('f');break;
			case 2: nonDiscounted('f');break;
			case 3: return 0;break;
		}
		return 0;
}

int Discounted(char type){
	Clothes *cloth = new Clothes();
	Cart userCart;
	extraWork obj;
	while(1){
		obj._clear();
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"**             Shopping Items                **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"** CustomerCare: 18001800102                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<endl;
		if(type == 'm'){
			cloth->DisplayItems(_MenClothItemD);
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'m','c',true);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}else if(type=='f'){
			cloth->DisplayItems(_WomenClothItemD);
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'f','c',true);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}
		cin.clear();
		fflush(stdin);
		char yn;
		cout<<endl<<"Do You Want To Continue Shopping ? [y/n] : ";
		cin>>yn;
		if(yn == 'y') continue;
		else break;
	}
	return 0;
}

int FootDiscounted(char type){
	Clothes *cloth = new Clothes();
	Cart userCart;
	extraWork obj;
	while(1){
		obj._clear();
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"**             Shopping Items                **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"** CustomerCare: 18001800102                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<endl;
		if(type == 'm'){
			cloth->DisplayItems(_MenFootwearItemD);
			cout<<endl;
			cout<<"* Represents Cost is printed on Boot"<<endl;
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'m','f',true);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}else if(type=='f'){
			cloth->DisplayItems(_WomenFootwearItemD);
			cout<<endl;
			cout<<"* Represents Cost is printed on Boot"<<endl;
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'f','f',true);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}
		cin.clear();
		fflush(stdin);
		char yn;
		cout<<endl<<"Do You Want To Continue Shopping ? [y/n] : ";
		cin>>yn;
		if(yn == 'y') continue;
		else break;
	}
	return 0;
}


int nonDiscounted(char type){
	Clothes *cloth = new Clothes();
	Cart userCart;
	extraWork obj;
	while(1){
		obj._clear();
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"**             Shopping Items                **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"** CustomerCare: 18001800102                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<endl;
		if(type == 'm'){
			cloth->DisplayItems(_MenClothItem);
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'m','c',false);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}else if(type=='f'){
			cloth->DisplayItems(_WomenClothItem);
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'f','c',false);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}
		cin.clear();
		fflush(stdin);
		char yn;
		cout<<endl<<"Do You Want To Continue Shopping ? [y/n] : ";
		cin>>yn;
		if(yn == 'y') continue;
		else break;
	}
	return 0;
}

int FootnonDiscounted(char type){
	Clothes *cloth = new Clothes();
	Cart userCart;
	extraWork obj;
	while(1){
		obj._clear();
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"**             Shopping Items                **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"** CustomerCare: 18001800102                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<endl;
		if(type == 'm'){
			cloth->DisplayItems(_MenFootwearItem);
			cout<<endl;
			cout<<"* Represents Cost is printed on Boot"<<endl;
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'m','f',false);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}else if(type=='f'){
			cloth->DisplayItems(_WomenFootwearItem);
			cout<<endl;
			cout<<"* Represents Cost is printed on Boot"<<endl;
			if(flagLogin){
				int itemID = obj._option();
				cout<<"Chosen ID : "<<itemID<<endl;
				userCart.AddItem(itemID,'f','f',false);
			}else{
				cout<<endl;
				cout<<"Please Login To Add Item in Cart !!"<<endl;
				obj._wait();
				break;
			}
		}
		cin.clear();
		fflush(stdin);
		char yn;
		cout<<endl<<"Do You Want To Continue Shopping ? [y/n] : ";
		cin>>yn;
		if(yn == 'y') continue;
		else break;
	}
	return 0;
}

int cart(){
	Cart userCart;
	extraWork obj;
	obj._clear();
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"**             Shopping Cart                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"** CustomerCare: 18001800102                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<endl;
	userCart.DisplayCart(_CartAddress);
		cout<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"**          Option | Function          **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"**            1.       PlaceOrder      **"<<endl;
		cout<<"**            2.       Delete Item     **"<<endl;
		cout<<"**            3.       Back            **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"** CustomerCare: 18001800102           **"<<endl;
		cout<<"**                                     **"<<endl;
		cout<<"*****************************************"<<endl;
		cout<<"*****************************************"<<endl;
		int option;
		option = obj._option();
		switch(option){
			case 1: placeOrder();break;
			case 2: deleteItem();break;
			case 3: return 0;break;
		}
	obj._wait();
	return 0;
}

int placeOrder(){
	Cart userCart;
	extraWork obj;
	if(_CartAddress == NULL) flagPlaced = false;
	else flagPlaced = true;

		obj._clear();
			cout<<"***********************************************"<<endl;
			cout<<"***********************************************"<<endl;
			cout<<"**                                           **"<<endl;
			cout<<"**             Placing Order                 **"<<endl;
			cout<<"**                                           **"<<endl;
			cout<<"** CustomerCare: 18001800102                 **"<<endl;
			cout<<"**                                           **"<<endl;
			cout<<"***********************************************"<<endl;
			cout<<"***********************************************"<<endl;
			cout<<endl;
		userCart.DisplayCart(_CartAddress);
			if(flagPlaced){
				DataBase db;
				db.insertData("Order/Name_"+_EMAIL+".sr",_NAME);
				db.insertData("Order/Email_MOB_"+_EMAIL+".sr",_EMAIL+ ' '+_MOBILE);
				db.insertData("Order/Address_"+_EMAIL+".sr",_Address);

				string data = "";
				float buy=0;
				CartNode *temp = _CartAddress;
				CartNode *temp2 = NULL;
				while(temp!=NULL){
					temp2 = temp;
					data+=temp->MaterailId+" ";
					data+=temp->MaterialName+" ";
					data+=to_string(temp->price)+"\n\n";
					buy+=temp->price;
					temp = temp->nextItem;
					delete temp2;
				}
				data+="Bill : "+to_string(buy);
				data+="\n\n\n\n";

				db.insertData("Order/Order_"+_EMAIL+".sr",data);
				_CartAddress = NULL;
			}
	return 0;
}

int deleteItem(){
	Cart userCart;
	extraWork obj;
		while(1){
			obj._clear();
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"**             Deleting Item                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"** CustomerCare: 18001800102                 **"<<endl;
		cout<<"**                                           **"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"***********************************************"<<endl;
		cout<<"Enter 0 for exit"<<endl;
		cout<<endl;
			userCart.DisplayCart(_CartAddress);
			int id;
			cout<<"Enter Item ID to Delete : ";
			cin>>id;
			if(id == 0) return 0;
			userCart.DeleteFromCart(id);
			cin.clear();
			fflush(stdin);
			char yn;
			cout<<endl<<"Do You Want To Delete More ? [y/n] : ";
			cin>>yn;
			if(yn == 'y') continue;
			else break;
		}
	obj._wait();
	return 0;
}