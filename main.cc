#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define N 30
#define CURRENT_YEAR 2016


struct Person {
	char name[N];
	char z[N];
	unsigned int number;
	unsigned int BD[3];
	Person *next;
};

struct Alpha {
	char letter;
	bool isEmpty;
	Person* page;
	Alpha *next;
};

void createSkelet(Alpha *A)
{
	Alpha *tmp = new Alpha();
	tmp = A;
	for (int i = 65; i < 91; i++)
	{
		tmp->letter = i;
		tmp->isEmpty = true;
		Alpha *temp = new Alpha();
		tmp->next = temp;
		if (i == 90) tmp->next = NULL;	
		else tmp = temp;	
	}
}

Alpha *findLetter(Alpha *List, char *name)
{
	Alpha *tmp = new Alpha();
	bool found = false;

	if (name[0] > 96)
		name[0] = name[0] - 32;
	//c++ style!!!

	tmp = List;
	while (!found)
	{
		if (tmp->letter == name[0])
		{
			found = true;
			return tmp;
		}
		else
		{
			tmp = tmp->next;
		}
	}
	if (!found)
		return NULL;
}

void printNote(Person *note) 
{
	cout << note->name << " " << note->z << endl;
	cout << "\t" <<note->number << endl;
	cout << "\t" << note->BD[0] << "/" << note->BD[1] << "/" << note->BD[2] << endl; 
}

void correction(Person *note)
{
	int i = 0;
	while (note->name[i] !=' ' || note->name[i] != '/0')
	{
		i++;
		if (i == N)
			break;
	}
	if (note->name[i+1] > 96)
		note->name[i+1] = note->name[i+1] - 32;
}

Person* findPlace(Alpha *List)
{
	Person *place = new Person();
	place = List->page;
	while (place->next != NULL)
	{
		place = place->next;
	}
	Person *field = new Person();
	place->next = field;
	return field;
}

bool noLettersInDate(char *date)
{
	bool cor = true;
	int i = 0;
	while (date[i])
	{
		if (date[i] < 48 || date[i] > 57)
		{
			cout << "Only numbers." << endl;
			cor = false;
			break;
		}
		i++;
	}
	return cor;
}

bool check_outDate(int day, int month, int year)
{
	bool alright = true;

	if ((year > CURRENT_YEAR) || (year < 1900))
	{
		alright = false;
		cout << "You can't call to dead people or in the future. Wrong year." << endl;
		cout << "(If you want to call someone's reincarnation we recommend the astral version of this phonebook)" << endl;
	}

	if (month == 2)
	{
		if (day > 28) {
			if (year % 4 != 0)
			{
				alright = false;
				cout << "There're only 28 days in this February!" << endl;
			}
			else
			{
				if (day > 29)
				{
					alright = false;
					cout << "There're only 29 days in this February." << endl;
				}
			}
		}
	}
	else
	{
		if (day > 31)
		{
			alright = false;
			cout << "Not more than 31 days per month! (Dunno why, though...)" << endl;
		}
		else
		{
			if ((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30))
			{
				alright = false;
				cout << "Not more than 30 days in this month!" << endl;
			}
		}
	}

	if ((month > 12) || (month < 1) || (day < 1)) 
	{
		alright = false;
		cout << "Seriously?" << endl;
	}

	return alright;
}

bool addDate(Person *note, bool from, int BD[3])
{
	bool alright = false;
	bool cor = false;
	char n[N];
	if (!from) {
		while (!cor){
     	cout << "Enter their birthday. Year:" << endl; 
		cin.getline(n, N);
		cor = noLettersInDate(n);
		}
		note->BD[2] = atoi(n);

		cor = false;
		while (!cor){
     	cout << "Enter their birthday. Month:" << endl; 
		cin.getline(n, N);
		cor = noLettersInDate(n);
		}
		note->BD[1] = atoi(n);

		cor = false;
		while (!cor){
     	cout << "Enter their birthday. Day:" << endl; 
		cin.getline(n, N);
		cor = noLettersInDate(n);
		}
		note->BD[0] = atoi(n);
	}
	else
	{
		note->BD[0] = BD[0]; note->BD[1] = BD[1]; note->BD[2] = BD[2];
	}
		alright = check_outDate(note->BD[0], note->BD[1], note->BD[2]);
		if (!alright) cout << "Try again." << endl;

		return alright;
}

