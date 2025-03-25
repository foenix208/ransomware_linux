# Projet d'Étude : Ransomware en C

Ce projet implémente un ransomware simple en langage C. Le programme parcourt les fichiers d'un répertoire donné et chiffre leur contenu à l'aide d'une clé spécifique. Les fichiers chiffrés sont renommés avec l'extension `.NorVoxx`, et l'original est supprimé après le chiffrement.

## Description du Projet

Le programme fonctionne en deux étapes principales :

1. **Chiffrement des fichiers** : Le programme ouvre chaque fichier dans un répertoire spécifié, le lit, et applique une opération de chiffrement (opération XOR) à l'aide d'une clé fixe. Les fichiers chiffrés sont ensuite sauvegardés sous un nouveau nom avec l'extension `.NorVoxx`.
   
2. **Parcours des répertoires** : Le programme parcourt de manière récursive tous les fichiers et sous-répertoires du répertoire de départ (ici `./toto/`) et applique le chiffrement à chaque fichier trouvé.

Le code utilise la bibliothèque standard POSIX pour manipuler les fichiers et répertoires (en particulier `dirent.h` et les fonctions associées).

## Prérequis

- **Compilateur C** : GCC (ou un compilateur compatible C).
- **Système d'exploitation** : Linux (le programme utilise des fonctions spécifiques à POSIX).
- **Permissions** : Le programme doit être exécuté avec des privilèges suffisants pour accéder et modifier les fichiers dans les répertoires ciblés.

## Installation

1. Clonez le projet depuis le dépôt ou copiez le code dans un fichier source (par exemple `ransomware.c`).
   
2. Compilez le programme avec la commande suivante :
   
   ```bash
   gcc -o ransomware ransomware.c
   ```

3. Exécutez le programme sur un répertoire de test (par exemple `./toto/`).
   
   ```bash
   ./ransomware
   ```

   **Important** : Utilisez un répertoire de test car ce programme modifiera les fichiers en les chiffrant et en supprimant les originaux.

## Fonctionnement du Code

### `fichier_cryp(char *path, char *file, int key)`

Cette fonction chiffre un fichier individuel en utilisant une clé XOR. Le fichier est ouvert en mode binaire, puis chaque byte du fichier est XORé avec la clé. Le fichier chiffré est ensuite sauvegardé avec l'extension `.NorVoxx`. Après cela, le fichier original est supprimé.

### `fichier_liste(char *path)`

Cette fonction parcourt récursivement tous les fichiers et sous-répertoires du répertoire spécifié. Pour chaque fichier trouvé, elle appelle `fichier_cryp` pour le chiffrer. Les sous-répertoires sont également explorés de manière récursive, mais certains répertoires tels que `..`, `.`, et `proc` sont ignorés.

### `main()`

La fonction principale initialise l'exécution en appelant `fichier_liste` avec le répertoire de départ `./toto/`. Ce répertoire peut être remplacé par n'importe quel autre répertoire de votre choix. 

## Remarques

- **Sécurité** : Ce programme est uniquement à des fins éducatives. Utilisez-le uniquement dans des environnements contrôlés et sur des répertoires de test. Ne l'exécutez pas sur des systèmes ou des données sensibles.
  
- **Comportement du programme** : Une fois que les fichiers sont chiffrés, il n'est pas possible de les restaurer à leur état original sans la clé de chiffrement.

- **Performance** : Le programme peut prendre du temps à s'exécuter en fonction du nombre de fichiers et de la taille des répertoires.

## Avertissement

Ce programme imite le comportement d'un ransomware. Il est important de noter que le but de ce projet est exclusivement éducatif et ne doit pas être utilisé à des fins malveillantes. Le chiffrement des fichiers sans consentement est illégal et contraire à l'éthique.

---
