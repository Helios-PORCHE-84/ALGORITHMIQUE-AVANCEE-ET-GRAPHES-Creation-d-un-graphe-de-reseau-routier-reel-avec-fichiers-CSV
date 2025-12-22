#pragma once // Directive pour inclure le fichier une seule fois

#include <unordered_map> // Inclure la bibliothèque standard pour les cartes non ordonnées
#include <iostream> // Inclure la bibliothèque standard pour les entrées/sorties
#include <string> // Inclure la bibliothèque standard pour les chaînes de caractères
#include "noeud.h" // Inclure le fichier d'en-tête pour la classe Noeud
#include "arc.h" // Inclure le fichier d'en-tête pour la classe Arc

class EnsembleArcs {
public:
    std::unordered_map<std::string, Arc> arcs; // Ensemble des arcs

    // Méthode pour ajouter un arc à l'ensemble
    void ajouterArc(Arc x);

    // Méthode pour trouver un arc par son identifiant
    void trouverArc(std::string identifiant);

    // Méthode pour afficher les arcs de l'ensemble
    void affiche();
};
