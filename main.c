#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SATIR 20
#define SUTUN 50

struct hayvan {
    int satir;
    int sutun;
    int kalem;
    int yon;
};

void ayristir(int *k1, int *k2, char *kmt);
void gez(struct hayvan *t, char o[SATIR][SUTUN], int k1, int k2);
void yaz(char o[SATIR][SUTUN]);

int main()
{
    int komut1, komut2;
    char oda[SATIR][SUTUN];

    for(int i=0; i<SATIR; i++) {
        for(int j=0; j<SUTUN; j++) {
            oda[i][j] = ' ';
        }
    }

    char komut[20];
    FILE *kaynak;
    struct hayvan kaplumbaga = {0, 0, 1, 3};//hayvanı tanımlama. bizim örneğimizde kaplumbağa

    kaynak = fopen("kaynak.txt", "r");//kaynak dosyası arama
    if (kaynak == NULL) { // Kaynak dosya kontrol
        printf("Dosya bulunamadi! Lutfen dosya adini ve uzantisini kontrol et.\n");
        return 1;
    }

    while (fscanf(kaynak, "%s", komut) == 1) {
        ayristir(&komut1, &komut2, komut);
        gez(&kaplumbaga, oda, komut1, komut2);
    }

    oda[kaplumbaga.satir][kaplumbaga.sutun] = '*';

    yaz(oda);

    fclose(kaynak);
    return 0;
}

void ayristir(int *k1, int *k2, char *kmt) {
    //Kaynak dosyadaki virgül var mı yok mu diye bakar ve ayrıştırır ona göre fonksiyonlar çalışır
    char *virgul = strchr(kmt, ',');

    if (virgul != NULL) {
        *virgul = '\0';
        *k1 = atoi(kmt); //ASCII to Integer: atoi
        *k2 = atoi(virgul + 1);
    } else {
        *k1 = atoi(kmt);
        *k2 = 0;
    }
}

void gez(struct hayvan *t, char o[SATIR][SUTUN], int k1, int k2) {
    switch (k1) {
        case 1: t->kalem = 1; break; // Kalem aşağı
        case 2: t->kalem = 2; break; // Kalem yukarı
        case 3: t->yon = 3; break;   // Sağ
        case 4: t->yon = 4; break;   // Sol
        case 5: t->yon = 5; break;   // Yukarı
        case 6: t->yon = 6; break;   // Aşağı
        case 7: // İlerleme
            for (int i = 0; i < k2; i++) {
                if (t->yon == 3) t->sutun++;
                if (t->yon == 4) t->sutun--;
                if (t->yon == 5) t->satir--;
                if (t->yon == 6) t->satir++;
                if (t->satir < 0) t->satir = 0;
                if (t->sutun < 0) t->sutun = 0;
                if (t->satir >= SATIR) t->satir = SATIR - 1;
                if (t->sutun >= SUTUN) t->sutun = SUTUN - 1;
                if (t->kalem == 1) {
                    if (t->yon == 3 || t->yon == 4)//sağa sola giderken tire şekli yazdırır
                        o[t->satir][t->sutun] = '-';
                    else if (t->yon == 5 || t->yon == 6)//aşağı yukarı giderken boru şekli yazdırır
                        o[t->satir][t->sutun] = '|';
                }
            }
            break;
    }
}

void yaz(char o[SATIR][SUTUN]) {
    FILE *cizimDosya = fopen("cizim.txt", "w");//Yazma kısmı dosya varsa içine yazar yoksa yenisini oluşturur
    if (cizimDosya == NULL) {
        printf("Cizim dosyasi olusturulamadi!\n");
        return;
    }

    for (int i = 0; i < SATIR; i++) {
        for (int j = 0; j < SUTUN; j++) {
            putchar(o[i][j]);// hem konsola,
            fputc(o[i][j], cizimDosya);//hem dosyaya yazdırır
        }
        putchar('\n');
        fputc('\n', cizimDosya);
    }

    fclose(cizimDosya);
    printf("\nIslem tamamlandi.\n");
}
