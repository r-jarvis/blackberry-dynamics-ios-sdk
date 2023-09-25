/*
 * (c) 2023 BlackBerry Limited. All rights reserved.
 *
 */

#ifndef __GD_IOS_H__
#define __GD_IOS_H__

#import <UIKit/UIKit.h>
#import <BlackBerryDynamics/GD/GDAppResultCode.h>
#import <BlackBerryDynamics/GD/GDAppConfig.h>
#import <BlackBerryDynamics/GD/GDVersion.h>

/* \cond DOXYGEN_IGNORE */
// See: http://clang.llvm.org/docs/LanguageExtensions.html
#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif
/* \endcond */

@class GDServiceProvider, GDVersion, GDState;


/** Constants for BlackBerry Dynamics service type.
 *
 * This enumeration represents the type of service for which a service discovery
 * query is being issued. The <tt>serviceType</tt> parameter of the
 * \reflink GDiOS::getServiceProvidersFor:andVersion:andServiceType: getServiceProvidersFor: (GDiOS) \endlink function always takes one of these values.
 */
typedef NS_ENUM(NSInteger, GDServiceType)
{
    /** Application-based service. */
    GDServiceTypeApplication=0,
    /** Server-based service. */
    GDServiceTypeServer,
};


NS_ASSUME_NONNULL_BEGIN

/*!
 * \class GDAuthDelegateInfo GDiOS.h <BlackBerryDynamics/GD/GDiOS.h>
 * \brief Provide information about the authentication delegate app, if one exists.
 *
 * This class is used to return information about the application 
 * authentication is delegated to. If there is no such delegated application, 
 * isAuthenticationDelegated will be \ss_false.
 * See \ref GDiOS::getAuthDelegate
 */
@interface GDAuthDelegateInfo : NSObject

/** Name of the auth delegate application.
 * 
 * Display name of the auth delegate app.
 *
 * This property contains displayed name of the auth delegate app registered in the Dynamics catalog.
 * This string may be empty but is not null.
*/
@property (nonatomic, copy) NSString* name;

/** Native application identifier of the auth delegate.
 * 
 * Native application identifier of the auth delegate app.
 *
 * This property contains the native application identifier of the auth delegate as in the catalog.
 * This string may be empty but is not null.
 */
@property (nonatomic, copy) NSString* address;

/** Entitlement identifier of the auth delegate.
 * 
 * Entitlement identifier of the auth delegate app.
 *
 * This property contains the entitlement identifier registered in the Dynamics catalog.
 * This string may be empty but is not null.
 */
@property (nonatomic, copy) NSString* applicationId;

/** Flag if authentication is delegated.
 * 
 * Indicate if authentication is delegated to another app.
 *
 * @return <tt>YES</tt> if the app is delegating authentication to another app.
 * @return <tt>NO</tt> if the app is managing authentication.

 */
@property (nonatomic, assign) BOOL isAuthenticationDelegated;

/** Description of the GDAuthDelegateInfo
 *
 * This method returns an NSString representing the values of GDAuthDelegateInfo
 */
- (NSString *)description;

@end

/*!
 * \class GDAppEvent GDiOS.h <BlackBerryDynamics/GD/GDiOS.h>
 * \brief Event dispatched from the BlackBerry Dynamics runtime.
 * 
 * This class is used to deliver events to the \ss_runtime_link event handler
 * in the application. See \ref GDiOSDelegate.
 */
@interface GDAppEvent : NSObject
{
   
    NSString* message;

    GDAppResultCode code;

    GDAppEventType type;
}

/** Textual description of the event.
 * 
 * This property contains a textual description of the event. The text is
 * suitable for display to the end user, at least for reporting diagnostic
 * information for support purposes.
 */
@property (nonatomic, copy) NSString* message;

/** Numeric result code.
 * 
 * This property contains a numeric result code.
 * For success events, the <tt>GDErrorNone</tt> code is used. Other values in
 * the \ref GDAppEvent.code enumeration are used for errors.
 */
@property (nonatomic, assign) GDAppResultCode code;
/* error code 0, means success */

/** Numeric event type.
 * 
 * This property contains a numeric type code. To determine the type of event
 * being notified, compare this property's value to the constants in the \ref
 * GDAppEvent.type enumeration.
 */
@property (nonatomic, assign) GDAppEventType type;

@end


/*!
 * \protocol GDiOSDelegate GDiOS.h <BlackBerryDynamics/GD/GDiOS.h>
 * \brief Handler for events dispatched from the BlackBerry Dynamics Runtime, including authorization events.
 * 
 * Errors and state changes that occur when using \ss_runtime_link can be
 * handled by creating a class that implements this protocol.
 *
 * @see \ref GDState for an alternative interface.
 */
@protocol GDiOSDelegate
@optional

/** Callback for all events.
 * 
 * The callback is invoked whenever a BlackBerry Dynamics runtime object event
 * occurs. Runtime object events include authorization results, see
 * \reflink GDiOS::authorize: authorize (GDiOS) \endlink for details.
 *
 * @param anEvent GDAppEvent populated with details of the event.
 */
- (void)handleEvent:(GDAppEvent*)anEvent;

@end

/*!
 * \class GDiOS GDiOS.h <BlackBerryDynamic/GD/GDiOS.h>
 * \brief BlackBerry Dynamics Runtime object interface, including authorization.
 *
 * \copydetails ssGDRunTime
 * 
 * \snippets_intro
 * \snippet{Authorization}
 * The following snippet shows initiation of BlackBerry Dynamics authorization.
 * \code
 * [GDiOS sharedInstance].delegate = self;
 * [[GDiOS sharedInstance] authorize];
 * \endcode
 * After executing the above code, the application would wait for its delegate
 * callback to be invoked. The invocation would have an event type of
 * <tt>GDAppEventAuthorized</tt> if the user was authorized. After that, the
 * application could make full use of all BlackBerry Dynamics capabilities.
 *
 * The above code relies on the identification parameters being in the
 * Info.plist file, as shown in the following snippet.
 * \code
 * <key>GDApplicationID</key>
 * <string>com.example.browser</string>
 * <key>GDApplicationVersion</key>
 * <string>1.0.0.0</string>
 * \endcode
 * The above is an extract from the XML of the application's Info.plist file.
 * The extract sets "com.example.browser" as the BlackBerry Dynamics entitlement
 * identifer, and "1.0.0.0" as the BlackBerry Dynamics entitlement version.
 *
 * \snippet{User interface pre-initialization}
 * The following snippet shows some necessary steps that precede initialization
 * of the application's user interface. The recommended place in the code for
 * these steps is as shown in the snippet.
 * \code
 *
 * - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 * { 
 *     GDiOS *gdiOS = [GDiOS sharedInstance];
 *     gdiOS.delegate = self;
 *     started = NO;
 *     // Following line will cause the BlackBerry Dynamics user interface to open.
 *     [gdiOS authorize];
 *     return YES;
 * }
 * \endcode
 *
 * The above snippet shows the following sequence of actions.
 * -# A reference to the GDiOS singleton object is obtained.
 * -# The current class is set as the delegated event handler.
 * -# The <tt>started</tt> flag is set, to control initialization of the
 *    application's user interface, which is covered in the following snippet.
 *    The flag's declaration (not shown) would be <tt>BOOL</tt>.
 * -# The application initiates BlackBerry Dynamics authorization.
 * .
 * Authorization processing is asynchronous. On completion, an event will be
 * dispatched to the application's handler. The application completes user
 * interface initialization within its event handler, as shown in the following
 * code snippet.
 *
 * \snippet{User interface initialization}
 * The following snippet shows the recommended place in the code to initialize
 * the application's user interface.
 * \code
 *
 * -(void)handleEvent:(GDAppEvent*)anEvent
 * {
 *     switch (anEvent.type) {
 *         case GDAppEventAuthorized: {
 *             if (!started) {
 *                 [self initializeUI];
 *                 started = YES;
 *             }
 *             break;
 *         }
 *
 *         case GDAppEventNotAuthorized: {
 *             [self onNotAuthorized:anEvent];
 *             break;
 *         }
 *
 *         case GDAppEventRemoteSettingsUpdate:
 *         case GDAppEventServicesUpdate:
 *         case GDAppEventPolicyUpdate:
 *         default: {
 *             // This application ignores other types of event.
 *             break;
 *         }
 *     }
 * }
 * \endcode
 * The above code shows a simple BlackBerry Dynamics runtime event handler.
 *
 * The handler calls the application's own <tt>initializeUI</tt> function when a
 * <tt>GDAppEventAuthorized</tt> event is received for the first time. The
 * application's <tt>started</tt> flag is used to control first-time execution.
 * Initialization of this flag is shown in the previous snippet.\n
 * The <tt>initializeUI</tt> function would complete user interface
 * initialization, utilizing a reference to the BlackBerry Dynamics runtime
 * <tt>UIWindow</tt>. This reference can be obtained using the <tt>window</tt>
 * property from the main app delegate.
 *
 * The handler calls the application's own <tt>onNotAuthorized</tt> function
 * whenever a <tt>GDAppEventNotAuthorized</tt> event is received.
 */
