#include <iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include <vector>
#include <conio.h>
#include <algorithm>

using namespace std;

bool separation = true;

struct Account
{
	string login;
	string password;
	int role;
};

struct Theater
{
	struct Date 
	{
		int Day;
		int Month;
		int Year;
	}Date;
	string nameOfTheater;
	string performance;
	int ticketSold;
};

struct TheaterAtoZ {
	bool operator()(const Theater& lhs, const Theater& rhs) const
	{
		return lhs.nameOfTheater < rhs.nameOfTheater;
	}
};

struct TheaterZtoA {
	bool operator()(const Theater& lhs, const Theater& rhs) const
	{
		return lhs.nameOfTheater > rhs.nameOfTheater;
	}
};

struct PerformanceAtoZ {
	bool operator()(const Theater& lhs, const Theater& rhs) const
	{
		return lhs.performance < rhs.performance;
	}
};

struct PerformanceZtoA {
	bool operator()(const Theater& lhs, const Theater& rhs) const
	{
		return lhs.performance > rhs.performance;
	}
};

int inNum();
int rangeOfNumbers(int, int);
string enterPassword();
string checkingTheLoginForTheNumberOfCharacters(string login);
string checkingThePasswordForTheNumberOfCharacters(string password);
int menuOfAutorization();
void coreOfAutorization(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance);
int adminMenu();
void adminCore(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance);
void separationOfRights(vector<Account>& accountVector, vector<Theater>& vectorPerformance);
void autorization(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance);
void showAccounts(vector<Account>& accountOfUsers);
void writeAccounts(vector<Account>& accountOfUsers);
void registration(vector<Account>& accountOfUsers);
void addAdminAccount(vector<Account>& accountOfUsers);
void addAccount(vector<Account>& accountOfUsers);
void updateAccount(vector<Account>& accountOfNewUsers);
void deleteAccount(vector<Account>& accountOfUsers);
void menuDate(vector<Theater>& vectorPerformance);
int editingMenu();
void coreOfEditing(vector<Theater>& vectorPerformance);
void showInfo(vector<Theater>& vectorPerformance);
void readInfo(vector<Theater>& vectorPerformance);
void writeInfo(vector<Theater>& vectorPerformance);
void addInfo(vector<Theater>& vectorPerformance);
void updateInfo(vector<Theater>& vectorPerformance);
void deleteInfo(vector<Theater>& vectorPerformance);
int processingMenu();
void coreOfProcessing(vector<Theater>& vectorPerformance);
int individualTaskMenu();
void individualTaskCore(vector<Theater>& vectorPerformance);
void mostPopularPerformance(vector<Theater>& vectorPerformance);
void mostPopularTheater(vector<Theater>& vectorPerformance);
int searchMenu();
void searchCore(vector<Theater>& vectorPerformance);
void searchByDate(vector<Theater>& vectorPerformance);
void searchByTheaterName(vector<Theater>& vectorPerformance);
void searchByPerformanceName(vector<Theater>& vectorPerformance);
int sortingMenu();
void coreOfSorting(vector<Theater>& vectorPerformance);
void sortingToTheOldestPerformance(vector<Theater>& vectorPerformance);
void sortingToTheNearestPerformance(vector<Theater>& vectorPerformance);
void sortingByTheaterNameAtoZ(vector<Theater>& vectorPerformance);
void sortingByTheaterNameZtoA(vector<Theater>& vectorPerformance);
void sortingByPerformanceNameAtoZ(vector<Theater>& vectorPerformance);
void sortingByPerformanceNameZtoA(vector<Theater>& vectorPerformance);
void sortinByTheNumberOfTicketsSoldMintoMax(vector<Theater>& vectorPerformance);
void sortinByTheNumberOfTicketsSoldMaxToMin(vector<Theater>& vectorPerformance);
int userMenu();
void coreUser(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance);

const string FILE_OF_ACCOUNT = "Account.txt";
const string FILE_OF_THEATER = "Theater.txt";


int inNum() // �������� �� Int
{
	int menuItemNumber;
	while (true)
	{
		cin >> menuItemNumber;
		if (cin.get() == '\n')
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "������������ ����!\n";
		}
	}
	return menuItemNumber;
}

int rangeOfNumbers(int min, int max) // �������� �� �������� ����
{
	int dateNumber;
	while (true)
	{
		cin >> dateNumber;
		if (cin.get() == '\n')
		{
			if (dateNumber >= min && dateNumber <= max)
				break;
			else
			{
				cout << "������� �������� �� " << min << " �� " << max << "!\n";
			}
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "������������ ����!\n";
		}
	}
	return dateNumber;
}

int main() // ����
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<Account> users;
	vector<Theater> theaters;
	addAdminAccount(users);
	readInfo(theaters);
	coreOfAutorization(users, theaters);
}

string enterPassword() // ������ ����� ������ �� *
{
		string password;
		while (true)
		{
			char c = _getch();
			if (c == 13) // Enter
			{
				if (password.length() != 0)
					break;
			}
			else if (c == 8) // Backspace
			{
				if (password.length() != 0)
				{
					cout << "\b \b";
					password.pop_back();
				}
			}
			else if (c != 32)
			{
				password += c;
				cout << '*';
			}
		}
		cout << endl;
		return password;
}

string checkingTheLoginForTheNumberOfCharacters(string login)
{
	string loginTemp;
	while (true)
	{
		cout << "������� �����: ";
		cin >> loginTemp;
		if (loginTemp.length() < 3)
		{
			cout << "����� �� ������ ��������� ����� 3-� ��������!\n";
		}
		else break;
	}
	return loginTemp;
}

string checkingThePasswordForTheNumberOfCharacters(string password)
{
	string passwordTemp;
	while (true)
	{
		passwordTemp = enterPassword();
		if (passwordTemp.length() < 3)
		{
			cout << "������ �� ������ ��������� ����� 3-� ��������!\n";
		}
		else break;
	}
	return passwordTemp;
}

int menuOfAutorization() // ���� �����������
{
	cout << "----- ���� ����������� -----\n\n";
	cout << " 1 � �����������\n";
	cout << " 2 � ����������� ������ ��������\n";
	cout << " 0 � ����� �� ���������\n";
	int num;
	num = rangeOfNumbers(0,2);
	return num;
}

