module less_than(a, b, y); //set less than
	input [31:0] a, b;
	output reg [31:0] y;
	
	wire [32:0] a_, b_; //to remove sign
	wire co; //set port number
	
	//load cla33
	cla33	U0_cla33(33'b0, a, 1'b0, a_, co);
	cla33	U1_cla33(33'b0, b, 1'b0, b_, co);
	
	always@(a_, b_, y)
	begin
		if(a_ < b_)
			y <= 32'b1;
		else
			y <= 32'b0;
	end
endmodule
	
module greater_than(a, b, y); //set greater than
	input [31:0] a, b;
	output reg [31:0] y;
	
	wire [32:0] a_, b_; //to remove sign
	wire co; //set port number
	
	//load cla33
	cla33	U0_cla33(33'b0, a, 1'b0, a_, co);
	cla33	U1_cla33(33'b0, b, 1'b0, b_, co);
	
	always@(a_, b_, y)
	begin
		if(a_ > b_)
			y <= 32'b1;
		else
			y <= 32'b0;
	end
endmodule 