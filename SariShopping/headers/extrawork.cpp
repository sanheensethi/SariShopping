#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
void extrawork :: _wait(){
		cout<<"Press Key To Continue ..!!";
		getch();
	}

int extrawork :: _option(){
		cout<<"Enter Option : ";
		int n;cin>>n;
		return n;
	}

void extrawork :: _clear(){
		system("cls");
	}

void extrawork :: print(string in,bool end=false){
		if(end) cout<<in<<"\n";
		else cout<<in;
	}