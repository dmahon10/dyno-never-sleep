# Dyno Never Sleep

### Set Up

Get an [ESP32 Dev Board](https://www.espressif.com/en/products/devkits) (or similar)

Download and install [Silicon Lab's USB to UART Bridge VCP Driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)

Download [Arduino IDE](https://www.arduino.cc/en/software)

Connect your ESP32 to your computer with a usb-to-micro-usb programming cable. 

Configure Arduino IDE for use with ESP32:
1. Click `Arduino` in the toolbar and navigate to `Preferences`
1. In `Additional Boards Manager URLs` field, paste `https://dl.espressif.com/dl/package_esp32_index.json`
1. Click `OK`
1. Navigate to `Tools > Board > Boards Manager`
1. Search for `ESP32` and install
1. Navigate to `Tools > Port` and select `/dev/cu.SLAB_USBtoUART`
⋅⋅* If this port is not listed you can use `ioreg -p IOUSB -w0 | sed 's/[^o]*o //; s/@.*$//' | grep -v '^Root.*'` from*erminal to list all ports in use and find out what port your board is connected to. 

Paste in the code from `main/main.ino` into the IDE .

Change the config variables at the top of the file to suit your needs. I suggest changing `period` to `5000` ms for testing purposes.

Click the right-pointing `Upload` arrow in the top right of the IDE window.

You may need to hold the `BOOT` button on your ESP32 Dev Board for a few seconds while the IDE console prints `Connecting...` for a successful upload.

After upload is complete click the `Serial Monitor` spy glass button in the top right on the IDE window to open the serial monitor. You should see the output from your board being printed.

The ESP32 can be restarted by pressing the `EN` button on the Dev board.