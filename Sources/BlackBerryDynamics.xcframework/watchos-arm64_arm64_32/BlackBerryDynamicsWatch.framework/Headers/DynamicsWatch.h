//
//  DynamicsWatch.h
//  DynamicsWatch
//
//  Created by Kari Ohlsen on 9/15/22.
//  Copyright © 2022 BlackBerry Limited. All rights reserved.

#import <Foundation/Foundation.h>

/** Not allowed by enterprise policy
 * 
 * The enterprise policy does not permit the use of a wearable device.
 */

extern NSInteger const WatchMessageErrorPolicyNotAllowed;

/** Communication needs to be secured. 
 * 
 * The communication between watch and companion app has not been secured. You must first use <tt>secureCommunicationSession</tt>.
 */

extern NSInteger const WatchMessageErrorNeedsCommunicationSecured;
/** Communication has failed.
 *
 * The communication failed because the container is locked.
 */

extern NSInteger const WatchMessageErrorRemoteLocked;
 
/** Not allowed by enterprise policy
 *
 * The enterprise compliance policy has been violated
 */

extern NSInteger const WatchMessageErrorIncompliant;

/** Communication has failed.
 *
 * An unknown error has occurred while trying to secure communication.
 */

extern NSInteger const WatchMessageErrorOther;

/** Error domain for watch message error
 * 
 * The error domain 'com.blackberry.dynamics.watch' is used to report messaging errors.
 */
extern NSString const *WatchMessageErrorDomain;

/** Error key for watch message error
 * 
 * The possible messaging errors are returned in a Dictionary entry using the error key.
 */
extern NSString const *WatchMessageErrorKey;

/** Error User Info key for watch message error
 *
 * User info for the possible messaging errors are returned in a Dictionary entry using the userInfo key.
 */
extern NSString const *WatchMessageErrorUserInfoKey;


/** Watch Communication State Info key for watch
 *
 * Watch Communication State is returned in a Dictionary entry using the WatchCommunicationStateKey key.
 */
extern NSString const *WatchCommunicationStateKey;


/**
 * 
 * @brief BlackBerry Dynamics WatchOS interface to support secure messaging between WatchOS and iOS applications.
 * 
 * This class enables secure communication from a Dynamics app running on WatchOS with a companion Dynamics app running on iOS. 
 * 
 * <h3>Introduction</h3>
 *
 * Use this class from a watchOS app to initiate secure authentication and communication with an iOS companion app. This interface
 * is not required within the iOS app. Instead the companion app should be built with BlackBerry Dynamics and utilize Apple's 
 * WCSession API to perform messaging with the watch.
 * 
 * Prerequisites:
 * - The watchOS app and iOS companion app must be integrated with BlackBerry Dynamics v12.1 or later.
 * - The Apple watch must be paired with the same user's iPhone.
 * - Enterprise policy must permit the use of a wearable device.
 * - The watch must be unlocked and worn on the wrist. 
 * 
 * <h3>Setting Up Secure Communications</h3>
 *
 * Setup and pairing of the watch and companion app is done using <tt>secureCommunicationSession</tt> within the WatchOS app. When successful, the 
 * completion block <tt>authStatus</tt> will be \ss_true and the WatchCommunicationState changed to <tt>WatchCommunicationReady</tt>. The other 
 * states and transitions are shown in the following diagram. 
 * 
 * \uimage{st06 WatchCommunicationState.png,Diagram of watchCommunicationState for BlackBerry Dynamics WatchOS application}
 *
 * <h4>Behavior On Companion App</h4>
 * It is best practice to first negotiate a secure communication session from the WatchOS app. This is because <tt>secureCommunicationSession</tt> is not available on 
 * the iOS companion app. If a WCSession <tt>sendMessage</tt> or <tt>sendMessageData</tt> is sent from the companion app prior to negotiation of the secure communication session 
 * then this will trigger the negotiation of the keys and the user will be required to confirm the 6 digit code on both devices. In this case the initiating message will 
 * need to be resent. Other APIs which initiate communication from the companion app to the watch are not currently handled in the same way, for example,  
 * <tt>transferFile</tt>, <tt>transferUserInfo</tt>, <tt>transferCurrentComplicationUserInfo</tt> and <tt>updateApplicationContext</tt>. Therefore use of these APIs without a 
 * <tt>secureCommunicationSession</tt> may fail.
 * 
 * <h3>Monitoring Watch Communication State</h3>
 *  The WatchCommunicationState can be monitored by subscribing to the Notification for the key WatchCommunicationStateKey
 *
 * @code
 * NotificationCenter.default.addObserver(self, selector: #selector(watchCommStateChanged(_: )), name: NSNotification.Name(rawValue: WatchCommunicationStateKey), object: nil)
 * @endcode
 *
 * The notification can be processed per this example code:
 *
 * @code
 * @objc func watchCommStateChanged(_ notification:Notification?) {
 *   guard let notif = notification else {
 *   //No notification
 *       return
 *   }
 *   if let watchCommState = WatchCommunicationState(rawValue: notif.userInfo?[WatchCommunicationStateKey] as! Int) {
 *      updateWatchCommString(state:watchCommState)
 *   }
 *}
 * * @endcode
 *
* <h3>Sending Messages</h3>
 *
 * Once secure communication is setup, use Apple's WCSession object to handle sending and receive messages between the 
 * watchOS and iOS companion app. An example using the 'sendMessage' function and associated 'replyHandler' can be found in the 
 * Dynamics WatchMessenger sample app (see below).
 * 
 * <h3>Handling Messaging Errors</h3>
 *
 * If an error is encountered when sending a message, the replies from the <tt>replyHandler</tt> in WCSessionDelegate session(_:didReceiveMessageData:) 
 * will be in the form of:
 * 
 * @code
 * @{WatchMessageErrorKey:[NSError errorWithDomain:WatchMessageErrorDomain
 *                                            code:WatchMessageErrorNeedsCommunicationSecured 
 *                                        userInfo:@{WatchMessageErrorUserInfoKey:@"Waiting to establish trust."}]}
 * @endcode
 * 
 * The error code in the <tt>NSError</tt> object indicates what the reason is for the error.
 *
 * Possible errors are:
 * - \ref WatchMessageErrorPolicyNotAllowed
 * - \ref WatchMessageErrorRemoteLocked
 * - \ref WatchMessageErrorIncompliant
 * - \ref WatchMessageErrorNeedsCommunicationSecured
 * - \ref WatchMessageErrorOther
 *
 * <h3>Secure File System</h3>
 *
 * The secure file system is part of the BlackBerry Dynamics Watch Secure Storage feature.
 
 * For applications, the BlackBerry Dynamics secure file system behaves like the default file system, with the following differences.
 * All data within the secure file system is stored on the device in an encrypted form.
 * Directory and file names are also encrypted.
 * The secure file system cannot be accessed until the Watch Communication is secured, see  <h3>Setting Up Secure Communications</h3> .
 *
 * Use GDFileManager instead of NSFileManager in the Watch app to access the Secure File System.
 *
 * For more info see <a href="https://developer.blackberry.com/files/blackberry-dynamics/ios/interface_g_d_file_manager.html">GDFileManager</a>
 *
 * <h3>Sample Application</h3>
 * 
 * Get started using the WatchOS and iOS sample app called 'WatchMessenger' located on BlackBerry's GitHub.
 * 
 * See 
 * <a href="https://github.com/blackberry/BlackBerry-Dynamics-iOS-Samples" target="_blank">BlackBerry Dynamics iOS Samples</a>.
 */
