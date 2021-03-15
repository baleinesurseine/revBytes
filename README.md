# revBytes utility #

Copyright &copy; 2021 &Eacute;douard FISCHER

revBytes is a small utility that transforms the output .ttf file from a Quartus ii compiled project into an app.h file suitable for integration into an arduino Vidor MK 4000 sketch.

This transformation is required since the bit order has to be reversed before burning the bitstream into the flash memory.

## usage ##

```linux
revBytes output.ttf app.h
```

`output.ttf` is put the `output_files` folder of the project by Quartus ii.

Help can be displayed with:

````linux
revBytes -h
````

or

```` linux
revBytes --help
````

## installation ##

`cd` into the top directory, at the same level as `Makefile`, then:

```linux
make clean
make
make install
````

The default installation dir for the executable is `/usr/local/bin`. The prefix can be changed from `/usr/local/` to another prefix with:

```linux
PREFIX=/another/prefix make install
````
