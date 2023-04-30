#include "reduction.hpp"

#include <assert.h>

// Les quatre premiers parametres sont les entrees de la fonction. Ils
// decrivent une instance du sac a dos decisionnel. Les deux derniers
// parametres sont les sorties de la fonction. Ils decrivent une
// instance du probleme d'ordonnancement.
void reduction(const std::vector<unsigned int>& poids,   // Parametre d'entree
	       const std::vector<unsigned int>& valeurs, // Parametre d'entree
	       unsigned int W,                           // Parametre d'entree
	       unsigned int V,                           // Parametre d'entree
	       std::vector<Tache>& taches,               // Parametre de sortie
	       unsigned int& P) {                        // Parametre de sortie
  assert(poids.size() == valeurs.size());

  // Remplacez ces deux lignes de code par votre algorithme
  P = 42;
  taches = std::vector<Tache>();
}
