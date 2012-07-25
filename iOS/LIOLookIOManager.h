//  
//  LIOLookIOManager.h
//  LookIO iOS Remote Support Client v152
//  
//  Copyright 2011-2012 LookIO, Inc. All rights reserved.
//  
//  This header file is for use with LookIO.
//  Documentation and support: http://support.look.io/

#import <UIKit/UIKit.h>

#define LOOKIO_VERSION_STRING @"152"

@class LIOLookIOManager;

@protocol LIOLookIOManagerDelegate
@optional
- (UIWindow *)lookIOManagerMainWindowForHostApp:(LIOLookIOManager *)aManager;
- (BOOL)lookIOManager:(LIOLookIOManager *)aManager shouldRotateToInterfaceOrientation:(UIInterfaceOrientation)anOrientation;
- (void)lookIOManager:(LIOLookIOManager *)aManager didUpdateEnabledStatus:(BOOL)lookioIsEnabled;
- (void)lookIOManagerDidHideControlButton:(LIOLookIOManager *)aManager;
- (void)lookIOManagerDidShowControlButton:(LIOLookIOManager *)aManager;
@end

@interface LIOLookIOManager : NSObject

@property(nonatomic, retain) UIImage *touchImage;
@property(nonatomic, retain) NSString *targetAgentId;
@property(nonatomic, assign) BOOL usesTLS;
@property(nonatomic, retain) UIWindow *mainWindow;
@property(nonatomic, readonly) BOOL enabled;
@property(nonatomic, assign) id<LIOLookIOManagerDelegate> delegate;

+ (LIOLookIOManager *)sharedLookIOManager;
- (void)performSetupWithDelegate:(id<LIOLookIOManagerDelegate>)aDelegate;
- (void)recordCurrentUILocation:(NSString *)aLocationString;
- (void)beginSession;
- (void)setSessionExtra:(id)anObject forKey:(NSString *)aKey;
- (id)sessionExtraForKey:(NSString *)aKey;
- (void)addSessionExtras:(NSDictionary *)aDictionary;
- (void)clearSessionExtras;

@end
