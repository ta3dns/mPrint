# mPrint
A lightweight print utility that turns text into GCODE for 3D printers, Plotters and CNC machines.

Developed by [Marinum](https://marinum.org)


## Why I built this? 
I wanted a way to print documents in a completely open source and secure way. I was okay with the speed and resolution trade offs compared to a printer. For my use case, I just wanted absolute control over my hardware. 

I built this tool to solve a problem for myself. I hope it will be useful to someone in a similar context. 


## How it works? 

The hardware abstraction layer, font and rendering logic are separated. You load a font (the system currently only supports Hershey Fonts, developed in 1967 by Dr. Allen Vincent Hershey. i.e a `.jhf` file). Pass the font along with the text to the renderer which then passes the coordinates to the hardware abstraction layer. Because they are separated it is fairly trivial to adapt any device that uses coordinates to this utility as a driver. 

## Build & Run

Compile the utility using `make`. There are zero external dependencies. 

## Attribution

The `.jhf` files used in this project, and thus the heavy lifting of the actual coordinate data for the characters were originally created by [Kamal Moustafa's Hershey-Fonts](https://github.com/kamalmostafa/hershey-fonts/tree/master?tab=readme-ov-file) repository.
## License

This software is released under **GNU GPLv3.0** please read [LICENSE](https://github.com/ta3dns/mPrint/blob/main/LICENSE) for the details. 

---

73s.
