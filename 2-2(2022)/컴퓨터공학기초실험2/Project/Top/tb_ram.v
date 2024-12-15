`timescale 1ns/100ps	//set simulation timescale

module tb_ram; //ram testbench
	reg tb_clk,tb_cen,tb_wen;
	reg [4:0] tb_S_addr;
	reg [31:0] tb_S_din;
	wire [31:0] tb_S_dout;
	
	//load ram
	ram U0_ram(tb_clk, tb_cen, tb_wen, tb_S_addr, tb_S_din, tb_S_dout);
	
	always #5 tb_clk = ~tb_clk; //set clock
	
	initial //set simulation bits
	begin
		tb_clk=0; tb_cen=0; tb_wen=0; tb_S_addr=5'b0; tb_S_din=32'b0;
		#10; tb_cen=1; tb_wen=1; tb_S_addr=5'b00001; tb_S_din=32'h00000001;
		#10; tb_S_addr=5'b00010; tb_S_din=32'h00000002;
		#10; tb_S_addr=5'b00011; tb_S_din=32'h00000003;
		#10; tb_S_addr=5'b00100; tb_S_din=32'h00000004;
		#10; tb_wen=0; tb_S_addr=5'b00001;
		#10; tb_S_addr=5'b00010;
		#10; tb_S_addr=5'b00011;
		#10; tb_S_addr=5'b00100;
		#10; tb_cen=0;
		#10; $stop;
	end
endmodule 