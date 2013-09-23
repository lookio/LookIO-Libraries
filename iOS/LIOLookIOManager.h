//  
//  LIOLookIOManager.h
//  LivePerson iOS Remote Support Client v357
//  
//  Copyright 2011-2013 LivePerson, Inc. All rights reserved.
//  
//  This header file is for use with LivePerson Mobile.
//  Documentation and support: https://community.liveperson.com/docs/DOC-2062

#import <UIKit/UIKit.h>

#define LOOKIO_VERSION_STRING @"357"

// Event constants.
// Use these with the "reportEvent" methods.
extern NSString *const kLPEventConversion;
extern NSString *const kLPEventPageView;
extern NSString *const kLPEventSignUp;
extern NSString *const kLPEventSignIn;
extern NSString *const kLPEventAddedToCart;

// Collaboration component constants.
// Return these via the "lookIOManagerEnabledCollaborationComponents:" delegate method.
#define kLPCollaborationComponentNone   0
#define kLPCollaborationComponentPhoto  1

@class LIOLookIOManager;
@protocol LIOPlugin;

@protocol LIOLookIOManagerDelegate
@optional

///---------------------------------------------------------------------------------------
/// @name Status Methods
///---------------------------------------------------------------------------------------

/*!
 Called whenever chat is enabled or disabled due to a change in your agents’ availability status, when chat is directly
 disabled, or any other reason. This status can be used to reflect the new availability status in your app’s UI.
 
 @param aManager The LIOLookIOManager shared instance.
 @param lookioIsEnabled Live Chat's newly updated enabled status.
 */
- (void)lookIOManager:(LIOLookIOManager *)aManager didUpdateEnabledStatus:(BOOL)lookioIsEnabled;

/*!
 Called whenever LP mobile hides its own control "Live Chat" tab/button.
 
 @param aManager The LIOLookIOManager shared instance.
 */
- (void)lookIOManagerDidHideControlButton:(LIOLookIOManager *)aManager;

/*!
 Called whenever LP mobile shows its own control "Live Chat" tab/button.
 
 @param aManager The LIOLookIOManager shared instance.
 */
- (void)lookIOManagerDidShowControlButton:(LIOLookIOManager *)aManager;

/*!
 Called whenever a chat session has ended.
 
 @param aManager The LIOLookIOManager shared instance.
 */
- (void)lookIOManagerDidEndChat:(LIOLookIOManager *)aManager;

///---------------------------------------------------------------------------------------
/// @name Customization Methods
///---------------------------------------------------------------------------------------

/*!
 Implement this method to provide a custom view for URLs sent by your agents during live chat. 
 
 LPMobile supports showing inline buttons for your app's registered custom URL schemes. For 
 example your app may have the scheme "myapp" registered for sending the user to a specific
 product page. An example URL for this purpose might look like this: "myapp://product/42". 
 These URLs can be sent from the agent to the client and the client will display them as inline 
 buttons in the conversation. By default, the buttons will display the raw URL. However, this 
 is rarely desirable, so you have the option to provide a custom view for each link. 
 For example, you may want the button to include a small image of the product in question or the
 name of the product.
 
 @return The object which will be used a custom view for the URL. You are allowed to return a
 UIView object or NSString. If you return a simple NSString, this string will be displayed in a 
 button in place of the URL. If you return a UIView, the entire UIView will be used in place of the 
 URL. Please note that the frame of the UIView you pass may be adjusted to fit inside the conversation
 bubble.  When the user clicks on the button, a standard openURL call is made on the shared UIApplication
 instance. This results in a standard delegate call being made to your application delegate, such as: 
 "application:openURL:sourceApplication:annotation:". Consult the official iOS documentation for
 more information on handling URL requests in your app.
 
 @param aManager The LIOLookIOManager shared instance.
 @param aURL The URL for which the custom link view should be returned.
 */

- (id)lookIOManager:(LIOLookIOManager *)aManager linkViewForURL:(NSURL *)aURL;

