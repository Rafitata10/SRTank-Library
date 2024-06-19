  * Rafael Ramírez Salas
  * Ingeniería de Computadores, Universidad de Málaga
  * Trabajo de Fin de Grado 2024: Fail Tolerant DualNano

## Fail Tolerant DualNano - SRTank-Library

This project is developed by Rafael Ramírez Salas, a Computer Engineering student at the University of Málaga. It is part of his Final Year Project for the year 2024.

## Overview

This folder contains a C++ library for controlling the simulated "Serial Remote Tank". It includes the functions getHighFloater, getLowFloater, getMaxTemperature, getMinTemperature, getVolume, getTemperature, setVolume, setTemperature, setHighFloater, setLowFloater, setMaxTemperature, setMinTemperature, openInletValve, closeInletValve, openOutletValve, closeOutletValve, turnOnHeater, turnOffHeater, turnOnCooler, turnOffCooler, turnOnAgitator, turnOffAgitator, setMaxTemperatureAlarm, setMinTemperatureAlarm, fillTank, emptyTank, heatTank, coolTank, stirTank, getInit, getInit2, getStructure, getStructure2, and setStructure.

## Environment Setup

This project is developed for the Arduino Uno platform using the Atmel AVR microcontrollers. The code is written in the Arduino framework.

The project is configured with the PlatformIO IDE. The configuration is specified in the `platformio.ini` file.

## Dependencies

The project depends on the following libraries:

- `LiquidCrystal`
- `Wire`
- `OneWire`

## Contributing

Contributions are welcome. Please open an issue to discuss your ideas before making a change.

## License

This project is licensed under the terms of the MIT license.

