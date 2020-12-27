cat /proc/bus/input/devices | awk '/keyboard/{for(a=0;a>=0;a++){getline;{if(/kbd/==1){ print 
$NF;exit 0;}}}}'