/*!
 Implement this method to specify which collaboration components you would like to enable for 
 Live Chat in your app, such as photo sharing. Collaboration components are disabled by default.
 
 @return Constant representing the collaboration component you would like to enable.
 Return the constant kLPCollaborationComponentPhoto to enable photo sharing.
 Return the constant kLPCollaborationComponentNone to disable all collaboration components.
 
 @param aManager The LIOLookIOManager shared instance.
 */

- (UInt32)lookIOManagerEnabledCollaborationComponents:(LIOLookIOManager *)aManager;

/*!
 Implement this method to specify your own branding image to be used within Live Chat, replacting the default LP Mobile
 logo.
 
 @return The image that should be used for custom branding.
 
 @param aManager The LIOLookIOManager shared instance.
 @param dimensions The ideal dimensions of the image to be used to custom branding. If you pass an image that is
 not of these optimal dimensions, LP Mobile will use the UIViewContentModeScaleAspectFit content mode to display the image.
 The optimal image size is 130x44 points for iPad, and 240x17 points for iPhone.
 */

- (UIImage*)lookIOManager:(LIOLookIOManager*)aManager brandingImageForDimensions:(CGSize)dimensions;

/*!
 Implement this method to specify if a custom action should be performed when a user starts a Live Chat, but
 no agents are available to answer the chat.
 
 This allows you to define any sort of custom action or message to be performed or displayed when no agents are
 available. When this method is not implemented or a NO value is returned, an offline survey will be displayed to the 
 user. If a custom offline survey was specified in the LP Admin Console it will be used, and if not a default offline
 survey will be used.
 
 @return A boolean value specifying if a custom action should be performed when no agents are available.
 
 @param aManager The LIOLookIOManager shared instance. 
 
 @see lookIOManagerCustomActionForChatNotAnswered:
 */

-(BOOL)lookIOManagerShouldUseCustomActionForChatNotAnswered:(LIOLookIOManager *)aManager;

/*!
 Implement this method to specify the custom action to be performed when a user starts a Live Chat, but
 no agents are available to answer the chat. This method will only be called if you have implemented 
 lookIOManagerUseCustomActionForChatNotAnswered: and are returning a value of YES.
 
 @param aManager The LIOLookIOManager shared instance.
 
 @see lookIOManagerShouldUseCustomActionForChatNotAnswered:
 */

-(void)lookIOManagerCustomActionForChatNotAnswered:(LIOLookIOManager *)aManager;

///---------------------------------------------------------------------------------------
/// @name Troubleshooting / UI Integration Methods
///---------------------------------------------------------------------------------------

// The following delegate methods should only be used when
// troubleshooting UI / general integration issues.

/*!
 Implement this method to return a pointer to your app's main UIWindow instance. This can help with integration 
 issues caused when the LP Mobile library is unable to locate this window independently.
 
 @return The main window of your app.
 
 @param aManager The LIOLookIOManager shared instance.
 */

- (UIWindow *)lookIOManagerMainWindowForHostApp:(LIOLookIOManager *)aManager;

/*!
 Like the UIViewController method with the same name, implement this method to control whether or not LookIO’s 
 view controllers should autorotate its interface elements at any given time. This method will be called for apps 
 running on various versions of iOS 5.0 and iOS 4.0
 
 @return Value specifying whether LP Mobile should rotate to the given interface orientation.
 
 @param aManager The LIOLookIOManager shared instance.
 @param anOrientation The orientation of the app’s user interface after the rotation. The possible values are described in UIInterfaceOrientation.

 */
- (BOOL)lookIOManager:(LIOLookIOManager *)aManager shouldRotateToInterfaceOrientation:(UIInterfaceOrientation)anOrientation;

/*!
 Like the UIViewController method with the same name, use this method to control whether or not LookIO’s view 
 controllers should autorotate its interface elements at any given time. This method will be called for apps 
 running on various versions of iOS 6.0 and above.
 
 @return Value specifying whether LP Mobile should autorotate.
 
 @param aManager The LIOLookIOManager shared instance.
 
 */
