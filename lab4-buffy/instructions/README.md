[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/atAt-hrK)
# Laboratoire 4: Buffy

**Date de rendu: 17/06/2023 17:00**

## 1. Introduction

Buffy, la tueuse, doit sauvegarder l’espèce humaine de la menace des vampires. L’application doit permettre de simuler les actions des vampires, des humains et de Buffy (dénotés par la suite comme “humanoïdes”), en mode “tour par tour” et d’effectuer des statistiques sur un ensemble de simulations.

- Buffy (B), les vampires (V) et les humains (h) sont placés aléatoirement sur une grille. La taille de la grille, le nombre d’humains et de vampires sont passés en paramètre du programme.
- Un menu affiche le numéro du tour courant et permet de passer au tour suivant (n ou <entrée>), d’effectuer des statistiques (s) ou de quitter le programme (q).
- A chaque tour de la simulation chaque humanoïde décide de sa prochaine action. Toutes les actions sont ensuite résolues simultanément (pour ne pas avantager les premiers humanoïdes dans la liste). L’état résultant de la simulation est ensuite affiché.

![image](https://github.com/HEIGVD-POA/lab4-buffy/assets/3931601/98222a3e-bfa9-4a43-9a26-0995fa4cf476)

Remarque: les codes couleurs dépendent de la plateforme, ils sont donc facultatifs à implémenter (en revanche, s'ils sont implémentés, ils doivent pouvoir être désactivés à la compilation pour éviter les problèmes).

##  2. Actions

- Chaque humain se déplace au hasard sur la grille, d’une case à la fois.
- Buffy attaque le vampire le plus proche. S’il est à une case de distance elle peut le tuer, sinon elle le chasse en avançant de deux cases dans sa direction. Si tous les vampires sont détruits, elle se déplacera au hasard sur la grille (comme les humains).
- Chaque vampire attaque l’humain (mais pas Buffy) le plus proche. S’il est à une case de distance il peut le tuer ou le transformer en vampire (une chance sur deux), sinon, il le chasse en avançant d’une case dans sa direction. Attention: un humain ne peut donner naissance qu’à un seul vampire. S’il n’y a plus d’humains à chasser, le vampire reste sur place pour dormir.
- Les statistiques (commande s) sont obtenues en effectuant 10’000 simulations pour les mêmes conditions initiales données (taille de la grille, nombre de vampires et d’humains, mais placement aléatoire), mais sans afficher le déplacement des humanoïdes. Chaque simulation est arrêtée lorsqu’il n’y a plus de vampires. Sur l’ensemble des simulations le pourcentage de succès de Buffy (pourcentage des simulations où au moins un humain reste vivant) est calculé et affiché.

## 3. Mise en oeuvre

- Concevoir un diagramme de classes permettant de factoriser au maximum le code et de dissocier la gestion de l’interface graphique du comportement des humanoïdes (une simulation doit pouvoir être réalisée sans affichage graphique, comme dans le cas du calcul des statistiques).
- Chaque classe d’humanoïde doit référencer un objet Action, caractérisant la prochaine action à effectuer. Cette classe Action doit posséder une méthode void execute(Field& f) permettant d’exécuter l’action courante en influant sur l’environnement, représenté par la classe Field.
- La classe Field permet de faire évoluer les humanoïdes sur une grille. Ceux-ci seront manipulés au moyen d’une liste STL. Cette classe doit fournir une méthode pour simuler un tour. Le code d'exemple ci-après peut servir de base à la réalisation de cette méthode (vous pouvez l'utiliser telle quelle ou la modifier, par exemple en utiliser des smart pointer).

```c++
int Field::nextTurn()
{
  // Déterminer les prochaines actions
  for (list<Humanoid*>::iterator it = humanoids.begin(); it != humanoids.end(); it++)
    (*it)->setAction(*this);
  // Executer les actions
  for (list<Humanoid*>::iterator it = humanoids.begin(); it != humanoids.end(); it++)
    (*it)->executeAction(*this);
  // Enlever les humanoides tués
  for (list<Humanoid*>::iterator it = humanoids.begin(); it != humanoids.end(); ) {
    if (!(*it)->isAlive()) {
      Humanoid* toDelete = *it;
      it = humanoids.erase(it); // suppression de l’élément dans la liste
      delete *toDelete; // destruction de l’humanoide référencé
    }
    else
      ++it;
  }
  return turn++;
}
```

- La classe Field doit également offrir une méthode permettant de trouver l’humanoïde, instance d’une classe donnée, le plus proche d’un humanoïde donné.
- Il n’est pas interdit d’empêcher que deux humanoïdes occupent la même case de la grille ou de concevoir des algorithmes plus performants que celui proposé pour augmenter le pourcentage de succès de Buffy.
- Le rapport inclura (entre autres) le pourcentage de succès de Buffy pour les conditions initiales: grille de 50x50, 10 vampires et 20 humains.
