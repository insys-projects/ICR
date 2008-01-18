//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: MSG_READ_FILE_CAPTION
//
// MessageText:
//
//  Select file to read Configuration
//
#define MSG_READ_FILE_CAPTION            0x00000001L

//
// MessageId: MSG_SAVE_FILE_CAPTION
//
// MessageText:
//
//  Select file to save Configuration
//
#define MSG_SAVE_FILE_CAPTION            0x00000002L

//
// MessageId: MSG_FILE_FILTER
//
// MessageText:
//
//  Binary Files (*.bin)|*.bin|All Files (*.*)|*.*||
//
#define MSG_FILE_FILTER                  0x00000003L

//
// MessageId: MSG_NOT_ENOUGH_MEMORY
//
// MessageText:
//
//  Not enough memory for configuration data !
//
#define MSG_NOT_ENOUGH_MEMORY            0xC0000004L

//
// MessageId: MSG_WARN_REWRITE_DATA
//
// MessageText:
//
//  Data of EPROM of device will rewrited!
//
#define MSG_WARN_REWRITE_DATA            0x80000005L

//
// MessageId: MSG_CONTINUE
//
// MessageText:
//
//  Continue?
//
#define MSG_CONTINUE                     0x80000006L

//
// MessageId: MSG_NON_ADM
//
// MessageText:
//
//  Non ADM-submodule
//
#define MSG_NON_ADM                      0x00000007L

//
// MessageId: MSG_FILE_FILTER_HEX
//
// MessageText:
//
//  Binary Files (*.hex)|*.hex|All Files (*.*)|*.*||
//
#define MSG_FILE_FILTER_HEX              0x00000008L

//
// MessageId: MSG_FILE_FILTER_BIN_AND_HEX
//
// MessageText:
//
//  Binary And Hex Files (*.bin;*.hex)|*.bin;*.hex|All Files (*.*)|*.*||
//
#define MSG_FILE_FILTER_BIN_AND_HEX      0x00000009L

