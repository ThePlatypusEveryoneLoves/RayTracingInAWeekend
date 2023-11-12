#include <iostream>
#include <fstream>

#include "Color.h"
#include "Vec3.h"
#include "Ray.h"

double hit_sphere(const Point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}

color ray_color(const ray& r) {
    auto t = hit_sphere(Point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
int main() {

    // Image
    double aspect_ratio = 16.0 / 9.0 ;
    int image_width = 400;

    //Calculate the image height, and ensure that it's at least 1
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //Camera:

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    Point3 camera_center = Point3(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    // Calculate 2 vectors: one from (0,0) to (Width,0) and (0,0) to (0,Height)
    // This makes sure that the Viewport is evenly split
    // We are treating this like a 2d Vector 
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // Calculate the change in the pixel height and width
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel. 
    // (0,0) is top left
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    

    // Render
    std::fstream file("filename.ppm");
    file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);
            //write it out
            color pixel_color = ray_color(r);
            write_color(file, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}