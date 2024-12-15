module _dff_en(clk, en, d, q); //enabled d flip-flop module
	input 	clk, en , d;
	output 	q;
	
	wire		w_d;
	
	//struct enabled d flip-flop
	mx2 	U0_mx2	(q, d, en, w_d);
	_dff	U1_dff	(clk, w_d, q);
endmodule 