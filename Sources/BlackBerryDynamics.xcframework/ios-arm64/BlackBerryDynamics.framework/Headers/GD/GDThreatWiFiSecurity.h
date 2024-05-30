/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <BlackBerryDynamics/GD/GDThreat.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Determine whether networking is subject to man in the middle attack.
 */
@interface BBDThreatWiFiSecurity : BBDThreat

/**
 * Creates an instance of BBDThreatWiFiSecurity.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Indicate the type of mitm threat.
 *
 * Indicate the specific type of mitm threat.
 *
 * @return NSString.
 */
- (NSString*)getSSID;

- (BBDThreatLevel)getWiFiThreatLevel;

@end

NS_ASSUME_NONNULL_END
