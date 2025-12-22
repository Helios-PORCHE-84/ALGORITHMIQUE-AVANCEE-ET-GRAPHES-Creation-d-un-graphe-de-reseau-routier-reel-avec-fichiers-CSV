#pragma once // Directive pour inclure le fichier une seule fois

#include "EnsembleNoeuds.h" // Inclure le fichier d'en-tête pour la classe EnsembleNoeuds
#include "EnsembleArcs.h" // Inclure le fichier d'en-tête pour la classe EnsembleArcs
#include <fstream> // Inclure la bibliothèque standard pour les flux de fichiers
#include <iostream> // Inclure la bibliothèque standard pour les entrées/sorties
#include <string> // Inclure la bibliothèque standard pour les chaînes de caractères

// Définition du type id pour les identifiants
typedef unsigned long id;

class Graphe {
public:
    EnsembleNoeuds lesNoeuds; // Ensemble des noeuds
    EnsembleArcs lesArcs; // Ensemble des arcs
    unsigned int nombreDeNoeuds; // Nombre de noeuds
    unsigned int nombreDArcs; // Nombre d'arcs

    // Constructeur de la classe Graphe
    Graphe(std::string fichierArcs, std::string fichierNoeuds);

    // Destructeur de la classe Graphe
    ~Graphe() {};

    // Méthode pour lire les noeuds depuis un fichier
    unsigned int lectureNoeuds(std::string fichier);

    // Méthode pour lire les arcs depuis un fichier
    unsigned int lectureArcs(std::string fichier);

    // Méthode pour mettre à jour la liste d'incidence
    void listeIncidence();

    // Méthode pour afficher les n premiers noeuds de plus fort degré
    void degre(int n);

    // Méthode pour trouver un chemin entre deux noeuds
    int chemin(id o, id d);

    // Méthode pour trouver le plus court chemin entre deux noeuds
    int plusCourtChemin(id o, id d);

    // Méthode pour trouver l'itinéraire le plus court entre deux rues
    int itineraire(std::string origine, std::string destination);

    // Méthode pour afficher le graphe
    void affiche();

    // Méthode pour afficher les noeuds
    void afficheNoeuds();

    // Méthode pour afficher les arcs
    void afficheArcs();

    // Méthode pour ajouter un noeud à l'ensemble des noeuds
    void ajouterNoeud(Noeud noeud);

    // Méthode pour ajouter un arc à l'ensemble des arcs
    void ajouterArc(Arc arc);

    // Méthode pour trouver un noeud par son identifiant
    void trouverNoeud(id identifiant);

    // Méthode pour trouver un arc par son identifiant
    void trouverArc(std::string identifiant);
};
