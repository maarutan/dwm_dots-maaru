// keymap/variables.h

// Define values for window operations
#define MOVE_WINDOW_J_VALUE "0x 45y 0w 0h"
#define MOVE_WINDOW_K_VALUE "0x -45y 0w 0h"
#define MOVE_WINDOW_L_VALUE "45x 0y 0w 0h"
#define MOVE_WINDOW_H_VALUE "-45x 0y 0w 0h"

#define MOVE_RESIZE_J_VALUE "0x 0y 0w 45h"
#define MOVE_RESIZE_K_VALUE "0x 0y 0w -45h"
#define MOVE_RESIZE_L_VALUE "0x 0y 45w 0h"
#define MOVE_RESIZE_H_VALUE "0x 0y -45w 0h"

// Focus stack values
#define FOCUSSTACK_UP_VALUE +1
#define FOCUSSTACK_DOWN_VALUE -1

// Master factor values
#define MFACT_INCREASE_VALUE +0.05
#define MFACT_DECREASE_VALUE -0.05

// Stack move values
#define MOVE_STACK_UP_VALUE +1
#define MOVE_STACK_DOWN_VALUE -1

// Zoom
#define ZOOM_CMD_VALUE 0  // empty struct for zoom command

// Resize edge values
#define RESIZE_EDGE_T_VALUE "t"
#define RESIZE_EDGE_B_VALUE "b"
#define RESIZE_EDGE_L_VALUE "l"
#define RESIZE_EDGE_R_VALUE "r"

// Resize edge with SHIFT values
#define RESIZE_EDGE_T_SHIFT_VALUE "T"
#define RESIZE_EDGE_B_SHIFT_VALUE "B"
#define RESIZE_EDGE_L_SHIFT_VALUE "L"
#define RESIZE_EDGE_R_SHIFT_VALUE "R"

// Quit command value
#define QUIT_CMD_VALUE "pkill -f dwm"

// Define SHCMD commands
#define KILL_DWM_CMD SHCMD("pkill -f dwm")
#define ZOOM_CMD SHCMD("")  // Assuming zoom doesn't need additional command
