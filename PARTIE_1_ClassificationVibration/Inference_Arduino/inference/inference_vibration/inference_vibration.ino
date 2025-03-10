#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#include "model.h"   // Importation du modèle TFLite

constexpr int tensorArenaSize = 8 * 1024;  
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

tflite::MicroErrorReporter tflErrorReporter;
tflite::AllOpsResolver tflOpsResolver;
const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

const float threshold = 0.8;  

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialisation de l'IMU (accéléromètre)
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("Accelerometer initialized");

  // Chargement du modèle TFLite
  tflModel = tflite::GetModel(model);  
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }

  // Création de l'interpréteur pour le modèle
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);
  
  // Allocation de la mémoire pour les tensors
  tflInterpreter->AllocateTensors();
  
  // Récupération des pointeurs d'entrée et de sortie
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() {
  float aX, aY, aZ;
  float gyroX, gyroY, gyroZ;

  // Vérification de la disponibilité des données d'accélération et de gyroscope
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    
    // Lecture des valeurs d'accélération et de gyroscope
    IMU.readAcceleration(aX, aY, aZ);
    IMU.readGyroscope(gyroX, gyroY, gyroZ);

    // Affichage des valeurs pour débogage
    Serial.print("aX: ");
    Serial.print(aX);
    Serial.print("\t");
    Serial.print("aY: ");
    Serial.print(aY);
    Serial.print("\t");
    Serial.print("aZ: ");
    Serial.print(aZ);
    Serial.print("\t");
    Serial.print("gyroX: ");
    Serial.print(gyroX);
    Serial.print("\t");
    Serial.print("gyroY: ");
    Serial.print(gyroY);
    Serial.print("\t");
    Serial.print("gyroZ: ");
    Serial.println(gyroZ);

    // Normalisation des données pour correspondre à l'échelle attendue par le modèle
    tflInputTensor->data.f[0] = (aX + 4.0) / 8.0;  
    tflInputTensor->data.f[1] = (aY + 4.0) / 8.0;  
    tflInputTensor->data.f[2] = (aZ + 4.0) / 8.0;  
    tflInputTensor->data.f[3] = (gyroX + 500.0) / 1000.0;  
    tflInputTensor->data.f[4] = (gyroY + 500.0) / 1000.0;  
    tflInputTensor->data.f[5] = (gyroZ + 500.0) / 1000.0;  

    // Exécution de l'inférence
    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) {
      Serial.println("Invoke failed!");
      while (1);
    }

    // Récupération de la prédiction
    float prediction = tflOutputTensor->data.f[0];  // La sortie est binaire

    // Affichage du résultat de la prédiction
    if (prediction > threshold) {
      Serial.println("Orientation: Vertical (1)");
    } else {
      Serial.println("Orientation: Horizontal (0)");
    }
  }

  delay(500);
}
