#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"
#include <stdbool.h>

typedef struct CellMorceau {
	struct CellMorceau *suiv; 
	int num;
	char* titre;
	char* artiste;
}CellMorceau;

struct Biblio {
	CellMorceau *L;
	int nE;
};



Biblio *nouvelle_biblio(){
	Biblio * res=(Biblio *)malloc(sizeof(Biblio));
	res->L=NULL;
	res->nE=0;
	return res;
}

void insere(Biblio *B, int num, char *titre, char *artiste){
	CellMorceau * mor =(CellMorceau *)(malloc(sizeof(CellMorceau)));
	mor->num=num;
	mor->titre=strdup(titre);
	mor->artiste=strdup(artiste);
	mor->suiv=B->L;
	B->L=mor;
	B->nE+=1;
}
void libere_biblio(Biblio *B){
	CellMorceau * tmp=B->L;
	CellMorceau * tmp2;
	while(tmp){
		tmp2=tmp->suiv;
		free(tmp->titre);
		free(tmp->artiste);
		free(tmp);
		tmp=tmp2;
	}
	free(B);
}
void afficheMorceau(CellMorceau * tmp){
		printf("num: %d titre: %s artiste(s): %s\n",tmp->num,tmp->titre,tmp->artiste);
	
}
void affiche(Biblio *B){
	if(B!=NULL){
		CellMorceau * tmp=B->L;
		printf("Nombre de morceaux : %d\n",B->nE);
		while(tmp){
			afficheMorceau(tmp);
			tmp=tmp->suiv;
		}
	}
}
CellMorceau * rechercheParNum(Biblio *b,int num){

	CellMorceau * tmp=b->L;
	while(tmp){
		if(tmp->num==num){
			return tmp;
		}
		tmp=tmp->suiv;
	}
	return NULL;
}
CellMorceau * rechercheParTitre(Biblio *b,char * titre){

	CellMorceau * tmp=b->L;
	while(tmp){	
		if(strcmp(tmp->titre,titre)==0){
			return tmp;
		}
		tmp=tmp->suiv;
	}
	return NULL;
}
CellMorceau * rechercheMArtiste(Biblio * b,char * artiste){
	CellMorceau * res=NULL;
	CellMorceau * tmp=b->L;
	CellMorceau * mor;
	while(tmp){
		if(strcmp(tmp->artiste,artiste)==0){
			mor =(CellMorceau *)malloc(sizeof(CellMorceau));
			mor->num=tmp->num;
			mor->titre=strdup(tmp->titre);
			mor->artiste=strdup(tmp->artiste);
			mor->suiv=res;
			res=mor;
		}
	}
	return res;
}
void insererMorceau(Biblio *b,CellMorceau * m){
	insere(b, m->num, m->titre, m->artiste);
}
void supprimeMorceauvoid(Biblio * B,CellMorceau *m){
	B->nE--;
	if(!m->suiv){
		free(m->titre);
		free(m->artiste);
		free(m);
		
	}
	if(B->L==m){
		B->L=m->suiv;
		free(m->titre);
		free(m->artiste);
		free(m);
		
		
	}
	CellMorceau *tmp=B->L;
	while(tmp->suiv!=m && tmp){
		tmp=tmp->suiv;
	}
	if(tmp){
	tmp->suiv=m->suiv;
	free(m->titre);
	free(m->artiste);
	free(m);
	}
}


Biblio *uniques(Biblio *B){
	Biblio *B2=nouvelle_biblio();
	CellMorceau *tab=B->L;
	while(tab){
		CellMorceau *bis=B->L;
		while(bis){
			if(tab->num != bis->num){
				if(strcmp(tab->titre,bis->titre)==0 && strcmp(tab->artiste,bis->artiste)==0){
					break;
				}
				bis=bis->suiv;
			}
			else{
				bis=bis->suiv;
			}
		}
		insererMorceau(B2,tab);
		tab=tab->suiv;
		
	}
	
	return B2;
}





int * tous_numeros(Biblio * B){
	CellMorceau * tmp=B->L;
	int *liste=(int *)(malloc(sizeof(int)*B->nE));
	int i;
	for(i=0;i<B->nE;i++){
		liste[i]=tmp->num;
		tmp=tmp->suiv;
	}
	return liste;
}

bool est_dans_liste(int a,int * liste,int n){
	int i;
	for(i=0;i<n;i++){
		if(liste[i]==a){
			return true;
		}
	}
	return false;
}
void insereSansNum(Biblio *B, char *titre, char *artiste){
	int * liste=tous_numeros(B);
	int num=0;
	while(est_dans_liste(num,liste,B->nE)){
		num++;
	}
	insere(B,num,titre,artiste);
}





Biblio *extraireMorceauxDe(Biblio *B, char * artiste){
	Biblio *new = nouvelle_biblio();
	CellMorceau *t = B->L;
	while(t){
		if (!strcmp(t->artiste,artiste)){
			insere(new,t->num,t->titre,t->artiste);
		}
		t=t->suiv;
	}
	return new;
}

	
