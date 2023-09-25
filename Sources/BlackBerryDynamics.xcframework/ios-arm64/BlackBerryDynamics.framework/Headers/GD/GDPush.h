/*
 * Copyright 2023 BlackBerry Limited. All rights reserved.
 *
 */

#ifndef __GD_PUSH_H__
#define __GD_PUSH_H__

#import <Foundation/Foundation.h>

// See: http://clang.llvm.org/docs/LanguageExtensions.html
/* \cond DOXYGEN_IGNORE */
#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif
/* \endcond */

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_PUSH_CONNECT_DISCONNECT __attribute__((deprecated("No longer required")))
#   define DEPRECATE_GDPUSHCONNECTION __attribute__((deprecated("GDPushConnection interface has been deprecated")))
#   define DEPRECATE_GDPUSHCHANNELDELEGATE __attribute__((deprecated("GDPushChannelDelegate protocol has been deprecated, use notifications instead.")))
#else
#   define DEPRECATE_PUSH_CONNECT_DISCONNECT __attribute__((deprecated))
#   define DEPRECATE_GDPUSHCONNECTION __attribute__((deprecated))
#   define DEPRECATE_GDPUSHCHANNELDELEGATE __attribute__((deprecated))
#endif
/* \endcond */

NS_ASSUME_NONNULL_BEGIN

/**
 * \ingroup pushchannelconstants
 * 
 * \{
 */

/** Push Channel state.
 * 
 * Use these enumerated constants to check the state of a Push Channel. The
 * \reflink GDPushChannel::state state \endlink property always takes one of these values.
 */
typedef NS_ENUM(NSInteger, GDPushChannelState)
{
    /** \copydetails ssPushChannelStateNone
     */
    GDPushChannelStateNone = 0,
    
    /** \copydetails ssPushChannelStateOpen
     */
    GDPushChannelStateOpen,
    
    /** \copydetails ssPushChannelStateClosed
     */
    GDPushChannelStateClosed,
    
    /** \copydetails ssPushChannelStateError
     */
    GDPushChannelStateError
};

/** Push Channel opened notification name.
 *
 * After a call to \reflink GDPushChannel::connect connect \endlink by the application,
 * an <tt>NSNotification</tt> with this name is posted when the Push Channel
 * opens. The notification object will be the corresponding \reflink GDPushChannel GDPushChannel \endlink
 * instance. The notification will have a user information dictionary that
 * contains.
 * - The Push Channel token. Use \ref GDPushChannelTokenKey as the key to
 * access the token value.
 * - The Push Channel host name if applicable. Use \ref GDPushChannelHostKey as
 * the key to access the host name value.
 * 
 * The application code that handles the notification
 * must initiate sending of the Push Channel token to the application server,
 * out of band. The application server will then be able to use the token to
 * address Push Channel messages back to the application, via the BlackBerry
 * Dynamics proxy infrastructure. See the \ref GNP.
 *
 * After receiving this notification, the application
 * could receive any of the following for the same channel.
 * - \reflink GDPushChannel::GDPushChannelMessageNotification GDPushChannelMessageNotification \endlink.
 * - \reflink GDPushChannel::GDPushChannelClosedNotification GDPushChannelClosedNotification \endlink.
 * - \reflink GDPushChannel::GDPushChannelErrorNotification GDPushChannelErrorNotification \endlink.
 * - \reflink GDPushChannel::GDPushChannelPingFailedNotification GDPushChannelPingFailedNotification \endlink.
 * .
 *
 * The value of this constant is suitable to use as the name parameter to an
 * NSNotificationCenter addObserver call.
 */
extern NSString* const GDPushChannelOpenedNotification;

/** Push Channel closed notification name.
 *
 * 
 * An <tt>NSNotification</tt> with this name is posted when a Push Channel
 * closes. The notification object will be the corresponding
 * \reflink GDPushChannel GDPushChannel \endlink instance. The notification will have a user information
 * dictionary that contains the Push Channel token. Use \ref
 * GDPushChannelTokenKey as the key to access the token value.
 *
 * The Push Channel could have been closed by the remote end, or the application
 * could have called \reflink GDPushChannel::disconnect disconnect \endlink.
 * 
 * After receiving this notification:
 * - The associated Push Channel token cannot be used any more.
 * - No more messages will be received on this Push Channel.
 * .
 *
 * If the notification wasn't expected, the
 * application code that handles it could alert the user that Push Channel 
 * notifications will not be received, or cause this to be displayed as an 
 * ongoing state. The code could also initiate release of the Push Channel
 * object. Alternatively, reconnection could be initiated, see
 * \reflink GDPushChannel::connect connect \endlink.
 *
 * Note that this notification is only sent for
 * permanent Push Channel closure; not for transient losses of channel
 * communication. For example, this notification
 * wouldn't be sent in the case of an application on a mobile device that loses
 * packet data coverage or otherwise cannot connect to the BlackBerry Dynamics
 * proxy infrastructure. The status of the connection to the infrastructure can
 * be monitored by using the
 * \link GDReachability \endlink
 * programming interface.
 * 
 * The value of this constant is suitable to use as the name parameter to an
 * NSNotificationCenter addObserver call.
 */