@interface GDiOS : NSObject

/** Get a reference to the runtime interface object.
 * 
 * This function returns a reference to the BlackBerry Dynamics
 * runtime object.
 * This function can be called in the
 * <tt>application:didFinishLaunchingWithOptions:</tt>  
 * handler of the application.
 *
 * The BlackBerry Dynamics runtime object is a "singleton class".
 *
 * @return Reference that can be used to call, for example,\reflink GDiOS::authorize: authorize (GDiOS) \endlink.
 */
+ (instancetype)sharedInstance;

/** Connect to the BlackBerry Dynamics infrastructure.
 * 
 * Call this function to initiate BlackBerry Dynamics authorization
 * processing.
 *
 * 
 * Authorization involves a number of exchanges with various servers in the
 * BlackBerry Dynamics proxy infrastructure, and may involve user interaction.
 * The following processing items are the most significant.<dl>
 *
 * <dt>Infrastructure activation</dt><dd>
 * The BlackBerry Dynamics runtime registers the application instance as a
 * terminal with the BlackBerry Dynamics Network Operation Center (NOC). The NOC
 * issues registration credentials, which are encrypted and stored locally by
 * the runtime. Infrastructure activation is not processed if registration
 * credentials are already present.</dd>
 *
 * <dt>Enterprise activation</dt><dd>
 * Enterprise activation is the completion of the enterprise provisioning
 * process. An access key will have been created by the enterprise management
 * console, and made available to the runtime instance embedded in the
 * application. See under Activation, above, for the methods by which the key
 * can be made available.
 *
 * During enterprise activation, the runtime sends the key to the NOC. If the
 * key is recognized, the application instance is associated with the enterprise
 * that created the key. Enterprise registration credentials are then issued,
 * and encrypted and stored locally by the runtime.\n
 * Enterprise activation is not processed if enterprise registration
 * credentials are already present.\n
 * Note that successful enterprise activation has the effect of consuming the
 * access key. This will be the case even if a later stage of authorization
 * processing fails, or if it is found that the user isn't entitled to this
 * application.</dd>
 *
 * <dt>Entitlement checking</dt><dd>
 * The enterprise that provisioned the end user can later withdraw the
 * user's entitlement to the application. Withdrawal is flagged in the
 * enterprise's management console. The runtime checks the end user's ongoing
 * entitlement to the application every time authorization is processed. (In
 * addition, withdrawal may be notified to the runtime by the NOC.)\n
 * In the management console, entitlement is given to particular versions of
 * particular applications. The entitlement version and identifier values built
 * into the application must match exactly with a version and identifier to
 * which the user has been given entitlement in the management console. If there
 * isn't an exact match, then user entitlement is assumed to have been
 * withdrawn.\n
 * If the user is found not to be entitled, then the runtime deletes all locally
 * stored application data and authentication credentials.</dd>
 *
 * <dt>Policy update</dt><dd>
 * Policies govern many aspects of the BlackBerry Dynamics user experience. For
 * example, the minimum characteristics of the end user's security password with
 * respect to length and types of character are governed by a policy. So is the
 * need for the end user to set a security password. The runtime checks for and
 * retrieves updated policies every time authorization is processed.</dd>
 *
 * <dt>Policy checking</dt><dd>
 * The runtime checks for compliance with the most up-to-date policies every
 * time authorization is processed.</dd>
 *
 * <dt>Configuration retrieval</dt><dd>
 * The runtime retrieves a set of application configuration settings from the
 * enterprise management console during authorization processing. These will
 * have been stored in the management console. See under
 * \reflink GDiOS::getApplicationConfig getApplicationConfig (GDiOS) \endlink for a list of settings.</dd>
 *
 * <dt>Unlock secure store</dt><dd>
 * The BlackBerry Dynamics secure store is unlocked during authorization. If the
 * store is protected by an end-user password, then the user must enter their
 * password for authorization processing to complete. Password entry takes place
 * in a BlackBerry Dynamics user interface, not in the application user
 * interface.</dd>
 * </dl>
 * Note that BlackBerry Dynamics user interfaces mentioned in the above, such as
 * Enterprise activation and Password entry, are opened and closed as needed,
 * without reference to the application.
 *
 * This function can be called in the
 * <tt>application:didFinishLaunchingWithOptions:</tt> 
 * handler of the application.
 *
 * This function must be called before any of the principal BlackBerry
 * Dynamics functions.
 *
 * Data communication during authorization processing doesn't go via the proxy
 * specified in the device's native settings, if any.
 *
 * @param delegate Reference to the delegated event handler, typically
 *                 <tt>self</tt>.
 *
 * Application identification parameters will be read from the following properties
 * in the application Info.plist fi<tt></tt>le:<table>
 *     <tr><th>Key</th><th>Type</th><th>Value</th>
 *     </tr><tr><td>
 *         <tt>GDApplicationID</tt></td>
 *         <td><tt>String</tt></td>
 *         <td>BlackBerry Dynamics entitlement identifier.\n
 *         (This identifier was previously referred to as the Good Dynamics
 *         application identifier, or in the abbreviated form GD App ID.)\n
 *         This identifier is used to control access to the application by end
 *         users, and to configure its application server connections. The value
 *         passed must be the same as the value present in the enterprise
 *         management console.\n
 *         (Note that the value needn't be the same as the native application
 *         identifier.)\n
 *         For syntax details see under Entitlement Identifier Format,
 *         above.</td>
 *     </tr><tr><td>
 *         <tt>GDApplicationVersion</tt></td>
 *         <td><tt>String</tt></td>
 *         <td>BlackBerry Dynamics entitlement version number\n The version
 *         number can be combined with the entitlement identifier, above, to
 *         control access to particular versions of the application.</td>
 *     </tr>
 * </table>
 * (In case there are multiple Info.plist files, check that the correct one has
 * been edited by opening the Info tab of the application target being built.
 * The settings should appear there.)
 * 
 * Authorization is asynchronous. When authorization processing completes:
 * - The delegate \link GDiOSDelegate::handleEvent: handleEvent\endlink callback
 *   is invoked.
 * - The \ref GDState singleton object is updated, and any observers of that
 *   object are sent notifications.
 * .
 *
 * @see \ref GC
 * @see \ref enterprisesimulation.
 */
- (void)authorize:(id<GDiOSDelegate> _Nonnull)delegate;

