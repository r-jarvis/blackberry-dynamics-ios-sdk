/*
 * Copyright © 2024 BlackBerry Limited. All rights reserved.
 */

#import <UIKit/UIKit.h>
#import <BlackBerryDynamics/GD/GTLCommonSettingsCellConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class GTLauncherViewController;

/*!
 * @protocol GTLauncherViewControllerDelegate GTLauncherViewController.h <BlackBerryDynamics/GD/GTLauncherViewController.h>
 * \brief Handler for events dispatched from the Launcher view controller.
 *
 * Launcher state changes and requests made by @p GTLauncherViewController  are handled by creating a class that implements this protocol.
 */
@protocol GTLauncherViewControllerDelegate <NSObject>

@optional

/*!
 * \brief Called before logs start uploading
 * 
 * This method is called before logs start uploading and must call the completion when app is ready for logs to start uploading.
 * 
 * If provided this function must complete before logs start uploading
 *
 * @param completionHandler which must be called to start upload. Failure to do so may hang the UI.
 */
- (void)completeAdditionalProcessingBeforeUploadingLogs:(void(^ _Nullable)(void))completionHandler;

/*!
 * \brief Indicate that the Launcher view will be set to an open state.
 *  
 * This method is called when the the app is in an open state and the user manually taps on the Launcher or
 * \code -[GTLauncherViewController setOpen:animated:] \endcode with @p YES as the first parameter is called.
 *
 * @param controller @p GTLauncherViewController that is being opened.
 */
- (void)launcherViewControllerWillOpen:(GTLauncherViewController *)controller;

/*!
 * \brief Indicate that the Launcher view will be set to a closed state.
 *  
 * This method is called when the the app is in a closed state and the user manually taps on the Launcher or
 * \code -[GTLauncherViewController setOpen:animated:] \endcode with @p NO as the first parameter is called.
 *
 * @param controller @p GTLauncherViewController that is being closed.
 */
- (void)launcherViewControllerWillClose:(GTLauncherViewController *)controller;

/*! 
 * \brief Allows the host application to perform additional work before exiting to an external application.
 * 
 * Allows the host application to perform additional work before exiting to an external application.
 * Certain Launcher actions, like selecting another Dynamics app or selecting a
 * create action, requires flipping to another application. However, if the
 * host application needs to perform additional action, such as present an
 * alert, beforebeing sent to the background, the delegate can implement this
 * method, retain a reference to the handler, and return @p NO. After
 * the host application finishes its respective action, it can then execute
 * the open handler.
 *
 * If this method is not implemented, the default value is @p YES and
 * the open handler is executed immediately.
 *
 * @param controller @p GTLauncherViewController that is requesting to launch an external application.
 * @param handler The block of code that, when called, executes the appropriate open behavior.
 * @param address @p NSString representing the address of the application being opened and fronted. Use
 * this value in conjunction with @code -[GDiOS getServiceProviders] @endcode to get additional information of
 * the application being opened.
 * @return @p YES if the launcher should perform the open behavior immediately.
 * @p NO if the host application intends on retaining the open handler and
 * executing it at a later time.
 */
- (BOOL)launcherViewController:(GTLauncherViewController *)controller shouldExecuteOpenHandler:(void (^)(void))handler atAddress:(NSString *)address;

