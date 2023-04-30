// NE PAS MODIFIER CE FICHIER

#ifndef CARGAISON
#define CARGAISON

#include <iostream>

class Cargaison {
private:
  unsigned int m_expediteur;
  unsigned int m_destinataire;
  unsigned int m_quantite;
public:
  Cargaison(unsigned int expediteur, unsigned int destinataire, unsigned quantite);
  Cargaison(const Cargaison& cargaison);

  unsigned expediteur() const;
  unsigned destinataire() const;
  unsigned quantite() const;
};

std::ostream& operator<<(std::ostream& os, const Cargaison& cargaison);

#endif
