DC Motor Controller & Driver README
===================================

This directory has the open source DC Motor Controller & Driver software, board layouts, schematics, and parts list.

For the latest updates by the original author of this project visit:
http://morgandemers.com/?page_id=444

Author: Morgan Demers

+---------+
| LICENSE |
+---------+

This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/.

+--------------+
| Introduction |
+--------------+

In the winter of 2009 I began working on a Gingery Style metal lathe, as an alternative to buying a chinese made 7x12. It was my desire to attain some casting and machining skills, and in the end to have a lathe with similar capabilities. The original Gingery design calls for cone pulleys and belt changes to get varying speeds with no compensation for load. As I have a background in Computer Engineering, I thought it would be a great opportunity to design a Controller & Driver for a 2hp DC Treadmill Motor for the Lathe. I also wanted a fairly nice & simple digital interface that I could use to control the machine tool. And thus in 2011 I began working on the electronics / software aspect of the project. It is now 2013, my lathe is built, and the Controller, Driver and Software fairly well tested. It has been my end goal to make the project available to anyone who is interested in building a similar Controller for their own machine tool ( this can be used on a lathe, milling machine, drill press, etc... ).

+--------------+
| Dependencies |
+--------------+

Software:

The software was written for the Microchip PIC18LF14K50 Microcontroller, and was developed in the MPLAB v8.76 IDE for the Microchip C18 compiler ( free / lite version ). It may be possible to use MPLAB X, however I have not tested it yet...

I use a PICkit2 to program the Controller. I'd imagine a PICkit3 would work fine as well...

Hardware:

The Board Layouts & Schematics are all done in the free / lite version of Eagle 6.1.0. 

+---------------+
| Prerequisites |
+---------------+

In order to build the Controller / Driver you will need some skills / tools. You should have some experience with etching your own printed circuit boards, soldering on components, etc... I've made a point to not use SMD components to make it a bit easier for those who might have through-hole experience, but not SMD...

To get the software onto the controller you will need a PICkit2 ( or PICkit3 ) programmer. At the very least you will need the PICkit2 programmer software to install the 'hex' file in the Sofware Directory, or you will need the MPLAB IDE with C18 compiler installed to build the project and program the Controller.

To print the board layouts you will need Eagle v6.1.0 ( or newer ).

I've made a point to design the Controller / Driver within the limitations of the free versions of MPLAB IDE, C18 Compiter, Eagle v6.1.0, and thus you should not have to buy any software to get this project to work.

+---------------------+
| Directories & Files |
+---------------------+

