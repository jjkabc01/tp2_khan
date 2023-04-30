// NE PAS MODIFIER CE FICHIER
//
// Classe permettant de manipuler des tableaux a plusieurs
// dimensions. Si vous ne voulez pas utiliser cette classe, vous
// pouvez simplement l'ignorer.
//
// ATTENTION: Il y a une raison pourquoi une telle classe n'existe pas
// dans la STL. Les erreurs de typages ne sont pas toutes detectees a
// la compilation. Par exemple, si vous declarez un tableau a 3
// dimensions, le compilateur vous permet d'appeler la fonction at
// avec seulement 2 indices. Ceci generera une erreur a l'execution.
//
// Exemple d'utilisation de la classe ou on cree un tableau de
// dimensions 2 x 2 x 2 et imprime son contenu.
//
//  unsigned int dimensions[3] = {2, 2, 2};
//  Tableau<std::string> t(std::vector<unsigned int>(dimensions, dimensions + 3));
//  t.at(0, 0, 0) = "Bonjour";
//  t.at(0, 1, 0) = "tout";
//  t.at(1, 0, 0) = "le";
//  t.at(1, 1, 0) = "monde";
//  t.at(0, 0, 1) = "comment";
//  t.at(0, 1, 1) = "allez";
//  t.at(1, 0, 1) = "-";
//  t.at(1, 1, 1) = "vous?";
//  std::cout << t.at(0, 0, 0) << ", " << t.at(0, 1, 0) << std::endl;
//  std::cout << t.at(1, 0, 0) << ", " << t.at(1, 1, 0) << std::endl;
//  std::cout << t.at(0, 0, 1) << ", " << t.at(0, 1, 1) << std::endl;
//  std::cout << t.at(1, 0, 1) << ", " << t.at(1, 1, 1) << std::endl;
//
//
//  Cree un tableau de dimensions 2 x 2 x 2 x 3 et imprime son contenu
//
//  unsigned int test[4] = {2, 2, 2, 3};
//  Tableau<std::string> t(std::vector<unsigned int>(test, test + 4));
//  t.at(0, 0, 0, 0) = "Bonjour";
//  t.at(0, 1, 0, 0) = "tout";
//  t.at(1, 0, 0, 0) = "le";
//  t.at(1, 1, 0, 0) = "monde";
//  t.at(0, 0, 1, 0) = "comment";
//  t.at(0, 1, 1, 0) = "allez";
//  t.at(1, 0, 1, 0) = "-";
//  t.at(1, 1, 1, 0) = "vous?";
//  t.at(0, 0, 0, 1) = "Bonjour";
//  t.at(0, 1, 0, 1) = "tout";
//  t.at(1, 0, 0, 1) = "le";
//  t.at(1, 1, 0, 1) = "monde";
//  t.at(0, 0, 1, 1) = "comment";
//  t.at(0, 1, 1, 1) = "allez";
//  t.at(1, 0, 1, 1) = "-";
//  t.at(1, 1, 1, 1) = "vous?";
//  t.at(0, 0, 0, 2) = "Bonjour";
//  t.at(0, 1, 0, 2) = "tout";
//  t.at(1, 0, 0, 2) = "le";
//  t.at(1, 1, 0, 2) = "monde";
//  t.at(0, 0, 1, 2) = "comment";
//  t.at(0, 1, 1, 2) = "allez";
//  t.at(1, 0, 1, 2) = "-";
//  t.at(1, 1, 1, 2) = "vous?";
//  std::cout << t.at(0, 0, 0, 0) << ", " << t.at(0, 1, 0, 0) << std::endl;
//  std::cout << t.at(1, 0, 0, 0) << ", " << t.at(1, 1, 0, 0) << std::endl;
//  std::cout << t.at(0, 0, 1, 0) << ", " << t.at(0, 1, 1, 0) << std::endl;
//  std::cout << t.at(1, 0, 1, 0) << ", " << t.at(1, 1, 1, 0) << std::endl;
//  std::cout << t.at(0, 0, 0, 1) << ", " << t.at(0, 1, 0, 1) << std::endl;
//  std::cout << t.at(1, 0, 0, 1) << ", " << t.at(1, 1, 0, 1) << std::endl;
//  std::cout << t.at(0, 0, 1, 1) << ", " << t.at(0, 1, 1, 1) << std::endl;
//  std::cout << t.at(1, 0, 1, 1) << ", " << t.at(1, 1, 1, 1) << std::endl;

