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
 * Use constants in this enumeration to indicate the type of analytics event being recorded. 
* The methods BlackBerryAnalytics.trackFeatureEvent and BlackBerryAnalytics.trackApplicationEvent always require one of these eventTypes. 
 */
typedef NS_ENUM(NSUInteger, BAFAnalyticsEvent) {
    /**
     * Record the start of an event which has a specific end point. 
     */
    BAFFeatureActive = 1000,
    
    /**
     * Record the end of an event which has a specific start point.
     */
    BAFFeatureInactive = 1001,
    
    /**
     * Record events or actions which occur in your application.
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
 * Call to record an event that has a start point (a "feature active event") followed by a stop point 
* (a "feature inactive event"). The start and stop points provide a period of time where the feature was active. 
* This type of event is typically used to measure user engagement of app features. The name that is used to 
* track a feature must be unique within the app.
 *
 * @param event         BAFAnalyticsEvent specifies the type of event. For example, <tt>FEATURE_ACTIVE</tt> or <tt>FEATURE_INACTIVE</tt>.
 * @param featureName   <tt>NSString</tt> containing the name of the feature for a given event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackFeatureEvent:(BAFAnalyticsEvent)event
          withFeatureName:(NSString *_Nonnull)featureName
               completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

/**
 * Record adoption events to analyse the frequency of specific user actions or events. 
 *
 * Call to record an event which occurs in your application. An adoption event has two attributes, key and value. 
* The key must be unique within the app, and the value is a count of the number of times a specific event occurs (for example,
* an event key called "Emails deleted" that tracks the number of emails deleted by a user). The adoption event value should be the 
* string representation of the integer count. An app can combine events and record a single event.
 *
 * @param event         AnalyticsEvent specifies the type of event. In this case use <tt>ADOPTION_EVENT</tt>.
 * @param eventValue    <tt>NSString</tt> containing the event value to record for the given event key.
 * @param eventKey      <tt>NSString</tt> to define the name of the event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackApplicationEvent:(BAFAnalyticsEvent)event
                    withValue:(NSString *_Nonnull)eventValue
                       forKey:(NSString *_Nonnull)eventKey
                   completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

@end