void coreOfAutorization(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) // ������ � ���� �����������
{
	bool flag = true;
	while (flag)
	{
		int menuItemNumber = menuOfAutorization();
		switch (menuItemNumber)
		{
		case 1: 
		{
			system("cls");
			autorization(accountOfUsers, vectorPerformance);
			
			break;
		}
		case 2:
		{
			system("cls");
			registration(accountOfUsers);
			break;

		}
		case 0: 
		{
			system("cls");
			flag = false;
			break;
		}
		}
	}
}

void autorization(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) // ����������� ��������
{
	cout << "	<�����������>\n\n";
	bool error = true;
	bool exit = false;
	while (error)
	{
		cout << "������� 0 � ����� ���� ����� ��������� � ���� �����������\n\n";
		string login;
		cout << "������� �����: ";
		cin >> login;
		cout << "������� ������: ";
		string password = enterPassword();

		if (login == "0" || password == "0")
		{
			error = false;
			exit = true;
		}
		for (int i = 0; i < accountOfUsers.size(); i++)
		{
			if (accountOfUsers[i].login == login && accountOfUsers[i].password == password)
			{
				if (accountOfUsers[i].role == 1)
				{
					separation = true;
				}
				else
				{
					separation = false;
				}
				system("cls");
				cout << "	<�� ���������������� ��� " << accountOfUsers[i].login << ">\n\n";
				error = false;
				break;
			}
			else
			{
				system("cls");
				if (exit == false)
				{
					cout << "�������� ����� ��� ������! ��������� �������.\n\n";
				}
			}
		}
	}
	if (exit == false)
	{
		separationOfRights(accountOfUsers, vectorPerformance);
	}
}

void separationOfRights(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) {
	if (separation == true) {
		adminCore(accountOfUsers, vectorPerformance);
	}
	else 
	{
		coreUser(accountOfUsers, vectorPerformance);
	}

}

int adminMenu() // ���� ������
{
	cout << "----- ���� �������������� -----\n\n";
	cout << " 1 � �������� ���� ������� �������\n";
	cout << " 2 � ���������� ����� ������� ������\n";
	cout << " 3 � �������������� ������� ������\n";
	cout << " 4 � �������� ������� ������\n";
	cout << " 5 � ������ � �������\n";
	cout << " 0 � ����� � ���� �����������\n";
	int num;
	num = rangeOfNumbers(0, 5);
	return num;
}

void adminCore(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) // ������ � ���� ������
{
	bool flag = true;
	while (flag)
	{
		int menuItemNumber = adminMenu();
		switch (menuItemNumber)
		{
		case 1:
		{
			system("cls");
			showAccounts(accountOfUsers);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			addAccount(accountOfUsers);
			system("cls");
			break;

		}
		case 3:
		{
			system("cls");
			updateAccount(accountOfUsers);
			break;

		}
		case 4:
		{
			system("cls");
			deleteAccount(accountOfUsers);
			break;

		}
		case 5:
		{
			system("cls");
			menuDate(vectorPerformance);
			system("cls");
			break;
		}
		case 0:
		{
			system("cls");
			flag = false;
			break;
		}
		}

	}
}

void showAccounts(vector<Account>& accountOfUsers)
{

	for (int i = 0; i < accountOfUsers.size(); i++)
	{
		if (accountOfUsers[i].role == 1)
		{
			cout << i + 1 << ") " << "�������������"
				<< ", ����� - " << accountOfUsers[i].login << " "
				<< ", ������ - " << accountOfUsers[i].password << " " << endl;
		}
		else
		{
			cout << i + 1 << ") " << "������������"
				<< ", ����� - " << accountOfUsers[i].login << " "
				<< ", ������ - " << accountOfUsers[i].password << " " << endl;
		}
	}
}

void writeAccounts(vector<Account>& accountOfUsers)  // ������ ��������� � ����
{
	ofstream fout(FILE_OF_ACCOUNT, ios::out);
	for (int i = 0; i < accountOfUsers.size(); i++)
	{
		fout << accountOfUsers[i].login << " " << accountOfUsers[i].password << " " << " " << accountOfUsers[i].role;
		if (i < accountOfUsers.size() - 1)
			fout << endl;
		
	}
	fout.close();
}

void registration(vector<Account>& accountOfUsers) // �������� �������� ������������
{
	Account new_account;
	cout << "		<�����������>\n\n";
	
	bool temp = true;
	string login;
	login = checkingTheLoginForTheNumberOfCharacters(login);
	while (temp)
	{
		for (int index = 0; index < accountOfUsers.size(); index++)
		{

			if (accountOfUsers.at(index).login == login)
			{
				cout << "\n����� �����. ����������� ������.\n" << endl;
				login = checkingTheLoginForTheNumberOfCharacters(login);
			}
			if (accountOfUsers.at(index).login != login)
			{
				temp = false;
				new_account.login = login;
			}
		}
	}

	string password;
	string passwordRepeated;
	int count = 0;
	do
	{
		if (count != 0)
		{
			cout << "������ �� ���������!" << endl;
		}
		cout << "\n������� ������: ";
		password = checkingThePasswordForTheNumberOfCharacters(password);
		cout << "\n�������� ������� ������: ";
		passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
		cout << endl;
		count++;
	} while (password != passwordRepeated);

	if (password == passwordRepeated)
	{
		new_account.password = password;
	}

	new_account.role = 0;
	accountOfUsers.push_back(new_account);
	ofstream fout(FILE_OF_ACCOUNT, ios::app);
	fout << endl;
	fout << new_account.login << " " << new_account.password << " " << " " << new_account.role;
	fout.close();
	system("cls");
	cout << "<������� ��� ������� ������>\n" << endl;
}

void addAdminAccount(vector<Account>& accountOfUsers) // ���������� �������� ������
{

	ifstream fin(FILE_OF_ACCOUNT, ios::in);
	if (!fin.is_open() || fin.peek() == EOF)
	{
		Account admin;
		admin.login = "admin";
		admin.password = "admin";
		admin.role = 1;
		accountOfUsers.push_back(admin);
		writeAccounts(accountOfUsers);
	}
	else
	{
		bool flag = true;
		while (!fin.eof())
		{
			Account new_account;
			fin >> new_account.login >> new_account.password >> new_account.role;
			while (flag)
			{
				if (new_account.login != "admin" && new_account.role != 1)
				{
					Account admin;
					admin.login = "admin";
					admin.password = "admin";
					admin.role = 1;
					accountOfUsers.push_back(admin);
				}
				flag = false;
			}
			accountOfUsers.push_back(new_account);
		}
	}
	fin.close();
}