#ifndef TABLEAUX
#define TABLEAUX

#include <assert.h>
#include <iostream>
#include <stdarg.h>
#include <vector>

template <class T>
class Tableau {
private:
  std::vector<unsigned int> m_dimensions;
  std::vector<T>  m_contenu;
public:
  // Construit un tableau dont le nombre de dimensions est dimensions.size().
  // La longueur du tableau sur chacune de ces dimensions est specifiee dans le vecteur dimensions

  // Complexite: Theta(n) ou n est le nombre de cellules du tableau
  // Theta(n) = Theta(dimensions[0] * dimensions[1] * dimensions[2] * ...)
  Tableau(const std::vector<unsigned int>& dimensions)
    : m_dimensions(dimensions)
  {
    assert(!dimensions.empty());
    unsigned int nb_elements = 1;
    for (std::vector<unsigned int>::const_iterator i = m_dimensions.begin(); i != m_dimensions.end(); i++) {
      assert(*i > 0);		// Les dimensions doivent etre positives
      nb_elements *= *i;
    }
    m_contenu.resize(nb_elements);
  }

  // Constructeur de copie
  // Complexite: Thete(nombre d'entrees dans le tableau) = Theta(produit des dimensions du tableau)
  Tableau(const Tableau<T>& original)
    : m_dimensions(original.m_dimensions),
      m_contenu(original.m_contenu)
  {
  }
    
  // Retourne un element du tableau. Cet element peut etre modifie
  // Exemple avec un tableau a trois dimensions de type Tableau<std::string>
  // t.at(1, 0, 4) = "bonjour";
  //
  // Complexite: Theta(d) ou d est le nombre de dimensions du
  // tableau. Donc pour un tableau a 7 dimensions, nous avons
  // Theta(d) = Theta(7) = Theta(1)
  T& at(unsigned int premier_index, ...) {
    assert(premier_index < m_dimensions[0]);
    unsigned int position = premier_index;

    va_list parametres;
    va_start(parametres, premier_index);
    for (std::vector<unsigned int>::const_iterator i = m_dimensions.begin() + 1; i != m_dimensions.end(); i++) {
      const unsigned int index = va_arg(parametres, unsigned int);
      if (index >= *i) {
	std::cerr << "Acces a la dimension " << (i - m_dimensions.begin()) << " a la position " << index << " alors que la plus grande position possible est " << (*i - 1) << std::endl;
      }
      assert(index < *i);
      position = position * *i + index;
    }
    va_end(parametres);
    return m_contenu[position];
  }
    
  // Retourne un element du tableau. Cet element ne peut pas etre modifie
  // Exemple avec un tableau a trois dimensions de type Tableau<std::string>
  // t.at(1, 0, 4);
  //
  // Complexite: Theta(d) ou d est le nombre de dimensions du
  // tableau. Donc pour un tableau a 7 dimensions, nous avons
  // Theta(d) = Theta(7) = Theta(1)
  const T& at(unsigned int premier_index, ...) const {
    assert(premier_index < m_dimensions[0]);
    unsigned int position = premier_index;

    va_list parametres;
    va_start(parametres, premier_index);
    for (std::vector<unsigned int>::const_iterator i = m_dimensions.begin() + 1; i != m_dimensions.end(); i++) {
      const unsigned int index = va_arg(parametres, unsigned int);
      if (index >= *i) {
	std::cerr << "Acces a la dimension " << (i - m_dimensions.begin()) << " a la position " << index << " alors que la plus grande position possible est " << *i << std::endl;
      }
      assert(index < *i);
      position = position * *i + index;
    }
    va_end(parametres);
    return m_contenu[position];
  }
};

#endif
