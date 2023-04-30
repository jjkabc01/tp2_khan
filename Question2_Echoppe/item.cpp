#include "item.hpp"

// Constructeur
// Complexite: O(n) ou n est le nombre de caracteres dans le nom de l'item
Item::Item(const std::string& nom,
	   unsigned int effet,
	   unsigned prix,
	   unsigned int utilisation_main,
	   unsigned utilisation_pieds)
  : m_nom(nom),
    m_prix(prix),
    m_effet(effet),
    m_utilisation_mains(utilisation_main),
    m_utilisation_pieds(utilisation_pieds)
{
}

// Constructeur
// Complexite: O(n) ou n est le nombre de caracteres dans le nom de l'item
Item::Item(const Item& item)
  : m_nom(item.m_nom),
    m_prix(item.m_prix),
    m_effet(item.m_effet),
    m_utilisation_mains(item.m_utilisation_mains),
    m_utilisation_pieds(item.m_utilisation_pieds)
{
}

// Complexite: O(1)
const std::string& Item::nom() const {
  return m_nom;
}

// Complexite: O(1)
unsigned int Item::effet() const {
  return m_effet;
}

// Complexite: O(1)
unsigned int Item::prix() const {
  return m_prix;
}

// Complexite: O(1)
unsigned int Item::utilisation_mains() const {
  return m_utilisation_mains;
}

// Complexite: O(1)
unsigned int Item::utilisation_pieds() const {
  return m_utilisation_pieds;
}

// Complexite: O(n) ou n est le nombre de caracteres dans le nom de l'item
bool Item::operator==(const Item& item) const {
  return (m_nom == item.m_nom) &&
    (m_prix == item.m_prix) &&
    (m_utilisation_mains == item.m_utilisation_mains) &&
    (m_utilisation_pieds == item.m_utilisation_pieds) &&
    (m_effet == item.m_effet);
}

// Complexite: O(n) ou n est le nombre de caracteres dans le nom de l'item
bool Item::operator!=(const Item& item) const {
  return !this->operator==(item);
}

// Complexite: O(n) ou n est le nombre de caracteres dans le nom de l'item
bool Item::operator<(const Item& item) const {
  return m_nom < item.m_nom;
}
