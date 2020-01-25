//
//  subject.h
//  quadris
//
//  Created by Lu Cheng on 2018-07-16.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#ifndef _SUBJECT_HEADER_
#define _SUBJECT_HEADER_

#include <vector>
#include <memory>
#include "info.h"
#include "observer.h"

class Subject {
    std::vector<std::shared_ptr<Observer>> ob;
public:
    Subject();
    void notifyObservers();
    void attach(std::shared_ptr<Observer> o);
    virtual BoardInfo getInfo() = 0;
};

#endif
