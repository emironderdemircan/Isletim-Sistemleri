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

// String uzunluğunu döndürür
int KomutUzunlukGetir(char* komut){
	int i;
	for(i=0;komut[i]!='\0';i++);
	return i;
	
}