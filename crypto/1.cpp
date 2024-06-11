#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

void myToLower(string& word) {

	vector <string> lc = { "à", "á", "â", "ã", "ä", "å", "¸", "æ", "ç", "è", "é", "ê", "ë", "ì", "í", "î", "ï", "ð", "ñ", "ò", "ó", "ô", "õ", "ö", "÷", "ø", "ù", "ý", "þ", "ÿ" };
	vector <char> uc = { 'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', '¨', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ý', 'Þ', 'ß' };

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