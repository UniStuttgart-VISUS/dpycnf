# dpycnf
A simple library for XML-based tiled display descriptions used for the Vvand. The library supports the XML format used by different in-house tool at VISUS like vv2 and ca.

## Usage

The information from the configuration file is eventually hold in the class `Visus::VvandConfig::DisplayConfiguration`. This class supports two modes of obtaining the information: loading from a file and parsing from an in memory string. The former method looks like

```c++
try {
    auto config = Visus::VvandConfig::DisplayConfiguration::Load(L"vvand20.xml");
} catch (std::exception e) {
    std::cerr << e.what() << std::endl;
}
```

the latter like 


```c++
try {
    auto text = L"<TiledDisplay ...";
    auto config = Visus::VvandConfig::DisplayConfiguration::Parse(text);
} catch (std::exception e) {
    std::cerr << e.what() << std::endl;
}
```