/*!
 * \deprecated Will be removed in a future release. BlackBerry Dynamics Launcher now handles GDAuthToken management internally.
 * @brief Provide an authentication token to Launcher [Deprecated].
 * 
 * Provide an authentication token to Launcher.
 * 
 * @p GDUtility is actually a singleton class with regards to the behavior
 * of its delegate. In other words, there can only be one for an application.
 * Application that provide @p GTLHostGDAuthTokenManagement as a startup
 * option must implement this delegate method so that Launcher can properly
 * execute its various services.
 *
 * Because the behavior of retrieving an auth token is asynchronous, a completion
 * handler is provided that must be retained until a token is made available or an
 * error occurs.
 *
 * When requesting an auth token, @p nil and the name parameter should be
 * used for the challenge string and server name parameters of @code -[GDUtility getGDAuthToken:serverName:] @endcode respectively.
 *
 * @param controller @p GTLauncherViewController that is requesting an auth token.
 * @param name @p NSString of the server name parameter to be provided to @p GDUtility when requesting an auth token.
 * @param completion The block of code to be retained and executed when an @p GDAuthTokenDelegate method is called. In the event of a sucess,
 * pass the @p NSString parameter provided in the callback. In the event of an error, pass @p nil.
 */
- (void)launcherViewController:(GTLauncherViewController *)controller didRequestGDAuthTokenForServerName:(NSString *)name completion:(void (^)(NSString *token))completion DEPRECATED_MSG_ATTRIBUTE("This method will be removed in a future release.");

/*!
 * \brief Provide custom application settings to be presented from Launcher.
 * 
 * The application settings table view controller to be presented from Launcher.
 * The host application can provide its own settings table view controller that would be displayed upon the user
 * selecting Settings from Launcher, along with Common settings provided by Launcher.
 *
 * Note that the view controller being presented is not the one being returned but rather an
 * internal context view controller which provides additional functionality to
 * Launcher. The settings view controller is a child view controller of the context view
 * controller and its bounds are set to the bounds of the context view controller. Thus,
 * any setting of the modal presentation or transition style is ignored.
 * Please exclude setting options offered by the Launcher Common settings section in the application table view controller.
 *
 * If this method is not implemented, the Launcher Common settings view controller will
 * be presented instead.
 * \param controller @p GTLauncherViewController that is requesting style for particular cell.
 * @return UITableViewController  with the settings for the host application. Returning @p nil will cause the default behavior of 
 * having the Launcher Common settings view controller being displayed.
 */
- (UITableViewController * _Nullable)applicationSettingsTableViewControllerForLauncher:(GTLauncherViewController *)controller;

/*!
 * \brief Customize the styling of common settings shown in the Launcher settings menu.
 *
 * Host application can configure styles for the common settings section by returning @p GTLCommonSettingsCellConfiguration object. 
 * This includes the fonts, icons and colors.
 * 
 * If this method is not implemented, default style will be used.
 *
 * \see: GTLCommonSettingsCellConfiguration
 * \see: GTLCommonSettingsCellConfiguration::GTLCommonSettingsCellType
 * \param cellType: @p GTLCommonSettingsCellType type of table view cell that requests styling.
 * \param controller: @p GTLauncherViewController that is requesting style for particular table view cell.
 *
 * @return @p GTLCommonSettingsCellConfiguration with the settings for the host application. Returning nil will cause the default behavior and 
 * default style to be applied.
 */
- (GTLCommonSettingsCellConfiguration * _Nullable)commonSettingsCellConfigurationForType:(GTLCommonSettingsCellType)cellType
                                                                  launcherViewController:(GTLauncherViewController *)controller;

/*! 
 *  \brief Called when a user selects a Launcher Collection View Element provided by the host appliction.
 *
 * Called when a user selects a Launcher Collection View element provided by the host application. An appropriate view controller for this element 
 * should be returned. Use the location parameter to determine what the appropriate view controller should be.
 *
 * @param controller @p GTLauncherViewController that is requesting a view controller for given location
 * @param location @p NSString id of element selected by user
 */
- (UIViewController *)launcherViewController:(GTLauncherViewController *)controller viewControllerForLauncherSectionLocation:(NSString *)location;

/*! 
 * \brief A local quick action, such as compose email, or an web app.
 * 
 * A local quick action, such as compose email, or an web app (for com.good.gdservice.open-url.http service providers) was selected. Only apps that have associated 
 * quick actions need to implement this.
 *
 * @param controller @p GTLauncherViewController that is requesting a quick action for given location
 * @param location @p NSString id of element selected by user
 */
