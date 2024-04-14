// Rafael Ramírez Salas
// Ingeniería de Computadores, Universidad de Málaga
// Trabajo de Fin de Grado 2024: Fail Tolerant DualNano

#ifndef SRTank_h
#define SRTank_h

#include <Arduino.h>

// Digital inputs.
#define _INPUT_VALVE  0x00 // Inlet valve
#define _OUTPUT_VALVE 0x01 // Outlet valve
#define _HEATER       0x02 // Heater
#define _COOLER       0x03 // Cooler
#define _AGITATOR     0x04 // Stirrer
// Digital outputs.
#define _HIGH_FLOATER 0x10 // High floater
#define _LOW_FLOATER  0x11 // Low floater
#define _MIN_TEMP     0x12 // Low temperature
#define _MAX_TEMP     0x13 // High temperature
// Analog inputs.
#define _TEMP_IN_MIN  0x20 // Minimal temperature alarm trigger level
#define _TEMP_IN_MAX  0x21 // Maximal temperature alarm trigger level
// Analog outputs.
#define _VOLUME       0x30 // Volume
#define _TEMP         0x31 // Temperature

// Actions.
#define _TURN_ON  0x01 // Turn on
#define _TURN_OFF 0x00 // Turn off

struct SRTankData {
    unsigned char highFloater;
    unsigned char lowFloater;
    unsigned char minTemperature;
    unsigned char maxTemperature;
}; extern SRTankData tankData;

struct SRTankData2 {
    unsigned int popurri;
    unsigned int volume;
    unsigned int temperature;
}; extern SRTankData2 tankData2;

class SRTank {
public:
    // Constructor.
    SRTank();
    // Getters para los outputs digitales.
    unsigned char getHighFloater();
    unsigned char getLowFloater();
    unsigned char getMaxTemperature();
    unsigned char getMinTemperature();
    // Getters para los outputs analógicos.
    unsigned int getVolume();
    unsigned int getTemperature();
    // Setters para los outputs digitales.
    void setVolume(void);
    void setTemperature(void);
    void setHighFloater(void);
    void setLowFloater(void);
    void setMaxTemperature(void);
    void setMinTemperature(void);
    // Functions with digital outputs.
    void openInletValve(void);
    void closeInletValve(void);
    void openOutletValve(void);
    void closeOutletValve(void);
    void turnOnHeater(void);
    void turnOffHeater(void);
    void turnOnCooler(void);
    void turnOffCooler(void);
    void turnOnAgitator(void);
    void turnOffAgitator(void);
    // Setters para los outputs analógicos.
    void setMaxTemperatureAlarm(unsigned int temperature);
    void setMinTemperatureAlarm(unsigned int temperature);
    // New functions.
    void fillTank(void);
    void fillTank(unsigned int volume);
    void emptyTank(void);
    void emptyTank(unsigned int volume);
    void heatTank(void);
    void heatTank(unsigned int temperature);
    void coolTank(void);
    void coolTank(unsigned int temperature);
    void stirTank(void);
    void stirTank(unsigned int time);
    // Functions with the Tank.
    SRTankData getInit(void);
    SRTankData2 getInit2(void);
    SRTankData getStructure(void);
    SRTankData2 getStructure2(void);
    void setStructure(void);

public:
    // Digital outputs.
    bool highFloater;
    bool lowFloater;
    bool minTemperature;
    bool maxTemperature;
    // Analog outputs.
    unsigned int volume;
    unsigned int temperature;

private:
    // Auxiliar values.
    unsigned char valueH, valueL;
    unsigned int maxVolume = 3000, minVolume = 0, maxTemp = 43, 
    minTemp = 3, maxTempAlarm = 33, minTempAlarm = 13, stirTime = 1000;
    // Auxiliar functions.
    void packTank();

}; extern SRTank tank; // Declaración externa para uso global.

#endif

// Path: lib/SRTank/SRTank.h