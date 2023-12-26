#pragma once

#include "Task.hpp"
#include "NANDFlash.h"


class NANDTask : public Task {
private:
    const uint16_t DelayMs = 500;

    const static inline uint16_t TaskStackDepth = 1000;

    StackType_t taskStack[TaskStackDepth];

public:
    void execute();

    NANDTask() : Task("NANDFlashInitilization") {}

    static inline TaskHandle_t nandTaskHandle;

    void createTask() {
        nandTaskHandle = xTaskCreateStatic(vClassTask<NANDTask>, this->TaskName,
                          NANDTask::TaskStackDepth, this, tskIDLE_PRIORITY + 2, this->taskStack,
                          &(this->taskBuffer));
    }

};

inline std::optional<NANDTask> nandTask;
