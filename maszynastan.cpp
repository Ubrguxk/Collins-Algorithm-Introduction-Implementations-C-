#include <iostream>

using namespace std;

string analise(string key) {
	// tworzymy wynikowy string 
	string newStr = "";
	
	// tworzymy tablice wielkosci tblicy ascii od 32 do 127
	bool tab[95] = { false };

	for (int i = 0; i < key.length(); i++) {
		if (tab[key[i] - 32] == false) {
			tab[key[i] - 32] = true;
			newStr += key[i];
		}
	}
	//cout << newStr;
	return newStr;
}

int checkIfBefore(string key, string alreadyDid, char x) {
	string temp = alreadyDid + x;
	string temp2 = key.substr(0, temp.length());

	if (temp == temp2) {
		//cout << " porownano cale klucze ";
		//cout << " to jest to ";
		return temp.length();
	}
	for (int i = 1; i != temp.length(); i++) {
		string temp3 = temp.substr(i, temp.length());
		temp2 = key.substr(0, temp3.length());

		//cout << " porownano " << temp3 << " z " << temp2;

		if (temp3 == temp2) {
			return temp3.length();
		}
	}

	return 0;
}

int addicionalcheck(string key, char x) {
	string temp = key + x;
	string temp2 = key.substr(0, temp.length());

	for (int i = 1; i != temp.length(); i++) {
		string temp3 = temp.substr(i, temp.length());
		temp2 = key.substr(0, temp3.length());

		if (temp3 == temp2) {
			return temp3.length();
		}
	}

	return 0;
}

int ** state_mach(string key) {
	//tworzymy stringa z wszysktich liczb
	string keyPattern = analise(key);

	// tworzymy tablice stanu 
	int** tab = new int*[key.length() + 1];
	
	// string liter które ju¿ sprawdziliœmy 
	
	string alreadyDid = "";
	int i = 0;

	while (alreadyDid != key) {
		// nowe 3 kolumny dla kazdego wiersza 
		tab[i] = new int[3];
		cout << "Litera " << i + 1<< " klucza = " << key[i] << endl;

		for (int j = 0; j < 3; j++) {
			cout << "Wartosc dla " << keyPattern[j] << " : ";
			tab[i][j] = checkIfBefore(key, alreadyDid, keyPattern[j]);
			cout << tab[i][j] << endl;
		}
		
		alreadyDid += key[i];
		i++;
	}
	
	//tworzenie dodatkowego rzedu
	tab[key.length()] = new int[3];
	cout << "Dodatkwoy rzad" << endl;
	for (int j = 0; j < 3; j++) {
		cout << "Wartosc dla " << keyPattern[j] << " : ";
		tab[key.length()][j] = addicionalcheck(key, keyPattern[j]);
		cout << tab[key.length()][j] << endl;
	}
	return tab;
}

int findLetterInKeyPattern(char let, string keyPattern) {
	for (int i = 0; i < keyPattern.length(); i++) {
		if (keyPattern[i] == let) {
			return i;
		}
	}
}

void search(string key, string tab, int** statemach) {
	int * states = new int[tab.length() + 1];
	states[0] = 0;
	string keyPattern = analise(key);
	
	for (int i = 0; i < tab.length(); i++) {
		if (states[i] == 7) {
			cout << "znaleziono klucz!" << endl;
		}
		cout << "Literka : " << tab[i] << endl;
		int x = states[i];
		int y = findLetterInKeyPattern(tab[i], keyPattern);
		cout << "Stan poprzedni:" << x << endl;
		cout << "Ktora to literka: " << keyPattern[y] << endl;
		cout << "Stan obecnej literki: "<<statemach[x][y] << endl;
		states[i + 1] = statemach[x][y];
	}
}

int main(){
	string tab = "abababacaba";
	string key = "ababaca";
	
	int ** statemach = state_mach(key);
	cout << endl << endl << endl << endl << endl;
	search(key, tab, statemach);
}