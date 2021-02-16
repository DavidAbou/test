## My_Sokoban


__Principe :__

> Déplacer les `X` dans les `O`, grace à une map composé de `#` pour les murs et de `P` pour les joueurs.

__Règles :__

> Les murs (`#`) doivent entourer entièrement la map sans aucuns trous. Il doit y avoir également autant de `X` que de `O`.

__Étapes :__

> 1. Convertir le fichier texte de la map en string.
> 2. Afficher la map dans la console.
> 3. Déplacer le curseur sur le `P`.
> 4. Implémenter un système de mouvement `UP`, `DOWN`, `LEFT`, `RIGHT`.
> 5. Quand `#` est en contacte avec `P`, ce dernier ne peut pas bouger dans la direction ou est situé le `P`.



**Exemple de map :**

```markdown
####################
#    X      P      #
#         O        #
#  X           O   #
####################
```
