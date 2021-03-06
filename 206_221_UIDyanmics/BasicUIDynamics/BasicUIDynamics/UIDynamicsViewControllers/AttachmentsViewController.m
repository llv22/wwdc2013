//
//  AttachmentsViewController.m
//  BasicUIDynamics
//
//  Created by ding orlando on 6/23/13.
//  Copyright (c) 2013 ding orlando. All rights reserved.
//

#import "AttachmentsViewController.h"
#import "AttachmentView.h"

@interface AttachmentsViewController ()

@property (nonatomic, weak) IBOutlet UIView* square;
@property (nonatomic, weak) IBOutlet UIView* redSquare;
@property (nonatomic, weak) IBOutlet UIView* blueSquare;
@property (nonatomic) UIDynamicAnimator* animator;
@property (nonatomic) UIAttachmentBehavior* attachmentBehavior;

@end

@implementation AttachmentsViewController

- (void)viewDidLoad
{	
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    UIDynamicAnimator* animator = [[UIDynamicAnimator alloc]initWithReferenceView:self.view];
    UICollisionBehavior* behCollision = [[UICollisionBehavior alloc]initWithItems:@[self.square]];
    behCollision.translatesReferenceBoundsIntoBoundary = YES;
    
    CGPoint squareCenterPoint = CGPointMake(self.square.center.x, self.square.center.y - 100.0);
    CGPoint attachmentPoint = CGPointMake(-25.0f, -25.0f);
    /*
     By default, an attachment behavior uses the center of a view. By using a small offset, we get a more interesting effect which will cause the view to have rotation movement when dragging the attachment.
     */
    UIAttachmentBehavior* attachmentBehavior = [[UIAttachmentBehavior alloc] initWithItem:self.square point:attachmentPoint attachedToAnchor:squareCenterPoint];
    /*
     By default, with spring effect, however, without delegate for frequency and damping
     */
//    [attachmentBehavior setFrequency:4.0];
//    [attachmentBehavior setDamping:0.5];
    // Show visually the attachment points
    self.redSquare.center = attachmentBehavior.anchorPoint;
    
    AttachmentView* containerView = (AttachmentView*)self.view;
    containerView.redSquare = self.redSquare;
    containerView.blueSquare = self.blueSquare;
    containerView.square = self.square;
//    NSLog(@"%f %f", self.redSquare.center.x, self.redSquare.center.y);
    // desc - incorrectly location
//    self.blueSquare.center = CGPointMake(25.0, 25.0);
    
    [animator addBehavior:attachmentBehavior];
    self.animator = animator;
    
    self.attachmentBehavior = attachmentBehavior;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - hanle with gesture in view

-(IBAction)handleAttachmentGesture:(UIPanGestureRecognizer*)gesture{
    CGPoint anchorPoint = [gesture locationInView:self.view];
//    NSLog(@"%f %f", anchorPoint.x, anchorPoint.y);
    [self.attachmentBehavior setAnchorPoint:anchorPoint];
    self.redSquare.center = anchorPoint;//self.attachmentBehavior.anchorPoint;
    [self.view setNeedsDisplay];
}

@end
