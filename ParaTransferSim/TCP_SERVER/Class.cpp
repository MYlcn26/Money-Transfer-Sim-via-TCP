#include "Class.h"
using namespace std;
#include <iostream>
#include <iomanip>
#include <string>


extern string SERVER_MESSAGE;
string userLoginData[10];
string temp1 = "";
string temp2 = "";
void account::create_account() {

	cout << "\nEnter The account No. : ";
	cin >> acno;
	cout << "\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin >> deposit;
	cout << "\nEnter Username(5 character):";
	cin >> temp1;
	cout << "\nEnter Password:(3 character) ";
	cin >> temp2;
	temp1 = temp1 + '*' + temp2 + '*';
	{
		int n = temp1.length();
		strcpy_s(userData_c, temp1.c_str());
	}
	cout << "\nEnter bankno: ";
	cin >> bankno;
	cout << "\n\n\nAccount Created..";

}

void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : ";
	cout << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit;
	string strName;
	for (int i = 0; i < 10; i++) {
		strName.push_back(name[i]);
	}

	SERVER_MESSAGE = "\nAccount No. : " + to_string(acno) + "\nType of Account : " + type + "\nBalance amount : " + to_string(deposit) + "\nAccount Holder Name : " + strName;
}
void account::readLoginData(int n) const {
	
	
		userLoginData[n] = "";
		for(int j=0;j<10;j++){
			userLoginData[n] = userLoginData[n] + userData_c[j];//stringe cevirme
		}
	
}


void account::modify()
{
	cout << "\nAccount No. : " << acno;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account : ";
	cin >> type;
	type = toupper(type);
	cout << "\nModify Balance amount : ";
	cin >> deposit;
}


void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
	SERVER_MESSAGE = SERVER_MESSAGE + to_string(acno) + "           " + name + "          " + type + "          " + to_string(deposit) + "\n";
}

int account::retacno() const
{
	return acno;
}
int account::retbankno() const
{
	return bankno;
}
int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}