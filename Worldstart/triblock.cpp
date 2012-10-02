/* Written by David Hardee
*  dhardee@gmail.com
*  This will be the basic block
*  for a proposed game called hexwars */
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

class Triblock()
{
    private:
        glVector4d top1, top2, top3, bot1, bot2, bot3;
        bool filled;
        enum blocktype;

    public:
        //Constructor 0 args
        Triblock() :
}
