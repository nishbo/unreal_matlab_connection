function closeConnect(  )
%CLOSECONNECT Sends stop message and closes descriptor
    global connectionDescriptor
    
    fwrite(connectionDescriptor, 'stop');
    fclose(connectionDescriptor);

    delete(connectionDescriptor);
end

