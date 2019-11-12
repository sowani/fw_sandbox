#ifndef FWUPCOMMON_H
#define FWUPCOMMON_H
#include <time.h>     /* for time_t */

#define MAX_GETCMD_LEN 40
#define MAX_USBDEVNAME_LEN 60
#define MAX_DIRNAME_LEN 80
#define MAX_DIRSTR_LEN 16
#define MAX_RBCMD_LEN 80

typedef enum reqID
{
  GET_FIRMWARE = 0,
  GET_FIRMWARE_UPDATEPLAN,
  GET_FIRMWARE_PACKAGE,
  GET_FIRMWARE_MANIFEST,
  GET_FIRMWARE_BINARY,
  GET_DEPLOYMENT,
  GET_LIVE_DEPLOYMENT,
  MAX_REQID
} RequestID;

typedef enum updateState
{
  UPDATE_NOT_CHECKED = 0,
  UPDATE_AVAILABLE,
  UPDATE_DOWNLOADED,
  UPDATE_VALID,
  UPDATE_APPLIED,
  UPDATE_SUCCESSFUL,
  UPDATE_ROLLEDBACK,
  MAX_UPDATE_STATES
} updateState;

/*
 * Additional states?
 * UPDATE_PLAN_DOWNLOADED
 * UPDATE_PACKAGE_DOWNLOADED
 * MANIFEST_DOWNLOADED
 * UPDATE_BINARY_DOWNLOADED
 */

typedef enum rollbackPolicy
{
  ROLLBACK_ALL = 0,
  ROLLBACK_AND_CONTINUE,
  CONTINUE,
  MAX_ROLLBACK_POLICIES
} rollbackPolicy;

typedef enum rebootPolicy
{
  REBOOT_NONE = 0,
  REBOOT_DEVICE,
  REBOOT_PACKAGE,
  REBOOT_GROUP,
  MAX_REBOOT_POLICIES
} rebootPolicy;

typedef enum manifestItemType
{
  MANIFEST_ITEM_FIRMWARE = 0,
  MANIFEST_ITEM_BOOTLOADER,
  MANIFEST_ITEM_CERTIFICATE,
  MANIFEST_ITEM_FILE,
  MANIFEST_ITEM_SCRIPT,
  MAX_MANIFEST_ITEM_TYPES
} manifestItemType;

typedef struct updateStatus
{
  updateState updateStatus;
  time_t updateTime;
} updateStatus;
updateStatus fwUpdateState;

#endif /* FWUPCOMMON_H */