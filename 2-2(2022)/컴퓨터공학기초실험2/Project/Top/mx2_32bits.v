module mx2_32bits(d0,d1,s,y); //32-bits mx2 module
   input [31:0] d0,d1;
   input s;
   output [31:0] y;

   assign y = (s==0)?d0:d1; //if s==0, y=d0 and if s!=0, y=d1
endmodule 