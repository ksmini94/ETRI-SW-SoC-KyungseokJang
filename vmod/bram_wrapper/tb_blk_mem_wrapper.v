`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/08/08 14:06:21
// Design Name: 
// Module Name: tb_fsm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_blk_mem_wrapper;

reg clk_a;
reg arstz_aq;
cnnip_mem_if           a();

reg clk_b;
reg arstz_bq;
cnnip_mem_if           b();

blk_mem_wrapper tb_blk_mem_wrapper(
    .clk_a(clk_a),
    .arstz_aq(arstz_aq),
    .mem_if_a(a),
    
    .clk_b(clk_b),
    .arstz_bq(arstz_bq),
    .mem_if_b(b)
);

initial begin
    clk_a=0;
    arstz_aq=0;
    a.en=0;
    a.we=0;
    a.addr=12'b0;
    a.din=32'b0;
    
    clk_b=0;
    arstz_bq=0;
    b.en=0;
    b.we=0;
    b.addr=12'b0;
    b.din=32'b0;
    
    @(posedge clk_b);
    #1 arstz_aq = 1; arstz_bq = 1;
    
    @(posedge clk_b);
    
    @(posedge clk_b);
    #1 a.en = 1; a.we = 1;
       a.addr = 12'h0010; a.din = 32'd1;
    
    @(posedge clk_b);
    #1 a.en = 1; a.we = 1;
       a.addr = 12'h0100; a.din = 32'd2;
    
    @(posedge clk_b);
    #1 a.en = 1; a.we = 1;
       a.addr = 12'h1000; a.din = 32'd3;
    
    @(posedge clk_b);
    #1 a.en = 0;   
 
       
    @(posedge clk_b);
    #1 b.en = 1; b.we = 1;
       b.addr = 12'h0010; b.din = 32'd4;
    
    @(posedge clk_b);
    #1 b.en = 1; b.we = 1;
       b.addr = 12'h0100; b.din = 32'd5;
    
    @(posedge clk_b);
    #1 b.en = 1; b.we = 1;
       b.addr = 12'h1000; b.din = 32'd6;
       
    @(posedge clk_b);
    #1 b.en = 1'b1; b.we = 1'b0;
       b.addr = 12'h0010;
    @(posedge clk_b);
    #1 b.en = 1'b1; b.we = 1'b0;
       b.addr = 12'h0100;
    @(posedge clk_b);
    #1 b.en = 1'b1; b.we = 1'b0;
       b.addr = 12'h1000;
 
 //(~(mem_if_b.en == 1'b1 && mem_if_b.we==1'b0))   
    @(posedge clk_b);
    #1 b.en = 1'b0; b.we = 1'b0;
       
    repeat (20) @(posedge clk_b);
    
    $finish;
    
end

always #10 clk_b = ~clk_b;
always #10 clk_a = ~clk_a;

endmodule
