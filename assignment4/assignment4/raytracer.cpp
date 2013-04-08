#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "vector.h"

#ifdef __linux__
    // "Compiled for Linux
#else
    // Windows doesn't define these values by default, Linux does
    #define M_PI 3.141592653589793
    #define INFINITY 1e8
#endif

#define MAX_RAY_DEPTH 4

class Geometry
{
public:
    enum
    {
        SPHERE = 1,
        PLANE = 2
    };
    Geometry() { isLight = false; }
    virtual Vector3 getNormal(Vector3 &hitPosition) = 0;
    virtual Vector3 getSurfaceColour() = 0;
    virtual Vector3 getEmissionColour() = 0;
    virtual float getTransparency() = 0;
    virtual float getReflection() = 0;
    virtual int getType() = 0;
    bool getIsLight() { return isLight; }
    void setIsLight(bool light) { isLight = light; }
    virtual bool intersect(Vector3 rayOrigin, Vector3 rayDirection, float *t0 = NULL, float *t1 = NULL) = 0;

protected:
    bool isLight;

};

class Sphere : public Geometry
{
public:
    Vector3 center;
    float radius;
    Vector3 surfaceColour, emissionColour;  // surface color and emission (light)
    float transparency, reflection;         // surface transparency and reflectivity

    Sphere(Vector3 c, float r, Vector3 sc, float refl, float transp, Vector3 ec) {
        center = c;
        radius = r;
        surfaceColour = sc;
        reflection = refl;
        transparency = transp;
        emissionColour = ec;
    }

    int getType() { return SPHERE; }
    Vector3 getNormal(Vector3 &hitPosition) { return hitPosition - center; }
    Vector3 getSurfaceColour() { return surfaceColour; }
    Vector3 getEmissionColour() { return emissionColour; }
    float getTransparency() { return transparency; }
    float getReflection() { return reflection; }
    bool intersect(Vector3 rayOrigin, Vector3 rayDirection, float *t0 = NULL, float *t1 = NULL)
    {
        // Sphere in implicit form: (x - xcenter)^2 + (y - ycenter)^2 + (z - zcenter)^2 - Radius^2 = 0
        // Converted to vector form: (p - c).dotProduct(p - c) - Radius^2 = 0

        // Equation for ray: ray(t) = origin + t * direction, t > 0, where t is a fractional distance along the ray

        // Substituting the ray equation for p in the sphere equation and expanding, we get:
        // (d dot d)t^2 + (2(o - c) dot d)t + ((o - c) dot (o - c) - r^2) = 0
        // This is a quadratic equation, so solving for t gives us our intersection point.
        // A = (d dot d), B = (2(o - c) dot d), C = ((o - c) dot (o - c) - r^2)
        // t = (-B +- sqrt(B^2 - 4AC))/(2.0A)
        // Discriminant tells us # of real solutions. sqrt(B^2 - 4AC)

        Vector3 l = center - rayOrigin;
        float tca = l.dot(rayDirection);
        if (tca < 0) return false; //
        float d2 = l.dot(l) - tca * tca;
        if (d2 > radius * radius) return false;
        float thc = sqrt(radius * radius - d2);
        if (t0 != NULL && t1 != NULL) {
            *t0 = tca - thc;
            *t1 = tca + thc;
        }

        return true;

        //        float A = rayDirection.dot(rayDirection);
        //        float B = 2 * (rayOrigin - center).dot(rayDirection);
        //        float C = ((rayOrigin - center).dot(rayOrigin - center)) - (radius * radius);

        //        float discriminant = B * B - 4.0 * A * C;
        //        if (discriminant < 0) {
        //            return false; // No solutions; no intersect.
        //        }

        //        float intersect1 = (-B + sqrt(B * B - 4.0 * A * C)) / (2.0 * A);
        //        float intersect2 = (-B - sqrt(B * B - 4.0 * A * C)) / (2.0 * A);

        //        if (t0 != NULL && t1 != NULL) {
        //            if (intersect1 < 0) { // First intersect was outside our view
        //                if (intersect2 < *t0) {
        //                    *t0 = intersect2;
        //                    *t1 = intersect1;
        //                }
        //            } else if (intersect1 < *t0) {
        //                *t0 = intersect1;
        //                *t1 = intersect2;
        //            }

        //        }

        //        return true;
    }
};

