module tl_cntr_w_left(clk,reset_n,Ta,Tal,Tb,Tbl,La,Lb); //traffic light controller with left signals module
	input 	clk,reset_n,Ta,Tb,Tal,Tbl;
	output   [1:0]La,Lb;
	wire 		[2:0]Q,D;
		
	//struct tl_cntr_w_left module
	ns_logic 		U0_ns_logic(Q, Ta, Tal, Tb, Tbl, D);
	_register3_r 	U1_register3(clk, reset_n, D, Q);
	o_logic 			U2_o_logic(Q, La, Lb);
endmodule
	