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
 * Call this function to request reset of all the application's
 * connections to the BlackBerry Dynamics infrastructure. The BlackBerry
 * Dynamics runtime generally connects and reconnects to the infrastructure as
 * needed and so there should be no need to call this function in normal
 * operation.
 *
 * @return <tt>YES</tt> if the reset request was accepted and put in progress.
 * @return <tt>NO</tt> otherwise.
 */
+ (BOOL)forceResetAllConnections;

@end
