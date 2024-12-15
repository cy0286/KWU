`timescale 1ns/100ps // set simulation time scale

module tb_ha(); // ha testbench module
	reg a;
	reg b;
	wire s;
	wire co;
	ha tb_ha(a,b,s,co); // load ha module

//set simulation bits
initial begin
	a=0; b=0;
	#10; a=0; b=1;
	#10; a=1; b=0;
	#10; a=1; b=1;
	#10;
end
endmodule