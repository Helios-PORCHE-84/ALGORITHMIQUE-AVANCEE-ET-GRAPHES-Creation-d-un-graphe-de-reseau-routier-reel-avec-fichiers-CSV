#pragma once // Directive pour inclure le fichier une seule fois

#include <unordered_map> // Inclure la bibliothèque standard pour les cartes non ordonnées
#include "noeud.h" // Inclure le fichier d'en-tête pour la classe Noeud

// Définition du type id pour les identifiants
typedef unsigned long id;

class EnsembleNoeuds {
public:
    std::unordered_map<id, Noeud> noeuds; // Ensemble des noeuds

    // Méthode pour ajouter un noeud à l'ensemble
    void ajouterNoeud(Noeud x);

    // Méthode pour trouver un noeud par son identifiant
    void trouverNoeud(id identifiant);

    // Méthode pour afficher les noeuds de l'ensemble
    void affiche();
};
