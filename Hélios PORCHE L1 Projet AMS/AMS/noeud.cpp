#include "noeud.h" // Inclure le fichier d'en-tête pour la classe Noeud
#include <iostream> // Inclure la bibliothèque standard pour les entrées/sorties

// Constructeur de la classe Noeud
Noeud::Noeud(valeursNoeud x) {
    this->identifiant = x.identifiant; // Initialiser l'identifiant du noeud
    this->latitude = x.latitude; // Initialiser la latitude du noeud
    this->longitude = x.longitude; // Initialiser la longitude du noeud
    this->nombreRues = x.nombreRues; // Initialiser le nombre de rues passant par ce noeud
    this->visite = false; // Initialiser la visite à faux
}

// Méthode pour afficher les détails du noeud
void Noeud::affiche() const {
    std::cout << "Noeud ID: " << identifiant // Afficher l'identifiant du noeud
              << ", Latitude: " << latitude // Afficher la latitude du noeud
              << ", Longitude: " << longitude // Afficher la longitude du noeud
              << ", Nombre de rues: " << nombreRues << std::endl; // Afficher le nombre de rues passant par ce noeud
}
