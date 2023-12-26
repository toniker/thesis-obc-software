#include "AmbientTemperatureTask.hpp"

void AmbientTemperatureTask::execute() {
    uint8_t numberOfDisconnectedSensors = 0;

    for (auto &sensor: sensors) {
        if (not sensor.isDeviceConnected()) {
            LOG_ERROR << "Temperature sensor with address " << sensor.getI2CUserAddress()
                      << " was disconnected";
            numberOfDisconnectedSensors++;
        }
    }

    if (numberOfDisconnectedSensors == NumberOfTemperatureSensors) {
        LOG_ERROR << "Suspending ambient temperature task";
        vTaskSuspend(taskHandle);
    }

    while (true) {
        for (uint8_t sensorCounter = 0; sensorCounter < NumberOfTemperatureSensors; sensorCounter++) {
            if (not sensors[sensorCounter].isDeviceConnected()) {
                LOG_ERROR << "Temperature sensor with address " << sensors[sensorCounter].getI2CUserAddress()
                          << " was disconnected";
                continue;
            }
            ambientTemperature[sensorCounter] = sensors[sensorCounter].getTemperature();
            LOG_INFO << "Sensor with address" << sensors[sensorCounter].getI2CUserAddress() <<
                " responded with ambient temperature = " << ambientTemperature[sensorCounter];
        }

        CommonParameters::boardTemperature1.setValue(ambientTemperature[0]);
        CommonParameters::boardTemperature2.setValue(ambientTemperature[1]);
        vTaskDelay(pdMS_TO_TICKS(DelayMs));
    }
}
