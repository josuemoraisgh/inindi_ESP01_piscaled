#include <Arduino.h>
#include "config.h"
#include "global_var.h"

typedef struct
{
  uint8_t pin;
  TickType_t delay;
} ledParameter_t;

void toggleLED(void *pinParameter) // Faz a mudança de estado de um led
{
  const ledParameter_t ledParameter = *(ledParameter_t *) pinParameter;
  for (;;)
  {
    digitalWrite(ledParameter.pin, !digitalRead(ledParameter.pin));
    vTaskDelay(ledParameter.delay / portTICK_PERIOD_MS);
  }
}

void analogReadFunc(void *parameters) // Faz a leitura do sinal Analógico
{
  double timeStamp = 0;
  for (;;)
  {
    unsigned int amplitude = (unsigned int)(1000.0 * ((float)analogRead(ANALOGPIN)) / 1023.0);
    timeStamp++;
    Serial.print(">onda:");
    Serial.print(timeStamp);
    Serial.print(":");
    Serial.print(amplitude);
    Serial.println("§Volts|g");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  pinMode(LEDPIN1, OUTPUT);
  pinMode(LEDPIN2, OUTPUT);
  pinMode(ANALOGPIN, INPUT);
  Serial.begin(115200);
  Serial.println("Starting serial...");  
  ledParameter_t led1 = {LEDPIN1, 500};
  xTaskCreate(
      toggleLED,   // Function name
      "Task LED1", // Task name
      1000,        // Stack size
      &led1,       // Task parameters
      1,           // Task priority
      NULL         // Task handle
  );
  ledParameter_t led2 = {LEDPIN2, 1000};
  xTaskCreate(
      toggleLED,   // Function name
      "Task LED2", // Task name
      1000,        // Stack size
      &led2,       // Task parameters
      1,           // Task priority
      NULL         // Task handle
  );
  xTaskCreate(
      analogReadFunc, // Function name
      "Task Analog",  // Task name
      1000,           // Stack size
      NULL,           // Task parameters
      1,              // Task priority
      NULL            // Task handle
  );
}
float i = 0;

void loop()
{
  i += 0.1;

  // Print log
  Serial.print("casa");
  Serial.println(i);

  // Plot a sinus
  Serial.print(">sin:");
  Serial.println(sin(i));

  // Plot a cosinus
  Serial.print(">Sum:");
  Serial.println(0.8 * sin(i) + 0.2 * cos(i));

  delay(50);
}