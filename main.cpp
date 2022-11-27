#include "face.hpp"

int main()
{
    bool pretraining = false;
    Face_initialize(pretraining);
    int a = Face_predict("testme1.jpg");
    int b = Face_predict("testme4.jpg");
    int c = Face_predict("testme5.jpg");
    printf("trial 1: %d trial 2: %d trial 3: %d\n",a,b,c);
    return 0;
}