/** Connect to the BlackBerry Dynamics infrastructure, without specifying a
 *  delegate.
 * 
 * Call this function to initiate BlackBerry Dynamics authorization
 * processing without specifying a delegated event handler. This style of call
 * can be used in the following cases.
 * - The <tt>delegate</tt> property has already been set directly, to a
 *   GDiOSDelegate implementation.
 * - The application uses the \ref GDState interface to monitor authorization
 *   state, doesn't implement <tt>GDiOSD</tt><tt>elegate</tt>, and has switched
 *   off the event receiver check. (Instructions for switching off are on the
 *   \ref BuildTimeConfiguration page, under the Event Receiver Check heading.)
 * .
 * 
 * Calling this function is otherwise equivalent to calling the
 * <tt>authorize:</tt> function, above. See \reflink GDiOS::authorize: authorize (GDiOS) \endlink for details.
 */
- (void)authorize;

/** Connect to the BlackBerry Dynamics infrastructure in background.
 *
 * Call this function to initiate BlackBerry Dynamics authorization
 * processing in background.
 *
 * This function should be called when the application is launched in
 * background. This could happen if any of the following are in use.
 * - Apple Push Notification Service (APNS).
 * - Background fetch.
 * .
 *
 * Authorization processing can complete in background, if all the following
 * conditions are met:
 * - Activation has completed. The application must have run in foreground and
 *   completed BlackBerry Dynamics authorization processing at least once for
 *   this to be the case.
 * - Authorization can complete autonomously, without user interaction, i.e. a
 *   <em>no-password</em> enterprise policy is in effect for the current end
 *   user.
 * - The application is currently in background.
 * .
 * 
 * Call this function from any callback that handles background launch, for
 * example the application <tt>didReceiveRemoteNotification:</tt> or
 * <tt>performFetchWithCompletionHandler:</tt> function. Access the
 * \reflink GDiOS::canAuthorizeAutonomously canAuthorizeAutonomously (GDiOS) \endlink property first, to check that a
 * no-password policy applies to the current end user and that autonomous
 * authorization is possible.
 * 
 * If authorization can complete autonomously, calling this function
 * results in the same processing and notification as if \reflink GDiOS::authorize: authorize (GDiOS) \endlink had
 * been called. Application identification parameters will be read from the
 * Info.plist file.
 *
 * @param delegate Reference to the delegated event handler, typically
 *                 <tt>self</tt>.
 *        
 * @return <tt>YES</tt> if authorization can complete autonomously. The application
 *         will be notified when authorization completes, or if it fails for
 *         some reason.
 * @return <tt>NO</tt> if authorization cannot complete autonomously. No further
 *         notification will be dispatched.
 */
- (BOOL)authorizeAutonomously:(id<GDiOSDelegate> _Nonnull)delegate;

/** Connect to the BlackBerry Dynamics infrastructure in background, without
 *  specifying a delegate.
 * 
 * Call this function to initiate autonomous BlackBerry Dynamics
 * authorization processing without specifying a delegated event handler. This
 * style of call can be used in the same cases as the
 * \reflink GDiOS::authorize authorize (GDiOS) \endlink function that takes no parameters, see above.
 * 
 * Calling this function is otherwise equivalent to calling the
 * <tt>authorizeAutonomously:</tt> function, above.
 * 
 * See \reflink GDiOS::authorizeAutonomously: authorizeAutonomously: (GDiOS) \endlink for details.
 */
- (BOOL)authorizeAutonomously;

/** Get a pointer to the GDAuthDelegateInfo structure. 
 * 
 * Get a pointer to the GDAuthDelegateInfo structure. Non-Null.
 * If there is no auth delegate application, isAuthenticationDelegated within structure will be NO.
 */
- (GDAuthDelegateInfo*)getAuthDelegate;

/** String constants used as keys for programmatic activation parameters.
 *Keys used to set the values of the activation parameters required during programmatic activation.
 *
 * <table>
 *     <tr>
 *         <th>Key Constant</th>
 *         <th>Setting</th>
 *         <th>Type</th>
 *     </tr>
 *     <tr>
 *         <td>
 *            <tt>ActivationParameterUserIdentifier</tt>
 *         </td>
 *         <td>
 *             <tt>NSString</tt> containing the first enterprise activation
 *               credential: the user identifier. This is typically the
 *               enterprise email address of the end user.
 *         </td>
 *         <td>
 *             <tt>NSString</tt>
 *         </td>
 *     </tr>
 *     <tr>
 *         <td>
 *             <tt>ActivationParameterAccessKey</tt>
 *         </td>
 *         <td>
 *             <tt>NSString</tt> containing the second enterprise activation credential: the access key. Using an Access Key instead of Activation Password is recommend.
 *         </td>
 *         <td><tt>NSString</tt></td>
 *     </tr>
 *      *     <tr>
 *         <td>
 *             <tt>ActivationParameterPassword</tt>
 *         </td>
 *         <td>
 *             <tt>NSString</tt> containing the activation password in the case an Access Key cannot be obtained. For example the activation email contains a QR code.
 *         </td>
 *         <td><tt>NSString</tt></td>
 *     </tr>
 *     <tr>
 *         <td>
 *             <tt>ActivationParameterNOCAddress</tt>
 *         </td>
 *         <td>
 *             <tt>NSURL</tt> containing
 *                   a NOC server address, or an alias. The URL must always
 *                   include a scheme, such as <tt>https</tt>.
 *         </td>
 *         <td><tt>NSURL</tt></td>
 *     </tr>
 *     <tr>
 *         <td>
 *             <tt>ActivationParameterShowUserInterface</tt>
 *         </td>
 *         <td>
 *             <tt>Boolean</tt> value which if set to <tt>false</tt>, will prevent the BlackBerry Dynamics runtime activation UI from being shown during activation.</td>
 *         </td>
 *         <td><tt>NSNumber</tt></td>
 *     </tr>
 * </table>
 * \link GDiOS::programmaticAuthorize: \endlink
 */
typedef NSString *ActivationParameter;
extern ActivationParameter const ActivationParameterUserIdentifier;
extern ActivationParameter const ActivationParameterAccessKey;
extern ActivationParameter const ActivationParameterNOCAddress;
extern ActivationParameter const ActivationParameterShowUserInterface;
extern ActivationParameter const ActivationParameterEnrollmentAddress;
extern ActivationParameter const ActivationParameterPassword;

/** Initiate programmatic activation.
 *
 * Call this function to 
 * initiate programmatic activation.
 * Programmatic activation can only be utilized by applications that can obtain
 * credentials for enterprise activation on behalf of the end user. The
 * credentials are passed as parameters to this function. The credentials
 * must already have been generated, by an enterprise BlackBerry Dynamics
 * management console, prior to this function being called.
 *
 * Activation requires processing on the BlackBerry Dynamics Network Operation
 * Center (NOC). From an architectural point-of-view, there is a single NOC for
 * all BlackBerry Dynamics enterprises and users. For practical reasons,
 * however, there may actually be a number of NOC deployments. For example,
 * there may be separate production and development deployments. The application
 * can specify which NOC is to process programmatic activation, in the
 * <tt>nocAddress</tt> parameter to this function.
 *
 * Calling this function also initiates authorization processing, as if the
 * \reflink GDiOS::authorize: authorize (GDiOS) \endlink function had
 * been called.
 *
 * Only call this function after checking that the application is not
 * already activated, by
 * accessing the \reflink GDiOS::activationComplete activationComplete (GDiOS) \endlink property.
 *
 * @param activationParameters <tt>NSDictionary</tt>
 *         object containing configuration values. Use the
 *         <tt>ActivationParameter</tt> string constants as keys.
 */
- (void)programmaticAuthorize:(NSDictionary<ActivationParameter, id> *)activationParameters;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_PROGRAMMATICAUTHORIZE __attribute((deprecated("Use -programmaticAuthorize:activationParameters instead.")))
#else
#   define DEPRECATE_PROGRAMMATICAUTHORIZE __attribute((deprecated))
#endif
/* \endcond */

