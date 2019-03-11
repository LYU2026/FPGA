-- can.vhd

-- This file was auto-generated as part of a SOPC Builder generate operation.
-- If you edit it your changes will probably be lost.

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity can is
	port (
		avalon_selectchip : in    std_logic                    := '0';             --   avalon_slave_0.chipselect
		avalon_addr       : in    std_logic_vector(9 downto 0) := (others => '0'); --                 .address
		avalon_waitreq    : out   std_logic;                                       --                 .waitrequest
		avalon_write      : in    std_logic                    := '0';             --                 .write
		avalon_writedata  : in    std_logic_vector(7 downto 0) := (others => '0'); --                 .writedata
		avalon_read       : in    std_logic                    := '0';             --                 .read
		avalon_readdata   : out   std_logic_vector(7 downto 0);                    --                 .readdata
		clk               : in    std_logic                    := '0';             --       clock_sink.clk
		reset_n           : in    std_logic                    := '0';             --       reset_sink.reset_n
		avalon_irq_n      : out   std_logic;                                       -- interrupt_sender.irq_n
		can_ad            : inout std_logic_vector(7 downto 0) := (others => '0'); --      conduit_end.export
		can_ale           : out   std_logic;                                       --                 .export
		can_write_n       : out   std_logic;                                       --                 .export
		can_read_n        : out   std_logic;                                       --                 .export
		can1_irq_n        : in    std_logic                    := '0';             --                 .export
		can2_irq_n        : in    std_logic                    := '0';             --                 .export
		can_cs1_n         : out   std_logic;                                       --                 .export
		can_cs2_n         : out   std_logic                                        --                 .export
	);
end entity can;

architecture rtl of can is
	component can_iphh2 is
		port (
			avalon_selectchip : in    std_logic                    := 'X';             -- chipselect
			avalon_addr       : in    std_logic_vector(9 downto 0) := (others => 'X'); -- address
			avalon_waitreq    : out   std_logic;                                       -- waitrequest
			avalon_write      : in    std_logic                    := 'X';             -- write
			avalon_writedata  : in    std_logic_vector(7 downto 0) := (others => 'X'); -- writedata
			avalon_read       : in    std_logic                    := 'X';             -- read
			avalon_readdata   : out   std_logic_vector(7 downto 0);                    -- readdata
			clk               : in    std_logic                    := 'X';             -- clk
			reset_n           : in    std_logic                    := 'X';             -- reset_n
			avalon_irq_n      : out   std_logic;                                       -- irq_n
			can_ad            : inout std_logic_vector(7 downto 0) := (others => 'X'); -- export
			can_ale           : out   std_logic;                                       -- export
			can_write_n       : out   std_logic;                                       -- export
			can_read_n        : out   std_logic;                                       -- export
			can1_irq_n        : in    std_logic                    := 'X';             -- export
			can2_irq_n        : in    std_logic                    := 'X';             -- export
			can_cs1_n         : out   std_logic;                                       -- export
			can_cs2_n         : out   std_logic                                        -- export
		);
	end component can_iphh2;

begin

	can : component can_iphh2
		port map (
			avalon_selectchip => avalon_selectchip, --   avalon_slave_0.chipselect
			avalon_addr       => avalon_addr,       --                 .address
			avalon_waitreq    => avalon_waitreq,    --                 .waitrequest
			avalon_write      => avalon_write,      --                 .write
			avalon_writedata  => avalon_writedata,  --                 .writedata
			avalon_read       => avalon_read,       --                 .read
			avalon_readdata   => avalon_readdata,   --                 .readdata
			clk               => clk,               --       clock_sink.clk
			reset_n           => reset_n,           --       reset_sink.reset_n
			avalon_irq_n      => avalon_irq_n,      -- interrupt_sender.irq_n
			can_ad            => can_ad,            --      conduit_end.export
			can_ale           => can_ale,           --                 .export
			can_write_n       => can_write_n,       --                 .export
			can_read_n        => can_read_n,        --                 .export
			can1_irq_n        => can1_irq_n,        --                 .export
			can2_irq_n        => can2_irq_n,        --                 .export
			can_cs1_n         => can_cs1_n,         --                 .export
			can_cs2_n         => can_cs2_n          --                 .export
		);

end architecture rtl; -- of can
