#pragma once

#include <vector>
#include <string>
#include "arc.h"

// Définition du type id pour les identifiants
typedef unsigned long id;

class Arc;

// Structure pour stocker les valeurs d'un noeud
struct valeursNoeud {
    id              identifiant; // Identifiant du noeud
    double          longitude; // Longitude du noeud
    double          latitude; // Latitude du noeud
    unsigned int    nombreRues; // Nombre de rues passant par ce noeud
};

class Noeud {
public:
    id                  identifiant; // Identifiant du noeud
    std::vector<std::string> arcsEntrants; // Liste des arcs entrants
    std::vector<std::string> arcsSortants; // Liste des arcs sortants
    double              longitude; // Longitude du noeud
    double              latitude; // Latitude du noeud
    unsigned int        nombreRues; // Nombre de rues passant par ce noeud
    bool                visite; // Indique si le noeud a été visité

    // Constructeur par défaut
    Noeud() {};

    // Constructeur avec valeurs initiales
    Noeud(valeursNoeud x);

    // Destructeur
    ~Noeud() {};

    // Méthode pour obtenir l'identifiant du noeud
    inline id obtenirId() const { return this->identifiant; };

    // Méthode pour afficher les détails du noeud
    void affiche() const;
};
