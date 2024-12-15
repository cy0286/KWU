`timescale 1ns/1ps
`include "booth.v"
module tb_booth;
    reg [3:0] input1, input2;
    reg clk, start, reset;
    wire [7:0] result;
    wire [2:0] count;

    booth Booth(input1, input2, clk, start, reset, result, count);

    always #5 clk = ~clk;

    initial begin
        $dumpfile("tb_booth.vcd");
        $dumpvars(0, tb_booth);

        reset = 1;
        start = 1;
        clk = 0;
        reset = 0;
        #10;

        start = 0;
        reset = 1;
        input1 = 4;
        input2 = 5;
        #10;
        start = 1;
        #100;

     start = 0;
        input1 = 0;
        input2 = 3;
        #10;
        start = 1;
        #100;

      start = 0;
        input1 = -2;
        input2 = 7;
        #10;
        start = 1;
        #100;

     start = 0;
        input1 = -4;
        input2 = -4;
        #10;
        start = 1;
     	  #100;
        #640;$finish; 
    end
endmodule