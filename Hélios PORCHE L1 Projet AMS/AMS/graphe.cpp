#include "graphe.h" // Inclure le fichier d'en-tête pour la classe Graphe
#include <algorithm> // Inclure la bibliothèque standard pour les algorithmes
#include <sstream> // Inclure la bibliothèque standard pour les flux de chaînes
#include <queue> // Inclure la bibliothèque standard pour les files
#include <stack> // Inclure la bibliothèque standard pour les piles
#include <unordered_map> // Inclure la bibliothèque standard pour les cartes non ordonnées

// Fonction pour supprimer un caractère d'une chaîne de caractères
void supprimerCaractere(std::string &ligne, char caractere) {
    ligne.erase(
        std::remove(
            ligne.begin(),
            ligne.end(),
            caractere
        ),
        ligne.end()
    );
}

// Fonction pour analyser une ligne de noeuds et retourner une structure valeursNoeud
valeursNoeud analyserNoeud(std::string ligne) {
    supprimerCaractere(ligne, '{'); // Supprimer le caractère '{'
    supprimerCaractere(ligne, '}'); // Supprimer le caractère '}'
    supprimerCaractere(ligne, '\''); // Supprimer le caractère '\''
    supprimerCaractere(ligne, '"'); // Supprimer le caractère '"'

    std::stringstream ss(ligne); // Créer un flux de chaîne à partir de la ligne
    std::string tampon; // Chaîne tampon pour stocker les sous-chaînes
    std::string token; // Chaîne token pour stocker les jetons

    unsigned short actuellementAnalyse = 0; // Variable pour suivre l'analyse actuelle

    valeursNoeud noeud { 0 }; // Initialiser la structure valeursNoeud
    noeud.nombreRues = 1; // Initialiser le nombre de rues à 1

    while (std::getline(ss, tampon, ',')) { // Lire les sous-chaînes séparées par des virgules
        std::stringstream s(tampon); // Créer un flux de chaîne à partir de la sous-chaîne

        if (actuellementAnalyse == 0) { // Si c'est la première analyse
            noeud.identifiant = std::stoull(tampon); // Convertir la sous-chaîne en identifiant
        } else { // Sinon
            while (std::getline(s, token, ':')) { // Lire les jetons séparés par des deux-points
                if (token == "y") { // Si le jeton est "y"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    noeud.latitude = std::stod(token); // Convertir le jeton en latitude
                }
                if (token == " x") { // Si le jeton est " x"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    noeud.longitude = std::stod(token); // Convertir le jeton en longitude
                }
                if (token == " street_count") { // Si le jeton est " street_count"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    noeud.nombreRues = std::stoi(token); // Convertir le jeton en nombre de rues
                }
            }
        }
        actuellementAnalyse++; // Incrémenter l'analyse actuelle
    }
    return noeud; // Retourner la structure valeursNoeud
}

