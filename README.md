# Conway's Game of Life implemented in C by use of SDL2

### You MUST install the SDL2 library and cmake before going any further.

## Automated Installation (Linux possibly Mac)
* git clone https://github.com/9ziggy9/gol.git
* cd gol
* chmod +x install.sh
* ./install.sh
* ./conway


## Manual Installation (Linux possibly Mac)
#### To install manually make sure you have requisite SDL2 libraries and cmake. You MUST use the recursive flag to pull in the FindSDL2.cmake submodules. (Or git submodule update --init after the fact).

* git clone --recursive https://github.com/9ziggy9/gol.git
* cd gol
* mkdir build
* cd build
* cmake .. && make install
* cd ..
* ./conway

Note that by default, the binary is targeted at the originating folder.

## Installation for FreeBSD/Dragonfly
It's the damndest thing but I cannot figure out why my original makefile works here yet the cmake build does not. No matter, this can still be installed via a makefile located here: https://github.com/9ziggy9/C_Trash/blob/main/Makefile. Place that makefile in the directory and simply run make. Of course, on Dragonfly you will have to change the CC option to gcc.

## Notes
Space will run/pause the time evolution and allow you to populate the grid. Escape to exit. Window should be resizable now. Please report any bugs and I'll try to fix them immediately.

For more advanced usage such as changing cell size and rate of time evolution see ./conway -h:

Usage: conway [-t ticks] [-c cell_size] 

-t      Set number of ticks in microseconds.
        Enter extremely low values at own peril.
        Recommended to stay in 30000-100000 range.
        Defaults to 50000.


 -c     Set cell size to small, medium or large.
        Defaults to small.


The inclusion of the FindSDL2.cmake modules should make this port to just about anything. If you have an issue on your system, please let me know.

I have previously added a keydown event to clear screen, I will bring that back ASAP.