/** Initiate programmatic activation (deprecated).
 *
 * \deprecated This function is deprecated and will be removed in a future
 * release. Use
 * \link GDiOS::programmaticAuthorize: \endlink
 * instead.
 *
 * Calling this function is equivalent to calling the
 * form with an additional URL parameter, see below, and specifying the URL of
 * the default production Network Operation Center.
 */
- (void)programmaticAuthorize:(NSString *)userID  withAccessKey:(NSString *)accessKey DEPRECATE_PROGRAMMATICAUTHORIZE;

/** Initiate programmatic activation by a specific Network Operation Center (deprecated).
 *
 * \deprecated This function is deprecated and will be removed in a future
 * release. Use
 * \link GDiOS::programmaticAuthorize: \endlink
 * instead.
 *
 * Call this function to 
 * initiate programmatic activation.
 * Programmatic activation can only be utilized by applications that can obtain
 * credentials for enterprise activation on behalf of the end user. The
 * credentials are passed as parameters to this function. The credentials
 * must already have been generated, by an enterprise BlackBerry Dynamics
 * management console, prior to this function being called.
 *
 * Activation requires processing on the BlackBerry Dynamics Network Operation
 * Center (NOC). From an architectural point-of-view, there is a single NOC for
 * all BlackBerry Dynamics enterprises and users. For practical reasons,
 * however, there may actually be a number of NOC deployments. For example,
 * there may be separate production and development deployments. The application
 * can specify which NOC is to process programmatic activation, in the
 * <tt>nocAddress</tt> parameter to this function.
 *
 * Calling this function also initiates authorization processing, as if the
 * \reflink GDiOS::authorize: authorize (GDiOS) \endlink function had
 * been called.
 *
 * Only call this function after checking that the application is not
 * already activated, by
 * accessing the \reflink GDiOS::activationComplete activationComplete (GDiOS) \endlink property.
 *
 * @param userID <tt>NSString</tt> containing the first enterprise activation
 *               credential: the user identifier. This is typically the
 *               enterprise email address of the end user.
 *               
 * @param accessKey <tt>NSString</tt> containing the second enterprise activation
 *                  credential: the access key.
 *                  
 * @param nocAddress <tt>NSURL</tt> containing
 *                   a NOC server address, or an alias. The URL must always
 *                   include a scheme, such as <tt>https</tt>.
 */
- (void)programmaticAuthorize:(NSString *)userID
                withAccessKey:(NSString *)accessKey
       networkOperationCenter:(NSURL *)nocAddress DEPRECATE_PROGRAMMATICAUTHORIZE;

#undef DEPRECATE_PROGRAMMATICAUTHORIZE

/** Application activation status.
 *
 * Read the value of this property, using the <tt>isActivated</tt> accessor, to
 * check whether the application has already been activated. It is necessary to
 * check whether the application has been activated before initiating
 * programmatic activation.
 *
 * This property has the value:
 * - <tt>YES</tt> if the application has been activated.
 * - <tt>NO</tt> otherwise.
 * .
 */
@property (nonatomic, assign, readonly, getter=isActivated) BOOL activationComplete;

