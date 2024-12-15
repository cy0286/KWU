`timescale 1ns/100ps // set simulation time scale

module tb_cla32; // cla32 testbench module
   reg	[31 : 0] tb_a, tb_b;
   reg            tb_ci;
   wire  [31 : 0] tb_s;
   wire            tb_co;
   wire  [32 : 0] tb_result;
   
   assign tb_result = {tb_co, tb_s};
   
   cla32 U0_cla32(tb_a, tb_b, tb_ci, tb_s, tb_co);
   
   initial begin
   tb_a = 0; tb_b = 0; tb_ci = 0;
   #10; tb_a = 32'h3333_3333; tb_b = 32'h5555_5555; tb_ci = 0;
   #10; tb_a = 32'h7777_7777; tb_b = 32'h9999_9999; tb_ci = 0;
   #10; tb_a = 32'h5555_5555; tb_b = 32'h5555_5555; tb_ci = 1;
   #10; tb_a = 32'h8888_8888; tb_b = 32'h7777_7777; tb_ci = 1;
   #10; tb_a = 32'hffff_ffff; tb_b = 32'hffff_ffff; tb_ci = 0;
   #10; tb_a = 32'hffff_ffff; tb_b = 32'hffff_ffff; tb_ci = 1;
   #10; $stop;
   end
endmodule 