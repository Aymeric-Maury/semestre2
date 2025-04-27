#include <stdio.h>

unsigned int fibonacci_rec_simple(unsigned int N) {
	if(N==0) return 0;
	if(N<=2) return 1;

	return fibonacci_rec_simple(N-1) + fibonacci_rec_simple(N-2);
}


unsigned int fibonacci_iter(unsigned int N) {
	if(N==0) return 0;
	if(N==1) return 1;

	unsigned int a,b = 0;

	for(int i = 2; i <= N; i++) {
		unsigned int temp = a+b;
		a = b;
		b = temp;
	}
	return b;
}


void inverser_tab_rec(int *tab, int taille, int indice) {
	int L = taille - 1 - indice;
	if(L <= indice) return;

	int temp = *(tab+indice);
	*(tab+indice) = *(tab+L);
	*(tab+L) = temp;

	inverser_tab_rec(tab, taille, indice+1);
}

void afficher_tab(int *tab, int taille) {
	for(int i = 0; i < taille; i++) {
		printf("%d",*(tab+i));
	}
	printf("\n");
}


int main() {
	int tableau[] = {0,1,2,3,4,5,6,7,8,9};

	afficher_tab(tableau, 10);

	inverser_tab_rec(tableau, 10, 3);

	afficher_tab(tableau, 10);

	return 0;
}
