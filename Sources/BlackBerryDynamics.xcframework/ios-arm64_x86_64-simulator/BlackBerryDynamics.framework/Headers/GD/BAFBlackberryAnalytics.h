/*
 * Copyright 2023 BlackBerry Limited. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

/**
 * Invoked when the track event operation completes (optional).
 *
 * @param error The BAFAnalyticsResponse error returned if the operation fails.
 */
typedef void (^BAFAnalyticsResponseCompletion)(NSError *__nullable error) API_AVAILABLE(ios(9.0));

/** Analytics Event Type.
 * \copydetails ssAnalyticsEventType
 */
typedef NS_ENUM(NSUInteger, BAFAnalyticsEvent) {
    /**
     * \copydetails ssAnalyticsFeatureActive 
     */
    BAFFeatureActive = 1000,
    
    /**
     * \copydetails ssAnalyticsFeatureInActive
     */
    BAFFeatureInactive = 1001,
    
    /**
     * \copydetails ssAnalyticsFeatureAdoption
     */
    BAFAdoptionEvent = 1002,
};

/*!
 * \class BAFBlackberryAnalytics BAFBlackberryAnalytics.h <BlackberryDynamics/GD/BAFBlackberryAnalytics.h>
 * \brief Class for BlackBerry Analytics
 * \copydetails ssAnalytics 
 * 
 */
@interface BAFBlackberryAnalytics : NSObject


/**
 * Record feature events to analyse the period a specific app feature is used. 
 *
 * \copydetails ssAnalyticsFeatureEvent
 *
 * @param event         BAFAnalyticsEvent specifies the type of event. For example, <tt>FEATURE_ACTIVE</tt> or <tt>FEATURE_INACTIVE</tt>.
 * @param featureName   \ss_string containing the name of the feature for a given event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackFeatureEvent:(BAFAnalyticsEvent)event
          withFeatureName:(NSString *_Nonnull)featureName
               completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

/**
 * Record adoption events to analyse the frequency of specific user actions or events. 
 *
 * \copydetails ssAnalyticsAdoptionEvent
 *
 * @param event         AnalyticsEvent specifies the type of event. In this case use <tt>ADOPTION_EVENT</tt>.
 * @param eventValue    \ss_string containing the event value to record for the given event key.
 * @param eventKey      \ss_string to define the name of the event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackApplicationEvent:(BAFAnalyticsEvent)event
                    withValue:(NSString *_Nonnull)eventValue
                       forKey:(NSString *_Nonnull)eventKey
                   completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

@end
