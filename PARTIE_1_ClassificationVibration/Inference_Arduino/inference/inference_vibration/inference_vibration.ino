#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#include "model.h"  


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

  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  
  
  Serial.println("Accelerometer initialized");

  
  tflModel = tflite::GetModel(model);  
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }

  
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);
  
  
  tflInterpreter->AllocateTensors();
  
  
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}

void loop() {
  
  float aX, aY, aZ;

  
  if (IMU.accelerationAvailable()) {
    
    IMU.readAcceleration(aX, aY, aZ);

    
    Serial.print("aX: ");
    Serial.print(aX);
    Serial.print("\t");
    Serial.print("aY: ");
    Serial.print(aY);
    Serial.print("\t");
    Serial.print("aZ: ");
    Serial.println(aZ);

    
    tflInputTensor->data.f[0] = (aX + 4.0) / 8.0;  
    tflInputTensor->data.f[1] = (aY + 4.0) / 8.0;  
    tflInputTensor->data.f[2] = (aZ + 4.0) / 8.0;  

    
    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) {
      Serial.println("Invoke failed!");
      while (1);
    }

    
    float prediction = tflOutputTensor->data.f[0];  // Assuming binary output (0 or 1)

    
    if (prediction > 0.5) {
      
      Serial.println("Vibration de machine a laver");
    } else {
      
      Serial.println("Vibration de Téléphone");
    }
  }

  
  delay(500);
}
