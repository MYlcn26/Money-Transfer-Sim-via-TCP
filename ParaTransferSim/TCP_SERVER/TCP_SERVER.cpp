#include "Server.h"
using namespace std;
string DATAPACK;
string numString;
char ch;
string num_s[3];
int datapack_length;
int num[3];
string SERVER_MESSAGE="~";
bool loggedIn = false;
string login[2];
extern string userLoginData[20];
string trueMessage = "TRUE";
string adminMessage = "ADMIN";
bool isAdmin = false;
extern int loggedAccount;

void main()
{
	num_s[0] = "";
	num_s[1] = "";
	num_s[2] = "";
	login[0] = "";
	login[1] = "";
	readLoginData();
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);

	// Wait for a connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	// Close listening socket
	closesocket(listening);

	// While loop: accept and echo message back to client
	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);

		// Wait for client to send data
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "Client disconnected " << endl;
			break;
		}
		cout << "\nBuffer";
		cout << string(buf, 0, bytesReceived) << endl;

		/*DATAPACK*/
		

		if (loggedIn == true) {
			DATAPACK = string(buf, 0, bytesReceived);
			ch = buf[0];

			if (buf[1] != '*') { cout << "Please enter a appropriate operation number"; }
			int a = 0;
			num_s[0] = "";
			num_s[1] = "";
			num_s[2] = "";
			for (int i = 2; i < bytesReceived + 1; i++) {
				if (buf[i] == '*') {


					stringstream toInt(num_s[a]);
					toInt >> num[a];
					a++;
				}
				else {
					num_s[a] = num_s[a] + (buf[i]);
				}
			}
		}
		/*DATAPACK RESOLVE*/
		/*LOGIN DATA RESOLVE*/
		else {

		readLoginData();
		string buffLoginData = string(buf, 0, bytesReceived);
		for(int i=0; i<10; i++){
			if (userLoginData[i] == buffLoginData) {
				isAdmin = false;
				loggedIn = true;
				loggedAccount = i;
				send(clientSocket, trueMessage.c_str(), trueMessage.size() + 1, 0);// SERVER TRUE MESSAGE
			}}
			 if ("admin*admin*" == string(buf, 0, bytesReceived)) {
				loggedIn = true;
				isAdmin = true;
				send(clientSocket, adminMessage.c_str(), adminMessage.size() + 1, 0);// SERVER TRUE MESSAGE
			}
			else {
				 if(loggedIn == false && isAdmin == false){
				cout << "Invalid Username or Password" << endl;
			}}
		}
		/*LOGIN DATA RESOLVE*/
		if (isAdmin == FALSE) {
			num[0] = loggedAccount;
			cout << "LOGGED ACCOUNT NO:";
			cout << loggedAccount << endl;
			select_operation(ch, num[0], num[1], num[2],isAdmin);
		}
		else {
			cout << "LOGGED ACCOUNT NO: ADMIN";
			select_operation(ch, num[0], num[1], num[2], isAdmin);

		}
	
			// Answer to client
		//	send(clientSocket, buf, bytesReceived + 1, 0);
			send(clientSocket, SERVER_MESSAGE.c_str(), SERVER_MESSAGE.size() + 1, 0);// SERVER MESSAGE

		}

		// Close the socket
		closesocket(clientSocket);

		// Cleanup winsock
		WSACleanup();

		system("pause");
	}