#include "header.h"

DataChild makeDataChild(string pasien, string keluhan, int lama, string status){
	DataChild data;
	
	strcpy(data.namaPasien, pasien);
	strcpy(data.keluhan, keluhan);
	strcpy(data.status, status);
	data.perawatan = lama;

	return data;
}
AddressChild alokasiChild(DataChild data){
	AddressChild ac;

	ac = (AddressChild) malloc(sizeof(NodeChild));
	ac->next = NULL;
	ac->dataChild = data;

	return ac;
}
void insertFirstChild(Multilist L, string dokter, DataChild data){
	AddressParent parent = findParent(L, dokter);

	if(parent != NULL){
		AddressChild dataBaru = alokasiChild(data);
		dataBaru->next = parent->firstChild;
		parent->firstChild = dataBaru;
	}
}
void insertLastChild(Multilist L, string dokter, DataChild data){
	AddressParent parent = findParent(L, dokter);

	if(parent != NULL){
		if(!haveChild(parent)){
			insertFirstChild(L, dokter, data);
		}else{
			AddressChild temp = parent->firstChild;
			AddressChild dataBaru = alokasiChild(data);

			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = dataBaru;
		}
	}
}
void deleteFirstChild(Multilist L, string dokter){
	AddressParent parent = findParent(L, dokter);

	if(parent != NULL){
		if(haveChild(parent)){
			AddressChild temp = parent->firstChild;
			parent->firstChild = parent->firstChild->next;

			free(temp);
		}
	}
}
void deleteLastChild(Multilist L, string dokter){
	AddressParent parent = findParent(L, dokter);

	if(parent != NULL){
		if(haveChild(parent)){
			if(parent->firstChild->next == NULL){
				deleteFirstChild(L, dokter);
			}else{
				AddressChild temp = parent->firstChild;
				while(temp->next->next != NULL){
					temp = temp->next;
				}

				free(temp->next);
				temp->next = NULL;
			}
		}
	}
}
void printChild(AddressChild child){
	if(child->dataChild.perawatan == 0){
		strcpy(child->dataChild.status, "Boleh Pulang");
	}
	printf("\n\t\t---> [ Data Pasien ]");
	printf("\n\t\t[-] Nama Pasien		: %s", child->dataChild.namaPasien);
	printf("\n\t\t[-] Keluhan		: %s", child->dataChild.keluhan);
	printf("\n\t\t[-] Lama Perawatan	: %d", child->dataChild.perawatan);
	printf("\n\t\t[-] Status		: %s", child->dataChild.status);
}
void printAllChild(AddressParent parent){
	AddressChild temp = parent->firstChild;

	while(temp != NULL){
		printChild(temp);
		temp = temp->next;
	}
}
void nextDay(Multilist *L, int hari){
	AddressParent tempParent = NULL;
	tempParent = L->firstParent;
	while(tempParent != NULL){
		AddressChild temp = tempParent->firstChild;
		while(temp != NULL){
			if(temp->dataChild.perawatan == 0){
				strcpy(temp->dataChild.status, "Boleh Pulang");
			}else if(temp->dataChild.perawatan != 0){
				temp->dataChild.perawatan--;
			}
			temp = temp->next;
		}
		tempParent = tempParent->next;
	}
}

