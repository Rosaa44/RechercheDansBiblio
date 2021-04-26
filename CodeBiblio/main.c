#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "biblio.h"
#include "parser.h"

void menu(){
	printf("Menu:\n");
	printf("0-Sortie\n");
	printf("1-Affichage\n");
	printf("2-recherche de morceaux uniques\n");
	printf("3-recherche de morceaux avec un titre\n");
	printf("4-recherche de morceaux avec un numero\n");
	printf("5-recherche de morceaux avec un nom d'artiste\n");
	printf("Votre choix : ");
}
int main(int argc,const char **argv){
	if(argc!=3){
		printf("Erreur format\n");
		return 1;
	}
	const char *nomfic=(const char *)(argv[1]);
	int nlignes=atoi(argv[2]);
	printf("Lecture :\n");
	Biblio *biblio=charge_n_entrees(nomfic,nlignes);
	Biblio *Bunique;
	int ch;
	char * titre=malloc(sizeof(char)*200);
	char * artiste=malloc(sizeof(char)*200);
	long int numero;
	clock_t t1;
	clock_t t2;
	CellMorceau * m;
	do{
		menu();
		int lus=scanf("%d",&ch);
		if(lus==0){
			ch=0;
		}
		switch(ch){
			case 1:
				printf("Affichage\n");	
				affiche(biblio);
				break;
			case 2:
				Bunique=uniques(biblio);
				affiche(Bunique);
				libere_biblio(Bunique);
				break;
			case 3:
				printf("entrez le titre : \n");
				scanf("%s",titre);
				t1=clock();												 m=rechercheParTitre(biblio,titre);
				if(m){
					afficheMorceau(m);
				}

				t2=clock();
				printf("temps de calcul : %f\n",difftime(t2,t1)/CLOCKS_PER_SEC);

				break;
			case 4:
				printf("entrez le numero : \n");
				scanf("%ld",&numero);
				t1=clock();
				m=rechercheParNum(biblio,numero);
				if(m){
					afficheMorceau(m);
				}
				t2=clock();
				printf("temps de calcul : %f\n",difftime(t2,t1)/CLOCKS_PER_SEC);
				break;
			case 5:
				printf("entrez le nom de l'artiste : \n");
				scanf("%s",artiste);
				t1=clock();							
				Bunique=extraireMorceauxDe(biblio,artiste);
				t2=clock();
				printf("temps de calcul : %f\n",difftime(t2,t1)/CLOCKS_PER_SEC);
				affiche(Bunique);
				libere_biblio(Bunique);				
				break;
			default:
				ch=0;
				break;
		}
	} while(ch!=0);
	libere_biblio(biblio);
	printf("Fin\n");

	return 0;
}	

