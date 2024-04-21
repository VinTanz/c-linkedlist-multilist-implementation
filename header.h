#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

typedef char string[100];
typedef struct Child* AddressChild;
typedef struct Parent* AddressParent;

typedef struct DataChild{
	string namaPasien;
	string keluhan;
	int perawatan;
	string status;
}DataChild;

typedef struct DataParent{
	string namaDokter;
	string status;
	string spesialisasi;
}DataParent;

typedef struct Child{
	DataChild dataChild;
	AddressChild next;
}NodeChild;

typedef struct Parent{
	DataParent dataParent;
	AddressParent next;
	AddressChild firstChild;
}NodeParent;

typedef struct{
	AddressParent firstParent;
}Multilist;

// Source Parent
DataParent makeDataParent(string dokter, string status, string spesialisasi);
void createEmpty(Multilist *L);
// Alokasi
AddressParent alokasiParent(DataParent data);
AddressParent findParent(Multilist L, string dokter);

void insertFirstParent(Multilist *L, DataParent data);
void insertAfterParent(Multilist *L, string dokter, DataParent data);
void insertLastParent(Multilist *L, DataParent data);

void deleteFirstParent(Multilist *L);
void deleteAtParent(Multilist *L, string dokter);
void deleteLastParent(Multilist *L);
void deleteAllChild(AddressParent parent);
void printParent(AddressParent parent);
void printAll(Multilist L);
void printAllParent(Multilist L);
bool isEmpty(Multilist L);
bool haveChild(AddressParent ap);

// Source Child
DataChild makeDataChild(string pasien, string keluhan, int lama, string status);
AddressChild alokasiChild(DataChild data);
void insertFirstChild(Multilist L, string dokter, DataChild data);
void insertLastChild(Multilist L, string dokter, DataChild data);
void deleteFirstChild(Multilist L, string dokter);
void deleteLastChild(Multilist L, string dokter);
void printChild(AddressChild child);
void printAllChild(AddressParent parent);
void nextDay(Multilist *L, int hari);

// Fungsi Umum
bool isUnique(Multilist L, int id);
int countParent(Multilist L);
void visualisasiData(Multilist L);

