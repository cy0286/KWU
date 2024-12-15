module ALUwMul(clk, reset_n, S_sel, S_wr, S_addr, S_din, S_dout); //ALU with Multiplier model
	input clk, reset_n, S_sel, S_wr;
	input [7:0] S_addr;
	input [31:0] S_din;
	output [31:0] S_dout;

	//alu32, multiplier wire, reg
	wire [31:0] aresult;
	wire clear2, done2;
	wire [63:0] mresult;
	
	//register32_r_en wire, reg
	reg [7:0] en;
	reg [31:0] d_in0, d_in1, d_in2, d_in3, d_in4, d_in5, d_in6, d_in7;
	wire [31:0] operandA, operandB, opcode, opstart, opdone, opclear, result1, result2;

	//read_operaion wire
	wire [31:0] data;

	//instance alu32, multiplier
	alu32	U0_alu32(operandA, operandB, opcode[3:0], aresult);
	multiplier U1_multiplier(clk, reset_n, operandA, operandB, opstart[0], opclear[0], done2, mresult);
	
	//load register32_r_en
	register32_r_en	U2_register32_r_en(clk, reset_n, en[0], d_in0, operandA);
	register32_r_en	U3_register32_r_en(clk, reset_n, en[1], d_in1, operandB);
	register32_r_en	U4_register32_r_en(clk, reset_n, en[2], d_in2, opcode); 
	register32_r_en	U5_register32_r_en(clk, reset_n, en[3], d_in3, opstart);
	register32_r_en	U6_register32_r_en(clk, reset_n, en[4], d_in4, opdone);
	register32_r_en	U7_register32_r_en(clk, reset_n, en[5], d_in5, opclear);
	register32_r_en	U8_register32_r_en(clk, reset_n, en[6], d_in6, result1);
	register32_r_en	U9_register32_r_en(clk, reset_n, en[7], d_in7, result2);

	//load modules(decide read&write)
	read_operation	U10_read_operation(S_addr[2:0], data, operandA, operandB, opcode, opstart, opdone, opclear, result1, result2);
	mx2_32bits	U11_mx2_32bits(data, 32'b0, S_wr, S_dout);
	
	always@(operandA, operandB, opcode, opstart, opdone, opclear, result1, result2, aresult, mresult, done2,S_sel, S_wr, S_addr, S_din) 
	begin
		if(S_sel == 1'b1) 
		begin
			if (opstart[0] == 1) //start operation
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 1;
				en[4] <= 1;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 32'b00000000000000000000000000000010; //start operation
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end
			
			else if (opcode[3:0] != 4'b1101 && opdone[1:0] == 2'b10) //alu and start operation
			begin
				en[0]	<= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0; //opstart initialize to zero
				en[4] <= 1;
				en[5] <= 0;
				en[6] <= 1;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 32'b00000000000000000000000000000011; //complete operation
				d_in5 <= 0;
				d_in6 <= aresult;
				d_in7 <= 0;
			end
			
			else if (opcode[3:0] == 4'b1101 && opdone[1:0] == 2'b10 && done2 == 1'b1) //multiplier and start operation
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 1;
				en[5] <= 0;
				en[6] <= 1;
				en[7] <= 1;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 32'b00000000000000000000000000000011; //complete operation
				d_in5 <= 0;
				d_in6 <= mresult[31:0]; //low 32 bit
				d_in7 <= mresult[63:32]; //high 32 bit
			end
			
			else if (opclear[0] == 1) //initialize register to default value
			begin
				en[0] <= 1;
				en[1] <= 1;
				en[2] <= 1;
				en[3] <= 1;
				en[4] <= 1;
				en[5] <= 1;
				en[6] <= 1;
				en[7] <= 1;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end
			
			else if(S_addr[2:0] == 3'b0 && opdone[1:0]  == 2'b00) //operandA and waiting operation 
			begin
				en[0] <= S_wr;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= S_din;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end
			
			else if(S_addr[2:0] == 3'b001 && opdone[1:0]  == 2'b00) //operandB and waiting operation 
			begin
				en[0] <= 0;
				en[1] <= S_wr;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= S_din;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end	
			
			else if(S_addr[2:0] == 3'b010 && opdone[1:0]  == 2'b00) //opcode and waiting operation 
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= S_wr;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= S_din;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end
			
			else if(S_addr[2:0] == 3'b011 && opdone[1:0]  == 2'b00) //opstart and waiting operation 
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= S_wr;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= S_din;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end	
			
			else if(S_addr[2:0] == 3'b100) //opdone
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= S_wr;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= S_din;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end	
			
			else if(S_addr[2:0] == 3'b101) //opclear
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= S_wr;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= S_din;
				d_in6 <= 0;
				d_in7 <= 0;
			end	
			
			else if(S_addr[2:0] == 3'b110) //result1 (just save value)
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end	
			
			else if(S_addr[2:0] == 3'b111) //result2 (just save value)
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end	
			
			else //defualt
			begin
				en[0] <= 0;
				en[1] <= 0;
				en[2] <= 0;
				en[3] <= 0;
				en[4] <= 0;
				en[5] <= 0;
				en[6] <= 0;
				en[7] <= 0;
				d_in0 <= 0;
				d_in1 <= 0;
				d_in2 <= 0;
				d_in3 <= 0;
				d_in4 <= 0;
				d_in5 <= 0;
				d_in6 <= 0;
				d_in7 <= 0;
			end
		end
		else //defualt
		begin
			en[0] <= 0;
			en[1] <= 0;
			en[2] <= 0;
			en[3] <= 0;
			en[4] <= 0;
			en[5] <= 0;
			en[6] <= 0;
			en[7] <= 0;
			d_in0 <= 0;
			d_in1 <= 0;
			d_in2 <= 0;
			d_in3 <= 0;
			d_in4 <= 0;
			d_in5 <= 0;
			d_in6 <= 0;
			d_in7 <= 0;
		end
	end
endmodule 