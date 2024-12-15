module ram(clk, cen, wen, addr, din, dout); //ram
	input clk, cen, wen;
	input [4:0] addr;
	input [31:0] din;
	output reg [31:0] dout;
	
	reg [31:0] mem [0:31];
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
			mem[addr] = din;
			dout = 32'b0;
		end
		else if(cen == 1 && wen == 0) //chip enable = 1, write enable = 0
			dout = mem[addr];
		else if(cen == 0) //chip enable = 0
			dout = 32'b0;
		else //default
			dout = 32'bx;
	end
endmodule 