// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#import "UIView+TouchExclusivity.h"
#include "SwallowPersonSearchResultPoiView.h"
#include "App.h"
#include "SwallowSearchParser.h"
#import "UIButton+DefaultStates.h"

@interface SwallowPersonSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

@implementation SwallowPersonSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    self = [super init];
    
    if(self)
    {
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pControlContainer];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];
        
        self.pContentSeparator = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview:self.pContentSeparator];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pLabelsContainer];
        
        self.pJobTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pJobTitleLabel];
        
        self.pWorkingGroupLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pWorkingGroupLabel];
        
        self.pOfficeLocationLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pOfficeLocationLabel];
        
        self.pDeskCodeLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pDeskCodeLabel];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pProfileImageContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pHeadlineContainer addSubview: self.pProfileImageContainer];
        
        self.pProfileImageActivityIndicator = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pProfileImageActivityIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        [self.pProfileImageContainer addSubview:self.pProfileImageActivityIndicator];
        
        self.pPlaceholderImage = [UIImage imageNamed: @"poi_placeholder.png"];
        
        self.pNameLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        self.pNameLabel.numberOfLines = 2;
        self.pNameLabel.lineBreakMode = NSLineBreakByWordWrapping;
        [self.pHeadlineContainer addSubview: self.pNameLabel];
        
        [self setTouchExclusivity: self];
        
        self.alpha = 0.f;
    }
    
    return self;
}

