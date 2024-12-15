module ns_logic(Q,Ta,Tal,Tb,Tbl,D); //next state logic module
	input  [2:0]Q;
	input  Ta,Tb,Tal,Tbl;
	output [2:0]D;
	wire 	 [2:0]w0,w1;
	wire 	 [3:0]w2;
	
	//sturct next state logic module	
	_and3 	U0_and3(~Q[2], Q[1], Q[0], w0[0]);
	_and2 	U1_and2(Q[2], ~Q[1], w0[1]);
	_and3 	U2_and3(Q[2], Q[1], ~Q[0], w0[2]);
	_or3 		U3_or3(w0[0], w0[1], w0[2], D[2]);
	_and3 	U4_and3(~Q[2], ~Q[1], Q[0], w1[0]);
	_and2 	U5_and2(Q[1], ~Q[0], w1[1]);
	_and3 	U6_and3(Q[2], ~Q[1], Q[0], w1[2]);
	_or3 		U7_or3(w1[0], w1[1], w1[2], D[1]);		
	_and4 	U8_and4(~Q[2], ~Q[1], ~Q[0], ~Ta, w2[0]);
	_and4 	U9_and4(~Q[2], Q[1], ~Q[0], ~Tal, w2[1]);
	_and4 	U10_and4(Q[2], ~Q[1], ~Q[0], ~Tb, w2[2]);
	_and4 	U11_and4(Q[2], Q[1], ~Q[0], ~Tbl, w2[3]);
	_or4 		U12_or4(w2[0], w2[1], w2[2], w2[3], D[0]);
endmodule
