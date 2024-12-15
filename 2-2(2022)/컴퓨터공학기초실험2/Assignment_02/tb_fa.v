`timescale 1ns/100ps // set simulation time scale

module tb_fa; // fa testbench module
	reg a, b, ci;
	wire s,co;
	fa tb_fa(a,b,ci,s,co); // load fa module

// set simulation bits
initial begin
	a=0; b=0; ci=0;
	#10; a=0; b=0; ci=1;
	#10; a=0; b=1; ci=0;
	#10; a=0; b=1; ci=1;
	#10; a=1; b=0; ci=0;
	#10; a=1; b=0; ci=1;
	#10; a=1; b=1; ci=0;
	#10; a=1; b=1; ci=1;
	#10;
end
endmodule 