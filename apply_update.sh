#!/bin/bash

# Location where the source image of update is stored.
DEFAULT_UPDATE_SOURCE_LOCATION='/home/test/tmp/fw_sandbox/fwsim/fwupdate'

# Location where files from update should ultimately reside.
DEFAULT_UPDATE_DESTINATION='/home/test/tmp/fw_sandbox/fwsim/master'

# Location where affected files are backed up before update.
DEFAULT_BACKUP_LOCATION='/home/test/tmp/fw_sandbox/fwsim/fwbackup'

# Temporary directory to extract (and process) files from update image.
DEFAULT_WORK_DIRECTORY='/tmp/fw'

# Default time duration for services to come up and running. Used to check
# if they are able to run properly after update is applied.
DEFAULT_WAIT=5

# Result of update process.
result=0

dateStr1=`date +%Y%m%d-%H%M%S`
dateStr2=`date -Iseconds`
BACKUP_DIR=$DEFAULT_BACKUP_LOCATION/$dateStr1
BACKUP_IMAGE=$DEFAULT_UPDATE_SOURCE_LOCATION/fwimage.tar

mkdir -p $DEFAULT_WORK_DIRECTORY

# Extract list of directories from the update image.
# Check if given paths exist, else create new.
echo "Checking update image for directories ... "
for i in `tar -tvf $BACKUP_IMAGE | grep "^d" | cut -c49-`
do
  if [ ! -e $DEFAULT_UPDATE_DESTINATION/$i ]; then
    echo -e "\tcreating $i in destination dir"
    mkdir -p $DEFAULT_UPDATE_DESTINATION/$i
  fi

  if [ ! -e $BACKUP_DIR/$i ]; then
    echo -e "\tcreating $i in backup dir"
    mkdir -p $BACKUP_DIR/$i
  fi
done
echo "done."

# Stop all service processes.
echo -n "Stopping service processes ... "
#/etc/init.d/agent1 stop
#/etc/init.d/agent2 stop
echo "done."

# Create a new date-stamped directory under backup area.
echo -n "Creating backup directory ... "
mkdir -p $BACKUP_DIR
echo "done."

# Extract files from the update image.
echo -n "Extracting update image ... "
tar -xf $BACKUP_IMAGE -C $DEFAULT_WORK_DIRECTORY
echo "done."

# Copy affected files to backup area.
echo -n "Backing up affected files ... "
for i in `tar -tvf $BACKUP_IMAGE | grep -v "^d" | cut -c49-`
do
  cp $DEFAULT_UPDATE_DESTINATION/$i $BACKUP_DIR/$i
done
echo "done."

# Copy new files to respective locations.
echo -n "Applying update ... "
for i in `tar -tvf $BACKUP_IMAGE | grep -v "^d" | cut -c49-`
do
  cp $DEFAULT_WORK_DIRECTORY/$i $DEFAULT_UPDATE_DESTINATION/$i
done
echo "done."

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

# Remove temporary work directory.
\rm -rf $DEFAULT_WORK_DIRECTORY

# Save update result.
updTime=`date -d$dateStr2 +%s`
echo $result:$updTime > $DEFAULT_BACKUP_LOCATION/result
echo $dateStr1 >> $DEFAULT_BACKUP_LOCATION/result
