#include "Func.h"

Func::Func(){
}

Func::Func(string e){
	T.BuildExp(e);
}

void Func::read(string e){
	T.BuildExp(e);
}

double Func::solve(double x){
	return T.solve(x);
}

void Func::clear(){
	T.clear();
}

bool Func::empty(){
	return T.empty();
}