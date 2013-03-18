//  
//  LIOLookIOManager.h
//  LivePerson iOS Remote Support Client v273
//  
//  Copyright 2011-2013 LivePerson, Inc. All rights reserved.
//  
//  This header file is for use with LivePerson Mobile.
//  Documentation and support: http://support.look.io/

#import <UIKit/UIKit.h>

#define LOOKIO_VERSION_STRING @"273"

// Event constants.
// Use these with the "reportEvent" methods.
extern NSString *const kLPEventConversion;
extern NSString *const kLPEventPageView;
extern NSString *const kLPEventSignUp;
extern NSString *const kLPEventSignIn;
extern NSString *const kLPEventAddedToCart;

@class LIOLookIOManager;
@protocol LIOPlugin;

@protocol LIOLookIOManagerDelegate
@optional
- (void)lookIOManager:(LIOLookIOManager *)aManager didUpdateEnabledStatus:(BOOL)lookioIsEnabled;
- (void)lookIOManagerDidHideControlButton:(LIOLookIOManager *)aManager;
- (void)lookIOManagerDidShowControlButton:(LIOLookIOManager *)aManager;
- (void)lookIOManagerDidEndChat:(LIOLookIOManager *)aManager;
- (id)lookIOManager:(LIOLookIOManager *)aManager linkViewForURL:(NSURL *)aURL;

// The following delegate methods should only be used when
// troubleshooting UI / general integration issues.
- (UIWindow *)lookIOManagerMainWindowForHostApp:(LIOLookIOManager *)aManager;
- (BOOL)lookIOManager:(LIOLookIOManager *)aManager shouldRotateToInterfaceOrientation:(UIInterfaceOrientation)anOrientation;
- (BOOL)lookIOManagerShouldAutorotate:(LIOLookIOManager *)aManager;
- (NSInteger)lookIOManagerSupportedInterfaceOrientations:(LIOLookIOManager *)aManager;
@end

@interface LIOLookIOManager : NSObject

@property(nonatomic, readonly) BOOL enabled;
@property(nonatomic, readonly) BOOL chatInProgress;
@property(nonatomic, retain) UIWindow *mainWindow;
@property(nonatomic, assign) id<LIOLookIOManagerDelegate> delegate;

+ (LIOLookIOManager *)sharedLookIOManager;
- (void)performSetupWithDelegate:(id<LIOLookIOManagerDelegate>)aDelegate;
- (void)beginChat;
- (void)setSkill:(NSString *)aRequiredSkill;
- (void)reportEvent:(NSString *)anEvent;
- (void)reportEvent:(NSString *)anEvent withData:(id<NSObject>)someData;
- (void)setCustomVariable:(id)anObject forKey:(NSString *)aKey;
- (id)customVariableForKey:(NSString *)aKey;
- (void)addCustomVariables:(NSDictionary *)aDictionary;
- (void)clearCustomVariables;

// Deprecated methods.
- (void)beginSession DEPRECATED_ATTRIBUTE;
- (void)setSessionExtra:(id)anObject forKey:(NSString *)aKey DEPRECATED_ATTRIBUTE;
- (id)sessionExtraForKey:(NSString *)aKey DEPRECATED_ATTRIBUTE;
- (void)addSessionExtras:(NSDictionary *)aDictionary DEPRECATED_ATTRIBUTE;
- (void)clearSessionExtras DEPRECATED_ATTRIBUTE;

@end
