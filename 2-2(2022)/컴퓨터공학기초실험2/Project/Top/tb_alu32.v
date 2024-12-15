`timescale 1ns/100ps //set simulation timescale

module tb_alu32; //alu32 testbench
	reg [31:0] tb_a, tb_b;
	reg [3:0] tb_op;
	wire [31:0] tb_result;
	
	//load alu32
	alu32 U0_alu32(tb_a, tb_b, tb_op, tb_result);
	
	initial begin
		#10 tb_a = 32'h00000003; tb_b = 32'h80000001; tb_op = 4'b0000;
		#10 tb_op = 4'b0001;
		#10 tb_op = 4'b0010;
		#10 tb_op = 4'b0011;
		#10 tb_op = 4'b0100;
		#10 tb_op = 4'b0101;
		#10 tb_op = 4'b0110;
		#10 tb_op = 4'b0111;
		#10 tb_op = 4'b1000;
		#10 tb_op = 4'b1001;
		#10 tb_op = 4'b1010;
		#10 tb_op = 4'b1011;
		#10 tb_op = 4'b1100;
		#10 tb_op = 4'b1101;
		#10 tb_op = 4'b1110;
		#10 tb_op = 4'b1111;
		#10 $stop;
	end
endmodule