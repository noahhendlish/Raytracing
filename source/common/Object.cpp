/////////////////////////////////////////////////////////////////////////////
//
//  --- Object.cpp ---
//  Created by Brian Summa
//
//////////////////////////////////////////////////////////////////////////////


#include "common.h"
#include <stdio.h>
#include <stdlib.h>
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

//Line:     P = P1 + t (P2 – P1), t ∈ [0,1]
//Ray:      P = P1 + t V , t ∈ [0,∞)
//Phase 1 (2.1) intersect functions:
//transform ray in world space to object space, call raySphereIntersection() or raySquareIntersection()
        //2.2:  Populate IntersectionValues result
//3.1:  raySphereIntersection()
//              Intersect a ray with a sphere
//4.1:  raySquareIntersection()
//              Intersect a ray with a square

Object::IntersectionValues Sphere::intersect(vec4 p0_w, vec4 V_w){
    //normalize V_w?
    //Let C be the local object definition space (OS) to world coordinate
    //space (WS) Transform the WS ray’s origin Rstart_ws and direction
    //Rdirection_ws to OS.
    
    //modeling transformation: {Model}ws = C {Model}os
    //Origin is just R′start_os = C-1Rstart_ws
 
    //R′direction_os = (C*)-1Rdirection_ws
    //So tws = tos / || R′direction_os ||
    //The intersection point in WS is: Pws = Rstart_ws + tws * Rdirection_ws
    //Pick any vector Vos in the tangent plane: Vws = C Vos
    
    //V_w = normalize(V_w);
    //V_w.w = 0;
    IntersectionValues result;
    vec4 p0_o = INVC*p0_w;
    vec4 V_o =  INVCStar*V_w;
    double L = length(V_o);
    V_o = normalize(V_o);
    
    double t_o = raySphereIntersection(p0_o, V_o);
    //result.t_o = t_o;
    result.t_w = t_o/L;
    //result.P_o = P0_o;
   
    result.P_w = p0_w + result.t_w * V_w;
    result.P_o = p0_o +t_o*V_o;
    result.N_o = result.P_o;
    result.N_o.w = 0;
    result.N_o = normalize(result.N_o);
    //also add this to other obj****:: NORMALIZE
    result.N_w = TRANINVC * result.N_o;
    result.N_w.w = 0;
    result.N_w = normalize(result.N_w);
    return result;
    
}

/* -------------------------------------------------------------------------- */
/* ------ Ray = p0 + t*V  sphere at origin O and radius r    : Find t ------- */
double Sphere::raySphereIntersection(vec4 p0, vec4 V, vec4 O, double r){
    double t   = std::numeric_limits< double >::infinity();
    //TODO: Ray-sphere intersection;
    //in slides (get 2 roots of equation)
    //define a b (from slides), find roots
    //default: doublt t = infinity
    //sphere|P–O|^2 -r^2 =0
    //Substitute ray form into sphere equation: |P0 + tV – O|^2 – r^2 = 0.
    //Solve quadratic equation at2 + bt + c = 0 where
    //a=1; b=2V·(P0–O); c=|P0–O|^2 –r^2
    //(expand|P0+tV–O|2 =|tV+P0–O|2 =|tV+(P0 –O)|2 and recallthat V · V = 1)
    //t=(-b±sqrt(b2 –4ac))/2a
    //0, 1, or 2 solutions!a
    double a = 1;
    double b = dot(2*V,(p0-O));
    double c = length(p0-O)*length(p0-O)  - pow(r,2);;
    double discriminant =(pow(b,2) - 4*a*c);
    if(discriminant<0){
        return t;
    }
    double sqroot = sqrt(discriminant);
    double t_0 = (-b + sqroot)/(2*a);
    double t_1 = (-b - sqroot)/(2*a);
    //take the one that is smaller
    //if less than epsilon (non-negative/zero)
    if(t_0 > EPSILON || t_1 > EPSILON){
        if(t_0 < EPSILON){
            t_0 =std::numeric_limits< double >::infinity();
        }
        if(t_1 < EPSILON){
            t_1= std::numeric_limits< double >::infinity();
        }
        t = fmin(t_0, t_1);
        return fmin(t_0, t_1);
    }
    return t;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
Object::IntersectionValues Square::intersect(vec4 p0_w, vec4 V_w){
    IntersectionValues result;
    //TODO: Ray-square setup
    vec4 p0_o = INVC*p0_w;
    vec4 V_o =  INVCStar*V_w;
    double L = length(V_o);
    V_o = normalize(V_o);
    double t_o = raySquareIntersection(p0_o, V_o);
    result.t_w = t_o/L;
    //result.t_o = t_0;
    //assume p and v are same as obj and pass to above function
    //if( == infinity){std::numeric_limits< double >::infinity();}
    result.P_w = p0_w + result.t_w * V_w;
    result.P_o = p0_o +t_o*V_o;
    result.N_o = vec4(0.0,0.0,1.0,0.0);
    //result.N_o.w = 0;
    //result.N_o = normalize(result.N_o);
    result.N_w = TRANINVC * result.N_o;
    result.N_w.w = 0;
    result.N_w = normalize(result.N_w);
    
    return result;
}

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
double Square::raySquareIntersection(vec4 p0, vec4 V){
    double t   = std::numeric_limits< double >::infinity();
    //TODO: Ray-square intersection;
    //Now you have to write code that intersects unit square on the XY­plane with Z=0.
    // t= N·(S–P1)/N·(P2–P1)
    //p1=p0
    //p2-p1 = V
    //N = (0,0,1,1) (positive z)
    //S = any point in plane (good point to pick is origin (0,0,0,1))
    vec4 N = vec4(0,0,1,0); //where z is positive (normal z is positive)
    vec4 S = vec4(0,0,0,1); //origin
    V = normalize(V);
    //dot product if : dot(N, V) ==0, return inf
    double t_1 = (dot(N, (S-p0)))/(dot(N, V));
    //if t < 0 --> it is infinity (no intersect)
    if(dot(N,V) == 0){
       return t;
    }
    if(t_1 <= EPSILON){
        //t = t_1;
        return t;
    }
    //else find p, check if within bounds: (1,1), (1,-1), (-1,-1), (-1,1)
    //P = P1 + t (P2 – P1)
    //if p in range xy -1 to 1, hit square, return new t
    vec4 P = p0 + t_1*V;
    //if((std::abs(P.x) < 1+EPSILON) && (std::abs(P.y) < 1+EPSILON)){
    if((std::abs(P.x) < 1+EPSILON) && (std::abs(P.y) < 1+EPSILON)){
        return t_1;
    }
    
    return t;
    /*
     vec4 norm = normalize(p0);
     vec4 x_plane = norm.x;
     vec4 y_plane = norm.y;
     vec4 z_plane = norm.z;
     */
}

