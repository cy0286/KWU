module multiplier(clk, reset_n, multiplier, multiplicand, op_start, op_clear, op_done, result); //multiplier
   input clk, reset_n, op_start, op_clear;
   input [31:0] multiplier, multiplicand; //X, A
   output reg op_done;
   output [63:0] result; //Y
	
	reg [31:0] data_count;
	reg [64:0] temp1, temp2;
	reg [64:0] multiplier_; //save (result + lastbit)
	wire [64:0] shift, add, adds, sub, subs; //s = shift 
	wire [31:0] data_count1; //data_count + 1
	wire [31:0] temp3;
	wire co;
	
	//load module
	ASR65	U0_ASR65(multiplier_, 2'b01, shift); //shift
	cla65	U1_cla65(multiplier_, temp1, 1'b0, add, co); //add
	ASR65 U2_ASR65(add, 2'b01, adds); //add and shift
	cla32 U3_cla32(32'b0, ~multiplicand, 1'b1, temp3, co); //-A
	cla65	U4_cla65(multiplier_, temp2, 1'b0, sub, co); //sub
	ASR65 U5_ASR65(sub, 2'b01, subs); //sub and shift
	cla32 U6_cla32(data_count, 32'b0, 1'b1, data_count1); //data_count + 1
	
	assign result = multiplier_[64:1];
	
	always@(posedge clk or negedge reset_n)
   begin
      if(reset_n == 0)
      begin
         op_done <= 1'b0;
         data_count <= 32'b0;
			temp1 <= 65'b0;
			temp2 <= 65'b0;
			multiplier_ <= 65'b0;	
      end
		
		else if(op_start == 1 && op_clear == 0) //start multiplication
      begin
         op_done <= 1'b0;
         data_count <= 32'b0;
			temp1[64:33] <= multiplicand;
			temp1[32:0] <= 33'b0;
			temp2[64:33] <= temp3;
			temp2[32:0] <= 33'b0;
			multiplier_[64:33] <= 32'b0;
			multiplier_[32:1] <= multiplier;
			multiplier_[0] <= 1'b0;
      end
      
      else if(op_start == 0 && op_clear == 0) //op_start == 1 && op_clear == 1)
      begin
			if(multiplier_[1] == 0 && multiplier_[0] == 0)
			begin
				multiplier_ <= shift;
			end
			
			else if(multiplier_[1] == 0 && multiplier_[0] == 1)
			begin
				multiplier_ <= adds;
			end
			
			else if(multiplier_[1] == 1 && multiplier_[0] == 0)
			begin
				multiplier_ <= subs;
			end
			
			else if(multiplier_[1] == 1 && multiplier_[0] == 1)
			begin
				multiplier_ <= shift;
			end
			
			else
				multiplier_ <= 65'bx; //default

			data_count <= data_count1;
			if (data_count == 32) //finish calculation, except op_done signal hold
			begin
				op_done <= 1'b1;
				data_count <= data_count;
				temp1 <= temp1;
				temp2 <= temp2;
				multiplier_ <= multiplier_;
			end
		end

     else if(op_start == 0 && op_clear == 1) //logical zero
      begin
			op_done <= 1'b0;
         data_count <= 32'b0;
			temp1 <= 65'b0;
			temp2 <= 65'b0;
			multiplier_ <= 65'b0;	
      end 
      
      else //defualt
      begin
         op_done <= 1'bx;
         data_count <= 32'bx;
			temp1 <= 65'bx;
			temp2 <= 65'bx;
			multiplier_ <= 65'bx;
      end 
   end
endmodule 