/** Get application configuration and other settings from the enterprise.
 * 
 * This function returns a collection of application configuration
 * and other settings. The settings will have been made in the enterprise
 * management console, and retrieved by the BlackBerry Dynamics runtime.
 *
 * Retrieval of configuration settings may happen during authorization
 * processing, or whenever settings are changed. When changed settings have been
 * retrieved by the runtime, a <tt>GDAppEventRemoteSettingsUpdate</tt> event
 * will be dispatched to the application. See the \reflink GDAppEvent GDAppEvent \endlink
 * class reference for details, and see the notes under the Enterprise
 * Configuration Information heading, above.
 *
 * Note that retrieval isn't as such triggered by calling this function.
 *
 * @return <tt>NSDictionary</tt>
 *         object containing configuration values. Use the
 *         <tt>GDAppConfigKey</tt> constant strings as keys.
 *         
 * Any of the following configuration settings may be present.
 * <table>
 *     <tr>
 *         <th>Key Constant</th>
 *         <th>Setting</th>
 *         <th>Type</th>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyServers</tt></td>
 *     <td>
 *         Application server configuration.\n
 *         A number of servers can be configured for an application, in the
 *         management console.\n
 *         See the \link GDAppServer
 *         GDAppServer class reference\endlink for documentation of the details
 *         that are returned for each configured server.
 * </td><td>
 *         <tt>NSArray</tt> of
 *         <tt>GDAppServer</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyConfig</tt></td>
 *     <td>
 *         Application-specific configuration data.\n
 *         As well as the application server details, above, a free
 *         text can also be entered in the management console. Whatever was
 *         entered is passed through by the runtime and made available to the
 *         application code here.</td>
 *     <td><tt>NSString</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyPreventDataLeakageOut</tt></td>
 *     <td>
 *         Outbound Data Leakage policy indicator.\n
 *         1 means that enterprise security
 *         policies require that the end user must be prevented from taking any
 *         action that is classified as data loss or data leakage in the
 *         BlackBerry Dynamics Security Compliance Requirements document.\n
 *         0 means that the above policy isn't
 *         in effect, so the user is permitted to take those actions.</td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyPreventDataLeakageIn</tt></td>
 *     <td>
 *         Inbound Data Leakage policy indicator.\n
 *         1 means that enterprise security
 *         policies require that the end user must be prevented from copying
 *         into the application data that originates from elsewhere than another
 *         BlackBerry Dynamics application activated by the same end user on the
 *         same device or computer.\n
 *         0 means that the above policy isn't
 *         in effect, so the user is permitted to copy in data from any other
 *         application.</td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyPreventDictation</tt></td>
 *     <td>
 *         Dictation Prevention policy indicator.\n
 *         1 means that enterprise security
 *         policies require that the end user must be prevented from using
 *         dictation as a form of input.\n
 *         0 means that the above policy isn't
 *         in effect, so the user is permitted to use dictation.\n
 *         This setting is included for completeness. The policy is generally
 *         enforced by the BlackBerry Dynamics runtime without reference to the
 *         application code.</td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr>  *     </tr> <tr><td>
 *         <tt>GDAppConfigKeyPreventScreenRecording</tt></td>
 *     <td>
 *         Screen Recording policy indicator.\n
 *         1 means that enterprise security
 *         policies require that the end user must be prevented from recording or sharing their screen.\n
 *         0 means that the above policy isn't
 *         in effect, so the user is permitted to record or share their screen.\n
 *         This setting is included for completeness. The policy is generally
 *         enforced by the BlackBerry Dynamics runtime without reference to the
 *         application code.</td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *    
 *     </tr> <tr><td>
 *         <tt>GDAppConfigKeyPreventCustomKeyboards</tt></td>
 *     <td>
 *         Custom Keyboard Prevention policy indicator.\n
 *         1 means that enterprise security policies require that the end
 *         user must be prevented from using custom keyboards.\n
 *         0 means that the above policy isn't in effect, so the user is
 *         permitted to use custom keyboards.\n
 *         This setting is included for completeness. The policy is generally
 *         enforced by the BlackBerry Dynamics runtime without reference to the
 *         application code.</td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr> <tr><td>
 *         <tt>GDAppConfigKeyDetailedLogsOn</tt></td>
 *     <td>
 *         Logging level.\n
 *         0 means that the logging level is
 *         low, and only minimal logs should be written.\n
 *         1 means that the logging level is
 *         high, and detailed logs should be written. Detailed logs facilitate
 *         debugging of issues encountered at run time.\n
 *         The BlackBerry Dynamics runtime will automatically adjust its logging
 *         according to the configured setting. The setting is present in the
 *         programming interface so that the application can adjust its logging
 *         consistently with the runtime.</td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr><tr>
 *         <td><tt>GDAppConfigKeyPreventUserDetailedLogs</tt></td>
 *     <td>
 *         User detailed logging block indicator.\n
 *         1 if the end user is blocked from
 *         switching on detailed logging, 0
 *         otherwise.\n
 *         Use this configuration key to determine whether to offer the end user
 *         an option to switch on detailed logging. Only offer the end user an
 *         option to switch on detailed logging if it isn't blocked by policy.\n
 *         See GDLogManager for
 *         how to switch on detailed logging from the application code.
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyUserId</tt></td>
 *     <td>
 *         Enterprise user identifier, typically email address.\n
 *         An enterprise identifier for the end user is one of the credentials
 *         required for activation of BlackBerry Dynamics application. This
 *         could be the email address entered in the activation user interface
 *         when the application was run for the first time, for example.\n
 *         The value obtained for this setting will initially be the enterprise
 *         email address, or other identifier, used for activation. If the
 *         enterprise email address of the end user changes after activation
 *         then the value of this setting will also change, next time it is
 *         obtained.</td>
 *     <td><tt>NSString</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyUserPrincipalName</tt></td>
 *     <td>
 *         User Principal Name.\n
 *         The User Principal Name (UPN) will have been retrieved from the
 *         enterprise Active Directory (AD) service by the enterprise management
 *         console, and then sent to the runtime, initially at activation time.
 *         This value will only be present if the current end user corresponds
 *         to an AD entry. The value may or may not be the same as the
 *         <tt>GDAppConfigKeyUserId</tt> value, depending on enterprise domain
 *         configuration.\n
 *         The value will be in
 *         <tt><em>username</em>\@<em>fully.qualified.domain.name</em></tt>
 *         format.\n
 *         If the UPN of the end user changes after activation then the value of
 *         this setting will also change, next time it is obtained.</td>
 *     <td><tt>NSString</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyInstanceIdentifier</tt></td>
 *     <td>
 *         Application instance identifier.\n
 *         The BlackBerry Dynamics runtime generates a unique identifier for the
 *         installed application when it is activated. This identifier doesn't
 *         change during upgrade of the application. It can be matched with a
 *         value on the management console, for tracking and analysis.\n
 *         This identifier will be different:
 *         - For the same application installed on different devices, even if
 *           installed for the same end user in the same deployment.
 *         - For different applications installed on the same device.
 *         - If the application is uninstalled and reinstalled.
 *         .
 *         The identifier will change value if the end user is migrated from one
 *         management console instance to another. See also the
 *         \link GDState::GDContainerMigrationPendingNotification
 *         GDContainerMigrationPendingNotification\endlink migration pending
 *         NSNotification name
 *         reference documentation.
 *         </td>
 *     <td><tt>NSString</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyCommunicationProtocols</tt></td>
 *     <td>
 *         Communication protocols allowed by the enterprise.\n
 *         A list of allowed and disallowed communication protocols can be set
 *         in the enterprise management console. The runtime will have retrieved
 *         the list, initially at activation time.\n
 *         The list is represented as
 *         an <tt>NSDictionary</tt>
 *          collection with the following keys:
 *         - \reflink GDiOS::GDProtocolsKeyTLSv1_0 GDProtocolsKeyTLSv1_0 (GDiOS) \endlink
 *         - \reflink GDiOS::GDProtocolsKeyTLSv1_1 GDProtocolsKeyTLSv1_1 (GDiOS) \endlink
 *         - \reflink GDiOS::GDProtocolsKeyTLSv1_2 GDProtocolsKeyTLSv1_2 (GDiOS) \endlink
 *         .
 *         The value in the collection for a particular key will be <tt>YES</tt> if
 *         the corresponding protocol is allowed, and <tt>NO</tt> otherwise.\n
 *         Some earlier versions of the management console software don't
 *         support this feature, and don't provide a list of allowed and
 *         disallowed protocols to the runtime. In that case, this element will
 *         be <tt>nil</tt> instead of a collection.</td>
 *     <td>
 *       <tt>NSDictionary</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyProtectedByPassword</tt></td>
 *     <td>
 *         BlackBerry Dynamics password enforcement.\n
 *         1 if a password or other interactive
 *         authentication is enforced by BlackBerry Dynamics,
 *         0 otherwise.\n
 *         See \reflink GDiOS::canAuthorizeAutonomously canAuthorizeAutonomously (GDiOS) \endlink for discussion.
 * </td>
 *     <td>
 *         <tt>NSNumber</tt></td>
 *
 *     </tr><tr><td>
 *         <tt>GDAppConfigKeyExtraInfo</tt></td>
 *     <td>
 *         Extra information sent by the management console.\n
 *         The management console can send extra information that isn't required
 *         for the operation of the BlackBerry Dynamics runtime but which might
 *         be of use to the application. For example, one or more additional
 *         identifiers for the end user could be included as extra
 *         information. The values will be encapsulated in a single JavaScript
 *         Object Notation (JSON) string.\n
 *         Some earlier versions of the management console software don't
 *         provide extra information. In that case, this element will be absent
 *         from the collection.</td>
 *     <td><tt>NSString</tt></td>
 *     
 *     </tr>
 * </table>

 * \par Data Leakage Policy Enforcement
 * Security policies other than the Data Leakage policy (DLP) mentioned in the
 * above are enforced by the BlackBerry Dynamics runtime, without reference to
 * the application. DLP must generally be enforced by the application, with some
 * exceptions.\n
 * If DLP is switched on, the BlackBerry Dynamics runtime will:<ul>
 * <li>
 *     Secure general cut-copy-paste operations by the user.</li>
 * <li>
 *     Secure data written to the general pasteboard
 *     by content-rendering <tt>UIKit</tt> components.</li>
 *   </ul>
 *  Secure cut-copy-paste  
 *  operations allow the user to copy and move data via the clipboard
 *  only:
 * - Within one BlackBerry Dynamics application.
 * - Between BlackBerry Dynamics applications, on the same device, that were activated
 *   for the same end user from the same enterprise management console.
 * - Between BlackBerry Dynamics applications, on multiple iOS and macOS devices
 *   conforming to Apple Continuity system requirements, that were activated
 *   for the same end user from the same enterprise management console.
 * .
 * Other aspects of data leakage must be enforced by the application.\n 
 * Note that pasteboards other than the general pasteboard, i.e.
 * programmatically created <tt>UIPasteboard</tt> instances, are never secured
 * by the BlackBerry Dynamics runtime.\n
 * @see <a
 href="https://support.apple.com/en-ca/HT204681#clipboard"
 target="_blank"> Universal Clipboard</a> on the apple.com support website. \n
 * \n \par Application Server Selection
 * The <tt>GDAppConfigKeyServers</tt> value will contain a list of the servers
 * that have been configured for the application in the enterprise management
 * console. In the case that more than one server has been configured, the
 * recommended selection algorithm is as follows:
 * -# For each priority value in the list, starting with the highest:
 * -# Select a server that has that priority, at random.
 * -# Attempt to connect to the server.
 * -# If connection succeeds, use that server.
 * -# If connection fails, try another server at the same priority, at random.
 * -# If there are no more untried servers at that priority, try the servers at
 *    the next lower priority.
 * .
 * 
 * @see \ref GC
 * @see <a
    href="https://developer.apple.com/reference/foundation/nsdictionary?language=objc"
    target="_blank"
    >NSDictionary class reference</a> in the Apple API Reference on the
    apple.com developer website.
 * @see The GD-Secure compliance document.
 */
- (NSDictionary<NSString *, id> *)getApplicationConfig;

