#include <iostream>

using namespace std;

struct node {
	node* next;
	int val;
};

void addH(node* &head, int x) {
	node* tmp = new node;
	tmp->val = x;
	tmp->next = head;
	head = tmp;
}

void add(node* &head, int x) {
	node* tmp = head;
	node* addn = new node;

	if (tmp == nullptr) {
		addH(head, x);
		return;
	}
	else {
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = addn;
		addn->val = x;
		addn->next = nullptr;
		return;
	}
}

void delval (node*& head, int x) {
	node* tmp = head;

	while (tmp->next != nullptr && tmp->val != x) {
		tmp = tmp->next;
	}
	if (tmp-> next == nullptr && tmp->val != x) {
		cout << "Nie znaleziono takiego elementu";
		cout << "sobie wyczytaj liste a potem sprawdzaj co jest" << endl;
		return;
	}
	else {
		tmp->next = tmp->next->next;
		return;
	}

}

void delpoint(node*& head, node * & p) {
	node* tmp = head;

	while (tmp->next != p && tmp->next !=nullptr) {
		tmp = tmp->next;
	}
	if (tmp->next == nullptr) {
		cout << "coœ jest nie tak dude" << endl;
		return;
	}
	else {
		tmp->next = tmp->next->next;
		return;
	}
}

void read(node* root) {
	node* tmp = root;
	
	while (tmp != nullptr) {
		cout << " Elem o wartoœci " << tmp->val << endl;
		tmp = tmp->next;
	}
}

node * find_first_one(node*& head, int x) {
	node* tmp = head;
	while (tmp->val != x) {
		tmp = tmp->next;
	}
	if (tmp == head && head->val != x) {
		cout << "Nie znaleziono elementu o podanej wartosci" << endl;
		return head;
	}
	else {
		return tmp;
	}
}

// ----------------------------------------------------------------------------

// zad1 Usun co drugi element
void zad1(node*& head) {
	node* tmp = head;
	int i = 1;
	while ( tmp != nullptr) {
		if (i % 2 == 1) {
			tmp = tmp->next;
		}
		else if (i % 2 == 0) {
			delpoint(head, tmp);
			tmp = tmp->next;
		}
		i++;
	}
}

// zad2 Kopia kazdego elementu, podwojenie go
void zad2(node*& head) {
	node* tmp = head;

	while (tmp != nullptr) {
		node* temp = new node;
		temp->next = tmp->next;
		tmp->next = temp; 
		temp->val = tmp->val;
		tmp = tmp->next->next;
	}
}

// zad3 Kopia listy jedna po drugiej -------------------------------
void zad3(node*& head) {
	node* tmp = head;
	node* tail = nullptr;
	
	while (tmp != nullptr) {
		tail = tmp;
		tmp = tmp->next;
	}
	node* tail2 = tail;
	tmp = head;
	while (tmp != tail2->next) {
		add(head, tmp->val);
		tmp = tmp->next;
	}
}

// zad4 œrednia el na liscie
void zad4(node*& head) {
	node* tmp = head;
	int suma = 0;
	int ile = 0;

	while (tmp != nullptr) {
		ile++;
		suma += tmp->val;
		tmp = tmp->next;
	}
	cout << suma << " podzielic przez " << ile << " daje œrednia rowna " << suma / ile << endl;
}

// zad5 zamieniamy ze swoim nastêpnikiem 
void zad5(node * & head, node * &p) {
	node* tmp = p->next;
	node* H = head;

	if (p == nullptr || p->next == nullptr) {
		return;
	}

	else if (p == head) {
		p->next = p->next->next;
		head = tmp;
		tmp->next = p;
		return;
	}

	else {
		while (H->next != p) {
			H = H->next;
		}

		H->next = tmp;
		p->next = p->next->next;
		tmp->next = p;
		return;
	}
}

// zad6 usun elementy parzyste
void zad6(node*& head) {
	node* tmp = head;

	while (tmp != nullptr) {
		if (tmp->val % 2 == 0) {
			delpoint(head,tmp);
		}
		tmp = tmp->next;
	}
}

// zad7 zamien miejscami co 2 element 
void zad7(node*& head) {
	node* tmp = head;

	while (tmp != nullptr && tmp->next != nullptr) {
		zad5(head, tmp);
		tmp = tmp->next;
	}
}

// zad8 h -> 1 -> 2 -> 3 -> Z => 1 -> 2 -> 3 -> 3 -> 2 -> 1 -> Z

void zad8( node * & head) {
	node* root = nullptr;
	node* H = head;
	node* last = nullptr;

	while (H != nullptr) {
		addH(root, H->val);

		if (H->next == nullptr) {
			last = H;
		}

		H = H->next;
	}

	last->next = root;

	return;
} 

// zad9 rozdzielenie na 2 listy 
void zad9(node* head, node * & H1, node * &  H2) {

	if (head == nullptr) {
		H1 = nullptr;
		H2 = nullptr;
		return;
	}
	H1 = head;
	H2 = head->next;

	node* tmp = H1;
	node* tmp2 = H2;

	while (tmp2 != nullptr && tmp2->next != nullptr) {

		tmp->next = tmp2->next;
		tmp = tmp->next;
		tmp2->next = tmp->next;
		tmp2 = tmp2->next;
	}

	tmp->next = nullptr; // Zakoñczenie listy H1
	head = nullptr;
	
}

