// Rafael Ramírez Salas
// Ingeniería de Computadores, Universidad de Málaga
// Trabajo de Fin de Grado 2024: Fail Tolerant DualNano

#include "SRTank.h"

SRTank tank;

// Constructor.
SRTank::SRTank() : highFloater(0), lowFloater(0), minTemperature(0), maxTemperature(0), volume(0), temperature(0) {
    ;
}

// --------------------- Getters para los outputs digitales ---------------------

unsigned char SRTank::getHighFloater(){
    // Request the simulator to measure highFloater.
    Serial.write(_HIGH_FLOATER);
    while(!Serial.available());
    highFloater = Serial.read();
    return highFloater;
}

unsigned char SRTank::getLowFloater(){
    // Request the simulator to measure lowFloater.
    Serial.write(_LOW_FLOATER);
    while(!Serial.available());
    lowFloater = Serial.read();
    return lowFloater;
}

unsigned char SRTank::getMaxTemperature(){
    // Request the simulator to measure minTemperature.
    Serial.write(_MAX_TEMP);
    while(!Serial.available());
    maxTemperature = Serial.read();
    return maxTemperature;
}

unsigned char SRTank::getMinTemperature(){
    // Request the simulator to measure minTemperature.
    Serial.write(_MIN_TEMP);
    while(!Serial.available());
    minTemperature = Serial.read();
    return minTemperature;
}

// --------------------- Getters para los outputs analógicos ---------------------

unsigned int SRTank::getVolume(){
    // Request the simulator to measure volume.
    Serial.write(_VOLUME);
    while(!Serial.available());
    valueH = Serial.read();
    while(!Serial.available());
    valueL = Serial.read();
    volume = (valueH << 8) | valueL;
    return volume;
}
unsigned int SRTank::getTemperature(){
    // Request the simulator to measure temperature.
    Serial.write(_TEMP);
    while(!Serial.available());
    valueH = Serial.read();
    while(!Serial.available());
    valueL = Serial.read();
    temperature = (valueH << 8) | valueL;
    return temperature;
}

// --------------------- Setters para los outputs digitales ---------------------

// Function to keep volume value.
void SRTank::setVolume(void){
    // Request the simulator to measure volume.
    Serial.write(_VOLUME);
    while(!Serial.available());
    valueH = Serial.read();
    while(!Serial.available());
    valueL = Serial.read();
    volume = (valueH << 8) | valueL;
}

// Function to keep temperature value.
void SRTank::setTemperature(void){    
    // Request the simulator to measure temperature.
    Serial.write(_TEMP);
    while(!Serial.available());
    valueH = Serial.read();
    while(!Serial.available());
    valueL = Serial.read();
    temperature = (valueH << 8) | valueL;
}

// Function to keep highFloater value.
void SRTank::setHighFloater(void){    
    // Request the simulator to measure highFloater.
    Serial.write(_HIGH_FLOATER);
    while(!Serial.available());
    highFloater = Serial.read();
}

// Function to keep lowFloater value.
void SRTank::setLowFloater(void){    
    // Request the simulator to measure lowFloater.
    Serial.write(_LOW_FLOATER);
    while(!Serial.available());
    lowFloater = Serial.read();
}

// Function to keep maxTemperature value.
void SRTank::setMaxTemperature(void){    
    // Request the simulator to measure maxTemperature.
    Serial.write(_MAX_TEMP);
    while(!Serial.available());
    maxTemperature = Serial.read();
}

// Function to keep minTemperature value.
void SRTank::setMinTemperature(void){    
    // Request the simulator to measure minTemperature.
    Serial.write(_MIN_TEMP);
    while(!Serial.available());
    minTemperature = Serial.read();
}

// --------------------- Functions with digital outputs ---------------------

// Function to open the inlet valve.
void SRTank::openInletValve(void){
    Serial.write(_INPUT_VALVE);
    Serial.write(_TURN_ON);
}

// Function to close the inlet valve.
void SRTank::closeInletValve(void){
    Serial.write(_INPUT_VALVE);
    Serial.write(_TURN_OFF);
}

// Function to open the outlet valve.
void SRTank::openOutletValve(void){
    Serial.write(_OUTPUT_VALVE);
    Serial.write(_TURN_ON);
}

// Function to close the outlet valve.
void SRTank::closeOutletValve(void){
    Serial.write(_OUTPUT_VALVE);
    Serial.write(_TURN_OFF);
}

// Function to turn on the heater.
void SRTank::turnOnHeater(void){
    Serial.write(_HEATER);
    Serial.write(_TURN_ON);
}

// Function to turn off the heater.
void SRTank::turnOffHeater(void){
    Serial.write(_HEATER);
    Serial.write(_TURN_OFF);
}

// Function to turn on the cooler.
void SRTank::turnOnCooler(void){
    Serial.write(_COOLER);
    Serial.write(_TURN_ON);
}

