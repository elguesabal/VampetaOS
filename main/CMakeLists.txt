idf_component_register(
    SRCS 
        "main.cpp"
        "Sd/sd.cpp"
        "Sd/directory.cpp"
        "Sd/file.cpp"
        "System/system.cpp"
        "Wifi/wifi.cpp"

    INCLUDE_DIRS
        "."
        "Sd"
        "System"
        "Wifi"
)