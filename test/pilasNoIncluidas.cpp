#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin donde está conectado el sensor LM35.
#define rx A5

bool b = 0;
uint16_t temp1_0 = 0;
uint16_t temp1_1 = 0;

uint8_t volt = 0;
uint8_t volt_med = 0;
float temp = 0;

void setup(){
    // Inicialización del puerto serie.
  Serial.begin(9600);
  Serial.println("\n");
  Serial.println("Temperature Proyect");
  Serial.println("\n");

  // Inicialización de la pantalla OLED.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al iniciar la pantalla OLED"));
    while(true);
  }
  display.clearDisplay();

  pinMode(rx, INPUT);
  pinMode(3, OUTPUT);
  analogReference(INTERNAL);

}

void transmitir(){

  volt = analogRead(rx);
  volt_med = volt;
  volt = 0;
  temp = volt_med * 1100.0 / 10240.0;
  Serial.print(temp);
  Serial.print("\n");
  Serial.print(volt_med);
  Serial.print("\n");

  for(int i = 0; i < 8; i++){
    b = bitRead(volt_med, i);

    if(b){
      digitalWrite(3, HIGH);
    } else {
      digitalWrite(3, LOW);
    }
  }

  // Mostrar la temperatura en la pantalla OLED.

  delay(500); // Esperar medio segundo antes de la próxima lectura.
}

void loop(){
  transmitir();
}
