/*
 * Copyright © 2024 BlackBerry Limited. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * \class GTLCommonSettingsCellConfiguration GTLCommonSettingsCellConfiguration.h <BlackBerryDynamics/GD/GTLCommonSettingsCellConfiguration.h>
 * \brief Configuration API to configure Launcher Common settings section table view cells styles.
 *
 * Configure the style of the common or default options shown in the settings menu. This includes the menu items to 'Change Password, 'Upload Logs' and
 * to configure the size of the launcher icon.
 * 
 * A host application can configure styles for common settings section by creating instance of this class and returning it in 
 * <tt>`GTLauncherViewControllerDelegate commonSettingsCellConfigurationForType:launcherViewController:`</tt>of the GTLauncherViewControllerDelegate
 * method:
 * \code
 * - (GTLCommonSettingsCellConfiguration *)commonSettingsCellConfigurationForType:(GTLCommonSettingsCellType)cellType
 *                                                         launcherViewController:(GTLauncherViewController *)controller {
 *       GTLCommonSettingsCellConfiguration *style = [GTLCommonSettingsCellConfiguration defaultConfigurationForType:cellType];
 *
 *       // Do updates
 *       
 *       return style;
 *   }
 * \endcode
 */
OBJC_EXPORT
@interface GTLCommonSettingsCellConfiguration : NSObject

/**
 * The type of common settings cell used by common settings section
 */
typedef enum {
    /// Cell type that represents 'Change Password' item
    GTLCommonSettingsCellTypeChangePassword = 1,
    /// Cell type that represents 'Launcher' item
    GTLCommonSettingsCellTypeLauncher,
    /// Cell type that represents 'Upload Logs' item
    GTLCommonSettingsCellTypeUploadLogs
} GTLCommonSettingsCellType;


/// Cell background color. Default is `nil`: system default color will be used.
@property (nonatomic, strong, nonnull) UIColor *backgroundColor;
/// Setting name text color. Default is black.
@property (nonatomic, strong, nonnull) UIColor *textColor;
/// Setting name text font. Default is ``UIFontTextStyleBody`` font.
@property (nonatomic, strong, nonnull) UIFont *textFont;
/// Icon to be displayed to the left of  setting name text, by default it is `nil`, no icon will be displayed.
@property (nonatomic, strong, nullable) UIImage *icon;
/// Tint color for icon, by default it is `nil`, no tint will be applied. Has no effect when `icon` is `nil`.
@property (nonatomic, strong, nullable) UIColor *iconTintColor;
/// Table view cell accessory type to be displayed on the right, by default is ``UITableViewCellAccessoryNone``.
@property (nonatomic, assign) UITableViewCellAccessoryType accessoryType;
/// Content left margin delta. This might be needed to align custom table view cells with Common settings table view cells. By default is `0`.
@property (nonatomic, assign) CGFloat leftMarginDelta;
/// Table view cell accessory view, by default is nil
@property (nonatomic, strong, nullable) UIView *accessoryView;

/** Provides ability to get the default style for provided table view cell type.
 * 
 * This method provides ability to get the default style for provided table view cell type. Useful in the case a style update is needed only to the font 
 * or color for a particular table view cell type.
 * @param type @p GTLCommonSettingsCellType  type of cell.
 * @return @p GTLCommonSettingsCellConfiguration default style for provided table view cell type.
 */
+ (GTLCommonSettingsCellConfiguration *)defaultConfigurationForType:(GTLCommonSettingsCellType)type;

@end

NS_ASSUME_NONNULL_END
