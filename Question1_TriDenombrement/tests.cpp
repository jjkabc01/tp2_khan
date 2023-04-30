#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "tri.hpp"

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& paire) {
  return os << "<" << paire.first << ", " << paire.second << ">";
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<int, int> >& vecteur) {
  os << "[";
  if (!vecteur.empty()) {
    os << vecteur[0];
  }
  for (unsigned int i = 1; i < vecteur.size(); i++) {
    os << ", " << vecteur[i];
  }
  return os << "]";
}

bool comparaison(const std::pair<int, int>& a, const std::pair<int, int>& b) {
  return a.first < b.first;
}

bool test_generique(const std::string& nom_du_test,
		    const std::vector<std::pair<int, int> >& liste,
		    bool mode_silencieux = false) {
  std::vector<std::pair<int, int> > copie1(liste);
  std::vector<std::pair<int, int> > copie2(liste);

  triParDenombrement(copie1);
  std::stable_sort(copie2.begin(), copie2.end(), comparaison);
  const bool resultat = (copie1 == copie2);
  if (!mode_silencieux) {
    if (resultat) {
      std::cout << "+1 point: Le test " << nom_du_test << " a passe." << std::endl;
    } else {
      std::cout << "+0 point: Le test " << nom_du_test << " a echoue." << std::endl;
      std::cout << "  Vecteur a trier: " << liste << std::endl;
      std::cout << "  Vecteur attendu: " << copie2 << std::endl;
      std::cout << "  Vecteur obtenu:  " << copie1 << std::endl;
    }
  }
  return resultat;
}

bool test_simple(int n) {
  std::vector<std::pair<int, int> > vecteur;
  for (int i = n; i > 0; i--) {
    vecteur.push_back(std::pair<int, int>(i, i));
  }
  return test_generique("Test simple", vecteur);
}

bool test_avec_doublons(int n) {
  std::vector<std::pair<int, int> > vecteur;
  for (int i = 0; i < n; i++) {
    vecteur.push_back(std::pair<int, int>(29 * i % 17, i));
  }
  return test_generique("Test avec doublons", vecteur);
}

bool test_degenere(int n) {
  std::vector<std::pair<int, int> > vecteur;
  for (int i = 0; i < n; i++) {
    vecteur.push_back(std::pair<int, int>(0, i));
  }
  return test_generique("Test degenere", vecteur);
}

bool test_randomise(int n, int germe) {
  std::srand(germe);
  const unsigned int nb_instances = 1000;
  unsigned int score = 0;
  for (int simulation = 0; simulation < nb_instances; simulation++) {
    std::vector<std::pair<int, int> > vecteur;
    for (int i = 0; i < n; i++) {
      vecteur.push_back(std::pair<int, int>(std::rand() % 1000, i));
    }
    if (test_generique("Test randomise", vecteur, true))
      score++;
  }
  std::cout << "+" << score * 7.0 / nb_instances << " points Test randomise (" << score << " instances sur " << nb_instances << ")" << std::endl;
  return true;
}

int main() {
  // Tous les parametres de ces tests pourront changer lors de la correction
  test_simple(10);
  test_avec_doublons(40);
  test_degenere(40);
  test_randomise(1000, 666);
  return 0;
}
