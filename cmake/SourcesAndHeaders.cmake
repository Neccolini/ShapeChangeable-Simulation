set(sources
    src/Network.cpp
    src/MultiProcess.cpp
    src/devices/hardware/Serial.cpp
    src/devices/Devices.cpp
    src/devices/Router.cpp
    src/devices/Cordinator.cpp
    src/devices/hardware/string_extensions.cpp
    src/main.cpp
)

set(exe_sources
		${sources}
)

set(headers
    include/shapechangeable-simulation/Network.h
    include/shapechangeable-simulation/MultiProcess.h
    include/shapechangeable-simulation/devices/hardware/Serial.h
    include/shapechangeable-simulation/devices/Devices.h
    include/shapechangeable-simulation/devices/Cordinator.h
    include/shapechangeable-simulation/devices/Router.h
    include/shapechangeable-simulation/devices/hardware/string_extensions.h
)

set(test_sources
  src/tmp_test.cpp
)
