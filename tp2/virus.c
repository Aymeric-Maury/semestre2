#include <stdio.h>

void init_zero(int *tab, int hauteur, int largeur) {
	for(int i=0; i<hauteur; i++) {
		for(int j=0; j<largeur; j++) {
			*(tab+i*largeur+j) = 0;
		}
	}
}

void afficher_tab(int *tab, int hauteur, int largeur) {
	for(int i=0; i<hauteur; i++) {
		for(int j=0; j<largeur; j++) {
			printf("%d ",*(tab+i*largeur+j));
		}
		printf("\n");
	}
	printf("\n\n");
}


void propagation(int *tab, int hauteur, int largeur, int *prop, int virulence, int x, int y) {
	if(x<0 || x>=hauteur || y<0 || y>=largeur) return;
	if(*(tab+x*largeur+y)>virulence) return;
	if(*(prop+x*largeur+y) == -1) return;
	
	*(prop+x*largeur+y)= -1;

	propagation(tab,hauteur,largeur,prop,virulence,x-1,y);
	propagation(tab,hauteur,largeur,prop,virulence,x+1,y);
	propagation(tab,hauteur,largeur,prop,virulence,x,y-1);
	propagation(tab,hauteur,largeur,prop,virulence,x,y+1);
}


int main() {
	int hauteur = 0;
	int largeur = 0;

	scanf("%d",&hauteur);
	scanf("%d",&largeur);

	int foule[hauteur][largeur];

	for(int i=0; i<hauteur; i++) {
		for(int j=0; j<largeur; j++) {
			scanf("%1d",&foule[i][j]);
		}
	}
	int x = 0;
	int y = 0;
	int virulence = 0;
	
	scanf("%d",&x);
	scanf("%d",&y);
	scanf("%d",&virulence);

	int prop[hauteur][largeur];
	init_zero(&prop[0][0],hauteur,largeur);

	printf("Taille = %d x %d\n",hauteur,largeur);
	afficher_tab(&foule[0][0],hauteur,largeur);
	printf("Foyer = (%dx%d)\n",x,y);
	printf("Virulence = %d\n", virulence);
	printf("\nPropagation du virus :\n");
	propagation(&foule[0][0],hauteur,largeur,&prop[0][0],virulence,x,y);
	afficher_tab(&prop[0][0],hauteur,largeur);

	return 0;
}
