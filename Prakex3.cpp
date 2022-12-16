// Prakex3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
using namespace std;
#include <iostream>
#include <fstream>
#include <string>


bool isUpper(char c) {														// Функция проверяет находиться ли символ в верхнем регистре
	return c >= 'А' && c <= 'Я';
}

bool isLower(char c) {														// Функция проверяет находиться ли символ в нижнем регистре
	return c >= 'а' && c <= 'я';
}

bool isLetter(char c) {														// Фукнция проверяет являеться ли символ буквой
	return isUpper(c) || isLower(c);
}

char upper(char c) {														// Функция поднимает регистр
	if (isLower(c) && isLetter(c)) {
		return c - 32;
	}
	return c;
}

char lower(char c) {														// Функция опускает регистр
	if (isUpper(c) && isLetter(c)) {
		return c + 32;
	}
	return c;
}

bool check(string word, char max_letters[]) {								// Функция проверяет содержит ли слово, хотя бы одну букву не входящую ни в одно из слов текста с максимальной длиной
	for (int i = 0; i < word.size(); i++) {
		if (strchr(max_letters, lower(word[i])) == 0) {
			if (isLetter(word[i])) {
				return true;
			}
		}
	}
	return false;
}



int main()
{
	setlocale(LC_ALL, "rus");
	string str;
	ifstream fin("input.txt");
	int max_lenght = 0;
	int max_count = 0;
	char max_letters[32] = "                               ";
	while (!fin.eof()) {													// В цикле, я считываю слова и нахожу слова максимальной длинны, а также их уникальные буквы
		fin >> str;
		char letters[32] = "                               ";
		int count = 0;
		int len = 0;
		for (int i = 0; i < str.size(); i++) {								// Считываю длинну слова, а также его уникальные буквы
			if (isLetter(str[i])) {
				len++;
				if (strchr(letters, lower(str[i])) == 0) {
					letters[count] = lower(str[i]);
					count++;
				}
			}
		}
		if (len > max_lenght) {												// Если нахожу слово большей длинны, то сбрасываю массив, в котором хранятся буквы самых длинных слов и записываю в него заново
			for (int i = 0; i < max_count; i++) {
				max_letters[i] = ' ';
			}
			max_lenght = len;
			max_count = count;
			for (int i = 0; i < count; i++) {
				max_letters[i] = letters[i];
			}
		}
		else if (len == max_lenght) {										// Если находиться слово такой же длинны как и максимальное, добавляю уникальные буквы в массив
			for (int i = 0; i < count; i++) {
				if (strchr(max_letters, letters[i]) == 0) {
					max_letters[max_count] = letters[i];
					max_count++;
				}
			}
		}
	}
	fin.close();
	ifstream ain("input.txt");												// В цикле считываю слова заново, для того чтобы вывыести текст, так как нам нужно по условию
	ofstream aout("output.txt");
	while (!ain.eof()) {														
		ain >> str;
		char letters[32] = "                               ";
		int count = 0;
		if (check(str, max_letters)) {										// проверяю содержит ли слово букву, не входящую ни в одно из слов текста с максимальной длиной и если да, то вывожу его в верхнем регистре
			for (int i = 0; i < str.size(); i++) {
				if (strchr(max_letters, lower(str[i])) == 0) {				// а также в скобках вывожу найденные буквы
					if (strchr(letters, upper(str[i])) == 0) {
						if (isLetter(str[i])) {
							letters[count] = upper(str[i]);
							count++;
						}
					}
				}
				aout << upper(str[i]);
			}
			aout << "(";
			for (int i = 0; i < count; i++) {
				aout << letters[i];
			}
			aout << ") ";
		}
		else {																// А если нет то просто вывожу слово
			aout << str << " ";
		}
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

