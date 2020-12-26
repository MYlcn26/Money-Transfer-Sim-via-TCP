
void main_menu();
void select_operation(char,int,int,int,bool);
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int,int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function
void transfer_money(int amount, int acno_s, int acno_r); // money transfer
void readLoginData();
bool checkBank(int n1, int n2);