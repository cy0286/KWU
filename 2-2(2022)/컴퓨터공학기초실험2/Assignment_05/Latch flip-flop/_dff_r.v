module _dff_r(clk, reset_n, d, q); //resettable d flip-flop module
	input		clk, reset_n, d;
	output	q;
	
	wire		w_d;
	
	 //struct resettable d flip-flop
	_and2	U0_and2	(d, reset_n, w_d);
	_dff	U1_dff	(clk, w_d, q);
endmodule 