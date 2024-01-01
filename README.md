# TP de statistiques pour l'image
![MORE GLOWSTONE](./glowstone_128.png) ![MORE CELLS](./cells_128.png)
Textures générés via les patrons suivants
![Glowstone](./glowstone.png) ![Cells](./cells.png)

## Génération de textures procédurale

- Etirement et génération de variation de textures (marche mieux avec du stochastique ou du near stochatique) via Efros Leung.
- Accélération de l'algorithme via une bounding box pour vérifier les pixels a traiter
- Utilisation d'OpenCV pour charger les images dans des tableaux.
- Utilisation d'OpenMP pour paralléliser certaines parties.

## Entrainement d'un classifieur KMEAN

- Implémentation d'un KMean générique à N dimensions
- Entrainement sur les données de ![Brodatz colorée](https://multibandtexture.recherche.usherbrooke.ca/colored%20_brodatz.html) découpée en patch avec des gradients d'histogramme.
- ça reste un kmean, on est a 50% d'accuracy, c'est pas si mal mais en fonction de la ou on est sur le patch etc, les textures ont d'énorme variation, et ça devient soit dur d'avoir assez de patch si on augmente la taille des patchs, soit dur d'avoir tout les patterns d'une texture.

(Conclusion faudrait implementer un meilleur classifieur, mais pas le but/ le temps dans le cadre de ce tp) 
