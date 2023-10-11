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


int inNum() // проверка на Int
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
			cout << "Некорректный ввод!\n";
		}
	}
	return menuItemNumber;
}

int rangeOfNumbers(int min, int max) // проверка на диапазон даты
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
				cout << "Введите значение от " << min << " до " << max << "!\n";
			}
		}
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Некорректный ввод!\n";
		}
	}
	return dateNumber;
}

int main() // Мейн
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

string enterPassword() // замена ввода пароля на *
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
		cout << "Введите логин: ";
		cin >> loginTemp;
		if (loginTemp.length() < 3)
		{
			cout << "Логин не должен содержать менее 3-х символов!\n";
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
			cout << "Пароль не должен содержать менее 3-х символов!\n";
		}
		else break;
	}
	return passwordTemp;
}

int menuOfAutorization() // Меню авторизации
{
	cout << "----- Меню авторизации -----\n\n";
	cout << " 1 — Авторизация\n";
	cout << " 2 — Регистрация нового аккаунта\n";
	cout << " 0 — Выход из программы\n";
	int num;
	num = rangeOfNumbers(0,2);
	return num;
}

void coreOfAutorization(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) // Работа с меню авторизации
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

void autorization(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) // Авторизация аккаунта
{
	cout << "	<Авторизация>\n\n";
	bool error = true;
	bool exit = false;
	while (error)
	{
		cout << "Введите 0 в любое поле чтобы вернуться в меню авторизации\n\n";
		string login;
		cout << "Введите логин: ";
		cin >> login;
		cout << "Введите пароль: ";
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
				cout << "	<Вы авторизировались как " << accountOfUsers[i].login << ">\n\n";
				error = false;
				break;
			}
			else
			{
				system("cls");
				if (exit == false)
				{
					cout << "Неверный логин или пароль! Повторите попытку.\n\n";
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

int adminMenu() // Меню админа
{
	cout << "----- Меню администратора -----\n\n";
	cout << " 1 — Просмотр всех учетных записей\n";
	cout << " 2 — Добавление новой учетной записи\n";
	cout << " 3 — Редактирование учетной записи\n";
	cout << " 4 — Удаление учетной записи\n";
	cout << " 5 — Работа с данными\n";
	cout << " 0 — Назад в меню авторизации\n";
	int num;
	num = rangeOfNumbers(0, 5);
	return num;
}

void adminCore(vector<Account>& accountOfUsers, vector<Theater>& vectorPerformance) // Работа с меню админа
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
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
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
			cout << i + 1 << ") " << "Администратор"
				<< ", логин - " << accountOfUsers[i].login << " "
				<< ", пароль - " << accountOfUsers[i].password << " " << endl;
		}
		else
		{
			cout << i + 1 << ") " << "Пользователь"
				<< ", логин - " << accountOfUsers[i].login << " "
				<< ", пароль - " << accountOfUsers[i].password << " " << endl;
		}
	}
}

void writeAccounts(vector<Account>& accountOfUsers)  // запись аккаунтов в файл
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

void registration(vector<Account>& accountOfUsers) // создание аккаунта пользователя
{
	Account new_account;
	cout << "		<Регистрация>\n\n";
	
	bool temp = true;
	string login;
	login = checkingTheLoginForTheNumberOfCharacters(login);
	while (temp)
	{
		for (int index = 0; index < accountOfUsers.size(); index++)
		{

			if (accountOfUsers.at(index).login == login)
			{
				cout << "\nЛогин занят. Используйте другой.\n" << endl;
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
			cout << "Пароли не совпадают!" << endl;
		}
		cout << "\nВведите пароль: ";
		password = checkingThePasswordForTheNumberOfCharacters(password);
		cout << "\nПовторно введите пароль: ";
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
	cout << "<Аккаунт был успешно создан>\n" << endl;
}

void addAdminAccount(vector<Account>& accountOfUsers) // добавление аккаунта админа
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

void addAccount(vector<Account>& accountOfUsers) // Добавление нового аккаунта
{
	Account new_account;
	cout << "\t<Добавление нового аккаунта>\n" << endl;
	cout << "Введите 0 для того, чтобы вернуться в меню администратора\n\n";

	bool temp = true;
	string login, exit;
	cout << "Введите логин: ";
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
					cout << "\nЛогин занят. Используйте другой.\n" << endl;
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
				cout << "Пароли не совпадают!" << endl;
			}
			cout << "\nВведите пароль: ";
			password = checkingThePasswordForTheNumberOfCharacters(password);
			cout << "\nПовторно введите пароль: ";
			passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
			cout << endl;
			count++;
		} while (password != passwordRepeated);

		if (password == passwordRepeated)
		{
			new_account.password = password;
		}

		cout << "Введите роль: ";
		new_account.role = rangeOfNumbers(0, 1);

		accountOfUsers.push_back(new_account);

		writeAccounts(accountOfUsers);
	}
}

