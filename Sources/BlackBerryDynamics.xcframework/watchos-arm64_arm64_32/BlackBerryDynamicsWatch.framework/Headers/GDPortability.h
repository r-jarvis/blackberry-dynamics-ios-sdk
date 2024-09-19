/*
 * (c) 2021 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#if defined(__APPLE__)

/** @file GDPortability.h Portability preprocessor macros and utility methods.
 * 
 * This file has a number of preprocessor macros and utility methods that enable
 * the BlackBerry Dynamics Software Development Kit (SDK) products for iOS and
 * macOS to make use of newer features of the corresponding native SDKs whilst
 * maintaining backward compatibility.
 *
 * Some examples of these newer features are:
 * - Nullability.
 * - Generics.
 * - API availability.
 * .
 * 
 * More comments can be found in the source .h file.
 */

#include <Availability.h>
#import <Foundation/Foundation.h>

#if defined(__OBJC__) && defined(__cplusplus)

namespace GD {
    
    /* NSObject type cast function template.
     * This template validates an instance of an NSObject subclass can be type
     * cast to another NSObject subclass prior to performing the cast.
     * Useage: NSCheckedCast<CastT>(arg) to cast 'arg' to type 'CastT'
     */
    template <typename CastT, typename ArgT>
    static inline CastT* NSCheckedCast(ArgT arg) {
        if (!arg || [arg isKindOfClass:[CastT class]]) {
            return (CastT*)arg;
        } else {
            @throw [NSException exceptionWithName:NSGenericException reason:[NSString stringWithFormat:@"%@ is not of type %@", arg, NSStringFromClass([CastT class])] userInfo:nil];
        }
    }
    
    template <typename CastT, typename ArgT>
    static inline CastT* CFCheckedCast(ArgT arg) {
        if (!(__bridge CastT)arg || [(__bridge CastT)arg isKindOfClass:[CastT class]]) {
            return (__bridge CastT*)arg;
        } else {
            @throw [NSException exceptionWithName:NSGenericException reason:[NSString stringWithFormat:@"%@ is not of type %@", (__bridge CastT*)arg, NSStringFromClass([CastT class])] userInfo:nil];
        }
    }
}

#endif // __OBJC__

#endif


