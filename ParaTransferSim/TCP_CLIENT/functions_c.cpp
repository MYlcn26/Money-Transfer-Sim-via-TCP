#include "functions.h"
#include "Class.h"
using namespace std;
#include <iostream>
#include <fstream>
extern bool isAdmin;
void main_menu() {
	cout << "\n\n\n\tMAIN MENU";

	if (isAdmin) {	cout << "\n\n\t01. NEW ACCOUNT";}
	cout << "\n\n\t02. DEPOSIT AMOUNT";
	cout << "\n\n\t03. WITHDRAW AMOUNT";
	cout << "\n\n\t04. BALANCE ENQUIRY";
	cout << "\n\n\t05. TRANSFER MONEY";
	cout << "\n\n\t06. EXIT";
	if (isAdmin) {	cout << "\n\n\t07. ALL ACCOUNT HOLDER LIST";}
	if (isAdmin) {	cout << "\n\n\t08. CLOSE AN ACCOUNT";}
	if (isAdmin) {	cout << "\n\n\t09. MODIFY AN ACCOUNT";}

	if (isAdmin) { cout << "\n\n\tSelect Your Option (1-9) "; }
	else{	cout << "\n\n\tSelect Your Option (2-6)";}
}
void intro()
{
	cout << "\n\n\n\tMONEY";
	cout << "\n\n\tTRANSFER";
	cout << "\n\n\tSIMULATION";
	cin.get();
}