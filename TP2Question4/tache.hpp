// Vous ne devez pas modifier ce fichier.

#ifndef TACHE
#define TACHE

class Tache {
private:
  unsigned int m_duree;
  unsigned int m_echeance;
  unsigned int m_penalite;

public:
  Tache(unsigned int duree, unsigned echeance, unsigned penalite);
  Tache(const Tache& tache);

  inline unsigned int duree() const { return m_duree; }
  inline unsigned int echeance() const { return m_echeance; }
  inline unsigned int penalite() const { return m_penalite; }
};

#endif
