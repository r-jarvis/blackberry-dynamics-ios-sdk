/*
 * (c) 2018 BlackBerry Limited. All rights reserved.
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

/** Manage Push Channel tokens and notifications.
 * 
 * The Push Channel framework is a BlackBerry Dynamics feature used to
 * receive notifications from an application server.
 *
 * Note that the BlackBerry Dynamics Push Channel feature is not part of the
 * native iOS notification feature set.
 *
 * Use of the Push Channel feature in the application is dependent on:
 * - Completion of BlackBerry Dynamics authorization processing.
 * - Connection to the BlackBerry Dynamics infrastructure.
 * .
 *
 * Push Channel data communication doesn't go via the proxy specified in the
 * native settings of the device or computer on which the application is
 * running, if any.
 *
 * @see <a  HREF="https://docs.blackberry.com/en/endpoint-management/blackberry-uem/"  target="_blank" >Manuals page for the BlackBerry Dynamics enterprise servers</a > for the Platform Overview.
 * @see \ref threads
 * @see \ref background_execution
 * @see <a
 *     HREF="https://developer.apple.com/library/content/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/"
 *     target="_blank"
 * >Local and Remote Notification Programming Guide</a> on the apple.com
 * developer website.
 *
 * <h2>Push Channel Usage</h2>
 * Push Channels are established by the BlackBerry Dynamics application, then
 * used by the application server when needed. The sequence of events is as
 * follows.
 * -# The application sets an event handler for Push Channel notifications.
 * -# The application requests a Push Channel token from the BlackBerry Dynamics
 *    proxy infrastructure.
 * -# The application sends the token to its server using, for example, a socket
 *    connection or HTTP request.
 * -# The application can now wait for a Push Channel notification.\n\n
 * Later, when the server has data for the user, the following steps take
 * place:\n\n
 * -# The server sends a Push Channel notification message through the
 *    BlackBerry Dynamics proxy infrastructure. The message is addressed using
 *    the token.
 * -# The message is sent on, and the waiting application's event handler is
 *    invoked.\n\n
 * Later, when the server has more data for the user, the following steps
 * take place:\n\n
 * -# The server sends another Push Channel notification message through the
 *    proxy infrastructure. The message is addressed using the same token.
 * -# The message is sent on, and the waiting application's event handler is
 *    invoked again.
 * .
 * \image html "sq01 Push Channel.png" "Push Channel sequence diagram"\image rtf "sq01 Push Channel.png" "Push Channel sequence diagram"
 *
 * The BlackBerry Dynamics platform keeps data communications between the
 * application and server alive while the application is waiting for a Push
 * Channel notification. This is achieved by sending "heartbeat" messages at an
 * interval that is dynamically optimized for battery and network performance.
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
 * 
 * <h2>Programming Interface</h2>
 * The Push Channel programming interface is asynchronous and state-based. The
 * application code creates a Push Channel object for each channel it will use,
 * typically one per application server. When a channel changes state, or a
 * channel event occurs, the BlackBerry Dynamics runtime notifies the
 * application.
 * 
 * <h3>Notifications</h3>
 * To notify the application, the runtime posts an <tt>NSNotification</tt>.
 *
 * For all <tt>NSNotification</tt> instances that are Push Channel
 * notifications:
 * - The object will be the Push Channel object for the channel to which the
 *   notification relates.
 * - The name depends on the type of event or change that has occurred. It will
 *   be one of the following values.
 *   - \reflink GDPushChannel::GDPushChannelOpenedNotification GDPushChannelOpenedNotification \endlink.
 *   - \reflink GDPushChannel::GDPushChannelMessageNotification GDPushChannelMessageNotification \endlink.
 *   - \reflink GDPushChannel::GDPushChannelClosedNotification GDPushChannelClosedNotification \endlink.
 *   - \reflink GDPushChannel::GDPushChannelErrorNotification GDPushChannelErrorNotification \endlink.
 *   - \reflink GDPushChannel::GDPushChannelPingFailedNotification GDPushChannelPingFailedNotification \endlink.
 *   .
 * - The contents of the user information dictionary, <tt>userInfo</tt>, depends
 *   on the event type. The following values are used as keys.
 *   - \reflink GDPushChannel::GDPushChannelTokenKey GDPushChannelTokenKey \endlink.
 *   - \reflink GDPushChannel::GDPushChannelHostKey GDPushChannelHostKey \endlink.
 *   - \reflink GDPushChannel::GDPushChannelMessageKey GDPushChannelMessageKey \endlink.
 *   - \reflink GDPushChannel::GDPushChannelErrorKey GDPushChannelErrorKey \endlink.
 *   .
 * .
 * Push Channel state changes can also be detected by key-value observing (KVO)
 * of the \reflink GDPushChannel::state state \endlink property.
 * 
 * @see <a
      href="https://developer.apple.com/library/content/documentation/Cocoa/Conceptual/KeyValueObserving/KeyValueObserving.html"
      target="_blank"
 * >Key-Value Observing Programming Guide</a>
 *  on the apple.com developer website.
 * @see <a
      href="https://developer.apple.com/reference/foundation/nsnotificationcenter"
      target="_blank"
 * >NSNotificationCenter class reference</a>
 *  on the apple.com developer website.
 *
 * <h3>State cycle</h3>
 * The availability of functions in the Push Channel programming interface,
 * and what actions take place, are detailed below, and summarized in the
 * following table. The table also summarizes which notifications are expected
 * in each state.
 * <table>
 *     <tr>
 *          <th>State</th>
 *          <th class="th50percent">Functions and actions</th>
 *          <th class="th35percent">Expected notifications\n See \ref pushchannelconstants</th>
 *     </tr>
 *     <tr>
 *          <td>Prepared</td>
 *          <td>Application can call <tt>connect</tt>: state becomes Connecting</td>
 *          <td>None</td>
 *     </tr>
 *     <tr>
 *          <td>Connecting</td>
 *          <td>BlackBerry Dynamics runtime requests a new channel from the proxy infrastructure</td>
 *          <td>
 *              <tt>GDPushChannelErrorNotification</tt>: new state is Failed\n
 *              <tt>GDPushChannelOpenedNotification</tt>: new state is Open
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Open</td>
 *          <td> Application can call <tt>disconnect</tt>: state becomes Disconnecting</td>
 *          <td>
 *              <tt>GDPushChannelMessageNotification</tt>: no state change\n
 *              <tt>GDPushChannelPingFailedNotification</tt>: no state change\n
 *              <tt>GDPushChannelClosedNotification</tt>: new state is Disconnected</td>
 *      </tr>
 *      <tr>
 *          <td>Disconnecting</td>
 *          <td>BlackBerry Dynamics Runtime requests the proxy infrastructure to close the channel</td>
 *          <td>
 *              <tt>GDPushChannelMessageNotification</tt>: no state change\n
 *              <tt>GDPushChannelPingFailedNotification</tt>: no state change\n
 *              <tt>GDPushChannelClosedNotification</tt>: new state is Disconnected
 *          </td>
 *      </tr>
 *      <tr>
 *          <td>Disconnected</td>
 *          <td>Application can call <tt>connect</tt>: state becomes Connecting</td>
 *          <td>None</td>
 *      </tr>
 *      <tr>
 *          <td>Failed</td>
 *          <td>Application can call <tt>connect</tt>: state becomes Connecting</td>
 *          <td>None</td>
 *     </tr>
 * </table>


 * The transitions in the above table are also shown in this diagram.
 * \image html "st01 Push Channel.png" "Push Channel state transition diagram"\image rtf "st01 Push Channel.png" "Push Channel state transition diagram"
 * 
 * Note that an individual Push Channel might or might not
 * be closed when the overall Push Channel service becomes unavailable.
 *
 * @see \ref GNP
 * 
 * <h3>Notification feature differences</h3>
 * The capabilities of the BlackBerry Dynamics Push Channel are different to the
 * capabilities of the native Apple Push Notification Service (APNS) in the
 * following ways.
 *
 * Only native notifications can be received when the application is in
 * background. This might change in a future release of iOS.
 *
 * In principle, native notifications alert the user, not the application.
 * Having been alerted, the user may choose to open the application. BlackBerry
 * Dynamics Push Channel messages alert the application, which in turn may alert
 * the user.
 *
 * BlackBerry Dynamics Push Channel messages can include a "payload" of
 * application data from the server. The application data is conveyed by the
 * proxy infrastructure from the server to the application.
 * 
 * Native notifications may be received whenever the device has a connection to
 * APNS. BlackBerry Dynamics Push Channel messages may be received whenever the
 * application has a connection to the BlackBerry Dynamics infrastructure.
 *
 * <h2>Push Channel Identifiers</h2>
 * Every Push Channel must have an identifier. Identifiers must be unique within
 * an application. A Push Channel identifier is a text string set by the
 * application code. Note that Push Channel identifiers aren't the same as Push
 * Channel tokens. Token values are set by the BlackBerry Dynamics
 * infrastructure and runtime.
 *
 * The following convention represents best practice for Push Channel
 * identifiers.
 *
 * A Push Channel identifier should be composed of a <em>domain</em> followed by
 * a module <em>name</em> and an optional <em>purpose</em>. The parts are
 * separated by full stops (periods). The following examples illustrate the
 * convention.
 *
 * Example: <tt>com.example.mobile-life.email</tt>
 * - Domain is "com.example"
 * - Name is "mobile-life"
 * - Purpose is "email"
 * .
 *
 * Example: <tt>com.example.dashboard</tt>
 * - Domain is "com.example"
 * - Name is "dashboard"
 * - Purpose is omitted.
 * .
 *
 * The rules for identifier part values are as follows.
 * - Domain must be the reversal of an Internet domain that is owned by the
 *   developer organisation.
 * - Name must be unique within all the organisation's applications, libraries,
 *   and other code modules that might create a Push Channel. Ensuring
 *   uniqueness of name values is the responsibility of the developer
 *   organisation.
 * - Purpose need only be used in the case that a single application, library,
 *   or other code module uses more than one Push Channel. Ensuring uniqueness
 *   of purpose values is the responsibility of the code module's developer.
 * .
 *
 * <h2>Code Snippets</h2> The following code snippets illustrate some common tasks.
 * <h3>Open Push Channel</h3>
 * The following snippet shows a Push Channel being created and opened after
 * checking that the service is available.
 * \code
 * if ([GDReachability sharedInstance].isPushChannelAvailable) {
 *     NSLog( @"Push Channel service available");
 *     myChannel = [[GDPushChannel alloc] initWithIdentifier:@"com.example.dashboard"];
 *     myHandler = [[AppChannelHandler alloc] init]
 *     NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
 *     [notificationCenter addObserver:myHandler
 *                            selector:@selector(channelOpenedNotification:)
 *                                name:GDPushChannelOpenedNotification
 *                              object:myChannel];
 *
 *     [notificationCenter addObserver:myHandler
 *                            selector:@selector(channelClosedNotification:)
 *                                name:GDPushChannelClosedNotification
 *                              object:myChannel];
 *
 *     [notificationCenter addObserver:myHandler
 *                            selector:@selector(channelErrorNotification:)
 *                                name:GDPushChannelErrorNotification
 *                              object:myChannel];
 *
 *     [notificationCenter addObserver:myHandler
 *                            selector:@selector(channelPingFailedNotification:)
 *                                name:GDPushChannelPingFailedNotification
 *                              object:myChannel];
 *
 *     [notificationCenter addObserver:myHandler
 *                            selector:@selector(channelMessageReceivedNotification:)
 *                                name:GDPushChannelMessageNotification
 *                              object:myChannel];
 *     [myChannel connect];
 * }
 * \endcode
 * The above snippet shows the following taking place:
 * - Availability logged to the system monitor.
 * - Allocation of a Push Channel object.
 * - Allocation of an application Push Channel event handler.
 * - Registration of the new handler for all notifications from the channel.
 *   All notifications are sent to the same handler instance, but to different
 *   functions, specified as selectors.
 * - Attempt to connect the Push Channel.
 * .
 * 
 * The attempt is asynchronous. The associated
 * <tt>GDPushChannelOpenedNotification</tt>
 * notification would be received if and when the attempt is succesful (not
 * shown).
 *
 * <h3>Close Push Channel</h3>
 * \code
 * [myChannel disconnect];
 * \endcode
 * The above snippet shows: Request to disconnect the Push Channel.
 * 
 * The request is asynchronous. The associated
 * <tt>GDPushChannelClosedNotification</tt>
 * notification would be received when the closure is finalized (not shown).
 *
 * <h2>Code Snippets</h2> The following code snippets illustrate some common tasks.
 * <h3>Handle Push Channel Opening</h3>
 * The following snippet shows a simple handler for when a Push Channel opens.
 * \code
 * -(void)channelOpenedNotification:(NSNotification *)notification
 * {
 *     NSString *token = notification.userInfo[GDPushChannelTokenKey];
 *     NSLog(@"GDPushChannelOpenedNotification token: %@", token);
 *     NSString *host = notification.userInfo[GDPushChannelHostKey];
 *     if (host != nil) {
 *         NSLog(@"GDPushChannelOpenedNotification push channel host: %@", host);
 *         myApp.pushChannelHost = host;
 *     }
 *     myApp.pushIsOpen = YES;
 *     myApp.pushToken = token;
 *     [myApp sendPushToken];
 * }
 * \endcode
 * The above snippet shows the following taking place:
 * - The Push Channel token is extracted from the user information dictionary in
 *   the notification.
 * - The token is logged to the system monitor.
 * - The application flags internally that its channel is open, and stores the
 *   token value.
 * - The <tt>sendPushToken</tt> function in the application is called.
 * .
 *
 * The <tt>sendPushToken</tt> function, which would be written by the
 * application developer, would send the token to the application server. This
 * could use a socket, an HTTP request, or another means of communication. From
 * the Push Channel point of view, this is an out-of-band communication.
 *
 * The server will use the token to address Push Channel notification messages
 * back to the application. These would be received by the application's
 * Push Channel event handler code.
 *
 * <h3>Receive Push Channel Message</h3>
 * \code
 * - (void)channelMessageReceivedNotification:(NSNotification *)notification
 * {
 *     NSString *data = notification.userInfo[GDPushChannelMessageKey];
 *     NSLog(@"channelMessageReceivedNotification message: %@", data);
 *     [myApp processPush:data];
 * }
 * \endcode
 * The above snippet shows the following taking place when a Push Channel
 * message is received:
 * - The Push Channel message is extracted from the user information dictionary
 *   in the notification.
 * - The message is logged to the system monitor.
 * - The <tt>processPush</tt> function in the application is called and
 *   passed the content of the message.
 *
 * The <tt>processPush</tt> function, which would be written by the
 * application developer, could initiate any of the following actions:
 * - Alert the user that new data is available.
 * - Connect to the application server to retrieve the data. (Connection
 *   could use a socket, an HTTP request, or another means of communication.
 *   From the Push Channel point of view, this is an out-of-band communication.)
 * .
 *
 * <h3>Handle Channel Closure</h3>
 * \code
 * -(void)channelClosedNotification:(NSNotification *)notification
 * {
 *     NSString *data = notification.userInfo[GDPushChannelTokenKey];
 *     NSLog(@"GDPushChannelClosedNotification: %@", data);
 *     myApp.pushIsOpen = NO;
 *     [myApp discardPushToken:data];
 * }
 * \endcode
 * The above snippet shows a simple channel closure handler. The following takes
 * place when the Push Channel is closed:
 * - The token is logged to the system monitor.
 * - The application flags internally that its channel isn't open.
 * - The application <tt>discardPushToken</tt> function is called. The token
 *   of the closed channel is passed as a parameter.
 * .
 *
 * The <tt>discardPushToken</tt> function would delete the application's
 * copy of the token, possibly after checking that it matches the previous
 * stored token.
 * 
 * The function could also initiate connection of a new Push Channel, which
 * would have a new token. See \reflink GDPushChannel::connect connect \endlink.
 *
 * <h3>Handle Channel Error</h3>
 * \code
 * - (void)channelErrorNotification:(NSNotification *)notification
 * {
 *     NSInteger errorCode = [notification[GDPushChannelErrorKey] integerValue];
 *     NSLog(@"GDPushChannelErrorNotification: %zd", error);
 *     myApp.pushIsOpen = NO;
 *     myApp.pushErr = error;
 *     [myApp discardPushToken];
 * }
 * \endcode
 * The above snippet shows a simple <tt>Error</tt> handler.
 *
 * The handler logs the error code to the system monitor, flags
 * the channel's state as not connected, records the error code in
 * the application, then calls the application <tt>discardPushToken</tt>
 * function.
 *
 * The <tt>discardPushToken</tt> function could do any of the following:
 * - Delete the application's copy of the token.
 * - Set the error state in an ongoing status display.
 * - Depending on the error code, initiate connection of a new Push Channel,
 *   which would have a new token. See \reflink GDPushChannel::connect connect \endlink.
 *
 * See under Ping Failure in the \ref GNP for an explanation of the Ping Failure feature.
 *
 * <h3>Handle Ping Failure</h3>
 * \code
 * - (void)channelErrorNotification:(NSNotification *)notification
 * {
 *     NSInteger errorCode = [notification[GDPushChannelErrorKey] integerValue];
 *     NSLog(@"GDPushChannelPingFailedNotification %zd", error);
 *     if ( error == 605 ) {
 *         [myApp resendPushToken];
 *     }
 * }
 * \endcode
 * The above snippet shows a simple Ping Failure handler.
 *
 * The handler logs the error code to the system monitor, then calls the
 * application <tt>resendPushToken</tt> function if the token was lost.
 *
 * The <tt>resendPushToken</tt> function, which would be written by the
 * application developer, would send the application's stored token to the
 * application server. This could use a socket, an HTTP request, or another
 * means of communication. From the Push Channel point of view, this is an
 * out-of-band communication.
 *
 * The <tt>resendPushToken</tt> function should expect that the server is
 * not immediately available, perhaps employing a retry policy.
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
