//
//  DynamicsWatch.h
//  DynamicsWatch
//
//  Created by Kari Ohlsen on 9/15/22.
//  Copyright © 2022 BlackBerry Limited. All rights reserved.

#import <Foundation/Foundation.h>

@interface DynamicsWatch : NSObject


typedef enum{
    WatchCommunicationStateNotSet,
    WatchCommunicationReady,
    WatchCommunicationNeedsTrust,
    WatchCommunicationNeedsWristDetected,
    WatchCommunicationNeedsFirstLaunch
}WatchCommunicationState;

typedef enum{
    WatchMessageErrorNone,
    WatchMessageErrorPolicyNotAllowed,
    WatchMessageErrorNeedsCommunicationSecured,
    WatchMessageErrorOther,
}WatchMessageError;

typedef void(^authCompletionBlock)(BOOL);

+ (instancetype)sharedBBDWatchIOS;

/** BlackBerry Dynamics Watch Communication
 *
 * Communication must be secured by running this method prior to sending messages to the watch.
 * This method checks for availability and reachability of a companion app in addition to determining
 * whether the Wearable Policy is enabled. Authentication status is available in the authStatus callback.
 * If companion app is unavailable the Watch displays an alert indicating that the companion app cannot be reached.
 * If Wearable Policy is disabled Watch displays an alert indicating that the Policy is disabled and IT Admin should be contacted.
 */
-(void)secureCommunicationSession:(authCompletionBlock)authStatus;

/** BlackBerry Dynamics Watch Errors
 *
 * If an error is encountered in sending a message, the replies from replyHandler will include information indicating
 * what the reason is for the error. These replies can be processed through this lookup function to determine the reason.
 * Possible states are:
 *      WatchMessageErrorNone,
 *      WatchMessageErrorPolicyNotAllowed,
 *      WatchMessageErrorNeedsCommunicationSecured,
 *      WatchMessageErrorOther
 */
-(WatchMessageError)errorTypeForReply:(NSDictionary *)reply;

/** BlackBerry Dynamics Watch Communication States
 *
 * The state of the communication channel between Watch and Companion app:
 *      WatchCommunicationStateNotSet - initial value
 *      WatchCommunicationReady - communication between the Watch app and Companion app has been secured is ready
 *      WatchCommunicationNeedsTrust - Validation code confirmation is required on Watch.
 *      WatchCommunicationNeedsWristDetected - Watch must be worn by user and secured with passcode to enable communication.
 *      WatchCommunicationNeedsFirstLaunch - Companion app must be launched on iPhone to establish connection.
*/
-(WatchCommunicationState)watchCommunicationState;

@end
