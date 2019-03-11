  //Example instantiation for system 'NIOS_II'
  NIOS_II NIOS_II_inst
    (
      .address_to_the_cfi_flash       (address_to_the_cfi_flash),
      .clk                            (clk),
      .data_to_and_from_the_cfi_flash (data_to_and_from_the_cfi_flash),
      .oled_cs_n_from_the_oled        (oled_cs_n_from_the_oled),
      .oled_data_cmd_n_from_the_oled  (oled_data_cmd_n_from_the_oled),
      .oled_write_n_from_the_oled     (oled_write_n_from_the_oled),
      .oled_writedata_from_the_oled   (oled_writedata_from_the_oled),
      .out_port_from_the_rst          (out_port_from_the_rst),
      .read_n_to_the_cfi_flash        (read_n_to_the_cfi_flash),
      .reset_n                        (reset_n),
      .rxd_to_the_uart0               (rxd_to_the_uart0),
      .select_n_to_the_cfi_flash      (select_n_to_the_cfi_flash),
      .txd_from_the_uart0             (txd_from_the_uart0),
      .write_n_to_the_cfi_flash       (write_n_to_the_cfi_flash),
      .zs_addr_from_the_sdram         (zs_addr_from_the_sdram),
      .zs_ba_from_the_sdram           (zs_ba_from_the_sdram),
      .zs_cas_n_from_the_sdram        (zs_cas_n_from_the_sdram),
      .zs_cke_from_the_sdram          (zs_cke_from_the_sdram),
      .zs_cs_n_from_the_sdram         (zs_cs_n_from_the_sdram),
      .zs_dq_to_and_from_the_sdram    (zs_dq_to_and_from_the_sdram),
      .zs_dqm_from_the_sdram          (zs_dqm_from_the_sdram),
      .zs_ras_n_from_the_sdram        (zs_ras_n_from_the_sdram),
      .zs_we_n_from_the_sdram         (zs_we_n_from_the_sdram)
    );

