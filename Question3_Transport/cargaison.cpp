// NE PAS MODIFIER CE FICHIER


#include "cargaison.hpp"

// Complexite: O(1)
Cargaison::Cargaison(unsigned int expediteur, unsigned int destinataire, unsigned quantite)
  : m_expediteur(expediteur),
    m_destinataire(destinataire),
    m_quantite(quantite)
{
}
    
// Complexite: O(1)
Cargaison::Cargaison(const Cargaison& cargaison)
  : m_expediteur(cargaison.m_expediteur),
    m_destinataire(cargaison.m_destinataire),
    m_quantite(cargaison.m_quantite)
{
}

// Complexite: O(1)
unsigned Cargaison::expediteur() const {
  return m_expediteur;
}

// Complexite: O(1)
unsigned Cargaison::destinataire() const {
  return m_destinataire;
}

// Complexite: O(1)
unsigned Cargaison::quantite() const {
  return m_quantite;
}

// Complexite: O(1)
std::ostream& operator<<(std::ostream& os, const Cargaison& cargaison) {
  return os << "(" << cargaison.expediteur() << " --"
	    << cargaison.quantite() << "--> " << cargaison.destinataire() << ")";
}
