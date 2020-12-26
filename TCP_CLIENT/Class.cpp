#include "Class.h"
using namespace std;
#include <iostream>
#include <iomanip>
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
	cout << "\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : ";
	cout << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit;
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
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}