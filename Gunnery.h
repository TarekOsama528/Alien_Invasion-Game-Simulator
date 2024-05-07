#pragma once
#include<iostream>
#include "Base_unit.h"
#include "priQueue.h"
using namespace std;

class Gunnery : public Unit, priQueue<Gunnery> {

};