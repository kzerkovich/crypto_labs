#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<string> group_set;
bool global_flag1, global_flag2 = true;
vector<int> primfac;
string neutral;

class Matrix {
public:
	int N;
	string** matrix;


	Matrix(int N) {
		this->N = N;
		matrix = new string* [N];

		for (int i = 0; i < N; i++)
			matrix[i] = new string[N];

	}

	void init() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> matrix[i][j];
			}
		}
	}

	void print(string** matrix) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	bool equal(string** a, string** b) {
		bool flag = true;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (a[i][j] != b[i][j]) flag = false;
			}
		}
		return flag;
	}

	void is_group() {
		string** xa;
		string** az;
		xa = new string * [N];
		az = new string * [N];
		bool flag1 = true;
		bool flag2 = false;
		for (int i = 0; i < N; i++)
			xa[i] = new string[N];
		for (int i = 0; i < N; i++)
			az[i] = new string[N];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					int col = distance(begin(group_set), find(begin(group_set), end(group_set), matrix[j][i]));
					xa[j][k] = matrix[col][k];
				}
			}
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					int row = distance(begin(group_set), find(begin(group_set), end(group_set), matrix[i][j]));
					az[k][j] = matrix[k][row];
				}
			}
			if (!equal(xa, az)) {
				flag1 = false;
				break;
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matrix[i][j] == matrix[j][i] && matrix[i][j] == group_set[j]) {
					flag2 = true;
				}
				else flag2 = false;
			}

			if (flag2) {
				neutral = group_set[i];
				break;
			}
		}

		int count = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matrix[i][j] == neutral) count++;
			}
		}

		if (flag1 && flag2 && count == N) {
			cout << "Данное множество является группой.";
			global_flag1 = true;
		}
		else {
			global_flag1 = false;
			cout << "Данное множество не является группой.";
		}
	}

	void is_abelian() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (matrix[i][j] != matrix[j][i]) {
					global_flag2 = false;
					break;
				}
			}
		}
	}

	void generating_element() {
		vector<pair<int, string>> el;

		for (int i = 0; i < N; i++) {
			set<string> elem;
			int prom = i, tmp = 0, count;
			if (group_set[i] != neutral) {
				for (int j = 0; j < N; j++) {
					elem.insert(matrix[prom][i]);
					prom = distance(begin(group_set), find(begin(group_set), end(group_set), matrix[prom][i]));
					if (matrix[prom][i] != neutral) {
						tmp++;
					}
					else count = tmp;
				}
				if (elem.size() == N) {
					el.push_back(make_pair(count, group_set[i]));
				}
			}
		}
		sort(begin(el), end(el));
		cout << "\nПорождающий элемент: " << el[0].second << "\n";
	}
};

int primeFactors(int n) {
	int i = 2;
	while (i * i <= n) {
		while (n % i == 0) {
			primfac.push_back(i);
			n = n / i;
		}
		i = i + 1;
	}
	if (n > 1) {
		primfac.push_back(n);
	}
	return primfac.size();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Rus");

	int N;
	cout << "Введите размер группы: " << endl;
	cin >> N;

	cout << "Введите элементы группы: " << endl;
	for (int i = 0; i < N; i++) {
		string tmp; cin >> tmp;
		group_set.push_back(tmp);
	}
	cout << endl << "Введите таблицу Кэли:" << endl;
	Matrix matrix(N);
	matrix.init();
	cout << endl;
	matrix.is_group();
	if (!global_flag1) return 0;
	cout << endl << endl;

	if (primeFactors(N) != 2 && primfac[0] != primfac[1]) {
		cout << "\nДанная группа не является группой порядка pq.";
		return 0;
	}
	else {
		cout << "Данная группа является группой порядка pq.\n";
		cout << "p = " << primfac[0] << ", q = " << primfac[1] << ".\n\n";
	}

	matrix.is_abelian();
	if (global_flag2) {
		cout << "Данная группа является абелевой.\n";
	}
	else {
		cout << "Данная группа не является абелевой.";
		return 0;
	}

	matrix.generating_element();
}