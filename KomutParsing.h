#ifndef KOMUTPARSING_H
#define KOMUTPARSING_H

#include<stdlib.h>
#include<stdio.h>

// satır sonunda enter('\n') var ise sil
char* EnterSil(char* satir){
  int sayac=0;
  while(satir[sayac]!='\0')
  	sayac++;
  satir[sayac-1]='\0';
  return satir;
}

// gelen komutun başındaki ve sonundaki boşlukları siler
char* BoslukSil(char* komut){
	char* yeni_komut = malloc(20);
	int index=0;
	for(int j=0;komut[j]!='\0';j++){
	    if(komut[j]!=' ')
	      yeni_komut[index++]=komut[j];
	}
	yeni_komut[index]='\0';
	return yeni_komut;
}

// her komut argümanını dolaşıp boşlukları temizletir.
char** BoslukTemizle(char** komutlar){

	for(int i=0;komutlar[i]!=NULL;i++){
		komutlar[i] = BoslukSil(komutlar[i]);
	}
	return komutlar;
}

// // gelen girdiyi boşluğa göre parçalar
char** StringParcala(char* a_str)
{
	char** komutlar = malloc(1000 * sizeof(char *));
	int index=0;
	char *token = strtok(a_str, " ");
	    while (token != NULL)
	    {
	    	komutlar[index++]=token;
		token = strtok(NULL, " ");
	    }
 return komutlar;
}


// aldığı stringin kelimelerini string dizisine atarak döndürür
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a" // çeşitli boşluklara göre böler
char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

// String uzunluğunu döndürür
int KomutUzunlukGetir(char* komut){
	int i;
	for(i=0;komut[i]!='\0';i++);
	return i;
	
}

// Komut uzunluğunu ve adet kontrolü yapılır.
int BoyutKontrol(char** komutlar){
	/*
	for(int j=0;komutlar[j]!=NULL;j++){
	 int x = KomutUzunlukGetir(komutlar[j]);
	   printf("%s->%d\n",komutlar[j],x);
	}	
	
	*/
	int x = KomutUzunlukGetir(komutlar[0]); // ilk komutun uzunluğu 80 den fazla olamaz
	if(x>80){
	   printf("Hata : Komut uzunluğu :80 'den fazla olamaz\n");
	   return -1;
	}
	
	int j;
	for(j=0;komutlar[j]!=NULL;j++);
	if(j>10){
	   printf("Hata : Komut argumanlari 10'dan fazla olamaz\n");
	   return -1;
	}	
	
  return 0;
}

// kullanıcıdan girdi al
char* GirdiAl(){
  char *line=NULL;
  ssize_t bufsize = 0; // have getline allocate a buffer for us
  getline(&line,&bufsize,stdin);
  return line;
}

#endif
