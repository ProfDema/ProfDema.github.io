#!/bin/bash
count=`ls -1 .209_web_root 2>/dev/null | wc -l` # basic sanity check to make sure that script is being run from www directory
if [ $count != 0 ]
then
	rsync --cvs-exclude --perms --recursive --times -e ssh ./ 209@mcs.utm.utoronto.ca:~/www/ --delete
else
	echo "This script should be run from the www directory."
fi
