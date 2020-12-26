#include "functions.h"
#include "Class.h"
using namespace std;
#include <iostream>
#include <fstream>

extern string SERVER_MESSAGE;
extern string userLoginData[20];
extern bool loggedIn;
extern bool isAdmin;
int loggedAccount;

void main_menu() {
	cout << "\n\n\n\tMAIN MENU";
	if (isAdmin) { cout << "\n\n\t01. NEW ACCOUNT"; }
	cout << "\n\n\t02. DEPOSIT AMOUNT";
	cout << "\n\n\t03. WITHDRAW AMOUNT";
	cout << "\n\n\t04. BALANCE ENQUIRY";
	cout << "\n\n\t05. TRANSFER MONEY";
	cout << "\n\n\t06. EXIT";
	if (isAdmin) { cout << "\n\n\t07. ALL ACCOUNT HOLDER LIST"; }
	if (isAdmin) { cout << "\n\n\t08. CLOSE AN ACCOUNT"; }
	if (isAdmin) { cout << "\n\n\t09. MODIFY AN ACCOUNT"; }

	cout << "\n\n\tSelect Your Option (1-9) ";
}

void select_operation(char ch, int num, int num2,int num3,bool is_admin) {

	
	switch (ch)
	{
	case '1':
		if (is_admin) {
			cout << "\nContinue on Server\n";
			write_account();
		}
		break;
	case '2':
		deposit_withdraw(num, 1, num2);
		break;
	case '3':
		deposit_withdraw(num, 2, num2);
		break;
	case '4':
		display_sp(num);
		break;
	case '5':
		transfer_money(num3, num, num2);
		break;
	case '6':
		cout << "\n\n\tThanks for using bank managemnt system";
		SERVER_MESSAGE = "\n\n\tThanks for using bank managemnt system";
		loggedIn = false;
		isAdmin = false;
		is_admin = false;
		break;
	case '7':
		if (isAdmin == true) {
			display_all();
		}
		break;
	case '8':
		if (is_admin) {
			delete_account(num);

		}
		break;
	case '9':
		if (is_admin) {
			modify_account(num);
			cout << "\nContinue on Server\n";
		}
		break;

	default:cout << "\a"; SERVER_MESSAGE = "\a";
	}
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	cout << "Continue on Server\n" << endl;
	SERVER_MESSAGE = "Continue on Server\n";
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}
void readLoginData() {
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		for(int i=0;i<10;i++){
		if (ac.retacno() == i)
		{
			ac.readLoginData(i);
//			loggedAccount = ac.retacno();
			flag = true;
		}
		}
	}

	inFile.close();
	if (flag == false) {
		cout << "\n\nAccount number does not exist";
		SERVER_MESSAGE = "\n\nAccount number does not exist";
	}
}
//BANKA HESAP NO KONTROL
bool checkBank(int n1, int n2) {
	account ac;
	bool flag = false;
	ifstream inFile;
	int bankno1 = 0;
	int bankno2 = 0;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
	}

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		

		for (int i = 0; i < 20; i++) {
			if (ac.retacno() == n1)
			{
				bankno1 = ac.retbankno();
				flag = true;
			}
			if (ac.retacno() == n2)
			{
				bankno2 = ac.retbankno();
				flag = true;
			}
		}
	}
	if (bankno1 == bankno2) { return 1; }
	else { return 0; }

	inFile.close();
	if (flag == false) {
		cout << "\n\nAccount number does not exist";
		SERVER_MESSAGE = "\n\nAccount number does not exist";
	}
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";
	SERVER_MESSAGE = "\nBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false){
		cout << "\n\nAccount number does not exist";
	SERVER_MESSAGE = "\n\nAccount number does not exist";
	}
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	cout << "Continue on Server\n" << endl;
	SERVER_MESSAGE = "Continue on Server\n";
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}

	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));

		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of account" << endl;
			SERVER_MESSAGE = "\n\nEnter The New Details of account";
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			SERVER_MESSAGE = "\n\n\t Record Updated";
			found = true;
		}
	}


	File.close();
	if (found == false){
		cout << "\n\n Record Not Found ";
		SERVER_MESSAGE = "\n\n Record Not Found ";
}}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	cout << "Continue on Server\n" << endl;
	SERVER_MESSAGE = "Continue on Server\n";
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
	SERVER_MESSAGE = "\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	SERVER_MESSAGE = "\n\n\t\tACCOUNT HOLDER LIST\n\n====================================================\nA/c no.      NAME           Type  Balance\n====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit , withdraw and transfer amounts
