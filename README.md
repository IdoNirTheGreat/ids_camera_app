# ids_camera_app

An application created to control an IDS camera (specifically designed for the **UI-3480ML-M-GL**).

## Build Instructions

### Using Visual Studio Code
Press **Ctrl+Shift+B** to build the application.

### Using Command Prompt
Run the following command:
```bash
gcc -g main.c -o app.exe -I "C:/Program Files/IDS/uEye/develop/include" -L "C:/Program Files/IDS/uEye/develop/lib" -lueye_api_64
