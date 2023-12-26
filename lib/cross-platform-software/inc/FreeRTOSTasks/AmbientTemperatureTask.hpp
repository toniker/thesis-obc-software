#pragma once

#include "Task.hpp"
#include "MCP9808.hpp"

/**
 * FreeRTOS task for periodically printing the value of the MCP9808 external temperature sensor.
 */
class AmbientTemperatureTask : public Task {
private:
    const uint16_t DelayMs = 1000;

    /**
     * Number of sensors on the PCB
     */
    static inline constexpr uint8_t NumberOfTemperatureSensors = 2;

    /**
     * The I2C addresses of the sensors based on the pin configuration of the physical devices
     */
    inline static constexpr etl::array<uint8_t, NumberOfTemperatureSensors>
            SensorI2CAddress = {0, 1};

    /**
     * The driver for the MCP9808 temperature sensor
     */
    etl::array<MCP9808, NumberOfTemperatureSensors> sensors = {MCP9808(SensorI2CAddress[0]),
                                                               MCP9808(SensorI2CAddress[1])};

    /**
     * The value of the temperature, measured in Celsius
     */
    etl::array<float, NumberOfTemperatureSensors> ambientTemperature = {0, 0};

    const static inline uint16_t TaskStackDepth = 2000;

    StackType_t taskStack[TaskStackDepth];

public:
    void execute();

    AmbientTemperatureTask() : Task("ExternalTemperatureSensors") {}

    void createTask() {
        taskHandle = xTaskCreateStatic(vClassTask < AmbientTemperatureTask > , this->TaskName,
                                       AmbientTemperatureTask::TaskStackDepth, this,
                                       tskIDLE_PRIORITY + 2, this->taskStack,
                                       &(this->taskBuffer));
    }

};

inline std::optional<AmbientTemperatureTask> ambientTemperatureTask;
