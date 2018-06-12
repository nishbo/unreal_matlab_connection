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

## Acknowledgements

The project uses code from [matlab_c_sockets](https://github.com/nishbo/matlab_c_sockets) repository.

## Authors

* **Anton Sobinov** - [nishbo](https://github.org/nishbo)

## License

This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.