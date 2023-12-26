# Cross Platfrom Software

A repository that contains functionality that is used across subsystems that use ATSAMs. 
Current AcubeSAT subsystems that are using it are:
- OBC
- SU
- ADCS

## How to integrate
-  A `CommonParameters.hpp` file needs to be added. Its purpose is to connect generic variables used in this repo's tasks, 
with platform-specific variables. Create this file here: `inc/Platform/Parameters/`
Example contents:
```c++
#pragma once

#include "Helpers/Parameter.hpp"
#include "OBC_Definitions.hpp"
#include "PlatformParameters.hpp"

namespace CommonParameters {
inline auto &boardTemperature = PlatformParameters::obcBoardTemperature1;
inline auto &mcuTemperature = PlatformParameters::mcuTemperature;
}
```
- Call `initializeTasks();` in main.cpp
- If you don't have an MCP9808 connected on the board, you need to comment out the `xTaskCreateStatic` call in 
the `initializeTasks();` function, in `common/src/Platform/TaskInitialization.cpp`

## Functionality Implemented

### FreeRTOS Tasks
- AmbientTemperatureTask (MCP9808 Temperature Sensor)
- TimekeepingTask (RTC)
- UARTGatekeeperTask
- WatchdogTask
- MCUTemperatureTask

### Platform-specific
- BootCounter
- TaskInitialization (initializes tasks, should be called in main.cpp)
- TimeGetter