LICENSE.txt - contains the license for this piece of software & hardware. Please read, open source though not for commercial use. If making modifications maintain changelog, and please leave the names of prior authors, and url to original source ( http://morgandemers.com/?page_id=444 )

README.txt - this file

Parts_List.xls - Excel Spreadsheet of all the parts required to build the Controller / Driver / Interface

Parts_List.csv - CSV version of Excel Sheet if you don't have Excel

'Software' folder - Contains the PIC18LF14K50 C18 software for the Controller. Load MPLAB v8.76 project file, or you can find pre-compiled HEX file that you could download directly to the Controller board.

'Hardware' folder - Contains all Eagle v6.1.0 Schematics & Board Layouts for this project

'Hardware/Eagle Libraries' folder - Contains any Eagle Library dependencies - only used for QRD1114 part in 'Tachometer' schematic / board.

'Hardware/Photos' folder - Contains some photos of my controller / boards / etc... A bit weak but thought it would be relevant to include some photos.

Hardware/Controller.{sch|brd} - Controller Schematic / Board.

Hardware/Driver.{sch|brd} - Driver Schematic / Board.

Hardware/Tachometer.{sch|brd} - Tachometer Schematic / Board.

Hardware/120VAC.sch - Mains 120VAC connection to Driver Schematic

Hardware/Motor.sch - Connections from Motor to Forward/Reverse Relay to Driver Schematic

Hardware/LCD.sch - Connections from LCD to 2x8_to_1x16 board to 1x16_to_1x16 board to Controller Schematic

Hardware/Interface.sch - Connections from 3 interface buttons and RPM potentiometer to 1x9_to_1x9 board to Controller Schematic

'Encoder Wheels' folder - Contains some sample pdf files of Encoder Wheels that you can print out. I would also recommend you download this encoder wheel software that I currently use to create all my wheels at this point - http://code.google.com/p/wheel-encoder-generator/

+-------------------------+
| Putting It All Together |
+-------------------------+

At some point I may produce a video tutorial of building the controller, driver boards, programming the controller, and hooking everything up to a treadmill motor. That being said, it hasn't been done yet, though you can follow the steps below to get an idea of how to go about building the Controller / Driver.


The Circuit Boards were all made at home using the Toner Transfer Method. I've had fairly good success with Staples Photo Basic Gloss paper and a cheap Laminator that I purchased at Costco. I use Ferric Chloride to etch my boards, and have had no problem doing so. I have recently become aware that the 'Staples Photo Basic Gloss' paper is no longer available, but similar results should be capable when using a Glossy Color Laser paper.

Some suggestions:

i. Heatshrink tubing is a great way to insulate all high voltage wires.
ii. 1/4" Quick Disconnect Connectors work well for 120VAC & Motor Connections ( my treadmill motor came with 1/4" quick disconnects ).

Step 1: LCD
-----------
*refer to LCD.sch, 2x8_to_1x16.{sch|brd}, 1x16_to_1x16.{sch|brd} in Hardware folder for details

a. Start by soldering on the 2-1x8 female headers ( if you purchased the LCD display with the 2x8 solder pads ).

b. Make a 2x8_to_1x16 PCB. You should cut a sufficient length of 16 conductor ribbon cable and solder one end to the 2x8_to_1x16 PCB. The 2x8 male pins will connect directly onto the LCD's female header that you soldered in (a) ( take a look at Hardware/Photos to get an idea of how this looks ).

c. Make a 1x16_to_1x16 PCB. Solder the other end of the ribbon cable to the solder pads on the 1x16_to_1x16 PCB. You will solder on a 1x16 male pin header which will connect to the Controller.


Step 2: Interface
-----------------
*refer to Interface.sch, 1x9_to_1x9.{sch|brd} in Hardware folder for details

a. Make a 1x9_to_1x9 PCB. Make note of the Interface Component positions from the Interface.sch. I'll repeat here for clarity - Pins {1,2} connect to Right Button ( SPST momentary push button - NO ), Pins {3,4} connect to Menu Button ( SPST momentary push button - NO ), Pins {5,6} connect to Left Button ( SPST momentary push button - NO ), Pins {7,8,9} connect to RPM Adjustment Precision Potentiometer ( 5k, Multi-Turn ) - Pin 7 = Ground, Pin 8 = V+, Pin 9 = Variable Pot Voltage.

b. Solder a 1x9 male pin header to the other end of the 1x9_to_1x9 PCB, this will connect to the Controller's 'INTERFACE' header.


Step 3: Controller
------------------
*refer to Controller.{sch|brd} in Hardware folder for details

a. Make the 'Controller' PCB, and solder on the components - Do not insert M1 ( PIC18LF14K50 ) until you do (d) below...

b. Connect the Interface 1x9_to_1x9 PCB to the 'INTERFACE' female header on the Controller.

c. Connect the 1x16_to_1x16 PCB to the 'LCD' female header on the Controller.

d. Connect +5V power to POWER terminal block, hook a multimeter up to VTEST, and adjust P1 until you get 3.4V ( *only if using a PIC18LF... )

e. Turn off +5V power, insert M1 ( PIC18LF14K50 )

f. Connect PICKIT2, Load MPLAB or PICKIT2 Programmer Software. PIC18LF14K50 should be detected.

g. Load the 'DC Motor Controller' software into MPLAB, and Program the PIC18LF14K50