void addAccount(vector<Account>& accountOfUsers) // ���������� ������ ��������
{
	Account new_account;
	cout << "\t<���������� ������ ��������>\n" << endl;
	cout << "������� 0 ��� ����, ����� ��������� � ���� ��������������\n\n";

	bool temp = true;
	string login, exit;
	cout << "������� �����: ";
	cin >> exit;
	if (exit == "0")
	{
		system("cls");
	}
	else
	{
		login = checkingTheLoginForTheNumberOfCharacters(login);
		while (temp)
		{
			for (int index = 0; index < accountOfUsers.size(); index++)
			{
				if (accountOfUsers.at(index).login == login)
				{
					cout << "\n����� �����. ����������� ������.\n" << endl;
					login = checkingTheLoginForTheNumberOfCharacters(login);
				}
				if (accountOfUsers.at(index).login != login)
				{
					temp = false;
					new_account.login = login;
				}
			}
		}


		string password;
		string passwordRepeated;
		int count = 0;
		do
		{
			if (count != 0)
			{
				cout << "������ �� ���������!" << endl;
			}
			cout << "\n������� ������: ";
			password = checkingThePasswordForTheNumberOfCharacters(password);
			cout << "\n�������� ������� ������: ";
			passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
			cout << endl;
			count++;
		} while (password != passwordRepeated);

		if (password == passwordRepeated)
		{
			new_account.password = password;
		}

		cout << "������� ����: ";
		new_account.role = rangeOfNumbers(0, 1);

		accountOfUsers.push_back(new_account);

		writeAccounts(accountOfUsers);
	}
}

void updateAccount(vector<Account>& accountOfUsers) // ��������� ���������� �������������
{
	cout << "----- �������������� ������� ������ -----\n\n";
	int number1;
	bool flag = true;
	while (flag)
	{
		int index;
		cout << "������� ����� ������� ������, ������� �� ������ ������������� | 0 - ������\n\n";
		showAccounts(accountOfUsers);
		cout << endl;
		index = rangeOfNumbers(0, accountOfUsers.size());
		
		switch (index)
		{
		default:
		{
			index--;
			if (accountOfUsers[index].role == 1)
			{
				system("cls");
				cout << "������� �������������� �� ����� ���� �������!\n\n";
				break;
			}
			else
			{
				cout << "----- ���� �������������� -----\n\n";
				cout << "����� ���������� ������������ �� ������ ��������?\n\n";
				cout << "1 - �����\n";
				cout << "2 - ������\n";
				cout << "3 - ���� ������������\n";
				cout << "4 - ��� ����������\n";
				cout << "0 - ����� � ���� ��������������\n";

				number1 = rangeOfNumbers(0, 4);
				switch (number1)
				{
				case 1:
				{
					bool temp = true;
					string login;
					login = checkingTheLoginForTheNumberOfCharacters(login);
					while (temp)
					{
						if (accountOfUsers.at(index).login == login)
						{
							cout << "\n����� �����. ����������� ������.\n" << endl;
							login = checkingTheLoginForTheNumberOfCharacters(login);
						}
						if (accountOfUsers.at(index).login != login)
						{
							temp = false;
							accountOfUsers[index].login = login;
						}
					}
					cout << endl;
					system("cls");
					cout << "<������ ������ ������ �������>\n\n";
					break;
				}
				case 2:
				{
					string password;
					string passwordRepeated;
					int count = 0;
					do
					{
						if (count != 0)
						{
							cout << "������ �� ���������!" << endl;
						}
						cout << "\n������� ������: ";
						password = checkingThePasswordForTheNumberOfCharacters(password);
						cout << "\n�������� ������� ������: ";
						passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
						cout << endl;
						count++;
					} while (password != passwordRepeated);

					if (password == passwordRepeated)
					{
						accountOfUsers[index].password = password;
					}
					system("cls");
					cout << "<������ ������ ������ �������>\n\n";
					break;
				}
				case 3:
					cout << "����� ���� ������������: ";
					accountOfUsers[index].role = rangeOfNumbers(0, 1);
					cout << endl;
					system("cls");
					cout << "<������ ���� ������������ ������ �������>\n\n";
					break;
				case 4:
				{
					bool temp = true;
					string login;
					login = checkingTheLoginForTheNumberOfCharacters(login);
					while (temp)
					{
						if (accountOfUsers.at(index).login == login)
						{
							cout << "\n����� �����. ����������� ������.\n" << endl;
							login = checkingTheLoginForTheNumberOfCharacters(login);
						}
						if (accountOfUsers.at(index).login != login)
						{
							temp = false;
							accountOfUsers[index].login = login;
						}
					}

					string password;
					string passwordRepeated;
					int count = 0;
					do
					{
						if (count != 0)
						{
							cout << "������ �� ���������!" << endl;
						}
						cout << "\n������� ������: ";
						password = checkingThePasswordForTheNumberOfCharacters(password);
						cout << "\n�������� ������� ������: ";
						passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
						cout << endl;
						count++;
					} while (password != passwordRepeated);

					if (password == passwordRepeated)
					{
						accountOfUsers[index].password = password;
					}


					cout << "����� ���� ������������: ";
					accountOfUsers[index].role = rangeOfNumbers(0, 1);
					cout << endl;
					system("cls");

					break;
				}
				case 0:
					system("cls");
					flag = false;
					break;
				}
				writeAccounts(accountOfUsers);
				break;
			}
		}
		case 0:
			system("cls");
			flag = false;
			break;
		}
	}
}

