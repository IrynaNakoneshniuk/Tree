#include <iostream>
#include <fstream>
#include <conio.h>
#include "Dictionary.h"
#include "Binary_Tree.h"
#include "Bus_Park.h"

using namespace std;
void Task1() {
	Dictionary* dictionary = new Dictionary();
	char n = 0;
	while (true) {
		system("cls");
		cout << "\nMenu" << endl;
		cout << "\n1-Add word" << endl;
		cout << "\n2-Remove word" << endl;
		cout << "\n3-Remove translate" << endl;
		cout << "\n4- Search word" << endl;
		cout << "\n5-Add translate" << endl;
		cout << "\n6-Change translate" << endl;
		cout << "\n7-Popular word" << endl;
		cout << "\n8-Unpopular word" << endl;
		cout << "\n9-Exit" << endl;
		cout << "\nDo your choice:";
		cin >> n;
		switch (n) {
		case '1':
			dictionary->InputWord();
			break;
		case '2':
			dictionary->DelWord();
			break;
		case '3':
			dictionary->DelTranslate();
			break;
		case '4':
			dictionary->Search();
			break;
		case '5':
			dictionary->AddTranslate();
			break;
		case '6':
			dictionary->ChangeTranslate();
			break;
		case '7':
			dictionary->OutMaxReq();
			system("pause");
			break;
		case'8':
			dictionary->OutMinReq();
			system("pause");
			break;
		case'9':
			dictionary->~Dictionary();
			return;
			break;
		default:
			cout << "\nUncorrect value!" << endl;
			system("pause");
			break;
		};
	}
}
void Task2() {
	char choise;
	Bus_Park* b_p = new Bus_Park();
	while (true) {
		system("cls");
		cout << "\nMenu" << endl;
		cout << "\n1- Add bus" << endl;
		cout << "\n2-Search information about bus" << endl;
		cout << "\n3-Print information about all buses" << endl;
		cout << "\n4-Save in file" << endl;
		cout << "\n5-Exit" << endl;
		cout << "\n6-Clear information" << endl;
		cout << "\nDo yor choise: " << endl;
		cin >> choise;
		if (choise == '1') {
			uint32_t numberB;
			uint32_t qtySeats;
			string nameDriver;
			uint32_t routeN;
			cout << "\nEnter a bus number: ";
			cin >> numberB;
			cout << "\nEnter an amount of seats: ";
			cin >> qtySeats;
			cout << "\nEnter name of driver: ";
			cin >> nameDriver;
			cout << "\nEnter a route number: ";
			cin >> routeN;
			b_p->AddBus(numberB, qtySeats, nameDriver, routeN);

		}
		else if (choise == '2') {
			uint32_t numberBus;
			cout << "\nEnter a bus number for searching: ";
			cin >> numberBus;
			b_p->FindAndPrint(numberBus);
			system("pause");
		}
		else if (choise == '3') {
			b_p->Print_All();
			system("pause");
		}
		else if (choise == '4') {
			if (!b_p->empty()) {
				string nameFile;
				string path;
				cout << "\nEnter name of file: ";
				cin >> nameFile;
				cout << "\nEnter path: ";
				b_p->SaveInFile(nameFile, path);
			}
			else {
				cout << "\Collection is empty!" << endl;
				system("pause");
			}
		}
		else if (choise == '5') {
			b_p->~Bus_Park();
			return;
		}
		else if (choise == '6') {
			b_p->Clear();
		}
		else {
			cout << "\n Uncorrect value!" << endl;
		}
	}
}

int main()
{
	//Task1();
	Task2();
	return 0;
}

