#include <math.h>
#include <iostream>
#include <windows.h>
#include <gl\GLU.h>
#include "Camara.h"

#define SQR(x) (x*x)

#define NULL_VECTOR F3dVector(0.0f,0.0f,0.0f)

SF3dVector F3dVector ( float x, float y, float z )
{
        SF3dVector tmp;
        tmp.x = x;
        tmp.y = y;
        tmp.z = z;
        return tmp;
}

float GetF3dVectorLength( SF3dVector * v)
{
        return (float)(sqrt(SQR(v->x)+SQR(v->y)+SQR(v->z)));
}

SF3dVector Normalize3dVector( SF3dVector v)
{
        SF3dVector res;
        float l = GetF3dVectorLength(&v);
        if (l == 0.0f) return NULL_VECTOR;
        res.x = v.x / l;
        res.y = v.y / l;
        res.z = v.z / l;
        return res;
}

SF3dVector operator+ (SF3dVector v, SF3dVector u)
{
        SF3dVector res;
        res.x = v.x+u.x;
        res.y = v.y+u.y;
        res.z = v.z+u.z;
        return res;
}

SF3dVector operator- (SF3dVector v, SF3dVector u)
{
        SF3dVector res;
        res.x = v.x-u.x;
        res.y = v.y-u.y;
        res.z = v.z-u.z;
        return res;
}

SF3dVector operator* (SF3dVector v, float r)
{
        SF3dVector res;
        res.x = v.x*r;
        res.y = v.y*r;
        res.z = v.z*r;
        return res;
}

SF3dVector CrossProduct (SF3dVector * u, SF3dVector * v)
{
        SF3dVector resVector;
        resVector.x = u->y*v->z - u->z*v->y;
        resVector.y = u->z*v->x - u->x*v->z;
        resVector.z = u->x*v->y - u->y*v->x;

        return resVector;
}

float operator* (SF3dVector v, SF3dVector u)    //dot product
{
        return v.x*u.x+v.y*u.y+v.z*u.z;
}

/***************************************************************************************/

Camera::Camera()
{
        //Init with standard OGL values:
        Position = F3dVector (0.0,-185, -50.0);
        ViewDir = F3dVector( 0.0, 0.5, 1.0);
        RightVector = F3dVector (1.0, 0.0, 0.0);
        UpVector = F3dVector (0.0, 1.0, 0.0);
		LeftVector = F3dVector (-1.0, 0.0, 0.0);
        //Only to be sure:
        RotatedX = RotatedY = RotatedZ = 0.0;
}

void Camera::Move (SF3dVector Direction)
{
        Position = Position + Direction;
}

void Camera::RotateX (float Angle)
{
        RotatedX += Angle;
        
        //Rotate viewdir around the right vector:
        ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)
                                                                + UpVector*sin(Angle*PIdiv180));

        //now compute the new UpVector (by cross product)
        //UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void Camera::RotateY (float Angle)
{
        RotatedY += Angle;
        
        //Rotate viewdir around the up vector:
        ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)- RightVector*sin(Angle*PIdiv180));

        //now compute the new RightVector (by cross product)
        RightVector = CrossProduct(&ViewDir, &UpVector);
}

void Camera::RotateZ (float Angle)
{
        RotatedZ += Angle;
        
        //Rotate viewdir around the right vector:
        RightVector = Normalize3dVector(RightVector*cos(Angle*PIdiv180)
                                                                + UpVector*sin(Angle*PIdiv180));
        //now compute the new UpVector (by cross product)
        //UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void Camera::Update( void )
{
        //The point at which the camera looks:
        ViewPoint = Position+ViewDir;
        //as we know the up vector, we can easily use gluLookAt:
		if(Position.x<=-200 && ViewPoint.x<=-209.0)
		{
			Position.x=-200;
		    ViewPoint.x=-209.0;
		}
			if(Position.x>=400 && ViewPoint.x>=409.0)
		{
			Position.x=400;
		    ViewPoint.x=409.0;
		}
       
        gluLookAt(Position.x,Position.y,Position.z,
                                ViewPoint.x,ViewPoint.y,ViewPoint.z,
                                0.0,1.0,0.0);

}

void Camera::MoveBack( float Distance )
{
        Position = Position + (ViewDir*-Distance);
}

void Camera::MoveRight ( float Distance )
{
        Position = Position + (RightVector*Distance);
		
}

void Camera::MoveUp( float Distance )
{
        Position = Position + (UpVector*Distance);
}

void Camera::MoveLeft ( float Distance )
{
        Position = Position + (LeftVector*Distance);
}