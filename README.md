# Get Started with CommonAPI for VSOME/IP

## Libraries
> Download & Build with CMake and install under path
- [vsomeip](https://github.com/COVESA/vsomeip)
- [CommonAPI Core Runtime Library](https://github.com/COVESA/capicxx-core-runtime)
- [CommonAPI SOME/IP Runtime Library](https://github.com/COVESA/capicxx-someip-runtime)
``` bash
# cd vsomeip/capicxx-core-runtime/capicxx-someip-runtime
cmake .
cd build
cmake install 
```

> Download, extract, and use directly with `.fidl` files
- [CommonAPI Core Generator](https://github.com/COVESA/capicxx-core-tools/releases)
> Download, extract, and use directly with `.fdepl` files
- [CommonAPI SOME/IP Generator](https://github.com/COVESA/capicxx-someip-tools/releases)

``` bash
# To make life easier, make an alias for generators in ~/.bashrc
alias ccgen="~/Downloads/commonapi_core_generator/commonapi-core-generator-linux-x86_64"
alias csgen="~/Downloads/commonapi_someip_generator/commonapi-someip-generator-linux-x86_64"
```

---

## Project Structure
``` bash
comAPITest/
├── hello.fidl                          # Interface definition
├── hello.fdepl                         # SomeIP deployment configuration
├── commonapi.ini                       # CommonAPI binding config
├── service-config.json                 # vsomeip config for service
├── client-config.json                  # vsomeip config for client
├── init_service.sh                     # Script to launch service
├── init_client.sh                      # Script to launch client
├── service/
│   ├── service.cpp                     # Service implementation
│   └── CMakeLists.txt
├── client/
│   ├── client.cpp                      # Client implementation
│   └── CMakeLists.txt
├── src-gen/                            # Auto-generated
│   └── v0/GettingStarted/
│       ├── HelloWorld.hpp
│       ├── HelloWorldProxy.hpp
│       ├── HelloWorldProxyBase.hpp
│       ├── HelloWorldStub.hpp
│       ├── HelloWorldStubDefault.hpp
│       ├── HelloWorldSomeIPProxy.hpp
│       ├── HelloWorldSomeIPProxy.cpp
│       ├── HelloWorldSomeIPStubAdapter.hpp
│       ├── HelloWorldSomeIPStubAdapter.cpp
│       ├── HelloWorldSomeIPDeployment.hpp
│       ├── HelloWorldSomeIPDeployment.cpp
│       └── HelloWorldSomeIPCatalog.json
├── CMakeLists.txt                      # Root CMake — builds both targets
└── build/                              # Build output (generated)
```
---

## Building & Running Demo

#### Configure your project in `.fidl` and `.fdepl` files
> Generate commonAPI files:
``` bash
ccgen -sk hello.fidl
csgen hello.fdepl
```
> This generates commonapi core & someip files

#### Implement your service & client code
> Service will use HelloWorldStubDefault.hpp

> Client will use HelloWorldProxy.hpp

#### Configure service & client in `.json` files using the same names and configs in `.fidl` and `.fdepl` files
#### `commonapi.ini` to tell the commonapi core to bind on someip

---

#### Build
``` bash
cmake -S . -B build
cmake --build build
```

---

#### Run
``` bash
./init_service.sh
./init_client.sh
```

> output
<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/a2ed31f6-d9bc-4f8f-9eb9-fd743c520efb" />
