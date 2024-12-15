`timescale 1ns/100ps // set simulation time scale

module tb_rca4; // rca testbench module
   reg [3:0] tb_a,tb_b;
   reg tb_ci;
   wire [3:0] tb_s;
   wire tb_co;
   wire [4:0] tb_result;
   
   rca4 rca0(tb_a,tb_b,tb_ci,tb_s,tb_co); // load rca module

//set simulation bits  
initial begin
	tb_a=4'b0000; tb_b=4'b0000; tb_ci=0;
	#10; tb_a=4'b0101; tb_b=4'b0100; tb_ci=0;
	#10; tb_a=4'b1111; tb_b=4'b1111; tb_ci=0;
	#10; tb_a=4'b1111; tb_b=4'b1111;	tb_ci=1;
	#10; 
end
	
   assign tb_result = {tb_co,tb_s}; // concatenation s and co
endmodule 