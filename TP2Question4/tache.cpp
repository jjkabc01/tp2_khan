// Vous ne devez pas modifier ce fichier.

#include "tache.hpp"

#include <assert.h>

Tache::Tache(unsigned int duree, unsigned int echeance, unsigned int penalite)
  : m_duree(duree),
    m_echeance(echeance),
    m_penalite(penalite)
{
  assert(penalite >= 1);
}

Tache::Tache(const Tache& tache)
  : m_duree(tache.m_duree),
    m_echeance(tache.m_echeance),
    m_penalite(tache.m_penalite)
{
}
