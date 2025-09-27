# Apple II Disk Clacker

This is a small circuit to generate fake disk-seeking noises for Apple II disk emulators using a
mechanical relay. It connects transparently between the Apple II and any disk emulator to detect
disk activity and make noises.

https://github.com/user-attachments/assets/748217c7-e036-4df3-93b7-2d29ec6acae3

This should work with:
 * BMOW Floppy Emu in 5.25" mode (tested)
 * BMOW Floppy Emu in 3.5" mode
 * Other floppy emulators in 5.25" or 3.5" mode

This project will not work with:
 * Smartport devices like FujiNet

This is currently only a DIY project and **it requires a high-voltage ATtiny programmer**. I use a XGecu T48 programmer
but any other compatible programmer can be used. If you're looking for a similar noise-maker that you can just purchase
directly then check out the [Big Mess o' Wires Noisy Disk Mechanical Sounder](https://shop.bigmessowires.com/products/noisy-disk).


# Building

The repo includes all source files for building your own clacker or modifying the design:
 * [KiCad project for the hardware](./AppleII-Disk-Clacker)
 * [Arduino source code](./Clacker)

All the generated outputs are also included in standard readable formats so you don't have to install
KiCad or the Arduino IDE if you don't want to:
 * [Schematic](./AppleII-Disk-Clacker/AppleII-Disk-Clacker.pdf) for circuit reference
 * [gerber files](./AppleII-Disk-Clacker/outputs) for PCB manufacturing
 * [Pre-compiled ATtiny code](./Clacker/Clacker.ino.hex) to flash into the ATtiny


### Parts List

Most of the components can be substituted freely but I included specific part numbers that I used for
reference. You don't have to order from Mouser but I also included their part numbers so you can reference
their datasheets to find substitutes. I also created a shared [Mouser Project](https://www.mouser.com/Tools/Project/Share?AccessID=db4092a81a)
that you can use to check part availability and add all the components from the table to your cart at once.

| Reference | Qty | Value             | Mfr                  | MfrPartNo        | MouserPartNo         |
|-----------|-----|-------------------|----------------------|------------------|----------------------|
|  C1       |  1  | 0.1µ              | Vishay               | A104K15X7RF5TAA  | 594-A104K15X7RF5TAA  |
|  D1       |  1  | 1N4007            | Diotec Semiconductor | 1N4007           | 637-1N4007           |
|  J1,J2    |  2  | 20 Pin header     | Amphenol             | T821120A1S100CEU | 649-T821120A1S100CEU |
|  K1       |  1  | Relay             | Amphenol             | AWHSH105D00G     | 523-AWHSH105D00G     |
|  Q1       |  1  | 2N3904            | Diotec Semiconductor | 2N3904           | 637-2N3904           |
|  R1       |  1  | 2.2k              | KOA Speer            | MF1/4LCT52R222J  | 660-MF1/4LCT52R222J  |
|  U1       |  1  | ATtiny13A-P       | Microchip            | ATTINY13A-PU     | 556-ATTINY13A-PU     |
|  U1       |  1  | DIP-8 Socket      | TE Connectivity      | 1-2199298-2      | 571-1-2199298-2      |
|           |  2  | 20 Pin IDC socket | Wurth Elektronik     | 61202023021      | 710-61202023021      |

In addition to these parts, you will also need a short length of 20 conductor 1.27mm pitch ribbon cable for the cable between your disk
emulator and the clacker. This is easy enough to salvage from old PC ribbon cables.



### Assembling

Assembly is pretty straightforward since there are not many components. Just start by soldering the lowest profile components first
and ensure the orientation of components match the labeling on the PCB.

If you're also making a 20 pin ribbon cable then make sure that the same wire is entering the marked pin 1 position on both connector housings.
The ribbon cable can enter either side of the housing as long as that wire lines up with the pin 1 position. This lets you construct a
cable with the polarization nub in the orientation that is the most convientent for your disk emulator.


### Flashing the ATtiny

These steps will vary depending on the programmer and software you use. A high-voltage ATtiny programmer is required. I can confirm that the
XGecu T48 programmer works but I am sure there are many others.

1. Select the ATtiny13a device (DIP8 packaging if the different packages are listed) in your programming software.
2. Load [the .hex file](./Clacker/Clacker.ino.hex) into your programming software. Make sure to load it as a hex file and not as a binary file.
3. Find and open the tab or dialog box to set the ATtiny fuse values. In the Xgpro application these settings are on the "Config" tab.
   * set CKDIV8 = 0  (divides clock by 8; this is the default fuse value for an ATtiny13)
   * set CKSEL1:0 = 10  (uses internal 9.6MHz oscillator; these are the default fuse values for an ATtiny13)
   * enable RSTDISBL  (disables /RESET so it can be used as GPIO)
4. Program the ATtiny


# Using

To use the clacker, just connect one of the 20 pin connectors to your disk emulator (like the Big Mess o' Wires Floppy Emu or a similar device)
and connect the other end to your disk controller card. It doesn't matter which cable goes to which connector, just make sure that pin 1 on the
cable connects to pin 1 on the connector.
