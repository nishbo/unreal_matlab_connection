function connect_sendDataOnce(  )
%SENDREPEATEDDATA Periodically sends same speed data
    % open connection
    connectLocalPort;
    
    global connectionDescriptor
    
    pause(1)
    % number of variabies in Array
    N = 14;
    % initialize data being sent
    dataToSend = -1*ones(1,N);
    
    dataToSend(1)   = 1; % 1 = spawn balls, 0 destroy balls if spawned
    dataToSend(2)   = 0; % 1 measurement data 0 means get trackpad and leap data
    
    % creates String to send data from dataToSend
    dataString = '';
    for c1=1:N
        dataString = [dataString ' ' sprintf('%.8f', dataToSend(c1))];
    end

    fwrite(connectionDescriptor, dataString);
    
    disp('Data Sent:')
    disp(dataString)
    
    % close connection
    pause(1)
    closeConnect
end

