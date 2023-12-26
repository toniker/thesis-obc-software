cmake_minimum_required(VERSION 3.7)
project(cross_platform_software)

add_subdirectory(lib/ecss-services/lib/logger)

add_compile_options(-Wvla)

add_library(common_cross STATIC)
target_compile_features(common_cross PRIVATE cxx_std_17)
target_include_directories(common_cross PUBLIC
        "inc/FreeRTOSTasks"
        "inc/Platform"
        "inc/Platform/CAN"
        "inc/Platform/Parameters"
        "lib/cobs-c"
        "inc/Helpers"
        "inc/Parameters")

target_sources(common_cross PRIVATE
        src/FreeRTOSTasks/AmbientTemperatureTask.cpp
        src/FreeRTOSTasks/CANGatekeeperTask.cpp
        src/FreeRTOSTasks/CANTestTask.cpp
        src/FreeRTOSTasks/MCUTemperatureTask.cpp
        src/FreeRTOSTasks/TimeKeepingTask.cpp
        src/FreeRTOSTasks/UARTGatekeeperTask.cpp
        src/FreeRTOSTasks/WatchdogTask.cpp
        src/Platform/CAN/ApplicationLayer.cpp
        src/Platform/CAN/Driver.cpp
        src/Platform/CAN/TPProtocol.cpp
        src/Platform/Parameters/BootCounter.cpp
        src/Platform/TaskInitialization.cpp
        src/Platform/TimeGetter.cpp
        src/Platform/Logger.cpp
        lib/cobs-c/cobs.c
        lib/cobs-c/cobsr.c
        )

target_compile_definitions(common_cross PRIVATE LOGLEVEL_TRACE)
