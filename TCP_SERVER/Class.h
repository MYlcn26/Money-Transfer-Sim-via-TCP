class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
	char  userData_c[20];
	int bankno;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int retacno() const;	//function to return account number
	int retbankno() const;
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account
	void readLoginData(int) const;


};
