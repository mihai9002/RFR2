# RFR2- Radio Frequency Receiver 2 — Journal Export

- Exported at: 2026-07-20T20:59:02Z
- Project ID: 673
- Entries: 16

## Entry 1
- ID: 387
- Author: mihai.a.ghetu
- Created At: 2026-03-23T20:57:12Z

### Content

**The basics**
Today, I started searching for parts, so I can build a schematic, and later a PCB. I am very happy with what I achieved, because I found the key components I will need for this project, and I found out they were really cheap.
For now, the stuff I already found:
- Microcontroller: XIAO RP2040;
- Audio amplifier: PAM8406 module board;
- Radio module: RDA5806;
- Display: 0.96'' OLED(might look for a bigger one).
I don't trust the speakers fully, so I might just take some from an old radio I have lying around. This would reduce the final cost of the build and make me get a bit of hands-on electronics experience.

Up next, I will look for:

- A way to connect via Bluetooth or Wi-Fi;
- Rotary encoders and maybe some switches.

KiCAD stuff:

- I forgot how to import libraries, and it took me a while to realize that the ok button was out of frame, but I figured it out after about 10 minutes.

Because i didn't get anything done yet, here's a picture of that old radio I disassembled:
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6ODk0LCJwdXIiOiJibG9iX2lkIn19--d17168b702a1d25d0a886a9932619d9ef29bd263/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/xFHIv8jMhXac/timelapse-xFHIv8jMhXac.mp4

## Entry 2
- ID: 423
- Author: mihai.a.ghetu
- Created At: 2026-03-24T20:34:58Z

### Content

Today, I started off by making the symbols for the components I chose to use for this project. After I was done with that, I got an idea: What if the radio could turn into a Bluetooth speaker?

It's did a very little amount of research on Bluetooth connectivity, but, from what I've discovered, it's not very complicated. With this info, I now know what my project will solve, other than aesthetic problems: Having both a radio you can take with you on, for example, a mountain, where signal strength is not very good and a speaker you can use when you get back down, all in a small form factor.


Next steps:

- Figure out how to wire these components, maybe it's very straightforward, maybe I'll have to include some resistors, capacitors and whatnot(I don't know what I'm talking about)

- Look into Bluetooth modules, make new symbols and find a way to integrate remote connectivity in my circuit

- Do I want to make it battery powered or USB-C rechargeable?

