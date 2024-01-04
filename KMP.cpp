#include <iostream>
#include <cmath>

using namespace std;

int DevineAndCompare(string word) {
	//cout << endl << "Dotychczas slowo: " << word << " o dlg " << word.length() << endl;
	int i = word.length() - 1;
	int j = 1;

	for (int k = word.length(); k != 0; k--) {
		//cout << k << endl;
		string temp = word.substr(0, i);
		string temp2 = word.substr(j, word.length());

		//cout << temp << " " << temp2 << endl;

		if (temp == temp2) {
			return i;
		}
		i--;
		j++;
	}
	return 0;
}

int * MakeTable(string key) {
	//cout << "Klucz : " << key << endl;
	//cout << key.length() << endl;
	int* tab = new int [key.length()];
	string already = "";

	for (int i = 0; i < key.length(); i++) {
		//cout << "Literka : " << key[i];
		char x = key[i];
		already += x;

		if (already == string(1,x)) {
			tab[i] = 0;
		}
		else {
			tab[i] = DevineAndCompare(already);
		}
		//cout << " Wartosc : " << tab[i] << endl << endl;
	}
	
	cout << "tabela: " << endl;
	for (int i = 0; i < key.length(); i++) {
		cout << i << ": " << tab[i] << endl;
	}
	
	return tab;
}

void TextSearch(string text, string key, int * tab) {
	int s = 0; // przesuniecie w tekscie
	int q = 1; // dlugosc poprawnosc dopasowania 

	while (s != text.length()) {
		cout << "q = " << q << " s = " << s << endl;
		cout << text.substr(s, q) << " " << key.substr(0, q) << endl;

		if (text.substr(s, q) == key.substr(0, q)) {
			q++;
		}
		else {
			//implementacja sprim
			if (q != 1) {
				cout << "Na pozycji " << q << " wystepuje niedopasowanie" << endl;
				q--;
			}
			s += q - tab[q - 1];
			// tab[q-1] bo na prezentacji licza tabelke od 1 anie od 0 jak w programie
			cout << "q = " << q << " , tab[q] = " << tab[q-1] << " , s prim = " << s << endl;
			q = 1;
		}
	}
}

int main() {
	string text = "bacbababaabab";
	string key = "ababababca";

	int * tab = MakeTable(key);

	TextSearch(text, key, tab);

	delete[] tab;
}