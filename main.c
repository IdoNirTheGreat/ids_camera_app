#include <stdio.h>
#include "ueye.h"

void connectToCamera(HIDS* phCam)
{
    // Connect to the camera:
    INT nRet = is_InitCamera(phCam, NULL);
    
    if (nRet != IS_SUCCESS)
    {
        printf("Error initializing camera.\n");
        exit(-1);
    }
    
    printf("Connected successfully to camera %d\n", *phCam);
}

void setExternalTrigger(HIDS hCam)
{
    // Set trigger to external mode:
    INT nTriggerMode = IS_SET_TRIGGER_LO_HI;
    INT nRet = is_SetExternalTrigger(hCam, nTriggerMode);

    if (nRet != IS_SUCCESS)
    {
        printf("Error setting external post-trigger.\n");
        exit(-3);
    }

    printf("Successfully set external post-trigger for camera %d.\n", hCam);
}

void setGlobalShutter(HIDS hCam)
{
    // Set the camera to be in global shutter mode:
    INT nShutterMode = IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL;
    INT nRet = is_DeviceFeature(hCam, IS_DEVICE_FEATURE_CMD_GET_SHUTTER_MODE, (void*)&nShutterMode, sizeof(nShutterMode));

    if (nRet != IS_SUCCESS)
    {
        printf("Error setting global shutter.\n");
        exit(-2);
    }

    printf("Successfully set global shutter mode for camera %d.\n", hCam);

}

void disconnectFromCamera(HIDS hCam)
{
    // Disconnect from the camera:
    INT nRet = is_ExitCamera(hCam);

    if (nRet != IS_SUCCESS)
    {
        printf("Error disconnecting from camera.\n");
        exit(-2);
    }
    
    printf("Disconnected successfully from camera %d.\n", hCam);

}

int main()
{
    HIDS hCam = 0;  // Initate the hCam (handle for the iDS camera)

    connectToCamera(&hCam);

    setExternalTrigger(hCam);

    setGlobalShutter(hCam);

    disconnectFromCamera(hCam);
    
    return 0;
}
