module mx3_32bit(d0, d1, d2, s, y); //3 input 32 bits mux
	input [31:0] d0, d1, d2;
	input [1:0] s;
	output reg [31:0] y;
	
	always@(d0, d1, d2, s)
	begin
		if(s[0] == 0 && s[1] == 0)
			y <= d0;
		else if(s[0] == 1 && s[1] == 0)
			y <= d2;
		else if(s[0] == 0 && s[1] == 1)
			y <= d1;
		else //default
			y <= 32'bx;
	end
endmodule 