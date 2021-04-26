#include "biblio_hachage.h"
#include <stdbool.h>

Biblio *nouvelle_biblio(void) 
{
	Biblio * res=(Biblio *)(malloc(sizeof(Biblio)));
	res->nE=0;
	res->m=TAILLE_TABLE;
	res->T=(CellMorceau **)(malloc(sizeof(CellMorceau *)*TAILLE_TABLE));
	return res;
}
void libere_morceau(CellMorceau *c){
	CellMorceau *tmp;
	while(c){
		tmp=c->suiv;
		free(c->titre);
		free(c->artiste);
		free(c);
		c=tmp;
	}
}

unsigned int fonction_cle(const char *artiste){
	int res=0;
	int i;
	while(artiste[i]!='\0'){
		res+=artiste[i];
		i++;
	}
	return res;
}

unsigned int fonction_hachage(unsigned int cle, int m){
	float knuth=(sqrt(5)-1)/2;
	int n=(int)(cle*knuth);
	return (int)(m*(cle*knuth-n));
}


		
void libere_tableau(CellMorceau **T,int m){
	int i;
	for(i=0;i<m;i++){
		if(T[i]){
			libere_morceau(T[i]);
		}
	}
}
void libere_biblio(Biblio *B){

	libere_tableau(B->T,B->m);
	free(B);
    
}

CellMorceau * creerMorceaux(int num, char *titre, char *artiste){ 
	CellMorceau * moc= (CellMorceau *)(malloc(sizeof(CellMorceau)));
	moc->num=num;
	moc->titre=strdup(titre);
	moc->artiste=strdup(artiste);
	return moc;
}


void insere(Biblio *B, int num, char *titre, char *artiste){
	CellMorceau **T2=B->T;
	CellMorceau *cell=creerMorceaux(num,titre,artiste);
	printf("ok\n");
	unsigned int cle=fonction_cle(artiste);
	unsigned int indice=fonction_hachage(cle,B->m); 
	CellMorceau * K=T2[indice];
	T2[indice]= cell;
	cell->suiv = K;

}


void afficheMorceau(CellMorceau *cell)
{
	printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
	CellMorceau * tmp;
	int i;
	for(i=0;i<B->m;i++){  
		tmp=(B->T)[i];
		while(tmp){
			afficheMorceau(tmp);
			tmp=tmp->suiv;
		}
	} 
}



Biblio *uniques (Biblio *B)
{
	Biblio *B2=nouvelle_biblio();
	B2->nE=B->nE;
	B2->m=B->m;
	
	int i;
	CellMorceau **tab=B->T;
	
	for(i=0;i<B->m;i++){
		CellMorceau * s=tab[i];
			while(s){
				CellMorceau * v=tab[i];
				while(v){
					if(s->num !=v->num){
						if((strcmp(s->titre,v->titre)==0) && (strcmp(s->artiste,v->artiste)==0)){
							break;
						}
						v=v->suiv;
					}
					else{v=v->suiv;}
					
				}
				insere(B2, s->num, s->titre, s->artiste);
				s=s->suiv;
			}
	}
	return B2;
    
}


CellMorceau * rechercheParNum(Biblio *B, int num)
{
	CellMorceau * tmp;
	int i;
	for(i=0;i<B->m;i++){  
		tmp=(B->T)[i];
		while(tmp){
			if(tmp->num==num){
				return tmp;
			}
			tmp=tmp->suiv;
		}
	} 
	return NULL;
	
}


CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	CellMorceau * tmp;
	int i;
	for(i=0;i<B->m;i++){  
		tmp=(B->T)[i];
		while(tmp){
			if(strcmp(tmp->titre,titre)==0){
				return tmp;
			}
			tmp=tmp->suiv;
		}
	} 
	return NULL;

}


int *tous_numeros(Biblio *B){
	int *res=(int *)(malloc(sizeof(int)*B->m));
	int i;
	int j=0;
	CellMorceau * tmp;
	for(i=0;i<B->m;i++){
		tmp=(B->T)[i];
		while(tmp){
			res[j]=tmp->num;
			j++;
		}
	}
	return res;
}
bool est_dans_liste(int num,CellMorceau ** res,int m){
	int i;
	for(i=0;i<m;i++){
		CellMorceau *s=res[i];
		while(s){
			if(num==s->num){
				return true;
			}
			s=s->suiv;
		}
	}
	return false;
}
void insereSansNum(Biblio *B, char *titre, char *artiste)
{

	int num=0;
	while(est_dans_liste(num,B->T,B->m)){
		num++;
	}
	insere(B,num,titre,artiste);
}


int supprimeMorceau(Biblio *B, int num)
{
	CellMorceau * tmp;
	CellMorceau * tmp2;
	int i;
	for(i=0;i<B->m;i++){  
		tmp=(B->T)[i];
		tmp2=NULL;
		while(tmp){
			if(tmp->num==num){
				if(tmp->suiv==NULL){
					free(tmp->titre);
					free(tmp->artiste);
					free(tmp);
				}
				else if(tmp2==NULL){
					tmp2=tmp->suiv;
					free(tmp->titre);
					free(tmp->artiste);
					free(tmp);
					(B->T)[i]=tmp2;
				}
				else{
					tmp2->suiv=tmp->suiv;
					free(tmp->titre);
					free(tmp->artiste);
					free(tmp);
				}
				return 0;
			}
		}
	}
	return 1;
}
					
					



Biblio *extraireMorceauxDe(Biblio *B, char * artiste){
	Biblio *new = nouvelle_biblio();
	CellMorceau **t = B->T;
	int indice=fonction_hachage(fonction_cle(artiste),B->m);
	(new->T)[indice]=(B->T)[indice];
	CellMorceau * tmp=(new->T)[indice];
	while(tmp){
		(new->nE)+=1;
		tmp=tmp->suiv;
	}
	return new;
}



























