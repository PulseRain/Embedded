#===========================================================================
# Copyright (c) : Pulserain Technology, LLC. 2015
#===========================================================================
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import sys

def string_to_number (str_in):
    accum = 0
    for i in range (0, len(str_in)):
        accum = accum + (ord(str_in[i]) << (i * 8))
   
    return accum
   

if (len(sys.argv) != 3):
        print "usage python wav2sample.py wave_file_name sample_output_file_name"
        os._exit(1)

       
bytes = open(sys.argv[1]).read()

chunk_ID = bytes [0:4].upper()

chunk_size = string_to_number (bytes[4:8])

format = bytes [8:12].upper()


subchunk1_ID = bytes [12:16].lower()  

subchunk1_size = string_to_number (bytes[16:20])
           

audio_format =  string_to_number(bytes[20:22])
           
num_of_channels = string_to_number(bytes[22:24])
         
sample_rate = string_to_number(bytes[24:28])

byte_rate = string_to_number(bytes[28:32])

block_align = string_to_number(bytes[32:34])

bits_per_sample = string_to_number(bytes[34:36])

subchunk2_ID = bytes [36:40].lower()  

subchunk2_size = string_to_number (bytes[40:44])
           
if (chunk_ID != "RIFF") :
    print "NOT RIFF format!\n"
    os._exit(1)

if (format != "WAVE") :
    print "NOT WAVE format!\n"
    os._exit(1)


if (subchunk1_ID != "fmt ") :
    print "unknown subchunk1 ID : " + subchunk1_ID
    os._exit(1)
   
if (subchunk1_size != 16) :
    print "incorrect subchunk1_size for PCM format: size = {0:d}".format(subchunk1_size)
    os._exit(1)

print "\nAudio Format is {0:d}, (1 = PCM)".format(audio_format)

print "\nnumer of channels = {0:d}".format(num_of_channels)

if (num_of_channels > 1) :
    print "More than one channel!"
    os._exit(1)


print "\nSample Rate = {0:d}, byte rate = {1:d}".format(sample_rate, byte_rate)
   
print "\nBlock Align = {0:d}, Bits_Per_Sample = {1:d}".format(block_align, bits_per_sample)

if (subchunk2_ID != "data") :
    print "subchunk2 is not data!"
    os._exit(1)

 
num_of_samples = subchunk2_size / block_align

output = open(sys.argv[2], "w")


for i in range (0, num_of_samples) :
    data = string_to_number(bytes[44 + i * block_align : 44 + i * block_align + block_align])
    if (bits_per_sample == 8):
        output.write("i = {0:d}\t data = {1:d}\n".format(i, data))
    elif (bits_per_sample == 16):
        if (data > 32767) :
            data = data - 65536
        output.write("i = {0:d}\t data = {1:d}\n".format(i, data))
   
   
print "\n===> {0:d} samples saved to {1:s}".format(num_of_samples, sys.argv[2])