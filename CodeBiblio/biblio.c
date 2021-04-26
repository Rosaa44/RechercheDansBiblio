#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#include "parser.h"

Biblio *charge_n_entrees(const char *nomfichier, int n){
	Biblio * res=nouvelle_biblio();
	int num;
	char * titre=malloc(sizeof(char)*200);
	char * auteur=malloc(sizeof(char)*200);
	int taille;
	int taille2;
	printf("%s\n",nomfichier);	
	FILE *f=fopen(nomfichier,"r");	
	while(n){
		n--;
		parse_int(f,&num);
		parse_char(f,'\t');
		parse_string(f,&titre,&taille,'\t');
		parse_char(f,'\t');
		parse_string(f,&auteur,&taille2,'\n');
		parse_char(f,'\n');
		insere(res,num,titre,auteur);
	}
	return res;	
}
