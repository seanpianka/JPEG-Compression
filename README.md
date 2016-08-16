# JPEG Compression on .BMP Image Files
---

## Introduction

A C script written to read in the pixel array data from .BMP image files and use Discrete Cosine Transform and other methods to re-implement JPEG compression and output a compressed image file..

[BMP File Format](https://en.wikipedia.org/wiki/BMP_file_format)
[JPEG Compression](https://en.wikipedia.org/wiki/JPEG)


Explanation (from Wikipedia) on how JPEG compression works:
```
JPEG uses a lossy form of compression based on the discrete cosine transform (DCT). This mathematical operation converts each frame/field of the video source from the spatial (2D) domain into the frequency domain (a.k.a. transform domain). A perceptual model based loosely on the human psychovisual system discards high-frequency information, i.e. sharp transitions in intensity, and color hue. In the transform domain, the process of reducing information is called quantization. 

In simpler terms, quantization is a method for optimally reducing a large number scale (with different occurrences of each number) into a smaller one, and the transform-domain is a convenient representation of the image because the high-frequency coefficients, which contribute less to the overall picture than other coefficients, are characteristically small-values with high compressibility. The quantized coefficients are then sequenced and losslessly packed into the output bitstream. 

Nearly all software implementations of JPEG permit user control over the compression-ratio (as well as other optional parameters), allowing the user to trade off picture-quality for smaller file size. In embedded applications (such as miniDV, which uses a similar DCT-compression scheme), the parameters are pre-selected and fixed for the application.
```

---

## Usage

To use the script, first clone the repository:

```bash
git clone https://github.com/seanpianka/JPEG-Compression.git
```

Then, modify the image file-name of the target .BMP image file and compile the script:

```bash
nano compress.c
make
```

Then, run the script and view the outputted information.

```bash
./compress.x
Done.
```

TODO: 
Finally, view the JPEG compressed version of the original image file.

```bash
[command-to-view-image] compressed.jpg
```

---

## Example Output

```
::begin of BMP header (14)::
42 	4d 	
8a 	0 	0 	0 	
0 	0 	
0 	0 	
7a 	0 	0 	0 	
::end of BMP header::

::begin of DIB header (108)::
6c 	0 	0 	0 	
2 	0 	0 	0 	
2 	0 	0 	0 	
1 	0 	
18 	0 	
0 	0 	0 	0 	
10 	0 	0 	0 	
13 	b 	0 	0 	
13 	b 	0 	0 	
0 	0 	0 	0 	
0 	0 	0 	0 	
42 	47 	52 	73 	
0 	0 	0 	0 	
0 	0 	0 	0 	
0 	0 	0 	0 	
0 	0 	0 	0 	
0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	0 	2 	0 	0 	0 	
0 	0 	0 	0 	
0 	0 	0 	0 	
0 	0 	0 	0 	
::end of DIB header::

Bits per pixel: 0x18
Color Planes: 0x1
Bitmap Width: 0x2
Bitmap Height: 0x2

::begin of pixel array (16)::
1 	1 	fe 	ff 	
fe 	fe 	0 	0 	
ff 	0 	0 	1 	
fe 	0 	0 	0 	
::end of pixel array::
```

---

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## License

Available for personal-use only. Do not reproduce, re-use, re-purpose, or sell
JPEG-Compression. Contributions towards this project may only be made to this repository.
