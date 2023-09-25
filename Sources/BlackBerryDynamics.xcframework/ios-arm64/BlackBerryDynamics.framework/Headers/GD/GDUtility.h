/*
 * Copyright 2023 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>

/** \defgroup jwtcallback BlackBerry Enterprise Identity JWT request callback
 * \{
 */

/** Status codes from BlackBerry Enterprise Identity JWT request.
 * 
 * These constants can be used for handling errors returned from JWT retrieval
 *
 * @see \ref GDUtility class reference.
 */

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BBDJWTStatusCode) {
    /** Request successful
     */
    BBDJWTStatusOK = 0,
    
    /** A general error occurred not covered by other status codes.
     */
    BBDJWTStatusUnknownError,
    
    /** MTD is not enabled (only for MTD related requests)
     */
    BBDJWTMTDNotEnabled,
    
    /** Server responded with an error.
     */
    BBDJWTServerError,
    
    /** Server not reachable or cannot establish a connection
     */
    BBDJWTServerUnreachable,
    
    /** Client is not authorised to make this request. For Zero Sign On (ZSO), a valid certificate is not enrolled.
     */
    BBDJWTAuthFailure,
    
    /** Server has not yet updated to accept a recently enrolled authorisation. Eg a ZSO is enrolled but not yet activated on the
     * server. This is temporary and can be retried.
     */
    BBDJWTPendingActivation
};
 
/** Completion Block definition for JWT retrieval
 *
 * @param JWT If successful an NSString object pointer containing the JWT. Empty otherwise.
 *
 * @param status A BBDJWTStatusCode value indicating the status of the request.
 *
 * @see BBDJWTStatusCode
 *
 * @param error An additional error parameter which may contain the HTTP status code of a server related failure, 0 on success.
 *
 */
typedef void (^BBDJWTCompletion)(NSString* JWT, BBDJWTStatusCode status, int error);
/** \}
 */

/*!
 * \protocol GDAuthTokenDelegate GDUtility.h <BlackBerryDynamics/GD/GDUtility.h>
 * \brief Delegate for handling the results of BlackBerry Dynamics authentication token requests.
 * 
 * \copydetails ssGDAuthTokenListener
 */
@protocol GDAuthTokenDelegate

/** Successful token request callback.
 * 
 * This callback will be invoked when a new BlackBerry Dynamics
 * authentication token has been generated. Token generation is always in
 * response to a call to the
 * \reflink GDUtility::getGDAuthToken:serverName: getGDAuthToken:serverName \endlink
 * function.
 *
 * The function that is invoked could initiate sending of the token to the
 * application server, out of band. The application server will then be able to
 * utilize the token to authenticate the end user.
 * 
 * @param gdAuthToken <tt>NSString</tt> containing the token.
 */
- (void)onGDAuthTokenSuccess:(NSString*)gdAuthToken;

/** Failed token request callback.
 * 
 * This callback will be invoked when a request for a BlackBerry
 * Dynamics authentication token has failed. Information about the error
 * condition is passed in a parameter.
 * 
 * The request will have been made by calling the
 * \reflink GDUtility::getGDAuthToken:serverName: getGDAuthToken:serverName \endlink
 * function.
 *
 * Invocation of this callback notifies the application that a token wasn't
 * issued in response to the request.
 *
 * Depending on the reason for failure, the function that is invoked could:
 * - Retry, by requesting a token again.
 * - Notify the user that this authentication mechanism isn't available.
 * .
 *
 * @param authTokenError <tt>NSError</tt> describing the error condition that
 *                       led to the failure of the token request.
 *
 * @see \ref gdauthtokendomain
 */
- (void)onGDAuthTokenFailure:(NSError*) authTokenError;

@end

/*!
 * \class GDUtility GDUtility.h <BlackBerryDynamics/GD/GDUtility.h>
 * \brief BlackBerry Dynamics utility for managing authentication tokens and identity.
 * 
 * \copydetails ssGDAuthToken
 * \copydetails ssSharedUserId
 */
@interface GDUtility : NSObject

