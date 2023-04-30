#include "cargaison.hpp"
#include "transport.hpp"

#include <assert.h>
#include <iostream>
#include <string>

// Complexite: O(nb_villes^5)
void transformer_pour_regner(unsigned int nb_villes,
			     std::vector<Cargaison> cargaisons,
			     std::vector<Cargaison>& solution) {
  // On recherche deux cargaisons (i -- q1 --> j) et (j -- q2 --> k) et on la
  // remplace par les cargaisons (i -- q3 --> k), (i -- (q1 - q3) --> j) (j -- (q2 - q3) --> k)
  // ou q3 = min(q1, q2).

  std::vector<std::vector<int> > bilan(nb_villes, std::vector<int>(nb_villes, 0));
  for (std::vector<Cargaison>::const_iterator i = cargaisons.begin();
       i != cargaisons.end(); i++) {
    bilan[i->expediteur()][i->destinataire()] += i->quantite();
  }

  bool changement;
  // Cette boucle peut itérer O(nb_villes^2) fois en pire cas. Chaque
  // fois, au moins un element de la matrice bilan est mis a
  // zero. Dans le cas moyen, elle iterera bien moins souvent.
  do {
    changement = false;
    for (unsigned int i = 0; i < nb_villes; i++) {
      for (unsigned int j = 0; j < nb_villes; j++) {
	if (i != j && bilan[i][j] > 0) {
	  for (unsigned int k = 0; k < nb_villes; k++) {
	    if (j != k && bilan[j][k] > 0) {
	      int quantite = std::min(bilan[i][j], bilan[j][k]);
	      bilan[i][j] -= quantite;
	      bilan[j][k] -= quantite;
	      bilan[i][k] += quantite;
	      changement = true;
	      assert(bilan[i][j] >= 0);
	      assert(bilan[j][k] >= 0);
	      assert(bilan[i][k] >= 0);
	    }
	  }
	}
      }
    }
  }
  while(changement);
  
  std::vector<Cargaison> sortie;
  for (unsigned int i = 0; i < nb_villes; i++) {
    for (unsigned int j = 0; j < nb_villes; j++) {
      if (i != j && bilan[i][j] > 0)
	sortie.push_back(Cargaison(i, j, bilan[i][j]));
    }
  }
  solution.swap(sortie);
}

// Complexite: O(1)
bool cargaison_valide(unsigned int nb_villes, const Cargaison& cargaison) {
  if (cargaison.destinataire() >= nb_villes) {
    std::cout << "La cargaison " << cargaison
	      << " est invalide car la ville "
	      << cargaison.destinataire() << " n'existe pas" << std::endl;
    return false;
  }
  if (cargaison.expediteur() >= nb_villes) {
    std::cout << "La cargaison " << cargaison
	      << " est invalide car la ville "
	      << cargaison.expediteur() << " n'existe pas" << std::endl;
    return false;
  }
  return true;
}

// Complexite: O(n + p + q) ou n est le nombre de villes et p et q les
// dimensions des vecteurs
bool solution_valide(unsigned int nb_villes,
		     const std::vector<Cargaison>& cargaisons_originales,
		     const std::vector<Cargaison>& cargaisons_optimisees) {
  std::vector<int> bilan(nb_villes, 0);
  for (std::vector<Cargaison>::const_iterator i = cargaisons_originales.begin();
       i != cargaisons_originales.end(); i++) {
    if (!cargaison_valide(nb_villes, *i))
      return false;
    bilan[i->expediteur()] -= i->quantite();
    bilan[i->destinataire()] += i->quantite();
  }
  for (std::vector<Cargaison>::const_iterator i = cargaisons_optimisees.begin();
       i != cargaisons_optimisees.end(); i++) {
    if (!cargaison_valide(nb_villes, *i))
      return false;
    bilan[i->expediteur()] += i->quantite();
    bilan[i->destinataire()] -= i->quantite();
  }
  for (unsigned int i = 0; i < nb_villes; i++) {
    if (bilan[i] < 0) {
      std::cout << "La ville " << i << " recoit " << -bilan[i] << " en trop." << std::endl;
      return false;
    }
    if (bilan[i] > 0) {
      std::cout << "La ville " << i << " envoit " << bilan[i] << " en trop." << std::endl;
      return false;
    }
  }
  return true;
}

// Complexite: O(n) ou n est le nombre de cargaisons
unsigned int quantite_totale(const std::vector<Cargaison>& cargaisons) {
  unsigned int total = 0;
  for (std::vector<Cargaison>::const_iterator i = cargaisons.begin();
       i != cargaisons.end(); i++)
    total += i->quantite();
  return total;
}

