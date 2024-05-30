/*
 * Copyright 2023 BlackBerry Limited. All rights reserved.
 */

#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * \category WKWebView(GDNET) WKWebView+GDNET.h <BlackBerryDynamics/GD/WKWebView+GDNET.h>
 * \brief WKWebView category with additional features.
 *
 * This class is a category of the <tt>WKWebView</tt> class that adds the
 * properties documented below to the programming interface.
*/
@interface WKWebView (GDNET)

/** Specify HTTP/HTTPS proxy protection space
 *
 * If this property is specified, all traffic of this WKWebView instance going through specified proxy. In order to remove proxy set this property to nil.
 *
 * @param proxyProtectionSpace <tt>NSURLProtectionSpace</tt> containing the following:\n
 *              Hostname or address,\n
 *              Port number,\n
 *              Authentication method,\n
 *              Proxy indicator.
 *              In order to create this object should be used method initWithProxyHost:port:type:realm:authenticationMethod: of class NSURLProtectionSpace
 */
@property (strong, nullable) NSURLProtectionSpace* proxyProtectionSpace;

/** Specify HTTP/HTTPS proxy credentials
 *
 * @param proxyCredentials <tt>NSURLCredential</tt> containing the username and
 *                    password.
*/
@property (strong, nullable) NSURLCredential* proxyCredentials;

/** Use default cookie handling within <tt>WKWebView</tt> instance.
*
* @param HTTPShouldHandleCookies <tt>BOOL</tt> A Boolean value that indicates whether the <tt>WKWebView</tt>
* instance should use the default cookie handling when making requests.
* <tt>YES</tt> if the request should use the default cookie handling or <tt>NO</tt> otherwise.
* The default is <tt>YES</tt> which means cookies are sent from and stored to the <tt>WKWebView</tt> instance.
*/
@property (nonatomic, assign) BOOL HTTPShouldHandleCookies;

@end

NS_ASSUME_NONNULL_END
