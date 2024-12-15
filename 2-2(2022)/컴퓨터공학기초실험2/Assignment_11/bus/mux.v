module mx2(d0, d1, s, y); //2 input mux
   input d0, d1;
   input s;
   output y;
   
   assign y = (s==1'b0) ? d0 : d1; //if s = 0 -> y= d0, s = 1 -> y = d1
endmodule

module mx2_32bit(d0, d1, s, y); //2 input 32 bits mux
	input [31:0] d0, d1;
	input s;
	output [31:0] y;
	
	assign y = (s==1'b0) ? d0 : d1; //if s = 0 -> y= d0, s = 1 -> y = d1
endmodule 

module mx2_8bit(d0, d1, s, y); //2 input 8 bits mux
	input [7:0] d0, d1;
	input s;
	output [7:0] y;
	
	assign y = (s==1'b0) ? d0 : d1; //if s = 0 -> y= d0, s = 1 -> y = d1
endmodule 

module mx3_32bit(d0, d1, d2, s, y); //3 input 32 bits mux
	input [31:0] d0, d1, d2;
	input [1:0] s;
	output reg [31:0] y;
	
	always@(d0, d1, d2, s)
	begin
	case({s[1], s[0]})
		2'b00	: y = d0;
		2'b10 : y = d1;
		2'b01 : y = d2;
		default : y = 32'bx;
	endcase
	end
endmodule 