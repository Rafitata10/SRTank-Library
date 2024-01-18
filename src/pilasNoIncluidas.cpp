#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Pin donde está conectado el sensor DS18B20.
const int oneWireBus = 2;

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

void setup(){
  // Inicialización de la pantalla OLED.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al iniciar la pantalla OLED"));
    while(true);
  }

  // Inicialización del sensor DS18B20.
  sensors.begin();
}

void loop(){
  // Lectura de la temperatura desde el sensor DS18B20.
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);

  // Mostrar la temperatura en la pantalla OLED.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Temperatura: "));
  display.print(temperatura, 1);
  display.print(F(" C"));
  display.display();

  delay(1000); // Esperar un segundo antes de la próxima lectura.
}
