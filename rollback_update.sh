#!/bin/bash

# Base location for stored backup directories
DEFAULT_BACKUP_LOCATION='/home/test/tmp/fw_sandbox/fwsim/fwbackup'

# Location where restored files should reside.
DEFAULT_UPDATE_DESTINATION='/home/test/tmp/fw_sandbox/fwsim/restored'

# Temporary directory for local processing.
DEFAULT_WORK_DIRECTORY='/tmp/fw'

# Default time duration for services to come up and running. Used to check
# if they are able to run properly after rollback is applied.
DEFAULT_WAIT=5

if [ $# -eq 0 ]; then
  echo "no arg given"
  exit 1
else
  echo $1
fi
backupDirName=$1
backupDirPath=$DEFAULT_BACKUP_LOCATION/$backupDirName

mkdir -p $DEFAULT_WORK_DIRECTORY

# Stop all service processes.
echo -n "Stopping service processes ... "
#/etc/init.d/agent1 stop
#/etc/init.d/agent2 stop
echo "done."

# Restore original files from backup area.
echo -n "Restoring files from $backupDirName ... "
find $backupDirPath -type f -print | cut -d- -f2 | cut -d/ -f2- > $DEFAULT_WORK_DIRECTORY/filelist
for i in `cat $DEFAULT_WORK_DIRECTORY/filelist`
do
  #echo "Restoring $i"
  cp $backupDirPath/$i $DEFAULT_UPDATE_DESTINATION/$i
done
echo "done."
exit 0

# Start all service processes.
echo -n "Starting service processes ... "
#/etc/init.d/agent1 start
#/etc/init.d/agent2 start
echo "done."

echo -n "Checking for restarted processes ... "
# Wait for some time to check if service processes are still running.
sleep $DEFAULT_WAIT
/etc/init.d/agent1 status >& /dev/null
ret=$?
if [ $ret -ne 0 ]
then
  #echo "not running"
  ret_val=1
else
  #echo "running"
  ret_val=0
fi
result=`expr $result + $ret_val`

/etc/init.d/agent2 status >& /dev/null
ret=$?
if [ $ret -ne 0 ]
then
  #echo "not running"
  ret_val=1
else
  #echo "running"
  ret_val=0
fi
result=`expr $result + $ret_val`
echo "done."
