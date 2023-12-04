# CPP-Project-BTS
projet de dev

Ce projet est un projet pour mon BTS SIO.
Je devais faire un projet à mon niveau dans un langage différent ou des specification plus avancées de ceux vu au cours de mon BTS.
On avais deja vu le C++ en cours mais j'ai appris par moi comment faire un jeu avec la librairie SFML.

# Le projet
Le projet est une simulation de communication entre un satellite et une station. Les 2 communicants doivent se connecter et peuvent s'envoyer des packets de données via le protocol TCP/IP.

On peut trouver 2 parties distinctes dans le projet:
- Construire et aménager une communication par TCP/IP
- Faire de l'affichage dynamique avec une librairie bas niveau

Egalement, il est aussi utile d'utiliser les Threads car la communication est asynchrone par rapport à l'affichage.
Un Thread est un moyen de séparer une fonction ou boucle généralement pour ne pas affecter et bloquer le processus principal.
