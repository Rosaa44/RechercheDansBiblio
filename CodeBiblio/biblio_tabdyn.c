#include <stdlib.h>
#include "biblio_tabdyn.h"
#include <stdbool.h>

Biblio *nouvelle_biblio(void) 
{
	Biblio *res=(Biblio *)(malloc(sizeof(Biblio)));
	res->nE=0;
	res->capacite=10;
	res->T=(CellMorceau *)(malloc(sizeof(CellMorceau)*10));  
	return res;
}

void libere_biblio(Biblio *B)
{

	free(B->T);
	free(B);
}

CellMorceau * creerMorceau(int num, char *titre, char *artiste){
	CellMorceau * res=(CellMorceau *)(malloc(sizeof(CellMorceau)));
	res->num=num;
	res->titre=strdup(titre);
	res->artiste=strdup(artiste);
	return res;
}
void insere(Biblio *B, int num, char *titre, char *artiste)
{
	if(B->nE<B->capacite){
		(B->T)[B->nE]=*creerMorceau(num,titre,artiste);
		(B->nE)++;
		return;
	}
	B->capacite*=2;	    
	B->T=realloc(B->T,sizeof(CellMorceau)*B->capacite);
	(B->T)[B->nE]=*creerMorceau(num,titre,artiste);
	(B->nE)++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("*T* %8d * %-32.32s * %-32.32s *T*\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
	CellMorceau *T=B->T;
	if(B==NULL){
		printf("\n");
		return;
	}
	printf("nE : %d\n",B->nE);
	printf("capacite : %d\n",B->capacite);
	int i;
	printf("Tableau : \n");
	for(i=0;i<B->nE;i++){
		afficheMorceau(T+i);
	}    
}

bool morceauxEgaux(CellMorceau c1,CellMorceau c2){
	return (c1.num==c2.num)&&(strcmp(c1.titre,c2.titre)==0)
	&&(strcmp(c1.artiste,c2.artiste)==0);
}

Biblio *uniques (Biblio *B)
{
	Biblio *res=nouvelle_biblio();
	int i,j,k;
	for(i=0;i<B->nE;i++){
		k=1;
		for(j=0;j<res->nE;j++){
			if (morceauxEgaux((B->T)[i],(res->T)[j])){
				k=0;	
			}
		}
		if(k==1){
			insere(res, (B->T)[i].num, (B->T)[i].titre, (B->T)[i].artiste);
		}	
	}
	return res;
}


CellMorceau * rechercheParNum(Biblio *B, int num)
{
	CellMorceau *T=B->T;
	int i;
	for(i=0;i<B->nE;i++){	
		if(T[i].num==num){
			return (T+i);
		}
	}
	return NULL;
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	CellMorceau *T=B->T;
	int i;
	for(i=0;i<B->nE;i++){	
		if(strcmp(T[i].titre,titre)==0){
			return (T+i);
		}
	}
	return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	Biblio *res=nouvelle_biblio();
	CellMorceau *T=B->T;
	int i;
	for(i=0;i<B->nE;i++){	
		if(strcmp(T[i].artiste,artiste)==0){
			insere(res,T[i].num,T[i].titre,T[i].artiste);
		}
	}
	return res;
}
bool numDifferent(Biblio *B,int num){
	int i;
	CellMorceau * T2=B->T;
	for(i=0;i<B->nE;i++){
		if(T2[i].num==num){
			return false;
		}
	}
	return true;
}
void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	int i=0;
	while(numDifferent(B,i)){
		i++;
	}
	insere(B,i,titre,artiste);	

}


int supprimeMorceau(Biblio *B, int num)
{
	CellMorceau * T2=B->T;
	while(T2){
		if((*T2).num==num){
			free(T2);
			return 0;
		}
		(T2)++;
	}
	
	return 1;
				
}




































