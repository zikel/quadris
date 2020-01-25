//
//  subject.cc
//  quadris
//
//  Created by Lu Cheng on 2018-07-19.
//  Copyright © 2018 Lu Cheng. All rights reserved.
//

#include "subject.h"
#include "observer.h"
using namespace std;

Subject::Subject(){}

void Subject::notifyObservers(){
    for (auto &o : ob) o->notify(*this);
}

void Subject::attach(shared_ptr<Observer> o){
    ob.emplace_back(o);
}