bool isUnic (Alpha *List, Alpha *A, Person *note)
{
	unsigned int number = note->number;
	Alpha *tmp = new Alpha();
	tmp = A;
	Person *t = new Person();
	t = tmp->page;
	while (tmp != NULL)
	{
		if (!tmp->isEmpty) {
		if ((t->number == number) && (note != t))
			return false;
		else //если номер не совпадает, переходим к следующей записи, если она вообще есть
		{
			if (t->next != NULL)
				t = t->next;
			else //страница кончилась, переходим на другую
			{
				if (tmp->next == NULL)
					return true;
				tmp = tmp->next;
				while (tmp->isEmpty)
				{ 
				if (tmp->next == NULL) 
					return true;				
				tmp = tmp->next;
				t = tmp->page;
				}
			}
		}
		}
		else
		{
			if (tmp->next == NULL)
					return true;
				tmp = tmp->next;
				t = tmp->page;
				while (tmp->isEmpty)
				{ 
				if (tmp->next == NULL) 
					return true;				
				tmp = tmp->next;
				t = tmp->page;
				}
		}
	}
}

bool addNumber(Person *note, Alpha *List, Alpha *A, bool from, int num)
{
	bool correct = false; bool cor = false;
	char numb[N];
	if (!from) {
	while (!cor) {
		cout << "Enter person's phone number (stationary, six numbers): " << endl;
		cin.getline(numb, N);
		cor = noLettersInDate(numb);
	}
	note->number = atoi(numb);
	}
	else
	{
		note->number = num;
	}
	
	bool unic = false;

while (!unic || !correct)
{
	if (((note->number / 1000000 == 0) && (note->number / 10000 > 0) && (note->number / 100000 != 0)) && noLettersInDate(numb)) 
	{
		correct = true;
	}
	else
	{
			cout << "Enter person's phone number (stationary, six numbers): " << endl;
			cin.getline(numb, N);
			cor = noLettersInDate(numb);
		note->number = atoi(numb);
	}

	unic = isUnic(List, A, note); 
	if (!unic) 
	{	
			cout << "Enter person's phone number (stationary, six numbers): " << endl;
			cin.getline(numb, N);
			correct = noLettersInDate(numb);
		while (!correct) {
			cout << "Enter person's phone number (stationary, six numbers): " << endl;
			cin.getline(numb, N);
			correct = noLettersInDate(numb);
		}
		note->number = atoi(numb);
	}
}
	return correct;
}

bool noNumbersInName(Person *note)
{
	bool correct = true;
	int i = 0;
	char ch = note->name[i];
	while (note->name[i])
	{
		ch = note->name[i];
		if ((ch < 65 ) || (ch <= 96 && ch >= 91) || ch >= 123)
		{ 
			correct = false; break; 
		}
		if (ch == ' ' && i == 0)
		{
			correct = false; break;
		}
		i++;
	}

	if (!correct)
	{
		cout << "Nothing but letters, please. Try again: " << endl;
	}
	else
	{
		ch = note->name[0];
		if (ch > 96)
			note->name[0] = ch - 32;
		int t = 0;
		while (note->name[t])
		{
			if (note->name[t] == ' ' && note->name[t+1] > 96)
				note->name[t+1] = note->name[t+1] - 32;
			t++;
		}
	}

	return correct;
}

bool isUniq(Person* note, Alpha *List)
{
	bool uniq = true;
	//уникально ли
	Person *tmp = new Person;
	tmp = List->page;
	while (tmp)
	{
		if (tmp != note && strcmp(tmp->name, note->name) == 0 && strcmp(tmp->z, note->z) == 0)
		{
			uniq = false;
			break;
		}
		tmp = tmp->next;
	}
	//уникально ли
	
	if (!uniq)
	{
		cout << "There's a person with this name already. 1 to add a note, 0 to change the name" << endl;
		bool d; cin >> d;
		if (d)
		{
			cout << "Enter the note: " << endl; cin.ignore();
			cin.getline(note->z, N);
		}
		else
		{
			cout << "Enter new name: " << endl; cin.ignore(); 
			cin.getline(note->name, N);
			if (note->name[0] != List->letter) { 
				cout << "It's " << List->letter << " page. Try again: " << endl; cin.ignore();
				cin.getline(note->name, N);
			}
		}
	}
	return uniq;
}

bool addName(Person *note, bool from, char *name, Alpha *List)
{
	bool correct = false;
	bool uniq = false;
	strcpy(note->name, name);
	while (!(correct && uniq)) //!!!
	{
		correct = noNumbersInName(note);
		while (!correct) {
		correct = noNumbersInName(note);
		if (!correct) cin >> note->name;
		}
		uniq = isUniq(note, List);
		correct = noNumbersInName(note);
	}
	correction(note);
	return correct;
}

