# unreal_matlab_connection
CPP code to connect Unreal to Matlab

A server is created on the Unreal side with variables that can be accessed from Unreal via local variable structure, and from Matlab through a socket. Communication with socket is included.

## Getting Started

This project's code is available on [GitHub](https://github.com/nishbo/unreal_matlab_connection).

### Prerequisites

[MATLAB 2017a+](https://www.mathworks.com/products/matlab.html)

[Unreal Engine 4.17+](https://www.unrealengine.com/)

C/C++ compiler for MATLAB:

* [Microsoft Visual Studio 2015+](https://www.visualstudio.com/downloads/) (recommended for Windows)

* GCC, available from [MinGW](http://www.mingw.org/)

### Testing the current project

Run `ConnectionProject\ConnectionProject.uproject` in your UE4. Run `matlab_client.mexw64` in MATLAB.

### Adding to your project

Create new classes in your project with names same to classes in ConnectionProject\Source\ConnectionProject\Private\.

Replace the code within them with code from ConnectionProject classes, changing the CONNECTIONPROJECT_API to YOURPROJECT_API in each header file.

Add these libraries to your YourProject.Build.cs in `ConnectionProject\Source\ConnectionProject`:

```
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
PrivateDependencyModuleNames.AddRange(new string[] { "Networking", "Sockets" });
```

### Compiling MATLAB side

Run the [src/makeClient.m](src/makeClient.m) from MATLAB IDE. It should create matlab_client.mexw64 file.

## Using

First start UE server, then connect/disconnect from MATLAB.

### UE side

All of the communication goes via `ConnectionActorUberStorage` class instance. Just spawn it wherever you need it and pass it to the server functions.

To start the server, run `startServer` command from a blueprint. To kill the server, run `shutDownServer`.

To send the data, update the `ConnectionActorUberStorageInstance.variableOutArray`, and pass the Storage to `updateOutDataAfterWriting`. Don't forget to update array's length. To receive the data, run `updateInDataBeforeReading` and read it from `ConnectionActorUberStorageInstance.variableInArray`.

### MATLAB side

Use `matlab_client('help')`. `matlab_client('connect')` connects to the server. Avoid running without UE server on. `matlab_client('close')` closes connection. `'request_data'`  and `'send_data'` allow you to request and send data to the server.

`mjDataReturnTime` and `mjData` both have two fields, `n` - length and `dat` - data.

## Using plugin
Add the Plugins folder (located in the project ConnectionProject2 folder) and place it in the root folder of your project. Compile the project files and it is ready to be used.
Information about pluggins located: https://docs.unrealengine.com/en-us/Programming/Plugins 
An example of creation is here: https://wiki.unrealengine.com/An_Introduction_to_UE4_Plugins 

## Acknowledgements

The project uses code from [matlab_c_sockets](https://github.com/nishbo/matlab_c_sockets) repository.

Special thanks to Rama for [multi-threading tutorial](https://wiki.unrealengine.com/Multi-Threading:_How_to_Create_Threads_in_UE4).

## Authors

* **Anton Sobinov** - [nishbo](https://github.org/nishbo)
* **Matthew Boots** - [mboots](https://github.org/mboots)

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.
