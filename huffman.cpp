#include <iostream>

using namespace std;

struct letters {
    char val;
    letters* right;
    letters* left;
    letters* parent;
};

struct node {
    int val;
    letters* tree;
    node* next;
};

node* head = nullptr;
letters* root = nullptr;

void addNode(node*& head, int x, letters*& let) {
    node* tmp = head;
    node* addn = new node;

    if (tmp == nullptr) {
        node* tmp = new node;
        tmp->val = x;
        tmp->next = head;
        tmp->tree = let;
        head = tmp;
    }
    else {
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = addn;
        addn->val = x;
        addn->next = nullptr;
        addn->tree = let;
        return;
    }
}

bool findnode(node* head, char x) {
    while (head != nullptr) {
        letters* tmp = head->tree;

        if (tmp != nullptr && tmp->val == x) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void setLetters(letters*& root, char x, letters* parent = nullptr) {
    if (root == nullptr) {
        letters* p = new letters;
        p->val = x;
        p->right = nullptr;
        p->left = nullptr;
        p->parent = parent;
        root = p;
    }
    else {
        if (x >= root->val) {
            setLetters(root->right, x, root);
        }
        else {
            setLetters(root->left, x, root);
        }
    }
}

void IncreaseVAL(node*& head, int x) {
    node* current = head;
    while (current != nullptr) {
        letters* tmp = current->tree;
        if (tmp->val == x) {
            current->val += 1;
            //cout << "Dodano jeden do litery " << current->tree->val;
            //cout << ". Obecna liczba " << current->val << endl;
        }
        current = current->next;
    }
    return;
}

void read2(letters*& root, bool isRoot = true) {
    if (root == nullptr) {
        return;
    }
    if (root != nullptr) {
        cout << root->val << " - ";

        if (isRoot) {
            cout << "Jest ona korzeniem. ";
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

void readLIST(node*& head) {
    node* tmp = head;

    while (tmp != nullptr) {
        cout << "Litera: ";
        read2(tmp->tree);
        cout << "Wartosc : " << tmp->val << endl;
        tmp = tmp->next;
    }
}

void connectTrees(node*& head) {
    node* p1 = nullptr;
    node* p2 = nullptr;
    letters* p1tree = nullptr;
    letters* p2tree = nullptr;
    node* tmp = head;

    while (tmp != nullptr) {
        if (p1 == nullptr || tmp->val < p1->val) {
            p2 = p1;
            p2tree = p1tree;
            p1 = tmp;
            p1tree = tmp->tree;
        }
        else if (p2 == nullptr || tmp->val < p2->val) {
            p2 = tmp;
            p2tree = tmp->tree;
        }
        tmp = tmp->next;
    }
    if (p2 == nullptr) {
        return;
    }

    //cout << "p1 = " << p1->val << endl;
    //cout << "p2 = " << p2->val << endl;

    letters* blank = new letters;
    blank->parent = nullptr;
    blank->left = p1tree;
    blank->right = p2tree;
    blank->val = NULL;

    p1->tree = blank;
    p1->val += p2->val;

    tmp = head;
    if (p2 == head) {
        head = head->next;
        delete p2;
    }
    else {
        while (tmp->next != p2) {
            tmp = tmp->next;
        }

        tmp->next = p2->next;

        delete p2;
    }
    
    //readLIST(head);
    connectTrees(head);
}

void defuse(string x) {
    int length = x.length();

    for (int i = 0; i < length; i++) {

        if (findnode(head, x[i]) == false) {
            letters* newer = new letters;
            newer->val = x[i];
            newer->left = nullptr;
            newer->right = nullptr;
            newer->parent = nullptr;
            addNode(head, 1, newer);
            //cout << "Dodano nowa litere " << x[i] << endl;
        }

        else {
            IncreaseVAL(head, x[i]);
        }
    }

    cout << "Slowo ma " << length << " znakow" << endl;
    
    readLIST(head);
    cout << endl;
    connectTrees(head);
    readLIST(head);
    
}

string findCode(letters* node, char ch, string code) {
    if (node == nullptr) {
        return "";
    }

    // Jeœli jesteœmy w liœciu i jest to szukany znak, zwróæ aktualny kod
    if (node->val == ch && node->left == nullptr && node->right == nullptr) {
        return code;
    }

    // Przeszukaj lewe poddrzewo
    string leftCode = findCode(node->left, ch, code + "0");

    if (!leftCode.empty()) {
        return leftCode;
    }

    // Przeszukaj prawe poddrzewo
    string rightCode = findCode(node->right, ch, code + "1");

    return rightCode;
}

void encoding(letters* root, letters * tmp) {
    if (root == nullptr) {
        return;
    }

    if (root != nullptr) {
       
        if (root->val != NULL) {
            cout << "Litera : " << root->val << endl;
            cout << "Wartosc : " << findCode(tmp, root->val, "") << endl;
 
        }

        encoding(root->left,tmp);
        encoding(root->right,tmp);
    }
}

void decode(node* root, string x) {
    letters* tmp = root->tree;
    int i = 0;
   while (tmp !=nullptr) {
        if (x[i] == '0') {
            tmp = tmp->left;
            i++;
        }
        else if (x[i] == '1') {
            tmp = tmp->right;
            i++;
        }
        else {
            cout << "wartosc:" << tmp->val << endl;
            return;
        }
    }

}

int main() {
    string slowo = "DAAFDDGFDSESESFSFDDFADFDAFDAFDDFSFDSFDSFDSDXFDDFSFDFFDAFDFDXFDFDGFDGFDSDAAAASAADSASASASASASASASAAAAAAAAASASSAWASAAAAAASASASDADDSADSADSSAASAAAADSADSSDAAAAADSASADSAAAAAAAASDADSADSADSASASASSSAAAAASSADSASADSAAAAFDFESDSADSADDSADADSFFFDSDSDAAAAAA";
    defuse(slowo);
    encoding(head->tree, head->tree);
    //decode(head,"110001");
}