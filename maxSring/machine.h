#pragma once
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	A(list <string> s, map <char, int> a, vector <pair <pair <string, char>, string>> dt, list <string> ins, list <string> outs); //конструктор автомата
	pair <bool, int> maxString(string str, int k); //maxString
	list <string> shift(list <string> state, char letter); //смена состояний
	bool finish(list <string> c); //проверка на заключительное состояние
	void sub(string str, int k); //вывод всех слов в строке

private:
	string subword;
	map <char, int> alphabeth;
	map <char, int>::iterator it;
	pair <bool, int> resm;
	list <string> States;
	list <string> CurrentState, S, F;
	vector <pair <pair <string, char>, string>> delta;
};