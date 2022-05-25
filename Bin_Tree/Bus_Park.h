#pragma once
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

template<typename T>
class File_S {
private:
	ofstream file;
	string nameFile;
	string path;
public:
	File_S(string nameFile, string path) {
		this->path = path;
		this->nameFile = nameFile;
	}
	~File_S() { this->file.clear(); this->nameFile.clear(); this->path.clear(); }
	void OpenFile() {
		file.open(path+nameFile, ios::out |ios::binary);
	}
	void SaveInFile(T* obj) {
		if (file) {
			T buf = *obj;
			file.write((char*)&buf, sizeof(buf));
		}
		else {
			throw;
		}
	}
	void CloseFile() {
		file.close();
	}
};
class Bus
{
public:
	uint32_t numberBus;
	uint32_t qtyPlace;
	string nameDrivers;
	uint32_t numberRoute;
	 Bus(uint32_t numberBus, uint32_t qtyPlace, 
		 string nameDrivers, uint32_t numberRoute) {
		 this->nameDrivers = nameDrivers;
		 this->numberBus = numberBus;
		 this->numberRoute = numberRoute;
		 this->qtyPlace = qtyPlace;
	 }
	 Bus() : Bus(0, 0, "", 0) {};
	 ~Bus() { this->nameDrivers.clear(); };
	 uint32_t getNumberBus(){ return this->numberBus; }
	 friend ostream& operator<<(ostream& out, Bus& obj) {
		 out << "\nNumber bus :  " << obj.numberBus <<" , " << "Drivers name:  " << obj.nameDrivers
			 <<" , " << "Qty place: " << obj.qtyPlace <<" , " << "Route number:  " << obj.numberRoute<<";" << endl;
		 return out;
	 }
};

class Bus_Park {
private:
	map<uint32_t, Bus>* park;
public:
	Bus_Park() { park = new map<uint32_t, Bus>(); }
	~Bus_Park() { this->Clear(); }
	void AddBus(uint32_t numberBus, uint32_t qtyPlace, string nameDrivers, uint32_t numberRoute) {
		Bus bus(numberBus, qtyPlace, nameDrivers, numberRoute);
		pair< uint32_t, Bus> p(numberBus, bus);
		park->insert(p);
	}
	void FindAndPrint(uint32_t Number_bus) {
		auto item = park->find(Number_bus);
		cout << item->first << " : " << item->second << endl;
	}
	void Print_All() {
		auto item = park->begin();
		if (item == park->end()) {
			cout << "\nNo information!" << endl;
		}
		else {
			for (; item != park->end(); item++) {
				cout << item->first << ": " << item->second << endl;
			}
		}
	}
	void SaveInFile(string nameF, string path) {
		try {
			auto item = park->begin();
			File_S<Bus>* f = new File_S<Bus>(nameF, path);
			if (item == park->end()) {
				cout << "\nNo information!" << endl;
				system("pause");
			}
			else {
				f->OpenFile();
				for (; item != park->end(); item++) {
					f->SaveInFile(&item->second);
				}
				f->CloseFile();
			}
		}
		catch (const ifstream::failure& e) {
			cout << e.what() << endl;
		}
	}
	void Clear() {
		park->clear();
	}
	bool empty(){return (park->empty()) ? true : false;}
};

