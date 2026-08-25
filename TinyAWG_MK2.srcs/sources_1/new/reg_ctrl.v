`timescale 1 ns / 1 ps

	module reg_ctrl #
	(
		// Users to add parameters here

		// User parameters ends
		// Do not modify the parameters beyond this line

		// Width of S_AXI data bus
		parameter integer C_S_AXI_DATA_WIDTH	= 32,
		// Width of S_AXI address bus
		parameter integer C_S_AXI_ADDR_WIDTH	= 8
	)
	(
		// Users to add ports here
        output wire [31:0] dds0_total_points,
        output wire dds0_en,
        output wire dds0_sel,
        output wire [31:0] dds0_pinc,
        output wire [31:0] dds0_poff,
        output wire [31:0] dds1_total_points,
        output wire dds1_en, 
        output wire dds1_sel,
        output wire [31:0] dds1_pinc,
        output wire [31:0] dds1_poff,
		// User ports ends
		// Do not modify the ports beyond this line

		// Global Clock Signal
		input wire  S_AXI_ACLK,
		// Global Reset Signal. This Signal is Active LOW
		input wire  S_AXI_ARESETN,
		// Write address (issued by master, acceped by Slave)
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_AWADDR,
		// Write channel Protection type. This signal indicates the
    		// privilege and security level of the transaction, and whether
    		// the transaction is a data access or an instruction access.
		input wire [2 : 0] S_AXI_AWPROT,
		// Write address valid. This signal indicates that the master signaling
    		// valid write address and control information.
		input wire  S_AXI_AWVALID,
		// Write address ready. This signal indicates that the slave is ready
    		// to accept an address and associated control signals.
		output wire  S_AXI_AWREADY,
		// Write data (issued by master, acceped by Slave) 
		input wire [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_WDATA,
		// Write strobes. This signal indicates which byte lanes hold
    		// valid data. There is one write strobe bit for each eight
    		// bits of the write data bus.    
		input wire [(C_S_AXI_DATA_WIDTH/8)-1 : 0] S_AXI_WSTRB,
		// Write valid. This signal indicates that valid write
    		// data and strobes are available.
		input wire  S_AXI_WVALID,
		// Write ready. This signal indicates that the slave
    		// can accept the write data.
		output wire  S_AXI_WREADY,
		// Write response. This signal indicates the status
    		// of the write transaction.
		output wire [1 : 0] S_AXI_BRESP,
		// Write response valid. This signal indicates that the channel
    		// is signaling a valid write response.
		output wire  S_AXI_BVALID,
		// Response ready. This signal indicates that the master
    		// can accept a write response.
		input wire  S_AXI_BREADY,
		// Read address (issued by master, acceped by Slave)
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_ARADDR,
		// Protection type. This signal indicates the privilege
    		// and security level of the transaction, and whether the
    		// transaction is a data access or an instruction access.
		input wire [2 : 0] S_AXI_ARPROT,
		// Read address valid. This signal indicates that the channel
    		// is signaling valid read address and control information.
		input wire  S_AXI_ARVALID,
		// Read address ready. This signal indicates that the slave is
    		// ready to accept an address and associated control signals.
		output wire  S_AXI_ARREADY,
		// Read data (issued by slave)
		output wire [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_RDATA,
		// Read response. This signal indicates the status of the
    		// read transfer.
		output wire [1 : 0] S_AXI_RRESP,
		// Read valid. This signal indicates that the channel is
    		// signaling the required read data.
		output wire  S_AXI_RVALID,
		// Read ready. This signal indicates that the master can
    		// accept the read data and response information.
		input wire  S_AXI_RREADY
	);

	// AXI4LITE signals
	reg [C_S_AXI_ADDR_WIDTH-1 : 0] 	axi_awaddr;
	reg  	axi_awready;
	reg  	axi_wready;
	reg [1 : 0] 	axi_bresp;
	reg  	axi_bvalid;
	reg [C_S_AXI_ADDR_WIDTH-1 : 0] 	axi_araddr;
	reg  	axi_arready;
	reg [1 : 0] 	axi_rresp;
	reg  	axi_rvalid;

	// Example-specific design signals
	// local parameter for addressing 32 bit / 64 bit C_S_AXI_DATA_WIDTH
	// ADDR_LSB is used for addressing 32/64 bit registers/memories
	// ADDR_LSB = 2 for 32 bits (n downto 2)
	// ADDR_LSB = 3 for 64 bits (n downto 3)
	localparam integer ADDR_LSB = (C_S_AXI_DATA_WIDTH/32) + 1;
	localparam integer OPT_MEM_ADDR_BITS = 5;
	//----------------------------------------------
	//-- Signals for user logic register space example
	//------------------------------------------------
	//-- Number of Slave Registers 64
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg0;
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg1;
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg2;
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg3;
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg4;
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg5;
	reg [C_S_AXI_DATA_WIDTH-1:0]	slv_reg6;
	integer	 byte_index;

	// I/O Connections assignments

	assign S_AXI_AWREADY	= axi_awready;
	assign S_AXI_WREADY	= axi_wready;
	assign S_AXI_BRESP	= axi_bresp;
	assign S_AXI_BVALID	= axi_bvalid;
	assign S_AXI_ARREADY	= axi_arready;
	assign S_AXI_RRESP	= axi_rresp;
	assign S_AXI_RVALID	= axi_rvalid;
	 //state machine varibles 
	 reg [1:0] state_write;
	 reg [1:0] state_read;
	 //State machine local parameters
	 localparam Idle = 2'b00,Raddr = 2'b10,Rdata = 2'b11 ,Waddr = 2'b10,Wdata = 2'b11;
		// Implement Write state machine
	// Outstanding write transactions are not supported by the slave i.e., master should assert bready to receive response on or before it starts sending the new transaction
	always @(posedge S_AXI_ACLK)                                 
	  begin                                 
	     if (S_AXI_ARESETN == 1'b0)                                 
	       begin                                 
	         axi_awready <= 1'b1;  // 初始就绪
	         axi_wready <= 1'b1;   // 初始就绪
	         axi_bvalid <= 0;                                 
	         axi_bresp <= 0;                                 
	         axi_awaddr <= 0;                                 
	         state_write <= Idle;                                 
	       end                                 
	     else                                  
	       begin                                 
	         case(state_write)                                 
	           Idle: begin
	             // 保持就绪状态，等待有效写操作
	             axi_awready <= 1'b1;
	             axi_wready <= 1'b1;
	             
	             // 当同时收到地址和数据时，进入响应状态
	             if (S_AXI_AWVALID && S_AXI_WVALID) begin
	                 state_write <= Waddr;                                 
	                 axi_awaddr <= S_AXI_AWADDR;
	                 axi_bvalid <= 1'b1;      // 立即响应
	                 axi_awready <= 1'b0;     // 暂时不接收新地址
	                 axi_wready <= 1'b0;      // 暂时不接收新数据
	             end
	           end                                 
	           
	           Waddr: begin
	             // 等待主设备确认响应
	             if (S_AXI_BREADY && axi_bvalid) begin
	                 axi_bvalid <= 1'b0;      // 清除响应
	                 state_write <= Idle;     // 回到空闲，准备下一次操作
	                 axi_awready <= 1'b1;     // 重新准备接收地址
	                 axi_wready <= 1'b1;      // 重新准备接收数据
	             end
	           end                                 
	         endcase                                 
	       end                                 
	  end
	// Implement memory mapped register select and write logic generation
	// The write data is accepted and written to memory mapped registers when
	// axi_awready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted. Write strobes are used to
	// select byte enables of slave registers while writing.
	// These registers are cleared when reset (active low) is applied.
	// Slave register write enable is asserted when valid address and data are available
	// and the slave is ready to accept the write address and write data.
	 
	// Write signal latch registers to shorten timing paths
	reg write_enable;
	reg [ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] write_addr;
	reg [C_S_AXI_DATA_WIDTH-1:0] write_data;
	reg [(C_S_AXI_DATA_WIDTH/8)-1:0] write_strb;

	// Latch write signals at clock edge
	always @(posedge S_AXI_ACLK) begin
	    if (S_AXI_ARESETN == 1'b0) begin
	        write_enable <= 1'b0;
	        write_addr <= 0;
	        write_data <= 0;
	        write_strb <= 0;
	    end else begin
	        // Generate write enable when all write signals are valid and ready
	        write_enable <= S_AXI_AWVALID && S_AXI_WVALID && axi_awready && axi_wready;
	        
	        // Latch address when address is valid and ready
	        if (S_AXI_AWVALID && axi_awready) begin
	            write_addr <= S_AXI_AWADDR[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB];
	        end
	        
	        // Latch data when data is valid and ready  
	        if (S_AXI_WVALID && axi_wready) begin
	            write_data <= S_AXI_WDATA;
	            write_strb <= S_AXI_WSTRB;
	        end
	    end
	end


		// Implement memory mapped register select and write logic generation
	// The write data is accepted and written to memory mapped registers when
	// axi_awready, S_AXI_WVALID, axi_wready and S_AXI_WVALID are asserted. Write strobes are used to
	// select byte enables of slave registers while writing.
	// These registers are cleared when reset (active low) is applied.
	// Slave register write enable is asserted when valid address and data are available
	// and the slave is ready to accept the write address and write data.

	always @( posedge S_AXI_ACLK )
	begin
	  if ( S_AXI_ARESETN == 1'b0 )
	    begin
	      slv_reg0 <= 0;
	      slv_reg1 <= 0;
	      slv_reg2 <= 0;
	      slv_reg3 <= 0;
	      slv_reg4 <= 0;
	      slv_reg5 <= 0;
	      slv_reg6 <= 0;	      
	    end 
	  else if (write_enable) begin
	    case ( write_addr )
	      6'h0:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 0
	            slv_reg0[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      6'h1:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 1
	            slv_reg1[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      6'h2:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 1
	            slv_reg2[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      6'h3:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 1
	            slv_reg3[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      6'h4:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 1
	            slv_reg4[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      6'h5:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 1
	            slv_reg5[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      6'h6:
	        for ( byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1 )
	          if ( write_strb[byte_index] == 1 ) begin
	            // Respective byte enables are asserted as per write strobes 
	            // Slave register 1
	            slv_reg6[(byte_index*8) +: 8] <= write_data[(byte_index*8) +: 8];
	          end  
	      default : begin
	                  // 默认情况下保持原值
	                  slv_reg0 <= slv_reg0;
	                  slv_reg1 <= slv_reg1;
	                  slv_reg2 <= slv_reg2;
	                  slv_reg3 <= slv_reg3;               
	                end
	    endcase
	  end
	end

	// Implement read state machine
	always @(posedge S_AXI_ACLK)                                       
	  begin                                       
	    if (S_AXI_ARESETN == 1'b0)                                       
	      begin                                       
	        axi_arready <= 1'b1;  // 初始就绪
	        axi_rvalid <= 1'b0;                                       
	        axi_rresp <= 2'b00;                                       
	        axi_araddr <= 0;                                       
	        state_read <= Idle;                                       
	      end                                       
	    else                                       
	      begin                                       
	        case(state_read)                                       
	          Idle:                                       
	            begin                                       
	              axi_arready <= 1'b1;
	              axi_rvalid <= 1'b0;
	              
	              if (S_AXI_ARVALID) begin
	                state_read <= Rdata;                                       
	                axi_araddr <= S_AXI_ARADDR;                                       
	                axi_rvalid <= 1'b1;  // 立即产生有效数据
	                axi_arready <= 1'b0; // 暂时不接收新地址
	              end
	            end                                       
	            
	          Rdata:                                       
	            begin                                       
	              if (S_AXI_RREADY && axi_rvalid) begin
	                axi_rvalid <= 1'b0;      // 清除数据有效
	                state_read <= Idle;      // 回到空闲状态
	                axi_arready <= 1'b1;     // 重新准备接收地址
	              end
	            end                                       
	        endcase                                       
	      end                                       
	  end
	    
	// Read address pipeline register to shorten timing path
	reg [ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB] read_addr_reg;
	reg read_addr_valid;
	
	always @(posedge S_AXI_ACLK) begin
	    if (S_AXI_ARESETN == 1'b0) begin
	        read_addr_reg <= 0;
	        read_addr_valid <= 1'b0;
	    end else begin
	        // 锁存读地址
	        if (S_AXI_ARVALID && axi_arready) begin
	            read_addr_reg <= S_AXI_ARADDR[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB];
	            read_addr_valid <= 1'b1;
	        end else if (axi_rvalid && S_AXI_RREADY) begin
	            read_addr_valid <= 1'b0;
	        end
	    end
	end
                                     
// Implement memory mapped register select and read logic generation
reg [C_S_AXI_DATA_WIDTH-1:0] s_axi_rdata_reg;

// 使用流水线后的读地址
always @(*) begin
    if (read_addr_valid) begin
        case (read_addr_reg)
            6'h00: s_axi_rdata_reg = slv_reg0;
            6'h01: s_axi_rdata_reg = slv_reg1;
            6'h02: s_axi_rdata_reg = slv_reg2;
            6'h03: s_axi_rdata_reg = slv_reg3;
            6'h04: s_axi_rdata_reg = slv_reg4;
            6'h05: s_axi_rdata_reg = slv_reg5;
            6'h06: s_axi_rdata_reg = slv_reg6;
            default: s_axi_rdata_reg = {C_S_AXI_DATA_WIDTH{1'b0}};
        endcase
    end else begin
        s_axi_rdata_reg = {C_S_AXI_DATA_WIDTH{1'b0}};
    end
end

assign S_AXI_RDATA = s_axi_rdata_reg;

// Add user logic here
reg [31:0] dds0_total_points_reg;
reg dds0_en_reg;
reg dds0_sel_reg;
reg [31:0] dds0_pinc_reg;
reg [31:0] dds0_poff_reg;
reg [31:0] dds1_total_points_reg;
reg dds1_en_reg;
reg dds1_sel_reg;
reg [31:0] dds1_pinc_reg;
reg [31:0] dds1_poff_reg;

always @(posedge S_AXI_ACLK) begin
    dds0_total_points_reg <= slv_reg0;
    dds1_total_points_reg <= slv_reg1;
    dds0_pinc_reg <= slv_reg3;
    dds0_poff_reg <= slv_reg4;
    dds1_pinc_reg <= slv_reg5;
    dds1_poff_reg <= slv_reg6;
    dds0_en_reg <= slv_reg2[0];
    dds1_en_reg <= slv_reg2[1];
    dds0_sel_reg <= slv_reg2[2];
    dds1_sel_reg <= slv_reg2[3];
end

// 驱动顶层输出
assign dds0_total_points  = dds0_total_points_reg;
assign dds0_en = dds0_en_reg;
assign dds0_sel  = dds0_sel_reg;
assign dds0_poff  = dds0_poff_reg;
assign dds0_pinc  = dds0_pinc_reg;

assign dds1_total_points = dds1_total_points_reg;
assign dds1_en  = dds1_en_reg;
assign dds1_sel  = dds1_sel_reg;
assign dds1_poff  = dds1_poff_reg;
assign dds1_pinc  = dds1_pinc_reg;
// User logic ends

endmodule
