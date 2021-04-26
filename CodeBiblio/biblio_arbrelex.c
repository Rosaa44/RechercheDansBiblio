
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "biblio_arbrelex.h"

Biblio *nouvelle_biblio(void) 
{
	Biblio *res=malloc(sizeof(Biblio));
	res->A=NULL;
	res->nE=0;
	return res;
}
void libere_Morceaux(CellMorceau *m){
	if(m==NULL){
		return;
	}
	libere_Morceaux(m->suiv);
	free(m->titre);
	free(m->artiste);
	free(m);
}
void libere_Noeud(Noeud *n){
	if(n==NULL){
		return;
	}
	libere_Noeud(n->liste_car);
	libere_Noeud(n->car_suiv);
	libere_Morceaux(n->liste_morceaux);
	free(n);
}
void libere_biblio(Biblio *B)
{
	libere_Noeud(B->A);
	free(B);	    
}
void afficheMorceau(CellMorceau *cell)
{
	printf("|A| %8d | %-32.32s | %-32.32s |A|\n", cell->num, cell->titre, cell->artiste);
}
void afficheNoeud(Noeud * n){
	CellMorceau * liste;
	while(n){
		liste=n->liste_morceaux;
		if(liste!=NULL){
			while(liste){
				afficheMorceau(liste);
				liste=liste->suiv;
			}
		}
		if(n->liste_car){
			afficheNoeud(n->liste_car);
		}
		n=n->car_suiv;
	}
}
void affiche(Biblio *B)
{
	afficheNoeud(B->A);
    
}

Noeud * creerNoeud(char car,CellMorceau *lm){
	Noeud * res=(Noeud *)(malloc(sizeof(Noeud)));
	res->liste_car=NULL;
	res->car_suiv=NULL;
	res->liste_morceaux=lm;
	res->car=car;
	return res;
}
Noeud * annexe_insere(char * artiste,Noeud * tmp,CellMorceau *m,int i){
	CellMorceau * tmp2;
	if(artiste[i+1]=='\0'){
		if(tmp==NULL){
			tmp=creerNoeud(artiste[i],m);
		}
		else if(artiste[i]==tmp->car){
			tmp2=tmp->liste_morceaux;
			m->suiv=tmp2;
			tmp->liste_morceaux=m;

		}
		else{
			tmp->liste_car=annexe_insere(artiste,tmp->liste_car,m,i);
		}
		return tmp;
	}
	if(tmp==NULL){
		tmp=creerNoeud(artiste[i],NULL);
		tmp->car_suiv=annexe_insere(artiste,tmp->car_suiv,m,i+1);
	}
	else if(tmp->car==artiste[i]){
		tmp->car_suiv=annexe_insere(artiste,tmp->car_suiv,m,i+1);
	}
	else {
		tmp->liste_car=annexe_insere(artiste,tmp->liste_car,m,i+1);
	}
	return tmp;
}
void insere(Biblio *B,int num,char *titre,char *artiste){
	CellMorceau * m=(CellMorceau *)(malloc(sizeof(CellMorceau)));
	m->num=num;
	m->titre=strdup(titre);
	m->artiste=strdup(artiste);
	Noeud * tmp=B->A;
	(B->nE)++;
	if(artiste[0]=='\0'){
		return;
	}
	B->A=annexe_insere(m->artiste,tmp,m,0);
	
}

