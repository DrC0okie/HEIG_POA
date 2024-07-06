[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/5d-lxBZU)
# Laboratoire 1: Matrix Reloaded


**Durée du laboratoire:** 4 périodes. 

**Date de rendu : 20/03/2024 avant 23h59 (GitHub), à la séance de labo du 21 mars pour le rendu physique**

#### A rendre: 

Tout est a rendre en **version imprimée + sur GitHub**, dans la branche `main` de votre repo (**attention** l'état de votre branche `main` à la date/heure de rendu sera considéré final):
- Code source (fichiers .cpp, .hpp, CMakeLists.txt uniquement, au format UTF-8)
  - le code source des tests / tests unitaires n'a pas besoin d'être imprimé
- Rapport au format PDF contenant:
  - instructions de compilation, détail du compilateur utilisé (nom/version)
  - explications sur les choix d'implémentation / design
  - tests effectués (ce qui est testé, pas le code source)
  - digramme de classe UML (+au format PNG et fichier source, eg fichier Sylum, StarUML...)

Prenez le temps de lire et de suivre les bonnes pratiques: https://docs.google.com/presentation/d/1pzc5u5aIQGjU4GK71yU8Lhr_1kabnl34vUIy7uJmU6U/edit?usp=sharing.

#### Compilateurs supportés:

|Compilateur|Version minimum|
|---|---|
|gcc|11|
|MSVC|2022|
|Apple Clang|14|

Version du standard C++ à utiliser: C++17.

#### Outils conseillés:

|Outil|version minimum recommandée|But|
|---|---|---|
|clang-format|14|formattage automatique du code|
|cmake|3.10|configuration du build|
|ninja|1.11|make system (optionel)|
|doxygen||pour la génération de la doc de votre API (optionel)|
|git|2.39|versionnage de votre code source|

#### Exemple de compilation

```shell
mkdir build
cd build
cmake .. -G "Unix Makefiles" # Utilisez l'option -G pour choisir votre générateur (eg make, Ninja, Visual Studio, etc. voir: cmake --help)
make # build avec make
```

#### Formattage du code

Pour vous aidez à formatter le code, nous proposons d'utiliser `clang-format` et nous mettons à disposition un fichier `.clang-format`.
Certains IDE appliquent automatiquement le formattage suivant ce fichier. Pour le faire manuellement utilisez la commande suivante:

```shell
cd src/
clang-format -i src/*.cpp src/*.hpp
```

## But de l'exercice

Définir une classe permettant de représenter des matrices de taille quelconque (`N`x`M`) contenant des éléments entre `0` et `n − 1` pour un entier `n` strictement  positif (les entiers sont "modulo" n) qui réponde aux contraintes ci-dessous:

- Une matrice peut être crée en générant son contenu aléatoirement (une fois sa taille et son modulo connus).
- Les valeurs de la matrice sont stockées dans un tableau de tableaux (ne pas utiliser de conteneur C/C++ de la STL).
- Le contenu de la matrice peut être affiché en utilisant l’opérateur d’écriture dans un flux (<<).
- Un matrice peut être _dupliquée_ (par construction et par assignement).
- Une matrice peut être _déplacée_ (par construction et par assignement).
- Les opérations suivantes entre deux matrices doivent être possible: 
  - l’addition
  - la soustraction 
  - le produit composante par composante défini par $$C{_i}{_j} = A{_i}{_j} · B{_i}{_j} mod n$$
  - toutes les opérations doivent être effectuées modulo n.

Note: 

- Implémenter chaque opération de trois manières différentes; documenter dans votre rapport les (dés-)avantages  de chaque méthode:
  - Soit en modifiant la matrice sur laquelle est invoquée la méthode,
  - Soit en retournant, par valeur (pourquoi par valeur et non par référence?) une nouvelle matrice résultat allouée statiquement,
  - Soit en retournant, un pointeur sur une nouvelle matrice résultat allouée dynamiquement.
- Si l’on effectue une opération entre une matrice `A` de taille `M1` × `N1` et une matrice `B` de taille `M2` × `N2` et que les tailles ne correspondent pas, le résultat est une matrice de taille `max(M1, M2)` × `max(N1, N2)` où les Ai,j et Bi,j manquants ont été remplacés par des 0.
- Si les modules n des deux matrices ne correspondent pas, lever une exception de type `std::invalid_argument`.
- En cas de toute autre erreur, lever une exception de type `std::runtime_error`.
- Ne pas utiliser d’expression lambda.
- Votre code ne doit en aucune circonstance créer de fuite de mémoire, même dans le cas où l'allocation d'un tableau échoue (par exemple si `new[]` venait à lancer une exception).

### Remarques

- Attention au comportement de l'opérateur `%` en C++, en particulier pour les nombres négatifs.
- Prendre garde à ce que toute la mémoire allouée dynamiquement soit libérée correctement
  - Rappel: la **règle de cinq** stipule que si l'utilisateur a besoin d'un de ces cinq éléments alors il doit nécessairement définir tous les cinq:
     - le constructeur de copie
     - l'opérateur d'affectation `=` 
     - le destructeur
     - le constructeur par déplacement
     - l'opérateur d'affectation par déplacement
- Pour qu’une méthode supporte la **liaison dynamique** il faut qu’elle soit déclarée virtuelle (mot clé `virtual`).
- Prendre garde à ce que la construction d’une matrice résultat s’effectue correctement.
- Factoriser au maximum le code, en particulier celui commun aux différentes opérations logiques en utilisant des fonctions représentant l’opération à effectuer sur les élements des matrices opérandes et ceci sans utiliser de structures de contrôle.

## Exemple de génération de nombres aléatoires

```c++
#include <iostream>
#include <random>
 
int main()
{
    std::random_device rd;  // Sera utilisé pour obtenir une graine pour le moteur de nombres aléatoires
    std::mt19937 gen(rd()); // Mersenne_twister_engine initialisé avec rd()
    std::uniform_int_distribution<> distrib(1, 6);
 
    // Utilisez distrib pour transformer l'entier aléatoire généré par gen dans l'intervalle [1, 6]
    for (int n = 0; n != 10; ++n)
        std::cout << distrib(gen) << ' ';
    std::cout << '\n';
}
```

## Instructions

1. Implémenter cette classe.
2. Ecrire un programme prenant en argument les tailles `N1`, `M1`, `N2`, `M2` de deux matrices ainsi qu’un modulo `n` qui teste toutes les fonctionalités de cette classse et qui effectue les opérations sur une matrice N1 × M1 et N2 × M2 de manière à produire un résultat semblable à:

```
The modulus is 5

one
1 3 1 1
3 2 4 2
1 0 1 0

two
1 4 2 3 2
0 1 0 4 2
0 0 2 0 2

one + two
2 2 3 4 2
3 3 4 1 2
1 0 3 0 2

one - two
0 4 4 3 3
3 1 4 3 3
1 0 4 0 3

one x two
1 2 2 3 0
0 2 0 3 0
0 0 2 0 0
```
