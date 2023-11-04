# Projet Capteur AHT20

## Description
Ce projet utilise Zephyr RTOS et le SDK Nordic Semiconductor pour interagir avec le capteur AHT20 via une communication I2C. Le capteur mesure l'humidité relative et la température, puis affiche ces données. Il est destiné à une utilisation sur la carte nRF7002DK équipée d'un nRF5340 SoC.

## Auteur
Yvan Tankeu

## Version du SDK Nordic Semiconductor
v2.4.99-dev2

## Langage de Programmation
C

## Prérequis
- Zephyr RTOS
- SDK Nordic Semiconductor

## Configuration
Pour installer les outils nécessaires, suivez les guides de [NRF Connect Fundamentals](https://shorturl.at/grKM7) pour une installation correcte du SDK Nordic Semiconductor et des bibliothèques Zephyr RTOS.
## Compilation et Exécution
1. Clonez ce dépôt.
2. Configurez le projet pour votre carte en utilisant les outils Zephyr.
3. Compilez le projet.
4. Flash le binaire sur la carte.
5. Exécutez le projet.

## Fonctionnalités
- Initialisation de la communication I2C.
- Réinitialisation du capteur AHT20.
- Calibration du capteur AHT20.
- Déclenchement d'une mesure du capteur AHT20.
- Lecture des données du capteur AHT20 et conversion en humidité et température.
  
## Branchement du Circuit
Assurez-vous de suivre ces étapes pour connecter correctement les composants du circuit :

Toutes les Broches de votre carte peuvent servir de SCL et SDA, il faut juste préciser les broches à utiliser dans votre overlay.dt sinon par défaut c'est la broche P1.03 pour la SDA et P1.02 pour SCL

![1541 pastedimage1698221179473v1](https://github.com/YvanTankeu/nrf7002dk-aht20-sensor/assets/25055874/f0d6f3b2-fb41-4497-be2f-6beac3cb8a53)

Avant de commencer, il est essentiel de vérifier les conditions de fonctionnement des capteurs par rapport à la carte de développement (DK) que vous utilisez. 
Il est important de noter que le capteur a une tension de fonctionnement minimale (2,2 V) supérieure à la tension fournie par les broches de la carte nRF7002DK (1,8 V) par défaut, 
ce qui signifie qu'ils ne sont pas compatibles sans modifications (ce qui est également indiqué dans les spécifications de la nRF7002DK).

Pour résoudre ce problème, vous pouvez utiliser la broche VIO_ref pour réguler la tension sur la carte nRF7002DK. 
Cela modifiera la tension sur la broche VDD de 1,8 V à la tension que vous avez sur VIO_ref du nRF5340 et IOVDD de la nRF7002. 

Comme indiqué dans le schéma ci-dessous, il est essentiel de noter que le capteur est connecté à la broche 5 V, plutôt qu'à VDD (1,8 V). Vous devrez donc disposer d'une alimentation externe supplémentaire pour alimenter le capteur AHT20 Adafruit de cette manière. Au lieu d'appliquer une tension externe, 
vous pouvez utiliser la broche VBAT MEAS. Veuillez noter que ceci est une solution, bien que ce ne soit pas une pratique courante, et vous devez vous assurer que cela correspond à vos besoins.

![pastedimage1698151993189v1 png-640x480](https://github.com/YvanTankeu/nrf7002dk-aht20-sensor/assets/25055874/c268d86f-bbf7-4be2-ac40-82f8c1a7bce0)

PS: Si vous n'avez pas de PSU vous pouvez connecter le vin de votre module adafruit a la broche VBAT MEANS de votre carte, je me suis rendu compte qu'elle fourni 3.3V et c'est suffisant pour alimenter le capteur
1. Connectez la carte nRF7002DK à votre ordinateur à l'aide de l'adaptateur USB fourni.

2. Utilisez le câble de connexion USB pour établir une connexion entre la carte nRF7002DK et votre ordinateur.

3. Assurez-vous que l'alimentation de la carte est correctement branchée.
   
## Résultat
Apres le televersement

![image](https://github.com/YvanTankeu/nrf7002dk-aht20-sensor/assets/25055874/2d9ea534-c354-4925-92d6-c7956184187f)

Moniteur serie

![image](https://github.com/YvanTankeu/nrf7002dk-aht20-sensor/assets/25055874/86d98410-4c16-4e5a-8de9-e5ddb96db58d)


### Réseaux 
- [Discord](https://discord.com/users/yvantankeu)
- [LinkedIn](https://www.linkedin.com/in/yvan-tankeu-ab029a129/)