h. Once programmed, disconnect the PICKIT2, LCD should show welcome message ( might have to cycle power first )

i. If 'welcome message' displayed, and now on 'RPM: 0','TRG: ...' menu, test the Interface Buttons, otherwise you will have to debug the Controller Board - possibly bad trace, connection, or misplaced components...

*How to use the interface - Menu Button rotates between sub-menus, and Holding the Menu Buttons and pressing Left or Right will change the main menu. Left and Right buttons alone either increment or decrement menu items, or do other actions as suggested on the LCD ( such as start or stop the motor ).

j. Connect your multimeter to the VTEST ( ground pin ) and the PWM Out pin of the 'DRIVER_OUT' header. On the main menu, set the RPM with the RPM Potentiometer, and then press the 'Left Button' to start the motor. You should see a change in voltage on the multimeter. If you have a Frequency measurement feature, use that to verify the 25khz frequency.


Step 4: Tachometer
------------------
*refer to Tachometer.{sch|brd} in Hardware folder for details

a. Make the 'Tachometer' PCB, and solder on the components. This board is a bit tricky, as it has 2 boards in 1 - you will cut off the smaller board that has the QRD1114, and then solder that board onto the main board such that the QRD1114 is facing outward ( toward the encoder wheel, at least in my setup ).

b. You can cut out a set of 3 conductors from your 16 conductor ribbon cable for the Tachometer cable. Using the 3-pin Molex .100 ( 2.54mm ) KK crimp terminals & housings, create a cable to connect the Tachometer to the Controller via the 'TACH' Male Header.

c. Using a laser printer ( or inkjet, then copied on a laser copier ) print out '16_transistion.pdf' from the 'Encoder Wheels' folder.

