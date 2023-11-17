# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.
cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "main.cpp" "LED.cpp" "contactor.cpp" "logger.cpp" "adc.cpp" "sensor_current.cpp"
                       INCLUDE_DIRS ".")
