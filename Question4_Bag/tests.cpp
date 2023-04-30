#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include "reduction.hpp"
#include "tache.hpp"

// Retourne la penalite d'un ordonancement
// Entree:
//   taches: Les taches du probleme d'ordonnancement
//   ordre:  Les index des taches dans l'ordre qu'elles sont executees
// Sortie:
//   la penalite de l'ordonnancement
// Complexite: Theta(n)
unsigned int penaliteSolution(const std::vector<Tache>& taches, const std::vector<unsigned int>& ordre) {
  assert(taches.size() == ordre.size());
  unsigned int temps = 0;
  unsigned int penalite = 0;
  for (unsigned int i = 0; i < ordre.size(); i++) {
    const Tache& tache = taches[ordre[i]];
    temps += tache.duree();
    if (tache.echeance() < temps) {
      penalite += tache.penalite();
    }
  }
  return penalite;
}

// Cette fonction resout le probleme a l'aide d'un algorithme de force brute
// Complexite: Theta(n * n!)
bool forceBrute(const std::vector<Tache>& taches, unsigned int P) {
  std::vector<unsigned int> ordre(taches.size());
  for (unsigned int i = 0; i < ordre.size(); i++) {
    ordre[i] = i;
  }
  do {
    if (penaliteSolution(taches, ordre) <= P) {
      return true;
    }
  } while (std::next_permutation(ordre.begin(), ordre.end()));

  return false;
}

// Cette fonction resout le probleme du sac a dos decisionnel
// Complexite: Theta(n * 2^{log_2 W})
// Cet algorithme s'execute en temps exponentiel par rapport a la taille de l'instance (en bits)
bool knapsackDecision(const std::vector<unsigned int>& poids,
		      const std::vector<unsigned int>& valeurs,
		      unsigned int W,
		      unsigned int V) {
  assert(poids.size() == valeurs.size());
  const unsigned int n = poids.size();
  std::vector<std::vector<unsigned int> > T(n + 1, std::vector<unsigned int>(W + 1));
  for (unsigned int i = 0; i <= n; i++) {
    T[i][0] = 0;
  }
  for (unsigned int j = 1; j <= W; j++) {
    T[0][j] = 0;
  }
  for (unsigned int i = 1; i <= n; i++) {
    for (unsigned int j = 1; j <= W; j++) {
      if (poids[i - 1] <= j) {
	T[i][j] = std::max(T[i - 1][j], valeurs[i - 1] + T[i - 1][j - poids[i - 1]]);
      } else {
	T[i][j] = T[i - 1][j];
      }
    }
  }
  return T[n][W] >= V;
}

bool test(const std::string& nom_du_test,
	  const std::vector<unsigned int>& poids,
	  const std::vector<unsigned int> valeurs,
	  unsigned int W,
	  unsigned int V) {
  assert(poids.size() == valeurs.size());
  std::vector<Tache> taches;
  unsigned int P;
  reduction(poids, valeurs, W, V, taches, P); // Transforme l'instance du sac a dos decisionnel en instance d'ordonnancement
  const bool solution_knapsack = knapsackDecision(poids, valeurs, W, V);
  const bool solution_ordonnancement = forceBrute(taches, P);

  if (solution_knapsack != solution_ordonnancement) {
    std::cout << "+0 point: Le test \"" << nom_du_test << "\" a echoue" << std::endl;
  } else {
    std::cout << "+1 point: Le test \"" << nom_du_test << "\" a passe" << std::endl;
  }
  std::cout << "   La reponse au probleme du sac a dos decisionnel est " << (solution_knapsack ? "oui" : "non") << std::endl;
  std::cout << "   La reponse au probleme d'ordonnancement est " << (solution_ordonnancement ? "oui" : "non") << std::endl;

  return solution_knapsack == solution_ordonnancement;
}

// Exemple tire de la page 14 du chapitre 8.
bool exempleDiapositivesOui() {
  const unsigned int nb_objets = 4;
  const unsigned int poids[nb_objets] = {2, 1, 3, 2};
  const unsigned int valeurs[nb_objets] = {12, 10, 20, 15};
  const unsigned int W = 5;
  const unsigned int V = 37;	// Il existe une solution d'au moins 37$
  return test("Exemple des diapositives (oui)",
	      std::vector<unsigned int>(poids, poids + nb_objets),
	      std::vector<unsigned int>(valeurs, valeurs + nb_objets),
	      W,
	      V);
}

// Exemple tire de la page 14 du chapitre 8.
bool exempleDiapositivesNon() {
  const unsigned int nb_objets = 4;
  const unsigned int poids[nb_objets] = {2, 1, 3, 2};
  const unsigned int valeurs[nb_objets] = {12, 10, 20, 15};
  const unsigned int W = 5;
  const unsigned int V = 38;	// Il n'existe pas de solution d'au moins 38$
  return test("Exemple des diapositives (non)",
	      std::vector<unsigned int>(poids, poids + nb_objets),
	      std::vector<unsigned int>(valeurs, valeurs + nb_objets),
	      W,
	      V);
}

bool testTrieOui() {
  const unsigned int nb_objets = 6;
  const unsigned int poids[nb_objets] = {6, 5, 4, 3, 2, 1};
  const unsigned int valeurs[nb_objets] = {1, 2, 3, 4, 5, 6};
  const unsigned int W = 5;
  const unsigned int V = 11;
  return test("Exemple trie (oui)",
	      std::vector<unsigned int>(poids, poids + nb_objets),
	      std::vector<unsigned int>(valeurs, valeurs + nb_objets),
	      W,
	      V);
}

bool testTrieNon() {
  const unsigned int nb_objets = 6;
  const unsigned int poids[nb_objets] = {6, 5, 4, 3, 2, 1};
  const unsigned int valeurs[nb_objets] = {1, 2, 3, 4, 5, 6};
  const unsigned int W = 5;
  const unsigned int V = 12;
  return test("Exemple trie (non)",
	      std::vector<unsigned int>(poids, poids + nb_objets),
	      std::vector<unsigned int>(valeurs, valeurs + nb_objets),
	      W,
	      V);
}

bool grandExemple() {
  const unsigned int nb_objets = 11;
  const unsigned int poids[nb_objets] = {4, 1, 7, 2, 9, 6, 2, 8, 3, 5, 9};
  const unsigned int valeurs[nb_objets] = {1, 7, 3, 9, 3, 2, 8, 4, 6, 2, 9};
  const unsigned int W = 15;
  const unsigned int V = 36;
  return test("Grand exemple",
	      std::vector<unsigned int>(poids, poids + nb_objets),
	      std::vector<unsigned int>(valeurs, valeurs + nb_objets),
	      W,
	      V);
}

bool testComplementaire() {
  const unsigned int nb_objets = 4;
  const unsigned int poids[nb_objets] = {4, 1, 7, 2};
  const unsigned int valeurs[nb_objets] = {2, 7, 3, 9};
  const unsigned int W = 3;
  const unsigned int V = 10000;
  return test("Grand exemple",
	      std::vector<unsigned int>(poids, poids + nb_objets),
	      std::vector<unsigned int>(valeurs, valeurs + nb_objets),
	      W,
	      V);
}


int main(void) {
  exempleDiapositivesOui();
  exempleDiapositivesNon();
  testTrieOui();
  testTrieNon();
  grandExemple();
  testComplementaire();
  return 0;
}
