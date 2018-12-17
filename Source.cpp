#include <iostream>
#include <fstream>
#define MAS_SIZE 1024
const char sep[] = ". ,!?:;_\n";
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
bool check_sep(const char c, const char *sp);
void strcpy(char* s1, const char *s2, int size);

int main() {
	int i, j;
	int first, second;
	int endFirst, endSecond;
	int len1, len2;
	int d;
	int size;
	char c;
	char *wordTMP;
	char buf[MAS_SIZE];
	ifstream in("in.txt");
	//Блок проверки открытия файла
	if (!in.is_open()) {
		cout << "Error: file is not opened" << endl;
		in.close();
		return 0;
	}
	//Чтение файла из файлового потока
	for (i = 0; (buf[i] = in.get()) != EOF; ++i);
	buf[i] = '\0';
	size = i;
	//Вывод считанного текста
	cout << "Original text: " << buf << endl;
	//Работа с текстом
	for (i = 0; i < size; ++i) {
		//Находим символ
		if (!check_sep(buf[i], sep)) {
			//Запоминаем его номер в массиве
			first = i;
			//Находим конец последовательности символов first
			for (j = i + 1; j < size; ++j)
				if (check_sep(buf[j], sep)) break;
			//Запоминаем конец первого слова в endFirst
			endFirst = j;
			//Находим начало второй последовательности символов
			for (j = endFirst + 1; j < size; ++j)
				if (!check_sep(buf[j], sep)) break;
			//Если первое слово последнее, то менять не с чем и выходим из цикла
			if (j >= size) break;
			//Сохраняем начало второго слова
			second = j;
			//Запоминаем конец второго слова
			for (++j; j < size; ++j)
				if (check_sep(buf[j], sep)) break;
			//Сохраняем в конец в endSecond
			endSecond = j;
			//Блок копирования в wordL и wordR
			len1 = endFirst - first;
			len2 = endSecond - second;
			d = len2 - len1;
			if (d > 0) {
				wordTMP = new char[len2];
				strcpy(wordTMP, buf + second, len2);
				for (j = second - 1; j >= endFirst; --j)
					buf[j + d] = buf[j];
				strcpy(buf + second + d, buf + first, len1);
				strcpy(buf + first, wordTMP, len2);
			}
			else {
				wordTMP = new char[len1];
				strcpy(wordTMP, buf + first, len1);
				for (j = endFirst; j < second; ++j)
					buf[j + d] = buf[j];
				strcpy(buf + first, buf + second, len2);
				strcpy(buf + second + d, wordTMP, len1);
			}
			//Отчистка
			delete[] wordTMP;
			i = endSecond;
		}
	}
	//Вывод результата
	cout.width(15);
	cout << "Result: " << buf << endl;
	in.close();
	cin >> i;
	return 0;
}
bool check_sep(const char c, const char *sp) {
	for (int i = 0; sp[i] != '\0'; ++i)
		if (sp[i] == c) return true;
	return false;
}

void strcpy(char* s1, const char *s2, int size) {
	for (int i = 0; i < size; ++i)
		s1[i] = s2[i];
}