//****************************************************************

void deposit_withdraw(int n, int option,int num)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				//cout << "\n\nEnter The amount to be deposite";
				SERVER_MESSAGE = "\n\n\tTO DEPOSITE AMOUNT ";
				amt = num;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				//cout << "\n\nEnter The amount to be withdraw";
				SERVER_MESSAGE = "\n\n\tTO WITHDRAW AMOUNT ";
				amt = num;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C')){
					cout << "Insufficience balance";
				SERVER_MESSAGE = "Insufficience balance";
			}
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			SERVER_MESSAGE = "\n\n\t Record Updated";
			ac.show_account();

			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
	SERVER_MESSAGE = "\n\n Record Not Found ";
}
void transfer_money(int amount, int acno_s, int acno_r) {
	bool found = false;
	account ac_s;
	account ac_r;
	fstream File;
	int transitionCharge = 0;

	if (!checkBank(acno_s, acno_r)) {
		transitionCharge = 6;
		cout << "\nDiffrent banks charge is: 6\n";
		SERVER_MESSAGE = "\nDiffrent banks charge is: 6\n";
	}
	else {
		transitionCharge = 2;
		cout << "\nSame banks charge is: 2\n";
		SERVER_MESSAGE = "\nSame banks charge is: 2\n";

	}
	File.open("account.dat", ios::binary | ios::in | ios::out);//YOLLAYAN
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac_s), sizeof(account));
		if (ac_s.retacno() == acno_s)
		{

			if(amount+ transitionCharge < ac_s.retdeposit()){
			ac_s.draw(amount+ transitionCharge);
			cout << "YOUR NEW BALANCE";
			SERVER_MESSAGE = "YOUR NEW BALANCE";
			ac_s.show_account();
			int pos = (-1) * static_cast<int>(sizeof(ac_s));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac_s), sizeof(account));
			cout << "\n\n\t Record Updated";
			SERVER_MESSAGE = "\n\n\t Record Updated";}
			else {
				cout << "\n\n\t Unsufficient Balance";
				SERVER_MESSAGE = "\n\n\t  Unsufficient Balance";
			}
			
			found = true;
		}

	}
	ac_s.show_account();

	File.close();

	found = false;
	File.open("account.dat", ios::binary | ios::in | ios::out);//ALICI
	if (found == false)
		cout << "\n\n Record Not Found ";
	SERVER_MESSAGE = "\n\n Record Not Found ";
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		SERVER_MESSAGE = "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac_r), sizeof(account));
		if (ac_r.retacno() == acno_r)
		{
			if (amount + transitionCharge < ac_s.retdeposit()) {
				ac_r.dep(amount);
				int pos = (-1) * static_cast<int>(sizeof(ac_r));
				File.seekp(pos, ios::cur);
				File.write(reinterpret_cast<char*> (&ac_r), sizeof(account));
				cout << "\n\n\t Record Updated";
				SERVER_MESSAGE = "\n\n\t Record Updated";
			}
			found = true;
		}


	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
	SERVER_MESSAGE = "\n\n Record Not Found ";


}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout << "\n\n\n\t  MONEY";
	cout << "\n\n\TRANSFER";
	cout << "\n\n\t  SIMULATION";
	SERVER_MESSAGE = "\n\n\n\t  MONEY\n\n\TRANSFER\n\n\t  SIMULATION";
	//cin.get();
}