// Fonction pour analyser une ligne d'arcs et retourner une structure valeursArc
valeursArc analyserArc(std::string ligne) {
    supprimerCaractere(ligne, '{'); // Supprimer le caractère '{'
    supprimerCaractere(ligne, '}'); // Supprimer le caractère '}'
    supprimerCaractere(ligne, '\''); // Supprimer le caractère '\''
    supprimerCaractere(ligne, '"'); // Supprimer le caractère '"'

    std::stringstream ss(ligne); // Créer un flux de chaîne à partir de la ligne
    std::string tampon; // Chaîne tampon pour stocker les sous-chaînes
    std::string token; // Chaîne token pour stocker les jetons

    valeursArc arc { 0 }; // Initialiser la structure valeursArc
    arc.voies = 1; // Initialiser le nombre de voies à 1
    arc.nom = "Nom inconnu"; // Initialiser le nom à "Nom inconnu"

    unsigned short actuellementAnalyse = 0; // Variable pour suivre l'analyse actuelle
    while (std::getline(ss, tampon, ',')) { // Lire les sous-chaînes séparées par des virgules
        std::stringstream s(tampon); // Créer un flux de chaîne à partir de la sous-chaîne

        if (actuellementAnalyse == 0) { // Si c'est la première analyse
            arc.origine = std::stoull(tampon); // Convertir la sous-chaîne en noeud d'origine
        } else if (actuellementAnalyse == 1) { // Si c'est la deuxième analyse
            arc.destination = std::stoull(tampon); // Convertir la sous-chaîne en noeud de destination
        } else { // Sinon
            while (std::getline(s, token, ':')) { // Lire les jetons séparés par des deux-points
                token.erase(0, 1); // Supprimer le premier caractère
                if (token == "smid") { // Si le jeton est "smid"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.identifiant = std::stoull(token); // Convertir le jeton en identifiant
                }
                if (token == "name") { // Si le jeton est "name"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    arc.nom = token; // Stocker le jeton dans le nom
                }
                if (token == "highway") { // Si le jeton est "highway"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.type = token; // Stocker le jeton dans le type
                }
                if (token == "oneway") { // Si le jeton est "oneway"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    if (token == "False") // Si le jeton est "False"
                        arc.sensUnique = false; // Mettre sensUnique à faux
                    if (token == "True") // Si le jeton est "True"
                        arc.sensUnique = true; // Mettre sensUnique à vrai
                }
                if (token == "reversed") { // Si le jeton est "reversed"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    if (token == "False") // Si le jeton est "False"
                        arc.inverse = false; // Mettre inverse à faux
                    if (token == "True") // Si le jeton est "True"
                        arc.inverse = true; // Mettre inverse à vrai
                }
                if (token == "length") { // Si le jeton est "length"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.longueur = std::stof(token); // Convertir le jeton en longueur
                }
                if (token == "speed_kph") { // Si le jeton est "speed_kph"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.vitesseKmh = std::stof(token); // Convertir le jeton en vitesse moyenne
                }
                if (token == "maxspeed") { // Si le jeton est "maxspeed"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.vitesseMax = std::stof(token); // Convertir le jeton en vitesse maximale
                }
                if (token == "travel_time") { // Si le jeton est "travel_time"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.tempsTrajet = std::stof(token); // Convertir le jeton en temps de trajet
                }
                if (token == "lanes") { // Si le jeton est "lanes"
                    std::getline(s, token, ':'); // Lire le jeton suivant
                    token.erase(0, 1); // Supprimer le premier caractère
                    if (token[0] == '[') { // Si le jeton commence par '['
                        supprimerCaractere(token, '['); // Supprimer le caractère '['
                        supprimerCaractere(token, ']'); // Supprimer le caractère ']'
                        supprimerCaractere(token, ' '); // Supprimer le caractère ' '
                        std::stringstream sss(token); // Créer un flux de chaîne à partir du jeton
                        std::getline(sss, token, ','); // Lire le jeton suivant
                    }
                    arc.voies = std::stoi(token); // Convertir le jeton en nombre de voies
                }
            }
        }
        actuellementAnalyse++; // Incrémenter l'analyse actuelle
    }
    return arc; // Retourner la structure valeursArc
}

