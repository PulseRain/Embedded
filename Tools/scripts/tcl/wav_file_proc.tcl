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

proc wav_PCM_file_read {file_name {samp_size_in_byte 2} {verbose 1}} {
	set fp [open $file_name rb]
	
	set data_samp {}
	set chunk_ID [read_str_data_from_file $fp 4]
	assert [string equal $chunk_ID "RIFF"] "!!! not RIFF format!"

	set chunk_size [read_bin_data_from_file $fp 4]
	set fmt [read_str_data_from_file $fp 4]

	assert [string equal $fmt WAVE]

	while 1 {

		set chunk_ID [read_str_data_from_file $fp 4]
		if {$chunk_ID ne ""} {
			if {$verbose} {
				puts "==========================="
				puts "!!!!!!!!! process chunk $chunk_ID"
			}
		}
				
		if {$chunk_ID eq "fact"} {
			if {$verbose} {
				puts "skip fact chunk"
			}
			set chunk_size [read_bin_data_from_file $fp 4]
			read_bin_data_from_file $fp $chunk_size
		} elseif {$chunk_ID eq "fmt "} {
			set chunk_size [read_bin_data_from_file $fp 4]
			
			set audio_format [read_bin_data_from_file $fp 2]
			
			# 1 = PCM
			assert [expr $audio_format == 1] 
			if {$verbose} {
				puts "Audio Format $audio_format"
			}
			
			set num_of_channels [read_bin_data_from_file $fp 2]
			if {$verbose} {
				puts "Num of Channel $num_of_channels"
			}
			
			set sample_rate [read_bin_data_from_file $fp 4]
			if {$verbose} {
				puts "Sample Rate $sample_rate"
			}
			
			set byte_rate [read_bin_data_from_file $fp 4]
			if {$verbose} {
				puts "Byte Rate $byte_rate"
			}
			
			set block_align [read_bin_data_from_file $fp 2]
			if {$verbose} {
				puts "Block Align $block_align"
			}
			
			set bits_per_sample [read_bin_data_from_file $fp 2]
			if {$verbose} {
				puts "Bits Per Sample $bits_per_sample"
			}
			
			read_bin_data_from_file $fp [expr $chunk_size - 16]
			
		} elseif {$chunk_ID eq "data"} {
			set chunk_size [read_bin_data_from_file $fp 4]
			if {$verbose} {
				puts "chunk_size $chunk_size"
			}
			for {set i 0} {$i < [expr $chunk_size / $samp_size_in_byte]} {incr i} {
				lappend data_samp [read_bin_data_from_file $fp $samp_size_in_byte]
			}
		} elseif {$chunk_ID eq "LIST"} {
			set chunk_size [read_bin_data_from_file $fp 4]
			if {$verbose} {
				puts "get LIST chunk, skip $chunk_size bytes"
			}
			set dummy_data [read_bin_data_from_file $fp $chunk_size]
		} elseif {$chunk_ID eq ""} {
			break
		} else {
			puts "Unknown chunkID $chunk_ID"
			exit 1
		}
	}
	
	close $fp
	return $data_samp
}

proc wav_PCM_file_write {file_name data_samp {samp_size_in_byte 2} {samp_rate 8000}} {
	
	set fp [open $file_name wb]
		
	puts  -nonewline $fp "RIFF"
	set chunk_size [expr [llength $data_samp] * $samp_size_in_byte + 36]
	puts  -nonewline $fp [binary format i $chunk_size]
	
	puts  -nonewline $fp "WAVE"
	puts  -nonewline $fp "fmt "

	# fmt chunk size 
	puts  -nonewline $fp [binary format i 16]
	
	# audio format 
	puts  -nonewline $fp [binary format s 1]
	
	# num of channels
	puts  -nonewline $fp [binary format s 1]
	
	# samp rate
	puts  -nonewline $fp [binary format i $samp_rate]
	
	# byte rate
	puts  -nonewline $fp [binary format i [expr $samp_rate * $samp_size_in_byte]]
			
	# block align
	puts  -nonewline $fp [binary format s $samp_size_in_byte]
	
	#bits per sample
	puts  -nonewline $fp [binary format s [expr $samp_size_in_byte * 8]]
	
	#data chunk
	puts  -nonewline $fp "data"
	set chunk_size [expr [llength $data_samp] * $samp_size_in_byte]
	puts  -nonewline $fp [binary format i $chunk_size]
		
	for {set i 0} {$i < [llength $data_samp]} {incr i} {
		if {$samp_size_in_byte == 1} {
			puts  -nonewline $fp [binary format c [lindex $data_samp $i]]
		} elseif {$samp_size_in_byte == 2} {
			puts  -nonewline $fp [binary format s [lindex $data_samp $i]]
		} elseif {$samp_size_in_byte == 4} {
			puts  -nonewline $fp [binary format i [lindex $data_samp $i]]
		} else {
			puts "can not handle $samp_size_in_byte bytes of sample size"
			exit 1;
		}
	}
	
	close $fp

}

proc PCM_sample_dual_channel_file_write {file_name data_samp {samp_size_in_byte 2} {samp_rate 8000}} {
	
	set fp [open $file_name wb]
			
	for {set i 0} {$i < [llength $data_samp]} {incr i} {
		if {$samp_size_in_byte == 1} {
			puts  -nonewline $fp [binary format c [lindex $data_samp $i]]
			puts  -nonewline $fp [binary format c [lindex $data_samp $i]]
		} elseif {$samp_size_in_byte == 2} {
			puts  -nonewline $fp [binary format s [lindex $data_samp $i]]
			puts  -nonewline $fp [binary format s [lindex $data_samp $i]]
		} elseif {$samp_size_in_byte == 4} {
			puts  -nonewline $fp [binary format i [lindex $data_samp $i]]
			puts  -nonewline $fp [binary format i [lindex $data_samp $i]]
		} else {
			puts "can not handle $samp_size_in_byte bytes of sample size"
			exit 1;
		}
	}
	
	close $fp

}
