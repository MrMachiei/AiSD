#include <iostream>
#include <functional>

using namespace std;

class Node
{
    public:
    Node *prev;
    Node *next;
    int key;
    int value;
};

Node *head = nullptr, *tail = nullptr;

void insertNode(int k, int v)
{
    Node *newNode = new Node();
    newNode->key = k;
    newNode->value = v;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if(head == nullptr)
    {
        head = newNode;
        tail = newNode;
        return;
    }

    newNode->next = head;

    if(newNode->next->key > newNode->key)
    {
        head = newNode;
        newNode->next->prev = newNode;
        return;
    }
    while (newNode->next->key < newNode->key)
    {
        if(newNode->next == tail)
        {
            newNode->prev = newNode->next;
            newNode->next->next = newNode;
            newNode->next = nullptr;
            tail = newNode;
            return;
        }
        newNode->next = newNode->next->next;
    }

    if(newNode->next->key == newNode->key)
    {
        cout<<"Podany klucz:"<<newNode->key<<" juz istnieje."<<endl;
        return;
    }

    newNode->prev = newNode->next->prev;
    newNode->next->prev = newNode;
    newNode->prev->next = newNode;//tu

    return;
}

void printList(Node *current)
{
    int i=0;
    while(current != nullptr)
    {
        cout<<++i<<". Klucz: "<<current->key<<" Wartosc: "<<current->value<<endl;
        current = current->next;

        if(i>10)
            break;
    }
}

void removeNode(int k)
{
    Node *i = head;

    while(i!=nullptr)
    {
        if(i->key == k)
        {
            if(i == head)
            {
                i->next->prev = nullptr;
                head = i->next;
            }
            else if(i == tail)
            {
                i->prev->next = nullptr;
                tail = i->prev;
            }
            else
            {
                i->next->prev = i->prev;
                i->prev->next = i->next;
            }

            delete i;
            break;
        }
        else
        {
            i = i->next;
        }
    }
}

void findNode(int k)
{
    Node *i = head;
    while(i != nullptr && i->key != k)
    {
        i = i->next;
    }

    if (i == nullptr)
    {
        cout<<"Brak wartosci dla tego klucza."<<endl;
        return;
    }

    cout<<i->value<<endl;
}

void removeList(){
    if(head == nullptr){
        return;
    }
    Node* k = head;
    while(k != tail){
        //cout<<k->value<<endl;
        k = k->next;
        delete k->prev;
    }
    tail = nullptr;
    head = nullptr;
}

int main()
{

    insertNode(2, 2);
    insertNode(4, 4);
    insertNode(3, 3);
    insertNode(5, 5);
    insertNode(1, 1);
    insertNode(12, 12);
    printList(head);
    removeNode(1);

    printList(head);

    findNode(1421);
    removeList();
    printList(head);
    return 0;
}