// Constructeur de la classe Graphe
Graphe::Graphe(std::string fichierArcs, std::string fichierNoeuds) {
    std::cout << "Lecture des noeuds depuis le fichier " << fichierNoeuds << "..." << std::endl; // Afficher un message
    this->nombreDeNoeuds = this->lectureNoeuds(fichierNoeuds); // Lire les noeuds depuis le fichier
    std::cout << "Nombre de noeuds lus: " << this->nombreDeNoeuds << std::endl; // Afficher le nombre de noeuds lus

    std::cout << "Lecture des arcs depuis le fichier " << fichierArcs << "..." << std::endl; // Afficher un message
    this->nombreDArcs = this->lectureArcs(fichierArcs); // Lire les arcs depuis le fichier
    std::cout << "Nombre d'arcs lus: " << this->nombreDArcs << std::endl; // Afficher le nombre d'arcs lus

    std::cout << "Mise à jour de la liste d'incidence..." << std::endl; // Afficher un message
    this->listeIncidence(); // Mettre à jour la liste d'incidence

    std::cout << "Affichage du graphe:" << std::endl; // Afficher un message
    this->affiche(); // Afficher le graphe

    std::cout << "Affichage des 5 premiers noeuds de plus fort degré:" << std::endl; // Afficher un message
    this->degre(5); // Afficher les 5 premiers noeuds de plus fort degré
    std::cout << "Noeuds de plus fort degré affichés." << std::endl; // Afficher un message

    std::cout << "Vérification de l'existence d'un chemin entre les noeuds 152303 et 152448:" << std::endl; // Afficher un message
    std::cout << "Chemin trouvé entre les noeuds 152303 et 152448." << std::endl; // Afficher un message
    int longueurChemin = this->chemin(152303, 152448); // Trouver le chemin entre les noeuds
    if (longueurChemin > 0) { // Si un chemin est trouvé
        std::cout << "Le chemin trouvé entre les noeuds 152303 et 152448 est de " << longueurChemin << " arcs." << std::endl; // Afficher un message
    } else { // Sinon
        std::cout << "Aucun chemin trouvé entre les noeuds 152303 et 152448." << std::endl; // Afficher un message
    }

    std::cout << "Calcul du plus court chemin entre les noeuds 152303 et 152448:" << std::endl; // Afficher un message
    int longueurPlusCourtChemin = this->plusCourtChemin(152303, 152448); // Trouver le plus court chemin entre les noeuds
    if (longueurPlusCourtChemin > 0) { // Si un chemin est trouvé
        std::cout << "Le plus court chemin trouvé entre les noeuds 152303 et 152448 est de " << longueurPlusCourtChemin << " arcs." << std::endl; // Afficher un message
    } else { // Sinon
        std::cout << "Aucun chemin trouvé entre les noeuds 152303 et 152448." << std::endl; // Afficher un message
    }

    std::cout << "Calcul de l'itinéraire le plus court entre les rues Avenue du Moulin de Notre-Dame et Avenue de la Cabrière:" << std::endl; // Afficher un message
    int longueurItineraire = this->itineraire("Avenue du Moulin de Notre-Dame", "Avenue de la Cabrière"); // Trouver l'itinéraire le plus court entre les rues
    if (longueurItineraire > 0) { // Si un itinéraire est trouvé
        std::cout << "L'itinéraire le plus court entre les rues Avenue du Moulin de Notre-Dame et Avenue de la Cabrière est de " << longueurItineraire << " rues." << std::endl; // Afficher un message
    } else { // Sinon
        std::cout << "Aucun itinéraire trouvé entre les rues Avenue du Moulin de Notre-Dame et Avenue de la Cabrière." << std::endl; // Afficher un message
    }

    // Ajouter des noeuds et des arcs pour tester les méthodes trouverNoeud et trouverArc
    this->ajouterNoeud(Noeud({1, 43.9376738, 4.8102078, 4})); // Ajouter un noeud
std::cout << "Noeud ajouté" << std::endl;
    this->ajouterArc(Arc({1, 1, 2, "Avenue Saint-Ruf", false, 1, "tertiary", false, 54.713, 0, 30, 30, 6.6})); // Ajouter un arc
std::cout << "Arc ajouté" << std::endl;

    std::cout << "Trouver un noeud par son identifiant: " << std::endl; // Afficher un message
    this->trouverNoeud(152303); // Trouver un noeud par son identifiant

    std::cout << "Trouver un arc par son identifiant: " << std::endl; // Afficher un message
    this->trouverArc("Chemin de la Forêt3"); // Trouver un arc par son identifiant
}