extern NSString* const GDPushChannelClosedNotification;

/** Push Channel error notification name.
 *
 * 
 * An <tt>NSNotification</tt> with this name is posted when a permanent error
 * occurs on a Push Channel. The notification object will be the
 * \reflink GDPushChannel GDPushChannel \endlink instance corresponding to the channel on which the error
 * occurred. The notification will have a user information dictionary that
 * contains an error code. Use \ref GDPushChannelErrorKey as the key to access
 * the error.
 *
 * <table>
 *     <tr><th>Error code</th><th>Channel Error reason</th>
 *     </tr>
 *     <tr><td>
 *         0</td>
 *     <td>
 *         Push is not currently connected.</td>
 *    </tr>
 *    <tr><td>
 *         200-499</td>
 *     <td>
 *         Internal error.</td>
 *     </tr>
 *     <tr><td>
 *         500-599</td>
 *     <td>
 *         Internal server error.</td>
 *     </tr>
 * </table>
 * 
 * Receiving this notification warns the application
 * that the associated Push Channel token cannot be used any more, or that the
 * channel could not be connected in the first place. Furthermore, no (more)
 * Push Channel notifications will be received on this channel.
 *
 * The application code that handles the notification
 * could alert the user that Push Channel messages will not be received, or
 * cause this to be displayed as an ongoing state. The code should also initiate
 * reconnection, see \reflink GDPushChannel::connect connect \endlink, after checking that the Push
 * Channel service is available. Service availability can be checked by using
 * the
 * \link GDReachability \endlink
 * programming interface.
 *
 * The value of this constant is suitable to use as the name parameter to an
 * NSNotificationCenter addObserver call.
 */
extern NSString* const GDPushChannelErrorNotification;

/** Push Channel received message notification name.
 *
 * 
 * An <tt>NSNotification</tt> with this name is posted when a Push Channel
 * receives a message. The notification object will be the corresponding
 * \reflink GDPushChannel GDPushChannel \endlink instance. The notification will have a user information
 * dictionary that contains the message "payload". Use
 * \ref GDPushChannelMessageKey as the key to access the message.
 * 
 * The Push Channel message will have been sent by an application server, using
 * the Push Channel notify service. See the \ref GNP.
 *
 * The service supports a "payload" of data to be included in the message. The
 * data could be in any format chosen by the application developer. The payload
 * could also be empty.
 *
 * Note that a Push Channel message can be received at any time when the channel
 * is open. This includes the interval between the request for disconnection
 * (\reflink GDPushChannel::disconnect disconnect \endlink called) and channel disconnection being
 * finalized
 * (\reflink GDPushChannel::GDPushChannelClosedNotification GDPushChannelClosedNotification \endlink received).
 *
 * The application code that handles the notification
 * could initiate the following actions, for example.
 * - Alert the user that new data is available.
 * - Connect to the application server to retrieve the data.
 * .
 *
 * \note
 * Because of this notification, the application code does not need to maintain a
 * constant connection with the server. This is an important benefit of using
 * the BlackBerry Dynamics Push Channel framework.
 * 
 * The value of this constant is suitable to use as the name parameter to an
 * NSNotificationCenter addObserver call.
 */
extern NSString* const GDPushChannelMessageNotification;