/** Get application-specific policy settings from the enterprise management
 *  console, as a collection.
 *  
 * 
 * This function returns a collection of application-specific policy
 * settings. The settings will have been made in the management console, and
 * retrieved by the BlackBerry Dynamics runtime.
 *
 * For more documentation of the feature and how application policies are
 * defined, see the \ref AppPolicies documentation.
 * 
 * Retrieval of policy settings may happen during authorization processing, or
 * whenever settings are changed. When changed settings have been retrieved by
 * the runtime, a <tt>GDAppEventPolicyUpdate</tt> event will be dispatched to
 * the application. See the \reflink GDAppEvent GDAppEvent \endlink class reference for
 * details, and see the notes under the Enterprise Configuration Information
 * heading, above.
 *
 * Note that retrieval of that latest policy from the management server is
 * not triggered by calling this function.
 * 
 * @return <tt>NSDictionary</tt>
 *         containing policy settings.
 *         
 * The keys will be the same as the settings identifiers in the policy
 * definition. The values will be the particular values that apply to the end
 * user. The value types are mapped from the definition as follows.
   <table
   ><tr
       ><th>Definition Type</th><th>Dictionary Value Type</th
 
   ></tr><tr><td>null</td><td><tt>nil</tt></td
 
   ></tr><tr><td
       >boolean</td><td><tt>NSNumber</tt></td
 
   ></tr><tr><td
       >double</td><td><tt>NSNumber</tt></td
 
   ></tr><tr><td
       >int</td><td><tt>NSNumber</tt></td
 
   ></tr><tr><td
       >object</td><td><tt
           >NSDictionary</tt></td
 
   ></tr><tr><td
       >array</td><td><tt>NSArray</tt></td
 
   ></tr><tr><td>string</td><td><tt>NSString</tt></td
 
  ></tr
  ></table>
 * @see \reflink GDiOS::getApplicationPolicyString getApplicationPolicyString (GDiOS) \endlink
 */
- (NSDictionary<NSString *, id> *)getApplicationPolicy;

/** Get application-specific policy settings from the enterprise management
 *  console, as JSON.
 * 
 *  
 * This function returns application-specific policy settings in a
 * JavaScript Object Notation (JSON) string. The settings will have been made in
 * the management console, and retrieved by the BlackBerry Dynamics runtime.
 * 
 * For more documentation of the feature and how application policies are
 * defined, see the \ref AppPolicies documentation.
 *
 * Retrieval of policy settings may happen during authorization processing, or
 * whenever settings are changed. When changed settings have been retrieved by
 * the runtime, a <tt>GDAppEventPolicyUpdate</tt> event will be dispatched to
 * the application. See the \reflink GDAppEvent GDAppEvent \endlink class reference for
 * details, and see the notes under the Enterprise Configuration Information
 * heading, above.
 *
 * Note that retrieval isn't as such triggered by calling this function.
 * 
 * @return <tt>NSString</tt> containing policy settings in a JSON string.
 *         The string will evaluate to an object with an attribute for each
 *         application-specific setting. The names of the attributes will be the
 *         same as the settings identifiers in the policy definition. The
 *         attribute values will be the particular values that apply to the end
 *         user.
 * 
 * @see \reflink GDiOS::getApplicationPolicy getApplicationPolicy (GDiOS) \endlink
 */
- (NSString*)getApplicationPolicyString;

/** Get providers of shared services.
 * 
 * This function returns a list of all available providers of
 * shared services. The list contains both application-based and server-based
 * service providers.
 *
 * The returned list is based on the BlackBerry Dynamics entitlement
 * configuration in the enterprise management console and in the central
 * BlackBerry Dynamics Catalog. An entitlement can correspond to an application,
 * or can be a placeholder for something more abstract such as access to a
 * feature or resource. In any case, entitlements have unique identifiers and
 * versions.
 *
 * The list includes an entry for each entitlement version that meets all the
 * following conditions.
 * - The entitlement version is registered as the provider of one or more shared
 *   services, see notes on service provider registrations, below.
 * - The end user that activated the running application has been granted the
 *   entitlement version, i.e. they are entitled to the service provider.
 * - For entitlements that represent application-based service providers: the
 *   corresponding application has been installed and activated for the same end
 *   user, and on the same device or computer, as the current application.
 * .
 *
 * On devices running iOS version 9 or later, the list could include providers
 * of application-based services that were installed and activated as above, but
 * then uninstalled. An attempt to send a service request to an application that
 * is not currently installed results in a
 * <tt>GDServicesErrorApplicationNotFound</tt> error.
 *
 * <em>Service provider registrations</em> are stored within the BlackBerry
 * Dynamics infrastructure, on a server known as the Catalog. Registrations are
 * stored as relationships between entitlement versions and service identifiers.
 * The user interface for registration administration is either the enterprise
 * management console, or a website that can be reached via the application
 * developer portal. The same user interfaces are used for the creation and
 * administration of individual shared service definitions.
 * 
 * The runtime retrieves the information used to generate the list of service
 * providers from the Catalog, and from the enterprise management console.
 * Retrieval can take place when the application is authorized, or when another
 * application activates on the same device, or when the configuration is
 * changed in the enterprise management console. Note that retrieval isn't as
 * such triggered by calling this function.
 * 
 * For each entitlement version that satisfies the above conditions, this
 * function returns a \reflink GDServiceProvider GDServiceProvider \endlink object.
 *
 * The returned details for an application-based provider can be used to send a
 * service request to the service provider using BlackBerry Dynamics
 * AppKinetics. See the \reflink GDService GDService class reference\endlink for details of the programming
 * interface. See under Service Provider Requirements on that page for
 * information on service provider registration, which is a prerequisite for an
 * application to be on the list returned by this function.
 *
 * The returned details for a server-based provider can be used to establish
 * HTTP or TCP socket communications with a server instance.
 * 
 * @return <tt>NSArray</tt> of <tt>GDServiceProvider</tt
 *         > objects containing the list of available service providers. The
 *         order of objects in the list is unspecified.
 * 
 * A single service could have multiple providers. A single provider could
 * provide multiple services, and multiple versions of services.
 *
 * When changed details have been retrieved by the runtime, a
 * <tt>GDAppEventServicesUpdate</tt> event will be dispatched to the
 * application. See the \reflink GDAppEvent GDAppEvent \endlink class reference for details,
 * and see the notes under the Enterprise Configuration Information heading,
 * above.
 * 
 * <h4>Icon images</h4>
 * The objects returned by this function can include icon images for service
 * provider applications. Utilization of icon images is optional. If the
 * application does utilize icon images, then make a setting in the
 * application's Info.plist file* as follows.
 * - Key: <tt>GDFetchResources</tt>
 * - Type: <tt>Boolean</tt>
 * - Value: <tt>YES</tt>
 * .
 * (*In case there are multiple Info.plist files, check that the correct one has
 * been edited by opening the Info tab of the application target being built.
 * The setting just made should appear there.)
 *
 * If the setting is missing or the value is <tt>NO</tt>, this indicates that
 * the application doesn't utilize icon images.
 *
 * The data for icon images would be retrieved by the BlackBerry Dynamics
 * runtime, from a BlackBerry Dynamics Catalog service. BlackBerry may switch
 * off the icon image service at the Catalog from time to time, for operational
 * reasons. If the icon image service is switched off then all icon images in
 * the returned objects will be <tt>nil</tt>.
 */
- (NSArray<GDServiceProvider *> *)getServiceProviders;

/** Discover providers of a specific shared service.
 *
 *  This function returns a list of the available providers of a
 * specified service.
 *
 * The returned list is based on the BlackBerry Dynamics entitlement
 * configuration in the enterprise management console and in the central
 * BlackBerry Dynamics Catalog. The list includes an entry for each entitlement
 * version that meets all the following conditions.
 * - The entitlement version would be on the list of service providers returned
 *   by the \reflink GDiOS::getServiceProviders getServiceProviders (GDiOS) \endlink function, see above.
 * - The entitlement version is registered as a provider of the specified
 *   service.
 * - The entitlement version is registered as a provider of the specified
 *   service type, either server-based or application-based.
 * - The entitlement version is registered as a provider of the service version,
 *   if specified.
 * .
 *
 * @param serviceId <tt>NSString</tt> specifying the identifier of the required
 *                  service.
 *
 * @param version <tt>NSString</tt> specifying the required version of the service, or
 *                <tt>nil</tt> to leave unspecified.
 *
 * @param serviceType <tt>GDServiceType</tt> value specifying the required type
 *                    of service.
 *
 * @return <tt>NSArray</tt> of <tt>GDServiceProvider</tt
 *         > objects containing the list of available service providers. The
 *         order of objects in the list is unspecified.
 *
 * See also the note on Icon images in the <tt>getServiceProviders</tt>
 * function documentation, above.
 */
