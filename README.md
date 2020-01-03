# Audio-Visualizer

This experiment requires the following equipment:
- 1 Arduino
- 1 1088AS 8x8 LED Matrix
- 1 MAX7219 LED Matrix Driver
- 1 MAX9814 AdaFruit AGC Electret Microphone Amplifier
- Wire pins 

The LED Driver assembles with the LED Matrix for the advantage of less wiring and simpler programming. The LED Driver connects to Pin 2 for the DIN connector, Pin 3 for the load connector, and Pin 4 for the clock connector. The microphone uses Pin 13 as the analog input. Each of the two devices are connected towards the LaunchPad through a ground pin and a voltage pin. The microphone requires 3.3 volts, while the LED driver requires 5 volts.
Once after, the finishing touches to the experiment is to program the device. There are two segments of the program: configuration of the microphone and configuration of the LED. For the microphone, it records an analog from the microphone and configures the minimum and maximum sound waves based on the integer value of the analog, calculate the peak-to-peak amplitude based on the difference between the minimum and maximum, and convert the amplitude into volts by dividing the amplitude by the maximum analog (1024).

For the LED, each column is defined into separate bytes within data. This data is then used into separate function: putByte, maxSingle, maxAll, and maxOne. putByte is responsible for writing to the individual LEDs digitally, while maxSingle is able to configure how much LEDs you want to light up based on the column number and the amount of bytes imputed as integers. maxAll and maxOne have similar functions, but are based on how much LED matrices you have. With these functions in mind, we then configured how much columns are lit up based on what range the volts is read within the loop. With this, you then have a LED fully aware on sound levels based on what the microphone inputs.



Credits to:
- Adafruit Microphone Amplifier sample sketch
- The original code was written for the LED Matrix Wiring board by: Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
https://www.potemkin.org/uploads/Wiring/MAX7219.txt