class Plane : public Geometry
{
public:
    Vector3 point;
    Vector3 normal;
    Vector3 surfaceColour, emissionColour;
    float transparency, reflection;

    Plane(Vector3 p, Vector3 n, Vector3 sc, float refl, float transp, Vector3 ec) {
        point = p;
        normal = n;
        surfaceColour = sc;
        reflection = refl;
        transparency = transp;
        emissionColour = ec;
    }

    int getType() { return PLANE; }
    Vector3 getNormal(Vector3 &hitPosition) { return normal; }
    Vector3 getSurfaceColour() { return surfaceColour; }
    Vector3 getEmissionColour() { return emissionColour; }
    float getTransparency() { return transparency; }
    float getReflection() { return reflection; }
    bool intersect(Vector3 rayOrigin, Vector3 rayDirection, float *t0 = NULL, float *t1 = NULL)
    {
        // A point P is on the plane if N dot (P - Q) = 0 where Q is a point on the plane, and N is the plane normal.
        // Substitute the ray equation E + tD in for the point P in the plane.
        // We end up with N dot (E + tD - Q) = 0
        // Solving for t, we get t = (N dot (Q - E)) / (E dot D)

        if (rayDirection.dot(normal) == 0) {
            return false; // The plane is parallel to the ray
        }

        float t = (normal.dot(point - rayOrigin)) / (rayDirection.dot(normal));

        if (t < 0) {
            return false; // The plane is not visible
        }

        if (t >= 0) {
            if (t0 != NULL && t1 != NULL && t < *t0) {
                *t0 = t;
            }
            return true; // We hit something!
        }
    }
};

float mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}

/**
 * @brief trace Shoots a ray into the scene to see if it intersects any objects.
 * @param rayOrigin The origin point of the ray. Used with the direction to define the ray.
 * @param rayDirection The direction of the ray. Used with the origin to define the ray.
 * @param geometries The list of objects in the scene.
 * @param depth Used to track the current level of recursion. Helpful for limiting reflected rays.
 * @return The colour of the intersected object or the background colour if it didn't intersect any objects.
 */
Vector3 trace(Vector3 rayOrigin, Vector3 rayDirection, std::vector<Geometry *> &geometries, int depth)
{
    float nearestIntersect = INFINITY;
    Geometry *geometry = NULL;

    // Go through the list of objects in the scene and find the closest intersect with an object
    for (unsigned i = 0; i < geometries.size(); ++i) {
        float t0 = INFINITY, t1 = INFINITY;
        if (geometries[i]->intersect(rayOrigin, rayDirection, &t0, &t1)) {
            if (t0 < 0) t0 = t1;
            if (t0 < nearestIntersect) {
                nearestIntersect = t0;
                geometry = geometries[i];
            }
        }
    }

    // If there's no intersection return black or the background color
    if (!geometry) {
        return Vector3(2, 2, 2);
    }

    Vector3 surfaceColour = Vector3(0, 0, 0);
    Vector3 intersectPoint = rayOrigin + rayDirection * nearestIntersect;
    Vector3 intersectNormal = geometry->getNormal(intersectPoint);

    // If the normal and the view direction are not opposite to each other reverse the normal direction
    if (rayDirection.dot(intersectNormal) > 0) {
        intersectNormal = -intersectNormal;
    }

    intersectNormal.normalize();

    double bias = 1e-5; // Add some bias to the point from which we will be tracing
    if ((geometry->getTransparency() > 0 || geometry->getReflection() > 0) && depth < MAX_RAY_DEPTH) {
        float IdotN = rayDirection.dot(intersectNormal);

        // I and N are not pointing in the same direction, so take the inverse
        float facingratio = std::max(0.0f, -IdotN);

        // change the mix value to tweak the effect
        float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);

        Vector3 reflectionDirection = rayDirection - intersectNormal * 2 * rayDirection.dot(intersectNormal);
        Vector3 reflection = trace(intersectPoint + intersectNormal * bias, reflectionDirection, geometries, depth + 1);
        Vector3 refraction = Vector3(0, 0, 0);

        // If the object is also transparent, then compute the refraction ray (transmission)
        if (geometry->getTransparency()) {
            double ior = 1.2, eta = 1 / ior;
            float k = 1 - eta * eta * (1 - IdotN * IdotN);
            Vector3 refractionDirection = rayDirection * eta - intersectNormal * (eta *  IdotN + sqrt(k));
            refraction = trace(intersectPoint - intersectNormal * bias, refractionDirection, geometries, depth + 1);
        }

        // The resulting colour is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColour = (reflection * fresneleffect + refraction * (1 - fresneleffect) * geometry->getTransparency()) * geometry->getSurfaceColour();
    }
    else
    {
        // It's a diffuse object, so we don't have to trace anymore
        for (unsigned i = 0; i < geometries.size(); ++i) {
            // Check if it's a light
            if (geometries[i]->getEmissionColour().x > 0) {
                Vector3 transmission = Vector3(1, 1, 1);
                Vector3 lightDirection = geometries[i]->getNormal(intersectPoint) * (-1);
                lightDirection.normalize();
                for (unsigned j = 0; j < geometries.size(); ++j) {
                    if (i != j) {
                        float t0, t1;
                        if (geometries[j]->intersect(intersectPoint + intersectNormal * bias, lightDirection, &t0, &t1)) {
                            transmission = 0;
                            break;
                        }
                    }
                }

                surfaceColour += geometry->getSurfaceColour() * transmission * std::max(0.0f, intersectNormal.dot(lightDirection)) * geometries[i]->getEmissionColour();
            } else {
                surfaceColour = geometry->getSurfaceColour();
            }
        }
    }

    return surfaceColour + geometry->getEmissionColour();
}

