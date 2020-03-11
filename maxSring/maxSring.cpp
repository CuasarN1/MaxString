#include <iostream>
#include <fstream>
#include "machine.h"

int main()
{
	pair <bool, int> result;
	string path = "automato.txt";
	bool stop = false;

	int depth, buff;
	string state, str, str2, str3;
	char letter;
	list <string> s;
	map <char, int> a;
	list <string> ins, outs;
	pair <pair <string, char>, string> delta;
	vector <pair <pair <string, char>, string>> dt;
	cout << "-------------------------------------" << endl;
	cout << "| root/"<< path <<"                 |" << endl;
	cout << "| Текущий адрес автомата. Изменить? |" << endl;
	cout << "| 1 - Да                            |" << endl;
	cout << "| 2 - Нет                           |" << endl;
	cout << "-------------------------------------" << endl;
	cin >> buff;
	if (buff == 1)
	{
		cout << "Введите новый адрес файла" << endl;
		cin >> path;
	}

	ifstream in;
	in.open(path);
	if (in.is_open()) // файл успешно открыт
	{
		in >> depth;
		getline(in, state);
		for (int i = 1; i <= depth; i++)
		{
			getline(in, state);
			s.push_back(state);
		}

		in >> depth;
		char letter;
		for (int i = 0; i < depth; i++)
		{
			in >> letter;
			a[letter] = i + 1;
		}
		
		in >> depth;
		getline(in, str);
		for (int i = 0; i < depth; i++)
		{
			str = str2 = str3 = "";
			int j = 0;
			getline(in, str);
			while (isalpha(str[j]) != 0)
			{
				str2 += str[j];
					j++;
			}

			letter = str[j + 1];

			for (int l = j + 3; l < str.length(); l++)
				str3 += str[l];

			delta.first.first = str2;
			delta.first.second = letter;
			delta.second = str3;
			dt.push_back(delta);

		}

		in >> depth;
		getline(in, state);
		for (int i = 0; i < depth; i++)
		{
			getline(in, state);
			ins.push_back(state);
		}

		in >> depth;
		getline(in, state);
		for (int i = 0; i < depth; i++)
		{
			getline(in, state);
			outs.push_back(state);
		}
	}
	in.close();

	A automato(s, a, dt, ins, outs);

	while (!stop)
	{
		result.first = false;
		result.second = 0;

		cout << "---------------------------------------------" << endl;
		cout << "| 1 - Все слова строки                      |" << endl;
		cout << "| 2 - Слово максимальной длинны с позиции k |" << endl;
		cout << "| 3 - Завершить приложение                  |" << endl;
		cout << "---------------------------------------------" << endl;
		cin >> buff;
		if (buff == 3)
			stop = true;
		else if (buff == 1)
		{
			cout << "Введите слово и k-ую позицию" << endl;
			cin >> str >> buff;
			automato.sub(str, buff);
		}
		else if (buff == 2)
		{
			cout << "Введите слово и k-ую позицию" << endl;
			cin >> str >> buff;
			result = automato.maxString(str, buff);
			if (result.first == 0)
				str = "false";
			else
				str = "true";
			cout << str << ' ' << result.second << endl;
		}
		else
			cout << "Ошибка ввода!" << endl;
	}
	
	return 0;
}
