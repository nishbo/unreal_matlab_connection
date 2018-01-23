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

tosend.n=6;tosend.dat=[1:6]*0.1;
tic
N=100000;
Bst = zeros(1, N);
for c1=1:N
%     A=matlab_client('request_data');
    matlab_client('send_data', tosend);
    Bst(c1) = toc;
end
B=toc;
fprintf('Mean time per call: %f microseconds.\n', 10^6*B/N);
A.dat

figure();
Bstdash = diff(Bst)*10^6;
Bstdash(Bstdash>250) = 0;
hist(Bstdash, 50);
xlabel('Delay, mus');
ylabel('Number of samples');

tosend.n=6;tosend.dat=[1:6]*0.1;
matlab_client('send_data', tosend);

matlab_client('close')
