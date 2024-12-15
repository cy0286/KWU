module _mx_2(rData, re, dout);	//2 input MUX
	input re;	
	input [31:0] rData;
	output reg [31:0] dout;
			
	always@(rData,re)
	begin
		if(re == 1'b1) 
			dout = rData;	
		else 
			dout = 32'h00;	
	end
endmodule 