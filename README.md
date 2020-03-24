## Introduction

A simple tool to convert YUV image to JPEG image.

## Usage

```bash
mkdir build
cd build
cmake ..
make
```

Binary is created at `bin` directory from the root entrance.

```bash
yuv2jpg -h <heigh> -w <width> img_list
```



## Problems

It's only work with YUV420sp currently. More specifically, YUV420sp can be categorized into NV12 and NV21. I'm sure it works with NV21, but whether it can handle NV12 depends on the OpenCV's ability.



## TODO

As what I said, it's required to use OpenCV for the conversion. However, this can be done by known formula. Also, OpenCV offers limited YUV formats for conversion to BGR.

- [ ] Get rid of the dependency to OpenCV.
- [ ] Support more YUV formats.