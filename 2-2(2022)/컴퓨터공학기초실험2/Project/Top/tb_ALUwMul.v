`timescale 1ns/100ps //set simulation timescale

module tb_ALUwMul; //ALU with Multiplier testbench
	reg tb_clk, tb_reset_n, tb_S_sel, tb_S_wr;
	reg [7:0] tb_S_addr;
	reg [31:0] tb_S_din;
	wire [31:0] tb_S_dout;
	
	//load ALUwMul
	ALUwMul U0_ALUwMul(tb_clk, tb_reset_n, tb_S_sel, tb_S_wr, tb_S_addr, tb_S_din, tb_S_dout);
	
	always #5 tb_clk = ~tb_clk; //set clk
	
	initial begin //set simulation bits
		#5; tb_clk = 0; tb_reset_n = 0;
		#10; tb_reset_n = 1; tb_S_sel =0; tb_S_wr = 1;
		
		#10; tb_S_wr = 1; tb_S_sel = 1;
		#10; tb_S_addr = 8'h00; tb_S_din = 32'h00000002;
		#10; tb_S_addr = 8'h01; tb_S_din = 32'h00000003;
		#10; tb_S_addr = 8'h02; tb_S_din = 32'h0000000C;
		#10; tb_S_addr = 8'h03; tb_S_din = 32'h00000001;
		#10; tb_S_wr = 0; tb_S_addr = 8'h04; 
		#10; 
		#10; tb_S_addr = 8'h06;
		#10; tb_S_wr = 1; tb_S_addr = 8'h05; tb_S_din = 32'h00000001;
		#20; tb_S_addr = 8'h00; tb_S_din = 32'h00000002;
		#10; tb_S_addr = 8'h01; tb_S_din = 32'h00000003;
		#10; tb_S_addr = 8'h02; tb_S_din = 32'h0000000D;
		#10; tb_S_addr = 8'h03; tb_S_din = 32'h00000001;
		#10; tb_S_wr = 0; tb_S_addr = 8'h04;
		#400;
		#10; tb_S_addr = 8'h06;
		#10; tb_S_addr = 8'h07;
		#10;
		#10; tb_S_wr = 1; tb_S_addr = 8'h04; tb_S_din = 0;
		#20; tb_S_addr = 8'h00; tb_S_din = 32'h00000002;
		#10; tb_S_addr = 8'h01; tb_S_din = 32'h00000003;
		#10; tb_S_addr = 8'h02; tb_S_din = 32'h0000000A;
		#10; tb_S_addr = 8'h03; tb_S_din = 32'h00000001;
		#10; tb_S_wr = 0; tb_S_addr = 8'h04;
		#30;
		#10; tb_S_addr = 8'h06;
		#10; tb_S_addr = 8'h07;
		#10; $stop;
	end	
endmodule