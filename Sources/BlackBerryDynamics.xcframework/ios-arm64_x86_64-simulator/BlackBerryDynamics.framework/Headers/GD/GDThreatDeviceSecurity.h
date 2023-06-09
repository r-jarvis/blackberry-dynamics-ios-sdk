/*
* (c) 2020 BlackBerry Limited. All rights reserved.
*
*/

#import <Foundation/Foundation.h>
#import <BlackBerryDynamics/GD/GDThreat.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Provide details of threats related to the device. A range of checks are performed to determine the security health of the users device. 
 * For example, if the user has jailbroken their device or if the iOS device integrity checks have failed.
 */
@interface BBDThreatDeviceSecurity : BBDThreat

/**
 * Creates an instance of BBDThreatDeviceSecurity.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
* Return whether the device has been compromised or is in an insecure state. 
*
* Return whether the device has been compromised or is in an insecure state. For example, if the device has been rooted or is connected to a debugger.
*/
- (BOOL)isDeviceCompromised;

/**
* Return the current risk level from evaluating the device integrity.  
*
* Return the level of risk posed by the current device state. If the device has been compromised a HIGH risk level will be returned.
*/
- (BBDThreatLevel) getCompromisedDeviceRisk;

/**
* Return whether app is running on an emulator.
*
* Return whether app is running on an emulator.
*/
- (BOOL)isRunningOnEmulator;

/**
* Return the current risk level related to the state of the emulator detection.
*
* Return the level of risk posed by the state of emulator detection. If emulator has been detected
* by the app this would be deemed a HIGH risk level.
*/
- (BBDThreatLevel)getRunningOnEmulatorRisk;

/**
* Return whether a screen lock is configured by the user.
*
* Return whether a screen lock (e.g. PIN) is enabled on the device.
*/
- (BOOL)isScreenLockEnabled;

/**
* Return the current risk level related to the state of the device screen lock.
*
* Return the level of risk posed by the state of the device screen lock. If no screen lock has been configured
* by the user this would be deemed a MEDIUM risk level.
*/
- (BBDThreatLevel)getScreenLockRisk;

/**
* Return the state of the iOS Device Integrity checks. 
*
* Return the state of the iOS Device Integrity checks. 
*/
- (BOOL)isDeviceAttestationFailed;

/**
* Return the current risk level related to the device integrity checks.
*
* Return the level of risk posed by the device attestation checks. If device attestation fails this could
* mean the boot loader is compromised and the security risk is level is HIGH.
*/
- (BBDThreatLevel) getDeviceAttestationRisk;

@end

NS_ASSUME_NONNULL_END
