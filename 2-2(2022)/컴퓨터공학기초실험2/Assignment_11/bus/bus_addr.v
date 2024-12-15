module bus_addr(s_address, s0_sel, s1_sel); //bus Address decoder
	input [7:0] s_address;
	output reg s0_sel, s1_sel;
	
	wire [2:0] upper_3bit;
	
	assign upper_3bit = s_address[7:5]; //3bit upper of s_address
	
	always@(upper_3bit, s_address)
	begin
		if(upper_3bit == 3'b000) 
			{s0_sel, s1_sel} = 2'b10; 
		else if(upper_3bit == 3'b001) 
			{s0_sel, s1_sel} = 2'b01;
		else
			{s0_sel, s1_sel} = 2'b00;
	end
endmodule 