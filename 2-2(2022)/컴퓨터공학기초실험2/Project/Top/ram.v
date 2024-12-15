module ram(clk, cen, wen, S_addr, S_din, S_dout); //ram module
	input clk, cen, wen;
	input [4:0] S_addr;
	input [31:0] S_din;
	output reg [31:0] S_dout;

	reg [31:0] mem [0:31]; //memory declaration
	integer i; //variable of for loop
	
	
	initial //memory initialization
	begin
		for(i = 0; i < 32; i = i + 1)
			mem[i] = 32'b0;
	end
	
	always@(posedge clk) //read/write performance
	begin
		if(cen == 1 && wen == 1) //chip enable = 1, write enable = 0
		begin
			mem[S_addr] = S_din;
			S_dout = 32'b0;
		end
		else if(cen == 1 && wen == 0) //chip enable = 1, write enable = 0
			S_dout = mem[S_addr];
		else if(cen == 0) //chip enable = 0
			S_dout = 32'b0;
		else //default
			S_dout = 32'bx;
	end
endmodule 