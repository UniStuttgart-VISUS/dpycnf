# dpycnf
A simple header-only library for XML-based tiled display descriptions used for the Vvand. The library supports the XML format used by different in-house tool at VISUS like vv2, ca and the vvebbrowser.

## Usage

The information from the configuration file is eventually held in the class `visus::vvand_config::display_configuration`. The class is templated with the XML character type of the underlying Expat parser, which you must provide and link with your application. Therefore, you normally want to instantiate `visus::vvand_config::display_configuration<XML_Char>`.

The `display_configuration` class supports two modes of obtaining the information: loading from a file and parsing from an in memory string. The former method looks like

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
