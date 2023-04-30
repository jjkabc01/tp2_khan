// Vous ne devez pas modifier ce fichier.

#ifndef REDUCTION
#define REDUCTION

#include <vector>

#include "tache.hpp"

// Les quatre premiers parametres sont les entrees de la fonction. Ils
// decrivent une instance du sac a dos decisionnel. Les deux derniers
// parametres sont les sorties de la fonction. Ils decrivent une
// instance du probleme d'ordonnancement.
void reduction(const std::vector<unsigned int>& poids,
	       const std::vector<unsigned int>& valeurs,
	       unsigned int W,
	       unsigned int V,
	       std::vector<Tache>& taches,
	       unsigned int& P);

#endif
