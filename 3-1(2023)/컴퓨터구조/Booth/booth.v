`include "alu.v"
module booth(input1, input2, clk, start, reset, result, count);
    input [3:0] input1, input2;
    input clk, start, reset;
    output [7:0] result;
    output reg [2:0] count;

    reg [3:0] A, Q, M;
    reg Q_1;
    wire [3:0] add, sub;

    always @(posedge clk or negedge reset) begin
        if(~reset)
        begin //reset
            A <= 4'b0;
            M <= 4'b0;
            Q <= 4'b0;
            Q_1 <= 1'b0;
            count <= 3'b0;
        end
        
        else if(~start)
        begin //start
            A <= 4'b0;
            M <= input1;
            Q <= input2;
            Q_1 <= 1'b0;
            count <= 3'b0;
        end
      else if(count == 3'b100)
        begin
            A <= A;
            M <= M;
            Q <= Q;
            Q_1 <= Q_1;
            count <= count;
        end
 
        else
        begin
        case({Q[0], Q_1})
        2'b0_1 : {A, Q, Q_1} <= {add[3], add, Q}; //A + M and shift right
        2'b1_0 : {A, Q, Q_1} <= {sub[3], sub, Q}; //A + ~M and shift right
        default : {A, Q, Q_1} <= {A[3], A, Q}; //shift right
        endcase

        count = count + 1'b1;
        end
    end
    
    alu adder(A, M, 1'b0, add);
    alu subtractor(A, ~M, 1'b1, sub);

    assign result = {A, Q};
endmodule