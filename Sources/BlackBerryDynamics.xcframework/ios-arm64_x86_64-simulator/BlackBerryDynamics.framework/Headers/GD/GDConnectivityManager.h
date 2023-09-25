/*
 * Copyright 2023 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>

/*!
 * \class GDConnectivityManager GDConnectivityManager.h <BlackBerryDynamics/GD/GDConnectivityManager.h>
 * \brief BlackBerry Dynamics infrastructure connection management.
 * 
 * \copydetails ssGDConnectionManagement
 */
@interface GDConnectivityManager : NSObject

/** Reset the BlackBerry Dynamics infrastructure connection.
 * 
 * \copydetails ssGDConnectionManagementForceResetAllConnections
 */
+ (BOOL)forceResetAllConnections;

@end