/** Push Channel ping failed on server notification name.
 *
 * 
 * An <tt>NSNotification</tt> with this name is posted when a Push Channel Ping
 * Failure occurs. The notification object will be the \reflink GDPushChannel GDPushChannel \endlink
 * instance corresponding to the channel on which the ping failure occurred. The
 * notification will have a user information dictionary that contains a ping
 * failure reason code. Use \ref GDPushChannelErrorKey as the key to access the
 * code.
 *
 * <table><tr><th>Reason code</th><th>Failure</th>
 *     </tr>
 *     <tr><td>
 *         600</td>
 *     <td>
 *         Application server address could not be resolved by the domain name
 *         service (DNS).</td>
 *     </tr>
 *     <tr><td>
 *         601</td>
 *     <td>
 *         Could not connect to application server address.</td>
 *     </tr>
 *    <tr><td>
 *         602</td>
 *     <td>
 *         Application server electronic certificate for Secure Socket Layer or
 *         Transport Layer Security (SSL/TLS) connection is invalid.</td>
 *     </tr>
 *    <tr><td>
 *         603</td>
 *     <td>
 *         Timed out waiting for application server HTTP response.</td>
 *     </tr>
 *     <tr><td>
 *         604</td>
 *     <td>
 *         Application server returned an invalid response.</td>
 *     </tr>
 *     <tr><td>
 *         605</td>
 *     <td>
 *         Application server indicated that the token has been lost.</td>
 *     </tr>
 * </table>
 * 
 * The application code that handles the notification
 * should initiate resending of the Push Channel token to the application
 * server, if the token has been lost. Loss of token is indicated by reason code
 * 605, see above. This is similar to the processing when the channel is
 * initially opened, see
 * \reflink GDPushChannel::GDPushChannelOpenedNotification GDPushChannelOpenedNotification \endlink.
 * If the application server is able to accept the token, then Push Channel
 * notification can resume.
 *
 * Note that ping failure can occur at any time when the channel is open. This
 * includes the interval between the request for disconnection
 * (\reflink GDPushChannel::disconnect disconnect \endlink called) and channel disconnection being
 * finalized
 * (\reflink GDPushChannel::GDPushChannelClosedNotification GDPushChannelClosedNotification \endlink received).
 *
 * <h2>Ping Failure</h2>
 * Ping Failure is an optional feature of the Push Channel framework. The
 * application server can register a ping address after receiving the Push
 * Channel token from the mobile application.
 *
 * If the application server registers a ping address, then it will be
 * periodically checked ("pinged") by the BlackBerry Dynamics Network Operation
 * Center (NOC). If the server does not respond to a ping, then the NOC notifies
 * the application that requested the corresponding Push Channel.
 * 
 * The purpose of this feature is to support servers that lose the Push Channel
 * token when they are restarted.
 *
 * See the \ref GNP for details of Ping Failure registration.
 */
extern NSString* const GDPushChannelPingFailedNotification;

/** Key for the Push Channel token, in a notification user information
 *  dictionary.
 *
 * Use this constant to access the Push Channel token in a notification. The
 * token will be in the posted <tt>NSNotification</tt> instance, in the user
 * information dictionary, with this value as its key. It will be an
 * <tt>NSString</tt>.
 *
 * Example of usage:
 * \code
 * NSString *token = nsNotification.userInfo[GDPushChannelTokenKey];
 * \endcode
 *
 * The key will be present if the <tt>NSNotification</tt> has one of the
 * following values as its <tt>name</tt>.
 * - \reflink GDPushChannel::GDPushChannelOpenedNotification GDPushChannelOpenedNotification \endlink.
 * - \reflink GDPushChannel::GDPushChannelClosedNotification GDPushChannelClosedNotification \endlink.
 * .
 */
extern NSString* const GDPushChannelTokenKey;

/** Key for the Push Channel host name, in a notification user information
 *  dictionary.
 *
 * Use this constant to get the host name of the push notification service in a notification. The
 * address will be in the posted <tt>NSNotification</tt> instance, in the user
 * information dictionary, with this value as its key. It will be an
 * <tt>NSString</tt>.
 *
 * Example of usage:
 * \code
 * NSString *pushServiceHostName = nsNotification.userInfo[GDPushChannelHostKey];
 * \endcode
 *
 * The key will be present if the <tt>NSNotification</tt> has the <tt>name</tt>:
 * \reflink GDPushChannel::GDPushChannelOpenedNotification GDPushChannelOpenedNotification \endlink.
 */
extern NSString* const GDPushChannelHostKey;

/** Key for the message data, in a Push Channel notification user information
 *  dictionary.
 *
 * Use this constant to access the message data in a Push Channel notification.
 * The message will be in the posted <tt>NSNotification</tt> instance, in the
 * user information dictionary, with this value as its key. It will be an
 * <tt>NSString</tt>.
 *
 * Example of usage:
 * \code
 * NSString *message = nsNotification.userInfo[GDPushChannelMessageKey];
 * \endcode
 * 
 * The key will be present if the <tt>NSNotification</tt> has the <tt>name</tt>:
 * \reflink GDPushChannel::GDPushChannelMessageNotification GDPushChannelMessageNotification \endlink.
 */
