module ns_logic(Q,Ta,Tb,D); //next state logic moudle
	input  [1:0]Q;
	input  Ta,Tb;
	output [1:0]D;
	wire 	 w0,w1;
	
	//struct next state logic module	
	_xor2 U0_xor2(Q[1], Q[0], D[1]);	
	_and3 U1_and3(~Q[1], ~Q[0], ~Ta, w0);
	_and3 U2_and3(Q[1], ~Q[0], ~Tb, w1);
	_or2 	U3_or2(w0, w1, D[0]);
endmodule 