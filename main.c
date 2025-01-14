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

    // Try disconnecting from the camera:
    int dRet = is_ExitCamera(hCam);

    if (dRet != IS_SUCCESS)
    {
        printf("Error disconnecting from camera.\n");
        return -2;
    }
    
    printf("Disconnected successfully from camera %d\n", hCam);

    return 0;
}