Person *addNote(Alpha *List, Person *note, char *name, Alpha *A, bool from, int BD[3], int num)
{
	if (List->isEmpty)
	{
		List->page = note;
		List->isEmpty = false;		
		note->next = NULL;

		bool added = false;
		while (!added)
			added = addName(note, from, name, List);

		added = false;
		while (!added)
			added = addDate(note, from, BD);

		added = false;
		while (!added)
			added = addNumber(note, List, A, from, num);

		printNote(note);
		cout << "Added." << endl;
	}
	else
	{
		note = findPlace(List);

		strcpy(note->name, name);
		note->next = NULL;

		bool added = false;
		while (!added)
			added = addName(note, from, name, List);

		added = false;
		while (!added)
			added = addDate(note, from, BD);

		added = false;
		while (!added)
			added = addNumber(note, List, A, from, num);

		printNote(note);
		cout << "Added." << endl;
	}
	return note;
}

Person * findNum(Alpha *A, int number)
{
	bool found = false;

	Alpha *tmp = new Alpha();
	tmp = A;
	Person *t = new Person();
	t = tmp->page;
	Person *here = new Person();
	while ((tmp != NULL) && !found)
	{
		if (!tmp->isEmpty) {
		if (t->number == number) {
			found = true;
			here = t;
		}
		else //если номер не совпадает, переходим к следующей записи, если она вообще есть
		{
			if (t->next != NULL)
			t = t->next; 
			else //страница кончилась, переходим на другую
			{
				if (tmp->next == NULL) //если все, Z
					break;
				tmp = tmp->next;
				t = tmp->page;
				while (tmp->isEmpty) //пролистывание пустых
				{ 
				if (tmp->next == NULL) 
					break;				
				tmp = tmp->next;
				t = tmp->page;
				}
			}
		}
		}
		else
		{
			if (tmp->next == NULL)
					break;
				tmp = tmp->next;
				while (tmp->isEmpty)
				{ 
				if (tmp->next == NULL) 
					break;				
				tmp = tmp->next;
				t = tmp->page;
				}
				t = tmp->page;
		}
	}
	if (found)
	{
		printNote(here);
		return here;
	}
	else
	{
		cout << "Sorry, haven't found a person with this number." << endl;
		return NULL;
	}
}

void deleteNote(Alpha * A, int num)
{
	Person * here = new Person();
	Person * before = new Person();
	before = NULL;
	Person *tmp = new Person();
	Alpha *List = new Alpha();
	here = findNum(A, num);

	if (!here)
	{
		cout << "Haven't found." << endl;
		return;
	}

	bool deleted = false;

	List = findLetter(A, here->name);
	tmp = List->page;

	while (!deleted)
	{
		if (tmp == here)
		{
			if (before == NULL)/*это первый элемент страницы*/
			{
				List->page = here->next;
				if (here->next == NULL)
					List->isEmpty = true;
				delete here;
				deleted = true;
			}
			else
			{
				before->next = here->next;
				delete here;
				deleted = true;
			}
		}
		else {
			before = tmp;
			tmp = tmp->next;
		}
	}
	if (deleted)
		cout << "Deleted." << endl;
	else
		cout << "Can't find a note." << endl;
}

void editNote(Alpha *A, int num)
{
	int BD[3];
	Person * here = new Person();

	Person *tmp = new Person();

	Alpha *List = new Alpha();
	cout << "Before: " << endl;
	here = findNum(A, num);

	if (!here)
	{
		cout << "Haven't found." << endl;
		return;
	}

	bool edited = false;

	char name[N];
	char sur[N];
	strcpy(name, here->name);

	List = findLetter(A, here->name);
	tmp = List->page;

	while (!edited)
	{
		if (tmp == here)
		{
			int x;
			cout << "What do you want to edit?" << endl;
			cout << "1 - name, 2 - phone number, 3 - date" << endl;
			char a[N];
			cin.getline(a, N);
			x = atoi(a);
			while (x < 1 || x > 3) 
			{
				cout << "Wrong command. Try again: " << endl;
				cin.getline(a, N);
				x = atoi(a);
			}

			if (x == 1)
			{
				edited = false;

				char new_name[N] = "";
				bool cor = false; Person *p = new Person;
				while (!cor)
				{
				cout << "Enter new name:" << endl;
				cin.getline(new_name, N);
				if (new_name[0] > 96)
					new_name[0] = new_name[0] - 32;
				strcpy(p->name, new_name);
				cor = noNumbersInName(p);
				}
				edited = addName(here, false, new_name, List);	
			}
			if (x == 2)
			{
				edited = addNumber(here, List, A, false, 0);
			}
			if (x == 3)
			{
				edited = addDate(here, false, BD);
			}
			printNote(here);
			cout << "Edited." << endl;
		}
		else {
			tmp = tmp->next;
		}
	}
}

