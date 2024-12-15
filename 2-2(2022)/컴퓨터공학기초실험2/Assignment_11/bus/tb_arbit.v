`timescale 1ns/100ps //set simulation timescale

module tb_arbit; //arbiter testbench
	reg tb_clk, tb_reset_n, tb_m0_req, tb_m1_req;
	wire tb_m0_grant, tb_m1_grant;
	
	//load bus_arbit
	bus_arbit U0_bus_arbit(tb_m0_req, tb_m1_req, tb_reset_n, tb_clk, tb_m0_grant, tb_m1_grant);
	
	always #5 tb_clk = ~tb_clk; //set clock
	initial
	begin
	tb_clk=1; tb_reset_n=0; tb_m0_req=0; tb_m1_req=0;
	#7; tb_reset_n=1; tb_m0_req = 1;   tb_m1_req = 1;
   #30; tb_m0_req = 0;   tb_m1_req = 1;
   #50; tb_m0_req = 0;   tb_m1_req = 0;
   #10; tb_m0_req = 0;   tb_m1_req = 1;
   #30; tb_m0_req = 1;   tb_m1_req = 1;
   #30; tb_m0_req = 1;   tb_m1_req = 0;
   #20; tb_m0_req = 0;   tb_m1_req = 0;
	#10; $stop;
   end
endmodule 