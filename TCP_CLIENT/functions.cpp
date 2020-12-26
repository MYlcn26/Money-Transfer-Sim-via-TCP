#include "functions.h"
#include "Class.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <string.h>

#include <WS2tcpip.h>
#include <cctype>
#pragma comment(lib, "ws2_32.lib")

string MESSAGE;

string& returnString(string& n) {
	n.clear();
	n = MESSAGE;
	return n;
}

void main_menu() {
	cout << "\n\n\n\tMAIN MENU";
	cout << "\n\n\t01. NEW ACCOUNT";
	cout << "\n\n\t02. DEPOSIT AMOUNT";
	cout << "\n\n\t03. WITHDRAW AMOUNT";
	cout << "\n\n\t04. BALANCE ENQUIRY";
	cout << "\n\n\t05. TRANSFER MONEY";
	cout << "\n\n\t06. EXIT";
	cout << "\n\n\t07. ALL ACCOUNT HOLDER LIST";
	cout << "\n\n\t08. CLOSE AN ACCOUNT";
	cout << "\n\n\t09. MODIFY AN ACCOUNT";

	cout << "\n\n\tSelect Your Option (1-9) ";
}

void select_operation(char ch) {
	int num, num2, num3;

	switch (ch)
	{
	case '1':
		write_account();
		break;
	case '2':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		deposit_withdraw(num, 1);
		break;
	case '3':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		deposit_withdraw(num, 2);
		break;
	case '4':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		display_sp(num);
		break;
	case '5':
		cout << "\n\n\tEnter The sender account No. : "; cin >> num;
		cout << "\n\n\tEnter The reciever account No. : "; cin >> num2;
		cout << "\n\n\tEnter amount : "; cin >> num3;
		transfer_money(num3, num, num2);
		break;
	case '6':
		cout << "\n\n\tThanks for using bank managemnt system";
		break;
	case '7':
		display_all();
		break;
	case '8':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		delete_account(num);
		break;
	case '9':
		cout << "\n\n\tEnter The account No. : "; cin >> num;
		modify_account(num);
		break;

	default:cout << "\a";
	}
}
//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
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
		return;
	}
	cout << "\nBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nAccount number does not exist";
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
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
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
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n====================================================\nA/c no.      NAME           Type  Balance========\n\n============================================\n\n";
	MESSAGE= "\n\n\t\tACCOUNT HOLDER LIST\n\n====================================================\nA/c no.      NAME           Type  Balance=======\n\n=============================================\n\n";
	
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();

}

//***************************************************************
//    	function to deposit , withdraw and transfer amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
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
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}
void transfer_money(int amount, int acno_s, int acno_r) {
	bool found = false;
	account ac_s;
	account ac_r;
	fstream File;
	
	File.open("account.dat", ios::binary | ios::in | ios::out);//YOLLAYAN
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac_s), sizeof(account));
		if (ac_s.retacno() == acno_s)
		{
			ac_s.draw(amount);
			cout << "YOUR NEW BALANCE";
			ac_s.show_account();
			int pos = (-1) * static_cast<int>(sizeof(ac_s));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac_s), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}

	}
	File.close();

	found = false;
	File.open("account.dat", ios::binary | ios::in | ios::out);//ALICI
	if (found == false)
		cout << "\n\n Record Not Found ";
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac_r), sizeof(account));
		if (ac_r.retacno() == acno_r)
		{
			ac_r.dep(amount);
			int pos = (-1) * static_cast<int>(sizeof(ac_r));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac_r), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}


	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";

	
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	cout << "\n\n\n\t  BANK";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************