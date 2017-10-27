% address for cpps: ..\ConnectionProject\Source\ConnectionProject\Private
% address for headers: ..\ConnectionProject\Source\ConnectionProject\Public
% copy files from Unreal Engine location
% copyfile ..\ConnectionProject\Source\ConnectionProject\Private\crossplatform_win.cpp crossplatform_win.cpp
% copyfile ..\ConnectionProject\Source\ConnectionProject\Private\socket.cpp socket.cpp
% copyfile ..\ConnectionProject\Source\ConnectionProject\Private\socket_api.cpp socket_api.cpp
% 
% copyfile ..\ConnectionProject\Source\ConnectionProject\Public\crossplatform.h crossplatform.h
% copyfile ..\ConnectionProject\Source\ConnectionProject\Public\socket.h socket.h
% copyfile ..\ConnectionProject\Source\ConnectionProject\Public\socket_api.h socket_api.h

mex -v COMPFLAGS='$COMPFLAGS /Otxg' -output matlab_client.mexw64 ...
    matlab_client.cpp ...
    socket_api.cpp ...
    socket.cpp ...
    crossplatform_win.cpp

matlab_client('connect')

A=matlab_client('version');
fprintf('Server version %d\n', A.n);

A=matlab_client('request_data')
A.dat

tosend.n=6;tosend.dat=[1:6]*0.1;
matlab_client('send_data', tosend);

matlab_client('close')

fprintf('Mean time per call: %f microseconds.\n', 10^6*B/N);