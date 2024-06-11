#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

string alpha = "��������������������������������";

void myToLower(string& word) {

	vector <string> lc = { "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�" };
	vector <char> uc = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�' };

	for (int i = 0; i <= word.length() - 1; i++) {
		for (int u = 0; u <= uc.size() - 1; u++) {
			if (word[i] == uc[u]) {
				word.replace(i, 1, lc[u]);
			}
		}
	}
}

void transform(string str, vector<int> &perm) {
	vector<int> help1, help2;
	string help = str.substr(0, str.find(")") + 1);
	str = str.substr(str.find(")") + 1, str.length());

	int num = help.find_first_of("0123456789");
	while (num != string::npos) {
		if (help.find(help[num + 1]) != string::npos) {
			help1.push_back(stoi(help.substr(num, 2)));
			help.erase(num, 2);
		}
		else {
			help1.push_back(stoi(help.substr(num, 1)));
			help.erase(num, 1);
		}
		num = help.find_first_of("0123456789");
	}

	if (!str.empty()) {
		int num = str.find_first_of("0123456789");
		while (num != string::npos) {
			if (str.find(str[num + 1]) != string::npos) {
				help2.push_back(stoi(str.substr(num, 2)));
				str.erase(num, 2);
			}
			else {
				help2.push_back(stoi(str.substr(num, 1)));
				str.erase(num, 1);
			}
			num = str.find_first_of("0123456789");
		}
	}

	for (int i = 0; i < help1.size() - 1; i++) perm[help1[i] - 1] = help1[i + 1];
	
	perm[help1[help1.size() - 1] - 1] = help1[0];

	for (int i = 0; i < help2.size(); i++) perm[help2[i] - 1] = help2[i];

}

void encrypt_1(string str, vector<int> first, vector<int> second) {
	string result_half, result;

	int fsize = first.size();
	int ssize = second.size();

	while (str.length() > 0) {
		if (str.length() < fsize) {
			int size = str.length();
			for (int i = 0; i < fsize - size; i++) str += char(alpha[rand() % alpha.size()]);
		}
		vector<char> helper(fsize);

		int i = 0;
		while (i < fsize) {
			helper[first[i] - 1] = str[i];
			i++;
		}

		int j = 0;
		while (j < fsize) {
			result_half += helper[j];
			j++;
		}

		str.erase(0, fsize);
	}

	while (result_half.length() > 0) {
		if (result_half.length() < ssize) {
			int size = result_half.length();
			for (int i = 0; i < ssize - size; i++) result_half += char(alpha[rand() % alpha.size()]);
		}

		vector<char> helper(ssize);

		int i = 0;
		while (i < ssize) {
			helper[second[i] - 1] = result_half[i];
			i++;
		}

		int j = 0;
		while (j < ssize) {
			result += helper[j];;
			j++;
		}
		result_half.erase(0, ssize);
	}

	cout << endl << "������������� ���������������� ����������� ������ ������: " << endl << result;
}

void encrypt_composition(string str, vector<int> first, vector<int> second) {
	string result;

	int fsize = first.size();
	int ssize = second.size();

	int superSize = fsize * ssize;

	vector<int> helper(superSize), compose(superSize);

	for (int i = 0; i < ssize; i++) {
		for (int j = 0; j < fsize; j++) {
			helper[first[j] - 1 + i * fsize] = j + i * fsize + 1;
		}
	}

	for (int i = 0; i < fsize; i++) {
		for (int j = 0; j < ssize; j++) {
			compose[second[j] + i * ssize - 1] = helper[j + i * ssize];
		}
	}

	cout << endl << "����� ������������:" << endl;

	for (int i = 0; i < superSize; i++) cout << compose[i] << " ";

	while (str.length() > 0) {
		if (str.length() < superSize) {
			int size = str.length();
			for (int i = 0; i < superSize - size; i++) str += char(alpha[rand() % alpha.size()]);
		}
		vector<char> helper(superSize);

		int i = 0;
		while (i < superSize) {
			helper[i] = str[compose[i] - 1];
			i++;
		}

		int j = 0;
		while (j < superSize) {
			result += helper[j];
			j++;
		}

		str.erase(0, superSize);
	}

	cout << endl << "������������� � ������� ���������� ������: " << endl << result;
}

void decrypt_1(string str, vector<int> first, vector<int> second) {
	string result_half, result;

	int fsize = first.size();
	int ssize = second.size();

	while (str.length() > 0) {
		vector<char> helper(ssize);

		int i = 0;
		while (i < ssize) {
			helper[i] = str[second[i] - 1];
			i++;
		}

		int j = 0;
		while (j < ssize) {
			result_half += helper[j];
			j++;
		}

		str.erase(0, ssize);
	}

	while (result_half.length() > 0) {
		vector<char> helper(fsize);

		int i = 0;
		while (i < fsize) {
			helper[i] = result_half[first[i] - 1];
			i++;
		}

		int j = 0;
		while (j < fsize) {
			result += helper[j];
			j++;
		}

		result_half.erase(0, fsize);
	}

	cout << "�������������� ���������������� ����������� ������ ������: " << endl << result;
}

void decrypt_composition(string str, vector<int> first, vector<int> second) {
	string result;

	int fsize = first.size();
	int ssize = second.size();

	int superSize = fsize * ssize;

	vector<int> helper(superSize), compose(superSize);

	for (int i = 0; i < ssize; i++) {
		for (int j = 0; j < fsize; j++) {
			helper[first[j] - 1 + i * fsize] = j + i * fsize + 1;
		}
	}

	for (int i = 0; i < fsize; i++) {
		for (int j = 0; j < ssize; j++) {
			compose[second[j] + i * ssize - 1] = helper[j + i * ssize];
		}
	}

	while (str.length() > 0) {
		if (str.length() < superSize) {
			int size = str.length();
			for (int i = 0; i < superSize - size; i++) str += char(alpha[rand() % alpha.size()]);
		}
		vector<char> helper(superSize);

		int i = 0;
		while (i < superSize) {
			helper[compose[i] - 1] = str[i];
			i++;
		}

		int j = 0;
		while (j < superSize) {
			result += helper[j];
			j++;
		}

		str.erase(0, superSize);
	}
	cout << "�������������� � ������� ���������� ������: " << endl << result;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Rus");

	srand(time(NULL));

	int mode, first_size, second_size;
	string f_perm, s_perm, message;

	cout << "�������� ����� ������. 1 � �����������/2 � ������������\n"; cin >> mode;
	cout << "������� ������ ����� ������� ����� m:\n"; cin >> first_size;
	cout << "������� ������������:\n";
	cin.get(); getline(cin, f_perm);
	cout << "������� ������ ����� ������� ����� k:\n"; cin >> second_size;
	cout << "������� ������������:\n";
	cin.get(); getline(cin, s_perm);
	cout << "������� ���������:\n";
	getline(cin, message);

	vector<int> ff(first_size, 0);
	vector<int> ss(second_size, 0);

	myToLower(message);
	string new_str;
	for (int i = 0; i < message.size(); i++) 
		if (alpha.find(message[i]) != string::npos) new_str += message[i];

	transform(f_perm, ff);
	transform(s_perm, ss);

	switch (mode)
	{
	case 1:
		encrypt_1(new_str, ff, ss);
		encrypt_composition(new_str, ff, ss);
		break;
	case 2:
		decrypt_1(message, ff, ss);
		decrypt_composition(message, ff, ss);
		break;
	default:
		break;
	}
}