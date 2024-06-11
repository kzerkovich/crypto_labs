#include <iostream>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <iterator>
#include <string>

using namespace std;

long long evaluatePolynomial(const vector<long long>& coefficients, int x) {
    long long result = 0;
    long long power = 1;
    for (int i = 0; i < coefficients.size(); i++) {
        result += coefficients[i] * power;
        power *= x;
    }
    return result;
}

vector<pair<long long, long long>> splitSecret(int secret, int n, int m) {
    vector<long long> coefficients(m);
    coefficients[0] = secret;
    for (int i = 1; i < m; i++) {
        coefficients[i] = rand() % 256;
    }

    vector<pair<long long, long long>> shares;
    for (int i = 1; i <= n; i++) {
        long long share = evaluatePolynomial(coefficients, i);
        shares.push_back(std::make_pair(i, share));
    }

    return shares;
}

double recoverSecret(const vector<pair<long long, long long>>& shares, vector<int> rec) {
    vector<long long> xValues;
    vector<long long> yValues;
    int m = rec.size();
    for (const auto& share : shares) {
        if (find(begin(rec), end(rec), share.first) != end(rec)) {
            xValues.push_back(share.first);
            yValues.push_back(share.second);
        }   
    }
    yValues[10] = 12;
    double secret = 0;
    for (int i = 0; i < m; i++) {
        double numerator = 1;
        double denominator = 1;
        for (int j = 0; j < m; j++) {
            if (i != j) {
                numerator *= -xValues[j];
                denominator *= xValues[i] - xValues[j];
            }
        }
        secret += yValues[i] * numerator / denominator;
    }

    return secret;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    setlocale(LC_ALL, "Rus");

    int secret, n, m;

    cout << "Введите секрет в виде числа: "; cin >> secret;
    cout << "\nВведите количество пользователей, между которыми необходимо разделить секрет: "; cin >> n;
    cout << "\nВведите количество пользователей, которые смогут восстановить секрет: "; cin >> m;

    vector<pair<long long, long long>> shares = splitSecret(secret, n, m);

    cout << "\nЧасти пользователей после разделения секрета: \n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 <<"-й пользователь: (" << shares[i].first << ", " << shares[i].second << ")\n";
    }

    cin.ignore();
    cout << "\nВведите номера пользователей, которые будут восстанавливать секрет: \n";
    string inputline;
    getline(cin, inputline);
    istringstream iss(inputline);
    vector<int> recoverUsers((istream_iterator<int>(iss)), istream_iterator<int>());

    double recoveredSecret = recoverSecret(shares, recoverUsers);

    cout << "Восстановленный секрет: " << recoveredSecret << endl;

    return 0;
}