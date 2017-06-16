## Project Description
This is an remake of the game "Mini Metro" for an ICS 4U project.
The game is available through a variet of outlets, all of which you can find on the game's [official page](https://dinopoloclub.com/minimetro/).

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

Optional arguments can be attached to the coordinates by appending a colon at the end of the coordinates, putting details, then appending the details with

    ###END DETAILS###

For example:

    1.00 2.00:
    COLOR:RED
    SIZE:BIG
    IMPORTANCE:HIGH
    ###END DETAILS###