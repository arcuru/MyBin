#! /usr/bin/env python
from PIL import Image
import glob, os, sys

filename=sys.argv[1]

file, ext = os.path.splitext(filename)
im = Image.open(filename)
pix=im.load()
print pix[0,0]
for x in range(im.size[0]):
	for y in range(im.size[1]):
		a=1
	
#im.save(file + ".edited.jpg","JPEG")