void exchange(Person *n1, Person *n2)
{
	//n1 to z
	Person *z = new Person();
	z->BD[0] = n1->BD[0]; z->BD[1] = n1->BD[1]; z->BD[2] = n1->BD[2];
	strcpy(z->name, n1->name);
	strcpy(z->z, n1->z);
	z->number = n1->number;
	//n2 to n1
	n1->BD[0] = n2->BD[0]; n1->BD[1] = n2->BD[1]; n1->BD[2] = n2->BD[2];
	strcpy(n1->name, n2->name);
	strcpy(n1->z, n2->z);
	n1->number = n2->number;
	//z to n2
	n2->BD[0] = z->BD[0]; n2->BD[1] = z->BD[1]; n2->BD[2] = z->BD[2];
	strcpy(n2->name, z->name);
	strcpy(n2->z, z->z);
	n2->number = z->number;
}

bool isSorted(Alpha *here)
{
	bool sorted = true;
	Person *tmp = new Person;
	tmp = here->page;
	int t = 0;
	while (tmp) 
	{
	while (tmp->name[t] == tmp->next->name[t])
		t++;
	if (!tmp->next->name[t] && tmp->name[t])
	{ 
		sorted = false; 
		break;
	}
	if (tmp->name[t] > tmp->next->name[t])
	{
		sorted = false;
		break;
	}
	tmp = tmp->next;
	if (!tmp->next) break;
	}
	return sorted;
}

void sort(Alpha *here, int amount)
{
	bool sorted = false;
	Person *tmp = new Person;
	tmp = here->page;
	int t = 0;
	while (!sorted)
	{
		t = 0;
		while (tmp->name[t] == tmp->next->name[t])
			t++;
		if (!tmp->next->name[t])
		{
				exchange(tmp, tmp->next);
				sorted = isSorted(here);
				tmp = here->page;
				continue;
		}
		if (tmp->next->name[t] < tmp->name[t])
		{
			exchange(tmp, tmp->next);
		}
		tmp = tmp->next;
		if (!tmp)
			tmp = here->page;
		if (!tmp->next)
			tmp = here->page;
		sorted = isSorted(here);
	}

}

void printAll(Alpha *A)
{
	Alpha *tmp = new Alpha;
	tmp = A;
	Person *p = new Person;
	while (tmp)
	{
		p = tmp->page;
		if (!tmp->isEmpty)
		{
			while (p) {
			printNote(p);
			p = p->next;
			}
		}
		tmp = tmp->next;	
	}
}

Person *findByName(Alpha *A, char *name)
{
	bool found = false;
	Alpha *List = new Alpha;
	List = findLetter(A, name);
	Person *here = new Person;
	here = List->page;
	while (here)
	{
		if (strcmp(name, here->name) == 0)
		{
			found = true; break; 
		}
		here = here->next;
	}
	if (found)
	{
		printNote(here);
		cout << "Found." << endl;
	}
	else
	{
		cout << "Haven't found." << endl;
		return NULL;
	}
}

