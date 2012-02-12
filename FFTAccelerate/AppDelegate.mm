//
//  AppDelegate.m
//  FFTAccelerate
//
//  Created by Tom on 12-02-12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

#import "ViewController.h"
#import "FFTAccelerate.h"
@implementation AppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;

- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPhone" bundle:nil] autorelease];
    } else {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPad" bundle:nil] autorelease];
    }
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];
    
    //Number of Samples for input(time domain)/output(frequency domain)
    //Must be Power of 2: 2^x
    int numSamples = 1024;

    //Output Array
    float *frequency = (float *)malloc(sizeof(float)*numSamples);
    
    //Input Array
    float *time = (float *)malloc(sizeof(float)*numSamples);
    
    //Fill Input Array with Sin Wave
    for (int i=0; i<numSamples; i++) {
        
        //DC Component frequency[0] = 0.5
        time[i] = 0.25;
        
        //First Harmonic (frequency[1]=1.0)
        time[i] += cos(2*M_PI*i/(float)numSamples);
        
        //Second Harmonic (frequency[2]=1.0)
        time[i] += cos(2*M_PI*2*i/numSamples);
        
        //Third Harmonic (frequency[3]=1.0)
        time[i] += cos(2*M_PI*3*i/numSamples);
    }
    
    
    
    FFTAccelerate *fftAccel = new FFTAccelerate(numSamples);
    fftAccel->doFFTReal(time, frequency, numSamples);
    
    for (int i=0; i<numSamples; i++) {
        NSLog(@"index: %d, amp: %.2f",i, frequency[i]);
    }
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

@end