// Méthode pour afficher les n premiers noeuds de plus fort degré
void Graphe::degre(int n) {
    if (n <= 0 || n > this->lesNoeuds.noeuds.size()) { // Si n est inférieur ou égal à 0 ou supérieur au nombre de noeuds
        return; // Retourner
    }

    std::vector<std::pair<unsigned int, id>> degresNoeuds; // Vecteur pour stocker les paires de degrés et d'identifiants de noeuds

    for (const auto& paireNoeud : this->lesNoeuds.noeuds) { // Pour chaque noeud dans l'ensemble des noeuds
        id identifiantNoeud = paireNoeud.first; // Obtenir l'identifiant du noeud
        const Noeud& noeud = paireNoeud.second; // Obtenir le noeud
        unsigned int degre = noeud.arcsEntrants.size() + noeud.arcsSortants.size(); // Calculer le degré du noeud
        degresNoeuds.emplace_back(std::make_pair(degre, identifiantNoeud)); // Ajouter la paire de degré et d'identifiant de noeud au vecteur
    }

    // Tri à bulles
    for (size_t i = 0; i < degresNoeuds.size(); ++i) { // Pour chaque élément du vecteur
        for (size_t j = 0; j < degresNoeuds.size() - i - 1; ++j) { // Pour chaque élément du vecteur sauf le dernier
            if (degresNoeuds[j].first < degresNoeuds[j + 1].first) { // Si le degré de l'élément actuel est inférieur au degré de l'élément suivant
                std::swap(degresNoeuds[j], degresNoeuds[j + 1]); // Échanger les éléments
            }
        }
    }

    for (int i = 0; i < n; ++i) { // Pour les n premiers éléments du vecteur
        std::cout << "Noeud ID: " << degresNoeuds[i].second << ", Degré: " << degresNoeuds[i].first << '\n'; // Afficher l'identifiant et le degré du noeud
    }
}

// Méthode pour trouver un chemin entre deux noeuds
int Graphe::chemin(id o, id d) {
    std::stack<id> pile; // Pile pour stocker les noeuds à visiter
    std::unordered_map<id, Arc> predecesseurs; // Carte pour stocker les prédécesseurs des noeuds
    std::unordered_map<id, bool> visites; // Carte pour stocker les noeuds visités

    for (const auto& item : this->lesNoeuds.noeuds) { // Pour chaque noeud dans l'ensemble des noeuds
        visites[item.first] = false; // Initialiser les visites à faux
    }

    pile.push(o); // Ajouter le noeud de départ à la pile
    visites[o] = true; // Marquer le noeud de départ comme visité

    while (!pile.empty()) { // Tant que la pile n'est pas vide
        id courant = pile.top(); // Obtenir le noeud courant
        pile.pop(); // Retirer le noeud courant de la pile

        if (courant == d) { // Si le noeud courant est le noeud de destination
            std::vector<Arc> chemin; // Vecteur pour stocker le chemin
            id noeud = d; // Initialiser le noeud à la destination

            while (noeud != o) { // Tant que le noeud n'est pas le noeud de départ
                Arc arc = predecesseurs[noeud]; // Obtenir l'arc prédécesseur
                chemin.push_back(arc); // Ajouter l'arc au chemin
                noeud = arc.origine; // Mettre à jour le noeud à l'origine de l'arc
            }

            std::reverse(chemin.begin(), chemin.end()); // Inverser le chemin
            std::cout << "Chemin trouvé et routes utilisées :" << std::endl; // Afficher un message
            for (const Arc& arc : chemin) { // Pour chaque arc dans le chemin
                std::cout << arc.origine << " -> " << arc.destination << " = " << arc.nom << std::endl; // Afficher l'arc
            }

            return chemin.size(); // Retourner la taille du chemin
        }

        Noeud noeud = this->lesNoeuds.noeuds[courant]; // Obtenir le noeud courant
        for (const std::string& identifiantArc : noeud.arcsSortants) { // Pour chaque arc sortant du noeud courant
            Arc arc = this->lesArcs.arcs[identifiantArc]; // Obtenir l'arc
            Noeud noeudSuivant = this->lesNoeuds.noeuds[arc.destination]; // Obtenir le noeud suivant

            if (!visites[noeudSuivant.identifiant]) { // Si le noeud suivant n'a pas été visité
                visites[noeudSuivant.identifiant] = true; // Marquer le noeud suivant comme visité
                pile.push(noeudSuivant.identifiant); // Ajouter le noeud suivant à la pile
                predecesseurs[noeudSuivant.identifiant] = arc; // Stocker l'arc comme prédécesseur du noeud suivant
            }
        }
    }

    return 0; // Retourner 0 si aucun chemin n'est trouvé
}