- (void)launcherViewController:(GTLauncherViewController *)controller didSelectLocalActionWithLocation:(NSString *)location;

@end

/*!
 * \class GTLauncherViewController GTLauncherViewController.h <BlackBerryDynamics/GD/GTLauncherViewController.h>
 * \brief This class represents the main application view controller class comprised of a floating Launcher button, Launcher's main view, and a base view controller.
 * 
 * The “Launcher” is a UX concept whereby an icon is displayed permanently on each screen, “floating” over the content.
 * From the Launcher a user is able to launch other BlackBerry Dynamics apps, as well as take Quick Actions such as compose an email or schedule a meeting. 
 * 
 *  \uimage{LauncherUXConcepts.png,Launcher UX Concepts}
 * 
 * <b> Setup </b> <br>
 * 
 * The Launcher will be automatically started, and present the floating Launcher button from every view. Applications can control the behavior by getting 
 * an instance of Launcher using <tt>`GDiOS.sharedInstance().getManagedLauncherViewController()`</tt> and then setting the Launcher delegate to the delegate object.
 *
 * \code
 * Class AppDelegate : GDiOSDelegate, GTLauncherViewControllerDelegate {
 * func handle(_ anEvent:GDAppEvent) {
 *              switch  anEvent.type
 *              {
 *              case .authorized:
 *                              GDiOS.sharedInstance().getManagedLauncherViewController().delegate = self
 *                              break;
 *              …
 * 
 * \endcode
 *
 * Alternatively, Launcher can be disabled completely by adding the following to the application’s info.plist:
 * 
 * \code
 *  <key>GDDisableAutomaticLauncherManagement</key>
 *  <value>true</value>
 * \endcode
 * 
 * The Launcher includes an affordance to open a settings page for the application. Applications may provide their own settings implementation, 
 * by implementing the GTLauncherViewControllerDelegate::applicationSettingsTableViewControllerForLauncher: method. If an application does not 
 * provide its own implementation, a default one will be provided, which includes basic functionality such as changing the application password 
 * and uploading logs. 
 * 
 *
 * <b> View Controller Heirarchy </b> <br>
 * The Launcher view controller is intended to be a container view controller whose base
 * view controller is a single child view controller. The base view controller's view's
 * bounds are set to that of the Launcher view controller's view. While the base view
 * controller can have child view controllers, it is not recommended that Launcher's
 * view controller's child view controllers be directly set. The @p GTLauncherViewController
 * class should also not be subsclassed.
 *
 * The view layers are setup such that the Launcher button and view shown in the open state
 * are always on top of the base view controller. The open state of launcher is not
 * displayed modally so any modal view controllers will display properly over the Launcher
 * view controller and no special steps need to be taken to present and dismiss them.
 * 
 * By default Launcher handles childViewControllerForStatusBarHidden call, to redirect related methods to baseViewController please implement GTLauncherViewController category
 * with next methods:
 *
 * \code
 * - (UIViewController *)childViewControllerForStatusBarHidden {
 *       return self.baseViewController;
 *   }
 * \endcode
 *
 * <b> View State </b> <br>
 * There are several properties and methods to manage the state of the Launcher. The following
 * are valid states:
 * - Closed with visible button
 *    This is the default state of Launcher when first initialized. The Launcher's button
 *    will be in the last placed position, relative to its rotation.
 * - Open with visible button
 *    This state is set whenever the user selects the Launcher button or is
 *    programmatically opened. The Launcher
 *    button will be in the bottom right corner and cannot be moved.
 * - Closed with hidden button
 *    This state is available when the @p showingLauncher property is set
 *    to @p YES. This property cannot be set if the launcher view is an open state.\n
 *    This state is useful for application that intend on providing modal-like behavior without
 *    the use of modal views, such as an introductory or account setup screen.
 *
 * \b Settings <br>
 * The settings button within Launcher allows for a host app to display its own custom settings.
 * If no settings view controller is provided via the delegate call
 * the default Launcher settings view will be presented modally.
 * \code -[id<GTLauncherViewControllerDelegate> applicationSettingsTableViewControllerForLauncher:] \endcode
 *
 * If the host app does choose to present its settings through Launcher, it must add the
 * Launcher view controller in an appropriate place within its settings heirarchy.
 * @see @p GTLauncherSettingsViewController
 * @see Launcher sample application
 *
 */

