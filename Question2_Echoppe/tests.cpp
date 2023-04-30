#include "echoppe.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>

// Retourne l'effet cumulatif des items
// Theta(n)
unsigned int effet(const std::vector<Item>& items) {
  unsigned int effet = 0;
  for (std::vector<Item>::const_iterator i = items.begin(); i != items.end(); i++)
    effet += i->effet();
  return effet;
}

// Affiche les items d'une solution de meme que leur effet
// et l'utilisation des pieds et des mains.
// Theta(n)
void afficheSolution(const std::vector<Item>& items) {
  unsigned int utilisation_mains = 0;
  unsigned int utilisation_pieds = 0;
  unsigned int prix = 0;
  for (std::vector<Item>::const_iterator i = items.begin(); i != items.end(); i++) {
    std::cout << i->nom() << ", ";
    utilisation_mains += i->utilisation_mains();
    utilisation_pieds += i->utilisation_pieds();
    prix += i->prix();
  }
  std::cout << "(effet = " << effet(items) <<
    ", prix = " << prix <<
    ", mains = " << utilisation_mains <<
    ", pieds = " << utilisation_pieds << ")" << std::endl;
}

// Retourne vrai si solution_a_tester est une solution valide a l'instance (items, budget, nb_pieds, n_mains).
// Une solution valide n'a pas a etre optimale.
// Theta(n log n)
bool solutionValide(std::vector<Item> items,
		    unsigned int budget,
		    unsigned int nb_mains,
		    unsigned int nb_pieds,
		    std::vector<Item> solution_a_tester) {
  std::sort(items.begin(), items.end()); // Theta(n log n)
  std::sort(solution_a_tester.begin(), solution_a_tester.end()); // Theta(n log n)

  if (!std::includes(items.begin(), items.end(),
		     solution_a_tester.begin(), solution_a_tester.end())) // O(n)
    return false;		// Les items de la solution ne sont pas ceux donnees en entree

  // Theta(n)
  unsigned int mains_utilisees = 0;
  unsigned int pieds_utilises = 0;
  unsigned int prix = 0;
  for (std::vector<Item>::const_iterator i = solution_a_tester.begin(); i != solution_a_tester.end(); i++) {
    mains_utilisees += i->utilisation_mains();
    pieds_utilises += i->utilisation_pieds();
    prix += i->prix();
  }
  return (mains_utilisees <= nb_mains) && (pieds_utilises <= nb_pieds) && (prix <= budget);
}

// Retourne une solution optimale au probleme.
// Theta(2^n * n log n) ou n est le nombre d'items
std::vector<Item> forceBrute(const std::vector<Item>& items, unsigned int budget, unsigned int nb_mains, unsigned int nb_pieds) {
  assert(items.size() <= 31); // Cette fonction ne fonctionne que pour de petites instances

  std::vector<Item> meilleure_solution;
  // Cette bouble s'execute 2^n fois.
  for (unsigned int mask = 0; mask < (1 << items.size()); mask++) {
    std::vector<Item> solution_courante;
    // Theta(n)
    for (unsigned int j = 0; j < items.size(); j++) {
      if ((1 << j) & mask) {
	solution_courante.push_back(items[j]);
      }
    }
    // Theta(n log n)
    if (solutionValide(items, budget, nb_mains, nb_pieds, solution_courante) &&
	(effet(solution_courante) > effet(meilleure_solution))) {
      meilleure_solution.swap(solution_courante);
    }
  }
  assert(solutionValide(items, budget, nb_mains, nb_pieds, meilleure_solution));
  return meilleure_solution;
}

// Execute un test
// Theta(2^n * n log n)
bool test(const std::string& nom_du_test, const std::vector<Item>& items, unsigned int budget, unsigned int nb_mains, unsigned int nb_pieds) {
  std::vector<Item> solution;
  magasine(items, budget, nb_mains, nb_pieds, solution);
  std::vector<Item> solution_optimale = forceBrute(items, budget, nb_mains, nb_pieds);

  if (!solutionValide(items, budget, nb_mains, nb_pieds, solution) || (effet(solution) != effet(solution_optimale))) {
      std::cout << "+0 point: Le test \"" << nom_du_test << "\" a echoue" << std::endl;
      std::cout << "  Solution attendue: ";
      afficheSolution(solution_optimale);
      std::cout << "  Solution obtenue:  ";
      afficheSolution(solution);
    } else {
      std::cout << "+1 point: Le test \"" << nom_du_test << "\" a passe" << std::endl;
      std::cout << "  Solution: ";
      afficheSolution(solution);
    }

  return false;
}