/**
 * @brief render Creates a ray for each pixel of the image, traces it, and returns the colour of the object it hits.
 * @param geometries The list of objects in the scene.
 */
void render(std::vector<Geometry *> &geometries)
{
    // Create our image plane
    unsigned width = 640, height = 480;
    Vector3 *image = new Vector3[width * height], *pixel = image;
    float invWidth = 1 / (float) width, invHeight = 1 / (float) height;
    float fov = 30, aspectratio = (float) width / (float) height;
    float angle = tan(M_PI * 0.5 * fov / 180);

    // Trace the rays
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x, ++pixel) {
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vector3 rayDirection = Vector3(xx, yy, -1);
            rayDirection.normalize();
            *pixel = trace(Vector3(0, 0, 0), rayDirection, geometries, 0);
        }
    }

    // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./image.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (unsigned i = 0; i < width * height; ++i) {
        ofs << (unsigned char)(std::min(1.0f, image[i].x) * 255) <<
        (unsigned char)(std::min(1.0f, image[i].y) * 255) <<
        (unsigned char)(std::min(1.0f, image[i].z) * 255);
    }

    ofs.close();
    delete [] image;
}

int main(int argc, char **argv)
{
    std::vector<Geometry *> geometries;

    // Spheres: position, radius, surface color, reflectivity, transparency, emission color
    geometries.push_back(new Sphere(Vector3(0, 0, -25), 4, Vector3(0.5, 0, 0), 1, 0.5, Vector3(0, 0, 0)));
    //geometries.push_back(new Sphere(Vector3(5, -1, -15), 2, Vector3(0.5, 0.5, 0.0), 0, 0.0, Vector3(0, 0, 0)));
    geometries.push_back(new Sphere(Vector3(5, 0, -30), 3, Vector3(0.0, 0.0, 0.5), 1, 0.0, Vector3(0, 0, 0)));
    geometries.push_back(new Sphere(Vector3(-5, 0, -30), 3, Vector3(0.5, 0.5, 0.0), 1, 0.0, Vector3(0, 0, 0)));

    // Planes: point, normal, surface color, reflectivity, transparency, emission color
    geometries.push_back(new Plane(Vector3(0, -4, -20), Vector3(0, 1, 0), Vector3(0.0, 0.2, 0.0), 0, 0.0, Vector3(0, 0, 0)));

    // Light
    geometries.push_back(new Sphere(Vector3(0, 20, -30), 3, Vector3(0, 0, 0), 0, 0, Vector3(3, 3, 3)));

    render(geometries);
    while (!geometries.empty()) {
        Geometry *sph = geometries.back();
        geometries.pop_back();
        delete sph;
    }

    return 0;
}
