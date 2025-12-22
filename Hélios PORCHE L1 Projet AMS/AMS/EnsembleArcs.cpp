#include "EnsembleArcs.h" // Inclure le fichier d'en-tête pour la classe EnsembleArcs

// Méthode pour ajouter un arc à l'ensemble
void EnsembleArcs::ajouterArc(Arc x) {
    int index = 0; // Initialiser l'index à 0
    std::string id = x.nom + std::to_string(index); // Créer un identifiant unique pour l'arc
    while (arcs.find(id) != arcs.end()) { // Tant que l'identifiant existe déjà
        index++; // Incrémenter l'index
        id = x.nom + std::to_string(index); // Mettre à jour l'identifiant
    }
    arcs.insert(std::make_pair(id, x)); // Insérer l'arc dans la carte
}

// Méthode pour trouver un arc par son identifiant
void EnsembleArcs::trouverArc(std::string identifiant) {
    if (arcs.find(identifiant) != arcs.end()) { // Si l'arc est trouvé
        std::cout << "Arc trouvé: " << std::endl; // Afficher un message
        arcs[identifiant].affiche(); // Afficher les détails de l'arc
    } else { // Sinon
        std::cout << "Arc non trouvé." << std::endl; // Afficher un message
    }
}

// Méthode pour afficher les arcs de l'ensemble
void EnsembleArcs::affiche() {
    for (const auto& paire : arcs) { // Pour chaque arc dans la carte
        paire.second.affiche(); // Afficher les détails de l'arc
    }
}
