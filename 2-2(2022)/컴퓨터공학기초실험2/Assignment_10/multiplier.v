module multiplier(clk, reset_n, multiplier, multiplicand, op_start, op_clear, op_done, result); //multiplier
   input clk, reset_n, op_start, op_clear;
   input [63:0] multiplier, multiplicand;
   output reg op_done;
   output [127:0] result;
   
   reg multiplier_;
   reg [5:0] data_count;
	reg [63:0] m_multiplier;
   reg [64:0] temp, m_multiplicand; //temporary value
   wire [64:0] add, add2, sub, sub2; //Add & subtract
   
   //binary encoding	
	parameter add0 = 3'b000;
	parameter add_multiplicand = 3'b001;
	parameter add_multiplicand2 = 3'b010;
	parameter add_2_multiplicand = 3'b011; //add 2* multiplicand
	parameter sub_2_multiplicand = 3'b100; //sub 2* multiplicand
	parameter sub_multiplicand = 3'b101;
	parameter sub_multiplicand2 = 3'b110;
	parameter sub0 = 3'b111;
	
   
   assign add = temp + m_multiplicand;
	assign add2 = temp + (m_multiplicand << 1);
   assign sub = temp + ~m_multiplicand + 1;
	assign sub2 = temp +((~m_multiplicand + 1) << 1);
   assign result = {temp[63:0], m_multiplier};
   
   always@(posedge clk or negedge reset_n)
   begin
      if(reset_n == 0)
      begin
         op_done <= 1'b0;
         multiplier_ <= 1'b0;
         data_count <= 6'b0;
         temp <= 65'b0;
         m_multiplier <= 64'b0;
         m_multiplicand <= 65'b0;
      end
      
      else if(op_start == 1 && op_clear == 0) //start multiplication
      begin
         op_done <= 1'b0;
         multiplier_ <= 1'b0;
         data_count <= 6'b0;
         temp <= 65'b0;
         m_multiplier <= multiplier;
         m_multiplicand <= {multiplicand[63], multiplicand};
      end
      
      else if(op_start == 0 && op_clear == 0) //op_start == 1 && op_clear == 1)
      begin
         case({m_multiplier[1], m_multiplier[0], multiplier_})
         add0:
         begin
            {temp, m_multiplier, multiplier_} <= {temp[64], temp[64], temp, m_multiplier[63:1]};
         end
         
			add_multiplicand:
         begin
            {temp, m_multiplier, multiplier_} <= {add[64], add[64], add, m_multiplier[63:1]};
         end
         
			add_multiplicand2:
         begin
            {temp, m_multiplier, multiplier_} <= {add[64], add[64], add, m_multiplier[63:1]};
         end
         
			add_2_multiplicand:
         begin
            {temp, m_multiplier, multiplier_} <= {add2[64], add2[64], add2, m_multiplier[63:1]};
         end
			
			sub_2_multiplicand:
			begin
				{temp, m_multiplier, multiplier_} <= {sub2[64], sub2[64], sub2, m_multiplier[63:1]};
			end
			
			sub_multiplicand:
			begin
				{temp, m_multiplier, multiplier_} <= {sub[64], sub[64], sub, m_multiplier[63:1]};
			end
			
			sub_multiplicand2:
			begin
				{temp, m_multiplier, multiplier_} <= {sub[64], sub[64], sub, m_multiplier[63:1]};
			end
			
			sub0:
			begin
				{temp, m_multiplier, multiplier_} <= {temp[64], temp[64], temp, m_multiplier[63:1]};
			end
			
         default:
         begin
            {temp, m_multiplier, multiplier_} <= {65'bx, 64'bx, 1'bx};
         end
      endcase
      data_count <= data_count + 1'b1;
      if (data_count == 32) //finish calculation, except op_done signal hold
      begin
         op_done <= 1'b1;
         multiplier_ <= multiplier_;
         data_count <= data_count;
         temp <= temp;
         m_multiplier <= m_multiplier;
         m_multiplicand <= m_multiplicand;
      end
   end

     else if(op_start == 0 && op_clear == 1) //logical zero
      begin
         op_done <= 1'b0;
         multiplier_ <= 1'b0;
         data_count <= 6'b0;
         temp <= 65'b0;
         m_multiplier <= 64'b0;
         m_multiplicand <= 65'b0;
      end 
      
      else //defualt
      begin
         op_done <= 1'bx;
         multiplier_ <= 1'bx;
         data_count <= 6'bx;
         temp <= 65'bx;
         m_multiplier <= 64'bx;
         m_multiplicand <= 65'bx;
      end 
   end
endmodule 