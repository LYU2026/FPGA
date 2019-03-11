-- oled.vhd

-- This file was auto-generated as part of a SOPC Builder generate operation.
-- If you edit it your changes will probably be lost.

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity oled is
	port (
		avalon_write      : in  std_logic                     := '0';             -- avalon_slave_0.write
		avalon_chipselect : in  std_logic                     := '0';             --               .chipselect
		avalon_writedata  : in  std_logic_vector(31 downto 0) := (others => '0'); --               .writedata
		avalon_address    : in  std_logic_vector(7 downto 0)  := (others => '0'); --               .address
		clk               : in  std_logic                     := '0';             --     clock_sink.clk
		reset_n           : in  std_logic                     := '0';             --     reset_sink.reset_n
		oled_cs_n         : out std_logic;                                        --    conduit_end.export
		oled_write_n      : out std_logic;                                        --               .export
		oled_data_cmd_n   : out std_logic;                                        --               .export
		oled_writedata    : out std_logic_vector(7 downto 0)                      --               .export
	);
end entity oled;

architecture rtl of oled is
	component oled_con is
		port (
			avalon_write      : in  std_logic                     := 'X';             -- write
			avalon_chipselect : in  std_logic                     := 'X';             -- chipselect
			avalon_writedata  : in  std_logic_vector(31 downto 0) := (others => 'X'); -- writedata
			avalon_address    : in  std_logic_vector(7 downto 0)  := (others => 'X'); -- address
			clk               : in  std_logic                     := 'X';             -- clk
			reset_n           : in  std_logic                     := 'X';             -- reset_n
			oled_cs_n         : out std_logic;                                        -- export
			oled_write_n      : out std_logic;                                        -- export
			oled_data_cmd_n   : out std_logic;                                        -- export
			oled_writedata    : out std_logic_vector(7 downto 0)                      -- export
		);
	end component oled_con;

begin

	oled : component oled_con
		port map (
			avalon_write      => avalon_write,      -- avalon_slave_0.write
			avalon_chipselect => avalon_chipselect, --               .chipselect
			avalon_writedata  => avalon_writedata,  --               .writedata
			avalon_address    => avalon_address,    --               .address
			clk               => clk,               --     clock_sink.clk
			reset_n           => reset_n,           --     reset_sink.reset_n
			oled_cs_n         => oled_cs_n,         --    conduit_end.export
			oled_write_n      => oled_write_n,      --               .export
			oled_data_cmd_n   => oled_data_cmd_n,   --               .export
			oled_writedata    => oled_writedata     --               .export
		);

end architecture rtl; -- of oled
