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
#
# Remarks:
#    This script is intended to tranverse a folder with given glob
# pattern and execute a certain command on each file selected by
# the glob pattern. The command line format will be:
#
# "perl dir_dig.pl executable_coomand options glob_pattern [-r | --recursive]"
#
# I've only tested it under Cygwin
# ($ echo $BASH_VERSION to get bash version as 4.1.10(4)-release )
# (Noted by C.Gu on 08/22/11)
#=============================================================================

use strict;

my $total_msg;
my $executable;
my $count;
my $recursive;
my @msg;

my $debug = 0;

($executable = shift @ARGV) || die "Usage: perl dir_dig.pl executable_coomand options glob_pattern (-r | --recursive) \n";

!(system "which $executable >/dev/null 2>/dev/null") || die "Can not locate $executable !!! \n";



$total_msg = 0;
#------------------------------------------------------------------------------
# getting the rest of the arguments
#------------------------------------------------------------------------------
while($_ = shift @ARGV){
    $msg[$total_msg] = $_;   
    ++$total_msg;
} # End of while loop

#------------------------------------------------------------------------------
#determine if recursive option is set
#------------------------------------------------------------------------------
$recursive = 0;
if (($msg[$total_msg - 1] eq "-r") || ($msg[$total_msg - 1] eq "--recursive")) {
   
    $recursive = 1;
    --$total_msg;
}

($total_msg > 0) || die "!!! Not enough parameters \n";


#------------------------------------------------------------------------------
# combine executable and its options
#------------------------------------------------------------------------------

$count = 0;
while($count < $total_msg - 1){
    $executable = $executable . ' ' . $msg[$count];
    ++$count;
}# End of while loop

chomp $msg[$total_msg - 1];
   
if ($debug) {   
    print "-- $executable\n";
    print "__ $msg[$total_msg - 1]\n";
}


#------------------------------------------------------------------------------
# start digging
#------------------------------------------------------------------------------
   
folder_glob_dig ($executable, $msg[$total_msg - 1], $recursive);

exit;

#=============================================================================
#   subroutine for folder_glob_dig, recursively go through each sub folder
#=============================================================================

sub folder_glob_dig { # dig folder with glob pattern
    my($executable, $glob_pattern, $recursive)  = @_;
    my $slash_index;
   
    my $folder_search_pattern;
    my $where;
    my $file;
    my @files;
   
    my $file_glob_pattern;
   
     
   
    if (-d $glob_pattern) {
       
        if ($glob_pattern =~ /\/$/) {
            $where = $glob_pattern . '*';
        } else {
            $where = $glob_pattern . '/*';
        }
       
    } else {
        $where = $glob_pattern;
    }
   
    @files = <${where}>;
   
    foreach $file (@files) {
        if ((!(-d $file)) && (-T $file) && (!($file =~ /\~$/))) {
            print "\n======> $executable \"$file\"\n";
            system ("$executable \"$file\"");
        }
       
    } # End of foreach loop
   
    if ($recursive) {
   
        $slash_index = rindex ($where, "/");
   
        if ($slash_index == -1) {
            $folder_search_pattern = "*";
            $file_glob_pattern = $glob_pattern;
        } else {
            $folder_search_pattern = substr($glob_pattern, 0, $slash_index).'/*';
            $file_glob_pattern = substr($glob_pattern, $slash_index + 1, length($glob_pattern) - $slash_index - 1);
        }
   
   
        @files = <${folder_search_pattern}>;
        foreach $file (@files) {
            if (-d $file) {
                folder_glob_dig ($executable, $file.'/'.$file_glob_pattern, $recursive);
            }
           
        } # End of foreach loop
    }
}# End of folder_glob_dig() 