bool testSansMainNiPied() {
  Item items[4] = {
    //   Nom                   Effet Prix NbMains NbPieds
    Item("collier",            12,   2,   0,      0),
    Item("lunettes",           10,   1,   0,      0),
    Item("monocle",            20,   3,   0,      0),
    Item("chapeau",            15,   2,   0,      0)}; 
  return test("sans main ni pied",
	      std::vector<Item>(items, items + 4),
	      5, 		// Budget
	      0,		// Nombre de mains
	      0);		// Nombre de pieds
}

bool testSansPied() {
  Item items[5] = {
    //   Nom                   Effet Prix NbMains NbPieds
    Item("casque",              5,   10,   0,      0),
    Item("epee",               25,   15,   1,      0),
    Item("Excalibur",          35,   25,   2,      0),
    Item("bouclier",            7,    7,   1,      0),
    Item("chale mite",         10,   10,   0,      0)
  }; 
  return test("sans pied",
	      std::vector<Item>(items, items + 5),
	      40, 		// Budget
	      2,		// Nombre de mains
	      0);		// Nombre de pieds
}

bool testHarryPotter() {
  Item items[9] = {
    //   Nom                   Effet Prix NbMains NbPieds
    Item("Choixpeau",          	   1,   15,   0,   0),
    Item("Epee de Gryffondor", 	  30,   40,   2,   0),
    Item("Deluminateur",           3,   10,   1,   0),
    Item("Balai Nimbus 2000",  	  15,    5,   1,   2),
    Item("Baguette de Sureau", 	  40,   30,   1,   0),
    Item("Chaussettes de Dobby",   2,    1,   0,   2),
    Item("Pierre de resurrection", 5,   15,   1,   0),
    Item("Cape d'invisibilite",   15,   30,   0,   0),
    Item("Hippogriffe",           10,    9,   0,   2)};
  return test("Harry Potter",
	      std::vector<Item>(items, items + 9),
	      65, 		// Budget
	      2,		// Nombre de mains
	      2);		// Nombre de pieds
}

bool testSeigneurDesAnneaux() {
  Item items[11] = {
    //   Nom               	      Effet  Prix NbDoigts NbPieds
    Item("Dard",           	      	 10,   5,       5,     0),
    Item("Arc elfique",    	         15,  20,       7,     0),
    Item("Aigle Gwaihir",  	          5,  10,       0,     2),
    Item("Cotte de mailles en mithril",  10,  15,       0,     0),
    Item("Sylvebarbe",                    7,   7,       0,     2),
    Item("Anneau unique",  	         60,  50,       1,     0),
    Item("Neuf anneaux des hommes",      30,  40,       9,     0),
    Item("Trois anneaux des elfes",      40,  30,       3,     0),
    Item("Septs anneaux des nains",      20,  30,       7,     0),
    Item("Gripoil",                       3,  10,       0,     2),
    Item("Baton de Gandalf",             20,  20,       5,     0)};
    
  return test("Seigneur des anneaux",
	      std::vector<Item>(items, items + 11),
	      70, 		// Budget
	      10,		// Nombre de doigts
	      2);		// Nombre de pieds
}

bool testMusique() {
  Item items[19] = {
    //   Nom               	      Effet  Prix  NbMains NbPieds
    Item("Guitare",        	      	 33,   30,       2,      0),
    Item("Grelots",                       2,    5,       0,      1),
    Item("Grosse caisse",                10,   10,       0,      1),
    Item("Harmonica",                    20,   10,       1,      0),
    Item("Maraca",                       10,    7,       1,      0),
    Item("Orgue",                        40,   40,       2,      2),
    Item("Piano",                        35,   20,       2,      1),
    Item("Caisse claire",                20,   20,       1,      0),
    Item("Cymbales charleston",          12,   15,       0,      1),
    Item("Tom",                          15,   12,       1,      0),
    Item("Flute",                        30,    8,       2,      0),
    Item("Violon",                       35,   25,       2,      0),
    Item("Trompette",                    15,   17,       1,      0),
    Item("Podorythmie",                  12,    7,       0,      2),
    Item("Cajon",                        30,   18,       2,      2),
    Item("Basse aux pieds",               8,   15,       0,      2),
    Item("Accordeon",                    27,   45,       2,      0),
    Item("Clarinette",                   12,   40,       2,      0),
    Item("Ukulele",                      15,    6,       2,      0)
  };
  return test("musique",
	      std::vector<Item>(items, items + 19),
	      40, 		// Budget
	      2,		// Nombre de mains
	      2);		// Nombre de pieds
}

int main(void) {
  testSansMainNiPied();
  testSansPied();
  testHarryPotter();
  testSeigneurDesAnneaux();
  testMusique();
  return 0;
}
