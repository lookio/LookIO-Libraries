//  
//  LIOLookIOManager.h
//  LookIO iOS Remote Support Client v234
//  
//  Copyright 2011-2012 LivePerson, Inc. All rights reserved.
//  
//  This header file is for use with LookIO.
//  Documentation and support: http://support.look.io/

#import <UIKit/UIKit.h>

#define LOOKIO_VERSION_STRING @"234"

/*
 * Plugin flow for creating and sending content:
 * ---------------------------------------------
 * 1) Host registers plugin (a class conforming to LIOPlugin) using registerPlugin:.
 * 2) LookIO asks plugin for info necessary to add button(s) to attachment action sheet.
 * 3) LookIO asks plugin for a UIViewController instance which is then presented modally.
 * 4) Plugin tells LookIO that it's done/canceled via delegate. If done, a key string is
 *    returned to LookIO.
 * 5) LookIO asks plugin for a content thumbnail to be displayed in conversation flow.
 * 6) If user taps bubble, LookIO asks plugin for a UIViewController instance which is
 *    then presented modally in order to display the custom plugin content to the user.
 * 7) Plugin tells LookIO via delegate when it's done displaying content.
 */
@protocol LIOPlugin;

@protocol LIOPluginDelegate <NSObject>
- (void)plugin:(id<LIOPlugin>)aPlugin didFinishChoosingContentWithResultKey:(NSString *)aKey;
- (void)pluginDidCancelChoosingContent:(id<LIOPlugin>)aPlugin;
- (void)pluginDidFinishDisplayingContent;
@end

@protocol LIOPlugin <NSObject>
- (NSString *)pluginId; // Must be a unique string.
- (NSArray *)pluginButtonLabels; // e.g. "Take Photo", "Choose Existing"
- (UIViewController *)viewControllerForPluginButtonIndex:(NSInteger)anIndex;
- (UIView *)thumbnailViewForPluginContentWithKey:(NSString *)aKey;
- (UIViewController *)viewControllerForDisplayingPluginContentWithKey:(NSString *)aKey;
- (void)resetPluginState;
@property(nonatomic, assign) id<LIOPluginDelegate> pluginDelegate;
@end

@class LIOLookIOManager;

@protocol LIOLookIOManagerDelegate
@optional
- (UIWindow *)lookIOManagerMainWindowForHostApp:(LIOLookIOManager *)aManager;
- (BOOL)lookIOManager:(LIOLookIOManager *)aManager shouldRotateToInterfaceOrientation:(UIInterfaceOrientation)anOrientation;
- (BOOL)lookIOManagerShouldAutorotate:(LIOLookIOManager *)aManager;
- (NSInteger)lookIOManagerSupportedInterfaceOrientations:(LIOLookIOManager *)aManager;
- (void)lookIOManager:(LIOLookIOManager *)aManager didUpdateEnabledStatus:(BOOL)lookioIsEnabled;
- (void)lookIOManagerDidHideControlButton:(LIOLookIOManager *)aManager;
- (void)lookIOManagerDidShowControlButton:(LIOLookIOManager *)aManager;
- (id)lookIOManager:(LIOLookIOManager *)aManager linkViewForURL:(NSURL *)aURL;
@end

@interface LIOLookIOManager : NSObject

@property(nonatomic, retain) UIImage *touchImage;
@property(nonatomic, retain) NSString *targetAgentId;
@property(nonatomic, retain) UIWindow *mainWindow;
@property(nonatomic, readonly) BOOL enabled, sessionInProgress;
@property(nonatomic, assign) id<LIOLookIOManagerDelegate> delegate;

+ (LIOLookIOManager *)sharedLookIOManager;
- (void)performSetupWithDelegate:(id<LIOLookIOManagerDelegate>)aDelegate;
- (void)setUILocation:(NSString *)aLocationString;
- (void)setSkill:(NSString *)aRequiredSkill;
- (void)beginSession;
- (void)setSessionExtra:(id)anObject forKey:(NSString *)aKey;
- (id)sessionExtraForKey:(NSString *)aKey;
- (void)addSessionExtras:(NSDictionary *)aDictionary;
- (void)clearSessionExtras;
- (BOOL)registerPlugin:(id<LIOPlugin>)aPlugin;

@end
