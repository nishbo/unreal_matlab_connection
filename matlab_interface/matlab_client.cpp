/*
  MEX wrapper for the CPP client
*/


#include "mex.h"
#include "socket_api.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

static bool basic_init = false;

//------------------------ copy data between MATLAB and Mujoco --------------------------

// check size of numeric field from MATLAB
static void checkNumeric(const mxArray* mx, const char* name, int sz0, int sz1)
{
    char msg[100];

    if( !mx )
    {
        sprintf(msg, "%s: missing numeric argument", name);
        mexErrMsgTxt(msg);
    }

    if( mxGetNumberOfDimensions(mx)!=2 )
    {
        sprintf(msg, "%s: numeric argument has %d dimensions, should be 2",
            name, mxGetNumberOfDimensions(mx));
        mexErrMsgTxt(msg);
    }

    if( mxGetClassID(mx)!=mxDOUBLE_CLASS )
    {
        sprintf(msg, "%s: expected class DOUBLE", name);
        mexErrMsgTxt(msg);
    }

    const mwSize* sz = mxGetDimensions(mx);
    if( (sz[0]!=sz0 || sz[1]!=sz1) && (sz[0]!=sz1 || sz[1]!=sz0) )
    {
        sprintf(msg, "%s: expected %d-by-%d or %d-by-%d, got %d-by-%d",
            name, sz0, sz1, sz1, sz0, sz[0], sz[1]);
        mexErrMsgTxt(msg);
    }
}

// MATLAB => Mujoco: structure field
template <typename T>
void mx2mjc(T* mj, const mxArray* arg, const int nr, const int nc, const char* name)
{
    // get field and check
    const mxArray* mx = mxGetField(arg, 0, name);
    if( !mx )
    {
        // skip empty array
        if( nr==0 || nc==0 )
            return;

        char msg[200];
        sprintf(msg, "missing field '%s'", name);
        mexErrMsgTxt(msg);
    }
    checkNumeric(mx, name, nr, nc);

    // copy data
    double* mat = mxGetPr(mx);
    for( int r=0; r<nr; r++ )
        for( int c=0; c<nc; c++ )
            mj[c+r*nc] = (T)mat[r+c*nr];
}


// Mujoco => MATLAB: structure field
template <typename T>
void mjc2mx(mxArray* out, const T* mj, const int nr, const int nc, const char* name)
{
    // return if no data; empty matrix assigned by default
    if( !nr || !nc )
        return;

    // check field name
    if( mxGetFieldNumber(out, name)==-1 )
    {
        mexPrintf("field name '%s' unrecognized\n", name);
        mexErrMsgTxt("error copying data from MuJoCo to Matlab");
    }

    // create field
    mxSetField(out, 0, name, mxCreateDoubleMatrix(nr, nc, mxREAL));

    // copy data
    double* mat = mxGetPr(mxGetField(out, 0, name));
    for( int r=0; r<nr; r++ )
        for( int c=0; c<nc; c++ )
            mat[r+c*nr] = (double)mj[c+r*nc];
}

// --------------------- API ----------------------------------------------------
// wrapper for mj_request_data
mxArray* request_data(void)
{
    mjDataReturnTime mjdatareturntime;
    memset(&mjdatareturntime, 0, sizeof(mjDataReturnTime));

    // call simulator, make sure call succeeds
    if( mj_request_data(&mjdatareturntime) != mjCOM_OK )
        mexErrMsgTxt(sa_last_result());

    // create Matlab structure for output
    const int size = 4;
    const char* name[size] = {
        "n",
        "dat",
        "lastUpdateTime",
        "lastUpdateDelta"
    };
    mxArray* out = mxCreateStructMatrix(1, 1, size, name);

    // fill structure with data
    mjc2mx(out, &mjdatareturntime.n,
           1, 1, "n");
    mjc2mx(out, &mjdatareturntime.lastUpdateTime,
           1, 1, "lastUpdateTime");
    mjc2mx(out, &mjdatareturntime.lastUpdateDelta,
           1, 1, "lastUpdateDelta");
    mjc2mx(out, mjdatareturntime.dat,
           mjdatareturntime.n, 1, "dat");

    return out;
}

