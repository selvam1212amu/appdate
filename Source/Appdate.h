/*
  ==============================================================================
   
   Copyright (C) 2012 Jacob Sologub
   
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
  
  ==============================================================================
*/

#import <Foundation/Foundation.h>

extern NSString* const kAppdateUrl;

@protocol AppdateDelegate;

#if NS_BLOCKS_AVAILABLE
typedef void (^AppdateCompletionBlock)(NSError* error, NSDictionary* appInfo, BOOL updateAvailable);
#endif

//==============================================================================
/**	Appdate Class 
 
    A simple class that calls Apple's search API service to get info for an 
    Apple "app" ID. The Apple Id can be found on your iTunes Connect App 
    Information page.
 
    The version that's used for comparison against the returned version is from
    the main bundle version retrieved using kCFBundleVersionKey.
 
    @code
    @implementation MyClass
    
    - (void) foo
    {
        Appdate* appdate = [Appdate appdateWithAppleId: yourAppleAppID];
        appdate.delegate = self;
        [appdate checkNow];
    }
 
    - (void) appdateComplete: (NSDictionary*) appInfo updateAvailable: (BOOL) updateAvailable
    {
        // Show the user an alert, take them to the app store etc...
    }

    - (void) appdateFailed: (NSError*) error
    {
        
    }
    @end
    @endcode
 
 */
@interface Appdate : NSObject <NSURLConnectionDelegate>
{
@private
    int appleId;
    id <AppdateDelegate> delegate;
    
   #if NS_BLOCKS_AVAILABLE
    AppdateCompletionBlock completionBlock;
   #endif
}

//==============================================================================
/**	Sets the delegate for this object. 
 
    @see AppdateDelegate
*/
@property (nonatomic, assign) id <AppdateDelegate> delegate;

//==============================================================================
/**	Creates a Appdate object with a specified Apple "app" ID. The Apple Id can
    be found on your iTunes Connect App Information page.
*/
- (id) initWithAppleId: (int) appleIdToUse;

/**	Creates a autoreleased Appdate object with a specified Apple "app" ID. 
    The Apple Id can be found on your iTunes Connect App Information page.
*/
+ (Appdate*) appdateWithAppleId: (int) appleIdToUse;

//==============================================================================
/**	Checks to see if an update is available.
    
    @see AppdateDelegate
*/
- (void) checkNow;

#if NS_BLOCKS_AVAILABLE
/**	Checks to see if an update is available with a completion handler.
 
    @see AppdateCompletionBlock
 */
- (void) checkNowWithBlock: (AppdateCompletionBlock) block;
#endif

@end

//==============================================================================
/**	AppdateDelegate protocol */
@protocol AppdateDelegate <NSObject>

@required
/**	Called when the Appdate object has finished fetching the application info.
    
    @see appdateFailed
*/
- (void) appdateComplete: (NSDictionary*) appInfo updateAvailable: (BOOL) updateAvailable;

/**	Called when the Appdate object has failed to get the application info. This
    can be caused by either a network failure or some other error generated by
    NSURLConnection class.
 
    @see AppdateDelegate#appdateComplete:appInfo:updateAvailable
*/
- (void) appdateFailed: (NSError*) error;
@end