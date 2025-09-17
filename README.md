# dpycnf
[![Build Status](https://visualisierungsinstitut.visualstudio.com/dpycnf/_apis/build/status/UniStuttgart-VISUS.dpycnf?branchName=master)](https://visualisierungsinstitut.visualstudio.com/dpycnf/_build/latest?definitionId=4&branchName=master)

A simple header-only library for XML-based tiled display descriptions used for the Vvand. The library supports the XML format used by different in-house tools at VISUS, like vv2, ca and the vvebbrowser.

## Usage
The library can be used by simply including it in the `#include` paths of your project. The library requires the [Expat XML parser](https://github.com/libexpat/libexpat) to be installed in the client application. You can use NuGet in Visual Studio to achieve this. If you are building with CMake, the [CMakeLists.txt](dpycnf/CMakeLists.txt) includes a `FetchContent_Declare` such that Expat is downloaded and built to be included directly. You can then use the library as follows:
```CMake
FetchContent_Declare(dpycnf
    GIT_REPOSITORY https://github.com/UniStuttgart-VISUS/dpycnf
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(dpycnf)

# [...]

target_link_libraries(${PROJECT_NAME} PRIVATE expat dpycnf)
```

The information from the configuration file is eventually held in the class `visus::vvand_config::display_configuration`. The class is templated with the XML character type of the underlying Expat parser, which you must provide and link with your application. Therefore, you normally want to instantiate `visus::vvand_config::display_configuration<XML_Char>`.

The `display_configuration` class supports two modes of obtaining the information: loading from a file and parsing from an in-memory string. The former method looks like
```c++
try {
    auto config = visus::vvand_config::display_configuration<XML_Char>::load("vvand20.xml");
} catch (std::exception& ex) {
    std::cerr << e.what() << std::endl;
}
```

the latter like 
```c++
try {
    auto text = "<TiledDisplay xmlns:i=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.visus.uni-stuttgart.de/vvand/2012/description\"><Machines><Machine><Identity>keshiki01</Identity><Tiles><Tile><LeftOffset>0</LeftOffset><Name>(0, 0), [2400, 4096] auf Maschine keshiki01</Name><StereoChannel>Left</StereoChannel><TopOffset>0</TopOffset><WindowHeight>4096</WindowHeight><WindowWidth>2400</WindowWidth></Tile></Tiles></Machine></Machines></TiledDisplay>";
    auto config = visus::vvand_config::display_configuration<XML_Char>::parse(text);
} catch (std::exception& ex) {
    std::cerr << e.what() << std::endl;
}
```

Once you have the configuration, you can iterate over the machines and the tiles attached to them. There are two ways of doing so: first, you can explicitly iterate machines and tiles like this:
```c++
for (auto& m : config) {
    for (auto& t : m) {
        std::cout << t.name() << std::endl;
    }
}
```

The second option is using a special iterator type which recursively visits all tiles:
```c++
for (auto it = config.tiles_begin(), end = config.tiles_end(); it != end; ++it) {
    std::cout << it->name() << std::endl;
}
```

If [JSON for Modern C++](https://github.com/nlohmann/json) is included before the library, conversion from and to JSON are enabled automatically:
```c++
// Convert a configuration object to JSON in memory.
nlohmann::json json = config;

// Print the configuration as JSON.
std::cout << json << std::endl;

// Restore a configuration object from JSON.
auto restored_config = json.template get<visus::vvand_config::display_configuration<XML_Char>>();
```

Using the same JSON library, the `ndisplay_builder` can be used to create a configuration file for Unreal Engine's nDisplay system:
```c++
// Load the XML configuration.
auto config = visus::vvand_config::display_configuration<char>::load("vvand.xml");

// Create a builder and provide the information missing in the XML file.
visus::vvand_config::ndisplay_builder<char> builder;

// Tell nDisplay about the head node, its IP address and the size of the preview shown there.
builder.controlled_by("minyou").add_ip_address("minyou", "10.35.3.1").with_preview_width(2592);

// Configure the physical size of the tiled display in centimetres.
builder.with_physical_width(600.0f).with_physical_height(224.0f);

// Add the IP addresses of the rendering nodes.
builder.add_ip_address("keshiki01", "10.35.1.1").add_ip_address("keshiki02", "10.35.1.2"); // etc.

// Alterntively, a JSON object holding the addresses can be used.
nlohman::json addresses = { 
    { "keshiki01", "10.35.1.1" },
    { "keshiki02", "10.35.1.2" },
    // etc.
};
builder.add_ip_addresses(addresses);

// Create the JSON configuration for nDisplay.
const auto ndisplay = builder.build(config);
std::cout << std::setw(4) << ndisplay << std::endl;
```