void updateAccount(vector<Account>& accountOfUsers) // Изменение информации пользователей
{
	cout << "----- Редактирование учетной записи -----\n\n";
	int number1;
	bool flag = true;
	while (flag)
	{
		int index;
		cout << "Введите номер учетной записи, которую вы хотите редактировать | 0 - Отмена\n\n";
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
				cout << "Аккаунт администратора не может быть изменен!\n\n";
				break;
			}
			else
			{
				cout << "----- Меню редактирования -----\n\n";
				cout << "Какую информацию пользователя вы хотите изменить?\n\n";
				cout << "1 - Логин\n";
				cout << "2 - Пароль\n";
				cout << "3 - Роль пользователя\n";
				cout << "4 - Всю информацию\n";
				cout << "0 - Назад в меню администратора\n";

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
							cout << "\nЛогин занят. Используйте другой.\n" << endl;
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
					cout << "<Замена логина прошла успешно>\n\n";
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
							cout << "Пароли не совпадают!" << endl;
						}
						cout << "\nВведите пароль: ";
						password = checkingThePasswordForTheNumberOfCharacters(password);
						cout << "\nПовторно введите пароль: ";
						passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
						cout << endl;
						count++;
					} while (password != passwordRepeated);

					if (password == passwordRepeated)
					{
						accountOfUsers[index].password = password;
					}
					system("cls");
					cout << "<Замена пароля прошла успешно>\n\n";
					break;
				}
				case 3:
					cout << "Новая роль пользователя: ";
					accountOfUsers[index].role = rangeOfNumbers(0, 1);
					cout << endl;
					system("cls");
					cout << "<Замена роли пользователя прошла успешно>\n\n";
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
							cout << "\nЛогин занят. Используйте другой.\n" << endl;
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
							cout << "Пароли не совпадают!" << endl;
						}
						cout << "\nВведите пароль: ";
						password = checkingThePasswordForTheNumberOfCharacters(password);
						cout << "\nПовторно введите пароль: ";
						passwordRepeated = checkingThePasswordForTheNumberOfCharacters(password);
						cout << endl;
						count++;
					} while (password != passwordRepeated);

					if (password == passwordRepeated)
					{
						accountOfUsers[index].password = password;
					}


					cout << "Новая роль пользователя: ";
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

