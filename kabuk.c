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