OBJC_EXPORT
@interface GTLauncherViewController : UIViewController

/*!
 * \deprecated Will be removed in a future release.
 * \brief Options for Launcher startup [Deprecated].
 *
 * These options represents the handling of a push connection status and the requesting of auth tokens. The parameter of
 * \code -[GTLauncherViewController startServicesWithOptions:] \endcode method requires either the
 * @p GTLInternalGDAuthTokenAndPushConnectionManagement option or one of both of the other options.
 * These options are required as @p GDUtility and @p GDPushConnection classes are singletons with a single delegate.
 *
 * Type of options to pass to BlackBerry Dynamics Launcher to tell it how to manage GDAuthToken and push connection.
 */
typedef enum : NSInteger
{
    /*!
     * \brief Launcher will utilize GDAuthToken and the GDPushConnection status internally.
     * Host application that neither utilize GDAuthToken or rely on the status of a GDPushConnection
     * can provide this startup option. Launcher will internally set itself as the delegate for @p GDUtility and @p GDPushConnection.
     */
    GTLInternalGDAuthTokenAndPushConnectionManagement = (1 << 0),
    
    /*!
     * \brief Host application will provide auth tokens upon request.
     * Host application that use the @p GDUtility to generate auth tokens should provide this option on Launcher services startup.
     * If this option is provided, the Launcher delegate @b must implement the method:
     * \code -[id<GTLauncherViewControllerDelegate> launcherViewController:didRequestGDAuthTokenForServerName:] \endcode
     */
    GTLHostGDAuthTokenManagement = (1 << 1),
    
    /*!
     * \brief Host application will update Launcher of GDPushConnection status.
     * Host application that set themselves as the @p GDPushConnectionDelegate to monitor the GDPushConnection status
     * should provide this option on Launcher services startup. If this option is provided, the host app should call the
     * \code -[GTLauncherViewController setGDPushConnectionStatus:] \endcode method
     * when the @p onStatus: delegate method is called, passing in the value of the status parameter.
     */
    GTLHostGDPushConnectionManagement = (1 << 2)
} GTLauncherServicesStartupOptions DEPRECATED_MSG_ATTRIBUTE("This enumeration will be removed in a future release.");

/*!
 * \brief Launcher's base view controller
 * 
 * The view controller on which Launcher's view and button will be displayed over.
 * The value of this property can be initially set through the @p initWithBaseViewController: initializer.
 *
 * If a base view controller has not been set at initialization time, setting
 * this property sets it up as a child view controller to the @p GTLauncherViewController
 * instance. Otherwise, the existing child view controller is swapped out with
 * the one being set. Setting this value to nil for an extended period of time
 * is not recommended as the user will see a black screen.
 */
@property (nonatomic, strong, nullable) UIViewController *baseViewController;

/*!
 * \brief Launcher view status.
 *  
 * Read the value of this property, using the @p isOpen accessor, to
 * check whether Launcher's view is open or closed.
 *
 * This property has the value:
 * - @p YES if Launcher is open
 * - @p NO otherwise
 *
 * Setting this property has the affect of providing an animated transition with these values:
 * - @p YES sets Launcher's view state to open.
 * - @p NO sets Launcher's view state to closed.
 */
@property (nonatomic, getter=isOpen) BOOL open;

