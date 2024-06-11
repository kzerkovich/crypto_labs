#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

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

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	string word;
	getline(cin, word);
	
	myToLower(word);

	map<char, double> probability;

	for (int i = 0; i < word.size(); i++) {
		auto tmp = probability.find(word[i]);
		if (tmp == probability.end()) {
			probability.insert(make_pair(word[i], 1));
		}
		else
			tmp->second++;
	}

	double entropy = 0.0;

	for (auto it = probability.begin(); it != probability.end(); ++it)
	{
		auto tmp = it->second / word.size();
		entropy += -tmp * log2(tmp);
	}

	cout << "\nEntropy H(X) = " << entropy;
}