// Méthode pour trouver le plus court chemin entre deux noeuds
int Graphe::plusCourtChemin(id o, id d) {
    std::queue<id> file; // File pour stocker les noeuds à visiter
    std::unordered_map<id, Arc> predecesseurs; // Carte pour stocker les prédécesseurs des noeuds
    std::unordered_map<id, bool> visites; // Carte pour stocker les noeuds visités

    for (const auto& item : this->lesNoeuds.noeuds) { // Pour chaque noeud dans l'ensemble des noeuds
        visites[item.first] = false; // Initialiser les visites à faux
    }

    file.push(o); // Ajouter le noeud de départ à la file
    visites[o] = true; // Marquer le noeud de départ comme visité

    while (!file.empty()) { // Tant que la file n'est pas vide
        id courant = file.front(); // Obtenir le noeud courant
        file.pop(); // Retirer le noeud courant de la file

        if (courant == d) { // Si le noeud courant est le noeud de destination
            std::vector<Arc> chemin; // Vecteur pour stocker le chemin
            id noeud = d; // Initialiser le noeud à la destination

            while (noeud != o) { // Tant que le noeud n'est pas le noeud de départ
                Arc arc = predecesseurs[noeud]; // Obtenir l'arc prédécesseur
                chemin.push_back(arc); // Ajouter l'arc au chemin
                noeud = arc.origine; // Mettre à jour le noeud à l'origine de l'arc
            }

            std::reverse(chemin.begin(), chemin.end()); // Inverser le chemin
            std::cout << "Chemin trouvé et routes utilisées :" << std::endl; // Afficher un message
            for (const Arc& arc : chemin) { // Pour chaque arc dans le chemin
                std::cout << arc.origine << " -> " << arc.destination << " = " << arc.nom << std::endl; // Afficher l'arc
            }

            return chemin.size(); // Retourner la taille du chemin
        }

        Noeud noeud = this->lesNoeuds.noeuds[courant]; // Obtenir le noeud courant
        for (const std::string& identifiantArc : noeud.arcsSortants) { // Pour chaque arc sortant du noeud courant
            Arc arc = this->lesArcs.arcs[identifiantArc]; // Obtenir l'arc
            Noeud noeudSuivant = this->lesNoeuds.noeuds[arc.destination]; // Obtenir le noeud suivant

            if (!visites[noeudSuivant.identifiant]) { // Si le noeud suivant n'a pas été visité
                visites[noeudSuivant.identifiant] = true; // Marquer le noeud suivant comme visité
                file.push(noeudSuivant.identifiant); // Ajouter le noeud suivant à la file
                predecesseurs[noeudSuivant.identifiant] = arc; // Stocker l'arc comme prédécesseur du noeud suivant
            }
        }
    }

    return 0; // Retourner 0 si aucun chemin n'est trouvé
}

// Méthode pour lire les noeuds depuis un fichier
unsigned int Graphe::lectureNoeuds(std::string nomFichier) {
    std::ifstream fichier(nomFichier); // Créer un flux de fichier pour lire les noeuds

    std::string ligne; // Chaîne pour stocker les lignes du fichier

    if (!fichier.is_open()) // Si le fichier ne peut pas être ouvert
        exit(1002); // Quitter avec un code d'erreur

    unsigned int compte = 0; // Initialiser le compteur de noeuds

    while (std::getline(fichier, ligne)) { // Lire les lignes du fichier
        valeursNoeud noeud = analyserNoeud(ligne); // Analyser la ligne pour obtenir les valeurs du noeud
        Noeud noeud_ = Noeud(noeud); // Créer un noeud avec les valeurs analysées
        this->lesNoeuds.ajouterNoeud(noeud_); // Ajouter le noeud à l'ensemble des noeuds
        compte++; // Incrémenter le compteur de noeuds
    }

    fichier.close(); // Fermer le fichier

    return compte; // Retourner le nombre de noeuds lus
}

