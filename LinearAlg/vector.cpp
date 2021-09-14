#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

//Vector2 class
class Vector2 {

    public:
        float xCoord;
        float yCoord;

        float dot(Vector2 otherVector);
        float getAngle(bool inDegrees);
        float getAngle(Vector2 otherVector, bool inDegrees);
        Vector2 getDirectionFromVector(Vector2 otherVector);
        Vector2 getDirectionToVector(Vector2 otherVector);
        float getDistance(Vector2 otherVector);
        float getMagnitude();
        Vector2 getOffsetVector(Vector2 otherVector);
        Vector2 normalize();
        void operator+(Vector2 otherVector);

        Vector2(float angle);
        Vector2(float xCoord, float yCoord);
};

//Constructor using an angle in degrees (Returns a direction vector)
Vector2::Vector2(float angle) {
   if (angle < 0) {
        angle = 0;
    }

    //Convert the angle to radians
    angle *= M_PI;
    angle /= 180;

    xCoord = cosf(angle);
    yCoord = sinf(angle);
    
    //Handles cases where cos(angle) is a very small value
    if (xCoord < 0.001) {
        xCoord = 0;
    }
}

//Constructor using coordinates
Vector2::Vector2(float xCoord, float yCoord) {
    this->xCoord = xCoord;
    this->yCoord = yCoord;
}

//Override for adding vectors
void Vector2::operator+(Vector2 otherVector) {
    xCoord += otherVector.xCoord;
    yCoord += otherVector.yCoord;
}

//Performs the dot product of this vector and the passed vector
float Vector2::dot(Vector2 otherVector) {
    return ((xCoord * otherVector.xCoord) + (yCoord * otherVector.yCoord));
}

//Returns the angle equivalent to this vector
float Vector2::getAngle(bool inDegrees=false) {
    float angle;

    Vector2 unitDirectionVector = normalize();

    angle = atan2f(unitDirectionVector.yCoord, unitDirectionVector.xCoord);

    if (inDegrees == true) {
        angle *= 180; 
        angle /= M_PI;
    }

    return angle;
}

//Returns the angle between this vector and the passed one
float Vector2::getAngle(Vector2 otherVector, bool inDegrees=false) {
    float angle;

    Vector2 unitVector = normalize();
    Vector2 unitOtherVector = otherVector.normalize();

    angle = acosf(unitVector.dot(unitOtherVector));

    if (inDegrees == true) {
        angle *= 180;
        angle /= M_PI;
    }

    return angle;
}

//Returns a Vector between two Vectors going from otherVector --> this Vector
Vector2 Vector2::getDirectionFromVector(Vector2 otherVector) {
    return Vector2(xCoord - otherVector.xCoord, yCoord - otherVector.yCoord);
}

//Returns a Vector between two Vectors going from this Vector --> otherVector
Vector2 Vector2::getDirectionToVector(Vector2 otherVector) {
    return Vector2(otherVector.xCoord - xCoord, otherVector.yCoord - yCoord);
}

//Returns the scalar distance magnitude of this vector from the passed vector
float Vector2::getDistance(Vector2 otherVector) {
    return sqrtf(powf((xCoord - otherVector.xCoord), 2) + powf((yCoord - otherVector.yCoord), 2));
}

//Returns the scalar magnitude or length of this vector
float Vector2::getMagnitude() {
    return sqrtf((xCoord * xCoord) + (yCoord * yCoord));
}

//Returns a new vector from this one as a normalized unit direction vector
Vector2 Vector2::normalize() {
    float magnitude = getMagnitude();

    if (magnitude > 0) {
        return Vector2(xCoord / magnitude, yCoord / magnitude);
    }

    else {
        return *this;
    }
}

/* Function: isLookingAtPoint
 * Description: This function returns true or false based on whether or not the lookVector 
 * lies within a threshold 'direction' to the pointVector. This has a similar effect of determining
 * if the lookVector is looking in the direction of the pointVector. A threshold can be specified between 0 and 1
 * where 0 allows perpindicular to exactly aligned vectors to match, and 1 narrows to exactly aligned vectors only.
*/ 
bool isLookingAtPoint(Vector2 lookVector, Vector2 pointVector, float threshold=0) {

    if (threshold < 0) {
        threshold = 0;
    }

    else if (threshold > 1) {
        threshold = 1;
    }

    //Normalize both vectors involved to narrow the range of values that can be returned.
    Vector2 unitLookVector = lookVector.normalize();
    Vector2 unitPointVector = pointVector.normalize();

    return unitLookVector.dot(unitPointVector) > threshold ? true : false;
}

/* Function: isWithinRadius
 * Description: This function returns true or false based on whether or not the outerPoint Vector2 provided
 * has a distance from the centerPoint Vector less than or equal to the passed radius.
 * This simulates a circular range around the centerPoint with the given radius, and an outer point somewhere
 * inside or outside of that radius.
*/ 
bool isWithinRadius(Vector2 outerPoint, Vector2 centerPoint, float radius) {
    return outerPoint.getDistance(centerPoint) <= radius ? true : false;
}


int main() {
    Vector2 a(2,0);
    Vector2 b(0,4);

    // cout << a.xCoord << " " << a.yCoord << endl;
    // cout << a.normalize().xCoord << " " << a.normalize().yCoord << endl;
    // cout << a.getMagnitude() << endl;
    // cout << b.normalize().xCoord << " " << b.normalize().yCoord << endl;
    // cout << b.getMagnitude() << endl;

    // Vector2 aToB = a.getDirectionToVector(b);
    // Vector2 bToA = b.getDirectionToVector(a);

    // Vector2 aToBDir = aToB.normalize();

    // cout << aToB.xCoord << " " << aToB.yCoord << endl;
    // cout << "aToBDir: " << aToB.normalize().xCoord << " " << aToB.normalize().yCoord << endl;
    // cout << bToA.xCoord << " " << bToA.yCoord << endl;
    // cout << "bToADir: " << bToA.normalize().xCoord << " " << bToA.normalize().yCoord << endl;

    // cout << isLookingAtPoint(a, b, 0) << endl;
    // cout << isWithinRadius(a, b, 2) << endl;

    // Vector2 c(40);
    // cout << c.xCoord << " " << c.yCoord << endl;
    // cout << c.getMagnitude() << endl;
    // cout << a.getAngle(b, true) << endl;
    return 0;
}