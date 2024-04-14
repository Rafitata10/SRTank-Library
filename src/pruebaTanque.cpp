/*
  * Rafael Ramírez Salas
  * Ingeniería de Computadores, Universidad de Málaga
  * Trabajo de Fin de Grado 2024: Fail Tolerant DualNano
*/

#include <Arduino.h>
#include <SRTank.h>

unsigned int initialValue = 125;

void initSRTank(){
    // Initialize serial communication.
    Serial.begin(19200);
    
    // Synchronize communication with the simulator.
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
}

void setup(){
    // Initialize the tank.
    initSRTank();

    // Initialize the tank alarm temperature.
    tank.setMaxTemperatureAlarm(initialValue);
}

void loop(){
    delay(2000); // Wait for 2 seconds.

    /* Keep the volume value.
    tank.setVolume();
    // Keep the temperature value.
    tank.setTemperature();
    // Keep the highFloater value.
    tank.setHighFloater();
    // Keep the lowFloater value.
    tank.setLowFloater();
    // Keep the maxTemperature value.
    tank.setMaxTemperature();
    // Keep the minTemperature value.
    tank.setMinTemperature();*/

    Serial.print("Volume: ");
    Serial.println(tank.getVolume());

    Serial.print("Temperature: ");
    Serial.println(tank.getTemperature());

    delay(1500); // Wait for 1.5 seconds.
    
    tank.fillTank(500); // Fill the tank.

    tank.heatTank(33); // Heat the tank.

    delay(2500); // Wait for 2.5 seconds.

    Serial.print("Volume: ");
    Serial.println(tank.getVolume());

    Serial.print("Temperature: ");
    Serial.println(tank.getTemperature());
}

// Path: src/DataLecture.cpp