- (NSArray<GDServiceProvider *> *)getServiceProvidersFor:(NSString*)serviceId andVersion:(nullable NSString*)version andServiceType:(GDServiceType)serviceType;


#undef DEPRECATE_GETSERVICEPROVIDERSFOR

/** Type for getEntitlementsFor block parameter.
 * 
 * Pass a code block of this type as the <tt>block</tt> parameter to the
 * \link GDiOS::getEntitlementVersionsFor:callbackBlock:
 * getEntitlementVersionsFor: \endlink function.
 *
 * The block receives the following parameters.
 * @param entitlementVersions <tt>NSArray</tt> of \ref GDVersion objects
 *                            representing the versions of the entitlement to
 *                            which the end user is entitled if the original
 *                            call succeeded, or <tt>nil</tt> otherwise.
 * 
 * @param error <tt>NSError</tt> containing a description of the error condition
 *                               if the original call failed, or <tt>nil</tt>
 *                               otherwise.
 */
typedef void (^GDGetEntitlementVersionsForBlock) (NSArray<GDVersion *>* _Nullable entitlementVersions, NSError* error);

/** Check whether the end user has a particular entitlement.
 * 
 * Call this function to check whether the current end user has a
 * specific BlackBerry Dynamics entitlement. The return value is a list of
 * entitlement versions, which might be empty.
 *
 * This function can be used to check for entitlement to:
 * - A specific BlackBerry Dynamics mobile or desktop application, identified by
 *   a BlackBerry Dynamics entitlement identifier.
 * - A more abstract entitlement, such as a feature, also identified by an
 *   entitlement identifier.
 * .
 * Note that there is a single namespace and format for entitlement identifiers,
 * whether used for applications or for more abstract entitlements. All
 * entitlements have versions, as well as identifiers. The syntax for
 * entitlement identifiers and versions is detailed above, under the headings
 * Entitlement Identifier Format and Entitlement Version Format. The syntax
 * applies to all types of entitlement.
 *
 * Specify the entitlement to be checked by passing its identifier as a
 * parameter. The return value will be a list:
 * - If the end user doesn't have the specified entitlement, the list will have
 *   zero elements.
 * - Otherwise, the list will have one element for each version to which the end
 *   user is entitled. Each element will be a
 *   \link GDVersion \endlink
 *   object.
 * .
 *
 * This function is asynchronous.
 * 
 * The result list is returned by execution of a code block. Specify the code
 * block as a parameter to this function. The result list will be passed as
 * a block parameter to the execution. If an error occurs and the entitlement
 * cannot be checked, <tt>nil</tt> will be passed instead of the list, and an
 * <tt>NSError</tt> object will be passed as a second block parameter.
 *
 * Calling this function can result in data communication with the
 * BlackBerry Dynamics infrastructure.
 * 
 * @param identifier <tt>NSString</tt> containing the entitlement identifier.
 * 
 * @param block Block to execute when the lookup completes. The block receives
 *              two parameters:\n
 *              <tt>NSArray</tt> of \ref GDVersion objects representing the
 *              versions to which the end user is entitled if the original call
 *              succeeds, or <tt>nil</tt> otherwise.\n
 *              <tt>NSError</tt> object containing a numeric code for the error
 *              condition if the original call fails, or <tt>nil</tt> otherwise.\n
 *              The numeric code will be in one of the following ranges,
 *              depending on the type of error condition encountered:
 *              - 400 to 599: One or more servers involved in the check
 *                            encountered an error and the check could not be
 *                            completed.
 *              - -1 to -50: A general error occurred.
 *              .
 * 
 * \par
 *
 * The entitlements of the end user can change, for example if the user's group
 * membership is changed at the enterprise management console. The BlackBerry
 * Dynamics runtime is notified of these changes by the BlackBerry Dynamics
 * infrastructure, and dispatches a <tt>GDAppEventEntitlementsUpdate</tt> event
 * to the application. See the \reflink GDAppEvent GDAppEvent \endlink class reference for
 * details, and see the notes under the Enterprise Configuration Information
 * heading, above.
 */
- (void)getEntitlementVersionsFor:(NSString*)identifier
                    callbackBlock:(GDGetEntitlementVersionsForBlock)block;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_GETWINDOW __attribute((deprecated("Use the window property from the main app delegate instance.")))
#else
#   define DEPRECATE_GETWINDOW __attribute((deprecated))
#endif
/* \endcond */

/** Get the <tt>UIWindow</tt> for the application (deprecated).
 * \deprecated This function is deprecated and will be removed in a future
 * release. Use the <tt>window</tt> property from the main app delegate instance.
 *
 * This function returns a reference to the <tt>UIWindow</tt> that contains
 * the core logic of the BlackBerry Dynamics runtime. Always use this function
 * instead of creating a new <tt>UIWindow</tt> in the application.
 *
 * The BlackBerry Dynamics runtime creates its own <tt>UIWindow</tt> in order to
 * show its user interface elements, and to track for user inactivity. The
 * runtime doesn't add any persistent subviews, so the application is free to
 * add and remove its own subviews on the BlackBerry Dynamics <tt>UIWindow</tt>.
 * For example, after authorization, the application could call
 * <tt>setRootViewController</tt> to add its own <tt>UIViewController</tt> or
 * <tt>UINavigationController</tt>.
 *
 * The runtime calls <tt>makeKeyAndVisible</tt> on its <tt>UIWindow</tt> during
 * authorization processing, so the application needn't do this. The application
 * mustn't make a different <tt>UIWindow</tt> the key window. The application
 * also mustn't release the runtime's <tt>UIWindow</tt> object.
 *
 * @return Reference to the BlackBerry Dynamics <tt>UIWindow</tt>, which must be
 *         used as the application's key window.
 *
 * @see <a
 *     HREF="https://developer.apple.com/reference/uikit/uiwindow?language=objc"
 *     target="_blank"
 * >UIWindow class reference</a> in the Apple API Reference on the apple.com
 * developer website.
 */
- (UIWindow*)getWindow DEPRECATE_GETWINDOW;

#undef DEPRECATE_GETWINDOW

/** Get the BlackBerry Dynamics runtime library version.
 * @return <tt>NSString</tt> containing the BlackBerry Dynamics runtime library
 *         version in
 *         <em>major</em><tt>.</tt><em>minor</em><tt>.</tt><em>build</em>
 *         format.
 */
- (NSString*)getVersion;

/** Open the BlackBerry Dynamics preferences user interface to change password.
 * 
 * Call this function to show the BlackBerry Dynamics interface
 * to enable the user to change their unlock password. 
 * 
 * This function enables a BlackBerry Dynamics user interface element to be
 * included in the application's own user interface.
 *
 * If authorization is delegated to another application, then that application
 * will be opened and its Change Password user interface will be shown.
 *
 * @param baseViewController Reference to the navigation controller within which
 *        the BlackBerry Dynamics user interface element is to open as a view
 *        controller.\n
 *        Pass a null pointer to open the the user interface as a modal view
 *        controller, for example when no navigation controller is available.
 *
 * @return <tt>YES</tt> if the user interface element opened OK.
 * @return <tt>NO</tt> if the user interface element was already open,
 *                   or if enterprise policy doesn't require a password to unlock the application,
 *                   or if the application has been wiped.
 */
- (BOOL)showPreferenceUI:(nullable UIViewController*)baseViewController;

