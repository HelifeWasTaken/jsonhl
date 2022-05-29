# Jsonhl

Lightwheight Json library

## Example:

```cpp
jsonhl::Deserializer json;

try {
    json.loadFromFile("file.json");
    int value = json["value"];
} catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```
