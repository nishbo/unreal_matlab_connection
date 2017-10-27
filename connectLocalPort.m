function connectLocalPort(  )
%CONNECTLOCALPORT Connects to a local port and returns descriptor
    global connectionDescriptor

    connectionDescriptor = tcpip('127.0.0.1', 10000);
    fopen(connectionDescriptor);
    fwrite(connectionDescriptor, 'Matlab handshake');

end

