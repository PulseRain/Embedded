/*
//===========================================================================
// Copyright (c) : Pulserain Technology, LLC. 2015
//===========================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/

`ifndef SYNCHRONIZER_SVH
`define SYNCHRONIZER_SVH

extern module async_reset_synchronizer (
    input   wire clk, 
    input   wire asyncrst_n,
    output  logic rst_n
);
    
extern module toggle_synchronizer_pulse #(parameter NUM_OF_SYNC_STAGES = 2) (
        //========== INPUT ==========
            input wire  clk_src_reset_n,    
            input wire  clk_dst_reset_n,
            
            input wire  clk_src,
            input wire  clk_dst,
            input wire  enable_in,
            
        //========== OUTPUT ==========  
            
            output wire enable_out
);
    
extern module toggle_synchronizer_data #(parameter DATA_WIDTH, NUM_OF_SYNC_STAGES = 2) (
        //========== INPUT ==========
        input wire                                  clk_src_reset_n,    
        input wire                                  clk_dst_reset_n,
            
        input wire                                  clk_src,
        input wire                                  clk_dst,
        
        input wire                                  enable_in,
        input wire  unsigned [DATA_WIDTH - 1 : 0]   data_in, 
            
        //========== OUTPUT ==========  
        
        output wire                                 ack,
        output logic                                enable_out,
        output logic unsigned [DATA_WIDTH - 1 : 0]  data_out
        
);
`endif
