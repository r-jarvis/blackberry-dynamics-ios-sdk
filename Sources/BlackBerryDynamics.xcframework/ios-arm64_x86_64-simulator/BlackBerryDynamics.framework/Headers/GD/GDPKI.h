/*
 * Copyright 2023 BlackBerry Limited. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/** Certificate addition notification identifier.
 * 
 * Use this value to add an observer of additions to the BlackBerry Dynamics
 * X.509 certificate store.
 * 
 * @see \ref GDPKICertificate.
 */
extern NSString* const GDPKINotificationCertificateAdded;

/** Certificate removal notification identifier.
 * 
 * Use this value to add an observer of removals from the BlackBerry Dynamics
 * X.509 certificate store.
 * 
 * @see \ref GDPKICertificate.
 */
extern NSString* const GDPKINotificationCertificateRemoved;

/*!
 * \class GDPKICertificate GDPKI.h <BlackBerryDynamics/GD/GDPKI.h>
 * \brief X.509 Public Key Certificate.
 * 
 * \copydetails ssGDPKICertificate
 *
 * <h2>Public Key Infrastructure Integration</h2>
 * \copydetails ssGDPKIOverview
 * 
 * \snippets_intro
 * \snippet{Certificate Notification Observer}
 * \code
 * - (void)addCertificateObservers {
 *     [[NSNotificationCenter defaultCenter] addObserver:self
 *                                              selector:@selector(certificateAdded:)
 *                                                  name:GDPKINotificationCertificateAdded
 *                                                object:nil];
 *     [[NSNotificationCenter defaultCenter] addObserver:self
 *                                              selector:@selector(certificateRemoved:)
 *                                                  name:GDPKINotificationCertificateRemoved
 *                                                object:nil];
 * }
 *
 * - (void)certificateAdded:(NSNotification *)nsNotification {
 *     GDPKICertificate *gdPKICertificate = nsNotification.object;
 *     SecCertificateRef secCertificate =
 *         SecCertificateCreateWithData(NULL, gdPKICertificate.binaryX509DER);
 *     CFStringRef secCertificateSummary =
 *         SecCertificateCopySubjectSummary(secCertificate);
 *     NSLog(@"Certificate added. Serial Number: \"%s\", Summary:\"%s\".\n",
 *           gdPKICertificate.serialNumber, (NSString*)secCertificateSummary);
 *     CFRelease(secCertificateSummary);
 *     CFRelease(secCertificate);
 * }
 *
 * - (void)certificateRemoved:(NSNotification *)nsNotification {
 *     GDPKICertificate *gdPKICertificate = nsNotification.object;
 *   
 *     NSLog(@"Certificate removed. Serial Number: \"%@\".\n",
 *           gdPKICertificate.serialNumber );
 * }
 * \endcode
 * \divclass{bulletlists}
 * The above snippet shows:
 * - Registration for notification of certificate addition and removal. The
 *   observer code is specified by selector.
 * - Dummy implementation of the certificate added listener that:
 *   - Logs one field directly from the notification object, which is a
 *     BlackBerry Dynamics representation of a certificate.
 *   - Creates a native representation of the same certificate, and logs another
 *     field from it.
 *   .
 * - Dummy implementation of the certificate removed listener that logs one
 *   X.509 field.
 * .
 * \enddivclass
 * @see <a
 *          href="https://developer.apple.com/documentation/security/certificate_key_and_trust_services/certificates?language=objc"
 *          target="_blank"
 *      >Certificates reference documentation</a> on the apple.com developer
 *      website.
 */
@interface GDPKICertificate : NSObject

/** Initialize from binary DER encoded X.509 certificate data.
 * 
 * Call this function to initialize a new object from binary DER encoded X.509
 * certificate data.
 *
 * @param x509 <tt>NSData</tt> containing the binary DER encoded X.509 data.
 */
- (instancetype)initWithData:(NSData*)x509;

/** Binary DER encoded certificate data.
 * 
 * Binary DER encoded representation of the X.509 certificate data.
 */
@property (atomic, readonly) NSData *binaryX509DER;

/** X.509 version.
 * 
 * The X.509 version of the certificate.
 */
@property (atomic, readonly) NSInteger version;

/** X.509 Serial Number field.
 * 
 * Value of the X.509 Serial Number field of the certificate.
 */
@property (atomic, readonly) NSString *serialNumber;

/** X.509 Subject field.
 * 
 * Value of the X.509 Subject field of the certificate.
 */
@property (atomic, readonly) NSString *subjectName;

/** X.509 Subject Alternative Name field.
 * 
 * Value of the X.509 Subject Alternative Name field of the certificate.
 */
@property (atomic, readonly) NSString *subjectAlternativeName;

/** X.509 Issuer field.
 * 
 * Value of the X.509 Issuer field of the certificate.
 */
@property (atomic, readonly) NSString *issuer;

/** X.509 Validity: Not Before date and time.
 * 
 * Value of the X.509 Validity: Not Before date and time of the certificate.
 */
@property (atomic, readonly) NSDate *notBeforeDate;

/** X.509 Validity: Not After date and time.
 * 
 * Value of the X.509 Validity: Not After date and time of the certificate.
 */
@property (atomic, readonly) NSDate *notAfterDate;

/** X.509 Key Usage field.
 * 
 * Value of the X.509 Key Usage field of the certificate.
 */
@property (atomic, readonly) NSString *keyUsage;

@end

/*!
 * \class GDCredentialManagerUI GDPKI.h <BlackBerryDynamics/GD/GDPKI.h>
 * \brief Credentials Management User Interface
 *
 *  Use this interface to embed the Credentials Management UI within your app.
 */
@interface GDCredentialManagerUI : NSObject

/** View of assigned User Credential Profiles.
 *
 * Access this property when presenting a list of User Credential
 * profiles (UCPs) for the user to manage.  Only registered UCPs are shown if
 * assigned to this user. Call GDCredentialsProfile_register_type() to register each
 * UCP type of interest. For example:
 *
 * \code
 * // Import Obj-C APIs
 * #import <BlackBerryDynamics/GD/GD/GDPKI.h>
 *
 * // Include generic C APIs
 * #include <BlackBerryDynamics/GD/GD/GDCredentialsProfile.h>
 *
 * // Register device keystore UCPs so they show up when presenting
 * // the Credential Manager UI.
 * GDCredentialsProfile_register_type(GDCredentialsProfileTypeDeviceKeystore, NULL, NULL);
 *
 *  // Present the Credentials Manager UI.
 *  UIViewController* ucpViewController = GDCredentialManagerUI.rootViewController;
 *  [ucpViewController setModalPresentationStyle:UIModalPresentationCurrentContext];
 *  [self presentViewController:ucpViewController
 *                     animated:YES
 *                   completion:nil];
 * \endcode
 */
@property (class, atomic, readonly) UIViewController* rootViewController;

/** Return YES if there are profiles assigned to the user.
 *
 * Access this property if you do not want the user to navigate to the Credential
 * Manager when there are no applicable profiles assigned to the user.
 */
@property (class, atomic, readonly) BOOL profilesAssigned;

/** Return YES if there are one or more profiles that need user attention.
 *
 * Access this property if you want to alert the user that there is one or
 * more assigned profiles that require user attention. For example, if a
 * certificate has expired or is due for renewal.
 */
@property (class, atomic, readonly) BOOL profilesRequireAttention;

@end
