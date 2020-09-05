#!/bin/bash
cp ./lib/tmux.conf ./ &&
sed -i 's:OPENOCD-LOG:/opt/openocd/bin/openocd --file /opt/openocd/scripts/board/st_nucleo_f4.cfg:' ./tmux.conf &&
sed -i 's/CONNECT-DEBUG/gdb-multiarch $1 -ex "target extended-remote :3333"/' ./tmux.conf &&
sed -i 's:GOTO-MAIN-DIR:cd ../RTOS:' ./tmux.conf &&
tmux -f './tmux.conf' &&
tmux a -d -t 'RTOS-DEV-CONSOLE'
tmux ls | awk '{print $1}'|sed 's/.$//'| xargs -t -n1 tmux kill-session -t &&
rm ./tmux.conf
