`timescale 1ns/1ps
`include "RippleCarryAdder.v"
module tb_RippleCarryAdder;
   reg [3:0] a;
   reg [3:0] b; 
   wire [3:0] sum;
   wire c_out;

   
   RippleCarryAdder uut(.a(a), .b(b), .sum(sum), .c_out(c_out));
   
   initial
   begin
      $dumpfile("tb_RippleCarryAdder.vcd");
      $dumpvars(0,tb_RippleCarryAdder); 

       a = 0;
       b = 0;
       #10;

       a = 1;
       b = 1;
       #10;

       a = 1;
       b = 0;
       #10;

       a = 8;
       b = 0;
       #10;

       a = 15;
       b = 0;
       #10;

       a = 15;
       b = 1;
       #10;

       a = 15;
       b = 2;
       #10;

       $display("Test complete");
   end

endmodule