// Méthode pour lire les arcs depuis un fichier
unsigned int Graphe::lectureArcs(std::string nomFichier) {
    std::ifstream fichier(nomFichier); // Créer un flux de fichier pour lire les arcs

    std::string ligne; // Chaîne pour stocker les lignes du fichier

    if (!fichier.is_open()) // Si le fichier ne peut pas être ouvert
        exit(1001); // Quitter avec un code d'erreur

    unsigned int compte = 0; // Initialiser le compteur d'arcs

    while (std::getline(fichier, ligne)) { // Lire les lignes du fichier
        valeursArc arc = analyserArc(ligne); // Analyser la ligne pour obtenir les valeurs de l'arc
        Arc arc_ = Arc(arc); // Créer un arc avec les valeurs analysées
        this->lesArcs.ajouterArc(arc_); // Ajouter l'arc à l'ensemble des arcs
        compte++; // Incrémenter le compteur d'arcs
    }

    fichier.close(); // Fermer le fichier

    return compte; // Retourner le nombre d'arcs lus
}

// Méthode pour mettre à jour la liste d'incidence
void Graphe::listeIncidence() {
    for (const auto& item : this->lesArcs.arcs) { // Pour chaque arc dans l'ensemble des arcs
        id depart = item.second.origine; // Obtenir le noeud de départ de l'arc
        id arrivee = item.second.destination; // Obtenir le noeud d'arrivée de l'arc

        this->lesNoeuds.noeuds[depart].arcsSortants.push_back(item.first); // Ajouter l'arc aux arcs sortants du noeud de départ
        this->lesNoeuds.noeuds[arrivee].arcsEntrants.push_back(item.first); // Ajouter l'arc aux arcs entrants du noeud d'arrivée
    }
}

// Méthode pour trouver l'itinéraire le plus court entre deux rues
int Graphe::itineraire(std::string origine, std::string destination) {
    id noeudDepart = -1; // Initialiser le noeud de départ à -1
    id noeudArrivee = -1; // Initialiser le noeud d'arrivée à -1

    // Trouver le noeud de départ
    for (const auto& item : this->lesNoeuds.noeuds) { // Pour chaque noeud dans l'ensemble des noeuds
        for (const std::string& identifiantArc : item.second.arcsSortants) { // Pour chaque arc sortant du noeud
            Arc arc = this->lesArcs.arcs[identifiantArc]; // Obtenir l'arc
            if (arc.nom == origine) { // Si le nom de l'arc correspond à l'origine
                noeudDepart = item.first; // Mettre à jour le noeud de départ
                break; // Sortir de la boucle
            }
        }
        if (noeudDepart != -1) // Si le noeud de départ a été trouvé
            break; // Sortir de la boucle
    }

    // Trouver le noeud d'arrivée
    for (const auto& item : this->lesNoeuds.noeuds) { // Pour chaque noeud dans l'ensemble des noeuds
        for (const std::string& identifiantArc : item.second.arcsEntrants) { // Pour chaque arc entrant du noeud
            Arc arc = this->lesArcs.arcs[identifiantArc]; // Obtenir l'arc
            if (arc.nom == destination) { // Si le nom de l'arc correspond à la destination
                noeudArrivee = item.first; // Mettre à jour le noeud d'arrivée
                break; // Sortir de la boucle
            }
        }
        if (noeudArrivee != -1) // Si le noeud d'arrivée a été trouvé
            break; // Sortir de la boucle
    }

    if (noeudDepart == -1 || noeudArrivee == -1) { // Si le noeud de départ ou d'arrivée n'a pas été trouvé
        std::cerr << "Une des rues n'a pas été trouvée." << std::endl; // Afficher un message d'erreur
        return 0; // Retourner 0
    }

    return this->plusCourtChemin(noeudDepart, noeudArrivee); // Retourner le plus court chemin entre les noeuds de départ et d'arrivée
}

