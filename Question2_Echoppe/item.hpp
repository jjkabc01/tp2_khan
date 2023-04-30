#ifndef ITEM
#define ITEM

#include <string>

class Item {
private:
  std::string m_nom;
  unsigned int m_prix;
  unsigned int m_effet;
  unsigned int m_utilisation_mains;
  unsigned int m_utilisation_pieds;
public:
  Item(const std::string& nom,
       unsigned int effet,
       unsigned prix,
       unsigned int utilisation_main,
       unsigned utilisation_pieds);
  Item(const Item& item);

  const std::string& nom() const;
  unsigned int effet() const;
  unsigned int prix() const;
  unsigned int utilisation_mains() const;
  unsigned int utilisation_pieds() const;

  bool operator==(const Item& item) const;
  bool operator!=(const Item& item) const;
  bool operator<(const Item& item) const;
};

#endif