@interface DynamicsWatch : NSObject

/** Constants for WatchCommunicationState type.
 * 
 * This enumeration represents the state of the communication channel between watch and companion app.
 */

typedef NS_ENUM(NSInteger, WatchCommunicationState) {
    /** The secure communication between watch and iOS application has not been started. This is the initial state.*/
     WatchCommunicationStateNotSet,
    /** The secure communication between watch and iOS companion application is being reset. This state is 
     * triggered by calling \ref resetTrustBetweenDevices or if an encrypted message is received that cannot 
     * be decrypted with the currently provisioned encryption keys.*/
     WatchCommunicationResetting,
     /** The secure communication between watch and iOS companion application is authenticated and ready for use.*/
     WatchCommunicationReady,
    /** A validation code has been sent to the phone which the user needs to confirm. */
     WatchCommunicationNeedsConfirmOnPhone,
    /** A validation code has been received on the watch which the user needs to confirm.*/
    WatchCommunicationNeedsConfirmOnWatch, 
    /** The watch must be worn by the user and secured with a passcode to enable communication.*/
     WatchCommunicationNeedsWristDetected,
    /** The companion app must be launched on iPhone to establish a connection.*/
     WatchCommunicationNeedsFirstLaunch,
    /** Securing of the communication channel was cancelled by the user or a validation code was rejected.*/
     WatchCommunicationSecuringFailed,
    /** Communication failed because the enterprise policy does not permit use of a wearable device.*/
     WatchCommunicationNotAllowedByPolicy,
    /** Communication failed because the companion app is remote locked.*/
     WatchCommunicationNotAllowedRemoteLocked,
    /** Communication failed because the devices are incompliant with Device policies.*/
     WatchCommunicationNotAllowedIncompliant,
};

/** Conditional block indicating if authentication between the watch and companion app is successful.
 *
 * @return <tt>boolean</tt> indicating if the communication has been secured. 
 * 
 * \ss_true indicates communication is secured between the watch and companion app. When the result is \ss_true \ref watchCommunicationState 
 * will also be set to \ref WatchCommunicationReady.
 */
typedef void(^authCompletionBlock)(BOOL);

/** Get a reference to the BBDWatchIOS interface object. 
 * 
 * Communication must be started by initializing sharedBBDWatchIOS prior to sending or receiving secure messages.
 * If the watch receives a secured message prior to this initialization it will not be decrypted.
 * 
 * This function returns a reference to the Dynamics Watch object. It can be called in the <tt>session(_:activationDidCompleteWith:error:)</tt>  
 * handler of the watch application.
 *
 * @return Reference that can be used to call, for example <tt>secureCommunicationSession</tt>.
 */
+ (instancetype)sharedBBDWatchIOS;

/** Setup Secure Communication
 *
 * Communication must be secured by running this method prior to sending and receiving messages with the watch.
 * Authentication status is available in the authStatus callback.
 * 
 * If a companion app is unavailable the watch displays an alert indicating that the companion app cannot be reached.
 * 
 * The enterprise policy assigned to the user must permit the use of a wearable device. If it is disabled the watch displays an alert 
 * indicating that the policy is disabled and the organization administrator should be contacted.
 */
-(void)secureCommunicationSession:(authCompletionBlock)authStatus;

/** Watch Communication States
 *
 * See enumeration \ref WatchCommunicationState
 */ 
-(WatchCommunicationState)watchCommunicationState;

/** Reset the connection between watch and companion app.
 * 
 * Invoke this API to reset trust between watch and companion app. This action will wipe all contents from the Dynamics watch app 
 * and initiate the setup of a new trust negotiation.
 */
-(void)resetTrustBetweenDevices;

@end
