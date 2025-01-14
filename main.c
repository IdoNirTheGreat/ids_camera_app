#include <stdio.h>
#include "ueye.h"

int main() {
    // Setup the iDS camera:
    HIDS hCam = 0;

    // Try connecting to the camera:
    INT nRet = is_InitCamera (&hCam, NULL);
    
    if (nRet != IS_SUCCESS)
    {
        printf("Error initializing camera.\n");
        return -1;
    }
    
    printf("Connected successfully to camera %d\n", hCam);

    // Set the camera to be in global shutter mode:
    INT nShutterMode = IS_DEVICE_FEATURE_CAP_SHUTTER_MODE_GLOBAL;
    nRet = is_DeviceFeature(hCam, IS_DEVICE_FEATURE_CMD_GET_SHUTTER_MODE, (void*)&nShutterMode, sizeof(nShutterMode));

    if (nRet != IS_SUCCESS)
    {
        printf("Error setting global shutter.\n");
        return -2;
    }

    printf("Successfully set global shutter mode for camera %d.\n", hCam);

    // Try disconnecting from the camera:
    nRet = is_ExitCamera(hCam);

    if (nRet != IS_SUCCESS)
    {
        printf("Error disconnecting from camera.\n");
        return -2;
    }
    
    printf("Disconnected successfully from camera %d.\n", hCam);

    return 0;
}
