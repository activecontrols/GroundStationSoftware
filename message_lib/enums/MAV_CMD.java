/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This class was automatically generated by the
 * java mavlink generator tool. It should not be modified by hand.
 */

package com.MAVLink.enums;

/**
 * Commands to be executed by the MAV. They can be executed on user request, or as part of a mission script. If the action is used in a mission, the parameter mapping to the waypoint/mission message is as follows: Param 1, Param 2, Param 3, Param 4, X: Param 5, Y:Param 6, Z:Param 7. This command list is similar what ARINC 424 is for commercial aircraft: A data format how to interpret waypoint/mission data. NaN and INT32_MAX may be used in float/integer params (respectively) to indicate optional/default values (e.g. to use the component's current yaw or latitude rather than a specific value). See https://mavlink.io/en/guide/xml_schema.html#MAV_CMD for information about the structure of the MAV_CMD entries. NOTE: not all common commands are supported, and sometimes only subsets of e.g. mission protocol are implemented. Not all messages behave the same as in common.
 */
public class MAV_CMD {
   public static final int MAV_CMD_NAV_LAND = 21; /* Land at current location. |Minimum target altitude if landing is aborted (0 = undefined/use system default).| (IGNORED) Precision land mode.| Empty.| Desired yaw angle. NaN to use the current system yaw heading mode (e.g. yaw towards next waypoint, yaw to home, etc.).| (IGNORED) Latitude.| (IGNORED) Longitude.| Landing altitude (ground level in current frame).|  */
   public static final int MAV_CMD_DO_PAUSE_CONTINUE = 193; /* Hold the current position or continue. |0: Pause current mission or reposition command, hold current position. 1: Continue mission. On pause, enter hover mode.| Reserved| Reserved| Reserved| Reserved| Reserved| Reserved|  */
   public static final int MAV_CMD_DO_SET_MISSION_CURRENT = 224; /* 
          Start the trajectory segment specified by Number. Note that this should also be used for RTL, since ASTRA does not support RTL.
         |Mission sequence value to set. -1 for the current mission item (use to reset mission without changing current mission item).| (CURRENTLY IGNORED) Resets mission. 1: true, 0: false. Resets jump counters to initial values and changes mission state "completed" to be "active" or "paused".| Empty| Empty| Empty| Empty| Empty|  */
   public static final int MAV_CMD_MISSION_START = 300; /* start running a mission |first_item: the first mission item to run| last_item:  the last mission item to run (after this item is run, the vehicle lands in place)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   public static final int MAV_CMD_MISSION_LOAD_SD = 51801; /* Load a trajectory mission from the SD card (/missions/mission{number}.atf) into PSRAM. |the mission number to load| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   public static final int MAV_CMD_ENUM_END = 51802; /*  | */
}
            