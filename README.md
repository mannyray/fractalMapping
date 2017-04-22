# fractalMapping

### Table of Contents:
1.  [Description](#d)
2.  [Comments on the code](#lc)
3.  [Library feautures](#lf)
	1. [regularFractal](#rf)
	2. [regularFractalWithRotation](#rfwr)
	3. [wavelet](#w)
	4. [letterMapping](#lm)


<h2>
<a name="d">
Description
</a>
</h2>

Set of libraries and code for running fractal compression and other related code. The fractal compression code is a lossy way of compressing images that keeps track of similarity of bigger blocks within an image to smaller blocks. By storing these similarities as mappings we can recreate an image that is very similar to the original image. 


Two core libraries (_blockImage.h_ and _compareImages.h_) have been created to allow for multiple flavours (_letterMapping_, _regularFractal_, _regularFractalWithRotation_, _wavelet_) of fractal compression with the help of class inheritance. The _blockImage.h_ library is used to read/write/manipulate images and _compareImages.h_ is the class responsible for generating the 'similarity' mappings as well as recreating an image given a mapping. The inheritance comes into play with _compareImages.h_. Classes that inherit from this define specific virtual methods that provide ways of determining optimal mappings and ways of generating images given mappings. The purposes of creating the core libraries was to provide an easy way of implementing new methods of fractal compression and image compression.


An image to showcase compression results will be ['Lenna'](http://www.cs.cmu.edu/~chuck/lennapg/lenna.shtml), a common test image used when working with image processing algorithms:


![image](sample_images/lenna.png)





<h2>
<a name="lc">
Comments on the code
</a>
</h2>
Each fractal compression code implementation stored in directories (_letterMapping_, _regularFractal_, _regularFractalWithRotation_, _wavelet_) contains a _compress.cc_ file and _decompress.cc_ file. _compress.cc_ is responsible for creating a fractal mapping and _decompress.cc_ is responsible for reading in a mapping and producing an image encrypted in the mapping. 


To compile the compress/decompress programs (within directory the program is located) run the following:


```
g++ -std=c++11 -o (de)compress (de)compress.cc ../blockImage.cc ../compareImages.cc
```

Some additional requirements and commands may be required for the directories.

<h2>
<a name="lf">
Library Features
</a>
</h2>
Next few sections will discuss features and results of different fractal compression implementations. The algorithms written do not encode the mappings in the most space efficient format, but simple methods to do add this and results of such actions is discussed.


The fractal compression algorithms have a very 'slow' nature to them because they require finding optimal mappings between pixel blocks in an image. This requires checking all possible block to block comparisons. No additional comments on runtime will be made other than compress and decompress code can take a few seconds to run for a standart 512x512 pixel image such as 'lenna'.

<h2>
<a name="rf">
regularFractal
</a>
</h2>

<h5>
Compression:
</h5>
Here is a diagram that will be used to explain the algorithm:

![image](sample_images/fractal_mapping_exp_1.png)


<h6>
1.
</h6>
We start off with the original image (in this example it is 32 by 32 pixels) and split it into two copies. One with 8 by 8 pixels blocks and the other with 16 by 16 pixel blocks.

<h6>
2.
</h6>
We take the 16 by 16 split image and reduce each block to an 8 by 8 pixel approximation by averaging 2 by 2 pixel blocks into one pixel.

<h6>
3.
</h6>
For each possible pairing between an 8 by 8 block from original split and the 16 by 16 reduced split we compute a mapping. The mapping is defined as a scalar multiple **a** and grayscale shift **B** computed through simple linear regression (by treating each block as a vector). 


<h6>
4.
</h6>
We look at all of the possible mappings between a single 8 by 8 block **C** and all of the reduced blocks computed in part 3. We store the mapping for the **C** block that produces the smallest error. The error is defined as taking the Euclidean norm of the difference between **C** and the appropriate mapping(computed in part 3) on a reduced block. We need to store each ideal mapping for each **C** block. This requires storing the **a**, **b** and the position of the 16 by 16 reduced block (in our example the position of the green block in 16 by 16 split is 2).



Each 8 by 8 block requires to store its approximating 16 by 16 block, scaling and grayscale shift. The values of scaling and grayscale are doubles (8 bytes) and approximating block number can be stored as an integer (4 bytes). This means that for each 8 by 8 block you need to store (8+8+4=20) bytes as an upperbound. For lenna, a 512 by 512 pixel image with 4096 - 8 by 8 blocks, that requires 4096*20=81920 bytes for mappings whereas lenna stores in png format requires 264069 bytes.  The compression can be optimized even further at the expense of precision. The code can be modified to limit the number of digits stored in scaling/grayscale in order to save space.

<h5>
Decompression:
</h5>
Once you have a mapping, you can then recreate the image approximation using _decompress.cc_ with any starting image such as the following:

![image](sample_images/a.png)

The algorithm reads in the starting image, mappings and then for each 8 by 8 block _A_ in starting, grabs its matching 16 by 16 block _B_ and maps it onto the _A_ block. The starting image is then replaced with the results of mappings and the process is repeated multiple times to produce the following:



![image](sample_images/regular.png)
<h2>
<a name="rfwr">
regularFractalWithRotation
</a>
</h2>

This feature is similar to regularFractal, except now the 16 by 16 blocks can be compared to 8 by 8 blocks by rotation as well. The mappings now also need to store how the 16 by 16 block was rotated. This adds an addition 2 bits per 8 by 8 block. A very negligible cost given that the decompressed image now looks much better than regularFractal(look at the lips and eyes). 

![image](sample_images/regularWithRotation.png)
<h2>
<a name="w">
wavelet
</a>
</h2>
The code in this sections requires the use of matlab in order to create the wavelet compression. It breaks an image into its wavelet decomposition and approximates the different levels by creating mappings between the child and parent levels.


![image](sample_images/lenna_approx_3.png)
<h2>
<a name="lm">
letterMapping
</a>
</h2>

Given an image and a set of blocks, we can approximate the image with the best fitting blocks. In the example below we approximate 'lenna' with alphabet characters in 8 by 8 pixel blocks. The letter that is chosen to approximate an 8 by 8 block within 'lenna' is the letter than reduces the error when subtracting the difference between letter block and image block.

![image](sample_images/lenna_letter.png)


Hypothetically, a 512 by 512 pixel image with 4096 - 8 by 8 pixel blocks that takes up 264069 bytes in png format can be stored with 4096 characters. Each character takes a byte to store implying 4096 bytes of storage overall per image. You can observe that this compression comes with a huge expense in accuracy. Here is a [video](https://youtu.be/nBnlKsu7sYI) where each frame went through the letterMapping.