d. Connect the Tachometer to the Controller, and then move the encoder wheel printout from (c) in front of the QRD1114 sensor ( needs to be very close to the encoder 1/8" or less ). While transitioning between black & white monitor the LCD to see if the RPM changes at all. You can also go to the second menu ( HOLD Menu and press the Right Button ), then the 3rd sub_menu ( press Menu 3 times ). It should have 'TRG: ..' and 'ENC: ..' displayed. While moving the wheel in front of the sensor you should see the ENC number change ( that is what it is seeing on the encoder in a given sample ).


Step 5: Driver
--------------
*refer to Driver.{sch|brd}, Motor.sch in Hardware folder for details

a. Make the 'Driver' PCB, and solder on the components. Note that AC1, AC2, M+, M- are wire pads, and should have 16 gauge wire soldered in and connected to fully insulated quick disconnect connectors on the other end ( for hooking up to 120VAC & Motor ).

b. You can cut out a set of 5 conductors from your 16 conductor ribbon cable for the Driver cable. Using the 5-pin Molex .100 ( 2.54mm ) KK crimp terminals & housings, create a cable to connect the Driver to the Controller via the 'DRIVER_IN' Male Header.

c. Connect either regulated +12V to POWER_IN ( and short 12VREG ) or connect unregulated +12V-30V to POWER_IN and adjust POT1 until voltage at FAN1 is +12V. You should see the white indicator LED ( LED3 ) turn on with power. When a PWM signal is present from the Controller, you should also see the 'Green' indicator LED ( LED1 ) illuminate ( though brightness will vary depending on the DUTY cycle of the PWM signal ).

d. You can cut out a set of 2 conductors from your 16 conductor ribbon cable for the Relay cable. Using the 2-pin Molex .100 ( 2.54mm ) KK crimp terminals & housings, create a cable to connect the Driver to the Relay ( which is used to reverse the motor ). The 'relay' end of the cable should be soldered to a 1/4" fully insulated female quick disconnects which can be put directly onto the relay drive plug pins. To see how you should connect the Motor to the Relay to the Driver refer to Motor.sch.

e. To set the current at which the 'Current Limit' will trip, hook up your multimeter to pins 3 & 4 of IC1, and adjust 'CSENSE_ADJUST' until voltage matches that of expected voltage across current sensing resistor 'RSENSE'. I use a 0.01ohm current sense resistor, so for a 10A current limit, set 'CSENSE_ADJUST' such that the voltage across pins 3 & 4 of IC1 is 0.1V. If your multimeter is not that sensitive, you can measure the resistance of the 'CSENSE_ADJUST' pot on the same pins. Since you know we are working with a +12V supply, you can use the voltage divider equation ( Vout = Vin*(R2/(R1+R2)) ) to determine the resistance at pins 3 & 4 such that the voltage across it would be 0.1V - for our 10A example, since the pot is a 5k and the upper leg is tied to a 22k resistor, you would do something like 0.1V = 12V*(R2/(22k+5k)) - solving for R2, you get R2 = ~225ohm.

f. To test the reverse relay, connect the relay via the 2 conductor cable made in (d) to the Driver, and on the Interface from the main menu ( when you first start up ) press the 'Menu Button' once. You should see the direction of rotation listed with the option to reverse, press the 'Left Button' to do that. You should hear the relay click, if it does that is ready to go.


Step 6: Testing on Low Voltage Motor
------------------------------------
a. It is best to test the setup out on a low voltage motor ( +12V preferrably ). You will have to bypass the bridge rectifier, and you can easily do this by connecting the lower drive voltage to the output pins of the rectifier with aligator clips, or micro clips. Once done, hookup the smaller motor to the M+, M- board wires. You should fashion a simple motor mount out of wood, and a means of affixing a small encoder wheel to the motor shaft ( I used hot glue - put a glob on the back of the wheel, and then press the motor shaft into the glob before it hardens ). You will have to mount the tachometer in such a way that it is positioned close enough to the wheel for a reading ( you could try and hold it by hand but would be difficult to maintain a consistent distance from the wheel ).

b. If you are not using a 96 transition encoder wheel for this test, you will need to hold down the 'Menu Button' and press the 'Right Button' until you get to the Encoder 'Resolution' menu. You can then use the left and right buttons to change the resolution of the encoder wheel. The setting is for transitions, not just black strips.

c. With the simple motor mount, encoder wheel on motor shaft, and tachometer positioned within 1/8" of the wheel you can proceed to set an RPM, and turn on the motor by pressing the 'Left Button' on the main menu. You should see the motor run and adjust such that RPM: and TRG: are the same. If the motor starts and runs at full speed, adjust the position of the Tachometer as it might be too far away, or too close to get a reading.

d. You can test the 'Reverse' capability by hooking the motor leads up to the 'Reverse Relay' and going to the 'Motor Direction' menu - second sub menu off the main menu. Press the 'Left Button' to switch directions.


Step 7: Testing on High Voltage Treadmill Motor
-----------------------------------------------
a. If everything tested successfully in 'Step 6', you can now test the Controller / Driver with the High Voltage Treadmill Motor. You should enclose the Driver within a grounded case of some sort ( I started off with a gutted ATX power supply ), though I have tested the circuit without it before ( standing some distance away with my hand on a power strip switch ). Caution must be taken as it is extremely dangerous working with a circuit that is connected to 120VAC. The 470uF capacitor will also hold a substantially dangerous charge after the power is removed, and even though there is a 200k bleeder, it takes a few minutes for the capacitor to drain - I have seen quite a few sparks when intentially shorting the terminals of the capacitor with an insulated screw driver, so be careful when you get to this point.

+-----------------------+
| Interface Menu System |
+-----------------------+

You navigate the menu system with Left, Right, and Menu Buttons. To change between 'Menus' you hold the 'Menu' button and press either 'Left' or 'Right' which will rotate forward or backward through the menus. If you go past the last menu, you will end up at the first and visa versa. To change between 'Sub Menus' you simply press the 'Menu' button.

On some menus the Left and Right buttons will increment / decrement a value.

On some menus either the Left or Right buttons will do some action as indicated.

############

Menu 1: Main

  Sub Menu 1 - RPM & RPM Target Display ( Main Menu )

  Sub Menu 2 - Motor Direction - Left Button for Forward or Reverse

  Sub Menu 3 - Indexer

Menu 2: Info

  Sub Menu 1 - Current & Last Sample Errors - ER0 = Current Error, ER1 = Last Error

  Sub Menu 2 - PWM Duty Cycle

  Sub Menu 3 - ( TRG: ) Target Setpoint vs. ( ENC: ) Last Sample

Menu 3: PID Algorithm Constants

  Sub Menu 1 - KP - Proportional Constant Numerator

  Sub Menu 2 - KP - Proportional Constant Denominator

  Sub Menu 3 - KI - Integral Constant Numerator

  Sub Menu 4 - KI - Integral Constant Denominator

  Sub Menu 5 - KD - Derivative Constant Numerator

  Sub Menu 6 - KD - Derivative Constant Denominator

  Sub Menu 7 - FF - Feed Forward Constant Numerator

  Sub Menu 8 - FF - Feed Forward Constant Denominator

Menu 4: Settings

  Sub Menu 1 - Max Duty

  Sub Menu 2 - Max RPM

  Sub Menu 3 - Encoder Resolution

+-----------------------+
| Tuning The Controller |
+-----------------------+

Depending on your particular motor, the PID constants will most likely be slightly different than my own for your own setup. There are quite a few good documents online on how to adjust the constants in order to get a fairly good response.

Setting up Feed Forward:

a. Turn off the PID constants by setting the numerators to 0.

b. Set a desired RPM - 200 or something like that.

c. Go to the Feed Forward Sub Menu, and increase the value until the RPM displayed matches that of your desired RPM target.

d. Increase the RPM via the RPM Adjustment Knob and see if the RPM displayed follows the change made.

* feed forward can be used exclusively for variable speed adjustment if no feedback / load compensation is required. It will help the PID algorithm to not have to work so hard to maintain speed if used in conjunction with KP, KI, KD.

Setting up the PID Constants:

a. Before doing this step you need a way to apply a load to the spindle - possibly by cutting some metal if you are setup for that. I have had ok success holding a blank spindle ( no tools, just the shaft ) with a welder's glove - I don't necessarily recommend this, but it seemed fairly safe when I was initially testing my controller.

b. With the spindle running at some desired RPM ( and hopefully Feed Forward setup to get to that speed without a load on the spindle ), go to the 'KP' sub menu and initially set it to 1/1. The proportional constant of the PID controller will simply apply Error*KP to the PID output ( duty cycle ). So this will give you an instantaneous boost in output from the motor to try and maintain speed.

c. Increase KP's constants until you get to a slight overshoot case where the motor will jump beyond the desired RPM when you load the spindle. Back off KP slightly.

d. Increase KD's constant to eliminate any overshoot and reduce the settling time. Be careful with KD ( mine is typically set to 2/30 or something like this ) as it will add instability to the system if too high. 

e. If you find you have a steady state error ( the system settles at an RPM other than the target ) or you are not getting a fast enough response you should increase KI.

*My current settings for a 2hp treadmill motor with 96 resolution encoder wheel - KP=2/1, KI=3/2, KD=2/30, FF=35/4.

Effects of increasing PID Constants on System:

KP will descrease rise time, increase overshoot, decrease steady state error

KI will decrease rise time, decrease overshoot, increase settling time, eliminate steady state error

KD will decrease overshoot, decrease settling time

+-----------------------+
| Spindle Indexing      |
+-----------------------+

This controller has the capability of indexing a spindle if the Tachometer and Reverse Relay is setup. Having the ability to accurately position a spindle can be of some benefit depending on what you are using the controller for. On a lathe for instance you could use it to cut graduated micrometer dials, or if you had a dremel holder for your toolpost, you could do some really interesting stuff...