#include <Arduino.h>

// Configuración de pines para el LCD
const int rs = 12;
const int en = 11;
const int d0 = 0;
const int d1 = 1;
const int d2 = 2;
const int d3 = 3;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int prueba8 = 8;
const int prueba9 = 9;

void LCD_command(byte command) {
  digitalWrite(rs, LOW);
  delayMicroseconds(1000);
  digitalWrite(en, HIGH);
  delayMicroseconds(1000);
  
  digitalWrite(d0, (command >> 0) & 0x01);
  digitalWrite(d1, (command >> 1) & 0x01);
  digitalWrite(d2, (command >> 2) & 0x01);
  digitalWrite(d3, (command >> 3) & 0x01);
  digitalWrite(d4, (command >> 4) & 0x01);
  digitalWrite(d5, (command >> 5) & 0x01);
  digitalWrite(d6, (command >> 6) & 0x01);
  digitalWrite(d7, (command >> 7) & 0x01);

  delayMicroseconds(1000);
  digitalWrite(en, LOW);
  delayMicroseconds(1000);
}

void LCD_data(byte data) {
  digitalWrite(rs, HIGH);
  delayMicroseconds(1000);
  digitalWrite(en, HIGH);
  delayMicroseconds(1000);

  digitalWrite(d0, (data >> 0) & 0x01);
  digitalWrite(d1, (data >> 1) & 0x01);
  digitalWrite(d2, (data >> 2) & 0x01);
  digitalWrite(d3, (data >> 3) & 0x01);
  digitalWrite(d4, (data >> 4) & 0x01);
  digitalWrite(d5, (data >> 5) & 0x01);
  digitalWrite(d6, (data >> 6) & 0x01);
  digitalWrite(d7, (data >> 7) & 0x01);

  delayMicroseconds(1000);
  digitalWrite(en, LOW);
  delayMicroseconds(1000);
}

void setup() {
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  pinMode(prueba8, OUTPUT);
  pinMode(prueba9, OUTPUT);

  delay(15);
  LCD_command(0x38); // Configuración: 8 bits, 2 líneas, fuente 5x8
  delayMicroseconds(100);
  LCD_command(0x0C); // Mostrar el cursor (0x0C para apagar el cursor, 0x0E para encender)
  delayMicroseconds(100);
  LCD_command(0x01); // Limpiar la pantalla
  delay(3);
  LCD_command(0x06); // Desplazamiento automático de la pantalla hacia la derecha después de escribir
  delay(3);

  digitalWrite(prueba8, HIGH);

  LCD_data('H');
  LCD_data('e');
  LCD_data('l');
  LCD_data('l');
  LCD_data('o');
  LCD_data(' ');
  LCD_data('A');
  LCD_data('r');
  LCD_data('d');
  LCD_data('u');
  LCD_data('i');
  LCD_data('n');
  LCD_data('o');

  LCD_command(0xC0);
  
  LCD_data('C');
  LCD_data('o');
  LCD_data('n');
  LCD_data('c');
  LCD_data('o');
  LCD_data('r');
  LCD_data('d');
  LCD_data('e');
  LCD_data('!');
  LCD_data('!');
  digitalWrite(prueba9, HIGH);
}

void loop() {
  // El programa principal no realiza ninguna acción en este ejemplo
}