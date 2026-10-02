// PROFILE: game
// Jumbo file for the SMS code (see zCareer.cpp for what jumbo files are; the name is ours).
//
// Why these belong together: SendOutrunVictoryOrDefeatSms (529BD0) keeps the number of SMS
// definitions in a register across calls to IsMessageAlreadyReceived (514CB0) but reloads it after
// SendMessage: the compiler had already compiled 514CB0 and knew it doesn't change that global.
#include "sms/00514CB0_SmsMessageList_IsMessageAlreadyReceived.cpp"
#include "sms/00529BD0_SmsMessageList_SendOutrunVictoryOrDefeatSms.cpp"
