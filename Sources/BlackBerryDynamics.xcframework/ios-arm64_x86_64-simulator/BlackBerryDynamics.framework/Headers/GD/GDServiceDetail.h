/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 * 
 */

#pragma once

#import <Foundation/Foundation.h>
#import <BlackBerryDynamics/GD/GDServiceProvider.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <BlackBerryDynamics/GD/GDiOS.h>
#else
#import <BlackBerryDynamics/GD/GDMac.h>
#endif

NS_ASSUME_NONNULL_BEGIN



/** Details of a provided service.
 * 
 * This class is used to return information about a provided service. The
 * <tt>services</tt> property of a \ss_class_link{GDServiceProvider} object is a
 * collection of instances of this class.
 */
@interface GDServiceDetail : NSObject

/** Initializer.
 *
 * The initializer is provided for completeness. In general, there is no need
 * for the application code to create instances of this class.
 */
- (instancetype)initWithService:(NSString*)identifier
                     andVersion:(NSString*)version
                 andServiceType:(GDServiceType)type;

/** BlackBerry Dynamics service identifier.
 */
@property (nonatomic, strong, readonly) NSString* identifier;

/** BlackBerry Dynamics service version.
 */
@property (nonatomic, strong, readonly) NSString* version;

/** Indicator of the type of the provided service, either application-based or
 *  server-based.
 */
@property (nonatomic, assign, readonly) GDServiceType serviceType;


@end
NS_ASSUME_NONNULL_END
