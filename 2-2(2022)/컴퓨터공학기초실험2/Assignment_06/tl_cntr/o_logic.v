module o_logic(Q,La,Lb); //output state logic module
	input  [1:0]Q;
	output [1:0]La, Lb;
	
	//struct output state logic module
	_and2 U0_and2(~Q[1], Q[0], La[0]);
	_and2 U1_and2(Q[1], Q[0], Lb[0]);
	
	assign La[1]=Q[1];
	assign Lb[1]=~Q[1];
	
endmodule 