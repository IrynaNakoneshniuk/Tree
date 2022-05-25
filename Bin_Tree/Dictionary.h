#pragma once
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <map>

using namespace std;

 class  Pair
{
    public:
    string keyWord;
    string ruWord;
    uint32_t counter;
    Pair* parent = nullptr;
    Pair* left = nullptr;
    Pair*right=nullptr;
    Pair(string keyWord, string ruWord) {
        this->keyWord = keyWord;
        this->ruWord = ruWord;
        this->counter = 0;
        this->parent = nullptr;
        this->right = nullptr;
        this->left = nullptr;
    };
    Pair() :Pair("", "") {};
    ~Pair() { this->keyWord.clear(); this->ruWord.clear(); /*delete this->left;
    delete this->right; delete this->parent;*/}
    string getruWord() { return this->ruWord; }
    void setruWord(string newW) { 
        if (!this->ruWord.empty()) {
            this->ruWord.clear();
        }
       this->ruWord = newW;}
    void delruWord(){
        if (!this->ruWord.empty()) {
            this->ruWord.clear();
        }
        this->ruWord = "";
    }
    friend ostream& operator <<(ostream& out, Pair* obj) {
        out << obj->keyWord << "  :  " << obj->ruWord << endl;
        return out;
    }
    void  ChangeCounter() { this->counter++; }
    uint32_t getCounter() { return this->counter; }

};

class Tree {
public:
   Pair* root;
   uint32_t size;
    Tree()
    {
        root = NULL;
        size = 0;
    }
    ~Tree()
    {
        while (this->root != 0) {
            Pair* del = this->Min(this->root);
            this->Del(del);
        }
    }
    void Print(Pair* Node)
    {
        if (Node != 0)
        {
            Print(Node->left);
            cout << Node->keyWord << " : " << Node->ruWord << "  " << Node->counter << endl;
            Print(Node->right);
        }
    }
    Pair*Search(string k)
    {
        Pair* Node = this->root;
        while (Node != 0 && k != Node->keyWord)
        {
            if (k < Node->keyWord)
                Node = Node->left;
            else if(k >Node->keyWord) 
                Node = Node->right;
        }
        if (Node) {
            Node->ChangeCounter();
            return Node;
        }
        return 0;
    }
    Pair* Min(Pair* Node)
    {
        if (Node != 0)
            while (Node->left != 0)
                Node = Node->left;
        return Node;
    }
    Pair* Max(Pair* Node)
    {
        if (Node != 0)
            while (Node->right != 0)
                Node = Node->right;
        return Node;
    }
    Pair* Next(Pair* Node)
    {
        Pair* y = 0;
        if (Node != 0)
        {
            if (Node->right != 0) {
                return Min(Node->right);
            }
            y = Node->parent;
            while (y != 0 && Node == y->right)
            {
                Node = y;
                y = y->parent;
            }
        }
        return y;
    }
    Pair* Previous(Pair* Node)
    {
        Pair* y = 0;
        if (Node != 0)
        {
            if (Node->left != 0)
                return Max(Node->left);
            y = Node->parent;
            while (y != 0 && Node == y->left)
            {
                Node = y;
                y = y->parent;
            }
        }
        return y;
    }
    Pair* GetRoot()
    {
        return root;
    }
    void Insert(Pair* z)
    {
        z->left = NULL;
        z->right = NULL;
        Pair* y = NULL;
        Pair* Node = root;
        while (Node != 0)
        {
            y = Node;
            if (z->keyWord < Node->keyWord) {
                Node = Node->left;
            }
            else {
                Node = Node->right;
            }
        }
        z->parent = y;
        if (y == 0) {
            root = z;
        }
        else if (z->keyWord < y->keyWord) {
            y->left = z;
        }
        else {
            y->right = z;
        }
        this->size++;
    }
    void Del(Pair* z)
    {
        if (z != 0)
        {
            Pair* Node, * y;
            if (z->left == 0 || z->right == 0) {
                y = z;
            }
            else {
                y = Next(z);
            }
            if (y->left != 0) {
                Node = y->left;
            }
            else {
                Node = y->right;
            }
            if (Node != 0) {
                Node->parent = y->parent;
            }
            if (y->parent == 0) {
                root = Node;
            }
            else if (y == y->parent->left) {
                y->parent->left = Node;
            }
            else {
                y->parent->right = Node;
            }
            if (y != z)
            {
                z->keyWord = y->keyWord;
            }
            delete y;
        }
        else
            while (root != 0) {
                Del(root);
            }
    }
};

class Dictionary {
  private:
    Tree* tree;
    multimap<uint32_t, string>* m;
    size_t N = 0;
  public:
      Dictionary()
      {
          this->tree = new Tree();
          this->m = new multimap<uint32_t, string>();
      }
      ~Dictionary() { tree->~Tree(); }
      void InputWord() {
          string ruWord;
          string enWord;
          cout << "\nInput russian word:  ";
          cin >> ruWord;
          cout << "\nInput english word: ";  
          cin >> enWord;
          Pair* p = new Pair(enWord, ruWord);
          tree->Insert(p);
      }
      void Print() {
          this->tree->Print(tree->root);
      }
      void Search() {
          string enWord;
          cout << "\nInput english word for searching: ";
          cin >> enWord;
          if (tree->Search(enWord)) {
              cout << tree->Search(enWord) << endl;
              this->RangeWord(tree->Search(enWord));
              this->N++;
          }
          else {
              cout << "\nWord not found!" << endl;
          }
          system("pause");
      }
      void ChangeTranslate() {
          string enWord;
          string ruWord;
          cout << "\nInput english word for searching: ";
          cin >> enWord;
          cout << "\nInput russian word for change the translation: ";
          cin >> ruWord;
          auto item = tree->Search(enWord);
          if (item) {
              item->setruWord(ruWord);
          }
          else {
              cout << "\nWord not found!" << endl;
          }
      }
      void DelTranslate() {
          string enWord;
          string ruWord;
          cout << "\nInput english word for searching: ";
          cin >> enWord;
          cout << "\nInput russian word for removing the translation: ";
          cin >> ruWord;
          auto item = tree->Search(enWord);
          if (item) {
              item->delruWord();
          }
          else {
              cout << "\nWord not found!" << endl;
          }
      }
      void AddTranslate() {
          string enWord;
          string ruWord;
          cout << "\nInput english word for searching: ";
          cin >> enWord;
          cout << "\nInput russian word for adding the translation: ";
          cin >> ruWord;
          auto item = tree->Search(enWord);
          if (item) {
              item->setruWord(item->getruWord() += " ,");
              item->setruWord(item->getruWord() += ruWord);
          }
          else {
              cout << "\nWord not found!" << endl;
          }
      }
      void DelWord() {
          string enWord;
          cout << "\nInput english word for searching: ";
          cin >> enWord;
         auto item= tree->Search(enWord);
         if (item) {
             tree->Del(item);
         }
         else {
             cout << "\nWord not found!" << endl;
         }
      }
      void RangeWord(Pair*obj) {
          pair < uint32_t, string>p(obj->getCounter(), obj->keyWord);
          m->insert(p);
      }
      void OutMaxReq() {
          auto iter = m->begin();
          for (size_t i = 0; i < N; i++,iter++) {
              cout << iter->first << " : " << iter->second << endl;
          }
      }
      void OutMinReq() {
          auto iter = tree->root;
          if (iter->counter == 0) {
              cout << iter << endl;
          }
      }
};