// zad10 H = null, H1 = 1,8,13,54, H2 = -6,0,7,10
// polacz te liste sortujac elementy 
// mialam problemy z tym zadaniem 

void zad10(node*& head, node*& H1, node*& H2) {
	head = nullptr;
	node* tail = nullptr; // ostatni element listy wynikowej 

	// zamiast na head dodajemy na tail 
	while (H1 != nullptr && H2 != nullptr) {
		if (H1->val > H2->val) {
			if (head == nullptr) { 
				head = H2;
				tail = H2;
			}
			else {
				tail->next = H2; 
				tail = tail->next;
			}
			H2 = H2->next;
		}
		else {
			if (head == nullptr) {
				head = H1;
				tail = H1;
			}
			else {
				tail->next = H1;
				tail = tail->next;
			}
			H1 = H1->next;
		}
	}

	if (H1 != nullptr) {
		tail->next = H1;
	}

	if (H2 != nullptr) {
		tail->next = H2;
	}
}

// zad11 zamieñ element o wartosci x z nastêpnikiem 

void zad11(node * & head, int x) {
	node* tmp = head;

	while (tmp->next != nullptr || tmp->val != x) {
		tmp = tmp->next;
	}

	if (tmp->next == nullptr && tmp->val != x) {
		cout << "Brak takiej wartoœci" << endl;
		return;
	}

	if (tmp->val == x) {
		zad5(head, tmp);
	}
}

// zad12 kopia listy, H -> 1 -> 2 -> 3 ==> H -> 1 -> 2 -> 2 -> 3 -> 3 -> 3

void zad12(node * & head) {
	node* tmp = head; 

	while (tmp != nullptr) {
		for (int i = 2; i <= tmp->val; i++) {
			node* x = new node;
			x->val = tmp->val;
			x->next = tmp->next;
			tmp->next = x;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

// zad13 zamieñ el. 1 z ostatnim 
void zad13(node*& head) {
	node* tmp = head;
	node* tmp2 = head;


	while (tmp->next != nullptr) {
		tmp2 = tmp;
		tmp = tmp->next;
	}

	tmp->next = head->next;
	tmp2->next = head;
	head->next = nullptr;
	head = tmp;
}

// ------------------------------------------------------------------------------------------

// zad 1 sortowanie babelkowe 


int main() {
	node* head = nullptr;

	// zadania 1-6
	/*cout << "podstawowa lista" << endl;
	add(head, 1);
	add(head, 2);
	add(head, 3);
	add(head, 4);
	add(head, 5);
	add(head, 6);
	read(head);
	zad1(head);
	cout << "zadanie 1" << endl;
	read(head);
	cout << "zadanie 2" << endl;
	zad2(head);
	read(head);
	cout << "zadanie 3" << endl;
	zad3(head);
	read(head);
	cout << "zadanie 4" << endl;
	zad4(head);
	cout << "zadanie 5" << endl;
	node* do_zad_5 = find_first_one(head, 1);
	do_zad_5 = do_zad_5->next;
	zad5(head, do_zad_5);
	read(head);
	cout << "dodam nowe wartosci przed zadaniem 6 " << endl;
	head = nullptr;
	add(head, 1);
	add(head, 2);
	add(head, 3);
	add(head, 4);
	add(head, 5);
	add(head, 6);
	read(head);
	cout << "I zadanie 6" << endl;
	zad6(head);
	read(head);
	cout << "dodam nowe wartosci przed zadaniem 7 " << endl;
	*/ 
	//zadanie 7-9 i 11-13
	
	head = nullptr;
	add(head, 1);
	add(head, 2);
	add(head, 3);
	add(head, 4);
	add(head, 5);
	add(head, 6);
	//read(head);
	//cout << "zadanie 7" << endl;
	zad7(head);
	read(head);
	cout << "zadanie 8" << endl;
	zad8(head);
	read(head);
	/*
	cout << "zadanie 9" << endl;
	node* H1 = nullptr;
	node* H2 = nullptr;
	zad9(head, H1, H2);
	read(H1);
	cout << endl;
	read(H2);
	cout << "dalej bedziemy pracowac na liscie H1" << endl;
	cout << "zadanie 11" << endl;
	zad11(H1, 1);
	read(H1);
	cout << "zadanie 12" << endl;
	zad12(H1);
	read(H1);
	cout << " zadanie 13" << endl;
	zad13(H1);
	read(H1);
	*/
	//zadanie 10
	/*
	cout << " dwie listy posortowane do zad 10" << endl;
	node* H1 = nullptr;
	node* H2 = nullptr;
	addH(H1, 2);
	add(H1, 8);
	add(H1, 13);
	add(H1, 54);
	addH(H2, -6);
	add(H2, 0);
	add(H2, 7);
	add(H2, 10);
	read(H1);
	cout << endl;
	read(H2);
	cout << endl;
	zad10(head, H1, H2);
	read(head);
	*/

	return 0;
}