void deleteAccount(vector<Account>& accountOfUsers) // �������� ��������
{
	int number;
	bool flag = true;
	while (flag)
	{
		cout << "----- ���� �������� ������������� -----\n\n";

		showAccounts(accountOfUsers);

		cout << "\n������� ����� ��������, ������� �� ������ ������� | 0 - ������ :\n";

		int index;
		index = rangeOfNumbers(0, accountOfUsers.size());
		switch (index)
		{
		case 0:
		{
			system("cls");
			flag = false;
			break;
		}
		default:
			index--;
			int n = 0;
			for (int i = 0; i < accountOfUsers.size(); i++)
			{
				if (accountOfUsers[i].role == 1)
				{
					n++;
				}
			}
			if (n > 1)
			{
				cout << "�� �������, ��� ������ ������� " << accountOfUsers[index].login << "?\n";
				cout << "1 - ��, � ������\n";
				cout << "2 - ���, ��������� � ���� ��������������\n";
				number = rangeOfNumbers(1, 2);
				switch (number)
				{
				case 1:
				{
					accountOfUsers.erase(accountOfUsers.begin() + index);
					system("cls");
					break;
				}
				case 2:
				{
					system("cls");
					flag = false;
					break;
				}
				}
			}
			else
			{
				cout << "\n������ ������� ���������� ��������������!!!\n";
				Sleep(3000);
				system("cls");
				return;
			}
			writeAccounts(accountOfUsers);
			break;
		}
	}
}

void menuDate(vector<Theater>& vectorPerformance)
{

	bool flag = true;
	while (flag) {
		system("cls");
		cout << "----- ������ � ������� -----\n\n 1 - ����� ��������������\n 2 - ����� ��������� ������\n 0 - ����� � ���� ��������������\n";
		int menuItemNumber = rangeOfNumbers(0, 2);
		switch (menuItemNumber) {
		case 1:
			system("cls");
			coreOfEditing(vectorPerformance);
			break;
		case 2:
			system("cls");
			coreOfProcessing(vectorPerformance);
			break;
		case 0:
			system("cls");
			flag = false;
			break;
		}
	}
}

int editingMenu() // ���� �������������� ������
{
	cout << "----- ���� �������������� ������ -----\n\n";
	cout << " 1 - �������� ������\n";
	cout << " 2 - ���������� ������\n";
	cout << " 3 - �������������� ������\n";
	cout << " 4 - �������� ������\n";
	cout << " 0 � ����� � ���� ������ � �������\n";
	int num;
	num = rangeOfNumbers(0, 4);
	return num;
}

