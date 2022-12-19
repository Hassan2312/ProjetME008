Bonsoir!
Pour compiler notre programme utiliser GCC sur Linux de preference avec gnuplot installé

Explicite.c:

gcc Explicite.c -lm
.\a.out

Dans notre code on utilise des scripts gnuplot (dans le dossier Script)
Pour cela il faut executer avec le dossier Script dans le meme repertoire que le a.out

Ce fichier contient tout les elements de reponse pour repondre a la partie I du projet
Tout d'abord on vous demandera de choisir quel type de conditions pour les bords
Il faut saisir 1 ou 2 ou 3 (précisé dans l'affichage)

Par défaut l'execution de ce programme va faire deux choses:
1) Afficher les vecteurs u a t=200 pour des dt allant de 1*dt a 22*dt (dt instable a partir de 21*dt)
2) Automatiquement tracer et afficher les graphes
Un premier graphe pour les instants, un deuxième pour les positions et un troisième pour la norme2 en fonction de dt (voir rapport/Convergence)
Il faut appuyer sur une touche dans le terminal pour les faire défiler

On peut facilement modifier les instants à tracer et les positions fixes à calculer en modifiant "list_t[]" et "list_x[]" dans le main()
Vous pouvez insérer 5 instants et positions différentes
Pour plus ou moins de points, il ne faut pas oublier de modifier les valeurs de "length" dans "save_instant_T" et "save_position_x".

Implicite.c:

gcc implicite.c -lm
.\a.out

Ce fichier contient tout les elements de reponse pour repondre a la partie II du projet. Vous pouvez modifier le dt directement dans le main().
Son execution affiche le vecteur u a t=200
