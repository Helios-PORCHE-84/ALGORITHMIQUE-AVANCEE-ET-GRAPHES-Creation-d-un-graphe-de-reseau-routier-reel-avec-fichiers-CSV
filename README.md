# ALGORITHMIQUE AVANCEE ET GRAPHES Création d'un graphe de réseau routier réel à partir de fichiers CSV.

# Contexte & Objectif : 

Projet individuel (L1 / L2, AMS Algorithmique Avancée et Graphes). Modélisation du réseau routier réel d'Avignon et algorithmes de recherche d'itinéraire. 


# Détails Techniques & Concepts Clés :

• Structures de données graphes : Liste d'adjacence / Matrice d'incidence. Choix de structures de recherche rapide (Tables de hachage / Arbres binaires) pour les nœuds et les arcs.

• Parsing de données massives : Lecture et traitement de fichiers CSV (nodes.csv, arcs.csv) contenant des coordonnées GPS, des sens uniques, et des limitations de vitesse.

• Algorithmes de parcours : DFS (Profondeur) pour l'accessibilité, BFS (Largeur) pour le plus court chemin (en nombre d'arcs). 


# Cheminement de réalisation (Synopsis) :

1. Conception des Classes : Création des classes Noeud (id, lat, lon, street_count) et Arc (osmid, oneway, maxspeed, length, geometry).

2. Ingestion des Données : Développement des méthodes lecture_noeuds et lecture_arcs pour parser les CSV et instancier les objets en mémoire.

3. Construction du Graphe : Implémentation de liste_incidence() pour attacher les arcs sortants et entrants à chaque nœud.

4. Analyse du Réseau : Création de la méthode degre(n) pour identifier les carrefours les plus complexes.

5. Algorithmes de Routage :

• chemin(o, d) : Parcours en profondeur avec pile pour vérifier si une route existe.

• pluscourtchemin(o, d) : Parcours en largeur avec file pour trouver le trajet avec le moins de segments.

• itineraire : Recherche par noms de rues plutôt que par identifiants techniques.