- (BOOL)lookIOManagerShouldAutorotate:(LIOLookIOManager *)aManager;

/*!
 Like the UIViewController method with the same name, use this method to control whether or not LookIO’s view
 controllers should autorotate its interface elements at any given time. This method will be called for apps
 running on various versions of iOS 6.0 and above.
 
 @return A bit mask specifying which orientations are supported. See UIInterfaceOrientationMask for valid bit-mask values. The value returned by this method must not be 0.
 
 @param aManager The LIOLookIOManager shared instance.
 */
- (NSInteger)lookIOManagerSupportedInterfaceOrientations:(LIOLookIOManager *)aManager;

@end

@interface LIOLookIOManager : NSObject

///---------------------------------------------------------------------------------------
/// @name Properties
///---------------------------------------------------------------------------------------

/*!
 A boolean value indicating whether or not Live Chat is currently enabled.
 */
@property(nonatomic, readonly) BOOL enabled;

/*!
 A boolean value indicating whether or not a chat is currently in progress.
 */
@property(nonatomic, readonly) BOOL chatInProgress;

/*!
 Your application's main window.
 
 @see lookIOManagerMainWindowForHostApp:
 */
@property(nonatomic, retain) UIWindow *mainWindow;

/*!
 The object implementing the LIOLookIODelegate protocol.
 
 @see LIOLookIOManagerDelegate
 */
@property(nonatomic, assign) id<LIOLookIOManagerDelegate> delegate;

///---------------------------------------------------------------------------------------
/// @name Lifecycle Methods
///---------------------------------------------------------------------------------------

/*!
 Returns the shared LIOLookIOManager instance.
 
 @return Returns the shared LIOLookIOManager instance.
 */
+ (LIOLookIOManager *)sharedLookIOManager;

/*!
 Initially setup LP Mobile for your app.
 This method should ideally be called at the end of your app delegate's application:didFinishLaunchingWithOptions: method.
 
 You can optionally specify a delegate which implements the LIOLookIOManagerDelegate protocol to set up callbacks for certain
 events or implement certain features. 
 
 @warning This method must be called AFTER you set up your app's UIWindow instance, which is typically setup by calling
[window makeKeyAndVisible]
 @param aDelegate Delegate which implements the LIOLookIOManagerDelegate protocol
 */

- (void)performSetupWithDelegate:(id<LIOLookIOManagerDelegate>)aDelegate;

/*!
 Displays the LP Mobile chat view and start a chat from your own custom chat button or other UI
 element used to start a chat.
 */
- (void)beginChat;

///---------------------------------------------------------------------------------------
/// @name Custom Button Reporting Methods
///---------------------------------------------------------------------------------------

/*!
 When using a custom Live Chat button instead of the LP Mobile tab, this method is used to report that chat is available in a
 certain part of the app. 
 It is important to report when chat is available to provide accurate availability reports to LP Mobile.
 When LP Mobile launches, the default setting is unavailable, so this method should be used when chat becomes available.
 If you are using the default Live Chat tab, you do not need to use this method.

 */
- (void)setChatAvailable;

/*!
 When using a custom Live Chat button instead of the LP Mobile tab, this method is used to report that chat is unavailable in a
 certain part of the app. It is important to report when chat is available to provide accurate availability reports to LP Mobile.
 When LP Mobile launches, the default setting is unavailable, so this method is useful to report that chat is unavailable after
 it had previously been reported as available.
 If you are using the default Live Chat tab, you do not need to use this method.
 */
- (void)setChatUnavailable;

/*!
 When using a custom Live Chat button instead of the LP Mobile tab, this method is used to report that an invitation to chat is
 being shown to the user, in the form of a chat button or other custom UI element.
 It is important to report when chat is available to provide accurate availability reports to LP Mobile.
 When LP Mobile launches, the default setting is hidden, so this method should be used when the invitation is shown.
 If you are using the default Live Chat tab, you do not need to use this method.
 
 */
