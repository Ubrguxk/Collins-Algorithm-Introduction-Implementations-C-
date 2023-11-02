#include <iostream>

using namespace std;

// KODY BAZOWANE NA ALGORYTMACH I STRUKTURACH DANYCH CORMENA

//struktura
struct bst {
	bst* left;
	bst* right;
	bst* parent;
	int val;
};

// zasady drzewa 
// po lewo - elementy mniejsze od parent
// po prawo - elementy wieksze od parent

// search time 0(log n )
// inorder time O(n) 

//dodawanie elementow 

void setBST(bst*& root, int x, bst * parent = nullptr) {
	if (root == nullptr) {
		bst* p = new bst;
		p->val = x;
		p->right = nullptr;
		p->left = nullptr;
		p->parent = parent;
		root = p;
	}
	else {
		if (x >= root->val) {
			setBST(root->right, x, root);
		}
		else {
			setBST(root->left, x, root);
		}
	}
}

// dodawanie elementow inaczej 
// domyslnie bst * el -> val = x, el->left = nullptr, el->right = nullptr

void insertBST(bst*& root, bst*& el) {
	bst* y = nullptr;
	bst* x = root; // lepiej u¿yæ wskaznika bo moga byæproblemy gdy lista pusta

	while (x != nullptr) { // przechodzi drzewo az znajdzie nulla ktorego zastapimy el 
		y = x; // zapisujemy rodzica miejsca gdzie zapiszemy el
		if (el->val < x->val) {
			y = x;
			if (el->val < x->val) {
				x = x->left;
			}
			else { x = x->right; }
		}
	}

	el->parent = y;

	if (y == nullptr) {
		x = el; // jezeli rodzica nie ma to 
	}
	else if (el->val < y->val) {
		y->left = el;
	}
	else {
		y->right = el;
	}
}

// wyczytanie preorder
void preorder(bst*& root) {
	if (root != nullptr) {
		cout << "Wartosc elementu to: " << root->val << endl;
		preorder(root -> left);
		preorder(root->right);
	}
}

// wyczytanie inorder
void inorder(bst*& root) {
	if (root != nullptr) {
		inorder(root->left);
		cout << "Wartosc elementu to: " << root->val << endl;
		inorder(root->right);
	}
}

//wyczytanie postorder
void postorder(bst*& root) {
	if (root != nullptr) {
		postorder(root->left);
		postorder(root->right);
		cout << "Wartosc elementu to: " << root->val << endl;
	}
}

//ladny read
void read(bst*& root, bool isRoot = true) {
	if (root != nullptr) {
		cout << root->val << " - ";

		if (isRoot) {
			cout << "Jest on korzeniem" << endl;
 		}
		else {
			if (root->parent->left == root) {
				cout << "Jest on lewym synem elementu " << root->parent->val << endl;
			}
			else {
				cout << "Jest on prawym synem elementu " << root->parent->val << endl;
			}
		}
		read(root->left, false);
		read(root->right,false);
	}
}

// read 2
void read2(bst*& root, bool isRoot = true) {
	if (root == nullptr) {
		return;
	}
	if (root != nullptr) {
		cout << root->val << " - ";

		if (isRoot) {
			cout << "Jest on korzeniem. ";
		}
		if (root->left) {
			cout << "Ma lewego syna " << root->left->val << ". ";
		}
		if (root->right) {
			cout << "Ma prawego syna " << root->right->val << ". ";
		}
		if (root->left == nullptr && root->right == nullptr) {
			cout << "Jest on lisciem.";
		}
		cout << endl;
		read2(root->left, false);
		read2(root->right, false);
	}
}

// wyczytanie elementu 
bst* search(bst*& root, int x) {
	if (root == nullptr || root->val == x) {
		return root;
	}
	if (root->val > x) {
		return search(root->left, x); // Zwracamy wynik rekurencyjnego wywo³ania.
	}
	if (root->val < x) {
		return search(root->right, x); // Zwracamy wynik rekurencyjnego wywo³ania.
	}
}

// bardziej efektyna wersja wyczytania

bst* searchBetter(bst*& root, int x) {
	while (root != nullptr && root->val != x) {
		if (x < root->val) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return root;
}

// minimum 
bst* min(bst* root) {
	while (root->left) {
		root = root->left;
	}
	return root;
}

// maksimum 
bst* max(bst* root) {
	while (root->right) {
		root = root->right;
	}
	return root;
}

// nastêpnik
bst* next(bst*& p) {
	if (p->right) { // je¿eli ma prawego syna
		// to najmniejszy z wiêkszych od niego
		return (min(p->right));
	}
	else {
		bst* par = p->parent;
		// jezeli nie ma prawego drzewa to zwracamy rodzica
		while (par && par->val < p->val) {
			// jezeli rodzic mniejsz od elementu to dziadka az do momentu az ktorys dziadek wiekszy
			p = par;
			par = par->parent;
		}
		return par;
	}
}

// poprzenik
bst* before(bst*& p) {
	if (p->left) {
		return (max(p->right));
	}
	else {
		bst* par = p->parent;
		while (par && par->val < p->val) {
			par = par->parent;
		}
		return par;
	}
}

// czas minimum, maksiumum, search, poprzdnik i nastepnik - O(h) gdzie h = d³ugoœæ drzewa

// wstawienie jednego wezla w miejsce drugiego wezla i zamiana ojcow
void transplant(bst*& root, bst*& u, bst*& v) {

	// jezeli u to root
	if (u->parent == nullptr) {
		root = u;
	}

	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v; // Poprawione: zmieni³em == na =
	}

	if (v != nullptr) {
		v->parent = u->parent;
	}
}

//usuwanie
void deleteBST(bst* & p, bst * & root) {
	bst* par = p->parent;

	// ma prawego syna 
	if (p->left == nullptr) {
		transplant(root, p, p->right);
	}

	// ma lewego syna 
	else if (p->right == nullptr) {
		transplant(root, p, p->left);
	}

	// jezeli ma obu synów badz nie ma zadnego
	else {
		// znajdujemy nastepnik
		bst* nextOne = next(p);

		if (nextOne->parent != p) { // jezeli jest bezposrednim dzieckiem
			transplant(root, nextOne, nextOne->right);//postepujemy tak jak z prawym synem 
			nextOne->right = p->right; //przepisujemy dzieci 
			nextOne->right->parent = p;
		}
		transplant(root, p, nextOne);
		
		nextOne->left = p->left;
		nextOne->left->parent = nextOne;
	}
}

int main() {
	bst* root = nullptr;
	setBST(root, 15);
	setBST(root, 5);
	setBST(root, 3);
	setBST(root, 12);
	setBST(root, 13);
	setBST(root, 10);
	setBST(root, 6);
	setBST(root, 7);
	setBST(root, 16);
	setBST(root, 20);
	setBST(root, 18);
	setBST(root, 23);
	read2(root);
	cout << endl;
	bst* del = search(root, 5);
	deleteBST(del, root);
	read2(root);
}