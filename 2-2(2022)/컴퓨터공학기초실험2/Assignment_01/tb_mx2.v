`timescale 1ns/100ps // set the time unit for Simulation

module tb_mx2; // testbench of 2 to 1 multiplexer
	reg tb_d0, tb_d1, tb_s;
	wire tb_y;
	
	mx2 U0_mx2(tb_d0, tb_d1, tb_s, tb_y); // load mx2
	
	// simulation as 10 time unit
	initial begin
		tb_d0 = 0; tb_d1 = 0; tb_s = 0;
		#10; tb_d0 = 0; tb_d1 = 0; tb_s = 1;
		#10; tb_d0 = 0; tb_d1 = 1; tb_s = 0;
		#10; tb_d0 = 0; tb_d1 = 1; tb_s = 1;
		#10; tb_d0 = 1; tb_d1 = 0; tb_s = 0;
		#10; tb_d0 = 1; tb_d1 = 0; tb_s = 1;
		#10; tb_d0 = 1; tb_d1 = 1; tb_s = 0;
		#10; tb_d0 = 1; tb_d1 = 1; tb_s = 1;
		#10;
		end
endmodule 