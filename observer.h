//
//  observer.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _OBSERVER_HEADER_
#define _OBSERVER_HEADER_

class Subject;
class Board;

class Observer {
    
public:
    virtual void notify(Subject &b) = 0;
};

#endif
