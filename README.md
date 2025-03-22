# ESP32 SD Card example (SDSPI)

This example demonstrates how to use an SD card with an ESP device over an SPI interface. Example does the following steps:

1. Use an "all-in-one" `esp_vfs_fat_sdspi_mount` function to:
    - initialize SDSPI peripheral,
    - probe and initialize the card connected to SPI bus (DMA channel 1, MOSI, MISO and CLK lines, chip-specific SPI host id),
    - mount FAT filesystem using FATFS library (and format card, if the filesystem cannot be mounted),
    - register FAT filesystem in VFS, enabling C standard library and POSIX functions to be used.
2. Print information about the card, such as name, type, capacity, and maximum supported frequency.
3. Create a file using `fopen` and write to it using `fprintf`.
4. Rename the file. Before renaming, check if destination file already exists using `stat` function, and remove it using `unlink` function.
5. Open renamed file for reading, read back the line, and print it to the terminal.

### Pin assignments

The GPIO pin numbers used to connect an SD card can be customized. This can be done in two ways:

1. Using menuconfig: Run `idf.py menuconfig` in the project directory and open "SD SPI Example Configuration" menu.
2. In the source code: See the initialization of ``spi_bus_config_t`` and ``sdspi_device_config_t`` structures in the example code.

This example doesn't utilize card detect (CD) and write protect (WP) signals from SD card slot.

The table below shows the default pin assignments.

SD card pin | SPI pin | ESP32 pin     | ESP32-S2, ESP32-S3 | ESP32-H2 | ESP32-C3 and other chips  |  Notes
------------|---------|---------------|--------------------|----------|---------------------------|-------------
 D0         | MISO    | GPIO2         | GPIO37             | GPIO0    | GPIO6                     |
 D3         | CS      | GPIO13 (MTCK) | GPIO34             | GPIO1    | GPIO1                     |
 CLK        | SCK     | GPIO14 (MTMS) | GPIO36             | GPIO4    | GPIO5                     |
 CMD        | MOSI    | GPIO15 (MTDO) | GPIO35             | GPIO5    | GPIO4                     |  10k pullup

#### ESP32-S3 related notes

With the default pin assignments, this example is compatible ESP32-S2-USB-OTG and ESP32-S3-USB-OTG development boards.

For other development boards, adjust the pin assignments as explained above.

## Troubleshooting

### Failure to mount filesystem

> The following error message is printed: `example: Failed to mount filesystem. If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.`

The example will be able to mount only cards formatted using FAT32 filesystem. If the card is formatted as exFAT or some other filesystem, you have an option to format it in the example code. Enable the `CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED` menuconfig option, then build and flash the example.


### Unable to flash the example, or serial port not available (ESP32 only)

> After the first successful flashing of the example firmware, it is not possible to flash again. Download mode not activated when running `idf.py flash` or the board's serial port disappears completely.

Some ESP32 boards require specific handling to activate the download mode after a system reset, due to GPIO2 pin now being used as both SDSPI (MISO) and an active-low bootstrapping signal for entering download mode. For instance, the ESP32-Azure IoT Kit requires KEY_IO0 button to remain pressed during whole firmware flashing operation, as it sets both GPIO0 and GPIO2 signals low.

Check you board documentation/schematics for appropriate procedure.

An attempt to download a new firmware under this conditions may also result in the board's serial port disappearing from your PC device list - rebooting your computer should fix the issue. After your device is back, use

`esptool --port PORT --before no_reset --baud 115200 --chip esp32 erase_flash`

to erase your board's flash, then flash the firmware again.