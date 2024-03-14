#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define rx 3

bool b = 0;

uint8_t volt = 0;
float temp = 0;

void setup(){
  // Inicialización del puerto serie.
  Serial.begin(9600);

  // Inicialización de la pantalla OLED.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Error al iniciar la pantalla OLED"));
    while(true);
  }
  display.clearDisplay();

  pinMode(rx, INPUT);
}

void recibir(){
  if(digitalRead(rx)){
    Serial.println("REPOSO");

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("REPOSO");
    display.setTextSize(2);
    display.setCursor(0,32);
    display.print(volt);
    display.setCursor(50, 32);
    temp = volt/255.0 * 50.0;
    display.print(temp);
    display.setCursor(110,32);
    display.print("C");
    display.display();
  } else {
    delay(250);
    display.clearDisplay();
    if(!digitalRead(rx)){
      for(int i = 0; i < 8; i++){
        delay(500);
        b = digitalRead(rx);
        bitWrite(volt, i, b);
        Serial.println(b);

        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(0,0);
        display.print("RECIBIENDO");
        display.setTextSize(2);
        display.setCursor(i*10, 32);
        display.print(b);
        display.display();
      }
    }
  }
}

void loop(){
  recibir();
}