// Méthode pour afficher le graphe
void Graphe::affiche() {
    std::cout << "Affichage des noeuds:" << std::endl; // Afficher un message
    afficheNoeuds(); // Afficher les noeuds
    std::cout << "Affichage des arcs:" << std::endl; // Afficher un message
    afficheArcs(); // Afficher les arcs
    std::cout << "Graphe affiché." << std::endl; // Afficher un message
}

// Méthode pour afficher les noeuds
void Graphe::afficheNoeuds() {
    for (const auto& paireNoeud : this->lesNoeuds.noeuds) { // Pour chaque noeud dans l'ensemble des noeuds
        const Noeud& noeud = paireNoeud.second; // Obtenir le noeud
        std::cout << "Noeud ID: " << noeud.identifiant // Afficher l'identifiant du noeud
                  << ", Latitude: " << noeud.latitude // Afficher la latitude du noeud
                  << ", Longitude: " << noeud.longitude // Afficher la longitude du noeud
                  << ", Nombre de rues: " << noeud.nombreRues << std::endl; // Afficher le nombre de rues passant par ce noeud
    }
}

// Méthode pour afficher les arcs
void Graphe::afficheArcs() {
    for (const auto& paireArc : this->lesArcs.arcs) { // Pour chaque arc dans l'ensemble des arcs
        const Arc& arc = paireArc.second; // Obtenir l'arc
        std::cout << "Arc ID: " << paireArc.first // Afficher l'identifiant de l'arc
                  << ", Osmid: " << arc.identifiant // Afficher l'identifiant OSM de l'arc
                  << ", Origine: " << arc.origine // Afficher le noeud d'origine de l'arc
                  << ", Destination: " << arc.destination // Afficher le noeud de destination de l'arc
                  << ", Sens unique: " << (arc.sensUnique ? "Oui" : "Non") // Afficher si l'arc est à sens unique
                  << ", Voies: " << arc.voies // Afficher le nombre de voies de l'arc
                  << ", Nom: " << arc.nom // Afficher le nom de l'arc
                  << ", Type: " << arc.type // Afficher le type de l'arc
                  << ", Inversé: " << (arc.inverse ? "Oui" : "Non") // Afficher si l'arc est inversé
                  << ", Longueur: " << arc.longueur << " m" // Afficher la longueur de l'arc
                  << ", Géométrie: <LINESTRING (" << arc.origine // Afficher la géométrie de l'arc
                  << " " << arc.destination << ")>" // Afficher la géométrie de l'arc
                  << ", Vitesse max: " << arc.vitesseMax << " km/h" // Afficher la vitesse maximale de l'arc
                  << ", Vitesse moyenne: " << arc.vitesseKmh << " km/h" // Afficher la vitesse moyenne de l'arc
                  << ", Temps de trajet: " << arc.tempsTrajet << " s" << std::endl; // Afficher le temps de trajet de l'arc
    }
}

// Méthode pour ajouter un noeud à l'ensemble des noeuds
void Graphe::ajouterNoeud(Noeud noeud) {
    this->lesNoeuds.ajouterNoeud(noeud); // Ajouter le noeud à l'ensemble des noeuds
}

// Méthode pour ajouter un arc à l'ensemble des arcs
void Graphe::ajouterArc(Arc arc) {
    this->lesArcs.ajouterArc(arc); // Ajouter l'arc à l'ensemble des arcs
}

// Méthode pour trouver un noeud par son identifiant
void Graphe::trouverNoeud(id identifiant) {
    this->lesNoeuds.trouverNoeud(identifiant); // Trouver le noeud par son identifiant
}

// Méthode pour trouver un arc par son identifiant
void Graphe::trouverArc(std::string identifiant) {
    this->lesArcs.trouverArc(identifiant); // Trouver l'arc par son identifiant
}
