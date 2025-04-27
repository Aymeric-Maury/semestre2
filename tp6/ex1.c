#include <stdio.h>

void permute(int * a, int * b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_LOMUTO(int n, int tab[n])
{
    int pivot = tab[n-1];
    int i = -1;

    for (int j = 0 ; j < n - 1 ; j++){
        if (tab[j] <= pivot){
			i = i + 1;
            permute(tab + i, tab + j); //   permute(&tab[i], &tab[j]);
			
		}
	}

    permute(tab + i + 1, tab + n - 1);
  
    return i + 1;
}

// k ième plus petit élément
// souvent k = n/2 donc recherche de la médiane
int mediane_dpr(int n, int tab[n], int k){
    if (n == 1) {
        return tab[0];
	}

	// partition retourne un pivot
	int pivot = partition_LOMUTO(n, tab);
   
    // le kième plus petit élément est trouvé
    if (pivot == k)
        return tab[k];
        
    // comparer un élément du tableau à tab[pivot]
    if (pivot < k) {
		// recursion à droite du pivot
		// la taille du tableau est n - pivot
		// le tableau de droite débute à tab + pivot
		// le k ième plus petit élément est le 
		// (k - pivot) ième dans le tableau de droite
		// exemple : raisonner avec n = 10, pivot = 3, k = 7
		// 3 éléments sont plus petits que le pivot 3
		// donc l'élément recherché est (7 - 3) = 4 ième dans
		// le tableau de droite
		// mediane_dpr(7, tab + 3, 4);
        return mediane_dpr(n - pivot, tab + pivot, k - pivot);
	}
	
    // recursion à gauche
    // la taille du tableau est pivot
	// le tableau est tab
	// le k ième plus petit élément est k
	// exemple : raisonner avec n = 10, pivot = 6, k = 4
	// mediane_dpr(6, tab, 4);
    return mediane_dpr(pivot, tab, k);
}



int rendu_de_monnaie1(int montant_a_rendre, int n, int systeme_monetaire[n], int caisse[n], int rendu[n]){
    int nombre_unites = 0;

	// parcours du système monétaire et de la caisse en parallèle
    for (int i = 0 ; i < n; i++){	
		// gestion de la ième unité de manière gloutonne
        while ((montant_a_rendre >= systeme_monetaire[i]) && (caisse[i] != 0)){
            nombre_unites++;
            rendu[i]++;
            caisse[i]--;
            montant_a_rendre = montant_a_rendre - systeme_monetaire[i];
           // printf("montant à rendre %d \n",   montant_a_rendre );
            nombre_unites++;
        }
    }
    
    if (montant_a_rendre == 0)
        return nombre_unites;
    
    // impossible de rendre la monnaie, on remet les unités dans la caisse
    for (int i = 0 ; i < n ; i++){
        caisse[i] += rendu[i];
        rendu[i] = 0;
    }
    
    // rendu impossible de la monnaie
    return -1;
}

int rendu_de_monnaie2(int montant_a_rendre, int n, int systeme_monetaire[n], int caisse[n], int rendu[n]){
    int nombre_unites = 0;
	int montant_rendu = 0;
	
	// parcours du système monétaire et de la caisse en parallèle
    for (int i = 0 ; i < n ; i++){
		// gestion de la ième unité de manière gloutonne
		// montant_rendu + systeme_monetaire[i] chronophage
		// pénalisant en temps d'exécution
        while ((montant_rendu + systeme_monetaire[i]) <= montant_a_rendre){
			if (caisse[i] == 0){
				break;
			}
			
			montant_rendu = montant_rendu + systeme_monetaire[i];
			//printf("montant rendu %d \n", montant_rendu);
            nombre_unites++;
            rendu[i]++;
            caisse[i]--;
        }
    }
    
    if (montant_rendu == montant_a_rendre)
        return nombre_unites;
    
    // impossible de rendre la monnaie, on remet les unités dans la caisse
    for (int i = 0 ; i < n ; i++){
        caisse[i] += rendu[i];
        rendu[i] = 0;
    }
    
    // rendu impossible de la monnaie
    return -1;
}


// First-Fit (FF) : Place chaque objet dans le premier bac dans lequel il rentre.
int first_fit(int objets[], int n, int capacite) {
    int bacs[n]; // au maximum n bacs (dans le pire des cas)
    int nb_bacs = 0; // nombre de bacs existants
	
	initTableau(bacs, n);
	
	// parcours du tableau d'objets
    for (int i = 0; i < n; i++) {
		// parcours du tableau des bacs
        int j;     
        for (j = 0; j < nb_bacs; j++) {
			// si l'objet peut rentrer dans le bac
			// alors on l'ajoute et on passe à l'objet suivant
            if (bacs[j] + objets[i] <= capacite) {
				printf("bac %d ajout objet %d\n", j, objets[i]);
                bacs[j] += objets[i];
                break;
            }
        }
        
        // Aucun bac existant ne peut contenir l’objet
        if (j == nb_bacs) { // Aucun bac existant ne peut contenir l’objet
			printf("bac %d ajout objet %d\n", nb_bacs, objets[i]);
            bacs[nb_bacs++] = objets[i];
        }
    }
    
	afficheTableau(bacs, n);
	
    return nb_bacs;
}

// Best-Fit (BF) : Place chaque objet dans le bac qui aura le moins d’espace restant 
// après ajout (mais qui reste valide).
int best_fit(int objets[], int n, int capacite) {
	int bacs[n]; // au maximum n bacs (dans le pire des cas)
    int nb_bacs = 0; // nombre de bacs existants

	initTableau(bacs, n);
	
    // parcours du tableau d'objets
    for (int i = 0; i < n; i++) {
		
        int min_espace = capacite + 1;
        int meilleur_bac = -1;
        
        // parcours du tableau des bacs
        for (int j = 0; j < nb_bacs; j++) {
            int espace_libre = capacite - bacs[j];
            if (objets[i] <= espace_libre && espace_libre < min_espace) {
                min_espace = espace_libre;
                meilleur_bac = j;
            }
        }

        if (meilleur_bac == -1) {
			printf("bac %d ajout objet %d\n", nb_bacs, objets[i]);
            bacs[nb_bacs++] = objets[i]; // nouveau bac
        } else {
			printf("bac %d ajout objet %d\n", meilleur_bac, objets[i]);
            bacs[meilleur_bac] += objets[i];
        }
    }
    
	afficheTableau(bacs, n);
	
    return nb_bacs;
}