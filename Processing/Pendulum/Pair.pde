// The Nature of Code
// <http://www.shiffman.net/teaching/nature>
// Spring 2011
// PBox2D example

// Series of Particles connected with distance joints

class Pair {

  
  Box box1; // base
  Box box2; // moving

  float len;
  float angle;
  // Chain constructor
  Pair(float x, float y) {
    len = 32*4;

    box1 = new Box(x, y, 20, 20, true); 
    box2 = new Box(x, y, 10, 10, false);


    DistanceJointDef djd = new DistanceJointDef();
    // Connection between previous particle and this one
    djd.bodyA = box1.body;
    djd.bodyB = box2.body;
    // Equilibrium length
    djd.length = box2d.scalarPixelsToWorld(len);
    
    // These properties affect how springy the joint is 
    djd.frequencyHz = 0;  // Try a value less than 5 (0 for no elasticity)
    djd.dampingRatio = 0.1; // Ranges between 0 and 1

    // Make the joint.  Note we aren't storing a reference to the joint ourselves anywhere!
    // We might need to someday, but for now it's ok
    DistanceJoint dj = (DistanceJoint) box2d.world.createJoint(djd);
  }



  // Draw the bridge
  void display() {
    Vec2 pos1 = box2d.getBodyPixelCoord(box1.body);
    Vec2 pos2 = box2d.getBodyPixelCoord(box2.body);
    stroke(0);
    line(pos1.x,pos1.y,pos2.x,pos2.y);

    box1.display();
    box2.display();
    
  }
}

