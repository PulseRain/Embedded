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

//****************************************************************************
// References:
//  [1] Michael Crews and Yong Yuenyongsgool,  Philips Semiconductors, 
//      Practical design for transferring signals between clock domains,
//      EDN Magazine, Feb 20, 2003
//****************************************************************************

`include "synchronizer.svh"

`default_nettype none

module toggle_synchronizer_pulse #(parameter NUM_OF_SYNC_STAGES = 2) (
        //========== INPUT ==========
            input wire  clk_src_reset_n,    
            input wire  clk_dst_reset_n,
            
            input wire  clk_src,
            input wire  clk_dst,
            input wire  enable_in,
            
        //========== OUTPUT ==========  
            
            output wire enable_out
);
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // signals
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        logic                                           take_it_toggle;
        logic  unsigned [NUM_OF_SYNC_STAGES - 1 : 0]    clk_dst_sr;
        
        logic                                           take_it_pulse;
        
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // in source clock domain
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                        
        // pulse to toggle
        always_ff @(posedge clk_src, negedge clk_src_reset_n) begin : take_it_toggle_proc
            if (!clk_src_reset_n) begin
                take_it_toggle <= 0;
            end else begin
                take_it_toggle <= take_it_toggle ^ enable_in;
            end
        end : take_it_toggle_proc
        
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // in destination clock domain
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        always_ff @(posedge clk_dst, negedge clk_dst_reset_n) begin : clk_dst_sr_proc
            if (!clk_dst_reset_n) begin
                clk_dst_sr <= 0;
            end else begin
                clk_dst_sr <= {clk_dst_sr [$high (clk_dst_sr) - 1 : 0], take_it_toggle};
            end
        end : clk_dst_sr_proc
        
        always_ff @(posedge clk_dst, negedge clk_dst_reset_n) begin : take_it_pulse_proc
            if (!clk_dst_reset_n) begin
                take_it_pulse <= 0;
            end else begin
                take_it_pulse <= clk_dst_sr [$high (clk_dst_sr)];
            end
        end : take_it_pulse_proc
        
        assign enable_out = take_it_pulse ^  clk_dst_sr [$high (clk_dst_sr)];
    
    
endmodule : toggle_synchronizer_pulse





        
module toggle_synchronizer_data #(parameter DATA_WIDTH, NUM_OF_SYNC_STAGES = 2) (
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
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // signals
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        wire                                        toggle_pulse_enable_out;
        
    
        toggle_synchronizer_pulse #(.NUM_OF_SYNC_STAGES (NUM_OF_SYNC_STAGES)) 
            toggle_synchronizer_pulse_i (
                .clk_src_reset_n (clk_src_reset_n),
                .clk_dst_reset_n (clk_dst_reset_n),
                
                .clk_src (clk_src),
                .clk_dst (clk_dst),
                
                .enable_in (enable_in),
                
                .enable_out (toggle_pulse_enable_out));
        
        toggle_synchronizer_pulse #(.NUM_OF_SYNC_STAGES (NUM_OF_SYNC_STAGES)) 
            toggle_synchronizer_pulse_ack (
                .clk_src_reset_n (clk_dst_reset_n),
                .clk_dst_reset_n (clk_src_reset_n),
                
                .clk_src (clk_dst),
                .clk_dst (clk_src),
                
                .enable_in (toggle_pulse_enable_out),
                
                .enable_out (ack));
        
    
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // output register
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        always_ff @(posedge clk_dst, negedge clk_dst_reset_n) begin
            if (!clk_dst_reset_n) begin
                enable_out <= 0;
                data_out <= 0;
            end else if (toggle_pulse_enable_out) begin
                enable_out <= 1'b1;
                data_out <= data_in;
            end else begin
                enable_out <= 1'b0;
            end
        end
    
    
endmodule : toggle_synchronizer_data

`default_nettype wire