- (void)setInvitationShown;

/*!
 When using a custom Live Chat button instead of the LP Mobile tab, this method is used to report that an invitation to chat is
 not being shown to the user.
 It is important to report when chat is available to provide accurate availability reports to LP Mobile.
 When LP Mobile launches, the default setting is hidden, so this method is useful to report that an invitation is hidden after
 it had previously been reported as shown.
 If you are using the default Live Chat tab, you do not need to use this method.
 
 */
- (void)setInvitationNotShown;

///---------------------------------------------------------------------------------------
/// @name Skill Methods
///---------------------------------------------------------------------------------------

/*!
 Reports what sort of skill is required to answer questions that the user might have while using a 
 particular part of your app. This information will be viewable to all available agents.
 
 @param aRequiredSkill The skill required to answer questions at this point in your app.
 */
- (void)setSkill:(NSString *)aRequiredSkill;

///---------------------------------------------------------------------------------------
/// @name Event Methods
///---------------------------------------------------------------------------------------

/*!
 Reports a set of pre-defined user events, including conversion, page view, sign up, sign in and add to cart.
 These events and the related custom data will be displayed to your agent in LivePerson Agent Console.
 
 @param anEvent The event you would like to report. Use the constants kLPEventConversion, kLPEventPageView, kLPEventSignUp,
 kLPEventSignIn and kLPEventAddedToCart to report these events.
  */
- (void)reportEvent:(NSString *)anEvent;

/*!
 Reports a set of pre-defined user events, including conversion, page view, sign up, sign in and add to cart,
 along with your own custom data.
 These events and the related custom data will be displayed to your agent in LivePerson Agent Console.
 
 @param anEvent The event you would like to report. Use the constants kLPEventConversion, kLPEventPageView, kLPEventSignUp,
 kLPEventSignIn and kLPEventAddedToCart to report these events.
 @param someData Any custom data you would like to report along with the event.
 */
- (void)reportEvent:(NSString *)anEvent withData:(id<NSObject>)someData;

///---------------------------------------------------------------------------------------
/// @name Custom Variable Methods
///---------------------------------------------------------------------------------------

/*! 
 Set the initial value for a set of custom variables, by passing a dictionary with set of key-value pairs.
 
 @param aDictionary A dictionary with a set of key-value pairs representing your custom variables.
 */
- (void)addCustomVariables:(NSDictionary *)aDictionary;

/*!
 Sets the initial value for a specific custom variable, by passing a a key-value pair.
 
 @param anObject The object to be set as a custom variable for the key.
 @param aKey The key for the custom variable to be set.
 */
- (void)setCustomVariable:(id)anObject forKey:(NSString *)aKey;

/*!
 Returns the value of a custom variable for a specific key.
 
 @param aKey The key for the custom variable to be returned.
 */
- (id)customVariableForKey:(NSString *)aKey;

/*!
 Returns the value of a custom variable for a specific key.
 
 @param aKey The key for the custom variable to be returned.
 */

///---------------------------------------------------------------------------------------
/// @name Helper Methods
///---------------------------------------------------------------------------------------

/*!
 Check the value of this method to limit auto-rotation of your app when LP Mobile displays view controllers that do
 not support auto rotation, such as UIImagePickerViewController. 
 */
- (BOOL)shouldLockInterfaceOrientation;

// Deprecated methods.
- (void)beginSession DEPRECATED_ATTRIBUTE;
- (void)setSessionExtra:(id)anObject forKey:(NSString *)aKey DEPRECATED_ATTRIBUTE;
- (id)sessionExtraForKey:(NSString *)aKey DEPRECATED_ATTRIBUTE;
- (void)addSessionExtras:(NSDictionary *)aDictionary DEPRECATED_ATTRIBUTE;
- (void)clearSessionExtras DEPRECATED_ATTRIBUTE;
- (void)clearCustomVariables DEPRECATED_ATTRIBUTE;

@end