/*!
 * \brief Launcher button's visibility status.
 * 
 * Read the value of this property, using the @p isLauncherButtonHidden accessor, to
 * check whether Launcher's button is showing or is hidden. Use this method if special,
 * non-modal views are to be displayed, such an application welcome screen, and the
 * Launcher button would be inhibiting.
 *
 * This property has the value:
 * - @p YES if the launcher button is visible
 * - @p NO otherwise.
 *
 * Setting this property changes the visibility of the Launcher button:
 * - @p YES sets Launcher button to be hidden.
 * - @p NO sets Launcher button to be visible.
 *
 * Attempts to change the value of this property while the Launcher's view
 * is in an open state are ignored.
 */
@property (nonatomic, getter=isLauncherButtonHidden) BOOL launcherButtonHidden;

/*!
 * \brief Delegate for Launcher view controller.
 * 
 * Delegate for Launcher view controller.
 * 
 * With the exception of @p GTLHostGDAuthTokenManagement as a startup option,
 * setting a delegate for the Launcher view controller is optional.
 */
@property (atomic, weak, nullable) id <GTLauncherViewControllerDelegate> delegate;

/*!
 * \brief Create and load the Launcher view controller.
 * 
 * Creates and loads the Launcher view controller, using resources from @p GTLauncherBundle,
 * with an initial base view controller. The base view controller can be nil at
 * startup, though the user will be presented with a black screen if one is not
 * set. Setting and changing this value can be done via the
 * @p baseViewController property.
 *
 * Use this or @p init method to load the Launcher view controller. Using
 * @p initWithNibName:bundle: will throw an exception.
 *
 * @param viewController @p UIViewController that will be the initial base view controller.
 * This value can be nil.
 */
- (nullable instancetype)initWithBaseViewController:(UIViewController * __nullable)viewController;

/*!
 * \deprecated This method will be removed in a future release as Dynamics now automatically starts Launcher.
 * \brief Grant Launcher Access to the various Dynamics Services [Deprecated].
 * 
 * Launcher relies on a number of Dynamics APIs internally. These APIs are not
 * available when the app is not yet in an authorized state. Call this
 * method when the host application's @p GDiOSDelegate receives
 * a @p handleEvent: call. Because Launcher relies on several Dynamics
 * APIs that are singleton's in nature, startup options are provided to
 * allow for use of these APIs by both Launcher and the host application.
 *
 * When providing options other than @p GTLInternalGDAuthTokenAndPushConnectionManagement,
 * certain methods must either be implemented or called when appropriate.
 *
 * @see -[GTLauncherViewController launcherViewController:didRequestGDAuthTokenForServerName:completion:]
 * and
 * -[GTLauncherViewController setGDPushConnectionStatus:]
 *
 * @param options @p GTLauncherServicesStartupOptions representing
 * the behavior for GDAuthToken and GDPushConnection management.
 */
- (void)startServicesWithOptions:(GTLauncherServicesStartupOptions)options DEPRECATED_MSG_ATTRIBUTE("This method will be removed in a future release.");

/*!
 * \deprecated This method will be removed in a future release as Dynamics now automatically starts Launcher.
 * \brief Grant Launcher Access to the various Dynamics Services [Deprecated].
 * 
 * Launcher relies on a number of Dynamics APIs internally. These APIs are not
 * available when the app is not yet in an authorized state. Call this
 * method when the host application's @p GDiOSDelegate recieves
 * a @p handleEvent: call.
 */
- (void)startServices;

/*!
 * \brief Set open and closed state of Launcher, providing option to animate transition.
 *
 * Programmatically set Launcher's view to an open or close state,
 * allowing for an option to do the transition with or without
 * animation.
 *
 * This method does nothing if Launcher's button is set to hidden.
 *
 * @param open @p BOOL indicating whether to set the state
 * of Launcher to be open or closed.
 * @param animated @p BOOL indicating whether to set
 * the open or closed state with or without animation.
 */
