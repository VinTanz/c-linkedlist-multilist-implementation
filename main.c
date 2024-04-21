#include "header.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
	[UGD 8 Multilist - ISD]
	Nama    : Kevin Philips Tanamas
	NPM     : 220711789
	Kelas   : A
*/
int main(int argc, char *argv[]) {
	int menu, lama, konfirmasi, hari = 0;
	string dokter, pasien, status, spesial, keluhan;
	bool cekBonus = false;
	
	Multilist L;
	AddressParent adrDokter;
	AddressChild adrPasien;
	
	createEmpty(&L);
	do{
		system("cls");
		system("color 1E");
		printf("\n\t\t===== UGD MULTILIST A =====");
		if(cekBonus == true){
			printf("\n\t--> Day %d", hari);
		}
		printf("\n\t[1]. Input Dokter");
		printf("\n\t[2]. Show Dokter");
		printf("\n\t[3]. Input Pasien");
		printf("\n\t[4]. Show Pasien Dokter Tertentu");
		printf("\n\t[5]. Show All");
		printf("\n\t[6]. Delete Pasien");
		printf("\n\n\t[BONUS]");
		printf("\n\t[7]. Next Day");
		printf("\n\t[8]. Tugas");
		printf("\n\t[0]. Exit...");
		printf("\n\t>>> ");scanf("%d", &menu);
		
		switch(menu){
			case 1:
				printf("\n\tInput Nama Dokter : ");fflush(stdin);gets(dokter);
				while(strlen(dokter)==0){
					printf("\n\t\tNama Dokter tidak boleh Kosong[!]");
					printf("\n\tInput Nama Dokter : ");fflush(stdin);gets(dokter);
				}
				printf("\n\tStatus Dokter [Senior | Junior] : ");fflush(stdin);gets(status);
				while(strcmpi(status, "Senior")!=0 && strcmpi(status, "Junior")!=0){
					printf("\n\t\tStatus harus Senior atau Junior[!]");
					printf("\n\tStatus Dokter [Senior | Junior] : ");fflush(stdin);gets(status);
				}
				printf("\n\tSpesialisasi Dokter : ");fflush(stdin);gets(spesial);
				while(strlen(spesial)==0 || strcmpi(spesial, "-")==0){
					printf("\n\t\tSpesialisasi tidak boleh kosong[!]");
					printf("\n\tSpesialisasi Dokter : ");fflush(stdin);gets(spesial);
				}
				if(strcmpi(status, "Senior")==0){
					insertFirstParent(&L, makeDataParent(dokter, status, spesial));
					printf("\n\t\tBerhasil Input First Dokter[+]");
				}else if(strcmpi(status, "Junior")==0){
					insertLastParent(&L, makeDataParent(dokter, status, spesial));
					printf("\n\t\tBerhasil Input Last Dokter[+]");
				}
				break;
			case 2:
				if(!isEmpty(L)){
					printAllParent(L);
				}else{
					printf("\n\t\tList masih kosong[!]");
				}
				break;
			case 3: // Input Pasien
				if(!isEmpty(L)){
					printf("\n\tMasukan Nama Dokter : ");fflush(stdin);gets(dokter);
					adrDokter = findParent(L, dokter);

					if(adrDokter != NULL){
						printParent(adrDokter);
						printf("\n\tInput Nama Pasien : ");fflush(stdin);gets(pasien);
						while(strlen(pasien)==0 || strcmpi(pasien, "-")==0){
							printf("\n\t\tNama Pasien tidak boleh kosong[!]");
							printf("\n\tInput Nama Pasien : ");fflush(stdin);gets(pasien);
						}
						printf("\n\tInput Keluhan Pasien : ");fflush(stdin);gets(keluhan);
						while(strlen(keluhan)==0 || strcmpi(keluhan, "-")==0){
							printf("\n\t\tInput Keluhan tidak boleh kosong[!]");
							printf("\n\tKeluhan Pasien : ");fflush(stdin);gets(keluhan);
						}
						printf("\n\tInput Lama Perawatan : ");scanf("%d", &lama);
						while(lama < 1){
							printf("\n\t\tLama Perawatan Minimal 1 Hari[!]");
							printf("\n\tInput Lama Perawatan : ");scanf("%d", &lama);
						}
						insertLastChild(L, dokter, makeDataChild(pasien, keluhan, lama, "Dalam Perawatan"));
						printf("\n\t\tBerhasil Input Pasien[-]");
					}else{
						printf("\n\t\tNama Dokter tidak ditemukan[!]");
					}
				}else{
					printf("\n\t\tList masih kosong[!]");
				}
				break;
			case 4:
				if(!isEmpty(L)){
					printf("\n\tMasukan Nama Dokter : ");fflush(stdin);gets(dokter);
					adrDokter = findParent(L, dokter);
					if(adrDokter != NULL){
						if(!haveChild(adrDokter)){
							printParent(adrDokter);
							printf("\n\t\tDokter ini tidak memiliki Pasien[!]");
						}else{
							printParent(adrDokter);
							printAllChild(adrDokter);
						}
					}else{
						printf("\n\t\tNama Dokter tidak ditemukan[!]");
					}
				}else{
					printf("\n\t\tList masih kosong[!]");
				}
				break;
			case 5:
				if(!isEmpty(L)){
					printAll(L);
				}else{
					printf("\n\t\tList masih kosong[!]");
				}
				break;
			case 6: // Delete Pasien
				if(cekBonus == false){
					if(!isEmpty(L)){
						printf("\n\tMasukan Nama Dokter : ");fflush(stdin);gets(dokter);
						adrDokter = findParent(L, dokter);
						if(haveChild(adrDokter)){
							if(adrDokter != NULL){
								printParent(adrDokter);
								printf("\n\t--> Hapus Pasien");
								printf("\n\t[1]. First");
								printf("\n\t[2]. Last");
								printf("\n\t>>> ");scanf("%d", &konfirmasi);
								if(konfirmasi == 1){
									deleteFirstChild(L, dokter);
									printf("\n\t\tBerhasil Menghapus First Pasien[!]");
								}else if(konfirmasi == 2){
									deleteLastChild(L, dokter);
									printf("\n\t\tBerhasil Menghapus Last Pasien[!]");
								}
							}else{
								printf("\n\t\tNama Dokter tidak ditemukan[!]");
							}
						}else{
							printf("\n\t\tDokter tidak memiliki Pasien[!]");
						}
					}else{
						printf("\n\t\tList masih kosong[!]");
					}
				}else{
					if(!isEmpty(L)){
						printf("\n\tMasukan Nama Dokter : ");fflush(stdin);gets(dokter);
						adrDokter = findParent(L, dokter);
						if(haveChild(adrDokter)){
							if(adrDokter != NULL){
								printParent(adrDokter);
								printf("\n\t--> Hapus Pasien");
								printf("\n\t[1]. First");
								printf("\n\t[2]. Last");
								printf("\n\t>>> ");scanf("%d", &konfirmasi);
								if(konfirmasi == 1){
									adrPasien = adrDokter->firstChild;
									if(adrPasien->dataChild.perawatan == 0){
										deleteFirstChild(L, dokter);
										printf("\n\t\tBerhasil Menghapus First Pasien[!]");
									}else{
										printf("\n\t\tPasien Masih dalam Perawatan[!]");
									}
								}else if(konfirmasi == 2){
									adrPasien = adrDokter->firstChild;
									while(adrPasien->next != NULL){
										adrPasien = adrPasien->next;
									}
									if(adrPasien->dataChild.perawatan == 0){
										deleteLastChild(L, dokter);
										printf("\n\t\tBerhasil Menghapus Last Pasien[!]");
									}else{
										printf("\n\t\tPasien Masih dalam Perawatan[!]");
									}
								}
							}else{
								printf("\n\t\tNama Dokter tidak ditemukan[!]");
							}
						}else{
							printf("\n\t\tDokter tidak memiliki Pasien[!]");
						}
					}else{
						printf("\n\t\tList masih kosong[!]");
					}
				}
				break;
			case 7: // Bonus Next Day
				if(!isEmpty(L)){
					nextDay(&L, hari);
					cekBonus = true;
					hari++;
					printf("\n\t\tMenuju Hari Selanjutnya[!]");
				}else{
					printf("\n\t\tList masih kosong[!]");
				}
				break;
			case 8:
				if(!isEmpty(L)){
					printf("\n\t==== Visualisasi Multilist ====\n");
					visualisasiData(L);
				}else{
					printf("\n\t\tList masih kosong[!]");
				}
				break;
			case 0:
				printf("\n\t\tKevin Philips Tanamas - A - 220711789");
				break;
			default:
				printf("\n\t\tMenu tidak ada[!]");
				break;
		}getch();

	}while(menu != 0);
	
	
	return 0;
}
