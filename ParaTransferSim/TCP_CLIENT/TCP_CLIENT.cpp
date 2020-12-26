#include "Client.h"

int ch;
int num1 = 0, num2 = 0, num3 = 0;
using namespace std;
string DATAPACK_s;
string userName;
string userPassword;
string loginDatapack;
bool loggedIn=false;
bool isAdmin = false;

void main()
{
	intro();
	string ipAddress = "127.0.0.1";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// Do-while loop to send and receive data
	char buf[4096];
//	string userInput;
	x:
	while( loggedIn == false){
	cout << "Username:"; cin >> userName;
	cout << "Password"; cin >> userPassword;
	loginDatapack = userName + "*" + userPassword + "*";
	send(sock, loginDatapack.c_str(), loginDatapack.size() + 1, 0);
	int bytesReceived =  recv(sock, buf, 4096, 0);
	cout << string(buf, 0, bytesReceived) << endl;

	if (string(buf, 0, bytesReceived) == "TRUE") {
		loggedIn = true;
		isAdmin = false;
	}
	else if (string(buf, 0, bytesReceived) == "ADMIN") {
		loggedIn = true;
		isAdmin = true;
	}
	if (loggedIn == true && isAdmin == false) { cout << "Welcome User"; }
	else { if (loggedIn == false)cout << "Please try again."; }
	if (loggedIn == true && isAdmin == true) { cout << "Welcome Admin"; }
	else { if(loggedIn == false)cout << "Please try again."; }
	}

	main_menu();
	do
	{
		// Prompt the user for some text

		if (loggedIn == true) {

			cout << "\n\n\tSELECT OPERATION: "; cin >> ch;

			
		// GET USER INPUTS
			switch (ch)
			{
			case 1:

				break;
			case 2:
				if (isAdmin) { cout << "\n\n\tEnter The account No. : "; cin >> num1; }
				cout << "\n\n\tEnter AMOUNT: : "; cin >> num2;

				break;
			case 3:
				if (isAdmin) { cout << "\n\n\tEnter The account No. : "; cin >> num1; }
				cout << "\n\n\tEnter AMOUNT: : "; cin >> num2;

				break;
			case 4:
				if (isAdmin) { cout << "\n\n\tEnter The account No. : "; cin >> num1; }

				break;
			case 5:
				if (isAdmin) { cout << "\n\n\tEnter The sender account No. : "; cin >> num1; }
				cout << "\n\n\tEnter The reciever account No. : "; cin >> num2;
				cout << "\n\n\tEnter amount : "; cin >> num3;

				break;
			case 6:
				cout << "\n\n\tThanks for using bank managemnt system";
				loggedIn = false;
				isAdmin = false;
				break;
			case 7:
				break;
			case 8:
				cout << "\n\n\tEnter The account No. : "; cin >> num1;
				break;
			case 9:
				cout << "\n\n\tEnter The account No. : "; cin >> num1;
				break;

			default:cout << "\a";
			}
			/*DATA PACK*/
			DATAPACK_s = to_string(ch) + '*' + to_string(num1) + '*' + to_string(num2) + '*' + to_string(num3) + '*';
			/*DATA PACK*/
			/*RECIEVE DATA*/
			if (loggedIn) {
				if (DATAPACK_s.size() > 0)		// Make sure the user has typed in something
				{
					// Send to server
					int sendResult = send(sock, DATAPACK_s.c_str(), DATAPACK_s.size() + 1, 0);

					if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(sock, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Answer from Server
							cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
						}
					}
				}
			}
		}
		/*else {
			goto x;
			bool loggedIn = false;
			bool isAdmin = false;
		}*/
	} while (DATAPACK_s.size() > 0 || loginDatapack.size()>0);
	


	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
