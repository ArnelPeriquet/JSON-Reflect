# JSON-Reflect
JSON-Based Runtime Reflection for C++

C++ JSON Reflect provides a reflection toolkit for C++ and a class schema representation based on the JavaScript Object Notation (JSON). The toolkit embeds a JSON-based type system into C++ programs that forms the basis for a meta-object protocol (MOP) to maniuplate objects and their classes at run-time. The libraries build on this type system to provide a JSON encoding for marshaling classes from/to an input or output stream. A ClassLoader is provided for loading classes from the file system, also allowing for loading classes from the network.

Benefits

- C++ embedded type system and run-time reflection API
- Object API for JSON parsing and generation (JSON.Stringify(), JSON.Parse())
- Object API for generating XML (XML.Stringify())
- JSON-based Class schema and ClassLoader