void deleteAccount(vector<Account>& accountOfUsers) // Удаление аккаунта
{
	int number;
	bool flag = true;
	while (flag)
	{
		cout << "----- Меню удаления пользователей -----\n\n";

		showAccounts(accountOfUsers);

		cout << "\nВведите номер аккаунта, который Вы хотите удалить | 0 - Отмена :\n";

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
				cout << "Вы уверены, что хотите удалить " << accountOfUsers[index].login << "?\n";
				cout << "1 - Да, я уверен\n";
				cout << "2 - Нет, вернуться в меню администратора\n";
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
				cout << "\nНельзя удалить последнего администратора!!!\n";
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
		cout << "----- Работа с данными -----\n\n 1 - Режим редактирования\n 2 - Режим обработки данных\n 0 - Назад в меню администратора\n";
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

int editingMenu() // меню редактирования данных
{
	cout << "----- Меню редактирования данных -----\n\n";
	cout << " 1 - Просмотр данных\n";
	cout << " 2 - Добавление данных\n";
	cout << " 3 - Редактирование данных\n";
	cout << " 4 - Удаление данных\n";
	cout << " 0 — Назад в меню работы с данными\n";
	int num;
	num = rangeOfNumbers(0, 4);
	return num;
}

void coreOfEditing(vector<Theater>& vectorPerformance) // Ядро меню редактирования данных
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
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню редактирования данных...";
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

void showInfo(vector<Theater>& vectorPerformance) // показ информации о спектаклях
{
	for (int i = 0; i < vectorPerformance.size(); i++)

		cout << i + 1 << ") " << vectorPerformance[i].Date.Day << "."
		<< vectorPerformance[i].Date.Month << "."
		<< vectorPerformance[i].Date.Year << ", название театра — "
		<< vectorPerformance[i].nameOfTheater << ", название спектакля - "
		<< vectorPerformance[i].performance << ", количество проданных билетов =  " 
		<< vectorPerformance[i].ticketSold << endl << endl;

}

void readInfo(vector<Theater>& vectorPerformance) // Запись в файл театра
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

void writeInfo(vector<Theater>& vectorPerformance)  // запись информации о спектаклях в файл
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

void addInfo(vector<Theater>& vectorPerformance) // Добавление нового спектакля
{
	Theater new_performance;
	cout << "\t<Добавление нового спектакля>\n" << endl;
	cout << "Введите 0 для того, чтобы вернуться в меню редактирования данных \n\n";

	cout << "Введите день спектакля (цифрами):\n";
	cout << "Месяц:";
	new_performance.Date.Month = rangeOfNumbers(0, 12);
	if (new_performance.Date.Month != 0)
	{
		if (new_performance.Date.Month == 1 || new_performance.Date.Month == 3 || new_performance.Date.Month == 5 || new_performance.Date.Month == 7 ||
			new_performance.Date.Month == 8 || new_performance.Date.Month == 10 || new_performance.Date.Month == 12)
		{
			cout << "День:";
			new_performance.Date.Day = rangeOfNumbers(1, 31);
		}
		if (new_performance.Date.Month == 2)
		{
			cout << "День:";
			new_performance.Date.Day = rangeOfNumbers(1, 28);
		}
		if (new_performance.Date.Month == 4 || new_performance.Date.Month == 6 || new_performance.Date.Month == 9 || new_performance.Date.Month == 11)
		{
			cout << "День:";
			new_performance.Date.Day = rangeOfNumbers(1, 30);
		}

		cout << "Год:";
		new_performance.Date.Year = rangeOfNumbers(2021, 2022);

		cout << "Введите название театра: ";
		cin >> new_performance.nameOfTheater;

		cout << "Введите название спектакля: ";
		cin >> new_performance.performance;

		cout << "Введите количество проданных билетов: ";
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

void updateInfo(vector<Theater>& vectorPerformance) // Изменение информации о спектаклях
{
	cout << "----- Редактирование информации о спектаклях -----\n\n";
	int number1;
	bool flag = true;
	while (flag)
	{
		int index;
		cout << "Введите номер спектакля, информацию о котором вы хотели бы изменить | 0 - Отмена\n\n";
		showInfo(vectorPerformance);
		cout << endl;
		
		index = rangeOfNumbers(0, vectorPerformance.size());
		
		switch (index)
		{
		default:
		{
			index--;
			cout << "----- Меню редактирования информации -----\n\n";
			cout << "Какую информацию о спектакле вы хотите изменить?\n\n";
			cout << "1 - Дата\n";
			cout << "2 - Название театра\n";
			cout << "3 - Название спектакля\n";
			cout << "4 - Количество проданных билетов\n";
			cout << "5 - Всю информацию\n";
			cout << "0 - Назад в меню редактирования данных\n";

			number1 = rangeOfNumbers(0, 5);
			switch (number1)
			{
			case 1:
			{
				system("cls");
				cout << "     <Редактирование даты>\n\n";
				cout << "Для отмены введите 0\n\n";
				cout << "Введите день спектакля (цифрами):\n ";
				cout << "Месяц:";
				vectorPerformance[index].Date.Month = rangeOfNumbers(0, 12);
				if (vectorPerformance[index].Date.Month != 0)
				{
					if (vectorPerformance[index].Date.Month == 1 || vectorPerformance[index].Date.Month == 3 || vectorPerformance[index].Date.Month == 5 || vectorPerformance[index].Date.Month == 7 ||
						vectorPerformance[index].Date.Month == 8 || vectorPerformance[index].Date.Month == 10 || vectorPerformance[index].Date.Month == 12)
					{
						cout << "День:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 31);
					}
					if (vectorPerformance[index].Date.Month == 2)
					{
						cout << "День:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 28);
					}
					if (vectorPerformance[index].Date.Month == 4 || vectorPerformance[index].Date.Month == 6 || vectorPerformance[index].Date.Month == 9 || vectorPerformance[index].Date.Month == 11)
					{
						cout << "День:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 30);
					}

					cout << "Год:";
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
				cout << "Введите название тетра: ";
				cin >> vectorPerformance[index].nameOfTheater;
				cout << endl;
				break;
			}
			case 3:
			{
				cout << "Введите название спектакля: ";
				cin >> vectorPerformance[index].performance;
				cout << endl;
				break;
			}
			case 4:
			{
				cout << "Введите количество проданных билетов: ";
				cin >> vectorPerformance[index].ticketSold;
				cout << endl;
				break;
			}
			case 5:
			{
				cout << "Введите день спектакля (цифрами):\n ";
				cout << "Месяц:";
				vectorPerformance[index].Date.Month = rangeOfNumbers(0, 12);
				if (vectorPerformance[index].Date.Month != 0)
				{
					if (vectorPerformance[index].Date.Month == 1 || vectorPerformance[index].Date.Month == 3 || vectorPerformance[index].Date.Month == 5 || vectorPerformance[index].Date.Month == 7 ||
						vectorPerformance[index].Date.Month == 8 || vectorPerformance[index].Date.Month == 10 || vectorPerformance[index].Date.Month == 12)
					{
						cout << "День:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 31);
					}
					if (vectorPerformance[index].Date.Month == 2)
					{
						cout << "День:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 28);
					}
					if (vectorPerformance[index].Date.Month == 4 || vectorPerformance[index].Date.Month == 6 || vectorPerformance[index].Date.Month == 9 || vectorPerformance[index].Date.Month == 11)
					{
						cout << "День:";
						vectorPerformance[index].Date.Day = rangeOfNumbers(1, 30);
					}

					cout << "Год:";
					vectorPerformance[index].Date.Year = rangeOfNumbers(2021, 2022);
					break;

				}

				cout << "Введите название тетра: ";
				cin >> vectorPerformance[index].nameOfTheater;

				cout << "Введите название спектакля: ";
				cin >> vectorPerformance[index].performance;
				cout << endl;

				cout << "Введите количество проданных билетов: ";
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

void deleteInfo(vector<Theater>& vectorPerformance) // Удаление информации о спектаклях
{
	int number;
	bool flag = true;
	while (flag)
	{
		cout << "----- Меню удаления спектаклей -----\n\n";

		showInfo(vectorPerformance);

		cout << "\nВведите номер спектакля, который Вы хотите удалить | 0 - Отмена :\n";

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
			cout << "Вы уверены, что хотите удалить всю информацию о спектакле " << vectorPerformance[index].performance << "?\n";
			cout << "1 - Да, я уверен\n";
			cout << "2 - Нет, вернуться в меню редактирования данных \n";
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
	cout << "----- Меню обработки данных -----\n\n";
	cout << " 1 - Индивидуальное задание\n";
	cout << " 2 - Поиск данных\n";
	cout << " 3 - Сортировка данных\n";
	cout << " 0 — Назад в меню работы с данными\n";
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
	cout << "----- Меню индивидумального задания -----\n\n";
	cout << "1 - Список самых популярных театров за указанный месяц\n";
	cout << "2 - Список самых популярных спектаклей за указанный месяц\n";
	cout << "0 - Назад в меню обработки данных\n";
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
	cout << "Cамые популярные театры за какой месяц и какого года вы хотите видеть?\n\n";
	cout << "Год: ";
	year = rangeOfNumbers(2021, 2022);
	cout << "\nМесяц: ";
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
		cout << i + 1 << ") " << "Название театра - " << vectorSum[i].nameOfTheater << ", " << "сумма проданных билетов - " << vectorSum[i].ticketSold << endl << endl;
	}
	

	cout << "Сортировка прошла успешно. Отсортировано по популярности театра за " << year << " год и " << month << " месяц.\n\n";
	cout << "Нажмите любую клавишу, чтобы вернуться обратно в меню поиска...";
	_getch();
	system("cls");
}

void mostPopularPerformance(vector<Theater>& vectorPerformance)
{
	vector<Theater>Temp;
	int n = 0;
	int year, month;
	cout << "Cамые популярные спектакли за какой месяц и какого года вы хотите видеть?\n\n";
	cout << "Год: ";
	year = rangeOfNumbers(2021, 2022);
	cout << "\nМесяц: ";
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
			"название театра - " << Temp[i].nameOfTheater << ", " << "название спектакля - " << Temp[i].performance << ", " << "количество проданных билетов - " << Temp[i].ticketSold << endl << endl;
		n++;
	}

	if (n == 0)
	{
		cout << "Спектаклей в этот месяц нет!\n\n";
		Sleep(3000);
		system("cls");
	}

	cout << "Сортировка прошла успешно. Отсортировано по популярности спектакля за " << year << " год и " << month << " месяц.\n\n";
	cout << "Нажмите любую клавишу, чтобы вернуться обратно в меню поиска...";
	_getch();
	system("cls");

}

int searchMenu()
{
	cout << "----- Меню поиска -----\n\n";
	cout << " 1 - Поиск по дате спектакля\n";
	cout << " 2 - Поиск по названию театра\n";
	cout << " 3 - Поиск по названию спектакля\n";
	cout << " 0 — Назад в меню обработки данных\n";
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
	cout << "----- Поиск -----\n\n";
	cout << "Введите точную дату спектакля | 0 - Для того, чтобы вернуться в меню поиска \n";

	cout << "Год: ";
	int year = rangeOfNumbers(0,2022);
	cout << endl;

	cout << "Месяц: ";
	int month = rangeOfNumbers(1, 12);
	cout << endl;

	cout << "День: ";
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
			cout << "Результ поиска:" << endl << endl;
			for (auto iter = vectorPerformance.begin(); iter != vectorPerformance.end(); iter++)
			{
				if (year == iter->Date.Year && day == iter->Date.Day && month == iter->Date.Month)
				{
					cout <<  n+1 << ") " << (*iter).Date.Day << "." << (*iter).Date.Month << "." << (*iter).Date.Year << "	" <<
						"название театра - " << (*iter).nameOfTheater << ", " << "название спектакля - " << (*iter).performance << ", " << "количество проданных билетов - " << (*iter).ticketSold << endl << endl;
					n++;

				}
			}

			flag = false;

			if (n ==0)
			{
				cout << "Спектаклей в этот день нет!\n\n";
				Sleep(3000);
				system("cls");
				break;
			}

		}
		cout << "Нажмите любую клавишу, чтобы вернуться обратно в меню поиска...";
		_getch();
		system("cls");
	}
}

void searchByTheaterName(vector<Theater>& vectorPerformance)
{
	cout << "----- Поиск -----\n\n";
	cout << "Введите название театра | 0 - Для того, чтобы вернуться в меню поиска \n";

	cout << "Название: ";
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
			cout << "Результ поиска:" << endl << endl;
			for (auto iter = vectorPerformance.begin(); iter != vectorPerformance.end(); iter++)
			{
				if (nameOfTheater == iter->nameOfTheater)
				{
					cout << n + 1 << ") " << (*iter).Date.Day << "." << (*iter).Date.Month << "." << (*iter).Date.Year << "	" <<
						"название театра - " << (*iter).nameOfTheater << ", " << "название спектакля - " << (*iter).performance << ", " << "количество проданных билетов - " << (*iter).ticketSold << endl << endl;
					n++;

				}
			}

			flag = false;

			if (n == 0)
			{
				cout << "В базе данных театров с таким названием нет!\n\n";
				Sleep(3000);
				system("cls");
				break;
			}

		}
		cout << "Нажмите любую клавишу, чтобы вернуться обратно в меню поиска...";
		_getch();
		system("cls");
	}
}

void searchByPerformanceName(vector<Theater>& vectorPerformance)
{
	cout << "----- Поиск -----\n\n";
	cout << "Введите название спектакля | 0 - Для того, чтобы вернуться в меню поиска \n";

	cout << "Название: ";
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
			cout << "Результ поиска:" << endl << endl;
			for (auto iter = vectorPerformance.begin(); iter != vectorPerformance.end(); iter++)
			{
				if (performanceName == iter->performance)
				{
					cout << n + 1 << ") " << (*iter).Date.Day << "." << (*iter).Date.Month << "." << (*iter).Date.Year << "	" <<
						"название театра - " << (*iter).nameOfTheater << ", " << "название спектакля - " << (*iter).performance << ", " << "количество проданных билетов - " << (*iter).ticketSold << endl << endl;
					n++;

				}
			}

			flag = false;

			if (n == 0)
			{
				cout << "В базе данных спектаклей с таким названием нет!\n\n";
				Sleep(3000);
				system("cls");
				break;
			}

		}
		cout << "Нажмите любую клавишу, чтобы вернуться обратно в меню поиска...";
		_getch();
		system("cls");
	}
}

int sortingMenu()
{
	cout << "----- Меню сортировки -----\n\n";
	cout << " 1 - Сортировка по дате спектакля (От ближайшего спектакля до самого старого)\n";
	cout << " 2 - Сортировка по дате спектакля (От самого старого до ближайшего спектакля)\n";
	cout << " 3 - Сортировка по названию театра (От А до Я)\n";
	cout << " 4 - Сортировка по названию театра (От Я до А)\n";
	cout << " 5 - Сортировка по названию спектакля (От А до Я)\n";
	cout << " 6 - Сортировка по названию спектакля (От Я до А)\n";
	cout << " 7 - Сортировка по количеству проданных билетов (От минимального значения до максимального значения)\n";
	cout << " 8 - Сортировка по количеству проданных билетов (От максимального значения до минимального значения)\n";
	cout << " 0 — Назад в меню обработки данных\n";
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
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			sortingToTheNearestPerformance(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			sortingByTheaterNameAtoZ(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 4:
		{
			system("cls");
			sortingByTheaterNameZtoA(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");
			sortingByPerformanceNameAtoZ(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");
			sortingByPerformanceNameZtoA(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 7:
		{
			system("cls");
			sortinByTheNumberOfTicketsSoldMintoMax(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
			_getch();
			system("cls");
			break;
		}
		case 8:
		{
			system("cls");
			sortinByTheNumberOfTicketsSoldMaxToMin(vectorPerformance);
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню администатора...";
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
	cout << "Сортировка прошла успешно. Отсортировано по дате от ближайшего спектакля до самого старого\n\n";
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
	cout << "Сортировка прошла успешно. Отсортировано по дате от самого старого спектакля до ближайшего\n\n";
	showInfo(vectorPerformance);
}

void sortingByTheaterNameAtoZ(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), TheaterAtoZ());
	cout << "Сортировка прошла успешно. Отсортировано по названию театра от А до Я\n\n";
	showInfo(vectorPerformance);
}

void sortingByTheaterNameZtoA(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), TheaterZtoA());
	cout << "Сортировка прошла успешно. Отсортировано по названию театра от Я до А\n\n";
	showInfo(vectorPerformance);
}

void sortingByPerformanceNameAtoZ(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), PerformanceAtoZ());
	cout << "Сортировка прошла успешно. Отсортировано по названию спектакля от А до Я\n\n";
	showInfo(vectorPerformance);
}

void sortingByPerformanceNameZtoA(vector<Theater>& vectorPerformance)
{
	sort(vectorPerformance.begin(), vectorPerformance.end(), PerformanceZtoA());
	cout << "Сортировка прошла успешно. Отсортировано по названию спектакля от Я до А\n\n";
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
	cout << "Сортировка прошла успешно. Отсортировано по количеству проданных билетов от минимального до максимального значения\n\n";
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
	cout << "Сортировка прошла успешно. Отсортировано по количеству проданных билетов от максимального до минимального значения\n\n";
	showInfo(vectorPerformance);
}

int userMenu()
{
	cout << "-------------- Меню пользователя --------------\n\n";
	cout << " 1 — Просмотр данных\n";
	cout << " 2 - Просмотр самых популярных театров/спектаклей за месяц (Индивидуальное задание)\n";
	cout << " 3 — Поиск данных\n";
	cout << " 4 — Сортировка\n";
	cout << " 0 — Назад в меню авторизации\n";
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
			cout << endl << "Нажмите любую клавишу, чтобы вернуться обратно в меню редактирования данных...";
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
