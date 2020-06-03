/*
 * Controller_Memory_View module
 * 
 * Controller_Memory specific view.
 * Shows write/read modal dialog by blinking all green leds.
 * Long period blinking means that dialog is opened and waiting for user confirmation.
 * When user click save button one more time, to confirm and continue saving, leds will blink faster.
 */

/*
 * Displays saving confirmation dialog.
 * All 4-leds indicator will blink slowly.
 */
#define Controller_Memory_View_ShowSaveDialog() Controller_View_Dialog_Show()

/*
 * Cancels saving and cleans 4 leds display.
 */
#define Controller_Memory_View_HideSaveDialog() Controller_View_Dialog_Hide()

/*
 * Starts blinking faster, which means saving in progress.
 */
#define Controller_Memory_View_ShowSaveProgressDialog() Controller_View_Dialog_ShowConfirmation()

/*
 * Check if saving dialog active and 4 leds are blinking.
 */
#define Controller_Memory_View_isSaveDialogVisible()  Controller_View_Dialog_isVisible()




