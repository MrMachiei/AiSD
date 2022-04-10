#include <iostream>

using namespace std;  

class BST{
private:
	struct Node{
		Node * Left = NULL;
		Node * Right = NULL;
		Node * Up;
		int key;
		int value;
	};
public:
	Node *root = new Node;
	BST(int key, int value){
		root->key = key;
		root->value = value;
		root->Up = NULL;
	}
	~BST(){
		postDest(root);
	}
	void append(int key, int value){
		Node * p = root;
		while(1){
		if(p->key >= key){
			if(p->Left != NULL){
				p = p->Left;
			}else{
				Node *k = new Node;
				p->Left = k;
				k->Up = p;
				k->key = key;
				k->value = value;
				return;
			}
		}
		if(p->key <= key){
			if(p->Right != NULL){
				p = p->Right;
			}else{
				Node *k = new Node;
				p->Right = k;
				k->Up = p;
				k->key = key;
				k->value = value;
				return;
			}
			}
		}
	}
	Node* findNode(int key){
		Node* p = root;
		while(p && p->key != key){
			if(p->key > key) p = p->Left;
			else p = p->Right;
		}
		return p;
	}
	Node* maxNode(Node* p){
		if(p!= NULL){
			while(p->Right != NULL) p = p->Right;
		}
		return p;
	}
	Node* minNode(Node* p){
		if(p!= NULL){
			while(p->Left != NULL) p = p->Left;
		}
		return p;
	}
	Node* find_next(Node* p){
		Node* help;
		if(p!= NULL){
			if(p->Right != NULL){
				return minNode(p->Right);
			}else{
				help = p->Up;
				while(help != NULL && (help->Right == p)){
					p = help;
					help = help -> Up;
				}
				return help;
			}
		}
		return p;
	}
	void remove(int key){
		Node * N1, *N2, *p = findNode(key);
		if(p == NULL) return;
		if(p->Left == NULL || p->Right == NULL) N1 = p;
		else N1 = find_next(p);
		if(N1->Left != 0) N2 = N1->Left;
		else N2 = N1->Right;
		if(N2!=NULL){
			N2->Up = N1 -> Up;
		}
		if(N1->Up == NULL) root = N2;
		else if(N1 == (N1->Up)->Left) (N1->Up)->Left = N2;
		else (N1->Up)->Right = N2;
		if(N1 != p){
			p->key = N1->key;
			p->value = N1->value;
		}
		delete N1;
	}
	void update(int key_find, int value){
		Node* p = findNode(key_find);
		p->value = value;
	}
	void postDest(Node * p){
		if(p == NULL) return;
		postDest(p -> Left);
		postDest(p -> Right);
		delete p;
	}
	void preOrder(Node * p){
		if(p == NULL) return;
		cout << "KEY: " << p -> key << " VALUE: " << p -> value<< endl;
		preOrder(p -> Left);
		preOrder(p -> Right);
	}
	void inOrder(Node * p){
		if(p == NULL) return;
		inOrder(p -> Left);
		cout << "KEY: " << p -> key << " VALUE: " << p -> value << endl;
		inOrder(p -> Right);
	}
	void postOrder(Node * p){
		if(p == NULL) return;
		postOrder(p -> Left);
		postOrder(p -> Right);
		cout << "KEY: " << p -> key << " VALUE: " << p -> value<< endl;
	}
};