- Design footprints(I'm scared)

- Do the PCB layout

- CAD, come up with some cool mechanical doohickeys


Now for the mandatory art gallery:


![Screenshot 2026-03-24 223042.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6OTYxLCJwdXIiOiJibG9iX2lkIn19--757b39589f9db42ab45b66ef2b921eb437baf18e/Screenshot 2026-03-24 223042.png)


![Screenshot 2026-03-24 223151.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6OTYyLCJwdXIiOiJibG9iX2lkIn19--a2fcea477d56655f79985acbce7915b5f50e39f6/Screenshot 2026-03-24 223151.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/uZCVOZ2TNOxa/timelapse-uZCVOZ2TNOxa.mp4

## Entry 3
- ID: 977
- Author: mihai.a.ghetu
- Created At: 2026-04-02T21:53:49Z

### Content

This time, I did 2 timelapses, one where I was researching for an esp32 to use. I landed on the esp32 devkit1, which has Wi-Fi, Bluetooth and many pins. 

In the second session, I continued researching about the esp32. After a bit of thinking, I changed my mind and decided to use a Raspberry Pi Pico, and add a Bluetooth module.
Updated  component list:
- RDA5807 FM receiver module
- JDY-62 Bluetooth receiver module
- PAM8406 amplifier
- SSD1306 OLED(for now, maybe (I'll upgrade it)
- Raspberry Pi Pico
- 2 speakers

I chose the JDY-63 because it is very cheap, easy to get and it works well. I don't really know if the OLED should be bigger, so I won't make the KICad Footprint for now. 

Speaking of footprints: I don't know how I'm supposed to design the RDA breakout board, because I have no idea what type of connection should be there(it's not through-hole, I know that for a fact)

The wiring isn't very complex, I think, so I'll explain it

Let's start with the pins on the RP Pi Pico:
- The 3v3 pin is connected to the VDD pin of the RDA and to the VCC pin of the OLED(both receive 3.3V)
- The GND pin is connected to all the other GND pins(obviously)
- GPIO0(SDA) and GPIO1(SCL) are connected to the OLED's corresponding pins
-GPIO2(SCK) and GPIO6(SDA) are connected to the corresponding pins on the FM receiver

The Pico will be used to handle Bluetooth stuff(I have no idea how Bluetooth works yet) and to change the radio frequency. Though this board is pretty powerful, and I am using it for some simple tasks, I have a few good reasons for why I am doing this: Firstly, it's cheap and you can find it in almost any electronics shop. Secondly, it has many SDA and SCK pins, used for data transfer, and GPIO pins, so I can add many features along the way. 

![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MjE1MiwicHVyIjoiYmxvYl9pZCJ9fQ==--dcd348d813a380ff1b2a7be681853c474f7d5cd6/image.png)

Next up, the FM and Bluetooth modules. The connections between these and the amp are like so: The left and right signals(for the speakers) go in the RIN and LIN("Right in" and "Left in" I suppose), then these signals get amplified and are sent to the speakers.

Terminology(I don't really know what I'm talking about, but I wanna give it a go):
- SCK(Serial Clock Line) paired with SDA(Serial Data Line) work to transfer data, through I2C protocol
-"The SDA line is used for sending data to transfer data between devices. It operates as a bidirectional line, meaning it can both send and receive data. On the other hand, the SCL line manages the timing of data transmission by providing a clock signal that synchronizes data rate during communication between devices. This synchronization ensures that data is transferred in a sequential and orderly manner" - https://wraycastle.com/blogs/knowledge-base/sda-and-scl?srsltid=AfmBOoqemJHwtWvf81pw7lNSScnJ2-QjRkQsLG_y-5AP4NSznUwUabNI

In short, I just did some research on what microcontroller I should use, I made the schematic in KiCad and tried to explain how those weird systems work, even though I don't understand them at all
![Screenshot 2026-03-29 121356.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MjE2MSwicHVyIjoiYmxvYl9pZCJ9fQ==--1a5e3f2d23e1c69b80e7cb9dbd50422f8a194ca4/Screenshot 2026-03-29 121356.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/-__ab0tXTE35/timelapse--__ab0tXTE35.mp4
- https://public.lapse-hackclub.link/timelapses/LoyRIq98bWQT/timelapse-LoyRIq98bWQT.mp4

## Entry 4
- ID: 1247
- Author: mihai.a.ghetu
- Created At: 2026-04-05T16:34:21Z

### Content

Done with most of the schematic! This time, I wanted to design some footprints, and I decided to begin with the PAM8406 amplifier. Unfortunately, I couldn't find any site/datasheet that mentioned pin dimensions and distances. I tried to count pixels, in order to find the sizes, but I was not successful.
I moved on to creating the blueprint for the RDA, found some dimensions, didn't work out how I wanted it to, then moved on to the JDY-62. This time, it worked, and I am pretty happy with the result:
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mjc1NCwicHVyIjoiYmxvYl9pZCJ9fQ==--6ab161788922e32f24ab707b5d74414cd101fffd/image.png)
In the second timelapse though, I remembered that the bottom row of pins on the bluetooth module was not used, so I deleted it from the footprint.
Also, I made the footprint for the radio receiver(off-camera, I forgot to record). I will solder the RDA on the SDM pads, and I will route them to some through-hole pads that are more spaced out.

Lastly, I looked for a bigger display, but at the end I settled for the 0.96'' OLED, because a bigger one is not very accessible.



### Recording Links

- https://public.lapse-hackclub.link/timelapses/IoKsX5JEUp4R/timelapse-IoKsX5JEUp4R.mp4
- https://public.lapse-hackclub.link/timelapses/kC0h3oUY4GXy/timelapse-kC0h3oUY4GXy.mp4

## Entry 5
- ID: 1252
- Author: mihai.a.ghetu
- Created At: 2026-04-05T17:33:13Z

### Content

I started by searching for some rechargeable batteries, and i landed on the 18650 cell. It's Li-ion. I want to charge with USB-C, so I searched for a USB-C charger with safety features. With 2500mAh, it should be able to last a while. After that, I found a generic battery holder and moved on to the schematic. I created a new symbol for the charger and tried to find the footprint for the OLED. I realized that I don't need any footprint, since I don't want to have it on the PCB. On second thought, I should make  a 4 pin connector, so I can wire it up easily. After that, I started routing, when I saw that the pin numbers on the JDY-62 were inverted. With that problem fixed, I was onto the routing, which took a while, because I decided to add a connector for the left and right audio channels, and because the first routing was pretty bad, so I erased it all and worked more patiently.

![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mjc2MywicHVyIjoiYmxvYl9pZCJ9fQ==--d72901633c5d9f1aaf92fbb227eb9075cd936721/image.png)
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mjc2MiwicHVyIjoiYmxvYl9pZCJ9fQ==--4acf5b18d923384c05c951b7a159310e5b487bab/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/_icO1d-l4hKW/timelapse-_icO1d-l4hKW.mp4

## Entry 6
- ID: 1329
- Author: mihai.a.ghetu
- Created At: 2026-04-06T14:53:15Z

### Content

I wanted to record myself writing the journal, because I forgot to do it these past few times. While writing, I realized that the footprint for the RDA was done wrong, because pins that are spaced out by 2.54 mm wouldn't fit perfectly, since the spacing was 4mm. After I reedited the footprint, I had to redo part of the routing, but it wasn't difficult. After that, I wrote the journal, added the components names on the PCB and that was it! The PCB is complete, because of 2 things

-I can't find the dimensions for the PAM, so I will wire it up normally

- The OLED, the speakers and the charger will not be on the PCB, because I want to place them wherever I want(I Don't know yet)

![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Mjk0MCwicHVyIjoiYmxvYl9pZCJ9fQ==--3feb9af7a6cef6bb3fb91228e10a6ce66534a833/image.png)

### Recording Links

- https://public.lapse-hackclub.link/timelapses/6gxSDTa49NLY/timelapse-6gxSDTa49NLY.mp4

## Entry 7
- ID: 1583
- Author: mihai.a.ghetu
- Created At: 2026-04-09T14:35:27Z

### Content

Because I'm probably done with the PCB(unless I have made a big mistake somewhere), I started working on the 3D model, finally. I wanted to insert the PCB in the design from the start, but I found it distracting and not very helpful, so I just made an enclosure for it. Because I don't know the size of the speakers, I just made a rough model. I really like the current design and the colors, but I can't decide if I should spray paint it or order colored filament. Anyways, there is time to think, so I'm not thinking too much about that.
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MzQ1NSwicHVyIjoiYmxvYl9pZCJ9fQ==--b28aac93d41ade48cd897825a55d7857ce6a1543/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/G2kzSc_Tq7PS/timelapse-G2kzSc_Tq7PS.mp4

## Entry 8
- ID: 1963
- Author: mihai.a.ghetu
- Created At: 2026-04-12T22:09:33Z

### Content

I had a very successful design session! I made the case a bit smaller, because I didn't need that size, then I made enclosures for some 5cm speakers and added a hole for the USB-c charger. After that, I filled in the space in the grille that isn't in front of the speakers, I made a quick model of the charging model and I designed the hole for the OLED and I began designing the volume and frequency changer knobs, aka some rotary encoders. At first, I wanted to have them pop out of the case, using a design similar to clicking pens, so I found this cool video that explains how that works: https://www.youtube.com/shorts/sFI1KhIpUjw
I started designing the "bottom cam" of the clicking mechanism, but halfway through this process I realized that it would render the clicking action on the encoders, which is a function I want, unusable. So, I resorted to making them stick out two millimeters, for a sleek look that also makes it more portable, since the knobs don't stick out much.

![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDE5MSwicHVyIjoiYmxvYl9pZCJ9fQ==--41bcf86b24b906eb0ecd7ea3d2b394a460196a05/image.png)
With that out of the way, I started placing all the components in their spots. The battery holder was quite tricky, but I managed to put it somewhere accessible. After coloring the parts, I thought I was done. There was something missing, though. I forgot to add the rotary encoders into the schematic and I totally forgot that I had to have a power button. Also, the charger doesn't have a proper holder. Fortunately, these things will be very easy to add on, so I will be done with the 3d model soon, and will be able to move on to the programming side of things, before finishing this up and submitting the project.

![Screenshot 2026-04-13 010406.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDE4OCwicHVyIjoiYmxvYl9pZCJ9fQ==--8a7b60abbfbf05b5f39838ca2dbcaa3949e614b8/Screenshot 2026-04-13 010406.png)
![Screenshot 2026-04-13 010449.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDE4OSwicHVyIjoiYmxvYl9pZCJ9fQ==--1177c6708fc192f4eb53297c5a6a9af5bda8b615/Screenshot 2026-04-13 010449.png)
![Screenshot 2026-04-13 010503.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDE5MCwicHVyIjoiYmxvYl9pZCJ9fQ==--b14fac162d8691045f9e99544c92e70f9b05f8f1/Screenshot 2026-04-13 010503.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/prkbMJz9iHs7/timelapse-prkbMJz9iHs7.mp4

## Entry 9
- ID: 2189
- Author: mihai.a.ghetu
- Created At: 2026-04-14T14:58:54Z

### Content

Again, I keep forgetting to add some very important things. For example, I saw that the charger had no way of being secured in that position, so I made it's exit hole on the backside of the case. Also, I spent a while researching on a on/off switch, which I also forgot about. I fortunately found it, but I feel like it's going to be pretty difficult to design a cap for it, since it has a very weird shape. After designing the enclosure, I moved on to adding the switch and the rotary encoders to the schematic. That's it, I wasn't very time efficient today, but I made some progress, so it's all good

I don't have anything notable to show, so here is the switch
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDYzNSwicHVyIjoiYmxvYl9pZCJ9fQ==--c4b2bf12ea01b719e1dffa11ae01ff26d40d8eaf/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/VGzu4vcs8Xy-/timelapse-VGzu4vcs8Xy-.mp4

## Entry 10
- ID: 2190
- Author: mihai.a.ghetu
- Created At: 2026-04-14T15:39:43Z

### Content

I am stupid. I wasted a lot of time today. Wow.

Ok so... I found out that I forgot something(again). I had no way to switch between Bluetooth and radio, so I wanted to get a switch that would switch between the 2 audio inputs. I had one problem though. The audio is stereo, so I would have to swap between 2 sets of inputs. In the end, I went with probably the worst option I could have chosen. I had two on-on switches that had both the left or right signals fed in, and these switches would be mechanically linked, making it impossible to have one signal in your left ear, another in your right
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDYzNywicHVyIjoiYmxvYl9pZCJ9fQ==--f8015a423bd6772ca825006c2cf98f437ce757c3/image.png)
What's with the third switch? Well, I want to also detect what mode is active, but I can't just wire audio signal to a GPIO, so I had to get a THIRD mechanically coupled switch that would tell the pin what state it's in. I updated the design too. It's a very big, probably unreliable switch, but I thought that was my only option.

The answer was right in front of me the whole time: Just cut supply power. I will use a voltage step-down thingy for that, and this will make the whole thing so much simpler.

Step-down thingy:
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDYzOSwicHVyIjoiYmxvYl9pZCJ9fQ==--45ffb93a2a420e054fa224f9aa11c25fa9e049bd/image.png)
Next time I hope I can finish this up, once and for all, and begin the second part of this, understanding how to code everything.

### Recording Links

- https://public.lapse-hackclub.link/timelapses/vDwFCMrRjwTy/timelapse-vDwFCMrRjwTy.mp4

## Entry 11
- ID: 2912
- Author: mihai.a.ghetu
- Created At: 2026-04-19T17:21:58Z

### Content

I'm really glad to be able to say that I am done with hardware. Actually, there is one more thing I could add... A status LED, but that's very easy to do. Also, maybe some screw holes for mounting the front and back plates.

Now to what I did in this timelapse. I started by adding the voltage reducer and the resistor to the schematic. The RDA5807's V+ pin is connected to a pin that should detect when current is flowing, but I also included a resistor that's hooked up to ground.

Next, I redid some of the wiring, because I had to include the resistor in the routes, and moved on to updating the 3D model. I redesigned the hole for the slider switch so it will house only one of these switches.

This concludes that session, and I will move on to program the components, probably starting with the RDA, then moving on to the amp and then to the display.
![Screenshot 2026-04-14 230810.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NjA3NiwicHVyIjoiYmxvYl9pZCJ9fQ==--cd641ff6954d87ccdeaf7ba479d5fa8a1c26be05/Screenshot 2026-04-14 230810.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/3cbiWOIoikEG/timelapse-3cbiWOIoikEG.mp4

## Entry 12
- ID: 3768
- Author: mihai.a.ghetu
- Created At: 2026-04-24T20:51:07Z

### Content

I'm going to stop saying that I'm done with anything, because it seems that I always find something that still needs to be done. This time, my plan was to journal for a bit and try to figure out how the RDA5807 is programmed. I did do these things, and I didn't understand a single thing about that FM receiver, but what I did do, was to add a status LED to the schematic and to the PCB (I put it on the backside so it can shine out the back of the case). In addition to that, I realized that the power switch had a wrong footprint, so I fixed that and moved it closer too the VSYS pin, which I'm 90% sure it's the power input pin. Also, wiring for a resistor was wrong, because it had to actually be connected to ground, so I wouldn't have any floating values. Connecting the receiver mode detector line to ground basically  adds a drain for power that otherwise would stay in the wire and trip up the pin.

Next up, I found some brass heated inserts and went in fusion. I then added holes for the heated inserts both on the front and the back of the case.

Now, I still have  to do  some hardware stuff: The PAM8406 can not be coded to adjust volume. This is not a big problem, because I can very quickly change out the wiring for the PAM with any other amplifier, thanks to me not finding any footprints and whatnot.

I found a pretty good alternative on Ali Express, it seems legit, so I might be getting that. The alternative is to get an official one from Adafruit, but the shipping is A LOT, so I think I'm sticking to Ali Express. If I find any footprints for that module, I will probably add it to the PCB, so I'll have to make some space for it. On second thought, I might actually just use the bare chip, with no module and just make a breakout board, using only the pins I need. I would have to order from some company named "Mouser electronics", and, though the delivery is 25 euros, I might be able to find all the parts I need on there, since this is a very big electronics shop.

So, I am not yet done with anything, and I hate trying to understand code. That's most of the things I said, summed up. 

![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6Nzc4MCwicHVyIjoiYmxvYl9pZCJ9fQ==--ab3ac9422779c5d9c0e13b361f635dd3ed743193/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/Or6XsYtRdT_9/timelapse-Or6XsYtRdT_9.mp4

## Entry 13
- ID: 6320
- Author: mihai.a.ghetu
- Created At: 2026-05-09T20:10:05Z

### Content

Firstly, I want to apologise for my bad English in all of the journals. I tried re-reading them and even I couldn't really understand what I said. I will try to make journals more coherent from now on.

Now, let me explain what I did in the past few days. Firstly, I  did some research on the new I2C amp I found, the TPA2016. I can either buy it from adafruit, but delivery is expensive, or from AliExpress. I think you know what I chose. I also tried to maybe find some bigger displays, like a 1.3'' one, but it's pretty hard to find and more than double the price of a .96'' display, so I will settle for the smaller one. Btw I considered the option of buying the small TPA2016 IC, since it was very cheap, but I figured that I would have to spend a lot of money on smd soldering tools, and the scope of this project is to have this device be accessible to anybody. So, I just stuck to the breakout board. I also saw that the circuit for the voltage transformer included some capacitors(I think they are for smoothing out the signal), so I found some on a website and added them to the list.

After this short research session, I added capacitors to the schematic:

![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MTIyMTQsInB1ciI6ImJsb2JfaWQifX0=--e58bd1297f56dd539b8c63871c6a7f6e24350a8b/image.png)

Then, I routed the capacitors and did a couple of tweaks to the schematic. Firstly, I had no reason to include through-hole pads, in extension to the ones on the RDA, so I got rid of them

Before
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MTIyMTUsInB1ciI6ImJsb2JfaWQifX0=--8850517fc4f5eec2c48bc2ee31ab1cbda3e576da/image.png)
After
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MTIyMTYsInB1ciI6ImJsb2JfaWQifX0=--9645633dafd07a3d68e7c81dacb4177cc88f2617/image.png)
Because of this, I had to reroute the connections to the FM receiver(only partially, most of the routes were unchanged). With that out of the way, I moved on to the amplifier board. After updating the symbol and the schematic, I designed the footprint for it, which was pretty hard, because the dimensions are in inches, and I didn't understand that for a while. The hardest part was finding the sizes for the audio connectors, since I had to find the dimensions for those generic terminal blocks.
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MTM0MTksInB1ciI6ImJsb2JfaWQifX0=--ce1a410565d1206a1822bb54331635151ff4bb92/image.png)
 Finally, I managed to design an accurate footprint and placed it in the PCB design. I will continue by routing everything and making space for this big new component. I learned a lot about KiCad, because I found the "Move" commands, which helped me move pads exact distances, while the "group" function helped me save a lot of time.

### Recording Links

- https://public.lapse-hackclub.link/timelapses/wi5ASixtqz1Z/timelapse-wi5ASixtqz1Z.mp4
- https://public.lapse-hackclub.link/timelapses/jLCmVbUxLXan/timelapse-jLCmVbUxLXan.mp4
- https://public.lapse-hackclub.link/timelapses/_8Fr48Rc7RKd/timelapse-_8Fr48Rc7RKd.mp4

## Entry 14
- ID: 6338
- Author: mihai.a.ghetu
- Created At: 2026-05-09T21:42:41Z

### Content

I am cautiously optimistic when saying I finished designing the PCB. This timelapse, I focused on making space for the TPA2016 breakout board, so there isn't much to be said about that. I think I will just try to explain what's what and how everything communicates:
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MTM0MjksInB1ciI6ImJsb2JfaWQifX0=--c309e44f32f44f691c086c279e51dba2de4f9e87/image.png)
Opening the image in a new tab will help

So... Let's start with the easiest to understand: the JDY-62 Bluetooth board. It is standalone, it doesn't need any programming, so no connections to the microcontroller, except for the 5V power input and ground, but no data lines. It has stereo signal, so it sends both right and left signals to the amplifier, and that's it!

The FM radio receiver: It's a bit more complicated, and I also don't fully understand it. I just found some working code online, couldn't understand what the random arrays were, so I asked an AI to explain the whole thing to me, and I think I somewhat get it now. This is the site I got the code from: https://www.instructables.com/Arduino-Based-Digital-Audio-FM-Radio-Using-RDA5807/, and here is the downloadable chat, where everything is explained comprehensively(hopefully): https://claude.ai/share/0e49ee5e-f6e1-4f8f-93b9-12f7cab0ad05. It gets its power (3.3V) from a voltage transformer. I used this transformer because I wanted to have a way to switch between BT and FM, and cutting power to either one was the most convenient option. Because they operate on different voltages, I had to unfortunately use a transformer, which comes with its own complications. Since I couldn't find the breakout board, I decided to use an IC, but I also had to get some through hole capacitors, because those were included in the board. This is a bit of a problem because it occupies quite some space, as opposed to the module board, which was using SMD capacitors.

Next, I would like to talk about the amplifier: I don't think it's very complex, I haven't done a whole lot of research, but Adafruit gives some good instructions on their website: https://learn.adafruit.com/adafruit-tpa2016-2-8w-agc-stereo-audio-amplifier

The rest of the things are either pretty intuitive, so I will skip over them.

How everything connects: The RDA communicates via I2C, same as the amp and the OLED. There is a connection between the RDA 3.3V line to a pin on the Pico. That pin detects if there is current flowing to the RDA, and that means that the device is on "radio" mode. This is so I can display this info on the OLED screen. It is also connected with a resistor to ground, and that is because if I just cut power, I would have a floating voltage  value, which fluctuates or something, so I have to hook it up to ground, in order for that current to be "released".

Everything else is quite easy to understand, so I will leave it at that.
![image.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6MTM0NTcsInB1ciI6ImJsb2JfaWQifX0=--3399b9089bb067bf8e66ff09219a04688cb4f83c/image.png)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/qmmZnqNjYeni/timelapse-qmmZnqNjYeni.mp4

## Entry 15
- ID: 16682
- Author: mihai.a.ghetu
- Created At: 2026-07-18T14:20:30Z

### Content

Coding is a very big issue... I don't know how to do it. I Tried to understand it, but I feel like if I just get the parts and take some time to understand how each works, individually, then I will be able to write something that will hopefully work, without using AI.

Other than that, I did some work on the case, making it a lot smaller than before and adding some holes, so it would use less filament. Also, I designed it to fit bigger and more accessible speakers, that would also have a proper way to be screwed on the case.

After filling out the Bill of Materials, i will have finally completed the GitHub page, and I will be publishing it soon, then submitting the project.

Here's a render of the final product:

![WhatsApp Image 2026-07-18 at 17.19.38.jpeg](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDE1NjYsInB1ciI6ImJsb2JfaWQifX0=--1586e59f663480e2a6917bbb25fe89f32dd767a9/WhatsApp Image 2026-07-18 at 17.19.38.jpeg)


### Recording Links

- https://public.lapse-hackclub.link/timelapses/XqNseBr7tUAg/timelapse-XqNseBr7tUAg.mp4
- https://public.lapse-hackclub.link/timelapses/RL0GZHAzuqBp/timelapse-RL0GZHAzuqBp.mp4
- https://lookout.hackclub.com/api/media/6ccce00b-6e24-4914-83f7-94a3ef04500d/video.mp4

## Entry 16
- ID: 16745
- Author: mihai.a.ghetu
- Created At: 2026-07-20T20:34:23Z

### Content

This is basically just the making of the BOM in 2 separate timelapses, plus writing this journal. Also, I had to change something on the PCB. A while ago, I thought that, for the voltage step-down thing, it would be better to just get an IC and add the other components, instead of buying the whole module. I ultimately went for the second option, since it was not only cheaper and easier, it was also guaranteed to work. After finishing the BOM, I took pictures of the checkouts, and made a big organized folder, with all the stuff that would end up on GitHub. I just have to export the finalized journal, export the BOM, look over the README again and I am ready to submit! I will be doing these last few things off camera, since I have to include this recording in the journal.
![cBS1YqheXJ1rhOgWfBbTkjmEYBWXLj4KehT2F-kBDkU.png](/user-attachments/blobs/redirect/eyJfcmFpbHMiOnsiZGF0YSI6NDE3NjQsInB1ciI6ImJsb2JfaWQifX0=--418b1d0fc773ab643d20857b8872eed158081b9c/cBS1YqheXJ1rhOgWfBbTkjmEYBWXLj4KehT2F-kBDkU.png)


### Recording Links

- https://lookout.hackclub.com/api/media/93c5a108-901d-4e5e-b8a0-e321726f661c/video.mp4
- https://lookout.hackclub.com/api/media/1cb9a83c-2ac3-417e-88fb-2d9a21ba8471/video.mp4
