import serial
import pandas as pd
import time

# Communivation série
port = "COM3"  
baudrate = 115200
ser = serial.Serial(port, baudrate, timeout=1)


data = []

duree_acquisition = 30  
temps_debut = time.time()

print("Acquisition en cours...")

# La collection pendant 30 s
while time.time() - temps_debut < duree_acquisition:
    ligne = ser.readline().decode('utf-8').strip()
    if ligne:
        valeurs = ligne.split(',')
        if len(valeurs) == 7:  
            data.append(valeurs)

# Fermer la connexion série
ser.close()


df = pd.DataFrame(data, columns=['Acc_X', 'Acc_Y', 'Acc_Z', 'Gyro_X', 'Gyro_Y', 'Gyro_Z', 'Label'])
df.to_excel("donnees_vibrations.xlsx", index=False)

print("Collection terminée.")