class AVL{
private:
	struct Node{
		Node * Left = NULL;
		Node * Right = NULL;
		Node * Up;
		int key;
		int value;
		int bf = 0;
	};
public:
	Node *root = new Node;
	AVL(int key, int value){
		root->key = key;
		root->value = value;
		root->Up = NULL;
	}
	~AVL(){
		postDest(root);
	}
	void RR(Node* p){
		Node* parent, *child;
		parent = p->Up;
		child = p->Right;
		p->Right = child->Left;
		if(p->Right != NULL) (p->Right)->Up = p;
		child->Left = p;
		child->Up = parent;
		p->Up = child;
		if(parent != NULL){ // jezeli p to nie korzen
			if(parent->Left == p) parent->Left = child;
			else parent->Right = child;
		}else root = child;
		if(child->bf == -1) p->bf = child->bf = 0;
		else{
			p->bf = -1;
			child->bf = 1;
		}
	}
	void LL(Node* p){
		Node* parent, *child;
		parent = p->Up;
		child = p->Left;
		p->Left = child->Right;
		if(p->Left != NULL) (p->Left)->Up = p;
		child->Right = p;
		child->Up = parent;
		p->Up = child;
		if(parent != NULL){ // jezeli p to nie korzen
			if(parent->Left == p) parent->Left = child;
			else parent->Right = child;
		}else root = child;
		if(child->bf == 1) p->bf = child->bf = 0;
		else{
			p->bf = -1;
			child->bf = 1;
		}
	}
	void RL(Node* p){
		Node* N1 = p->Right, *N2 = N1->Left, *N3 = p->Up;
		N1->Left = N2->Right;
		if(N1->Left != NULL) (N1->Left)->Up = N1;
		p->Right = N2 ->Left;
		if(p->Right != NULL) (p->Right)->Up = p;
		N2->Left = p;
		N2->Right = N1;
		p->Up = N1->Up = N2;
		N2->Up = N3;
		if(N3 != NULL){
			if(N3->Left == p) N3->Left = N2;
			else N3->Right = N2;
		}else root = N2;
		if(N2->bf == -1) p->bf = 1;
		else p->bf = 0;
		if(N2->bf == 1) N1->bf = 1;
		else N1->bf = 0;
		N2->bf = 0;
	}
	void LR(Node* p){
		Node* N1 = p->Left, *N2 = N1->Right, *N3 = p->Up;
		N1->Right = N2->Left;
		if(N1->Right != NULL) (N1->Right)->Up = N1;
		p->Left= N2 ->Right;
		if(p->Left != NULL) (p->Left)->Up = p;
		N2->Right = p;
		N2->Left = N1;
		p->Up = N1->Up = N2;
		N2->Up = N3;
		if(N3 != NULL){
			if(N3->Left == p) N3->Left = N2;
			else N3->Right = N2;
		}else root = N2;
		if(N2->bf == 1) p->bf = -1;
		else p->bf = 0;
		if(N2->bf == -1) N1->bf = 1;
		else N1->bf = 0;
		N2->bf = 0;
	}
	void append(int key, int value){
		Node * p = root;
		Node *k = new Node;
		while(1){
		if(p->key >= key){
			if(p->Left != NULL){
				p = p->Left;
			}else{
				p->Left = k;
				k->Up = p;
				k->key = key;
				k->value = value;
				break;
			}
		}
		if(p->key <= key){
			if(p->Right != NULL){
				p = p->Right;
			}else{
				p->Right = k;
				k->Up = p;
				k->key = key;
				k->value = value;
				break;
			}
			}
		}
		if(p->bf != 0) p->bf = 0;
		else{
			if(p->Left == k){
				p->bf = 1;
			} //lewy syn
			else p->bf = -1;
			k = p->Up;
			bool flag = false;
			while(k != NULL){
				if(k->bf != 0){
					flag = true; //potrzeba rotacji
					break;
				}
				if(k->Left == p) k->bf = 1;
				else k->bf = -1;
				p = k;
				k = p->Up;
			}
			if(flag == true){
				if(k->bf == 1){
					if(k->Right == p) k->bf = 0;//rownowaga
					else if(p->bf == -1) LR(k);
					else LL(k);
				}else{
					if(k->Left == p) k->bf = 0;//rownowaga
					else if(p->bf == -1) RR(k);
					else RL(k);
				}
			}
		}
	}
	Node* findNode(int key){
		Node* p = root;
		while(p != NULL && p->key != key){
			if(p->key > key) p = p->Left;
			else p = p->Right;
		}
		return p;
	}
	Node* maxNode(Node* p){
		if(p!= NULL){
			while(p->Right != NULL) p = p->Right;
		}
		return p;
	}
	Node* minNode(Node* p){
		if(p!= NULL){
			while(p->Left != NULL) p = p->Left;
		}
		return p;
	}
	Node* find_next(Node* p){
		Node* help;
		if(p!= NULL){
			if(p->Right != NULL){
				return minNode(p->Right);
			}else{
				help = p->Up;
				while(help != NULL && (help->Right == p)){
					p = help;
					help = help -> Up;
				}
				return help;
			}
		}
		return p;
	}
	Node* find_before(Node* p){
		Node* help;
		if(p!= NULL){
			if(p->Left != NULL){
				return maxNode(p->Left);
			}else{
				help = p->Up;
				while(help != NULL && (help->Left == p)){
					p = help;
					help = help -> Up;
				}
				return help;
			}
		}
		return p;
	}
	void remove(int key){
		Node * N1, *N3, *k, *N2 = NULL,*p = findNode(key);
		if(p==NULL) return;
		if(p->Left == NULL && p->Right == NULL){
			if(p==root){
				cout << "NIE MOZNA USUNAC KORZENIA!\n";
				return;
			}
			N1 = p;
			//TU BEDE COS ROBIC
		}else if(p->Left == NULL || p->Right == NULL){//jedno dziecie
			N1 = p;
		}
		else{ // ma dwojke dzieci
			N1 = find_before(p);
		}
		k = (N1->Up);
		int strona; //1 jesli lewa
		if(k == NULL) strona = 0;
		else strona = k->Left == N1 ? 1 : -1;
		if(N1->Right != 0) N2= N1->Right;
		else N2= N1->Left;
		if(N2!=NULL){
			N2->Up = N1->Up;
		}
		if(N1->Up == NULL) root = N2;
		else if ((N1->Up)->Left == N1){
			(N1->Up)->Left = N2;
		}else{
			(N1->Up)->Right = N2;
		}
		if(N1 != p){
			p->key = N1->key;
			p->value = N1->value;

		}
		delete N1;
		//N2 = p->Up;
		/*if(k==NULL){
			if(root -> bf == 0){
				root -> bf = strona == -1 ? 1: -1;
			}else if(root->bf == 1){
				if(strona == 1) root->bf = 0;/*!!!!!!
				else LL(root);
			}else{
				if(strona == -1) root->bf = 0;
				else RR(root);
			}
		}*/
		while(k != NULL){
			N2 = k->Up;
			if(k->bf == 0){
				if(k==root) return;
				k->bf = strona == -1? 1: -1;
			}else if(k->bf == -1){
				if(strona == -1) k->bf = 0;
				else{
					if((k->Right)->bf == 1) RL(k);
					else RR(k);
					if(k->bf == 0){
						k=k->Up;
						if( k== NULL){
						break;
					}
				}
			}
			}else{
				if(strona == 1) k->bf = 0;
				else{
					if((k->Left)->bf == -1) LR(k);
					else LL(k);
					if(k->bf == 0){
						k=k->Up;
						if( k== NULL){
						break;
					}
				}
			}
		}
			N2 = k;
			k = k->Up;
			if( k== NULL){
				break;
		}
			strona = k->Right == N2? -1: 1;
		}
	}
	void update(int key_find, int value){
		Node* p = findNode(key_find);
		p->value = value;
	}
	void postDest(Node * p){
		if(p == NULL) return;
		postDest(p -> Left);
		postDest(p -> Right);
		delete p;
	}
	void preOrder(Node * p){
		if(p == NULL) return;
		cout << "KEY: " << p -> key << " VALUE: " << p -> value  << " BF: " << p-> bf << endl;
		preOrder(p -> Left);
		preOrder(p -> Right);
	}
	void inOrder(Node * p){
		if(p == NULL) return;
		inOrder(p -> Left);
		cout << "KEY: " << p -> key << " VALUE: " << p -> value  << " BF: " << p-> bf << endl;
		inOrder(p -> Right);
	}
	void postOrder(Node * p){
		if(p == NULL) return;
		postOrder(p -> Left);
		postOrder(p -> Right);
		cout << "KEY: " << p -> key << " VALUE: " << p -> value << " BF: " << p-> bf << endl;
	}
	int get(Node *p){
		return p->key;
	}
};
int main(){
	AVL root(3,3);
	root.append(2,0);
	//root.append(4,0);
	root.append(18,0);
	root.append(1,0);
	root.append(16,0);
	root.append(20,0);
	root.append(15,0);
	root.inOrder(root.root);
	cout << endl;
	root.remove(2);
	root.preOrder(root.root);
}