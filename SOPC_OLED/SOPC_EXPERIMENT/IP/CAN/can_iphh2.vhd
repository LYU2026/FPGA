library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity can_iphh2 is
    port
    (
   --global signal
     clk       : in   std_logic;
     reset_n   : in   std_logic;
   --avalon signal
     avalon_selectchip   :   in    std_logic;
     avalon_addr         :   in    std_logic_vector(9 downto 0);
     avalon_waitreq      :   out   std_logic;
     
     avalon_write        :   in    std_logic;
     avalon_writedata    :   in    std_logic_vector(7 downto 0);

     avalon_read         :   in    std_logic;
     avalon_readdata     :   out   std_logic_vector(7 downto 0);
     
     avalon_irq_n        :   out   std_logic;          
   --can  signal
     can_ad              :   inout std_logic_vector(7 downto 0);
     can_ale             :   out   std_logic; 
     can_write_n         :   out   std_logic;
     can_read_n          :   out   std_logic;
     can1_irq_n           :   in    std_logic;
     can2_irq_n           :   in    std_logic;
	 can_cs1_n			 :	 out	std_logic;
	 can_cs2_n			 :	 out	std_logic
    );
end can_iphh2;

architecture arch of can_iphh2  is
   
    TYPE           STATE_TYPE   IS       (idle,first,second,third,forth,fifth,sixth);
	SIGNAL         present_state         :   STATE_TYPE:=idle;
	SIGNAL         busy_flag             :   std_logic :='0';
	SIGNAL         address_temp          :   STD_LOGIC_VECTOR(7 DOWNTO 0);
	SIGNAL         writedata_temp        :   STD_LOGIC_VECTOR(7 DOWNTO 0);	     
	begin
    
    avalon_irq_n<=can1_irq_n and can2_irq_n; 

process(avalon_selectchip,avalon_write,avalon_addr)
    begin
       if avalon_selectchip ='1' then	
        case avalon_addr(9 downto 8) is
           when "00"	 =>
              can_cs1_n <='0';
              can_cs2_n <='1';
           when "01"	 =>
              can_cs1_n <='1';
              can_cs2_n <='0';
           when "10"	 =>
              if(avalon_write='1') then
                 can_cs1_n <='0';
                 can_cs2_n <='0';
              else
                 can_cs1_n <='1';
                 can_cs2_n <='1';
              end if;
           when others =>
              can_cs1_n <='1';
              can_cs2_n <='1';	
         end case;	
        else
              can_cs1_n <='1';
              can_cs2_n <='1';
        end if;
						
    end process;

    process(reset_n,clk,avalon_selectchip)--,busy_flag
        variable counter :integer range 0 to 15 :=0; 
        begin
            if reset_n  ='0' or avalon_selectchip='0' then 
               address_temp    <="00000000";
               writedata_temp  <="00000000";
               can_ad          <="ZZZZZZZZ";
               can_ale         <='0';
               can_write_n     <='1';
               can_read_n      <='1'; 
               avalon_waitreq  <='1';  
               busy_flag       <='0';
               counter         :=0;
               present_state   <=first;
			elsif clk'event and clk='1' then
				if avalon_selectchip ='1' and avalon_write='1' then
					case present_state is
					when first	=>	can_ale <= '1';
									can_ad <= avalon_addr(7 downto 0);
									writedata_temp <= avalon_writedata;
									avalon_waitreq <= '1';
									present_state <= second; 
									
					when second	=>	can_ale <= '0';
									present_state <= third;
									
					when third	=>	can_ad <= writedata_temp;						         
						       		can_write_n <= '0';
									present_state <= forth;
									
					when forth	=>	can_write_n <= '0';
									present_state <= fifth;
									
					when  fifth	=>	can_write_n <= '1';						       
						       		present_state <= sixth;
					
					when  sixth	=>	can_ad <= "ZZZZZZZZ";
									can_ale <= '0';
									can_write_n <= '1';
									can_read_n <= '1';
									avalon_waitreq <= '0';
									present_state <=idle;
									
					when others	=>	Null;	
					end case;
					
				elsif avalon_selectchip ='1' and avalon_read ='1' then 
					case present_state is
					when first	=>	can_ad <= avalon_addr(7 downto 0); 
									can_ale <= '1'; 
									present_state <=second;
									
					when second	=>	can_ale <= '0';                               
                               		present_state <=third;

					when third	=>	can_ad <= "ZZZZZZZZ";							   
							   		can_read_n <= '0';
							   		counter := 0;
							   		present_state <= forth;
							
					when forth	=>	counter := counter+1;
							   		if counter<2 then --1clk
						          		present_state <= forth;
						       		else 
						          		counter := 0;
						         		 present_state <= fifth;
						       		end if;
						
					when fifth	=>	avalon_readdata <= can_ad;							   
							   		can_read_n    <= '1';
							   		present_state <= sixth;		
												
					when sixth	=>	can_ad <= "ZZZZZZZZ";
							      	can_ale <= '0';
						       		can_write_n <= '1';
						       		can_read_n <= '1';
									avalon_waitreq  <='0';
                               		present_state <=idle;																										
							
					when others=>	null;
					end case;					
					end if;
			end if;
	end process;
end arch;
							
							   
