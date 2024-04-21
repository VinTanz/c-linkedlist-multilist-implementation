#include "header.h"

void createEmpty(Multilist *L){
	L->firstParent = NULL;
}
bool isEmpty(Multilist L){
	return L.firstParent == NULL;
}
bool haveChild(AddressParent ap){
	return ap->firstChild != NULL;
}
//bool isUnique(Multilist L, int id){
//	AddressParent temp = L.firstParent;
//
//	while(temp != NULL){
//		if(temp->dataParent.idMentor == id){
//			return false;
//		}
//		temp = temp->next;
//	}
//	return true;
//}
DataParent makeDataParent(string dokter, string status, string spesialisasi){
	DataParent data;

	strcpy(data.namaDokter, dokter);
	strcpy(data.status, status);
	strcpy(data.spesialisasi, spesialisasi);

	return data;
}
AddressParent alokasiParent(DataParent data){
	AddressParent ap;

	ap = (AddressParent) malloc(sizeof(NodeParent));
	ap->next = NULL;
	ap->firstChild = NULL;
	ap->dataParent = data;

	return ap;
}
AddressParent findParent(Multilist L, string dokter){
	AddressParent temp = NULL;

	temp = L.firstParent;
	while(temp != NULL){
		if(strcmpi(temp->dataParent.namaDokter, dokter)==0){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
void insertFirstParent(Multilist *L, DataParent data){
	AddressParent temp = alokasiParent(data);

	temp->next = L->firstParent;
	L->firstParent = temp;
}
void insertAfterParent(Multilist *L, string dokter, DataParent data){
	AddressParent dataBaru = alokasiParent(data);

	if(!isEmpty(*L)){
		AddressParent temp = findParent(*L, dokter);
		if(temp != NULL){
			dataBaru->next = temp->next;
			temp->next = dataBaru;
		}
	}
}
void insertLastParent(Multilist *L, DataParent data){
	AddressParent dataBaru = alokasiParent(data);

	if(isEmpty(*L)){
		insertFirstParent(L, data);
	}else{
		AddressParent temp = L->firstParent;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = dataBaru;
	}
}
void deleteFirstParent(Multilist *L){
	AddressParent temp = L->firstParent;

	if(!isEmpty(*L)){
		deleteAllChild(temp);
		L->firstParent = L->firstParent->next;
		free(temp);
	}
}
//void deleteAtParent(Multilist *L, int idParent){
//	AddressParent temp = L->firstParent;
//	AddressParent hapus;
//
//	if(!isEmpty(*L)){
//		if(temp->dataParent.idMentor == idParent){
//			deleteFirstParent(L);
//		}else{
//			while(temp->next != NULL){
//				if(temp->next->dataParent.idMentor == idParent){
//					hapus = temp->next;
//					temp->next = temp->next->next;
//
//					deleteAllChild(hapus);
//					free(hapus);
//					hapus = NULL;
//					break;
//				}
//				temp = temp->next;
//			}
//		}
//	}
//}
void deleteLastParent(Multilist *L){
	AddressParent temp = L->firstParent;

	if(!isEmpty(*L)){
		if(temp->next == NULL){
			deleteFirstParent(L);
		}else{
			while(temp->next->next != NULL){
				temp = temp->next;
			}
			deleteAllChild(temp->next);
			free(temp->next);
			temp->next = NULL;
		}
	}
}
void deleteAllChild(AddressParent parent){
	AddressChild temp;

	while(haveChild(parent)){
		temp = parent->firstChild;
		parent->firstChild = parent->firstChild->next;
		free(temp);
	}
}
void printParent(AddressParent parent){
	printf("\n\t=== Data Dokter ===");
	printf("\n\t[+] Nama Dokter		: %s", parent->dataParent.namaDokter);
	printf("\n\t[+] Status 		: %s", parent->dataParent.status);
	printf("\n\t[+] Spesialisasi  	: %s", parent->dataParent.spesialisasi);
	printf("\n\t--------------------------------------\n");
}
void printAllParent(Multilist L){
	AddressParent temp = L.firstParent;

	while(temp != NULL){
		printParent(temp);
		printf("\n");
		temp = temp->next;
	}
}
void printAll(Multilist L){
	AddressParent temp = L.firstParent;

	while(temp != NULL){
		if(!haveChild(temp)){
			printParent(temp);
			printf("\n\t\tDokter ini tidak memiliki Pasien[!]");
		}else{
			printParent(temp);
			printAllChild(temp);
			printf("\n");
		}
		temp = temp->next;
	}
}
int countParent(Multilist L){
	AddressParent temp = L.firstParent;
	int count = 0;
	
	while(temp != NULL){
		count++;
		temp = temp->next;
	}
	
	return count;
}
void visualisasiData(Multilist L){
	int i,j;
	AddressParent temp = L.firstParent;
	AddressChild tempChild = temp->firstChild;
	char lineH = 205, lineV = 186, lineLU = 201, lineLD = 200;
	char lineRU = 187, lineRD = 188;
	char garis= 196, panah = 175;
	int tempSpasi, tempSpasiChild, totalSpasi;
	
	while(temp != NULL){
		if(haveChild(temp)){
			tempChild = temp->firstChild;
			tempSpasi = strlen(temp->dataParent.namaDokter);
			printf("\t\n");
			// Bagian Atas Kotak
			printf("%c", lineLU);
			for(i=0; i<tempSpasi+2; i++){
				printf("%c", lineH);
			}
			printf("%c", lineRU);
			while(tempChild != NULL){
				// Bagian Atas Child
				totalSpasi = strlen(temp->dataParent.namaDokter)+3;
				tempSpasiChild = strlen(tempChild->dataChild.namaPasien);
				for(i=0; i<8; i++){
					printf(" ");
				}
				printf("%c", lineLU);
				for(i=0; i<tempSpasiChild+2; i++){
					printf("%c", lineH);
				}
				printf("%c", lineRU);
				tempChild = tempChild->next;
			}
			tempChild = temp->firstChild;
			// Bagian tengah Kotak
			printf("\n%c %s %c", lineV, temp->dataParent.namaDokter, lineV);
			printf(" %c%c%c%c%c%c ", garis, garis, garis, garis, garis, panah);
			while(tempChild != NULL){
				printf("%c %s %c", lineV, tempChild->dataChild.namaPasien, lineV);
				if(tempChild->next == NULL){
					printf(" %c%c%c%c%c%c NULL", garis, garis, garis, garis, garis, panah);
				}else{
					printf(" %c%c%c%c%c%c ", garis, garis, garis, garis, garis, panah);
				}
				tempChild = tempChild->next;
			}
			// Bagian Bawah Kotak
			printf("\n%c", lineLD);
			for(i=0; i<tempSpasi+2; i++){
				printf("%c", lineH);
			}
			printf("%c", lineRD);
			tempChild = temp->firstChild;
			// Bagian Bawah Child
			while(tempChild != NULL){
				totalSpasi = strlen(temp->dataParent.namaDokter)+3;
				tempSpasiChild = strlen(tempChild->dataChild.namaPasien);
				for(i=0; i<8; i++){
					printf(" ");
				}
				printf("%c", lineLD);
				for(i=0; i<tempSpasiChild+2; i++){
					printf("%c", lineH);
				}
				printf("%c", lineRD);
				tempChild = tempChild->next;
			}
		}else{
			tempSpasi = strlen(temp->dataParent.namaDokter);
			printf("\t\n");
			// Bagian Atas Kotak
			printf("%c", lineLU);
			for(i=0; i<tempSpasi+2; i++){
				printf("%c", lineH);
			}
			printf("%c", lineRU);
			// Bagian Isi
			printf("\n%c %s %c", lineV, temp->dataParent.namaDokter, lineV);
			printf(" %c%c%c%c%c%c NULL", garis, garis, garis, garis, garis, panah);
			// Bagian Bawahnya
			printf("\n%c", lineLD);
			for(i=0; i<tempSpasi+2; i++){
				printf("%c", lineH);
			}
			printf("%c", lineRD);
		}
		temp = temp->next;
	}
}