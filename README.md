# Musical Keyboard
This project allows a user to play notes on a virtual piano and stores the played notes in an array for later playback.

The program uses the TIMER2 peripheral to generate a periodic interrupt every 1ms, which is used to keep track of time in milliseconds. It also uses TIMER1 to generate a square wave tone of a specified frequency.

The program reads the state of eight switches connected to pins PD0 to PD7 of the microcontroller. When a switch is pressed, the program plays a tone of a corresponding frequency for a short duration, records the switch number and the duration of the note, and stores this information in two arrays. The program then waits for a short period of time before reading the switches again. This loop continues indefinitely until the user presses a "clear" button or a "play" button.
