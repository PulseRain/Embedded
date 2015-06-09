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


proc read_bin_data_from_file {fp num_of_chars}   {
	set x 0
	
	if {$num_of_chars} {
		for {set i 0} {$i < $num_of_chars} {incr i} {
			scan [read $fp 1] "%c" c
			if {![info exists c]} {
				return $x
			}
			set x [expr $x + $c *  [tcl::mathfunc::pow 256 $i]]
		}
		set x [tcl::mathfunc::entier $x]
	}

	return $x
}

proc read_str_data_from_file {fp num_of_chars}   {
	set x ""
	
	if {$num_of_chars} {
		for {set i 0} {$i < $num_of_chars} {incr i} {
			scan [read $fp 1] "%c" c
			
			if {![info exists c]} {
				return $x
			}
			set x "$x[format "%c" $c]"
		}
	}
	
	return $x
}