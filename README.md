# Projet Tiny Machine Learning

![DALL·E 2025-03-10 22 07 28 - A futuristic TinyML project setup featuring an Arduino Nano 33 BLE sensing vibrations with a small accelerometer module  Next to it, a compact camera ](https://github.com/user-attachments/assets/d65caabb-3160-4357-8bb6-755100cd6fbe)

## Introduction
Ce projet explore deux partie, la premiere consiste a l'utilisation du TinyML pour la classification des vibrations et la deuxieme partie pour la classification des composants électroniques. Il repose sur l'Arduino Nano 33 BLE et TensorFlow Lite pour la détection en temps réel des vibrations, ainsi que sur une caméra et Node-RED pour l'identification des composants électroniques.

## Structure du Projet

### 1. Classification des Vibrations avec Arduino Nano 33 BLE et TensorFlow Lite
L'objectif est d'exploiter l'IMU (Inertial Measurement Unit) de l'Arduino Nano 33 BLE pour collecter des données de vibrations, entraîner un modèle de machine learning capable de reconnaître différents types de vibrations, et l'intégrer sur l'Arduino pour une classification en temps réel.

#### Étapes principales :
- Acquisition et prétraitement des données de vibrations.
- Entraînement d'un modèle avec TensorFlow Lite.
- Déploiement du modèle sur l'Arduino Nano 33 BLE.
- Classification des vibrations en temps réel.

### 2. Classification des Composants avec Caméra et Node-RED
Cette partie du projet vise à capturer des images de composants électroniques, les classifier à l'aide d'un modèle pré-entraîné, puis envoyer les résultats vers Node-RED pour une automatisation avancée.

#### Étapes principales :
- Capture d'images des composants électroniques.
- Classification des composants avec un modèle de vision par ordinateur.
- Intégration avec Node-RED pour le traitement et la gestion des données.

## Objectifs
- **Détecter et classifier différentes vibrations** en temps réel avec Arduino Nano 33 BLE et TensorFlow Lite.
- **Reconnaître et identifier des composants électroniques** via une caméra et un modèle de classification d’images.
- 
## Technologies Utilisées
- **Arduino Nano 33 BLE** pour la collecte des vibrations.
- **TensorFlow Lite** pour l'entraînement et le déploiement du modèle de classification.
- **Caméra** pour la capture d'images des composants.
- **IMU** Inertial Measurement Unit

Ce projet combine l'IA avce les système embarqués pour développer un système intelligent de classification en temps réel.
