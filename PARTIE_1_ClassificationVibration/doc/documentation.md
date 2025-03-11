# Documentation

## Partie 01 : Acquisition et Enregistrement des Données de Vibration

Ce projet utilise l'Arduino Nano 33 BLE Sense pour collecter des données de vibrations en temps réel à l'aide de son capteur embarqué **LSM9DS1**. L'objectif est de fournir des données exploitables pour l'entraînement d'un modèle d'intelligence artificielle en classification de vibrations.

### 1. Initialisation et Configuration du Capteur
Au démarrage du microcontrôleur, la communication avec le capteur de mouvements **LSM9DS1** est établie. Ce capteur intègre :
- **Un accéléromètre** qui mesure l'accélération linéaire sur les axes **X, Y et Z**.
- **Un gyroscope** qui mesure la vitesse angulaire sur ces mêmes axes.

Si l'initialisation échoue, le programme affiche un message d'erreur et s'interrompt pour éviter une collecte incorrecte des données.

### 2. Lecture des Données du Capteur
Le système effectue une **lecture continue** des mesures fournies par le capteur :
- **Accélération (⁠ax, ay, az⁠)** : exprimée en **g** (accélération terrestre), elle sert à détecter les variations de mouvement.
- **Vitesse angulaire (⁠gx, gy, gz⁠)** : exprimée en **degrés par seconde (°/s)**, elle fournit des informations sur la rotation du dispositif.

Avant chaque lecture, le programme vérifie la disponibilité de nouvelles mesures afin d'assurer l'intégrité des données collectées.

### 3. Enregistrement et Format des Données
Une fois les données extraites, elles sont transmises au **port série** sous forme de valeurs séparées par des virgules (**CSV**). Ce format facilite leur stockage et leur exploitation dans des logiciels d'analyse ou de machine learning.

Format des données :
ax, ay, az, gx, gy, gz, label

Où :
- ax, ay, az : accélération sur les axes X, Y, Z.
- gx, gy, gz : vitesse angulaire sur les axes X, Y, Z.
- **Label** : identifiant pour l'annotation des données en vue de l'entraînement d'un modèle de classification.

L'échantillonnage est réalisé **toutes les 100 millisecondes**, soit une **fréquence de 10 Hz**.

### 4. Collecte et Sauvegarde des Données avec Python
Un script Python est utilisé pour **collecter les données envoyées par l'Arduino via le port série** et les enregistrer sous forme de fichier **Excel**.

### Étapes du processus :
1. Connexion au **port série** avec une vitesse de transmission de **115200 bauds**.
2. Lecture continue des données envoyées par l'Arduino pendant une **durée définie** (ex: 30 secondes).
3. Vérification et stockage des données sous forme de **DataFrame Pandas**.
4. Sauvegarde des mesures sous un **fichier Excel (`donnees_vibrations.xlsx`)** pour une analyse ultérieure.

## Partie 02 : Apprentissage de modèle d'IA

### 1.Introduction
Après avoir collecté les données de vibration dans la première partie, nous abordons ici la phase d’apprentissage. L'objectif est de construire un modèle capable de classer les signaux de vibration en deux catégories : vibration de téléphone et vibration de machine à laver. Pour cela, nous avons utilisé TensorFlow et Keras afin de développer un réseau de neurones dense adapté à notre problème de classification.

### 2.Prétraitement des Données
Avant l'entraînement, les données ont été prétraitées pour assurer une meilleure convergence du modèle. Les étapes comprennent :

Normalisation : Les données ont été mises à l'échelle grâce à un StandardScaler, garantissant une distribution centrée et homogène.
Séparation des données : Le dataset a été divisé en un ensemble d'entraînement (90 %) et de test (10 %) afin d'évaluer la performance du modèle sur des données non vues.
Transformation des données : Les caractéristiques extraites du signal (éventuellement issues d’analyses temporelles ou fréquentielles) sont transformées pour être compatibles avec le modèle.

### 2.Architecture du Modèle
Le modèle de classification est un réseau de neurones dense structuré de la manière suivante :

Couche d'entrée : Accepte en entrée les caractéristiques prétraitées (nombre de features déterminé par le dataset).
Deux couches cachées : Chacune composée de 16 neurones et utilisant l'activation ReLU pour capter des relations non linéaires.
Couche intermédiaire : Une couche dense de 8 neurones pour raffiner l'extraction des caractéristiques.
Couche de sortie : Une unique neurone avec une activation sigmoïde pour la classification binaire.
Le modèle est compilé avec l’optimiseur Adam et la fonction de perte binary_crossentropy. Il a été entraîné sur 50 epochs avec une taille de batch de 20.

### 3.Résultats et Visualisation
Évolution de la Loss
Les résultats d'entraînement indiquent une diminution progressive de la loss, illustrant une bonne convergence du modèle. Le graphique ci-dessous montre l'évolution de la loss sur les 50 epochs :
![image](https://github.com/user-attachments/assets/53b38d84-0874-412e-9773-0243ec03f4d6)


### 4.Performance du Modèle
À l'issue de l'entraînement, le modèle a atteint :
Test Loss : 0.0289
Test Accuracy : 98.25%
Ces résultats démontrent que le modèle est capable de bien généraliser sur des données non vues, indiquant que les caractéristiques extraites sont pertinentes pour différencier les vibrations de téléphone et de machine à laver.

A la fin de l'apprentissage on a ajouté une partie qui fait l'extraction du model en format .h pour l'implémentation dans la carte Arduino.

## Partie 03 : Implémentation du modèle dans la carte

Dans cette partie, nous implémente le modèle dans la carte et on fait des tests, voici les résultats obtenus: 
![Capture d’écran (1113) (2)](https://github.com/user-attachments/assets/3a00e09f-39a5-42e3-a7d9-7841c2edf813)

## Propositions pour les Travaux Futurs
Optimisation du modèle pour réduire l’empreinte mémoire et améliorer la rapidité d’exécution.
Augmentation de la fréquence d’échantillonnage et ajout d'autres capteurs pour enrichir les données.
Extension du dataset avec de nouvelles catégories de vibrations pour améliorer la robustesse du modèle.
Développement d’une interface en temps réel pour la visualisation et l’analyse des vibrations.
Intégration avec des systèmes de surveillance industrielle ou de maintenance prédictive.


## Conclusion
Ce projet a démontré la faisabilité de l’implémentation d’un modèle de classification de vibrations sur un microcontrôleur embarqué. Grâce à l’utilisation de l’Arduino Nano 33 BLE Sense et TensorFlow Lite, nous avons pu collecter, traiter et classifier efficacement les données vibratoires. Les résultats obtenus confirment la pertinence de cette approche, ouvrant ainsi la voie à des applications industrielles et embarquées.
