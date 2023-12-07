#include <iostream>

using namespace std;

static const int sizeL = 13;


struct node {
    node* next;
    string val;
};

void addfront(node*& head, string x) {
    node* p = new node();
    p->val = x;
    p->next = head;
    head = p;
}

void printt(node* p) {
    if (p == nullptr) {
        cout << "brak elementow" << endl;
        return;
    }
    else {
        while (p != nullptr) {
            cout << p->val << "-> ";
            p = p->next;
        }
        cout << endl;
    }
}

void read(node** L) {
    for (int i = 0; i < sizeL; i++) {
        cout << i << ": ";
        node* p = L[i];
        printt(p);
    }
}

int stringToCode(string x) {
    int results = 0;

    for (int i = 0; i < x.length(); i++) {
        if (x[i] >= 65 && x[i] <= 90) {
            results += x[i] - 64;
        }
        else if (x[i] >= 97 && x[i] <= 122) {
            results += x[i] - 96;
        }
    }

    return results;
}

node * search(node** L, string x) {
   node* tmp = L[stringToCode("Aneta") % sizeL];

   int i = 0;
   while (tmp != nullptr) {
       if (tmp->val == x) {
           cout << "Znaleziono element na pozycji " << i+1 << endl;
           return tmp;
       }
       i++;
       tmp = tmp->next;
   }
   cout << "Nie znaleziono elementu " << endl;
   return nullptr;
}

int main() {
    node** L = new node * [sizeL]();

    addfront(L[stringToCode("Aneta") % sizeL], "Aneta");
    addfront(L[stringToCode("Marek") % sizeL], "Marek");
    addfront(L[stringToCode("Damian") % sizeL], "Damian");
    addfront(L[stringToCode("Kasia") % sizeL], "Kasia");

    read(L);
    
    search(L, "Aneta");

    delete[] L;

    return 0;
}