// Complexite: O(n) ou n est le nombre de cargaisons
void imprime_cargaisons(const std::vector<Cargaison>& cargaisons) {
  for (std::vector<Cargaison>::const_iterator i = cargaisons.begin();
       i != cargaisons.end(); i++) {
    std::cout << *i << " ";
  }
}

bool test_generique(const std::string& nom_du_test,
		    unsigned int nb_villes,
		    const std::vector<Cargaison>& cargaisons,
		    unsigned int score = 1) {
  std::vector<Cargaison> solution_vorace;
  transport(nb_villes, cargaisons, solution_vorace);
  bool resultat = solution_valide(nb_villes, cargaisons, solution_vorace);

  std::vector<Cargaison> solution_transformer_pour_regner;
  transformer_pour_regner(nb_villes, cargaisons, solution_transformer_pour_regner);
  assert(solution_valide(nb_villes, cargaisons, solution_transformer_pour_regner));

  unsigned int quantite_totale_vorace = quantite_totale(solution_vorace);
  unsigned int quantite_totale_transformer = quantite_totale(solution_transformer_pour_regner);
  assert(!resultat || (quantite_totale_transformer <= quantite_totale_vorace));

  if (quantite_totale_transformer < quantite_totale_vorace) {
    std::cout << "La quantite transportee n'est pas optimale." << std::endl;
    resultat = false;
  }

  if (resultat) {
    if (score > 0) {
      std::cout << "+1 Le test " << nom_du_test << " a passe." << std::endl;
    }
  } else {
    std::cout << "+0 Le test " << nom_du_test << " a echoue." << std::endl;
    std::cout << "  Solution obtenue: ";
    imprime_cargaisons(solution_vorace);
    std::cout << std::endl << "  Solution attendue: ";
    imprime_cargaisons(solution_transformer_pour_regner);
    std::cout << std::endl;
  }
  return resultat;
}

void test_simple() {
  const unsigned nb_villes = 3;
  const unsigned nb_cargaisons = 2;
  Cargaison cargaisons[nb_cargaisons] = {
    Cargaison(0, 1, 10),
    Cargaison(1, 2, 20)};

  test_generique("simple", nb_villes,
		 std::vector<Cargaison>(cargaisons, cargaisons + nb_cargaisons));
}

void test_quatre_villes() {
  const unsigned nb_villes = 4;
  const unsigned nb_cargaisons = 6;
  Cargaison cargaisons[nb_cargaisons] = {
    Cargaison(0, 1, 10),
    Cargaison(1, 2, 7),
    Cargaison(2, 3, 4),
    Cargaison(3, 0, 12),
    Cargaison(0, 2, 3),
    Cargaison(1, 3, 6)};
  test_generique("quatre villes", nb_villes,
		 std::vector<Cargaison>(cargaisons, cargaisons + nb_cargaisons));
}

void test_rien_ne_bouge(unsigned int nb_villes) {
  std::vector<Cargaison> cargaisons;
  for (unsigned int i = 0; i < nb_villes; i++) {
    for (unsigned int j = 0; j < nb_villes; j++) {
      if (i != j) {
	cargaisons.push_back(Cargaison(i, j, 1000));
      }
    }
  }
  test_generique("rien ne bouge", nb_villes, cargaisons);
}

void test_chaine(unsigned int nb_villes) {
  std::vector<Cargaison> cargaisons;
  for (unsigned int i  = 1; i < nb_villes; i++) {
    cargaisons.push_back(Cargaison(i - 1, i , 10));
  }
  test_generique("chaine", nb_villes, cargaisons);
}

void test_aleatoire(unsigned int nb_villes,
		    unsigned int nb_tests,
		    unsigned int germe) {
  std::srand(germe);
  double score = 0.0;
  for (unsigned int instance = 0; instance < nb_tests; instance++) {
    std::vector<Cargaison> cargaisons;
    for (int i = 0; i < nb_villes; i++) {
      for (int j = 0; j < nb_villes; j++) {
	if (i != j) {
	  cargaisons.push_back(Cargaison(i, j, std::rand() % 1000));
	}
      }
    }
    char tampon[100];
    snprintf(tampon, sizeof(tampon), "Test statistiques #%d", instance);
    if (test_generique(tampon, nb_villes, cargaisons, 0))
      score += 1.0;
  }
  std::cout << "+" << score / nb_tests << " Les tests randomises ont passe." << std::endl;
}

int main(void) {
  test_simple();
  test_quatre_villes();
  test_rien_ne_bouge(100);
  test_chaine(100);
  test_aleatoire(100, 500, 42);
  return 0;
}
