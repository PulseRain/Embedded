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
// [1] Clifford E. Cummings,  Don Mills and Steve Golson, 
//     Asynchronous & Synchronous Reset Design Techniques 
//                  - Part Deux (Rev 1.3),   SNUG Boston 2003
//****************************************************************************

`default_nettype none

`include "synchronizer.svh"



//----------------------------------------------------------------------------
// Synchronizer for async reset
//----------------------------------------------------------------------------

module async_reset_synchronizer (
    
    //========== input =========
        input   wire clk, 
        input   wire asyncrst_n,
    //========== output =========
        output  logic rst_n
);
    
    logic rff1;
    
    always_ff @(posedge clk, negedge asyncrst_n) begin
        if (!asyncrst_n) begin
            {rst_n,rff1} <= 2'b0;
        end else begin
            {rst_n,rff1} <= {rff1,1'b1};
        end
    end
    
endmodule : async_reset_synchronizer

`default_nettype wire