// Function to turn off the cooler.
void SRTank::turnOffCooler(void){
    Serial.write(_COOLER);
    Serial.write(_TURN_OFF);
}

// Function to turn on the agitator.
void SRTank::turnOnAgitator(void){
    Serial.write(_AGITATOR);
    Serial.write(_TURN_ON);
}

// Function to turn off the agitator.
void SRTank::turnOffAgitator(void){
    Serial.write(_AGITATOR);
    Serial.write(_TURN_OFF);
}

// --------------------- Setters para los outputs analógicos ---------------------

// Function to set the hight temperature alarm value.
void SRTank::setMaxTemperatureAlarm(unsigned int temperature){
    Serial.write(_TEMP_IN_MAX);
    Serial.write((temperature & 0xFF00) >> 8);
    Serial.write(temperature & 0x00FF);
}

// Function to set the low temperature alarm value.
void SRTank::setMinTemperatureAlarm(unsigned int temperature){
    Serial.write(_TEMP_IN_MIN);
    Serial.write((temperature & 0xFF00) >> 8);
    Serial.write(temperature & 0x00FF);
}

// --------------------- New functions ---------------------

void SRTank::fillTank(void){
    // Open the inlet valve.
    openInletValve();
    // Wait until the tank is full.
    while(getVolume() < maxVolume);
    // Close the inlet valve.
    closeInletValve();
}
void SRTank::fillTank(unsigned int volume){
    // Open the inlet valve.
    openInletValve();
    // Wait until the tank is at 'volume'.
    while(getVolume() < volume);
    // Close the inlet valve.
    closeInletValve();
}
void SRTank::emptyTank(void){
    // Open the outlet valve.
    openOutletValve();
    // Wait until the tank is empty.
    while(getVolume() >= minVolume);
    // Close the outlet valve.
    closeOutletValve();

}
void SRTank::emptyTank(unsigned int volume){
    // Open the outlet valve.
    openOutletValve();
    // Wait until the tank is at 'volume'.
    while(getVolume() > volume);
    closeOutletValve();
}
void SRTank::heatTank(void){
    // Turn on the heater.
    turnOnHeater();
    // Wait until the tank is max hot.
    while(getTemperature() <= maxTemp);
    turnOffHeater();
}
void SRTank::heatTank(unsigned int temperature){
    // Turn on the heater.
    turnOnHeater();
    // Wait until the tank is at 'temperature'.
    while(getTemperature() < temperature);
    turnOffHeater();
}
void SRTank::coolTank(void){
    // Turn on the cooler.
    turnOnCooler();
    // Wait until the tank is max cold.
    while(getTemperature() >= minTemp);
    turnOffCooler();
}
void SRTank::coolTank(unsigned int temperature){
    // Turn on the cooler.
    turnOnCooler();
    // Wait until the tank is at 'temperature'.
    while(getTemperature() > temperature);
    turnOffCooler();
}
void SRTank::stirTank(void){
    // Turn on the agitator.
    turnOnAgitator();
    // Wait until the tank is stirred.
    delay(stirTime);
    turnOffAgitator();
}
void SRTank::stirTank(unsigned int time){
    // Turn on the agitator.
    turnOnAgitator();
    // Wait until the tank is stirred 'time' seconds.
    delay(time);
    turnOffAgitator();
}

// --------------------- Functions with the Tank ---------------------

// Initialize the tank with default values.
SRTankData SRTank::getInit(void){
    tankData.highFloater = 1;
    tankData.lowFloater = 1;
    tankData.maxTemperature = 1;
    tankData.minTemperature = 1;
    return tankData;
}

// Initialize the tank with default values.
SRTankData2 SRTank::getInit2(void){
    packTank();
    tankData2.volume = 5;
    tankData2.temperature = 5;
    return tankData2;
}

SRTankData SRTank::getStructure(void){
    tankData.highFloater = getHighFloater();
    tankData.lowFloater = getLowFloater();
    tankData.maxTemperature = getMaxTemperature();
    tankData.minTemperature = getMinTemperature();
    return tankData;
}

// Define the function packTank.
void SRTank::packTank(){
    tankData2.popurri = 0;
    tankData2.popurri |= tankData.highFloater << 3;
    tankData2.popurri |= tankData.lowFloater << 2;
    tankData2.popurri |= tankData.maxTemperature << 1;
    tankData2.popurri |= tankData.minTemperature;
}

SRTankData2 SRTank::getStructure2(void){
    packTank();
    tankData2.volume = getVolume();
    tankData2.temperature = getTemperature();
    return tankData2;
}

void SRTank::setStructure(void){
    tankData.highFloater = getHighFloater();
    tankData.lowFloater = getLowFloater();
    tankData.maxTemperature = getMaxTemperature();
    tankData.minTemperature = getMinTemperature();
    tankData2.volume = getVolume();
    tankData2.temperature = getTemperature();
}

// --------------------- Auxiliar functions ---------------------

// path: lib/SRTank/SRTank.cpp