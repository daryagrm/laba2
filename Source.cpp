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
	//���� �������� �������� �����
	if (!in.is_open()) {
		cout << "Error: file is not opened" << endl;
		in.close();
		return 0;
	}
	//������ ����� �� ��������� ������
	for (i = 0; (buf[i] = in.get()) != EOF; ++i);
	buf[i] = '\0';
	size = i;
	//����� ���������� ������
	cout << "Original text: " << buf << endl;
	//������ � �������
	for (i = 0; i < size; ++i) {
		//������� ������
		if (!check_sep(buf[i], sep)) {
			//���������� ��� ����� � �������
			first = i;
			//������� ����� ������������������ �������� first
			for (j = i + 1; j < size; ++j)
				if (check_sep(buf[j], sep)) break;
			//���������� ����� ������� ����� � endFirst
			endFirst = j;
			//������� ������ ������ ������������������ ��������
			for (j = endFirst + 1; j < size; ++j)
				if (!check_sep(buf[j], sep)) break;
			//���� ������ ����� ���������, �� ������ �� � ��� � ������� �� �����
			if (j >= size) break;
			//��������� ������ ������� �����
			second = j;
			//���������� ����� ������� �����
			for (++j; j < size; ++j)
				if (check_sep(buf[j], sep)) break;
			//��������� � ����� � endSecond
			endSecond = j;
			//���� ����������� � wordL � wordR
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
			//��������
			delete[] wordTMP;
			i = endSecond;
		}
	}
	//����� ����������
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