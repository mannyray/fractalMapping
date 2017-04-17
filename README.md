# fractalMapping

### Table of Contents:
1.  [Description](#d)
2.  [Math involved](#mi)
3.  [Comments on the code](#lc)
4.  [Library feautures](#lf)
	1. [regularFractal](#rf)
	2. [regularFractalWithRotation](#rfwr)
	3. [wavelet](#w)
	4. [letterMapping](#lm)
4.	[Sources](#sources)


<a name="d">
##1. Description
</a>

Set of libraries and code for running fractal compression and other related code. The fractal compression code is a lossy way of compressing images that keeps track of similarity of bigger blocks within an image to smaller blocks. By storing these similarities as mappings we can recreate an image that is very similar to the original image. The math behind this will be explained later.


Two core libraries (_blockImage.h_ and _compareImages.h_) have been created to allow for multiple flavours (_letterMapping_, _regularFractal_, _regularFractalWithRotation_, _wavelet_) of fractal compression with the help of class inheritance. The _blockImage.h_ library is used to read/write/manipulate images and _compareImages.h_ is the class responsible for generating the 'similarity' mappings as well as recreating an image given a mapping. The inheritance comes into play with _compareImages.h_. Classes that inherit from this define specific virtual methods that provide ways of determining optimal mappings and ways of generating images given mappings. The purposes of creating the core libraries was to provide an easy way of implementing new methods of fractal compression and image compression.


An image to showcase compression results will be ['Lenna'](http://www.cs.cmu.edu/~chuck/lennapg/lenna.shtml), a common test image used when working with image processing algorithms:


![image](sample_image/lenna.png)



<a name="mi">
##2. Math Involved
</a>

In this section I will be brief and will mention additional reading for the curious reader.






<a name="lc">
##3. Comments on the code
</a>

Each fractal compression code implementation stored in directories (_letterMapping_, _regularFractal_, _regularFractalWithRotation_, _wavelet_) contains a _compress.cc_ file and _decompress.cc_ file. _compress.cc_ is responsible for creating a fractal mapping and _decompress.cc_ is responsible for reading in a mapping and producing an image encrypted in the mapping. 


To compile the compress/decompress programs (within directory the program is located) run the following:


```
g++ -std=c++11 (de)compress.cc ../blockImage.cc ../compareImages.cc
```







discuss about inefficiency about blockImage


<a name="lf">
##4. Library Features
</a>

Next few sections will discuss features and results of different fractal compression implementations.


<a name="rf">
### regularFractal
</a>



<a name="rfwr">
### regularFractalWithRotation
</a>


This feature is similar to regularFractal, except now the 16 by 16 blocks can be compared to 

<a name="w">
### wavelet
</a>



<a name="lm">
###4. letterMapping
</a>


