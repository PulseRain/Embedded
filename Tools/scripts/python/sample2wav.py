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

def number_to_string (num_in, str_out_len):
    str_out = ''
    for i in range (0, str_out_len):
        str_out = str_out + chr((num_in >> (i*8)) & 0xFF)
        
    return str_out
   

if (len(sys.argv) != 3):
        print "usage python sample2wav.py sample_input_file_name wave_output_file_name"
        os._exit(1)

data = open(sys.argv[1]).read()

num_of_samples =  len(data) / 2


chunk_ID = "RIFF"

chunk_size = number_to_string((num_of_samples * 1 * 16 / 8) + 36, 4) 

format = "WAVE"
subchunk1_ID = "fmt "
subchunk1_size = number_to_string(16, 4)



audio_format = number_to_string(1, 2) # PCM = 1
num_of_channels = number_to_string(1, 2)
sample_rate = number_to_string(8000, 4)
byte_rate = number_to_string(8000 * 2, 4)

block_align = number_to_string( 1 * 16 / 8, 2)

bits_per_sample = number_to_string (16, 2)

subchunk2_ID = "data"
subchunk2_size = number_to_string (num_of_samples * 1 * 16 / 8, 4)




bytes = []

bytes.append(chunk_ID)
bytes.append(chunk_size)
bytes.append(format)
bytes.append(subchunk1_ID)
bytes.append(subchunk1_size)
bytes.append(audio_format)
bytes.append(num_of_channels)
bytes.append(sample_rate)
bytes.append(byte_rate)
bytes.append(block_align)
bytes.append(bits_per_sample)
bytes.append(subchunk2_ID)
bytes.append(subchunk2_size)

non_data = ''.join(bytes)
  

output = open(sys.argv[2], "wb")
output.write(non_data)
output.write(data)
output.close()
   
   
print "\n===> {0:d} samples (8KHZ, 16bit Mono) saved to {1:s}".format(num_of_samples, sys.argv[2])