// wrapper for mj_send_data
void send_data(const mxArray* pin)
{
    mjData mjdata;
    memset(&mjdata, 0, sizeof(mjData));

    // copy data from Matlab structure to C structure
    mx2mjc(&mjdata.n,     pin, 1,                     1, "n");
    mx2mjc(mjdata.dat,    pin, mjdata.n,    1, "dat");

    // call simulator, make sure call succeeds
    if( mj_send_data(&mjdata) != mjCOM_OK )
        mexErrMsgTxt(sa_last_result());
}

// wrapper for mj_request_info
mxArray* getinfo()
{
    mjInfo mjinfo;
    memset(&mjinfo, 0, sizeof(mjInfo));

    // call server, make sure call succeeds
    if( mj_request_info(&mjinfo) != mjCOM_OK )
        mexErrMsgTxt(sa_last_result());

    // create Matlab structure for output
    const int size = 1;
    const char* name[size] = {
        "n"
    };
    mxArray* out = mxCreateStructMatrix(1, 1, size, name);

    // fill structure with data
    mjc2mx(out, &mjinfo.n,    1,                1, "n");

    return out;
}


//------------------------- main mex API ------------------------------------------------

const char _help[] =
"\nUSAGE:  [output] = matlab_client(command, [input])\n\n"
"  OUTPUT               COMMAND                     INPUT\n\n"
"                       'connect'                   [host name or ip address [, port]] \n"
"                       'close'\n"
"  mjDataReturnTime     'request_data'\n"
"                       'send_data'                 mjData\n"
"  mjInfo               'version'\n"
"\nExamples:\n"
"\tmatlab_client('help')                            Displays this message\n"
"\tmatlab_client('connect')                         Connects to localhost on default port\n"
"\tmatlab_client('connect', '10.3.29.233')\n"
"\tmatlab_client('connect', '', '44401')            Connects to localhost on port 44401\n";


// exit function
void exitFunction(void)
{
    sa_close();
    mexUnlock();
}


// entry point
void mexFunction(int nout, mxArray* pout[], int nin, const mxArray* pin[])
{
    char command[200], text[200], text2[200];
    int res = 0;

    // register exit function only once
    if( !basic_init )
    {
        mexAtExit(exitFunction);
    }

    // no inputs: print help, return
    if( !nin )
    {
        mexPrintf("%s\n", _help);
        return;
    }

    // get command string
    if( mxGetClassID(pin[0])!=mxCHAR_CLASS )
        mexErrMsgTxt("first argument must be command string");
    mxGetString(pin[0], command, 200);


    // apply command string
    if( !strcmp(command, "connect") )
    {
        // no host name: NULL
        if( nin==1 )
            res = sa_connect(0, 0);
        else
        {
            if(mxGetClassID(pin[1])!=mxCHAR_CLASS )
                mexErrMsgTxt("string argument expected for host");
            else
            {
                mxGetString(pin[1], text, 200);
                if( nin>2 )
                    if (mxGetClassID(pin[2])!=mxCHAR_CLASS)
                        mexErrMsgTxt("string arguments expected for port");
                    else {
                        mxGetString(pin[2], text2, 200);
                        if (res = sa_change_port(text2) == saOK)
                            res = sa_connect(text, 0);
                    }
                else
                    res = sa_connect(text, 0);
            }
        }
        if (!res)
            mexLock();
    }

    // sa_close or close
    else if( !strcmp(command, "close") )
        exitFunction();

    // request_data
    else if( !strcmp(command, "request_data"))
        pout[0] = request_data();

    // send_data
    else if( !strcmp(command, "send_data"))
        send_data(pin[1]);

    // getinfo
    else if( !strcmp(command, "version") || !strcmp(command, "info"))
        pout[0] = getinfo();

    // unknown command
    else
        mexErrMsgTxt("unknown command");


    // return error message text
    if( res )
        mexErrMsgTxt(sa_last_result());
}
