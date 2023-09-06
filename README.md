**staramp** detects stars within a night photo and then amplifies only the star pixels by some defined percentage, without altering the background.

<img src="https://gitlab.com/bashrc2/staramp/-/raw/main/images/example.jpg?ref_type=heads" width="70%"/>

## Installation

``` bash
git clone https://gitlab.com/bashrc2/staramp
cd staramp
make
sudo make install
```

## Usage

An example of use can be seen within the *test.sh* script.

``` bash
staramp --dog 8 --dogthresh 145 --dogamp 80 --miny 0 --maxy 2100 -f images/stars1.png
```

It produces a file called *result.png**

**--dog** specifies the radius for the *difference of gaussians** filter. It should be approximately the same as the width of the stars in pixels within your image.

**--dogthresh** applies a threshold to the *difference of gaussians** filter, so that faint pixels which might just be noise can be excluded.

**--miny** sets the minimum Y axis coordinate to begin processing at. This is typically 0 (the top of the photo).

**--maxy** sets the maximum Y axis coordinate to end processing at. This can be 0 which means process the whole image, or it can be some other value to exclude any scenery at the bottom of the photo.

**-f** defines the night image to be processed. This must be in PNG format.
