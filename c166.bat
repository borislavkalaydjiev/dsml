
setlocal

set LM_LICENSE_FILE=C:\tools\compiler\Tasking\license.dat
set CC=C:\tools\compiler\c166\v86r3\bin\cc166 -c -Wc-misrac-advisory-warnings -Wc-misrac-required-warnings -Wc-w135 -Wc-x -Wc-Fs -Wc-Ml -Wc-T0 -Wc-P -Wc-g -Wc-Oa -Wc-w68 -Wc-AF -Wc-I. -Wc-I..\..\
set SIZE=C:\tools\compiler\c166\v86r3\bin\dmp166 -s

%CC% debug.c
%CC% tools.c
%CC% mem_file_iface.c
%CC% core.c

%SIZE% *.obj | findstr os_size