void coreOfEditing(vector<Theater>& vectorPerformance) // ���� ���� �������������� ������
{
	bool flag = true;
	while (flag)
	{
		int  menuItemNumber = editingMenu();
		switch (menuItemNumber) 
		{
		case 1: 
			system("cls");
			showInfo(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������� ������...";
			_getch();
			system("cls");
			break;
		case 2: 
			system("cls");
			addInfo(vectorPerformance);
			break;
		case 3: 
			system("cls");
			updateInfo(vectorPerformance);
			break;
		case 4: 
			system("cls");
			deleteInfo(vectorPerformance);
			break;
		case 0:
			system("cls");
			flag = false;
			break;
		}

	}
}

void showInfo(vector<Theater>& vectorPerformance) // ����� ���������� � ����������
{
	for (int i = 0; i < vectorPerformance.size(); i++)

		cout << i + 1 << ") " << vectorPerformance[i].Date.Day << "."
		<< vectorPerformance[i].Date.Month << "."
		<< vectorPerformance[i].Date.Year << ", �������� ������ � "
		<< vectorPerformance[i].nameOfTheater << ", �������� ��������� - "
		<< vectorPerformance[i].performance << ", ���������� ��������� ������� =  " 
		<< vectorPerformance[i].ticketSold << endl << endl;

}

void readInfo(vector<Theater>& vectorPerformance) // ������ � ���� ������
{

	ifstream fin(FILE_OF_THEATER, ios::in);
	if (!fin.is_open() || fin.peek() == EOF)
	{

	}
	else
	{
		while (!fin.eof())
		{
			Theater new_performance;
			fin >> new_performance.Date.Day >> new_performance.Date.Month >> new_performance.Date.Year >> 
				new_performance.nameOfTheater >> new_performance.performance >> new_performance.ticketSold;
			vectorPerformance.push_back(new_performance);
		}
	}
	fin.close();
}

void writeInfo(vector<Theater>& vectorPerformance)  // ������ ���������� � ���������� � ����
{
	ofstream fout(FILE_OF_THEATER);
	for (int i = 0; i < vectorPerformance.size(); i++)
	{
		fout << vectorPerformance[i].Date.Day << " " << vectorPerformance[i].Date.Month << " " << vectorPerformance[i].Date.Year << " " 
			<< vectorPerformance[i].nameOfTheater << " " << vectorPerformance[i].performance << " " << vectorPerformance[i].ticketSold;
		if (i < vectorPerformance.size() - 1)
			fout << endl;
	}
	fout.close();
}

void addInfo(vector<Theater>& vectorPerformance) // ���������� ������ ���������
{
	Theater new_performance;
	cout << "\t<���������� ������ ���������>\n" << endl;
	cout << "������� 0 ��� ����, ����� ��������� � ���� �������������� ������ \n\n";

	cout << "������� ���� ��������� (�������):\n";
	cout << "�����:";
	new_performance.Date.Month = rangeOfNumbers(0, 12);
	if (new_performance.Date.Month != 0)
	{
		if (new_performance.Date.Month == 1 || new_performance.Date.Month == 3 || new_performance.Date.Month == 5 || new_performance.Date.Month == 7 ||
			new_performance.Date.Month == 8 || new_performance.Date.Month == 10 || new_performance.Date.Month == 12)
		{
			cout << "����:";
			new_performance.Date.Day = rangeOfNumbers(1, 31);
		}
		if (new_performance.Date.Month == 2)
		{
			cout << "����:";
			new_performance.Date.Day = rangeOfNumbers(1, 28);
		}
		if (new_performance.Date.Month == 4 || new_performance.Date.Month == 6 || new_performance.Date.Month == 9 || new_performance.Date.Month == 11)
		{
			cout << "����:";
			new_performance.Date.Day = rangeOfNumbers(1, 30);
		}

		cout << "���:";
		new_performance.Date.Year = rangeOfNumbers(2021, 2022);

		cout << "������� �������� ������: ";
		cin >> new_performance.nameOfTheater;

		cout << "������� �������� ���������: ";
		cin >> new_performance.performance;

		cout << "������� ���������� ��������� �������: ";
		cin >> new_performance.ticketSold;

		vectorPerformance.push_back(new_performance);

		writeInfo(vectorPerformance);
		system("cls");
	}
	else
	{
		system("cls");
	}
}

void updateInfo(vector<Theater>& vectorPerformance) // ��������� ���������� � ����������
{
	cout << "----- �������������� ���������� � ���������� -----\n\n";
	int number1;
	bool flag = true;
	while (flag)
	{
		int index;
		cout << "������� ����� ���������, ���������� � ������� �� ������ �� �������� | 0 - ������\n\n";
		showInfo(vectorPerformance);
		cout << endl;
		
		index = rangeOfNumbers(0, vectorPerformance.size());
		
		switch (index)
		{
		default:
		{
			index--;
			cout << "----- ���� �������������� ���������� -----\n\n";
			cout << "����� ���������� � ��������� �� ������ ��������?\n\n";
			cout << "1 - ����\n";
			cout << "2 - �������� ������\n";
			cout << "3 - �������� ���������\n";
			cout << "4 - ���������� ��������� �������\n";
			cout << "5 - ��� ����������\n";
			cout << "0 - ����� � ���� �������������� ������\n";

			number1 = rangeOfNumbers(0, 5);
			switch (number1)
			{
			case 1:
			{
				system("cls");
				cout << "     <�������������� ����>\n\n";
				cout << "��� ������ ������� 0\n\n";
				cout << "������� ���� ��������� (�������):\n ";
				cout << "�����:";
				vectorPerformance[index].Date.Month = rangeOfNumbers(0, 12);
				if (vectorPerformance[index].Date.Month != 0)
				{
					if (vectorPerformance[index].Date.Month == 1 || vectorPerformance[index].Date.Month == 3 || vectorPerformance[index].Date.Month == 5 || vectorPerformance[index].Date.Month == 7 ||
						vectorPerformance[index].Date.Month == 8 || vectorPerformance[index].Date.Month == 10 || vectorPerformance[index].Date.Month == 12)
					{
						cout << "����:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 31);
					}
					if (vectorPerformance[index].Date.Month == 2)
					{
						cout << "����:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 28);
					}
					if (vectorPerformance[index].Date.Month == 4 || vectorPerformance[index].Date.Month == 6 || vectorPerformance[index].Date.Month == 9 || vectorPerformance[index].Date.Month == 11)
					{
						cout << "����:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 30);
					}

					cout << "���:";
					vectorPerformance[index].Date.Year = rangeOfNumbers(2021, 2022);
					break;
				}
				else
				{
					system("cls");
					flag = false;
					break;
				}
			}
			case 2:
			{
				cout << "������� �������� �����: ";
				cin >> vectorPerformance[index].nameOfTheater;
				cout << endl;
				break;
			}
			case 3:
			{
				cout << "������� �������� ���������: ";
				cin >> vectorPerformance[index].performance;
				cout << endl;
				break;
			}
			case 4:
			{
				cout << "������� ���������� ��������� �������: ";
				cin >> vectorPerformance[index].ticketSold;
				cout << endl;
				break;
			}
			case 5:
			{
				cout << "������� ���� ��������� (�������):\n ";
				cout << "�����:";
				vectorPerformance[index].Date.Month = rangeOfNumbers(0, 12);
				if (vectorPerformance[index].Date.Month != 0)
				{
					if (vectorPerformance[index].Date.Month == 1 || vectorPerformance[index].Date.Month == 3 || vectorPerformance[index].Date.Month == 5 || vectorPerformance[index].Date.Month == 7 ||
						vectorPerformance[index].Date.Month == 8 || vectorPerformance[index].Date.Month == 10 || vectorPerformance[index].Date.Month == 12)
					{
						cout << "����:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 31);
					}
					if (vectorPerformance[index].Date.Month == 2)
					{
						cout << "����:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 28);
					}
					if (vectorPerformance[index].Date.Month == 4 || vectorPerformance[index].Date.Month == 6 || vectorPerformance[index].Date.Month == 9 || vectorPerformance[index].Date.Month == 11)
					{
						cout << "����:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 30);
					}

					cout << "���:";
					vectorPerformance[index].Date.Year = rangeOfNumbers(2021, 2022);
					break;

				}

				cout << "������� �������� �����: ";
				cin >> vectorPerformance[index].nameOfTheater;

				cout << "������� �������� ���������: ";
				cin >> vectorPerformance[index].performance;
				cout << endl;

				cout << "������� ���������� ��������� �������: ";
				cin >> vectorPerformance[index].ticketSold;
				cout << endl;
				break;

				break;
			case 0:
				system("cls");
				flag = false;
				break;
			}
			writeInfo(vectorPerformance);
			break;
			}
		}
		case 0:
			system("cls");
			flag = false;
			break;
		}
	}
}

void deleteInfo(vector<Theater>& vectorPerformance) // �������� ���������� � ����������
{
	int number;
	bool flag = true;
	while (flag)
	{
		cout << "----- ���� �������� ���������� -----\n\n";

		showInfo(vectorPerformance);

		cout << "\n������� ����� ���������, ������� �� ������ ������� | 0 - ������ :\n";

		int index;
		index = rangeOfNumbers(0, vectorPerformance.size());
		switch (index)
		{
		case 0:
		{
			system("cls");
			flag = false;
			break;
		}
		default:
			index--;
			cout << "�� �������, ��� ������ ������� ��� ���������� � ��������� " << vectorPerformance[index].performance << "?\n";
			cout << "1 - ��, � ������\n";
			cout << "2 - ���, ��������� � ���� �������������� ������ \n";
			number = rangeOfNumbers(1, 2);
			switch (number)
			{
			case 1:
			{
				vectorPerformance.erase(vectorPerformance.begin() + index);
				system("cls");
				break;
			}
			case 2:
			{
				system("cls");
				flag = false;
				break;
			}
			}
		}
		writeInfo(vectorPerformance);
		break;
	}
		
}

int processingMenu()
{
	cout << "----- ���� ��������� ������ -----\n\n";
	cout << " 1 - �������������� �������\n";
	cout << " 2 - ����� ������\n";
	cout << " 3 - ���������� ������\n";
	cout << " 0 � ����� � ���� ������ � �������\n";
	int num;
	num = rangeOfNumbers(0, 3);
	return num;
}

void coreOfProcessing(vector<Theater>& vectorPerformance)
{
	bool flag = true;
	while (flag)
	{
		int  menuItemNumber = processingMenu();
		switch (menuItemNumber)
		{
		case 1:
		{
			system("cls");
			individualTaskCore(vectorPerformance);
			break;
		}
		case 2:
		{
			system("cls");
			searchCore(vectorPerformance);
			break;
		}
		case 3:
		{
			system("cls");
			coreOfSorting(vectorPerformance);
			break;
		}
		case 0:
		{
			system("cls");
			flag = false;
			break;
		}
		}
	}
}

int individualTaskMenu()
{
	cout << "----- ���� ���������������� ������� -----\n\n";
	cout << "1 - ������ ����� ���������� ������� �� ��������� �����\n";
	cout << "2 - ������ ����� ���������� ���������� �� ��������� �����\n";
	cout << "0 - ����� � ���� ��������� ������\n";
	int num;
	num = rangeOfNumbers(0, 2);
	return num;
}

void individualTaskCore(vector<Theater>& vectorPerformance)
{
	bool flag = true;
	while (flag)
	{
		int  menuItemNumber = individualTaskMenu();
		switch (menuItemNumber)
		{
		case 1:
		{
			system("cls");
			mostPopularTheater(vectorPerformance);
			break;
		}
		case 2:
		{
			system("cls");
			mostPopularPerformance(vectorPerformance);
			break;
		}
		
		case 0:
		{
			system("cls");
			flag = false;
			break;
		}
		}
	}
}

void mostPopularTheater(vector<Theater>& vectorPerformance)
{
	vector<Theater>additionalVector;
	vector<Theater>vectorSum;
	vectorSum.reserve(100);

	int year, month;
	cout << "C���� ���������� ������ �� ����� ����� � ������ ���� �� ������ ������?\n\n";
	cout << "���: ";
	year = rangeOfNumbers(2021, 2022);
	cout << "\n�����: ";
	month = rangeOfNumbers(1, 12);
	cout << endl;

	for (int i = 0; i < vectorPerformance.size(); i++)
	{
		if (year == vectorPerformance[i].Date.Year && month == vectorPerformance[i].Date.Month)
		{
			additionalVector.push_back(vectorPerformance[i]);
		}
	}

	sort(additionalVector.begin(), additionalVector.end(), TheaterAtoZ());

	
	int o = 0;
	int amountOfTicketsSold, amountOfTicketsSold2;
	bool flag;

	for (int k = 0; k < additionalVector.size(); k++)
	{
		flag = false;
		amountOfTicketsSold = additionalVector[k].ticketSold;

		for (int j = k + 1; j < additionalVector.size(); j++)
		{
			if (additionalVector[k].nameOfTheater == additionalVector[j].nameOfTheater)
			{
				amountOfTicketsSold2 = amountOfTicketsSold + additionalVector[j].ticketSold;
				flag = true;
			}
		}


		if (flag)
		{
			vectorSum.push_back(additionalVector[k]); vectorSum[o].ticketSold = amountOfTicketsSold2;
			o++;
		}
		else
		{
			vectorSum.push_back(additionalVector[k]);
			o++;
		}

		

		for (int z = k + 1; z < additionalVector.size(); z++)
		{
			if (additionalVector[k].nameOfTheater == additionalVector[z].nameOfTheater)
			{
				additionalVector.erase(additionalVector.begin() + z);
			}
		}

		
	}

	cout << "-----------------------------------------------------------\n\n";

	for (int i = 0; i < vectorSum.size() - 1; i++)
	{
		for (int j = i + 1; j < vectorSum.size(); j++)
		{
			if (vectorSum[j].ticketSold > vectorSum[i].ticketSold)
			{
				swap(vectorSum[j], vectorSum[i]);
			}
		}
	}

	for (int i = 0; i < vectorSum.size(); i++)
	{
		cout << i + 1 << ") " << "�������� ������ - " << vectorSum[i].nameOfTheater << ", " << "����� ��������� ������� - " << vectorSum[i].ticketSold << endl << endl;
	}
	

	cout << "���������� ������ �������. ������������� �� ������������ ������ �� " << year << " ��� � " << month << " �����.\n\n";
	cout << "������� ����� �������, ����� ��������� ������� � ���� ������...";
	_getch();
	system("cls");
}

void mostPopularPerformance(vector<Theater>& vectorPerformance)
{
	vector<Theater>Temp;
	int n = 0;
	int year, month;
	cout << "C���� ���������� ��������� �� ����� ����� � ������ ���� �� ������ ������?\n\n";
	cout << "���: ";
	year = rangeOfNumbers(2021, 2022);
	cout << "\n�����: ";
	month = rangeOfNumbers(1, 12);
	cout << endl << "--------------------------------------------------------------------------------------------------\n\n";

	for (int i = 0; i < vectorPerformance.size(); i++)
	{
		if (year == vectorPerformance[i].Date.Year && month == vectorPerformance[i].Date.Month)
		{
			Temp.push_back(vectorPerformance[i]);
		}
	}

	for (int i = 1; i < Temp.size(); i++)
	{
		for (int j = 0; j < Temp.size()-1; j++)
		{
			if (Temp[j].ticketSold < Temp[i].ticketSold)
			{
				swap(Temp[j], Temp[i]);
			}
		}
	}

	for (int i = 0; i < Temp.size(); i++)
	{
		cout << n + 1 << ") " << Temp[i].Date.Day << "." << Temp[i].Date.Month << "." << Temp[i].Date.Year << "	" <<
			"�������� ������ - " << Temp[i].nameOfTheater << ", " << "�������� ��������� - " << Temp[i].performance << ", " << "���������� ��������� ������� - " << Temp[i].ticketSold << endl << endl;
		n++;
	}

	if (n == 0)
	{
		cout << "���������� � ���� ����� ���!\n\n";
		Sleep(3000);
		system("cls");
	}

	cout << "���������� ������ �������. ������������� �� ������������ ��������� �� " << year << " ��� � " << month << " �����.\n\n";
	cout << "������� ����� �������, ����� ��������� ������� � ���� ������...";
	_getch();
	system("cls");

}

int searchMenu()
{
	cout << "----- ���� ������ -----\n\n";
	cout << " 1 - ����� �� ���� ���������\n";
	cout << " 2 - ����� �� �������� ������\n";
	cout << " 3 - ����� �� �������� ���������\n";
	cout << " 0 � ����� � ���� ��������� ������\n";
	int num;
	num = rangeOfNumbers(0, 3);
	return num;
}

void searchCore(vector<Theater>& vectorPerformance)
{
	bool flag = true;
	while (flag)
	{
		int  menuItemNumber = searchMenu();
		switch (menuItemNumber)
		{
		case 1:
		{
			system("cls");
			searchByDate(vectorPerformance);
			break;
		}
		case 2:
		{
			system("cls");
			searchByTheaterName(vectorPerformance);
			break;
		}
		case 3:
		{
			system("cls");
			searchByPerformanceName(vectorPerformance);
			break;
		}
		case 0 :
		{
			system("cls");
			flag = false;
			break;
		}
		}
	}
}

void searchByDate(vector<Theater>& vectorPerformance)
{
	cout << "----- ����� -----\n\n";
	cout << "������� ������ ���� ��������� | 0 - ��� ����, ����� ��������� � ���� ������ \n";

	cout << "���: ";
	int year = rangeOfNumbers(0,2022);
	cout << endl;

	cout << "�����: ";
	int month = rangeOfNumbers(1, 12);
	cout << endl;

	cout << "����: ";
	int day = rangeOfNumbers(1, 31);
	cout << endl;

	bool flag = true;
	while (flag)
	{
		if (year == 0)
		{
			flag = false;
			break;
		}
		else
		{
			int n = 0;
			cout << "������� ������:" << endl << endl;
			for (auto iter = vectorPerformance.begin(); iter != vectorPerformance.end(); iter++)
			{
				if (year == iter->Date.Year && day == iter->Date.Day && month == iter->Date.Month)
				{
					cout <<  n+1 << ") " << (*iter).Date.Day << "." << (*iter).Date.Month << "." << (*iter).Date.Year << "	" <<
						"�������� ������ - " << (*iter).nameOfTheater << ", " << "�������� ��������� - " << (*iter).performance << ", " << "���������� ��������� ������� - " << (*iter).ticketSold << endl << endl;
					n++;

				}
			}

			flag = false;

			if (n ==0)
			{
				cout << "���������� � ���� ���� ���!\n\n";
				Sleep(3000);
				system("cls");
				break;
			}

		}
		cout << "������� ����� �������, ����� ��������� ������� � ���� ������...";
		_getch();
		system("cls");
	}
}

void searchByTheaterName(vector<Theater>& vectorPerformance)
{
	cout << "----- ����� -----\n\n";
	cout << "������� �������� ������ | 0 - ��� ����, ����� ��������� � ���� ������ \n";

	cout << "��������: ";
	string nameOfTheater;
	cin >> nameOfTheater;
	cout << endl;

	bool flag = true;
	while (flag)
	{
		if (nameOfTheater == "0")
		{
			flag = false;
			break;
		}
		else
		{
			int n = 0;
			cout << "������� ������:" << endl << endl;
			for (auto iter = vectorPerformance.begin(); iter != vectorPerformance.end(); iter++)
			{
				if (nameOfTheater == iter->nameOfTheater)
				{
					cout << n + 1 << ") " << (*iter).Date.Day << "." << (*iter).Date.Month << "." << (*iter).Date.Year << "	" <<
						"�������� ������ - " << (*iter).nameOfTheater << ", " << "�������� ��������� - " << (*iter).performance << ", " << "���������� ��������� ������� - " << (*iter).ticketSold << endl << endl;
					n++;

				}
			}

			flag = false;

			if (n == 0)
			{
				cout << "� ���� ������ ������� � ����� ��������� ���!\n\n";
				Sleep(3000);
				system("cls");
				break;
			}

		}
		cout << "������� ����� �������, ����� ��������� ������� � ���� ������...";
		_getch();
		system("cls");
	}
}

void searchByPerformanceName(vector<Theater>& vectorPerformance)
{
	cout << "----- ����� -----\n\n";
	cout << "������� �������� ��������� | 0 - ��� ����, ����� ��������� � ���� ������ \n";

	cout << "��������: ";
	string performanceName;
	cin >> performanceName;
	cout << endl;

	bool flag = true;
	while (flag)
	{
		if (performanceName == "0")
		{
			flag = false;
			break;
		}
		else
		{
			int n = 0;
			cout << "������� ������:" << endl << endl;
			for (auto iter = vectorPerformance.begin(); iter != vectorPerformance.end(); iter++)
			{
				if (performanceName == iter->performance)
				{
					cout << n + 1 << ") " << (*iter).Date.Day << "." << (*iter).Date.Month << "." << (*iter).Date.Year << "	" <<
						"�������� ������ - " << (*iter).nameOfTheater << ", " << "�������� ��������� - " << (*iter).performance << ", " << "���������� ��������� ������� - " << (*iter).ticketSold << endl << endl;
					n++;

				}
			}

			flag = false;

			if (n == 0)
			{
				cout << "� ���� ������ ���������� � ����� ��������� ���!\n\n";
				Sleep(3000);
				system("cls");
				break;
			}

		}
		cout << "������� ����� �������, ����� ��������� ������� � ���� ������...";
		_getch();
		system("cls");
	}
}

int sortingMenu()
{
	cout << "----- ���� ���������� -----\n\n";
	cout << " 1 - ���������� �� ���� ��������� (�� ���������� ��������� �� ������ �������)\n";
	cout << " 2 - ���������� �� ���� ��������� (�� ������ ������� �� ���������� ���������)\n";
	cout << " 3 - ���������� �� �������� ������ (�� � �� �)\n";
	cout << " 4 - ���������� �� �������� ������ (�� � �� �)\n";
	cout << " 5 - ���������� �� �������� ��������� (�� � �� �)\n";
	cout << " 6 - ���������� �� �������� ��������� (�� � �� �)\n";
	cout << " 7 - ���������� �� ���������� ��������� ������� (�� ������������ �������� �� ������������� ��������)\n";
	cout << " 8 - ���������� �� ���������� ��������� ������� (�� ������������� �������� �� ������������ ��������)\n";
	cout << " 0 � ����� � ���� ��������� ������\n";
	int num;
	num = rangeOfNumbers(0, 8);
	return num;
}

void coreOfSorting(vector<Theater>& vectorPerformance)
{
	bool flag = true;
	while (flag)
	{
		int  menuItemNumber = sortingMenu();
		switch (menuItemNumber)
		{
		case 1:
		{
			system("cls");
			sortingToTheOldestPerformance(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			sortingToTheNearestPerformance(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			sortingByTheaterNameAtoZ(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 4:
		{
			system("cls");
			sortingByTheaterNameZtoA(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");
			sortingByPerformanceNameAtoZ(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");
			sortingByPerformanceNameZtoA(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 7:
		{
			system("cls");
			sortinByTheNumberOfTicketsSoldMintoMax(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 8:
		{
			system("cls");
			sortinByTheNumberOfTicketsSoldMaxToMin(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������...";
			_getch();
			system("cls");
			break;
		}
		case 0: 
		{
			system("cls");
			flag = false;
			break;
		}
		}
	}
}

void sortingToTheOldestPerformance(vector<Theater>& vectorPerformance)
{
	for (int i = 0; i < vectorPerformance.size() - 1; i++)
	{
		for (int j = i + 1; j < vectorPerformance.size(); j++)
		{
			if (vectorPerformance[j].Date.Year > vectorPerformance[i].Date.Year)
			{
				swap(vectorPerformance[j], vectorPerformance[i]);
			}

			if (vectorPerformance[j].Date.Year == vectorPerformance[i].Date.Year)
			{
				if (vectorPerformance[j].Date.Month > vectorPerformance[i].Date.Month)
				{
					swap(vectorPerformance[j], vectorPerformance[i]);
				}
			}

			if (vectorPerformance[j].Date.Year == vectorPerformance[i].Date.Year)
			{
				if (vectorPerformance[j].Date.Month == vectorPerformance[i].Date.Month)
				{
					if (vectorPerformance[j].Date.Day > vectorPerformance[i].Date.Day)
					{
						swap(vectorPerformance[j], vectorPerformance[i]);
					}
				}
			}
		}
	}
	cout << "���������� ������ �������. ������������� �� ���� �� ���������� ��������� �� ������ �������\n\n";
	showInfo(vectorPerformance);
}

void sortingToTheNearestPerformance(vector<Theater>& vectorPerformance)
{
	for (int i = 0; i < vectorPerformance.size() - 1; i++)
	{
		for (int j = i + 1; j < vectorPerformance.size(); j++)
		{
			if (vectorPerformance[j].Date.Year < vectorPerformance[i].Date.Year)
			{
				swap(vectorPerformance[j], vectorPerformance[i]);
			}

			if (vectorPerformance[j].Date.Year == vectorPerformance[i].Date.Year)
			{
				if (vectorPerformance[j].Date.Month < vectorPerformance[i].Date.Month)
				{
					swap(vectorPerformance[j], vectorPerformance[i]);
				}
			}

			if (vectorPerformance[j].Date.Year == vectorPerformance[i].Date.Year)
			{
				if (vectorPerformance[j].Date.Month == vectorPerformance[i].Date.Month)
				{
					if (vectorPerformance[j].Date.Day < vectorPerformance[i].Date.Day)
					{
						swap(vectorPerformance[j], vectorPerformance[i]);
					}
				}
			}
		}
	}
	cout << "���������� ������ �������. ������������� �� ���� �� ������ ������� ��������� �� ����������\n\n";
	showInfo(vectorPerformance);
}

void sortingByTheaterNameAtoZ(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), TheaterAtoZ());
	cout << "���������� ������ �������. ������������� �� �������� ������ �� � �� �\n\n";
	showInfo(vectorPerformance);
}

void sortingByTheaterNameZtoA(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), TheaterZtoA());
	cout << "���������� ������ �������. ������������� �� �������� ������ �� � �� �\n\n";
	showInfo(vectorPerformance);
}

void sortingByPerformanceNameAtoZ(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), PerformanceAtoZ());
	cout << "���������� ������ �������. ������������� �� �������� ��������� �� � �� �\n\n";
	showInfo(vectorPerformance);
}

void sortingByPerformanceNameZtoA(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), PerformanceZtoA());
	cout << "���������� ������ �������. ������������� �� �������� ��������� �� � �� �\n\n";
	showInfo(vectorPerformance);
}

void sortinByTheNumberOfTicketsSoldMintoMax(vector<Theater>& vectorPerformance)
{
	for (int i = 0; i < vectorPerformance.size() - 1; i++)
	{
		for (int j = i + 1; j < vectorPerformance.size(); j++)
		{
			if (vectorPerformance[j].ticketSold < vectorPerformance[i].ticketSold)
			{
				swap(vectorPerformance[j], vectorPerformance[i]);
			}
		}
	}
	cout << "���������� ������ �������. ������������� �� ���������� ��������� ������� �� ������������ �� ������������� ��������\n\n";
	showInfo(vectorPerformance);
}

void sortinByTheNumberOfTicketsSoldMaxToMin(vector<Theater>& vectorPerformance)
{
	for (int i = 0; i < vectorPerformance.size() - 1; i++)
	{
		for (int j = i + 1; j < vectorPerformance.size(); j++)
		{
			if (vectorPerformance[j].ticketSold > vectorPerformance[i].ticketSold)
			{
				swap(vectorPerformance[j], vectorPerformance[i]);
			}
		}
	}
	cout << "���������� ������ �������. ������������� �� ���������� ��������� ������� �� ������������� �� ������������ ��������\n\n";
	showInfo(vectorPerformance);
}

int userMenu()
{
	cout << "-------------- ���� ������������ --------------\n\n";
	cout << " 1 � �������� ������\n";
	cout << " 2 - �������� ����� ���������� �������/���������� �� ����� (�������������� �������)\n";
	cout << " 3 � ����� ������\n";
	cout << " 4 � ����������\n";
	cout << " 0 � ����� � ���� �����������\n";
	int num;
	num = rangeOfNumbers(0, 3);
	return num;
}

void coreUser(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance)
{
	bool flag = true;
	while (flag)
	{
		int  menuItemNumber = userMenu();
		switch (menuItemNumber)
		{
		case 1:
		{
			system("cls");
			showInfo(vectorPerformance);
			cout << endl << "������� ����� �������, ����� ��������� ������� � ���� �������������� ������...";
			_getch();
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			individualTaskCore(vectorPerformance);
			break;
		}
		case 3:
		{
			system("cls");
			searchCore(vectorPerformance);
			break;
		}
		case 4:
		{
			system("cls");
			coreOfSorting(vectorPerformance);
			break;
		}
		case 0:
		{
			system("cls");
			flag = false;
			break;
		}
		}
	}
}
