#include <Arduino.h>
#include "config.h"
#include "global_var.h"

typedef struct {
	uint8_t pin;
  TickType_t delay;
} ledParameter_t;

void toggleLED(void *pinParameter) // Faz a leitura do sinal Analogico
{
  const ledParameter_t ledParameter = *(ledParameter_t *) pinParameter;
  for (;;)
  {
    digitalWrite(2, !digitalRead(2));
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void analogReadFunc(void *parameters) // Faz a leitura do sinal Analogico
{
  for (;;)
  {
    unsigned int amplitude = (unsigned int)(1000.0 * ((float)analogRead(ANALOGPIN)) / 1023.0);
    //Serial.println(amplitude);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  pinMode(LEDPIN1, OUTPUT);
  pinMode(ANALOGPIN, INPUT);
  //Serial.begin(9600);
  ledParameter_t led = {LEDPIN1, 1000};
  xTaskCreate(
      toggleLED, // Function name
      "Task 1", // Task name
      1000,     // Stack size
      &led,   // Task parameters
      1,        // Task priority
      NULL      // Task handle
  );
  xTaskCreate(
      analogReadFunc, // Function name
      "Task 2",       // Task name
      1000,           // Stack size
      NULL,           // Task parameters
      1,              // Task priority
      NULL            // Task handle
  );
}

void loop() {}