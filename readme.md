## Project Description
This is an remake of the game "Mini Metro" for an ICS 4U project.
The game is available through a variet of outlets, all of which you can find on the game's [official page](https://dinopoloclub.com/minimetro/).

## How to install (Visual Studio only)
This project uses SFML (Simple & Fast Media Library) to render graphics in C++.
Go to [the sfml download page](https://www.sfml-dev.org/download.php), and download the most recent version for your compiler. MAKE SURE YOU ARE USING THE CORRECT BIT VERSION (32-bit and 64-bit is different)
Afterwards, in your Visual Studio project go under `Project -> C/C++ -> General -> Additional Include Directories` and add `sfml folder>/include/`.
Next, include the libraries by going under `Project -> Linker -> Additional Library Directories` and include `<sfml folder>/lib/`.
Next, specify the .lib files you want to include by adding them under `Project -> Linker -> Input`. You should include `sfml-graphics-d.lib`, `sfml-system-d.lib`, `sfml-main-d.lib`, `sfml-window-d.lib`. If you want to build for **RELEASE** rather than **DEBUG**, then just remove the appended `-d`.
Once you are done, you should be able to build the project, but if you run, you will get an error. This is because your executable cannot find the run-time libraries needed. To help it find it, move the libraries from `<sfml folder>/bin/` next to your executable.

If you are still confused, there are official tutorials available for [Visual Studio](https://www.sfml-dev.org/tutorials/2.0/start-vc.php) (or if you reeeeeeallllllyyy prefer) [Code::Blocks MinGW](https://www.sfml-dev.org/tutorials/2.0/start-cb.php).

## File Specifications
maplist.txt will contain the name of the map on a line, followed by the location of the file on the next line

## Map File Details

The file will first give details. Details will be in the format

    VALUE_NAME:VALUE STRING
The value name will only be considered up to the first `:`. If no colons are found, the program should throw an error. Quotation marks are not necessary.
After inputting all the values, the file should separate the coordinates with 

    ###END DETAILS###
matching exactly.

The coordinates will then be given in pairs of floating point numbers separated by a space.

    1.00 1.00
    2.00 3.00
    0.50 0.12
	
## Notices

Only the NYC map is playable, typing coordinates off PDFs is very hard and tedious, but if you'd like you can type in your own maps.