- (void)dealloc
{
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];
    
    [self.pProfileImageActivityIndicator removeFromSuperview];
    [self.pProfileImageActivityIndicator release];
    
    [self.pPlaceholderImage release];
    
    [self.pProfileImageContainer removeFromSuperview];
    [self.pProfileImageContainer release];
    
    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];
    
    [self.pDeskCodeLabel removeFromSuperview];
    [self.pDeskCodeLabel release];
    
    [self.pOfficeLocationLabel removeFromSuperview];
    [self.pOfficeLocationLabel release];
    
    [self.pWorkingGroupLabel removeFromSuperview];
    [self.pWorkingGroupLabel release];
    
    [self.pJobTitleLabel removeFromSuperview];
    [self.pJobTitleLabel release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pContentSeparator removeFromSuperview];
    [self.pContentSeparator release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void) layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const float boundsOccupyMultiplierHeight = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplierHeight;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pControlContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              mainWindowWidth,
                                              mainWindowHeight);
    
    const float headlineHeight = 60.f;
    const float closeButtonSectionHeight = 64.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSeparatorHeight = 32.0f;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + contentSeparatorHeight + headlineHeight);
    
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               0.f,
                                               mainWindowWidth,
                                               headlineHeight);
    
    self.pContentSeparator.frame = CGRectMake(0.0f,
                                              headlineHeight,
                                              mainWindowWidth,
                                              contentSeparatorHeight);
    
    self.pContentContainer.frame = CGRectMake(0.f,
                                              headlineHeight + contentSeparatorHeight,
                                              mainWindowWidth,
                                              contentSectionHeight);
    
    const float labelsSectionOffsetX = 0.f;
    m_labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);
    
    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                             0.f,
                                             m_labelsSectionWidth,
                                             contentSectionHeight);
    
    const float labelHeight = 18.0f;
    const float labelXPadding = 10.0f;
    const float labelSpacing = 6.0f;
    const float labelWidth = mainWindowWidth - labelXPadding * 2.0f;
    
    float currentLabelY = 10.0f;
    
    self.pJobTitleLabel.frame = CGRectMake(labelXPadding,
                                           currentLabelY,
                                           labelWidth,
                                           labelHeight);
    
    currentLabelY += labelHeight + labelSpacing;
    
    self.pWorkingGroupLabel.frame = CGRectMake(labelXPadding,
                                               currentLabelY,
                                               labelWidth,
                                               labelHeight);
    
    currentLabelY += labelHeight + labelSpacing;
    
    self.pOfficeLocationLabel.frame = CGRectMake(labelXPadding,
                                                 currentLabelY,
                                                 labelWidth,
                                                 labelHeight);
    
    currentLabelY += labelHeight + labelSpacing;
    
    self.pDeskCodeLabel.frame = CGRectMake(labelXPadding,
                                           currentLabelY,
                                           labelWidth,
                                           labelHeight);
    
    currentLabelY += labelHeight + labelSpacing;
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
    
    self.pCloseButtonContainer.frame = CGRectMake(0.f,
                                                  closeButtonSectionOffsetY,
                                                  mainWindowWidth,
                                                  closeButtonSectionHeight);

    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
                                         0.f,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);
    
    self.pProfileImageContainer.frame = CGRectMake(0.f, 0.f, headlineHeight, headlineHeight);
    
    self.pProfileImageActivityIndicator.center = CGPointMake(headlineHeight / 2.0f, headlineHeight / 2.0f);
    
    const float titlePadding = 10.0f;
    self.pNameLabel.frame = CGRectMake(headlineHeight + titlePadding,
                                        0.f,
                                        mainWindowWidth - (headlineHeight + titlePadding),
                                        headlineHeight);
    self.pNameLabel.font = [UIFont systemFontOfSize:24.0f];
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    
    m_swallowPersonModel = ExampleApp::Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(m_model);
    
    [self.pProfileImageActivityIndicator startAnimating];
    
    self.pNameLabel.text = [NSString stringWithUTF8String:m_swallowPersonModel.GetName().c_str()];
    
    const std::string jobTitlePrefix = "Job Title: ";
    const std::string workingGroupPrefix = "Working Group: ";
    const std::string officeLocationPrefix = "Location: ";
    const std::string deskCodePrefix = "Desk: ";
    
    self.pJobTitleLabel.text = [NSString stringWithUTF8String:(jobTitlePrefix + m_swallowPersonModel.GetJobTitle()).c_str()];
    self.pWorkingGroupLabel.text = [NSString stringWithUTF8String:(workingGroupPrefix + m_swallowPersonModel.GetWorkingGroup()).c_str()];
    self.pOfficeLocationLabel.text = [NSString stringWithUTF8String:(officeLocationPrefix + m_swallowPersonModel.GetOfficeLocation()).c_str()];
    self.pDeskCodeLabel.text = [NSString stringWithUTF8String:(deskCodePrefix + m_swallowPersonModel.GetDeskCode()).c_str()];
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
    
    [self.pProfileImageContainer setImage:self.pPlaceholderImage];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
//    if(url == m_swallowPersonModel.GetImageUrl())
//    {
        [self.pProfileImageActivityIndicator stopAnimating];
        
        if(success)
        {
            NSData* imageData = [NSData dataWithBytes:&bytes->at(0) length:bytes->size()];
            UIImage *image = [UIImage imageWithData:imageData];
            [self.pProfileImageContainer setImage:image];
            
            [self.pProfileImageContainer.layer removeAllAnimations];
            self.pProfileImageContainer.hidden = false;
        }
//    }
}

- (void) setFullyActive
{
    if(self.alpha == 1.f)
    {
        return;
    }
    
    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    if(self.alpha == 0.f)
    {
        return;
    }
    
    [self animateToAlpha:0.f];
}

- (void) setActiveStateToIntermediateValue:(float)openState
{
    self.alpha = openState;
}

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
{
    return m_pInterop;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    return self.alpha > 0.f;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.alpha = alpha;
     }];
}

- (UILabel*) createLabel:(UIColor*)textColor :(UIColor*)backgroundColor
{
    UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pLabel.textColor = textColor;
    pLabel.backgroundColor = backgroundColor;
    pLabel.textAlignment = NSTextAlignmentLeft;
    return pLabel;
}

- (void) handleClosedButtonSelected
{
    m_pInterop->HandleCloseClicked();
}

@end
