#include "arc.h" // Inclure le fichier d'en-tête pour la classe Arc
#include <iostream> // Inclure la bibliothèque standard pour les entrées/sorties

// Constructeur de la classe Arc
Arc::Arc(valeursArc x) {
    this->origine = x.origine; // Initialiser le noeud d'origine
    this->destination = x.destination; // Initialiser le noeud de destination
    this->voies = x.voies; // Initialiser le nombre de voies
    this->longueur = x.longueur; // Initialiser la longueur de la route
    this->vitesseMax = x.vitesseMax; // Initialiser la vitesse maximale
    this->nom = x.nom; // Initialiser le nom de la route
    this->sensUnique = x.sensUnique; // Initialiser si la route est à sens unique
    this->inverse = x.inverse; // Initialiser le sens de la route si elle est à sens unique
    this->vitesseKmh = x.vitesseKmh; // Initialiser la vitesse moyenne
    this->tempsTrajet = x.tempsTrajet; // Initialiser le temps de trajet
    this->type = x.type; // Initialiser le type de route
    this->identifiant = x.identifiant; // Initialiser l'identifiant de l'arc
}

// Méthode pour afficher les détails de l'arc
void Arc::affiche() const {
    std::cout << "Arc ID: " << identifiant // Afficher l'identifiant de l'arc
              << ", Origine: " << origine // Afficher le noeud d'origine
              << ", Destination: " << destination // Afficher le noeud de destination
              << ", Sens unique: " << (sensUnique ? "Oui" : "Non") // Afficher si la route est à sens unique
              << ", Voies: " << voies // Afficher le nombre de voies
              << ", Nom: " << nom // Afficher le nom de la route
              << ", Type: " << type // Afficher le type de route
              << ", Inversé: " << (inverse ? "Oui" : "Non") // Afficher le sens de la route si elle est à sens unique
              << ", Longueur: " << longueur << " m" // Afficher la longueur de la route
              << ", Vitesse max: " << vitesseMax << " km/h" // Afficher la vitesse maximale
              << ", Vitesse moyenne: " << vitesseKmh << " km/h" // Afficher la vitesse moyenne
              << ", Temps de trajet: " << tempsTrajet << " s" << std::endl; // Afficher le temps de trajet
}
