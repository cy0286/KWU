module o_logic(Q,La,Lb); //output state logic module
	input  [2:0]Q;
	output [1:0]La, Lb;
	wire   [1:0]w0;
	
	//struct output state logic module
	_and2 	U0_and2(Q[1], ~Q[0], w0[0]);
	_or2 		U1_or2(w0[0], Q[2], La[1]);
	_or2 		U2_or2(Q[0], Q[2], La[0]);
	_and2 	U3_and2(Q[1], ~Q[0], w0[1]);
	_or2		U4_or2(~Q[2], w0[1], Lb[1]);
	_or2 		U5_or2(~Q[2], Q[0], Lb[0]);
endmodule
