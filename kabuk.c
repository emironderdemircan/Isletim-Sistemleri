#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <wait.h> 
#include "KomutParsing.h"

// Renk kodları
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// oluşan son 5 prosesi tutan dizi
pid_t prosesler[5];
int adet=0; // proses sayısı
int indeks=0; // son eklenen prosesin indeksi

// komut çalıştırma
int KomutIcrasi(char **args,int index){
  pid_t pid, wpid;
  int status;

  pid = fork(); // yavru proses oluştur
  if (pid == 0) {
    // çocuk proses
    if (execvp(args[index], args) == -1) {
      perror("lsh:execvp");
    }

    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // fork() hatası
    perror("lsh");
  } else {
    // Parent proses
 
    do {
    	if(indeks==5) // indeks 5 e ulaştıysa baştan eklemeye devam et
    	  indeks=0;
    	prosesler[indeks++] = pid; // ekle
    	if(adet!=5) // 5 adet proses yoksa adet artır
    	  adet++;
      wpid = waitpid(pid, &status, WUNTRACED); // çocuk prosesin tamamlanmasını bekle
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

// Built-in komutlar var ise seç icra et yoksa gönder
void KomutSec(char** komutlar){
  if(strcmp(komutlar[0],"exit")==0){ // exit ise
    printf("exit\n");
    exit(0);
  }
  else if(strcmp(komutlar[0],"cd")==0){ // cd ise
    int sonuc = chdir(komutlar[1]);
    if(sonuc)
    	perror("chdir");
  }
   else if(strcmp(komutlar[0],"showpid")==0){// showpid ise
    for(int i=0;i<adet;i++)
    	printf("%d\n",prosesler[i]);
  }
  else{
  	KomutIcrasi(komutlar,0); // icraya gönder
  }
}

int main(){

   char* satir = NULL; // okunan girdi
   char** komut_dizisi = NULL;// komut dizisi
   char* calisma_dizini=NULL; // anlık çalışma dizini
   
   while(1){
   calisma_dizini = (char *) malloc (1024);
   if (getcwd(calisma_dizini, 1024) != NULL)
   	printf("%s%s  ",KYEL,calisma_dizini);
   	
     printf("%s",KCYN);
     printf("sau >");     	// renk ayarı
     printf("%s",KNRM);
     
     satir = GirdiAl();
     
     satir = EnterSil(satir);// kullancıcı komutu girince sonda enter oluyor bunu sil
    // komut_dizisi = StringParcala(satir);// boşluğa parçala
     komut_dizisi = lsh_split_line(satir);
     // komut uzunluk ve argüman sayısı kontrolü
     int sonuc = BoyutKontrol(komut_dizisi);
     if(sonuc==0) // aykırı durum yoksa icraya gönder
     	KomutSec(komut_dizisi);     	
     	
     free(komut_dizisi); 	// verileri temizle
     free(satir);
     free(calisma_dizini);	// satir değişkeni malloc ile oluşturulmadığı için silmeye gerek yok.
   }
   return 0;
}
