//
//  SinaWeiboRequest.h
//  MultiTaskforSina
//
//  Created by ding orlando on 7/12/13.
//  Copyright (c) 2013 ding orlando. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SinaWeiboRequest;
@class SinaWeibo;

// desc - delegate for callback
typedef void (^CRefreshCompletionHandler)(BOOL didReceiveNewPosts);

/**
 * @description 第三方应用访问微博API时实现此此协议，当sdk完成api的访问后通过传入的此类对象完成接口访问结果的回调，应用在协议实现的相应方法中接收访问结果并做对应处理。
 */
@protocol SinaWeiboRequestDelegate <NSObject>
@optional
- (void)request:(SinaWeiboRequest *)request didReceiveResponse:(NSURLResponse *)response;
- (void)request:(SinaWeiboRequest *)request didReceiveRawData:(NSData *)data;
- (void)request:(SinaWeiboRequest *)request didFailWithError:(NSError *)error;
- (void)request:(SinaWeiboRequest *)request didFinishLoadingWithResult:(id)result callback:(CRefreshCompletionHandler)callback;
@end

@interface SinaWeiboRequest : NSObject
{
    NSString                        *url;
    NSString                        *httpMethod;
    NSDictionary                    *params;
    
    NSURLConnection                 *connection;
    NSMutableData                   *responseData;
}

@property (nonatomic, assign) SinaWeibo *sinaweibo;
@property (nonatomic, retain) NSString *url;
@property (nonatomic, retain) NSString *httpMethod;
@property (nonatomic, retain) NSDictionary *params;
@property (nonatomic, assign) id<SinaWeiboRequestDelegate> delegate;
// desc - callback handler assign&weak [warnings : 2013-08-02 22:52:54.683 MultiTaskforSina[1501:70b] Warning: Application delegate received call to -application:performFetchWithCompletionHandler: but the completion handler was never called.]
@property (nonatomic, strong) CRefreshCompletionHandler callback;

+ (SinaWeiboRequest *)requestWithURL:(NSString *)url
                          httpMethod:(NSString *)httpMethod
                              params:(NSDictionary *)params
                            delegate:(id<SinaWeiboRequestDelegate>)delegate;

+ (SinaWeiboRequest *)requestWithURL:(NSString *)url 
                          httpMethod:(NSString *)httpMethod 
                              params:(NSDictionary *)params
                            delegate:(id<SinaWeiboRequestDelegate>)delegate
                            callback:(CRefreshCompletionHandler)callback;

+ (SinaWeiboRequest *)requestWithAccessToken:(NSString *)accessToken
                                         url:(NSString *)url
                                  httpMethod:(NSString *)httpMethod 
                                      params:(NSDictionary *)params
                                    delegate:(id<SinaWeiboRequestDelegate>)delegate;

+ (NSString *)getParamValueFromUrl:(NSString*)url paramName:(NSString *)paramName;
+ (NSString *)serializeURL:(NSString *)baseURL params:(NSDictionary *)params httpMethod:(NSString *)httpMethod;

- (void)connect;
- (void)disconnect;

@end
