#pragma once

#include <string>
#include "noeud.h"

// Définition du type id pour les identifiants
typedef unsigned long id;

// Enumération des types de routes
enum TypeRoute {
    AUTOROUTE,
    PRINCIPALE,
    SECONDAIRE,
    RESIDENTIELLE
};

// Structure pour stocker les valeurs d'un arc
struct valeursArc {
    id              identifiant; // Identifiant de l'arc
    id              origine; // Noeud d'origine
    id              destination; // Noeud de destination
    std::string     nom; // Nom de la route
    bool            sensUnique; // Indique si la route est à sens unique
    unsigned int    voies; // Nombre de voies de la route
    std::string     type; // Type de route
    bool            inverse; // Indique le sens de la route si elle est à sens unique
    float           longueur; // Longueur de la route en mètres
    int             geometrie; // Géométrie de la route
    float           vitesseMax; // Vitesse maximale sur la route en km/h
    float           vitesseKmh; // Vitesse moyenne sur la route en km/h
    float           tempsTrajet; // Temps de trajet sur la route en secondes
};

class Arc {
public:
    id              identifiant; // Identifiant de l'arc
    id              origine; // Noeud d'origine
    id              destination; // Noeud de destination
    bool            sensUnique; // Indique si la route est à sens unique
    unsigned int    voies; // Nombre de voies de la route
    std::string     nom; // Nom de la route
    std::string     type; // Type de route
    bool            inverse; // Indique le sens de la route si elle est à sens unique
    unsigned int    longueur; // Longueur de la route en mètres
    unsigned short  vitesseMax; // Vitesse maximale sur la route en km/h
    unsigned short  vitesseKmh; // Vitesse moyenne sur la route en km/h
    unsigned short  tempsTrajet; // Temps de trajet sur la route en secondes

    // Constructeur par défaut
    Arc() {};

    // Constructeur avec valeurs initiales
    Arc(valeursArc a);

    // Méthode pour obtenir l'identifiant de l'arc
    inline id obtenirId() { return this->identifiant; };

    // Méthode pour obtenir le nom de l'arc
    inline std::string obtenirNom() const { return this->nom; };

    // Méthode pour afficher les détails de l'arc
    void affiche() const;
};
