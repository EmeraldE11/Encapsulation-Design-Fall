/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
using namespace std;


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight), lander(posUpperRight), thrust(), gravity(-1.625)
   {
      // Set each star to random positions and phases
      for (int i = 0; i < 100; i++)
         {
            stars[i].reset(posUpperRight.getX(), posUpperRight.getY());
         }
      lander.reset(posUpperRight);
   }
   
   Ground ground;
   // Create 50 stars
   Star stars[100];
   Lander lander;
   Thrust thrust;
   double gravity;
};



/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;
   
   ogstream gout;
   
   // draw the stars
   for(int i = 0; i < 100; i++)
   {
      pSimulator->stars[i].draw(gout);
   }

   // draw the ground
   pSimulator->ground.draw(gout);
   
   // draw the lander
   pSimulator->lander.draw(pSimulator->thrust, gout);
   
   
   Acceleration a = pSimulator->lander.input(pSimulator->thrust, pSimulator->gravity);
   
   if (pSimulator->lander.isDead())
   {
      
   }
   else
   {
      pSimulator->thrust.set(pUI);
      double timeStep = 0.1;  // 1/10th a second per frame
      pSimulator->lander.coast(a, timeStep);
   }
   
   if (pSimulator->lander.isFlying())
   {
      double speed = pSimulator->lander.getSpeed();
      double angle = fabs(pSimulator->lander.getAngle().getRadians());

      if ((speed <= pSimulator->lander.getMaxSpeed() && angle < 0.1) && pSimulator->ground.onPlatform(pSimulator->lander.getPosition(), pSimulator->lander.getWidth()))
         pSimulator->lander.land();
      else if (pSimulator->ground.hitGround(pSimulator->lander.getPosition(), pSimulator->lander.getWidth()))
      {
         pSimulator->lander.crash();
      }
   }
   
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
