cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(nrf7002_aht20)

target_sources(app 
    PRIVATE 
        src/main.c
        src/i2c_controller.c
        src/aht20_controller.c
)

# Inclusion du répertoire contenant le fichier d'en-tête
target_include_directories(app PRIVATE include)