CellMorceau * annexeRechercheNum(Noeud * BA,int num){
	CellMorceau * liste;
	while(BA){
		if(BA->liste_car){
			liste=annexeRechercheNum(BA->liste_car,num);
		 	if(liste!=NULL ){
				return liste;
			}
		}
		if(BA->liste_morceaux){
			liste=BA->liste_morceaux;
			while(liste){
				if(liste->num==num){
					return liste;
				}
				liste=liste->suiv;
			}
		}
		BA=BA->car_suiv;
	}
	return NULL;
}
CellMorceau * rechercheParNum(Biblio *b,int num){
	return annexeRechercheNum(b->A,num);
}

		
CellMorceau * annexeRechercheTitre(Noeud * BA,char * titre){
	CellMorceau * liste;
	CellMorceau *res;
	while(BA){
		if(BA->liste_morceaux){
			res=BA->liste_morceaux;
			while(res){
				 if(strcmp(res->titre,titre)==0){
					 return res;
				 }
				res=res->suiv;
			}
		}
		if(BA->liste_car){
			liste=annexeRechercheTitre(BA->liste_car,titre);
			if(liste!=NULL){
				return liste;
			}
		}
		BA=BA->car_suiv;
	}
	return NULL;
}
CellMorceau * rechercheParTitre(Biblio *B, char * titre){
	return annexeRechercheTitre(B->A,titre);
}	
CellMorceau * rechercheArtiste(Biblio *B, char * artiste){
	int i=0;
	 Noeud *cour=B->A;
	 while((cour!=NULL) && (artiste[i+1]!='\0')){
	 	
	 	if(cour->car== artiste[i]){
	 		cour=cour->car_suiv;
	 		i++;
	 	}
	 	else{
	 		cour=cour->liste_car;
	 	}
	 }
	if(cour==NULL){
		return NULL;
	}
	return cour->liste_morceaux;
}
Biblio *extraireMorceauxDe(Biblio *B, char * artiste){
	Biblio *res=nouvelle_biblio();
	int nE=0;
	Noeud *tmp;
	Noeud * tmp2;

	CellMorceau * listeM=rechercheArtiste(B,artiste);
	CellMorceau *l=listeM;
	while(l){
		nE++;
		l=l->suiv;
	}
	int i=0;	
	tmp=creerNoeud(artiste[i],NULL);
	tmp2=tmp;
	while(artiste[i+1]!='\0'){
		tmp->car_suiv=creerNoeud(artiste[i],NULL);
		tmp=tmp->car_suiv;
		i++;
	}
	tmp->car_suiv=creerNoeud(artiste[i],listeM);
	res->A=tmp2;
	res->nE=nE;
	return res;
	
}
int annexeSupprimeMorceau(Noeud *n,int num){
	while(n && n->liste_morceaux==NULL){
		if(n->liste_car){
			if(annexeSupprimeMorceau(n->liste_car,num)==0){
				return 0;
			}
		}
		n=n->car_suiv;
	}
	if(n==NULL){
		return 1;
	}
	CellMorceau * l=n->liste_morceaux;
	CellMorceau * tmp=NULL;
	while(l){
		if(l->num==num){
			if(tmp==NULL){
				tmp=l->suiv;
				n->liste_morceaux=tmp;				
				free(l->artiste);
				free(l->titre);
				free(l);
			}
			else{
				tmp->suiv=l->suiv;
				free(l->artiste);
				free(l->titre);
				free(l);
			}
			return 0;
		}
		tmp=l;
		l=l->suiv;

	}
	if(n->liste_car){
			if(annexeSupprimeMorceau(n->liste_car,num)==0){
				return 0;
			}
	}
	return 1;
}
int supprimeMorceau(Biblio * B,int num){
	return annexeSupprimeMorceau(B->A,num);
}
int morEgaux(CellMorceau * c1,CellMorceau * c2){
	if(!strcmp(c1->artiste,c2->artiste) && !strcmp(c1->titre,c2->titre)){
		return 1;
	}
	return 0;
}
CellMorceau * copieMorceau(CellMorceau * tmp){
	CellMorceau * mor =(CellMorceau *)malloc(sizeof(CellMorceau));
	mor->num=tmp->num;
	mor->titre=strdup(tmp->titre);
	mor->artiste=strdup(tmp->artiste);
	mor->suiv=NULL;
	return mor;
}

CellMorceau * copieUniques(CellMorceau * c1,CellMorceau * c2,int *num){
	CellMorceau * res=NULL;
	CellMorceau *tmp;
	CellMorceau *tmp2;
	int k;
	if(c2==NULL){
		return c1;
	}
	while(c2){
		k=1;
		while(c1){
			if(morEgaux(c1,c2)){
				k=0;
			}
			c1=c1->suiv;
		}
		if(k==1){
			tmp2=res;
			tmp=copieMorceau(c1);
			tmp->suiv=tmp2;
			res=tmp;
			(*num)++;
		}
		c2=c2->suiv;

	}
	return res;
}
Noeud * copieNoeud(Noeud *n){
	Noeud *res=malloc(sizeof(Noeud));
	res->car=n->car;
	res->liste_car=NULL;
	res->car_suiv=NULL;
	return res;
	
}
Noeud * annexeUniques(Biblio *B,Noeud * BA,int *num){
	Noeud * res=copieNoeud(BA);
	while(BA->car_suiv){

		if(BA->liste_car){
			res->liste_car=annexeUniques(B,BA->liste_car,num);
		}
		BA=BA->car_suiv;
		res->car_suiv=copieNoeud(BA);
		res=res->car_suiv;
	}
	
	if(BA->liste_morceaux==NULL){
		return res;
	}
	CellMorceau * liste=rechercheArtiste(B,BA->liste_morceaux->artiste);
	res->liste_morceaux=copieUniques(BA->liste_morceaux,liste,num);	
	return res;
}
Biblio * uniques(Biblio * B){
	int * num=0;
	Biblio * res=malloc(sizeof(Biblio));
	res->A=annexeUniques(B,B->A,num);
	res->nE=*num;
	return res;
}
void rec_tous_num(Noeud * BA,int liste[],int * i){
	while(BA->car_suiv){
		if(BA->liste_car){
			rec_tous_num(BA->liste_car,liste,i);	
		}
		BA=BA->car_suiv;
	}
	CellMorceau * tmp=BA->liste_morceaux;
	while(tmp){
		liste[*i]=tmp->num;
		(*i)++;
		tmp=tmp->suiv;
	}
}

int * tous_numeros(Biblio * B){
	int *liste=(int *)malloc(sizeof(int));
	int * i=0;
	rec_tous_num(B->A,liste,i);
	return liste;
}
int est_dans_liste(int a,int * liste,int n){
	int i;
	for(i=0;i<n;i++){
		if(liste[i]==a){
			return 1;
		}
	}
	return 0;
}
void insereSansNum(Biblio *B, char *titre, char *artiste){
	int * liste=tous_numeros(B);
	int num=0;
	while(est_dans_liste(num,liste,B->nE)){
		num++;
	}
	insere(B,num,titre,artiste);
}






















