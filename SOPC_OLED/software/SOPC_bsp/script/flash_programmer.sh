#!/bin/sh
#
# This file was automatically generated.
#
# It can be overwritten by nios2-flash-programmer-generate or nios2-flash-programmer-gui.
#

#
# Converting SOF File: F:\SOPC_OLED\SOPC_MinSys.sof to: "..\flash/SOPC_MinSys_epcs.flash"
#
$SOPC_KIT_NIOS2/bin/sof2flash --input="F:/SOPC_OLED/SOPC_MinSys.sof" --output="../flash/SOPC_MinSys_epcs.flash" --epcs --verbose 

#
# Programming File: "..\flash/SOPC_MinSys_epcs.flash" To Device: epcs
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/SOPC_MinSys_epcs.flash" --base=0x0 --epcs --sidp=0x1C58 --id=0x0 --timestamp=1431481602 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

#
# Converting ELF File: F:\SOPC_OLED\software\SOPC\SOPC.elf to: "..\flash/SOPC_epcs.flash"
#
$SOPC_KIT_NIOS2/bin/elf2flash --input="F:/SOPC_OLED/software/SOPC/SOPC.elf" --output="../flash/SOPC_epcs.flash" --epcs --after="../flash/SOPC_MinSys_epcs.flash" --verbose 

#
# Programming File: "..\flash/SOPC_epcs.flash" To Device: epcs
#
$SOPC_KIT_NIOS2/bin/nios2-flash-programmer "../flash/SOPC_epcs.flash" --base=0x0 --epcs --sidp=0x1C58 --id=0x0 --timestamp=1431481602 --device=1 --instance=0 '--cable=USB-Blaster on localhost [USB-0]' --program --verbose 