/** Configure the visual appearance of the BlackBerry Dynamics user interface.
 * 
 * 
 * Call this function to configure the visual appearance of the built-in
 * BlackBerry Dynamics user interface. The following aspects can be configured:
 * - Logo image.
 * - Brand color, used for the key line and interactive elements.
 * .
 * This function can be called prior to <tt>authorize</tt>, in order to
 * configure the user interface as displayed during authorization processing.
 *
 * @param imagePath <tt>NSString</tt> containing the path of the image to show as the
 *                  logo. The image must be in PNG format.\n
 *                  The maximum supported image size is 528 by 140 pixels. If
 *                  the specified image is larger than the maximum, the image
 *                  will be adjusted using
 *                  <tt>UIViewContentModeScaleAspectFit</tt> mode.
 * @param bundle <tt>NSBundle</tt> for the resource bundle that contains the
 *               replacement logo image, or <tt>nil</tt> to specify
 *               <tt>mainBundle</tt>.
 * 
 * @param color <tt>UIColor</tt> for the brand color, or
 *              <tt>nil</tt> to select the default.
 *
 * @see \reflink GDiOS::authorize: authorize (GDiOS) \endlink for details of which BlackBerry Dynamics user
 * interface elements may be shown during authorization processing.
 * @see <a
      href="https://developer.apple.com/reference/uikit/uiviewcontentmode?language=objc"
      target="_blank"
  >UIViewContentMode documentation</a> in the Apple API Reference on the
  apple.com developer website, for definitions of image adjustment modes
 */
- (void)configureUIWithLogo:(NSString*)imagePath
                     bundle:(nullable NSBundle*)bundle
                      color:(nullable UIColor*)color;

/** Delegated event-handling.
 * 
 * When authorization processing completes, or a BlackBerry Dynamics runtime
 * object event occurs, an event is generated by the runtime, and passed to a
 * callback function in the application code.
 *
 * Set this property to an instance of a class in the application that contains
 * the code for the required callback function, i.e. a class that implements
 * the GDiOSDelegate protocol.
 *
 * @see \ref GDState for an alternative mechanism.
 */
@property (nullable, nonatomic, weak) id<GDiOSDelegate> delegate;

/** Whether it is possible to authorize autonomously.
 *
 * Access this property to check
 * whether autonomous authorization is possible. Autonomous authorization won't
 * be possible if the application is protected by a BlackBerry Dynamics
 * password. This means a password or other interactive authentication that is
 * enforced by the BlackBerry Dynamics runtime.
 *
 * Interactive authentication will be enforced by BlackBerry Dynamics unless a
 * <em>no-password</em> policy applies to the current end user. A no-password
 * policy would typically be put in place only in the case that interactive
 * authentication is enforced by some other means. For example, enterprise
 * mobile device management (MDM) can be used to force users to set a device
 * password or lock pattern. In that case, the enterprise might choose to set a
 * no-password policy for BlackBerry Dynamics, so that end users don't have to
 * enter two passwords.
 *
 * If interactive authentication isn't enforced by BlackBerry Dynamics, then it
 * is possible for authorization processing to complete autonomously, because
 * interaction with the user isn't required.
 *
 * The intended use of this property is to check
 * whether it is possible for authorization processing to complete autonomously,
 * before calling the
 * \reflink GDiOS::authorizeAutonomously: authorizeAutonomously: (GDiOS) \endlink function.
 * 
 * Note that it won't be possible to authorize autonomously if enterprise
 * policy specifies that the application delegates authentication to another
 * application. This would only happen if the current end user somehow had both
 * policies in place: authentication delegation, and no-password. This
 * combination isn't recommended. There would seem to be no point in delegating
 * authentication to another application if that other application is going to
 * authenticate the end user without interaction.
 *
 * This property can be accessed before
 * authorization processing is complete.
 * 
 * This property has the value:
 * - <tt>YES</tt> if autonomous authorization is possible.
 * - <tt>NO</tt> if a password is enforced by BlackBerry Dynamics, or if
 *             autonomous authorization isn't possible for some other reason.
 */
@property (nonatomic, readonly) BOOL canAuthorizeAutonomously;

/** Lock the application permanently.
 * 
 * Call this function to lock the application permanently, as
 * though a remote lock-out had been received from the enterprise management
 * console. The application data will become inaccessible but won't be erased.
 *
 * A remote lock-out is, in effect, a withdrawal of the end user's authorization
 * to utilise the application. The user cannot unlock the application in the
 * normal way, for example they cannot enter their BlackBerry Dynamics password,
 * if a remote lock-out is in place. Instead, a special unlock code must be
 * obtained from the management console, and entered in the remote unlock
 * BlackBerry Dynamics user interface.
 *
 * @see \reflink GDAppEvent GDAppEvent \endlink class reference, which mentions the
 * <tt>GDErrorRemoteLockout</tt> result code. An event with that result code
 * would be dispatched if a remote lock-out command was received from the
 * management console.
 */
- (BOOL)executeRemoteLock;

/** Blocks application locally with defined blockId.
 *
 * Call this function to block use of the application, as though a remote block
 * had been received from the enterprise management console. Include a title and description
 * to inform the user what threat or action has triggered the block. If several blocks have
 * been applied then it is the most recent block which will be displayed
 * to the user in the block screen.
 
 * While blocked, the application can utilize the principal Dynamics APIs like secure
 * storage and secure communications.
 
 * Blocks are persisted which means that after an application is restarted and the user
 * is authenticated the block screen will be displayed. In addition a \reflink GDAppEvent GDAppEvent \endlink
 * with the result code <tt>GDErrorBlocked</tt> would be dispatched. This event would be received
 * for blocks applied locally with this function and those applied from the management console.
 *
 * The application should persist in secure storage the blockId called in this function. When
 * a <tt>GDErrorBlocked</tt> event is received the application should check if any blocks are
 * applied locally and determine if the block can now be removed.
 *
 * @param blockId <tt>NSString</tt> specifying the block identifier. This identifier is required to
 * subsequently remove the block.
 * @param title <tt>NSString</tt> containing the title shown on the block screen.
 * @param message <tt>NSString</tt> containing the detailed message to display on the block screen.
 */
- (void)executeBlock:(NSString *)blockId withTitle:(NSString *)title withMessage:(NSString *)message;

/** Unblocks application locally with defined blockId.
 *
 * Call this function to remove a block screen with associated blockId.
 * Other local or remote blocks will still leave the application blocked. Blocks applied
 * by the management console cannot be unblocked using this function.
 *
 * @param blockId <tt>NSString</tt> specifying the block identifier.
 */
- (void)executeUnblock:(NSString *)blockId;

/** Executes migration of the application to a different management console.
 * @return <tt>YES</tt> if destinationTenantID is provided
 * @return <tt>NO</tt> if destinationTenantID is empty
 *
 * Call this function to execute a migration of the application to the specified
* management console. This should only be called by an application that has been informed by the
* management console that a migration request is pending. If a migration request is not pending
* calling this method may result in the container being wiped.
*
* @param destinationTenantID <tt>NSString</tt> specifying the tenant identifier of the UEM management console.
* @param uemServerAddress <tt>NSString</tt> containing the URL for UEM enrollment service.
 */
-(BOOL)executePendingConsoleMigration:(NSString *)destinationTenantID withUemServerAddress:(NSString *)uemServerAddress;

/** Observable representation of authorization state and user interface state.
 *
 * Access this property to check or observe the state of the BlackBerry Dynamics
 * runtime.
 *
 * A number of aspects of run-time state are represented in this property,
 * including authorization state and user interface state. The representation is
 * compatible with key-value observing (KVO). See the \link GDState \endlink
 * class reference for details.
 * 
 * @return GDState instance representing the current state.
 */
@property (nonatomic, strong, readonly) GDState *state;

@end

NS_ASSUME_NONNULL_END

#endif /* __GD_IOS_H__ */
