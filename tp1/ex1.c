#include <stdio.h>

void init_zero(int taille, double tab[taille]) {
	for(int i = 0, i < taille, i++) {
		tab[i] = 0.0;
	}
}


void init_zero_point(int taille, double *tab) {
	if(taille<=0) return;

	*tab= 0.0;

	init_zero_point(taille-1, tab+1);
}


void init_n_point(int taille, double *tab, double n) {
	if(taille<=0) return;

	*tab = n;

	init_n_point(taille-1, tab+1, n);
}


void echange_2_int(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}



