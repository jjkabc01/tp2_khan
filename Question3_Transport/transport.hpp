// NE PAS MODIFIER CE FICHIER


#ifndef TRANSPORT
#define TRANSPORT

#include "cargaison.hpp"

#include <vector>

void transport(unsigned int nb_villes,
	       const std::vector<Cargaison>& cargaisons,
	       std::vector<Cargaison>& sortie);

#endif
