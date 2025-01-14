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

void setFrameRate(HIDS hCam, double frameRate)
{
    printf("Trying to set new frame rate\n");
    // Set the camera FPS:
    double newFrameRate;
    INT nRet = is_SetFrameRate(hCam, frameRate, &newFrameRate);
    if (nRet != IS_SUCCESS)
    {   
        printf("Failed here 2\n");
        printf("Error setting new frame rate.\n");
        exit(-4);
    }

    printf("Successfully set frame rate %f for camera %d.\n", newFrameRate, hCam);
}

void setExposureTime(HIDS hCam, double exposureTime)
{
    printf("Trying to set new exposure time\n");
    
    // Set the camera exposure time:
    INT nRet = is_Exposure(hCam, IS_EXPOSURE_CMD_SET_EXPOSURE, &exposureTime, sizeof(exposureTime));
    if (nRet != IS_SUCCESS)
    {   
        printf("Error setting new exposure time.\n");
        exit(-5);
    }

    printf("Successfully set exposure time to %f for camera %d.\n", exposureTime, hCam);
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
    setFrameRate(hCam, 10.00);
    setExposureTime(hCam, 0.001);

    INT triggerStatus = 0;

    printf("Waiting for external trigger...\n");

    while (1) {
        // Check for external trigger status
        INT nRet = is_SetExternalTrigger(hCam, IS_GET_TRIGGER_STATUS);
        
        if (nRet) {
            printf("External trigger received!\n");
            // break; // Exit the loop after receiving the trigger
        }

        // Small delay to avoid excessive CPU usage
        Sleep(50); // 100 ms (Windows-specific; use usleep or nanosleep for Linux)
    }

    disconnectFromCamera(hCam);
    
    return 0;
}
