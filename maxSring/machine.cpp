#include "machine.h"

A::A(list <string> s, map <char, int> a, vector <pair <pair <string, char>, string>> dt, list <string> ins, list <string> outs)
{
	//количество состояний
	this->States = s;
	//алфавит
	this->alphabeth = a;
	//функции перехода
	this->delta = dt;
	//начальные состояния
	this->S = ins;
	//заключительные состояния
	this->F = outs;
	//выход
	this->resm.first = false;
	this->resm.second = 0;

}

pair <bool, int> A::maxString(string str, int k)
{
	subword = "";
	resm.first = false;
	resm.second = 0;
	CurrentState = S;
	if (str.length() == 0 && finish(CurrentState)) //если стартовое состояние - заключительное
		resm.first = true;
	else {
		string buff = "";
		for (int i = k; i < str.length(); i++) //проход по строке
		{
			it = alphabeth.find(str[i]); //проверка совпадения текущего символа с алфавитом
			if (it == alphabeth.end())
				break;
			else
			{
				buff += str[i];
				CurrentState = shift(CurrentState, str[i]); //смена состояний
				if (finish(CurrentState)) //если среди текущих состояний есть заключительное
				{
					resm.first = true;
					resm.second = buff.length();
					subword = buff;
				}
			}
		}
	}
	return resm;
}

list <string> A::shift(list <string> state, char letter) //смена состояний
{
	list <string> buff;
	buff.clear();

	for (list <string>::iterator j = state.begin(); j != state.end(); j++)
		for (int i = 0; i < delta.size(); i++)
			if (delta[i].first.first == *j && delta[i].first.second == letter)
				buff.push_back(delta[i].second);

	buff.sort();
	buff.unique();
	return buff;
}

bool A::finish(list <string> c) //проверка на заключительное состояние
{
	for (list <string>::iterator i = F.begin(); i != F.end(); i++)
		for (list <string>::iterator j = c.begin(); j != c.end(); j++)
			if (*i == *j)
				return true;
	return false;

}

void A::sub(string str, int k) //процедура вывода всех слов строки
{
	int length = str.length();
	bool flag = false;
	while (k < length)
	{
		pair <bool, int> result;
		result.first = false;
		result.second = 0;
		result = maxString(str, k);
		if (result.first)
		{
			cout << "true " << result.second << ' ' << subword << endl;
			flag = true;
			k += result.second;
		}
		else
			k++;
	}
	if (!flag)
		cout << "false 0" << endl;
}