- (void)setOpen:(BOOL)open animated:(BOOL)animated;

/*!
 * \brief Dismiss the presented settings.
 *
 * Dismiss the presented settings view controller.
 */
- (void)dismissSettings;

/*!
 * \brief Method to present settings.
 *
 * Can be used to present settings screen via other than settings button in Launcher actions.
 */
- (void)presentSettings;

/*!
 * \deprecated Will be removed in a future release. BlackBerry Dynamics Launcher now handles push connection management internally.
 * @brief Update Launcher's internal push connection status [Deprecated].
 * 
 * Host application that start with @p GTLHostGDPushConnectionManagement
 * are assumed to have a @p GDPushConnectionDelegate within their app.
 * Delegate calls to @p onStatus: must be forwarded to the current
 * Launcher view controller via this method, passing along the status
 * parameter that was provided from the delegate callback.
 *
 * @param status @p int value of the push connection status.
 */
- (void)setGDPushConnectionStatus:(int)status DEPRECATED_MSG_ATTRIBUTE("This method will be removed in a future release.");

/*!
 * \deprecated This method will be removed in a future release.
 * \brief The Launcher version [Deprecated].
 * 
 * A value in the form of "X.Y.Z" where X represents the major version,
 * Y represents the minor version, and Z represents the build number. This
 * value is retrieved from the Dynamic bundle.. Use this value
 * for either logging or to diplay in a settings view.
 */
+ (NSString *)launcherVersion DEPRECATED_MSG_ATTRIBUTE("This method will be removed in a future release.");

/*!
 * \brief Sets interval when launcher data cache will be considered as fresh.
 * 
 * Sets interval when launcher data cache will be considered as fresh.
 * - 1 value means it will be forever.
 * - 0  no cache will be used.
 */
+ (void)setCacheExpiry:(NSTimeInterval)seconds;

/*!
 * \brief Indicate that the Launcher view will be set to Certificate Status page.
 * 
 * Indicate that the Launcher view will be set to Certificate Status page.
 *
 * This method is called when the the app is in an open state and the user manually taps on the Certificate Status button
 */
- (void)openCertificatesStatus;

/*!
 * \brief Control showing of coachmark tutorial.
 * 
 * Indicate that the Launcher view will be set to show the Coachmark screen i.e. first time setup screen, this is your launcher walk through
 *
 * This method overrides the default behavior which shows the walk-through on first use only.  If called prior to showing launcher button with NO, the walkthough will not be shown.
 */
+ (void)shouldShowCoachmarkScreen:(BOOL)shouldShow;

/*!
 * \brief Control location of Launcher button.  
 * 
 * Stores Launch Pad Button Image View Center Coordinates in containing view's coordinates.  Must be valid coordinates with respect to device orientation or default position will be used.
 * 
 * This method overrides the default behavior which uses either default button position or last position as user left the button.  The coordinates can only be set once, after that last stored coods
 * are used.
 */
- (void)storeLaunchPadButtonImageViewCenterCoordinates:(CGPoint)point;

/*!
 * \brief Set the state of a Launcher Collection View Element provided by the host application.
 * 
 * To set the state of a host application provided Launcher Collection View Element
 *
 * Setting state to disabled will hide the element.
 *
 * @param enabled @p BOOL indicating whether to set the state of element is enabled or disabled
 * @param identifier  @p NSString id of the element
 */
+ (void)setSectionEnabled:(BOOL)enabled forSectionWithIdentifier:(NSString *)identifier;

/*!
 * \brief Check the state of a Launcher Collection View Element provided by the host application.
 * 
 * To check the state of a host application provided Launcher Collection View Element
 * *
 * @param identifier  @p NSString id of the element
 */
// We need this function to check is Docs section is enabled for GMAGDIOS-3550
+ (BOOL)isSectionEnabled:(NSString *)identifier;

@end

NS_ASSUME_NONNULL_END
