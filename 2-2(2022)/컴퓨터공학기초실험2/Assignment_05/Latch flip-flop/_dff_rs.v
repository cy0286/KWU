module _dff_rs(clk, set_n, reset_n, d, q); //set/resettable d flip-flop module
	input		clk, set_n, reset_n, d;
	output	q;
	
	wire		w_d1, w_d2;
	
	//struct set/resettable d flip-flop
	_or2		U0_or2	(d, ~set_n, w_d1);
	_and2		U1_and2	(w_d1, reset_n, w_d2);
	_dff		U2_dff	(clk, w_d2, q);
endmodule  