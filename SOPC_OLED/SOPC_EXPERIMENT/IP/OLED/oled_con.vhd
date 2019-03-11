library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
--edit by yr 2010-11-23
entity oled_con IS
	PORT 
	(
		clk         			:  in  std_logic;		
		reset_n					:  in  std_logic;		
				
		avalon_write			:  in  std_logic;			
		avalon_chipselect 		:  in  std_logic;		
		avalon_writedata		:  in  STD_LOGIC_VECTOR(31 DOWNTO 0);		
		avalon_address			:  in  STD_LOGIC_VECTOR(7 DOWNTO 0);
	 	oled_cs_n   		:  out std_logic;	
	 	oled_write_n		:  out std_logic;	
	 	oled_data_cmd_n		:  out std_logic;	
		oled_writedata 		:  out  STD_LOGIC_VECTOR(7 DOWNTO 0)	
		
			
	);	
	
END oled_con;
ARCHITECTURE a_oled_con OF oled_con IS
	signal state: STD_LOGIC_VECTOR(3 DOWNTO 0);	
BEGIN
process (clk, reset_n)	
begin
     if reset_n='0' then
		state<="0000";
		oled_cs_n<='1';
		oled_write_n <= '1';
		oled_data_cmd_n<='1';
		oled_writedata <= (OTHERS=>'0');    
	 elsif clk'event and clk='1' then	
		if (avalon_chipselect='1' and avalon_write='1' ) then
			CASE state IS
				WHEN "0000" =>     --first step cs,cmd,data,1
					state<="0001";	
					oled_cs_n<='0';
					oled_data_cmd_n<=avalon_address(0);
					oled_writedata(7 downto 0)<=avalon_writedata(7 downto 0);
				WHEN "0001" =>	--second step write_n,2
					state<="0010";	
					oled_write_n <= '0';
				WHEN "0010" =>--,3
					state<="0011";	
				WHEN "0011" =>--,4
					state<="0100";	
				WHEN "0100" => -- third step write data,5
					state<="0101";	
					oled_write_n <= '1';	
				WHEN "0101" =>--,6
					state<="0110";	
				WHEN "0110" =>--,7
					state<="0111";	
				WHEN "0111" =>--,8
					state<="0000";	
					oled_cs_n<='1';
					oled_write_n <= '1';
					oled_data_cmd_n<='1';	
					oled_writedata <= (OTHERS=>'0');    			
				WHEN OTHERS =>
					null;
			END CASE;				
		end if;		
     end if;
end process; 
END a_oled_con;