/** BlackBerry Dynamics authentication token request.
 * 
 * Call this function to request a new BlackBerry Dynamics
 * authentication token. Pass the challenge string and server name as
 * parameters.
 *
 * See under BlackBerry Dynamics Authentication Token Mechanism, above, for
 * background on tokens and the challenge string.
 * 
 * This function requests a BlackBerry Dynamics authentication token from
 * the BlackBerry Dynamics runtime. The runtime might connect to the BlackBerry
 * Dynamics infrastructure installed at the enterprise in order to service the
 * request.
 * 
 * The request is asynchronous. If the request succeeds, the token will be
 * passed to the \reflink GDAuthTokenDelegate::onGDAuthTokenSuccess: onGDAuthTokenSuccess \endlink callback in the
 * delegate. If the attempt fails, an error will
 * be passed to the \reflink GDAuthTokenDelegate::onGDAuthTokenFailure: onGDAuthTokenFailure \endlink callback in
 * the delegate instead.
 *
 * The <tt>delegate</tt> property must be set before this function is
 * called.
 *
 * @param challenge <tt>NSString</tt> containing the challenge string for the token.
 *                  The challenge string can be empty.
 *
 * @param serverName <tt>NSString</tt> containing additional identification, by
 *                   convention the fully qualified domain name of the
 *                   application server for which a token is being requested.
 *                   Whatever value is passed here will also be returned to the
 *                   server as part of the token validation response.
 *
 */
- (void)getGDAuthToken: (NSString*) challenge serverName:(nullable NSString*) serverName;

/** Get User Dynamics Shared identifier.
 *
 * 
 * Call this method to get a BlackBerry Dynamics shared user identifier.
 *
 * See under BlackBerry Dynamics Shared User Identifier, above, for
 * background on shared id usage and characteristics.
 *
 * If calculation of shared id is not possible, empty string will be returned
 *
 * \return Shared Id String
 */
- (NSString *)getDynamicsSharedUserIDWithError:(NSError **)error;

/** Get JWT from BlackBerry Enterprise Identity (EID) server
 *
 * Call this function to request a BlackBerry Enterprise Identity
 * JWT Bearer Token for authentication purposes. Pass a registered client ID string, scope
 * string and closure reference (for calling back) as parameters. Tokens are cached
 * until expired, but a new token from the server may be specified by setting the refresh flag true.
 *
 * This function requests a BlackBerry Dynamics JWT from
 * the BlackBerry Dynamics runtime. The runtime might connect to the BlackBerry
 * Dynamics infrastructure installed at the enterprise in order to service the
 * request.
 *
 * The request is asynchronous.
 *
 * @param clientID <tt>NSString</tt> containing the client ID.
 *
 * @param scope <tt>NSString</tt> the scope for the token.
 *
 * @param resourceServer <tt>NSString</tt> optional resource server specifier (not currently used)
 *
 *
 * @param refresh A flag to force a new token to be fetched from the server.
 *
 * @param callback block of type \ref BBDJWTCompletion, void (^BBDJWTCompletion)(NSString* JWT, BBDJWTStatusCode status, int error);
 *
 * @param error Optional pointer to NSError object which may contain further information.
 *
 */
- (BOOL) getEIDToken:(NSString *) clientID withScope:(NSString*) scope withResourceServer:(NSString*) resourceServer withRefresh:(BOOL) refresh withCompletion:(BBDJWTCompletion) callback withError:(NSError**) error;

/** Delegated event-handling.
 * 
 * BlackBerry Dynamics authentication token requests are asynchronous. When a
 * request succeeds or fails, a callback in the application code is invoked by
 * the BlackBerry Dynamics runtime.
 * 
 * Set this property to an instance of a class in the application that contains
 * the code for the required callbacks, i.e. a class that implements
 * the GDAuthTokenDelegate protocol.
 */
@property (nullable, weak, getter = getGDAuthDelegate, setter = setGDAuthDelegate:) id<GDAuthTokenDelegate> gdAuthDelegate;


@end

/**
 * \defgroup gdauthtokendomain BlackBerry Dynamics authentication token error domain
 * These constants can be used when handling BlackBerry Dynamics authentication
 * token request errors, in a \reflink GDAuthTokenDelegate GDAuthTokenDelegate \endlink
 * implementation.
 *
 * \{
 */

/** Error domain for the BlackBerry Dynamics authentication token mechanism.
 */
extern NSString* const GDAuthTokenDomain;


typedef NS_ENUM(NSInteger, GDAuthTokenError)
{
    /** The BlackBerry Dynamics server software installed at the enterprise
     * doesn't support the authentication token mechanism.
     */
    GDAuthTokenErrNotSupported = -2,
    
    /** An error occurred during token generation or communication.
     * 
     * Sending the same request later mightn't encounter the same condition, and
     * could succeed.
     */
    GDAuthTokenErrRetry         = -1,
    
};

/** \}
 */

NS_ASSUME_NONNULL_END
