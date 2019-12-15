# Kinetic-Filter

Concept 

My concept for this project started with the idea of attaching motors to balls that would move up and down and side to side, with the ball’s position corresponding to some musical output. Originally, I envisioned stainless steel balls that would move within a box and have their position be sent to my computer to use for audio processing. Shortly into the design phase, I realized that this concept of balls moving up and down made me think of parametric equalization, where you drag frequency bands up and down to change their volume, and I thought that would actually make for a more compelling project. In this way, the installation brings the concept of equalization and filtering, which we normally think of as a purely digital and algorithmic effect, into the real world. I think of this installation as a cross between a kinetic sculpture and a VST plugin. 

Many aspects of my design changed as I got further along in the construction process. I decided to move away from the steel balls, which would have been very difficult to securely and cleanly attach to string, to a graduated set of wooden balls, which I could easily drill and glue to the balls. It also allowed me to paint the balls and give the sculpture a much more aesthetically pleasing look. The graduated balls also give a nice representation of the frequency bands, with the larger bands controlling the low end and the smaller ones controlling the high end. I also had originally envisioned using the Raspberry Pi for the audio processing. However I ended up using my laptop, because I wanted the user to easily be able to select from a variety of input audio files into the system, which would have been difficult to accomplish on the Pi. This ended up working extremely well, and I think the fact that users could select from a variety of songs made the installation more accessible and fun to use. Lastly, and most significantly, I changed my design to make the project interactive, by having users control the position of the balls with knobs rather than have them move on their own. I believe this was the greatest success of the installation, as it gives the users control over how they shape the sound and really allowed them to discover how it worked. 

Construction

The construction of the box began with a thin plank of wood, which I laser cut to dimensions I needed to construct the box. I added additional wooden planks on the bottom to elevate the box and allow for wires to go underneath it. Finally I added a wooden plank at the top to conceal the motors. I also drilled 6 holes in the top panel to allow the string holding the balls to pass through.

The circuit design for the project was the most challenging aspect, as I was dealing with a lot of hardware: six stepper motors, six potentiometers, and two ESP’s. My first concern was having a sufficient power supply to power all of these components simultaneously. I ended up using an external power supply of 5 volts and 12 amps plugged into the wall. This gave me more than enough amperage to power all the motors (which require half an amp each) and the ESP’s. Another concern was having enough input pins on the ESP to accommodate 4 inputs for each stepper motor and one for each potentiometer. This concern was heightened because the steppers motors are not compatible with all the pins, and the use of WiFi also limited my pin options (some of the analog pins conflict with the ESP WiFi). Two ESP’s gave me just enough pins to power everything successfully. 

After testing all 6 motors with the ESP’s I was ready to attach the motors to the box. I glued the motors to the top of the box, and glued a breadboard to the back of the box, which is where everything would receive power and ground. Then I glued the potentiometers to a plank at the base of the box, and ran their wires under the box to a separate breadboard. The potentiometers work much better with 3.3 volts than 5 volts, so instead of using the main power supply, I ran the 3.3 volt pin out of one of the ESP’s to the second breadboard. 

Refinements 

After all of my hardware was up and running, it was time to attach the balls to the string and the string to the stepper motors. I glued colored yarn to each stepper motor, however I found that the stepper motors alone were not fast enough to make the balls move up and down at an acceptable rate. To amend this, I attached wheels to each stepper motor to create a greater angle of rotation and thus making the balls move up and down quicker. After glueing the string to the wheels and attaching the balls to the strings, the construction was complete. 

One mistake I made during the construction was drilling the holes too small, so that the string would sometimes get caught on the wood and impede movement of the balls. This problem could have been resolved by drilling bigger holes, and glue a plastic or metal spacer inside each hole to give the strings a smooth surface to move over. However after gluing everything in place, this was difficult to achieve. Instead, I lessened the problem by sanding and waxing the edge of the wood and the string itself. This definitely helped, however did not solve the problem completely. In hindsight, bigger holes with spacers certainly would have been the right choice.

Code and Communication

The code for this project was relatively straightforward. The ESP’s are reading each potentiometer value, scaling it, and then comparing that value with the current step count for the motor. The step count is a range of values, calibrated separately for each ball, that increases or decreases when the potentiometers increase or decrease. While the potentiometer’s value changes instantly, the step count increases gradually until it catches up to the potentiometers. This effect allows for the smooth, continuous motion of the balls. Each time the step count increases or decreases, I tell the stepper motor to move up or down respectively. I also built in some padding so that small changes in the potentiometer value didn’t change the step count. 

The last code component for the ESP’s is the WiFi, which I chose to use to keep the box wireless and to communicate with my laptop without the need for USB cords. One of the ESP’s acts as a host, and creates the WiFi network. The other ESP acts as a client and connects to this network (this is the only difference in their code). Then, by connecting my laptop to the network, I can communicate wirelessly across all 3 devices. I am using different ports on the ESP’s to distinguish them when I’m reading their values in Max.

Finally, I am running Max/MSP on my laptop, which receives the step count coming in from the ESP’s. These values are then scaled and fed into a 6 band filter, controlling the gain of each band. Other filter parameters, like cutoff frequency and Q value, are predetermined in Max. The cutoff frequencies for each ball are 100 Hz, 300 Hz, 750 Hz, 1600 Hz, 4000 Hz, and 10000 Hz. Because the value coming in is the step count and not the potentiometer value, the filtering happens at the same rate as the movement of the balls. Finally, preloaded audio are played through the filter.

Calibration 

One of the biggest challenges I had with the project was calibrating the motors to have a precise range of motion. Ideally, I wanted the balls to all align together at the top and bottom when they are at their maximum and minimum values. However, because of discrepancies between the motors and potentiometers, this was difficult to achieve. I tried to calibrate each motor and potentiometer by reading its initial value and adjusting the scaling ranges based on that. This certainly improved my results, but ultimately was not consistent. In a future iteration of this project, this problem could be lessened by more robust equipment or a more complex calibration procedure. 

Installation

To install my project, I attached a pair of desktop speakers to my laptop for audio output. The open house installation in CCAM was a great success, and I was really happy with how people interacted with my project. Even those unfamiliar with audio processing and filter were able to grasp the concept and understand what the height of the balls were doing to the sound. The filtering effect was very one-to-one as consistent. After the installation, I refined the filtering algorithm in Max to make the effect even more pronounced, which will be great for documenting the project. 

Reflection

Ultimately I was extremely satisfied with my sculpture and happy that I put a lot of time into building it. It’s made me really interested in the idea of kinetic audio sculptures, and has given me new ideas for potential design improvements and new projects altogether. Check out the video below to see the Kinetic Filter in action.

Parts List 

Two ESP32’s
Six 28BYJ-48 Stepper Motors with ULN2003 motor drivers 
Six Stepper Motor Wheels 
Six Dial Potentiometers 
5 Volt 12 Amp External Power Source
Graduated Wooden Balls 
Colored Yarn 
Wooden Enclosure 
Breadboard and Wires 
Laptop 
Desktop Speakers 
