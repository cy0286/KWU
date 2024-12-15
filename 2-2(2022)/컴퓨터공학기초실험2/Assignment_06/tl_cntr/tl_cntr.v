module tl_cntr(clk,reset_n,Ta,Tb,La,Lb);//traffic light controller module
	input 	clk,reset_n,Ta,Tb;
	output   [1:0]La,Lb;
	wire 		[1:0]Q,D;
	
	//struct tl_cntr module
	ns_logic 				U0_ns_logic(Q, Ta, Tb, D);
	_register2_r_async 	U1_register2(clk, reset_n, D, Q);
	o_logic 					U2_o_logic(Q, La, Lb);
endmodule 