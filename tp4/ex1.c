#include <stdio.h>
#include <math.h>

double Racine_Carree(double n, double epsilon) {
    double a = 1.0;
    double b = n;
    double m;

    while ((b - a) > epsilon) {
        m = (a + b) / 2.0;
        if (m * m < n) {
            a = m;
        } else {
            b = m;
        }
    }

    return (a + b) / 2.0;
}


int recherche_dicho(int *tab, int n, int elt) {
	int g = 0;
	int d = n;

	while(g <= d) {
		int milieu = (g+d)/2;

		if(*(tab+milieu) == elt) {
			d = milieu-1;
		} else if(*(tab+milieu) > elt) {
			d = milieu -1;
		} else {
			g = milieu+1;
		}
	}
	return (g+d)/2;
}


int puissance_modulaire(int g, int e, int n) {
	if(e==1) return g%n;
	if(e%2==0) return puissance_modulaire(g*g%n,e/2,n);
	else return g*puissance_modulaire(g*g%n,(e-1)/2,n);
}

int puissance_modulaire_2(int g, int e, int n) {
	if(e==1) return g%n;
	if(e==2) return g*g%n;
	if(e%2==0) return puissance_modulaire_2(pow(g,e/2),2,n)%n;
	else return g*puissance_modulaire_2(pow(g,(e-1)/2),2,n)%n;
}


void tab_neg(int tab[], int taille) {
	int i,j = 0;

	for(i=0; i<taille; i++) {
		if(tab[i] <0) {
			int temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			j++;
		}
	}
}


int trouver_pic(int tab[], int taille) {
    int g = 0;
    int d = taille - 1;

    while (g <= d) {
        int mid = (g + d) / 2;

        // Cas où mid est un pic
        if ((mid == 0 || tab[mid] >= tab[mid - 1]) &&
            (mid == taille - 1 || tab[mid] >= tab[mid + 1])) {
            return mid;
        }

        // Si la pente monte à gauche, il y a un pic à gauche
        if (mid > 0 && tab[mid - 1] > tab[mid]) {
            d = mid - 1;
        }
        // Sinon, il y a un pic à droite
        else {
            g = mid + 1;
        }
    }

    // Théoriquement, ce point n'est jamais atteint car un pic est toujours garanti
    return -1;
}


// Fonction de partition de Lomuto
int partition(int tab[], int g, int d) {
    int pivot = tab[d];  // Choix du pivotvot (dans cet exemple, le dernier élément)
    int i = (g - 1);  // Index du plus petit élément

    for (int j = g; j <= d - 1; j++) {
        // Si l'élément actuel est plus petit ou égal au pivotvot
        if (tab[j] <= pivot) {
            // Incrémente l'index du plus petit élément
            i++;
            // Échange l'élément actuel avec l'élément à l'index du plus petit élément
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }

    // Échange le pivotvot avec l'élément à l'index suivant du plus petit élément
    int temp = tab[i + 1];
    tab[i + 1] = tab[d];
    tab[d] = temp;
    
    // Retourne l'index du pivot
    return (i + 1);
}

// Fonction principale pour trier un tableau en utilisant la partition de Lomuto
void quickSort(int tab[], int g, int d) {
    if (g < d) {
        // Effectue la partition
        int pivot = partition(tab, g, d);

        // Trie les éléments avant et après la partition
        quickSort(tab, g, pivot - 1);
        quickSort(tab, pivot + 1, d);
    }
}



