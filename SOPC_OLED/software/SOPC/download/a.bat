C:\\altera\\11.0\\quartus\\bin64\\quartus_pgm.exe -m jtag -c "USB-Blaster[USB-0]" -o "p;SOPC_MinSys.sof"

@ set SOPC_BUILDER_PATH_110=%SOPC_KIT_NIOS2%+%SOPC_BUILDER_PATH_110%
@"C:\altera\11.0\quartus\bin64\cygwin\bin\bash.exe" --rcfile ".\hello_ucosii_bashrc"
pause