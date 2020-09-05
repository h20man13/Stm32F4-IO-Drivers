#!/bin/bash
rm -f ./Debugger_Info.txt &&
> ./Debugger_Info.txt &&
/opt/openocd/bin/openocd --log_output ./Debugger_Info.txt --file /opt/openocd/scripts/board/st_nucleo_f4.cfg &
gdb-multiarch $1 -ex 'target extended-remote :3333' &&
var=$(sudo pidof /opt/openocd/bin/openocd) &&
kill $var &&
echo ""
echo ""
echo "Open OCD Session Summary"
echo "========================================================================="
Storage=$(cat ./Debugger_Info.txt) &&
echo "$Storage"
echo "========================================================================="
echo ""
rm -f ./Debugger_Info.txt;
