#ifndef ECHOPPE
#define ECHOPPE

#include <vector>

#include "item.hpp"

void magasine(const std::vector<Item>& items,
	      unsigned int budget,
	      unsigned int nb_mains,
	      unsigned int nb_pieds,
	      std::vector<Item>& item_achetes);

#endif
