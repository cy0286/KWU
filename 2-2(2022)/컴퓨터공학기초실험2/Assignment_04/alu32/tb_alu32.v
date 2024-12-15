`timescale 1ns/100ps // set simulation time scale, self-checking testbench with testvectors 
module tb_alu32; // alu32 testbench module
   
   reg tb_clk, tb_reset; 
   reg [31:0] vectornum, errors; 
   reg [103:0] testvectors[100:0]; 
   reg [31:0] result_exp; 
   reg c_exp, n_exp, z_exp, v_exp; 
   
   reg [31:0] tb_a, tb_b; 
   reg [2:0] tb_op;
	reg g_v; // matches the number of beats 
   wire [31:0] tb_result; 
   wire tb_c, tb_n, tb_z, tb_v; 

   // load alu32 module
   alu32 U0_alu32(tb_a, tb_b, tb_op, tb_result, tb_c, tb_n, tb_z, tb_v); 
   
   // generate clock
   always begin
      tb_clk = 1; #5; tb_clk = 0; #5;
   end
   
   initial begin
         $readmemh("./../../example.tv",testvectors);
         vectornum=0; errors=0; 
         tb_reset=1; #4; tb_reset=0;
      end
   
   always @ (posedge tb_clk) // positive edge, apply test vectors on rising edge of clk 
      begin
         #1; {tb_a, tb_b, g_v, tb_op, result_exp, c_exp, n_exp, z_exp, v_exp} = testvectors[vectornum];
      
      end
   always @ (negedge tb_clk) // negative edge, check results on falling edge of clk
      if(~tb_reset) 
         begin 
            if(tb_result !== result_exp || tb_c !== c_exp || tb_n !== n_exp || tb_z !== z_exp || tb_v !== v_exp) 
               begin 
                  $display("Error: inputs = a: %h, b: %h, op: %b",tb_a, tb_b, tb_op);
                  $display("outputs = result: %h, c: %b, n: %b, z: %b, v: %b (%h %b %b %b %b expected)", tb_result, tb_c, tb_n, tb_z, tb_v, result_exp, c_exp, n_exp, z_exp, v_exp);
                  errors = errors + 1; 
               end
         // increment array index and read next testvector 
            vectornum = vectornum + 1; 
         if(testvectors[vectornum] === 104'hx) 
            begin
               $display("%d tests completed with %d errors", vectornum, errors); 
               $finish;
            end
      end
endmodule 