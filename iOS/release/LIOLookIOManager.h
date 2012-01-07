//
//  LIOLookIOManager.h
//  LookIO
//
//  Created by Joseph Toscano on 8/19/11.
//  Copyright (c) 2011 LookIO, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

UIImage *lookioImage(NSString *path);

@class LIOLookIOManager;

@protocol LIOLookIOManagerDelegate
@optional
- (UIWindow *)lookIOManagerMainWindowForHostApp:(LIOLookIOManager *)aManager;
- (BOOL)lookIOManager:(LIOLookIOManager *)aManager shouldRotateToInterfaceOrientation:(UIInterfaceOrientation)anOrientation;
- (void)lookIOManager:(LIOLookIOManager *)aManager didUpdateEnabledStatus:(BOOL)lookioIsEnabled;
@end

@interface LIOLookIOManager : NSObject

@property(nonatomic, retain) UIImage *touchImage;
@property(nonatomic, retain) NSString *targetAgentId;
@property(nonatomic, assign) BOOL usesTLS, usesSounds;
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