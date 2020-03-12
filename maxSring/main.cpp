#include <iostream>
#include <fstream>
#include "machine.h"

int main()
{
	pair <bool, int> result;
	string path = "automato.txt";
	bool stop = false;
	string menu = "";

	int depth, buff;
	string state, str, str2, str3;
	char letter;
	set <char> a;
	set <string> s, ins, outs;
	vector <triple> dt;
	cout << "-------------------------------------" << endl;
	cout << "| root/"<<path << "                 |" << endl;
	cout << "| Текущий адрес автомата. Изменить? |" << endl;
	cout << "| 1 - Да                            |" << endl;
	cout << "| 2 - Нет                           |" << endl;
	cout << "-------------------------------------" << endl;
	cin >> menu;
	if (menu == "1")
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
			s.insert(state);
		}

		in >> depth;
		char letter;
		for (int i = 0; i < depth; i++)
		{
			in >> letter;
			a.insert(letter);
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

			triple delta(str2, letter, str3);
			dt.push_back(delta);

		}

		in >> depth;
		getline(in, state);
		for (int i = 0; i < depth; i++)
		{
			getline(in, state);
			ins.insert(state);
		}

		in >> depth;
		getline(in, state);
		for (int i = 0; i < depth; i++)
		{
			getline(in, state);
			outs.insert(state);
		}
	}
	in.close();

	Machine automato(s, a, dt, ins, outs);

	while (!stop)
	{
		result.first = false;
		result.second = 0;

		cout << "---------------------------------------------" << endl;
		cout << "| 1 - Все слова строки                      |" << endl;
		cout << "| 2 - Слово максимальной длинны с позиции k |" << endl;
		cout << "| 3 - Завершить приложение                  |" << endl;
		cout << "---------------------------------------------" << endl;
		cin >> menu;
		if (menu == "3")
			stop = true;
		else if (menu == "1")
		{
			cout << "Введите слово и k-ую позицию" << endl;
			cin >> str >> buff;
			automato.sub(str, buff);
		}
		else if (menu == "2")
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