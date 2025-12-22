#include "EnsembleNoeuds.h" // Inclure le fichier d'en-tête pour la classe EnsembleNoeuds
#include <iostream> // Inclure la bibliothèque standard pour les entrées/sorties

// Méthode pour ajouter un noeud à l'ensemble
void EnsembleNoeuds::ajouterNoeud(Noeud x) {
    noeuds.insert(std::make_pair(x.obtenirId(), x)); // Insérer le noeud dans la carte
}

// Méthode pour trouver un noeud par son identifiant
void EnsembleNoeuds::trouverNoeud(id identifiant) {
    if (noeuds.find(identifiant) != noeuds.end()) { // Si le noeud est trouvé
        std::cout << "Noeud trouvé: " << std::endl; // Afficher un message
        noeuds[identifiant].affiche(); // Afficher les détails du noeud
    } else { // Sinon
        std::cout << "Noeud non trouvé." << std::endl; // Afficher un message
    }
}

// Méthode pour afficher les noeuds de l'ensemble
void EnsembleNoeuds::affiche() {
    for (const auto& paire : noeuds) { // Pour chaque noeud dans la carte
        paire.second.affiche(); // Afficher les détails du noeud
    }
}
