/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - LGPL
  
  See http://www.osirix-viewer.com/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/

#import "N3Geometry.h"
#import "N3BezierCore.h"

// N3BezierDefaultFlatness and N3BezierDefaultSubdivideSegmentLength are defined in N3BezierCore.h

@class NSBezierPath;

enum _N3BezierPathElement {
    N3MoveToBezierPathElement,
    N3LineToBezierPathElement,
    N3CurveToBezierPathElement,
	N3CloseBezierPathElement
};
typedef NSInteger N3BezierPathElement;

@interface N3BezierPath : NSObject <NSCopying, NSMutableCopying, NSCoding>
{
    N3MutableBezierCoreRef _bezierCore;
	CGFloat _length;
    N3BezierCoreRandomAccessorRef _bezierCoreRandomAccessor;
}

- (id)init;
- (id)initWithBezierPath:(N3BezierPath *)bezierPath;
- (id)initWithDictionaryRepresentation:(NSDictionary *)dict;
- (id)initWithN3BezierCore:(N3BezierCoreRef)bezierCore;
- (id)initWithNodeArray:(NSArray *)nodes; // array of N3Vectors in NSValues;

+ (id)bezierPath;
+ (id)bezierPathWithBezierPath:(N3BezierPath *)bezierPath;
+ (id)bezierPathN3BezierCore:(N3BezierCoreRef)bezierCore;

- (BOOL)isEqualToBezierPath:(N3BezierPath *)bezierPath;

- (N3BezierPath *)bezierPathByFlattening:(CGFloat)flatness;
- (N3BezierPath *)bezierPathBySubdividing:(CGFloat)maxSegmentLength;
- (N3BezierPath *)bezierPathByApplyingTransform:(N3AffineTransform)transform;
- (N3BezierPath *)bezierPathByAppendingBezierPath:(N3BezierPath *)bezierPath connectPaths:(BOOL)connectPaths;
- (N3BezierPath *)outlineBezierPathAtDistance:(CGFloat)distance initialNormal:(N3Vector)initalNormal spacing:(CGFloat)spacing;

- (NSInteger)elementCount;
- (CGFloat)length;
- (CGFloat)lengthThroughElementAtIndex:(NSInteger)element; // the length of the curve up to and including the element at index
- (N3BezierCoreRef)N3BezierCore;
- (NSDictionary *)dictionaryRepresentation;
- (N3Vector)vectorAtStart;
- (N3Vector)vectorAtEnd;
- (N3Vector)tangentAtStart;
- (N3Vector)tangentAtEnd;
- (N3Vector)normalAtEndWithInitialNormal:(N3Vector)initialNormal;
- (N3BezierPathElement)elementAtIndex:(NSInteger)index;
- (N3BezierPathElement)elementAtIndex:(NSInteger)index control1:(N3VectorPointer)control1 control2:(N3VectorPointer)control2 endpoint:(N3VectorPointer)endpoint; // Warning: differs from NSBezierPath in that controlVector2 is is not always the end

// extra functions to help with rendering and such
- (N3Vector)vectorAtRelativePosition:(CGFloat)relativePosition; // RelativePosition is in [0, 1]
- (N3Vector)tangentAtRelativePosition:(CGFloat)relativePosition;
- (N3Vector)normalAtRelativePosition:(CGFloat)relativePosition initialNormal:(N3Vector)initialNormal;

- (CGFloat)relalativePositionClosestToVector:(N3Vector)vector;
- (CGFloat)relalativePositionClosestToLine:(N3Line)line;
- (CGFloat)relalativePositionClosestToLine:(N3Line)line closestVector:(N3VectorPointer)vectorPointer;
- (N3BezierPath *)bezierPathByCollapsingZ;

- (NSArray*)intersectionsWithPlane:(N3Plane)plane; // returns NSValues containing N3Vectors of the intersections.
- (NSArray*)intersectionsWithPlane:(N3Plane)plane relativePositions:(NSArray **)returnedRelativePositions;

@end


@interface N3MutableBezierPath : N3BezierPath
{
}

- (void)moveToVector:(N3Vector)vector;
- (void)lineToVector:(N3Vector)vector;
- (void)curveToVector:(N3Vector)vector controlVector1:(N3Vector)controlVector1 controlVector2:(N3Vector)controlVector2;
- (void)close;
- (void)flatten:(CGFloat)flatness;
- (void)subdivide:(CGFloat)maxSegmentLength;
- (void)applyAffineTransform:(N3AffineTransform)transform;
- (void)appendBezierPath:(N3BezierPath *)bezierPath connectPaths:(BOOL)connectPaths;
- (void)setVectorsForElementAtIndex:(NSInteger)index control1:(N3Vector)control1 control2:(N3Vector)control2 endpoint:(N3Vector)endpoint;

@end


