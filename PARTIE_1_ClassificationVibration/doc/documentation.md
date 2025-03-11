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
- `ax, ay, az` : accélération sur les axes X, Y, Z.
- `gx, gy, gz` : vitesse angulaire sur les axes X, Y, Z.
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
