`timescale 1ns/100ps //set simulation timescale

module tb_Top; //Top testbench
	reg tb_clk, tb_reset_n, tb_M_req, tb_M_wr;
	reg [7:0] tb_M_addr;
	reg [31:0] tb_M_dout;
	wire tb_M_grant;
	wire [31:0] tb_M_din;
	
	//load Top
	Top tb_Top(tb_clk, tb_reset_n, tb_M_req, tb_M_wr, tb_M_addr, tb_M_dout, tb_M_grant, tb_M_din);
	
	always #5 tb_clk = ~tb_clk; //set clk
	
	initial begin //set simulation bits
		#5; tb_clk = 0; tb_reset_n = 0;
		#10; tb_reset_n = 1;
		#10; tb_M_wr = 1; tb_M_req = 1;
		#10; tb_M_addr = 8'h30; tb_M_dout = 32'h00000002;
		#10; tb_M_addr = 8'h31; tb_M_dout = 32'h00000003;
		#10; tb_M_addr = 8'h32; tb_M_dout = 32'h0000000C;
		#10; tb_M_addr = 8'h33; tb_M_dout = 32'h00000001;
		#10; tb_M_wr = 0; tb_M_addr = 8'h34; 
		#10; 
		#10; tb_M_addr = 8'h36;
		
		#10; tb_M_wr = 1;
		#20; tb_M_addr = 8'h00; tb_M_dout = 32'h00000002;
		#10; tb_M_addr = 8'h01; tb_M_dout = 32'h00000003;
		#10; tb_M_addr = 8'h02; tb_M_dout = 32'h0000000D;
		#10; tb_M_addr = 8'h03; tb_M_dout = 32'h00000001;
		
		#10; tb_M_wr = 0;
		#10; tb_M_addr = 8'h00; 
		#10; tb_M_addr = 8'h01; 
		#10; tb_M_addr = 8'h02; 
		#10; tb_M_addr = 8'h03; 
		
		#10; tb_M_wr = 1; tb_M_addr = 8'h34; tb_M_dout = 0;
		#20; tb_M_addr = 8'h30; tb_M_dout = 32'h00000002;
		#10; tb_M_addr = 8'h31; tb_M_dout = 32'h00000003;
		#10; tb_M_addr = 8'h32; tb_M_dout = 32'h0000000D;
		#10; tb_M_addr = 8'h33; tb_M_dout = 32'h00000001;
		#10; tb_M_wr = 0; tb_M_addr = 8'h34;
		#400;
		#10; tb_M_addr = 8'h36;
		#10; tb_M_addr = 8'h37;
		#10; $stop;
	end
endmodule