function receiveData(  )
%RECEIVEDATA Summary of this function goes here
%   Detailed explanation goes here

    fid = fopen('VR_data.bin','wb');

    t = tcpip('127.0.0.1', 10010, 'NetworkRole', 'server');
    disp('Waiting for connection...');
    fopen(t);  % will NOT return until connected
    disp('connection established');
    keepConnection = 1;
    data = [];
    while keepConnection
        pause(0.001);
        if t.BytesAvailable > 0
            cInc = char(fread(t, t.BytesAvailable))';
%             disp(['Receiving ' cInc]);
            if strcmp(cInc, 'EOC')
                keepConnection = 0;
                disp('Closing connection');
            else
                ix = strfind(cInc,'[');
%                 data(end+1, :) = str2num(cInc(ix(end):end));
                fwrite(fid,[str2num(cInc(ix(end):end))]','double');
            end
        end
    end
%     data
    fclose(fid)
    fclose(t);

end