extern NSString* const GDPushChannelMessageKey;

/** Key for the error code, in a Push Channel notification user information
 *  dictionary.
 *
 * Use this constant to access the error code in a Push Channel notification. The
 * code will be in the posted <tt>NSNotification</tt> instance, in the user
 * information dictionary, with this value as its key. It will be an
 * <tt>NSInteger</tt> value.
 *
 * Example of usage:
 * \code
 * NSInteger code = [nsNotification.userInfo[GDPushChannelErrorKey] integerValue];
 * \endcode
 *
 * The key will be present if the <tt>NSNotification</tt> has one of the
 * following values as its <tt>name</tt>.
 * - \reflink GDPushChannel::GDPushChannelErrorNotification GDPushChannelErrorNotification \endlink.
 * - \reflink GDPushChannel::GDPushChannelPingFailedNotification GDPushChannelPingFailedNotification \endlink.
 * .
 */
extern NSString* const GDPushChannelErrorKey;

/** \}
 */

/*!
 * \class GDPushChannel GDPush.h <BlackBerryDynamics/GD/GDPush.h>
 * \brief Manage Push Channel tokens and notifications.
 * 
 * \copydetails ssPushChannel
 */
@interface GDPushChannel : NSObject {
    @private
    void* m_pushChannelInternal;
}

/** Push Channel state.
 *
 * The BlackBerry Dynamics runtime sets this property to one of the
 * GDPushChannelState values to represent the state of the channel.
 * 
 * This property is compatible with key-value observing (KVO).
 */
@property (nonatomic, readonly) GDPushChannelState state;


/** Constructor that prepares a new Push Channel.
 *
 * Call this function to construct a new Push Channel object. This
 * function does not initiate data communication.
 * See \reflink GDPushChannel::connect connect \endlink.
 *
 * @param pushChannelIdentifier <tt>NSString</tt> containing the identifier for this
 *                              Push Channel, see under Push Channel
 *                              Identifiers, above.
 * @throws_GDauth
 */
- (instancetype)initWithIdentifier:(NSString*)pushChannelIdentifier;

/** Connect Push Channel.
 * 
 * Call this function to open the Push Channel connection. This
 * function can only be called when the channel isn't open.
 *
 * This function causes a request for a Push Channel to be sent to the
 * BlackBerry Dynamics Network Operation Center (NOC). The NOC will create the
 * channel, and issue a Push Channel token, which can then be used to identify
 * the channel.
 *
 * The connection attempt is asynchronous.
 * An <tt>NSNotification</tt> with a user information dictionary,
 * <tt>userInfo</tt>, will be posted to notify the application of the result. If
 * the attempt succeeds, the notification name will be
 * <tt>GDPushChannelOpenedNotification</tt>, and the <tt>userInfo</tt> will
 * contain a <tt>GDPushChannelTokenKey</tt> entry of <tt>NSString</tt> type with
 * the token as its value and if applicable a <tt>GDPushChannelHostKey</tt> entry of
 * <tt>NSString</tt> type with push service host name. If the attempt fails,
 * the notification name will be <tt>GDPushChannelErrorNotification</tt>, and
 * the <tt>userInfo</tt> will contain a <tt>GDPushChannelErrorKey</tt> entry holding
 * an <tt>NSInteger</tt> value.
 *
 * @throws_GDauth
 */
- (void)connect;

/** Disconnect Push Channel.
 * 
 * Call this function to initiate permanent disconnection of the
 * Push Channel. This function can only be called when the channel is open.
 *
 * This function causes a request for Push Channel termination to be sent to
 * the BlackBerry Dynamics Network Operation Center (NOC). The NOC will delete
 * the channel, and invalidate the Push Channel token that was issued when the
 * channel was initially opened, see \reflink GDPushChannel::connect connect \endlink.
 *
 * Disconnection is asynchronous. When disconnection is complete,
 * an <tt>NSNotification</tt> is posted to notify the application. The
 * notification name will be <tt>GDPushChannelClosedNotification</tt>.
 * 
 * Note. This function is for permanent closure of the channel. Transient
 * suspension of Push Channel notifications may be more easily accomplished
 * out-of-band, by direct communication with the application server.
 *
 * If the connection with the NOC is open and operating, and the application
 * server that was sent the token registered for <tt>isDisconnected</tt>, then a
 * disconnect notification will be sent to the application server, by the NOC.
 * See the \ref GNP.
 * 
 * @throws_GDauth
 */
- (void)disconnect;

@end

NS_ASSUME_NONNULL_END

#endif /* __GD_PUSH_H__ */
