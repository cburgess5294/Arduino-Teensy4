# Arduino-Teensy4
Version 1.0

Assembling the Board
--------------------

You can find the full assembly instructions here:  https://www.instructables.com/id/Arduino-Teensy4-for-Teensy-40-Full-Assembly/

MicroSD Card Slot
-----------------
The SD card socket used SDIO and requires the flat-flex cable to be installed.  Set chip-select to "= BUILTIN_SDCARD" when using the Teensy 4 examples from Teensyduino.  This does not appear to work in the standard SD examples which I don't think support SDIO.

It has been successfully tested with 16 and 32GB cards using the SD examples included for the Teensy 4 in the latest Teensyduino, which can read either FAT16/32 or exFAT formatted cards.

It has also been successfully tested with the uSDFS library examples, which require the card to be formatted as exFAT.  Set TEST_DRV to type 1 // SDHC

I have not been able to get it to work with the latest SdFat library examples but there is no reason it shouldn't as the SD card port is connected exactly the same as the port on the PJRC breakout-board and from what I understand, that works with SdFat.

USB-HOST
--------
USB-HOST requires that the 2 foremost-center pogo pins be installed under the Teensy.  The flatflex cable can push them out of alignment if it is not bent close enough to the socket.  Ensure that the Teensy is fully-seated in the socket and the pogo pins are making connection if you have issues with the USB-Host.

The USB-Host has been successfully tested with wireless and wired USB devices while the Teensy is powered from a powered-USB hub via the micro-USB port.  There is a test-sketch in the reposity that tests both the USB-Host and MicroSD card at the same time.  Pressing the left mouse button will trigger the SD card to be read.

The Teensy can get pushed up in the socket due to the pressure from the pogo pins.  A dab of hot-glue or similar adheseve on the side of the connector where they come together will prevent this.

rev 1.0