int main()
{
	setlocale( LC_ALL,"Russian" );

	Alpha *A = new Alpha();

	createSkelet(A);

	Person *t = new Person();
	Person *add = new Person();

	char str[N];
	char named[N];
	char z[N];
	char for_n[6];
	char for_bd1[2], for_bd2[2], for_bd3[4];
	int b[3];
	int numb = 0;
	bool end = false;

	ifstream fin("C:\\Users\\Alena\\Desktop\\CourseProject\\notebook.txt"); //oткрыть файл в режиме чтения данных; является режимом по умолчанию для потоков ifstream;
	long long int size = fin.tellg();
	if (!fin || !fin.tellg()) // если файл не открывается или пуст
        cout << "Creating a phonebook..." << endl; 
    else
	{
		{
			fin.getline(str, N); 
			while (!end)
			{
				
				fin.getline(named, N);
				fin.getline(z, N);
				fin.getline(for_n, 7);
				fin.getline(for_bd1, 4);
				fin.getline(for_bd2, 4);
				fin.getline(for_bd3, 6);

				numb = atoi(for_n);
				b[0] = atoi(for_bd1); b[1] = atoi(for_bd2); b[2] = atoi(for_bd3);

				Alpha *L = new Alpha(); 
				L = findLetter(A, named);
				Person *add = new Person;
				add = addNote(L, add, named, A, true, b, numb);
				L->isEmpty = false;

				fin.getline(str, N);
				end = (str[0] == '.' && str[1] !='$');
			}
		}
	}
	fin.clear();
    ofstream fout;
	fout.open("C:\\Users\\Alena\\Desktop\\CourseProject\\notebook.txt"); // в режиме записи данных в конец файла;

	cout << "Welcome to your phonebook! What do you want to do?" << endl;
	int x;
while (true)
{
	cout << "1 - Add" << endl; cout << "2 - Search" << endl; cout << "3 - Delete" << endl; cout << "4 - Edit" << endl;
	cout << "5 - Sort in alphabetical order" << endl; cout << "6 - Print" << endl; cout << "7 - Save changes" << endl;
	cout << "8 - Finish" << endl; char a[N]; 
	cin.getline(a, N);
	x = atoi(a);
	while (x < 0 || x > 8) {
		cout << "Wrong command. Try again: " << endl;
		cin.getline(a, N);
		x = atoi(a);
	}

	if (x == 1) 
	{
		char name[N];

		bool corName = false;

		Person *p = new Person();

		while (!corName)
		{
			cout << "Enter person's name: " << endl;
			cin.getline(name, N);
			strcpy(p->name, name);
			corName = noNumbersInName(p);
		}
		strcpy(p->name, "");

		Alpha *List = new Alpha();
		List = findLetter(A, name);
		int BD[3];
		p = addNote(List, p, name, A, false, BD, 0);
	}
	if (x == 2) 
	{
		bool done = false; int n_n = 0;
		while (!done) {
			cout << "Do you want to find by number or by name? 1 as by number, 2 as by name" << endl;
			char nb[N];
			cin.getline(nb, N);
			
			n_n = atoi(nb);
			if (n_n == 1 || n_n == 2)
				done = true;
		}
	if (n_n == 1) {
			cout << "Enter their phone number: " << endl;
			char num[N];  int n;
			cin.getline(num, N);
			while (!noLettersInDate(num))
			{
				cout << "Try again: ";
				cin.getline(num, N);
			}
			n = atoi(num);
			t = findNum(A, n);
		}
		else
		{
			cout << "Enter their name: " << endl;
			char num[N];  int n;
			cin.getline(num, N);
			Person *p = new Person; strcpy(p->name, num);
			while (!noNumbersInName(p))
			{
				cout << "Try again: ";
				cin.getline(num, N);
			}
			t = findByName(A, num);
		}
	}
	if (x == 3) 
	{
		cout << "Enter phone number of the person you want to delete: " << endl; 
		char num[N];  int n;
		cin.getline(num, N);
		while (!noLettersInDate(num))
		{
			cout << "Try again: ";
			cin.getline(num, N);
		}
		n = atoi(num);
			deleteNote(A, n);
	}
	if (x == 4) 
	{
		cout << "Enter phone number of the person note you want to edit: " << endl;
		char num[N];  int n;
			cin.getline(num, N);
			while (!noLettersInDate(num))
			{
				cout << "Try again: ";
				cin.getline(num, N);
			}
		n = atoi(num);
		editNote(A, n);
	}
	if (x == 5) 
	{
		Alpha *tmp = new Alpha();
		tmp = A;
		for (int i = 0; i < 26; i++)
		{
			if (tmp->isEmpty)
				tmp = tmp->next;
			else
			{
				Person *temp = new Person();
				temp = tmp->page;
				int j = 0;
				while (temp)
				{
					j++;
					temp = temp->next;
				}
				if (j != 1)
					sort(tmp, j);
				tmp = tmp->next;
			}
		}
	}
	if (x == 6) 
	{
		//вывод на экран
		printAll(A);
	}
	if (x == 7) 
	{
		//запись в файл
		Alpha *tmp = new Alpha;
		tmp = A;
		Person *p = new Person;
		while (tmp)
		{
			p = tmp->page;
			if (!tmp->isEmpty)
			{
				while (p) 
				{
					//перед началом записи
					fout << "$\n"; 
				//	fin.getline(named, N);
					fout << p->name << "\n";
				//fin.getline(z, N);
					fout << p->z << "\n";
				//fin.getline(for_n, 6);
					fout << p->number << "\n";
				//fin.getline(for_bd1, 2);
					fout << p->BD[0] << "\n";
				//fin.getline(for_bd2, 2);
					fout << p->BD[1] << "\n";
				//fin.getline(for_bd3, 4);
					fout << p->BD[2] << "\n";
				p = p->next;
				}	
			}
		tmp = tmp->next;	
		if (!tmp)
			fout << ".";
		}
	}
	if (x == 8) 
	{
		break;
	}
}
	fin.close();
	fout.close();

	system("pause");
	return 0;
}