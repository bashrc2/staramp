**staramp** detects stars within a night photo and then amplifies only the star pixels by some defined percentage, without altering the background.

<img src="https://gitlab.com/bashrc2/staramp/-/raw/main/images/example.jpg?ref_type=heads" width="70%"/>

## Installation

On a Debian based distro:

``` bash
sudo apt install build-essential
```

Then build and install:

``` bash
git clone https://gitlab.com/bashrc2/staramp
cd staramp
make
sudo make install
```

## Usage

An example of use can be seen within the **test.sh** script.

``` bash
staramp --dog 8 --dogthresh 145 --dogamp 80 --miny 0 --maxy 2100 -f images/stars1.png
```

It produces a file called **result.png**

**--dog** specifies the radius for the *difference of gaussians* filter. It should be approximately the same as the width of the stars in pixels within your image.

**--dogthresh** applies a threshold to the *difference of gaussians* filter, so that faint pixels which might just be noise can be excluded.

**--dogamp** the amplification percentage.

**--miny** sets the minimum Y axis coordinate to begin processing at. This is typically 0 (the top of the photo).

**--maxy** sets the maximum Y axis coordinate to end processing at. This can be 0 which means process the whole image, or it can be some other value to exclude any scenery at the bottom of the photo.

**-f** defines the night image to be processed. This must be in PNG format.

You can also exclude areas of the image within specified bounding boxes, by using the **--exclude** option:

``` bash
staramp --dog 12 --dogthresh 140 --dogamp 70 --miny 0 --maxy 0 --exclude "0,1590,1287,2013" -f images/stars2.png
```

Here the bounding box to be excluded has top left coordinate **0,1590** and bottom right coordinate **1287,2013**. If you specify additional numbers then you can have multiple exclusion areas. An example might be:

``` bash
--exclude "(0,1590,1287,2013),(50,100,300,500)"
```
