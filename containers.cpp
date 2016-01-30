#include "containers.h"
using namespace std;
using namespace cont;

template <class T>
compNum operator+( compNum cn1) {
    &real += cn1.real;
    &imagine += cn1.imagine;
}

compNum operator-( compNum cn1) {
    &real -= cn1.real;
    &image -= cn1.imagine;

}
