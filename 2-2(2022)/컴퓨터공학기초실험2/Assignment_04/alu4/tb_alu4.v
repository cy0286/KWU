`timescale 1ns/100ps //set simulation time scale, self-checking testbench with testvectors 
module tb_alu4; //alu4 testbench module
	
	reg tb_clk, tb_reset; 
	reg [3:0] vectornum, errors; 
	reg [18:0] testvectors[100:0]; 
	reg [3:0] result_exp; 
	reg c_exp, n_exp, z_exp, v_exp; 
	
	reg [3:0] tb_a, tb_b; 
	reg [2:0] tb_op; 
	wire [3:0] tb_result; 
	wire tb_c, tb_n, tb_z, tb_v; 

	//load alu4 module
	alu4 U0_alu4(tb_a, tb_b, tb_op, tb_result, tb_c, tb_n, tb_z, tb_v); 
	
	// generate clock
	always begin
		tb_clk = 1; #5; tb_clk = 0; #5;
	end
	
	initial begin
			$readmemb("./../../example.tv",testvectors);
			vectornum=0; errors=0; 
			tb_reset=1; #4; tb_reset=0;
		end
	
	always @ (posedge tb_clk) // positive edge, apply test vectors on rising edge of clk 
		begin
			#1; {tb_a, tb_b, tb_op, result_exp, c_exp, n_exp, z_exp, v_exp} = testvectors[vectornum];
		
		end
	always @ (negedge tb_clk) // negative edge, check results on falling edge of clk
		if(~tb_reset) 
			begin 
				if(tb_result !== result_exp || tb_c !== c_exp || tb_n !== n_exp || tb_z !== z_exp || tb_v !== v_exp) 
					begin 
						$display("Error: inputs = a: %b, b: %b, op: %b",tb_a, tb_b, tb_op);
						$display("outputs = result: %b, c: %b, n: %b, z: %b, v: %b (%b %b %b %b %b expected)", tb_result, tb_c, tb_n, tb_z, tb_v, result_exp, c_exp, n_exp, z_exp, v_exp);
						errors = errors + 1; 
					end
			// increment array index and read next testvector 
				vectornum = vectornum + 1; 
			if(testvectors[vectornum] === 19'bx) 
				begin
					$display("%d tests completed with %d errors", vectornum, errors); 
					$finish;
				end
		end
endmodule 